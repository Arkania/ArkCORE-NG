
UPDATE gossip_menu_option SET OptionBroadcastTextID=20225, option_id=3, npc_option_npcflag=129 WHERE menu_id=12759 AND id=0;

UPDATE creature_template SET unit_flags=33554432 WHERE entry=52812;

UPDATE creature_template SET unit_flags=33587968, unit_flags2=2099200, InhabitType=4 WHERE entry=52810;

UPDATE creature_template SET unit_flags=32768 WHERE entry=52809;

UPDATE creature_template_addon SET aiAnimKit=1348 WHERE entry=52809;

UPDATE creature_template_addon SET auras="96847" WHERE entry=52812;

UPDATE creature_template_addon SET bytes1=33554432, auras="96850 16245 97577" WHERE entry=52810;

UPDATE creature SET MovementType=2 WHERE guid=117016;

DELETE FROM creature_addon WHERE guid=117016;
INSERT INTO creature_addon VALUES 
(117016, 117016, 0, 0, 257, 0, 1348, 0, 0, "");

DELETE FROM waypoint_data WHERE id=117016;
INSERT INTO waypoint_data VALUES 
(117016, 1, 1841.66, -4524.05, 23.95056, 3.322066, 0, 0, 0, 100, 0),
(117016, 2, 1812.714, -4527.733, 23.27535, 3.247452, 0, 0, 0, 100, 0),
(117016, 3, 1774.411, -4531.47, 24.53489, 3.192474, 0, 0, 0, 100, 0),
(117016, 4, 1753.376, -4512.867, 28.11869, 2.430638, 0, 0, 0, 100, 0),
(117016, 5, 1776.027, -4532.438, 24.38704, 5.603647, 0, 0, 0, 100, 0),
(117016, 6, 1841.377, -4526.104, 23.94983, 0.098003, 0, 0, 0, 100, 0),
(117016, 7, 1857.084, -4520.495, 24.24923, 0.353257, 0, 0, 0, 100, 0),
(117016, 8, 1878.302, -4536.685, 27.32486, 5.619355, 0, 0, 0, 100, 0),
(117016, 9, 1893.079, -4535.359, 28.42798, 0.070515, 0, 0, 0, 100, 0),
(117016, 10, 1894.141, -4500.044, 24.31446, 1.55099, 0, 0, 0, 100, 0),
(117016, 11, 1884.989, -4497.634, 23.31713, 2.882241, 0, 0, 0, 100, 0),
(117016, 12, 1854.319, -4520.133, 24.17787, 3.777595, 0, 0, 0, 100, 0);

DELETE FROM creature WHERE id=52812 AND guid=117018;

DELETE FROM creature WHERE id=52810 AND guid=117017;

delete from vehicle_template_accessory where entry=52809 and accessory_entry=52812;
insert into vehicle_template_accessory values 
(52809, 52812, 0, 1, "", 6, 30000);

delete from vehicle_template_accessory where entry=52812 and accessory_entry=52810;
insert into vehicle_template_accessory values 
(52812, 52810, 0, 1, "", 6, 30000);

delete from npc_spellclick_spells where spell_id=46598 and npc_entry in (52809, 52812);
insert into npc_spellclick_spells values 
(52809, 46598, 0, 0),
(52812, 46598, 0, 0);



