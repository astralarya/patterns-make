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


CREATE OR REPLACE FUNCTION DB_NAME_version() RETURNS text
    LANGUAGE plpgsql
    AS $$
    BEGIN
        RETURN 'DB_VERSION';
    END;
$$;

CREATE OR REPLACE FUNCTION DB_NAME_hash() RETURNS text
    LANGUAGE plpgsql
    AS $$
    BEGIN
        RETURN 'DB_HASH';
    END;
$$;

SET client_min_messages TO ERROR;
CREATE OR REPLACE FUNCTION DB_NAME_hash_status() RETURNS text
    LANGUAGE plpgsql
    AS '
    BEGIN
        RETURN ''DB_STATUS'';
    END;
';

CREATE OR REPLACE FUNCTION DB_NAME_version_long(out version text, out hash text, out status text)
    LANGUAGE SQL
    AS $$ SELECT DB_NAME_version(), DB_NAME_hash(), DB_NAME_hash_status();
$$;
RESET client_min_messages;
