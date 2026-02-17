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
Author: Hans Bihs
--------------------------------------------------------------------*/

#ifndef DIVE_H_
#define DIVE_H_

#include<iostream>
#include"lexer.h"
#include"field.h"
#include"intfield.h"
#include"increment.h"
#include"field2d.h"
#include"intfield2d.h"
#include<vector>

using namespace std;

class dive : public increment, public resize_class
{
public:
    dive(lexer*);
    virtual ~dive();

    intfield flag;         // water/soC12/empty  +  which bc
    intfield solid,topo,porous;
    field solid_dist,topo_dist;
    intfield subgrid;      // for all water cells: number of subgrid
    field2d topobed,solidbed;
    field2d bedlevel;      // combined bedlevel
    field2d zstl_max,zstl_min;
    field2d dataset;
    intfield2d flagslice,subslice;

    int knox,knoy,knoz;
    int incount,utcount,fsfcount,bedcount,surfcount,surfcount_solid,surfnum_solid;
    int **surf,**surf_solid;
    int *in,*ut,*fsf,*bed,*wall;                                // surface counter
    int *subknox,*subknoy,*subknoz;
    int i_dir,j_dir,k_dir;
    int *solid_gcbextra,*topo_gcbextra,*tot_gcbextra;

    //domain decomp
    int *mpx,*mpy,*mpz;                                         // possible subgrids in each directions
    int mx,my,mz;                                               // final subgrids in each direction

    double *xorig,*yorig,*zorig;                                // origin in [m] for each subgrid
    int *xnode,*ynode,*znode;                                   // origin of subgrids in ijk in large grid

    int para1count,para2count,para3count,para4count,para5count,para6count;
    int paraslice1count,paraslice2count,paraslice3count,paraslice4count;
    int paracoslice1count,paracoslice2count,paracoslice3count,paracoslice4count;
    int paraco1count,paraco2count,paraco3count,paraco4count,paraco5count,paraco6count;
    int **para1sf,**para2sf,**para3sf,**para4sf,**para5sf,**para6sf;
    int **paraslice1sf,**paraslice2sf,**paraslice3sf,**paraslice4sf;
    int **para1void,**para2void,**para3void,**para4void,**para5void,**para6void;
    int **para1co,**para2co,**para3co,**para4co,**para5co,**para6co;
    int **paracoslice1sf,**paracoslice2sf,**paracoslice3sf,**paracoslice4sf;
    int *para1,*para2,*para3,*para4,*para5,*para6;              // para surface counter
    int *paraco1,*paraco2,*paraco3,*paraco4,*paraco5,*paraco6;
    int *paraslice1,*paraslice2,*paraslice3,*paraslice4;              // paraslice surface counter
    int *paracoslice1,*paracoslice2,*paracoslice3,*paracoslice4;
    int *nbpara1,*nbpara2,*nbpara3,*nbpara4,*nbpara5,*nbpara6;  // neigbours for each subgrid

    int*** sgfield;

    int **periodicX,*periodicXall;

    //ibm
    int *solid_gcb,*topo_gcb;

    //polygon objects
    int vertice_num;
    // grid refinement
    int maxlevels = 1; // maximum number of grid refinement levels, including the base level (level 1 is the base grid, level 2 is the first refinement level, etc.)
    std::vector<std::vector<std::pair<double[3], double[3]>>> grid_refinement_data; // index is offset by 1, blocks[0] is for level 1, blocks[1] for level 2, etc. Each block is a pair of two 3D points (min and max corners of the block)
};


#endif
