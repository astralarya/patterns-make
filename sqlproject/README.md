sqlproject
=============

**sqlproject** - Barebones SQL project



## Summary

*sqlproject* tracks and automatically commits changes to any \*.sql files in its directory.

The files can be committed to multiple databases, and the changes and commits are tracked independently of each other.

Two databases are defined by default: DEVDB and LIVEDB.  To add more databases, simply add them to DBS.

To commit to DEVDB, simply:

    make

To commit to all databases:

    make all

To create a tarball of the project:

    make tar

The project automatically tracks version info via git, and commits them via version.sql to generate DEVDB\_version(), DEVDB\_hash(), DEVDB\_status(), and DEVDB\_version\_long().


## License

sqlproject

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
