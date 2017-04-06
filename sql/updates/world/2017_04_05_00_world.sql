
UPDATE creature_template SET AIName="", ScriptName="npc_lady_jaina_proudmoore_4968" WHERE entry=4968;

delete from smart_scripts where entryorguid=4968;

UPDATE creature_template SET ScriptName="npc_zelfrax_23864" WHERE entry=23864;

UPDATE gameobject_template SET ScriptName="go_blackhoof_cage_186287" WHERE entry=186287;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=8782 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 8782, 9, 27239);

UPDATE creature_template SET ScriptName="npc_cassa_crimsonwing_23704" WHERE entry=23704;

delete from conditions where SourceTypeOrReferenceId=15 AND SourceGroup=4107 AND SourceEntry=1 AND SourceId=0;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=2465 AND SourceEntry=3158 AND SourceId=0;

delete from gossip_menu where entry=2465 and text_id=3158;

DELETE FROM spell_area WHERE spell=42316;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(42316,  518, 27239, 0, 0, 2098253, 2, 1,  2, 11),
(42316, 2079, 27239, 0, 0, 2098253, 2, 1, 74, 11);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=2465 AND ConditionValue1 in (558,18642,11222);

delete from gossip_menu_option where menu_id=2465 and id=1;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=2465 AND SourceEntry=0 AND SourceId=0;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 2465, 28, 27240);

DELETE FROM gossip_menu_option WHERE menu_id=2465;
INSERT INTO gossip_menu_option VALUES 
(2465, 0, 0, "I'm ready to travel to Stormwind.", 22522, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM creature_text WHERE entry=29611;
INSERT INTO creature_text VALUES 
(29611, 1, 0, "People of Stormwind! Citizens of the Alliance! Your king speaks!", 12, 7, 100, 0, 0, 0, "King Varian Wrynn", 31675),
(29611, 2, 0, "Today marks the first of many defeats for the Scourge! Death knights, once in service of the Lich King, have broken free of his grasp and formed a new alliance against his tyranny!", 12, 7, 100, 0, 0, 0, "King Varian Wrynn", 31676),
(29611, 3, 0, "You will welcome these former heroes of the Alliance and treat them with the respect that you would give to any ally of Stormwind!", 12, 7, 100, 0, 0, 0, "King Varian Wrynn", 31677),
(29611, 4, 0, "Glory to the Alliance!", 12, 7, 100, 0, 0, 0, "King Varian Wrynn", 31678);

UPDATE creature_template SET ScriptName="npc_archmage_malin_2708" WHERE entry=2708;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=8846 AND SourceEntry=0 AND SourceId=0;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 8846, 28, 27241);

delete from waypoint_data where id=6566;
INSERT INTO `waypoint_data` VALUES 
(6566, 0, -8890.74, 612.523, 95.2582, 0, 0, 0, 0, 100, 0),
(6566, 1, -8886.82, 600.705, 95.2586, 0, 0, 0, 0, 100, 0);








