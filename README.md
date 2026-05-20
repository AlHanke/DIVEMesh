
DIVEMesh
=======

Overview
--------

DIVEMesh is a command-line tool for generating structured/unstructured 3D meshes for REEF3D. It is tailored to coastal, fluvial and oceanographic simulations. It provides utilities to create geometry primitives, sample and interpolate bathymetry, partition domains for parallel processing, and export meshes and datasets in formats compatible with simulation engines and visualization tools.

Key features
------------

- Flexible geometry primitives (boxes, cones, cylinders, ellipsoids, hexahedra, etc.)
- Bathymetry and field handling, filtering and hole checking
- Partitioning and decomposition helpers for parallel runs
- Export to REEF3D and visualization in ParaView

Quickstart
----------

1. Build the project (requires a C++ toolchain):

	make

2. Run the command-line executable in `bin/`:

	./bin/DiveMESH input-file

Usage
-----

DIVEMesh is used as a standalone CLI tool for mesh generation and preprocessing before simulations.

User guide and documentation
----------------------------

See the User Guide included in this repository for detailed usage instructions, examples and input file descriptions.

Related projects and references
-------------------------------

- REEFD (simulation engine): https://github.com/REEF3D/REEFD
- REEF3D website and project information: https://reef3d.com

Contributing
------------

The project is currently not accepting external contributions.

License
-------

This project is distributed under the terms specified in the LICENSE file.

Contact
-------

For questions and support, please open a thread on the forum https://www.cfd-online.com/Forums/reef3d/.
