-- (Northrend, Borean Tundra (3128.89 4892.63 1.43)
-- Fixes quest 11949 (Not without a fight!) - Target mobs (25760) were not selectable, removed UNIT_FLAG_NOT_SELECTABLE flag
UPDATE creature_template SET unit_flags=32768 WHERE entry=25760;