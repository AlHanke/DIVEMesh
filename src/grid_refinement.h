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

#ifndef GRIDREFINEMENT_H_
#define GRIDREFINEMENT_H_

#include"driver_declarations.h"

class grid_refinement
{
public:
    grid_refinement(lexer* p, dive* a);
    void start(lexer* p, dive* a);
private:
    void B11_refinement(lexer* p, dive* a);
    void B12_refinement(lexer* p, dive* a){};
    void fill_intermediate_levels(lexer* p, dive* a);
    void print_levels(lexer* p, dive* a);
    const int refinement_ratio = 2; // how many times finer the refined grid is compared to the base grid (e.g., 2 means that the refined grid has half the cell size of the base grid)
};

#endif
