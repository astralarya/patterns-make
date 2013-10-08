-- version.sql
-- Define functions to record version information
--
-- Copyright (C) 2013 Mara Kim
--
-- This program is free software: you can redistribute it and/or modify it under
-- the terms of the GNU General Public License as published by the Free Software
-- Foundation, either version 3 of the License, or (at your option) any later
-- version.
--
-- This program is distributed in the hope that it will be useful, but WITHOUT
-- ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
-- FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
-- details.
--
-- You should have received a copy of the GNU General Public License along with
-- this program. If not, see http://www.gnu.org/licenses/.


CREATE TYPE version_type AS ENUM ('version', 'hash', 'status', 'diff');

CREATE TABLE version (
    id version_type PRIMARY KEY,
    value text
);

TRUNCATE TABLE version;

INSERT INTO version VALUES
    ('version','__DB_VERSION'),
    ('hash', '__DB_HASH'),
    ('status',E'__DB_STATUS'),
    ('diff',E'__DB_DIFF');
