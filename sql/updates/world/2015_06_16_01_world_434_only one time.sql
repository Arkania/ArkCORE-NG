
-- create a female-name place holder for later use..
ALTER TABLE creature_template
    ADD COLUMN femaleName VARCHAR(100) NOT NULL DEFAULT ''
    AFTER name;

