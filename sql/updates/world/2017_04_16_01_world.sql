
UPDATE locales_quest SET QuestGiverTextWindow_loc3="Rotkamm Bastard", QuestGiverTargetName_loc3="Rotkamm Bastard" WHERE Id=26504;

delete from spell_area where area=44 and spell in (80695,80696,80817,80818,81004,81010,81019,81080,81202,81241);

delete from spell_area where area=44 and spell in (82100);

insert into spell_area values 
(80695, 44, 26503, 26567, 0, 0, 0, 1, 74, 9), -- 1
(80696, 44, 26503, 26726, 0, 0, 0, 1, 74, 9),
(80817, 44, 26503, 26567, 0, 0, 0, 1, 74, 9), -- 3
(80818, 44, 26567, 26563, 0, 0, 0, 1, 66, 11),
(81004, 44, 26586, 26560, 0, 0, 0, 1, 74, 9), -- 5
(81010, 44, 26560, 26561, 0, 0, 0, 1, 74, 9),
(81019, 44, 26561, 26562, 0, 0, 0, 1, 74, 9), -- 7
(81080, 44, 26562, 26563, 0, 0, 0, 1, 74, 9),
(81202, 44, 26563, 26616, 0, 0, 0, 1, 74, 9), -- 9 
(81241, 44, 26616, 26726, 0, 0, 0, 1, 74, 9),

(82100, 44, 26503, 26726, 0, 0, 0, 1, 74, 9); -- 19


UPDATE quest_template SET PrevQuestId=26510 WHERE Id=26513;

delete from gameobject_queststarter where id=47 and quest=180;

delete from gameobject_queststarter where id=60 and quest=169;

UPDATE quest_template SET PrevQuestId=26505 WHERE Id=26511;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Murloc Fleischfresser", QuestGiverTargetName_loc3="Murloc Fleischfresser" WHERE Id=26511;

UPDATE gameobject_loot_template SET QuestRequired=1 WHERE entry=154357 AND item=10958;

UPDATE gameobject SET position_x=-9391.23, position_y=-2169.78, position_z=38.75 WHERE guid=5635;

UPDATE gameobject SET position_x=-9326.06, position_y=-2142.33, position_z=44.81 WHERE guid=34;

UPDATE gameobject SET position_x=-9326.52, position_y=-1995.104, position_z=41.487 WHERE guid=2736;

DELETE FROM creature_loot_template WHERE Entry=518 and item in (3614, 58937);
INSERT INTO creature_loot_template VALUES 
(518,  3614, 0, 100, 1, 1, 0, 1, 1, ""), 
(518, 58937, 0, 100, 1, 1, 0, 1, 1, ""); 

UPDATE creature_template SET AIName="", ScriptName="npc_canyon_ettin_43094" WHERE entry=43094;

DELETE FROM creature WHERE id=43248 AND guid=6605;
INSERT INTO creature VALUES 
(6605, 43248, 0, 0, 0, 1, 169, 0, 33288, 0, -9202.24, -2157.7, 57.1858, 1.48215, 120, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature_template_addon SET auras="" WHERE entry=43248;

DELETE FROM creature_addon WHERE guid=6605;
INSERT INTO creature_addon VALUES 
(6605, 0, 0, 65536, 1, 0, "80816 80201");

UPDATE creature SET position_z=159.993 WHERE guid=9364;

UPDATE creature_template_addon SET auras="81079" WHERE entry=43275;

UPDATE creature_template SET minlevel=17, maxlevel=17, faction=12, unit_flags=33088 WHERE entry=43275;

delete from creature where guid in (34373,33907,44142,44129,34054,33886,34373,44136,44138,34296,44147,44141,44131,44143,44153);

DELETE FROM creature_addon WHERE guid=34373;
DELETE FROM creature_addon WHERE guid=34296;
DELETE FROM creature_addon WHERE guid=34054;
DELETE FROM creature_addon WHERE guid=33907;
DELETE FROM creature_addon WHERE guid=33886;


