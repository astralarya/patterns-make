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
