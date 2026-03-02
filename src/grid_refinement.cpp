/*--------------------------------------------------------------------
DIVEMesh
Copyright 2008-2026 Hans Bihs

This file is part of DIVEMesh.

DIVEMesh is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
--------------------------------------------------------------------
Author: Alexander Hanke (@AlHanke)
--------------------------------------------------------------------*/

#include "grid_refinement.h"
#include "driver_headers.h"

#include <utility>

grid_refinement::grid_refinement(lexer* p, dive* a)
{
}

void grid_refinement::start(lexer* p, dive* a)
{
    std::cout << "Starting grid refinement..." << std::endl;
    B11_refinement(p,a);
    B12_refinement(p,a);

    fill_intermediate_levels(p,a);

    print_levels(p,a);
}

/*!
    * @brief Refines the grid in the boxs specified by B11 in control.txt
    *
    * For each box specified in B11, this function will create refinement regions on the desired level.
    * The desired level is determined by the base dx, the B11_dx and the fixed refinement_ratio.
    * Should a box exceed the global domain, it will be truncated to fit within the global domain.
    * If a box has a specified dx that is not finer than the base grid, it will be skipped.
*/
void grid_refinement::B11_refinement(lexer* p, dive* a)
{
    if(p->B11>0)
    {
        const double base_dx = p->dx;
        for(int i=0; i<p->B11; i++)
        {
            const int level = std::ceil(base_dx / p->B11_dx[i] / refinement_ratio);
            if(level < 1)
            {
                continue;
            }
            if(a->grid_refinement_data.size() < level)
            {
                a->grid_refinement_data.resize(level);
                a->nlevels = level+1;
            }
            std::pair<double[3], double[3]> box;
            box.first[0] = p->B11_xs[i]>=p->xmin?p->B11_xs[i]:p->xmin;
            box.first[1] = p->B11_ys[i]>=p->ymin?p->B11_ys[i]:p->ymin;
            box.first[2] = p->B11_zs[i]>=p->zmin?p->B11_zs[i]:p->zmin;
            box.second[0] = p->B11_xe[i]<=p->xmax?p->B11_xe[i]:p->xmax;
            box.second[1] = p->B11_ye[i]<=p->ymax?p->B11_ye[i]:p->ymax;
            box.second[2] = p->B11_ze[i]<=p->zmax?p->B11_ze[i]:p->zmax;

            a->grid_refinement_data[level-1].push_back(box);
        }
    }
}

/*!
    * @brief Fills the intermediate levels between the base grid and the finest refined grid
    *
    * This function will create additional refinement regions for intermediate levels to ensure a smooth transition between the base grid and the finest refined grid.
    * The intermediate levels will cover the finer regions with a cell buffer to avoid abrupt changes in cell size.
*/
void grid_refinement::fill_intermediate_levels(lexer* p, dive* a)
{
    const int buffer_cells = 2; // Number of coarse cells used as buffer. Based on ceil(n_ghost cells / refinement_ratio)
    const double global_min[3] = {p->xmin, p->ymin, p->zmin};
    const double global_max[3] = {p->xmax, p->ymax, p->zmax};

    for (int level = a->nlevels - 1; level > 1; level--)
    {
        if (a->grid_refinement_data.size() < level)
        {
            continue;
        }
        for (const auto& box : a->grid_refinement_data[level-1])
        {
            double min_corner[3];
            double max_corner[3];
            for (int d = 0; d < 3; d++)
            {
                min_corner[d] = box.first[d] - buffer_cells * p->dx * pow(refinement_ratio, level-1);
                max_corner[d] = box.second[d] + buffer_cells * p->dx * pow(refinement_ratio, level-1);
                min_corner[d] = std::max(min_corner[d], global_min[d]);
                max_corner[d] = std::min(max_corner[d], global_max[d]);
            }
            std::pair<double[3], double[3]> intermediate_box;
            std::copy(std::begin(min_corner), std::end(min_corner), std::begin(intermediate_box.first));
            std::copy(std::begin(max_corner), std::end(max_corner), std::begin(intermediate_box.second));
            a->grid_refinement_data[level-2].push_back(intermediate_box);
        }
    }
}

void grid_refinement::print_levels(lexer* p, dive* a)
{
    cout << "Grid refinement levels: " << a->nlevels << endl;
    cout << "Level 0: Base grid" << endl;
    cout << "Min corner: (" << p->xmin << ", " << p->ymin << ", " << p->zmin << ")";
    cout << " Max corner: (" << p->xmax << ", " << p->ymax << ", " << p->zmax << ")" << endl;
    for (int level = 0; level < a->nlevels - 1; level++)
    {
        cout << "Level " << level + 1 << " boxs:" << endl;
        for (const auto& box : a->grid_refinement_data[level])
        {
            cout << "  Min corner: (" << box.first[0] << ", " << box.first[1] << ", " << box.first[2] << ")";
            cout << " Max corner: (" << box.second[0] << ", " << box.second[1] << ", " << box.second[2] << ")" << endl;
        }
    }
}