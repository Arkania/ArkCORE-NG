
-- Borean Tundra
-- Fix quest ID:11949 (.go xyz 3128.89 4892.63 1.43) - Target mobs not selectable, removed unit flag: UNIT_FLAG_NOT_SELECTABLE

UPDATE creature_template SET unit_flags=32768 WHERE entry=25760;

