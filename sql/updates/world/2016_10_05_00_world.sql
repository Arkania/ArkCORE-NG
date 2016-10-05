
DELETE FROM gameobject_loot_template WHERE entry=195492 AND item IN (48766);
INSERT INTO gameobject_loot_template VALUES 
(195492, 48766, 0, 100, 1, 1, 0, 1, 1, "");

update version set db_version="ArkDB 7.9.19 - 2016-OCT-01 for ArkCORE4 NG";

update creature_template_addon set auras="" where entry=35186;

UPDATE creature_template SET ScriptName="npc_kezan_partygoer_35175_86" WHERE entry=35175;

UPDATE creature_template SET ScriptName="npc_kezan_partygoer_35175_86" WHERE entry=35186;

UPDATE creature_template SET npcflag=0 WHERE entry=35175;

UPDATE quest_template SET RequiredItemId1=0, RequiredItemId2=0, RequiredItemId3=0, RequiredItemId4=0, RequiredItemCount1=0, RequiredItemCount2=0, RequiredItemCount3=0, RequiredItemCount4=0, RewardSpell=0 WHERE Id=14153;

UPDATE quest_template SET RewardSpell=0 WHERE Id=14116;

update creature set phaseIds="381 382" where guid=245822 and id=35222;

update creature set phaseIds="378 379 380 381 382" where guid=245772 and id=35053;

update creature set phaseIds="378 379 380 381 382" where guid=245773 and id=35054;

UPDATE quest_template SET PrevQuestId=14120, NextQuestId=14124, ExclusiveGroup=-14121, NextQuestIdChain=14124 WHERE Id=14121;

UPDATE quest_template SET PrevQuestId=14120, NextQuestId=14124, ExclusiveGroup=-14121, NextQuestIdChain=14124 WHERE Id=14122;

UPDATE quest_template SET PrevQuestId=14120, NextQuestId=14124, ExclusiveGroup=-14121, NextQuestIdChain=14124 WHERE Id=14123;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=14125 WHERE Id=14124;

UPDATE quest_template SET PrevQuestId=14124, NextQuestId=0 WHERE Id=14125;

delete from creature_equip_template where entry=35234 and id=2;

update creature set equipment_id=1 where id=35234;

delete from creature where guid in (249190, 249191, 249192);

delete from creature where guid in (249207, 249208, 249209);

UPDATE creature_template SET AIName="", ScriptName="npc_hired_looter_35234" WHERE entry=35234;

delete from smart_scripts where entryorguid = 35234;

UPDATE quest_template SET RequiredRaces=256, SourceItemId=48935, SourceItemCount=1, RequiredSourceItemId1=48935, RequiredSourceItemCount1=1 WHERE Id=14123;

delete from gameobject where guid=403804 and id=195523;

update gameobject_loot_template set QuestRequired=1 where entry=195516 and item=48939;

delete from waypoint_data where id=249327;
insert into waypoint_data values
(249327, 0, -8018.27, 1876.23, 52.6039, 3.46488, 0, 0, 0, 100, 0),
(249327, 1, -8039.93, 1872.76, 52.5144, 3.19488, 0, 0, 0, 100, 0);

delete from waypoint_data where id=249331;
insert into waypoint_data values
(249331, 0, -8022.56, 1878.29, 52.6039, 6.20412, 0, 0, 0, 100, 0),
(249331, 1, -8040.21, 1882.56, 52.5155, 3.19199, 0, 0, 0, 100, 0);

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=249327;

UPDATE creature SET spawndist=0, MovementType=2 WHERE guid=249331;

delete from creature_addon where guid in (249327, 249331);
insert into creature_addon values 
(249331, 249331, 0, 0, 1, 0, ""),
(249327, 249327, 0, 0, 1, 0, "");

DELETE FROM gameobject_loot_template WHERE entry=195518 AND item IN (48941);
INSERT INTO gameobject_loot_template VALUES 
(195518, 48941, 0, 100, 1, 1, 0, 1, 1, "");

DELETE FROM gameobject_loot_template WHERE entry=195515 AND item IN (48937);
INSERT INTO gameobject_loot_template VALUES 
(195515, 48937, 0, 100, 1, 1, 0, 1, 1, "");

UPDATE creature_template SET ScriptName="npc_first_bank_of_kezan_vault_35486" WHERE entry=35486;

DELETE FROM phase_definitions WHERE zoneId=4737;
INSERT INTO phase_definitions VALUES 
(4737, 0, 378, 0, 0, 1, "Kezan from start to -Reward 14109"),
(4737, 1, 378, 0, 0, 1, "Kezan from start to -Reward 14110"),
(4737, 2, 379, 0, 0, 1, "Kezan from reward 14109/14113"),
(4737, 3, 379, 0, 0, 1, "Kezan from reward 14110/14153"),
(4737, 4, 380, 0, 0, 1, "Kezan from reward 14113/14115"),
(4737, 5, 380, 0, 0, 1, "Kezan from reward 14153/14115"),
(4737, 6, 381, 0, 0, 1, "Kezan from reward 14115/14116"),
(4737, 7, 382, 0, 0, 1, "Kezan from reward 14116/14120"),
(4737, 8, 383, 0, 0, 1, "Kezan from reward 14120/14124"),
(4737, 9, 384, 0, 0, 1, "Kezan from reward 14125/14126");

DELETE FROM phase_area WHERE areaId=4737;
INSERT INTO `phase_area` VALUES 
(4737, 0, 14138, 14109, 75, 11, 1, 'Kezan from start to -reward 14109'),
(4737, 1, 14138, 14110, 75, 11, 1, 'Kezan from start to -reward 14110'),
(4737, 2, 14109, 14113, 64, 11, 1, 'Kezan from reward Female 14109 to -reward 14113'),
(4737, 3, 14110, 14153, 64, 11, 1, 'Kezan from reward Male   14110 to -reward 14153'),
(4737, 4, 14113, 14115, 64, 11, 1, 'Kezan from reward Female 14113 to -reward 14115'),
(4737, 5, 14153, 14115, 64, 11, 1, 'Kezan from reward Male   14153 to -reward 14115'),
(4737, 6, 14115, 14116, 64, 11, 1, 'Kezan from reward 14115 to -reward 14116'),
(4737, 7, 14116, 14120, 64, 11, 1, 'Kezan from reward 14116 to -reward 14120'),
(4737, 8, 14120, 14124, 64, 11, 1, 'Kezan from reward 14120 to -reward 14124'),
(4737, 9, 14125, 14126, 64, 11, 1, 'Kezan from reward 14125 to -reward 14126');

UPDATE creature_template SET unit_class=8, unit_flags=33555208 WHERE entry=35486;

UPDATE creature_template SET Mana_mod=.833333 WHERE entry=35486;

DELETE FROM creature_text WHERE entry=35486 and groupid=12;
INSERT INTO creature_text VALUES 
(35486, 12, 0, "$B ", 42, 0, 100, 0, 0, 0, "Empty Line", 0);



