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
Author: Alexander Hanke
--------------------------------------------------------------------*/

#include "grid_refinement.h"
#include "driver_headers.h"

grid_refinement::grid_refinement(lexer* p, dive* a)
{
    cout<<"grid refinement ini";

    cout<<"."<<endl;
}

void grid_refinement::start(lexer* p, dive* a)
{
    cout<<"grid refinement "<<endl;

    if(p->B11>0)
    {
        cout<<"B11: "<<p->B11<<endl;
    }

    if(p->B12>0)
    {
        cout<<"B12: "<<p->B12<<endl;
    }

    cout<<"."<<endl;
}
