
-- maelstrom

UPDATE creature_template SET ScriptName="npc_thrall_45042" WHERE entry=45042;

DELETE FROM npc_spellclick_spells WHERE npc_entry=45005;
INSERT INTO npc_spellclick_spells VALUES 
(45005, 84071, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=45004;
INSERT INTO npc_spellclick_spells VALUES 
(45004, 46598, 0, 0);

delete from vehicle_template_accessory where entry=45004;
-- 45004	45028	0	1	Wyvern - Aggra	6	30000

delete from vehicle_template_accessory where entry=45024;
-- 45024	45027	0	1	Wyvern - Aggra	6	30000

UPDATE creature_template SET faction=35 WHERE entry=45028;

UPDATE creature_template SET InhabitType=4, ScriptName="npc_wyvern_45004" WHERE entry=45004;

UPDATE creature_template SET ScriptName="npc_wyvern_45005" WHERE entry=45005;

UPDATE creature SET spawntimesecs=120 WHERE guid=257393;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` IN (18) AND `SourceGroup` IN (45005) AND `SourceEntry` IN (84071);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(18, 45005, 84071, 0, 0, 28, 0, 27123, 0, 0, 0, 0, 0, '', '');

DELETE FROM waypoint_data WHERE id=4500401;
INSERT INTO waypoint_data VALUES 
(4500401, 0, 833.6, 1052.91, -6.74, 0, 0, 1, 0, 100, 0),
(4500401, 1, 842.7, 1051.95, 1.74, 0, 0, 1, 0, 100, 0),
(4500401, 2, 770.34, 949.726, 38.8637, 0, 0, 1, 0, 100, 0),
(4500401, 3, 792.222, 737.495, 38.8637, 0, 0, 1, 0, 100, 0),
(4500401, 4, 920.221, 698.87, 3.86366, 0, 0, 1, 0, 100, 0),
(4500401, 5, 985.457, 788.34, -31.0252, 0, 0, 1, 0, 100, 0),
(4500401, 6, 937.471, 883.339, -39.7197, 0, 0, 1, 0, 100, 0),
(4500401, 7, 835.682, 853.524, -54.1363, 0, 0, 1, 0, 100, 0),
(4500401, 8, 842.057, 757.833, -80.2752, 0, 0, 1, 0, 100, 0),
(4500401, 9, 948.002, 751.8, -107.581, 0, 0, 1, 0, 100, 0),
(4500401, 10, 947.352, 798.976, -147.995, 0, 0, 1, 0, 100, 0),
(4500401, 11, 893.021, 788.55, -245.521, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4502401;
INSERT INTO waypoint_data VALUES 
(4502401, 0, 1109.14, 649.396, 413.65, 0, 0, 1, 0, 100, 0),
(4502401, 1, 954.589, 657.99, 289.706, 0, 0, 1, 0, 100, 0),
(4502401, 2, 875.491, 621.337, 191.761, 0, 0, 00, 0, 100, 0),
(4502401, 3, 837.281, 565.34, 122.955, 0, 0, 00, 0, 100, 0),
(4502401, 4, 820.571, 487.705, 39.7609, 0, 0, 00, 0, 100, 0),
(4502401, 5, 903.094, 501.446, -36.7289, 0, 0, 00, 0, 100, 0),
(4502401, 6, 935.057, 506.95, -48.1708, 0, 0, 00, 0, 100, 0);

UPDATE creature_template SET ScriptName="npc_wyvern_45024" WHERE entry=45024;

UPDATE creature_template SET faction=1629, InhabitType=4 WHERE entry=45024;

UPDATE creature_template SET Health_mod=1, faction=35 WHERE entry=45027;

-- vashj'ir

DELETE FROM npc_spellclick_spells WHERE npc_entry=39584;
INSERT INTO npc_spellclick_spells VALUES 
(39584, 76546, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41051;
INSERT INTO npc_spellclick_spells VALUES 
(41051, 46598, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41986;
INSERT INTO npc_spellclick_spells VALUES 
(41986, 76546, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41225;
INSERT INTO npc_spellclick_spells VALUES 
(41225, 76546, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=42202;
INSERT INTO npc_spellclick_spells VALUES 
(42202, 78749, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=40760;
INSERT INTO npc_spellclick_spells VALUES 
(40760, 46598, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41057;
INSERT INTO npc_spellclick_spells VALUES 
(41057, 46598, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41157;
INSERT INTO npc_spellclick_spells VALUES 
(41157, 46598, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=40223;
INSERT INTO npc_spellclick_spells VALUES 
(40223, 46598, 1, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=41098;
INSERT INTO npc_spellclick_spells VALUES 
(41098, 46598, 1, 0);





