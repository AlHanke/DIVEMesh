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

#include "dive.h"

dive::dive(lexer* p) : flag(p),
                    solid(p),topo(p),porous(p),
                    solid_dist(p),topo_dist(p),
                    subgrid(p),
                    topobed(p),solidbed(p),
                    bedlevel(p),dataset(p),
                    zstl_min(p),zstl_max(p),
                    flagslice(p),subslice(p)
{
    p->Darray(xorig,p->M10+10);
    p->Darray(yorig,p->M10+10);
    p->Darray(zorig,p->M10+10);

    p->Iarray(xnode,p->M10+10);
    p->Iarray(ynode,p->M10+10);
    p->Iarray(znode,p->M10+10);

    knox=p->knox;
    knoy=p->knoy;
    knoz=p->knoz;

    p->Iarray(subknox,p->M10+1);
    p->Iarray(subknoy,p->M10+1);
    p->Iarray(subknoz,p->M10+1);

    incount=0;
    utcount=0;
    fsfcount=0;
    surfcount=0;
    surfcount_solid=0;
    bedcount=0;

    para1count=0;
    para2count=0;
    para3count=0;
    para4count=0;
    para5count=0;
    para6count=0;

    in.resize(p->M10+1,0);
    ut.resize(p->M10+1,0);
    fsf.resize(p->M10+1,0);
    wall.resize(p->M10+1,0);
    bed.resize(p->M10+1,0);

    para1.resize(p->M10+1,0);
    para2.resize(p->M10+1,0);
    para3.resize(p->M10+1,0);
    para4.resize(p->M10+1,0);
    para5.resize(p->M10+1,0);
    para6.resize(p->M10+1,0);

    paraco1.resize(p->M10+1,0);
    paraco2.resize(p->M10+1,0);
    paraco3.resize(p->M10+1,0);
    paraco4.resize(p->M10+1,0);
    paraco5.resize(p->M10+1,0);
    paraco6.resize(p->M10+1,0);

    paraslice1.resize(p->M10+1,0);
    paraslice2.resize(p->M10+1,0);
    paraslice3.resize(p->M10+1,0);
    paraslice4.resize(p->M10+1,0);

    paracoslice1.resize(p->M10+1,0);
    paracoslice2.resize(p->M10+1,0);
    paracoslice3.resize(p->M10+1,0);
    paracoslice4.resize(p->M10+1,0);

    nbpara1.resize(p->M10+1,-1);
    nbpara2.resize(p->M10+1,-1);
    nbpara3.resize(p->M10+1,-1);
    nbpara4.resize(p->M10+1,-1);
    nbpara5.resize(p->M10+1,-1);
    nbpara6.resize(p->M10+1,-1);

    i_dir=j_dir=k_dir=0;

    if(p->knox>1 || p->B5!=1)
    i_dir=1;

    if(p->knoy>1 || p->B5!=1)
    j_dir=1;

    if(p->knoz>1 || p->B5!=1)
    k_dir=1;

    //object print
    Iarray(solid_gcb,p->M10+2);
    Iarray(topo_gcb,p->M10+2);

    Iarray(solid_gcbextra,p->M10+2);
    Iarray(topo_gcbextra,p->M10+2);
    Iarray(tot_gcbextra,p->M10+2);

    cout<<'.'<<endl;
}

dive::~dive()
{
    delete [] xorig;
    delete [] yorig;
    delete [] zorig;

    delete [] xnode;
    delete [] ynode;
    delete [] znode;

    delete [] solid_gcb;
    delete [] topo_gcb;

    delete [] solid_gcbextra;
    delete [] topo_gcbextra;
    delete [] tot_gcbextra;
}
