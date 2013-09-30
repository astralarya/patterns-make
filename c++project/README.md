c++project
=============

**c++project** - Barebones C++ project

## Summary

*c++project* makes a C++ program capable of parsing both command line and persistent file options.

To build, simply:

    make

Copy this project with

    make tar

to create a \*.tar.gz containing the project.

The project automatically compiles version info into the executable.  You can view this with

    myprog --version

It also automatically generates help and usage output based on the options described in main.cpp using Initializer.  You can view these with

    myprog --help

    myprog --usage

The hash and branch of the current HEAD commit (via `git rev-parse HEAD` and `git rev-parse --abbrev-ref HEAD`), as well as the status and diff of the index file verses the current HEAD commit (via `git status --porcelain` and `git diff`) at the time of compilation are compiled into the executable.  Note that this functionality only records changes while in a git repository, so modifying the project after unpacking the result of `make tar` will not track any changes until a new git repository is initialized. 

You can view this information with

    myprog -#

You can also provide the following arguments to filter the output of this option:

* Show version - `v`

* Show hash - `h`

* Show status - `s`

* Show diff - `d`

These options can be combined.  For example, to show the revision hash and status:

    myprog -#hs

## License

c++project

Copyright (C) 2013 Mara Kim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
