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

CREATE OR REPLACE FUNCTION DB_NAME_hash_status() RETURNS text
    LANGUAGE plpgsql
    AS $$
    BEGIN
        RETURN E'DB_STATUS';
    END;
$$;

CREATE OR REPLACE FUNCTION DB_NAME_version_long(out version text, out hash text, out status text)
    LANGUAGE SQL
    AS $$ SELECT DB_NAME_version(), DB_NAME_hash(), DB_NAME_hash_status();
$$;
