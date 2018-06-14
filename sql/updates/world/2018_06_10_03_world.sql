

DELETE FROM creature WHERE guid=128099;

DELETE FROM creature WHERE guid=128101;

delete from creature_queststarter where quest in (51000, 51001, 51002, 51003, 51004);

delete from creature_questender where quest in (51000, 51001, 51002, 51003, 51004);

delete from creature where id=57013;

-- npc are spawned for player lvl 85, talking with Herezegor Flametusk, and has taken quest 26311/unfamiliar-waters
delete from creature where id=42707;

-- a warrior skill teached by rogue.. wrong
DELETE FROM npc_trainer WHERE entry=2130 and spell=3127;

