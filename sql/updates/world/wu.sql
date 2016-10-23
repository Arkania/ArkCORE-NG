
UPDATE quest_template SET Method=2, RequiredRaces=0, NextQuestId=24520, ExclusiveGroup=0 WHERE Id=24503; 

UPDATE quest_template SET Method=0, Flags=0, RequiredRaces=0 WHERE Id=28414; 

UPDATE creature_template SET type_flags=4256 WHERE entry=34957;
UPDATE creature_template SET type_flags=4256 WHERE entry=34958;
UPDATE creature_template SET type_flags=4256 WHERE entry=34959;


DELETE FROM creature_text WHERE entry=34957;
INSERT INTO creature_text VALUES 
(34957, 0, 0, "Go for the face! Go for the face!", 12, 0, 100, 0, 0, 0, "Ace Say", 35385),
(34957, 0, 1, "Is this the deadbeat?", 12, 0, 100, 0, 0, 0, "Ace Say", 35386),
(34957, 0, 2, "Get 'em!", 12, 0, 100, 0, 0, 0, "Ace Say", 35387),
(34957, 0, 3, "I never liked you anyway!", 12, 0, 100, 0, 0, 0, "Ace Say", 35388),
(34957, 0, 4, "It's payback time!", 12, 0, 100, 0, 0, 0, "Ace Say", 35389),
(34957, 0, 5, "You do NOT mess with us!", 12, 0, 100, 0, 0, 0, "Ace Say", 35390),
(34957, 0, 6, "You lookin' at me?", 12, 0, 100, 0, 0, 0, "Ace Say", 35391),
(34957, 0, 7, "I been waitin' all day for this!", 12, 0, 100, 0, 0, 0, "Ace Say", 35392),
(34957, 1, 0, "What was that thing, $G dude : toots;?", 12, 0, 100, 0, 0, 0, "Ace Say", 48862);

DELETE FROM creature_text WHERE entry=34959;
INSERT INTO creature_text VALUES 
(34959, 0, 0, "Go for the face! Go for the face!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35385),
(34959, 0, 1, "Is this the deadbeat?", 12, 0, 100, 0, 0, 0, "Izzy Say", 35386),
(34959, 0, 2, "Get 'em!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35387),
(34959, 0, 3, "I never liked you anyway!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35388),
(34959, 0, 4, "It's payback time!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35389),
(34959, 0, 5, "You do NOT mess with us!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35390),
(34959, 0, 6, "You lookin' at me?", 12, 0, 100, 0, 0, 0, "Izzy Say", 35391),
(34959, 0, 7, "I been waitin' all day for this!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35392),
(34959, 1, 0, "Why's the ground shaking, $N?!", 12, 0, 100, 0, 0, 0, "Izzy Say", 48861);




	
delete from creature where id=37179;

UPDATE creature SET spawndist=0, MovementType=0 WHERE guid=249060 and id=48526;

UPDATE creature_template_addon SET auras="90366" WHERE entry=48526;

UPDATE creature_template SET faction=2204, unit_flags=8, unit_flags2=67584, VehicleId=579, ScriptName="npc_bilgewater_buccaneer_37213" WHERE entry=37213;

update creature set modelid=31295 where id=37203 and guid=245281;

UPDATE creature_template SET ScriptName="npc_fourth_and_goal_target_37203" WHERE entry=37203;

delete from spell_script_names where spell_id=70052;
insert into spell_script_names values 
(70052, "spell_kick_footbomb_70052");

delete from creature where id=42196 and guid=52753;
insert into creature values 
(52753, 42196, 648, 0, 0, 1, 378, 20024, 0, -8421.41, 1482.6, 100.6743, 0, 500, 0, 0, 6141, 0, 0, 0, 0, 0);

UPDATE creature_template SET InhabitType=5, ScriptName="npc_deathwing_48572" WHERE entry=48572;
UPDATE creature_template SET minlevel=88, maxlevel=88, faction=14, unit_flags=33587968 WHERE entry=48572;

UPDATE creature_template SET InhabitType=5 WHERE entry=42196;

DELETE FROM creature_template_addon WHERE entry=48572;
INSERT INTO creature_template_addon VALUES 
(48572, 0, 0, 50331648, 1, 0, "");





UPDATE quest_template SET RequiredSourceItemId1=47044, RequiredSourceItemId4=0, RequiredSourceItemCount1=10, RequiredSourceItemCount4=0 WHERE Id=14110;

UPDATE quest_template SET RequiredSourceItemId1=47044, RequiredSourceItemId4=0, RequiredSourceItemCount1=10, RequiredSourceItemCount4=0 WHERE Id=14109;

UPDATE creature_template SET gossip_menu_id=10618, ScriptName="npc_fbok_bank_teller_35120" WHERE entry=35120;

UPDATE quest_template SET RewardSpell=0 WHERE Id=14110;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35363 WHERE menu_id=10622 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35383 WHERE menu_id=10624 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35354 WHERE menu_id=10620 AND id=0;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14113;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14153;

delete from phase_definitions where zoneId=4737;
insert into phase_definitions values 
(4737, 0, 378, 0, 0, 1, "Kezan from start to -Reward 14109"),
(4737, 1, 378, 0, 0, 1, "Kezan from start to -Reward 14110"),
(4737, 2, 379, 0, 0, 1, "Kezan from reward 14109/14109"),
(4737, 3, 379, 0, 0, 1, "Kezan from reward 14110/14110"),
(4737, 4, 380, 0, 0, 1, "Kezan from reward 14113/14113"),
(4737, 5, 380, 0, 0, 1, "Kezan from reward 14153/14153"),
(4737, 6, 381, 0, 0, 1, "Kezan from reward 14115/14115"),
(4737, 7, 382, 0, 0, 1, "Kezan from reward 14116/14116"),
(4737, 8, 383, 0, 0, 1, "Kezan from reward 14120/14120"),
(4737, 9, 384, 0, 0, 1, "Kezan from reward 14122/14122");

delete from phase_area where areaId=4737;
insert into phase_area values 
(4737, 0, 14138, 14109, 75, 11, 1, "Kezan from start to -reward 14109"),
(4737, 1, 14138, 14110, 75, 11, 1, "Kezan from start to -reward 14110"),
(4737, 2, 14109, 14113, 64, 11, 1, "Kezan from reward Female 14109 to -reward 14113"),
(4737, 3, 14110, 14153, 64, 11, 1, "Kezan from reward Male   14110 to -reward 14153"),
(4737, 4, 14113, 14115, 64, 11, 1, "Kezan from reward Female 14113 to -reward 14115"),
(4737, 5, 14153, 14115, 64, 11, 1, "Kezan from reward Male   14153 to -reward 14115"),
(4737, 6, 14115, 14116, 64, 11, 1, "Kezan from reward 14115 to -reward 14116"),
(4737, 7, 14116, 14120, 64, 11, 1, "Kezan from reward 14116 to -reward 14120"),
(4737, 8, 14120, 14122, 64, 11, 1, "Kezan from reward 14120 to -reward 14122"),
(4737, 9, 14122, 14126, 64, 11, 1, "Kezan from reward 14122 to -reward 14126");










UPDATE creature_template SET ScriptName="npc_chip_endale_35054" WHERE entry=35054;

DELETE FROM creature_text WHERE entry=35054 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(35054, 0, 0, "Make sure you pull plenty of moolah out of the bank. I don't want you buying any of that cheap clothing you usually like to wear. This party's important!", 12, 0, 100, 0, 0, 0, "Chip Endale", 49022);

DELETE FROM creature_text WHERE entry=35054 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35054, 1, 0, "You're dressed to impress! Use your new powers below to make your party guests happy!", 12, 0, 100, 0, 0, 0, "Chip Endale", 35444);

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_partygoer_35175" WHERE entry=35175;

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_partygoer_35186" WHERE entry=35186;

DELETE FROM creature WHERE id=24110 AND guid=254315;
INSERT INTO creature VALUES 
(254315, 24110, 648, 0, 0, 1, "379", 0, 0, -8482.854, 1341.462, 112.348, 0, 500, 0, 0, 6141, 0, 0, 0, 0, 0);

UPDATE creature_template SET AIName="", ScriptName="npc_elm_general_purpose_bunny_large_24110" WHERE entry=24110;

delete from smart_scripts where entryorguid in (24110, 35175, 35186);

UPDATE creature_template SET InhabitType=2 WHERE entry=35185;

UPDATE creature_template_addon SET bytes1=50331648 WHERE entry=35185;

UPDATE creature_template SET ScriptName="" WHERE entry=35185;

UPDATE gameobject_template SET ScriptName="go_kajamite_deposit_195488" WHERE entry=195488;

update gameobject set phaseIds="378 379 380 382" where id=195489;



DELETE FROM creature_text WHERE entry=35175;
INSERT INTO creature_text VALUES 
(35175, 1, 0, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40222),
(35175, 6, 0, "A fresh glass of bubbly. Just what the doctor ordered, $N.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35417),
(35175, 6, 1, "Thanks for the refill, $G sir : ma'am;!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35418),
(35175, 6, 2, "This sparkling white wine is delicious! Wherever did you get it?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35419),
(35175, 6, 3, "I think this one will have to be my last. I'm driving home after the party.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35420),

(35175, 2, 0, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40223),
(35175, 7, 0, "Thanksh!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35421),
(35175, 7, 1, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35422),
(35175, 7, 2, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35423),
(35175, 7, 3, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35424),

(35175, 3, 0, "If only I had someone to dance with.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40224),
(35175, 8, 0, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35425),
(35175, 8, 1, "How do you like my moves, $N?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35426),
(35175, 8, 2, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35427),
(35175, 8, 3, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35428),

(35175, 4, 0, "I love fireworks!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40225),
(35175, 9, 1, "Wow! That sure beats this puny, little sparkler!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35429),
(35175, 9, 2, "You really stop at no expense, $N! Amazing!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35430),
(35175, 9, 3, "Best... Party... Evar!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35431),
(35175, 9, 4, "Woo hoo, fireworks! More, more!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35432),

(35175, 5, 0, "This is delicious! Are there more hors d'oeuvres?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40226),
(35175, 10, 0, "Thanks. I was almost out. So hungry!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35433),
(35175, 10, 1, "These are the most delicious hors d'oeurves I have ever tasted. You must share your recipe, $N!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35434),
(35175, 10, 2, "Finger licking good!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35435),
(35175, 10, 3, "Nom, nom, nom!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35436);

DELETE FROM creature_text WHERE entry=35186;
INSERT INTO creature_text VALUES 
(35186, 1, 0, "I could really use a refill on my drink here.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40222),
(35186, 6, 0, "A fresh glass of bubbly. Just what the doctor ordered, $N.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35417),
(35186, 6, 1, "Thanks for the refill, $G sir : ma'am;!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35418),
(35186, 6, 2, "This sparkling white wine is delicious! Wherever did you get it?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35419),
(35186, 6, 3, "I think this one will have to be my last. I'm driving home after the party.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35420),

(35186, 2, 0, "Ugh... I need a bucket!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40223),
(35186, 7, 0, "Thanksh!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35421),
(35186, 7, 1, "I feel much better now...hic!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35422),
(35186, 7, 2, "Oh, my head hurtsh.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35423),
(35186, 7, 3, "Shorry about your shoes.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35424),

(35186, 3, 0, "If only I had someone to dance with.", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40224),
(35186, 8, 0, "A disco ball?! Groovy!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35425),
(35186, 8, 1, "How do you like my moves, $N?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35426),
(35186, 8, 2, "We should totally have a pants-off dance-off!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35427),
(35186, 8, 3, "Shake it like a goblinoid picture!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35428),

(35186, 4, 0, "I love fireworks!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40225),
(35186, 9, 1, "Wow! That sure beats this puny, little sparkler!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35429),
(35186, 9, 2, "You really stop at no expense, $N! Amazing!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35430),
(35186, 9, 3, "Best... Party... Evar!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35431),
(35186, 9, 4, "Woo hoo, fireworks! More, more!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35432),

(35186, 5, 0, "This is delicious! Are there more hors d'oeuvres?", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 40226),
(35186, 10, 0, "Thanks. I was almost out. So hungry!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35433),
(35186, 10, 1, "These are the most delicious hors d'oeurves I have ever tasted. You must share your recipe, $N!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35434),
(35186, 10, 2, "Finger licking good!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35435),
(35186, 10, 3, "Nom, nom, nom!", 12, 0, 100, 0, 0, 0, "Kezan Partygoer", 35436);


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





DELETE FROM `creature_template_addon` WHERE `entry`=34840;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (34840,0,0,0,1,0,'70329');

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry` in (35063, 35234);

DELETE FROM `smart_scripts` WHERE `entryorguid`IN(35063,35234) AND `source_type`=0;

INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(35063,0,0,0,8,0,100,0,70330,0,0,500,1,0,20000,0,0,0,0,1,0,0,0,0,0,0,0,'on_spell_hit kezan citizen say random'),
(35234,0,0,0,0,0,100,0,5000,11000,7800,21300,11,6257,0,0,0,0,0,2,0,0,0,0,0,0,0,'Cast Torch Toss'),
(35234,0,1,2,8,0,100,0,70330,0,0,500,11,67041,0,0,0,0,0,17,0,20,0,0,0,0,0,'Looter On Spell hit, cast create quest item.'),
(35234,0,2,0,61,0,100,0,0,0,0,0,37,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Looter On Spell hit, die.');



DELETE FROM phase_area WHERE areaId=4737 AND entry=8;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 8, 14120, 14125, 64, 1, 1, "Kezan from reward 14120 to not taken 14125");

DELETE FROM phase_area WHERE areaId=4737 AND entry=9;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 9, 14125, 14126, 74, 11, 1, "Kezan from incomplete 14125 to -reward 14126");

DELETE FROM creature WHERE guid IN (16465, 248944);
INSERT INTO creature VALUES 
( 16465, 34692, 648, 0, 0, 1, "384 ", 0, 1, -8414.11, 1329.39, 102.646, 2.12930, 300, 0, 0, 111, 259, 0, 0, 0, 0), 
(248944, 34692, 648, 0, 0, 1, "379 380 381 382 383 ", 0, 1, -8425.34, 1347.73, 105.055, 4.61407, 300, 0, 0, 111, 259, 0, 0, 0, 0);



DELETE FROM creature WHERE id=34874 AND guid=16744;
INSERT INTO creature VALUES 
(16744, 34874, 648, 0, 0, 1, "384 ", 29472, 0, -8435.33, 1316.88, 102.632, 0.959931, 300, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=35054 AND guid=16745;
INSERT INTO creature VALUES 
(16745, 35054, 648, 0, 0, 1, "384 ", 29555, 1, -8377.3, 1335.13, 102.397, 4.41568, 300, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseIds="383 384 " WHERE guid=13300;

delete from creature where guid=248973 and id=37680;

UPDATE creature SET phaseIds="378 379 380 381 382 383 " WHERE guid=245821;

DELETE FROM gameobject WHERE id=201745;
	
UPDATE creature_template SET minlevel=5, maxlevel=5, faction=2204, unit_flags=32776 WHERE entry=37598;

UPDATE creature_template SET faction=2204, unit_flags=33554688 WHERE entry=37599;

delete from event_scripts where id=201734;

UPDATE gameobject_template SET data2=0 WHERE entry=201734;

delete from creature where id=37599;

UPDATE creature_template SET npcflag=16777219 WHERE entry=37598;
UPDATE creature_template SET npcflag=0 WHERE entry=37599;

delete from npc_spellclick_spells where npc_entry=37598;
insert into npc_spellclick_spells values 
(37598, 46598, 1, 0);

delete from npc_spellclick_spells where npc_entry=37599;
insert into npc_spellclick_spells values 
(37599, 46598, 1, 0);

delete from vehicle_template_accessory where entry = 37598;
insert into vehicle_template_accessory values 
(37598, 37599, 0, 1, "Gasbot", 6, 30000),
(37598, 37599, 1, 1, "Gasbot", 6, 30000),
(37598, 37599, 2, 1, "Gasbot", 6, 30000),
(37598, 37599, 3, 1, "Gasbot", 6, 30000);

UPDATE creature_template SET ScriptName="npc_gasbot_37598" WHERE entry=37598;

DELETE FROM creature_template_addon WHERE entry=37598;

UPDATE creature_template SET InhabitType=4 WHERE entry=37599;

DELETE FROM creature_template_addon WHERE entry=37599;
INSERT INTO creature_template_addon VALUES 
(37599, 0, 0, 50331648, 1, 0, "");

UPDATE gameobject_template SET ScriptName="go_447_fire_201745" WHERE entry=201745;

UPDATE gameobject_template SET ScriptName="go_gasbot_control_panel_201736" WHERE entry=201736;




DELETE FROM waypoint_data WHERE id=37676;
INSERT INTO waypoint_data VALUES 
(37676, 0, -8425.034, 1324.767, 101.9176, 1.624928, 0, 1, 0, 100, 0),
(37676, 1, -8419.421, 1333.294, 102.3921, 0.120894, 0, 1, 0, 100, 0),
(37676, 2, -8400.216, 1340.02, 101.9965, 0.336878, 0, 1, 0, 100, 0),
(37676, 3, -8374.318, 1349.09, 101.7101, 0.336878, 0, 1, 0, 100, 0),
(37676, 4, -8356.793, 1343.94, 97.13021, 6.070287, 0, 1, 0, 100, 0),
(37676, 5, -8334.182, 1331.252, 87.02554, 5.771836, 0, 1, 0, 100, 0),
(37676, 6, -8312.973, 1313.47, 85.94204, 5.854303, 0, 1, 0, 100, 0),
(37676, 7, -8251.665, 1291.138, 44.66432, 6.101694, 0, 1, 0, 100, 0),
(37676, 8, -8129.597, 1297.265, 20.09859, 0.030566, 0, 1, 0, 100, 0),
(37676, 9, -8124.546, 1350.449, 17.52898, 1.54638, 0, 1, 0, 100, 0),
(37676, 10, -8121.129, 1384.686, 23.69516, 1.475694, 0, 1, 0, 100, 0),
(37676, 11, -8109.652, 1442.592, 10.3243, 1.35003, 0, 1, 0, 100, 0),
(37676, 12, -8106.67, 1465.324, 10.09128, 1.471767, 0, 1, 0, 100, 0),
(37676, 13, -8118.039, 1477.232, 10.28002, 2.31607, 0, 1, 0, 100, 0),
(37676, 14, -8117.421, 1485.756, 10.33561, 1.483548, 0, 1, 0, 100, 0),
(37676, 15, -8103.097, 1500.302, 9.948122, 0.796325, 0, 1, 0, 100, 0),
(37676, 16, -8096.165, 1650.852, 10.13463, 1.62492, 0, 1, 0, 100, 0),
(37676, 17, -8097.564, 1682.969, 14.16721, 1.58565, 0, 1, 0, 100, 0),
(37676, 18, -8124.712, 1710.631, 27.03143, 2.217896, 0, 1, 0, 100, 0),
(37676, 19, -8131.997, 1720.4, 31.38888, 2.166845, 0, 1, 0, 100, 0),
(37676, 20, -8136.745, 1735.666, 34.38874, 1.87232, 0, 1, 0, 100, 0),
(37676, 21, -8136.068, 1754.767, 34.43086, 1.463913, 0, 1, 0, 100, 0),
(37676, 22, -8120.522, 1778.391, 29.24019, 0.988747, 0, 1, 0, 100, 0),
(37676, 23, -8108.241, 1788.452, 29.47246, 0.686369, 0, 1, 0, 100, 0),
(37676, 24, -8095.225, 1804.285, 33.63052, 0.882719, 0, 1, 0, 100, 0),
(37676, 25, -8082.288, 1826.98, 41.06969, 1.055506, 0, 1, 0, 100, 0),
(37676, 26, -8068.063, 1822.022, 42.92684, 5.956391, 0, 1, 0, 100, 0),
(37676, 27, -8040.964, 1824.189, 41.81443, 6.14096, 0, 1, 0, 100, 0),
(37676, 28, -7994.833, 1822.505, 22.09344, 0.360428, 0, 1, 0, 100, 0),
(37676, 29, -7956.281, 1836.39, 9.489035, 0.26618, 0, 1, 0, 100, 0),
(37676, 30, -7886.333, 1834.303, 4.354057, 6.266622, 0, 1, 0, 100, 0),
(37676, 31, -7886.333, 1834.303, 4.354057, 0.171932, 0, 1, 0, 100, 0),
(37676, 32, -7859.835, 1840.59, 7.684859, 6.262692, 0, 1, 0, 100, 0),
(37676, 33, -7849.395, 1840.313, 7.587613, 6.254839, 0, 1, 0, 100, 0),
(37676, 34, -7849.395, 1840.313, 7.587613, 6.254839, 0, 1, 0, 100, 0);

UPDATE creature_template SET gossip_menu_id=12494 WHERE entry=34668;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=12494 AND SourceEntry=17576 AND SourceId=0 AND ConditionTypeOrReference=8 AND ConditionTarget=0 AND ConditionValue1=14125;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 12494, 17576, 8, 14125);

delete from spell_scripts where id=92629;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES 
(92629,0,0,6,648,0,0,-7849.25,1838.15,7.72742,1.56003);

UPDATE creature_template SET ScriptName="npc_hot_rod_37676" WHERE entry=37676;

delete from npc_spellclick_spells where npc_entry in (37676, 37680);
insert into npc_spellclick_spells values 
(37676, 46598, 1, 0);

delete from vehicle_template_accessory where entry=37676;
insert into vehicle_template_accessory values 
(37676, 37680, 0, 1, "sassy driving hot rod", 6, 30000);

UPDATE quest_template SET Flags=262144 WHERE Id=14126;

delete from creature where id=37676 and guid=248986;

UPDATE creature_template SET ScriptName="npc_trade_prince_gallywix_35222" WHERE entry=35222;

DELETE FROM creature_text WHERE entry=35053 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(35053, 2, 0, "We're through, $N! I'm with Chip now.", 12, 0, 100, 0, 0, 0, "Candy Cane Say", 49306);

DELETE FROM creature_text WHERE entry=35054 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(35054, 2, 0, "We're through, $N! I'm with Candy now.", 12, 0, 100, 0, 0, 0, "Chip Endale Say", 49307);



update creature set phaseIds="170" where guid=245968;
update creature set phaseIds="170 171 172" where guid=245965;
UPDATE creature SET phaseIds="185" WHERE guid=247591;
UPDATE creature SET phaseIds="184 185" WHERE guid=247592;
UPDATE creature SET phaseIds="179" WHERE guid=247593;
UPDATE creature SET phaseIds="179" WHERE guid=247594;
delete from creature where guid = 245962;

update creature set phaseIds="179" where id in (36188, 36418, 36422, 36424, 36426, 36428, 36468, 36469, 36513, 36518, 36519, 36523, 36524);

UPDATE creature SET phaseIds="170 171 172" WHERE id=36179;
UPDATE creature SET phaseIds="179" WHERE guid=246053 AND id=35917;
UPDATE creature SET phaseIds="179" WHERE guid=246054 AND id=36063;
UPDATE creature SET phaseIds="179" WHERE guid=246055 AND id=36578;
UPDATE creature SET phaseIds="179" WHERE guid=246067 AND id=36429;
UPDATE creature SET phaseIds="179" WHERE guid=246068 AND id=36501;
UPDATE creature SET phaseIds="179" WHERE guid=246069 AND id=38738;
UPDATE creature SET phaseIds="179" WHERE guid=246070 AND id=36467;
UPDATE creature SET phaseIds="179" WHERE guid=246073 AND id=36520;
UPDATE creature SET phaseIds="179" WHERE guid=246074 AND id=36521;
UPDATE creature SET phaseIds="179" WHERE guid=246081 AND id=36615;
UPDATE creature SET phaseIds="179" WHERE guid=246263 AND id=36423;
UPDATE creature SET phaseIds="179" WHERE guid=246264 AND id=36423;
UPDATE creature SET phaseIds="179" WHERE guid=246744 AND id=38432;
UPDATE creature SET phaseIds="179" WHERE guid=246782 AND id=36417;
UPDATE creature SET phaseIds="179" WHERE guid=247294 AND id=36383;
UPDATE creature SET phaseIds="179" WHERE guid=247967 AND id=36466;
UPDATE creature SET phaseIds="179" WHERE guid=248444 AND id=36422;

UPDATE creature SET phaseIds="179" WHERE id=36421;
UPDATE creature SET phaseIds="170 171 172 179" WHERE  id=35904;
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=36383;
UPDATE creature SET phaseIds="170 171 172 179" WHERE guid=245986 AND id=36735;
UPDATE creature SET phaseIds="170 171 172" WHERE map=648 AND id=36591;
UPDATE creature SET phaseIds="170" WHERE  id=35897;
UPDATE creature SET phaseIds="171 172 179" WHERE id=35928;
UPDATE creature SET phaseIds="171 172 179" WHERE id=35929;
UPDATE creature SET phaseIds="170" WHERE guid=248543 AND id=35896;
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=35896;
UPDATE creature SET phaseIds="170 171 172 179 180 181 182 183" WHERE guid in (248581, 248582, 248583, 248584) AND id=36719;
UPDATE creature SET phaseIds="170" WHERE id=35995;

delete from creature WHERE guid=249508 AND id=36042;

UPDATE creature SET phaseIds="170 171 172 179" WHERE id=34699; 
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=36740; 
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=36732; 
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=34763; 

UPDATE gameobject SET phaseIds="170 171 172" WHERE id=195201; 
UPDATE gameobject SET phaseIds="170 171 172" WHERE id=195188;
UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168790 and id=202536;

delete from creature WHERE guid=247490 AND id=34748;

UPDATE creature_template SET InhabitType=2 WHERE entry=34763;

update creature set position_x=490.975, position_y=3139.124 where guid=245573;

UPDATE creature SET phaseIds="170 171 172 179" WHERE id=36721; 
UPDATE creature SET phaseIds="170 171 172 179" WHERE id=34748; 

UPDATE creature SET phaseIds="170 171 172" WHERE guid=249461 and id=39169;

UPDATE creature SET phaseIds="170 171 172" WHERE guid=246743;
UPDATE creature SET phaseIds="170 171 172" WHERE id in (36496, 35650, 35786);

UPDATE creature SET phaseIds="170 171 172" WHERE guid=245960 AND id=36427;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245961 AND id=36186;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245963 AND id=36404;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245966 AND id=36180;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245967 AND id=36615;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245969 AND id=36179;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245970 AND id=36179;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245971 AND id=35758;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245972 AND id=35778;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245973 AND id=35780;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245974 AND id=36184;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245976 AND id=36430;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245977 AND id=35805;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245978 AND id=35806;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245980 AND id=35807;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245982 AND id=38432;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=245983 AND id=38738;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=246034 AND id=36426;
UPDATE creature SET phaseIds="170 171 172" WHERE guid=249467 AND id=36406;

UPDATE creature SET phaseIds="170 171 172 " WHERE guid=246030 AND id=36426;
UPDATE creature SET phaseIds="170 171 172 " WHERE guid=246035 AND id=36403;
UPDATE creature SET phaseIds="170 171 172 " WHERE guid=246038 AND id=35810;
UPDATE creature SET phaseIds="170 171 172 " WHERE guid=246039 AND id=35769;
UPDATE creature SET phaseIds="179 " WHERE guid=246040 AND id=35812;
UPDATE creature SET phaseIds="170 171 172 " WHERE guid=246198 AND id=36344;
UPDATE creature SET phaseIds="170 171 172 " WHERE guid=249463 AND id=37895;





update arkcore_string set content_default=
"Map: %u (%s) 
Zone: %u (%s)
Area: %u (%s)
X: %.3f Y: %.3f Z: %.3f O: %.3f
grid[%u,%u]cell[%u,%u] InstanceID: %u
ZoneX: %.3f ZoneY: %.3f GroundZ: %.3f FloorZ: %.3f 
Have height data (Map: %u VMap: %u MMap: %u)"
where entry=101;
 
update arkcore_string set content_loc3= 
"Karte: %u (%s) 
Zone: %u (%s) 
Gebiet: %u (%s)
X: %.3f Y: %.3f Z: %.3f O: %.3f
grid[%u,%u]Zelle[%u,%u] InstanzID: %u
ZoneX: %.3f ZoneY: %.3f GroundZ: %.3f FloorZ: %.3f 
Have height data (Map: %u VMap: %u)"
where entry=101;

update arkcore_string set content_default=
"Liquid level: %.3f, ground: %.3f, type: %u, flags %u, status: %d."
where entry=175;

update arkcore_string set content_loc3=
"Wasserspiegel: %.3f, Boden: %.3f, Art: %d, Flags %u, Status: %d"
where entry=175;





UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249464;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249466;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249463;

UPDATE creature SET phaseIds="170 171 172", spawndist=0, MovementType=0 WHERE guid=249465;

UPDATE creature SET phaseIds="171", spawndist=0, MovementType=0 WHERE id=36344;

UPDATE creature SET phaseIds="170 171 179", spawndist=0, MovementType=0 WHERE id=35837;

UPDATE creature SET phaseIds="170", spawndist=0, MovementType=0 WHERE id=35812;

UPDATE gameobject SET phaseIds="170 171 172 179" WHERE id=195622;

UPDATE gameobject SET phaseIds="170 171 172" WHERE id=205351;

UPDATE gameobject SET phaseIds="172" WHERE id=205471;

UPDATE creature SET phaseIds="170 171 172" WHERE id=35810;

delete from creature where id=39329;

delete from creature where id=46485;

UPDATE creature SET phaseIds="170 171 172 179" WHERE guid=246177;

DELETE FROM phase_area WHERE areaId=4720 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 0, 14474, 14303, 75, 11, 1, "arrival in Lost Island");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=1;
INSERT INTO phase_definitions VALUES 
(4720, 1, 171, 0, 0, 1, "Comment for phase 171");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=2;
INSERT INTO phase_definitions VALUES 
(4720, 2, 172, 0, 0, 1, "Comment for phase 172");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=3;
INSERT INTO phase_definitions VALUES 
(4720, 3, 179, 0, 0, 1, "Comment for phase 179");

DELETE FROM phase_definitions WHERE zoneID=4720 AND entry=4;
INSERT INTO phase_definitions VALUES 
(4720, 4, 180, 661, 681, 1, "Comment for phase 180");





UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168787;

UPDATE quest_template SET Method=2 WHERE Id=14239;

UPDATE quest_template SET PrevQuestId=14239, NextQuestId=14014, ExclusiveGroup=0, RequiredGender=0 WHERE Id=14474;

UPDATE quest_template SET PrevQuestId=14239, NextQuestId=14014, ExclusiveGroup=0, RequiredGender=1 WHERE Id=14001;

delete from smart_scripts where entryorguid=36608;

delete from smart_scripts where entryorguid=3660800;

UPDATE creature_template SET AIName="", ScriptName="npc_doc_zapnozzle_36608" WHERE entry=36608;

UPDATE creature_template SET ScriptName="npc_geargrinder_gizmo_36600" WHERE entry=36600;

UPDATE creature_template_addon SET emote=0, auras="68327 91298" WHERE entry=36600;

"2016_10_14_01_world.sql" may be a binary file.  See it anyway? 

UPDATE gameobject_loot_template SET QuestRequired=1 WHERE entry=195201 AND item=46828;

UPDATE quest_template SET ExclusiveGroup=14001 WHERE Id=14001;

UPDATE quest_template SET ExclusiveGroup=14001 WHERE Id=14474;

UPDATE quest_template SET PrevQuestId=-14014, NextQuestId=0, ExclusiveGroup=0, Flags=0 WHERE Id=14019;

UPDATE quest_template SET PrevQuestId=-14014, NextQuestId=0, ExclusiveGroup=0 WHERE Id=14473;

DELETE FROM `creature_queststarter` WHERE `id`=35650;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES
(35650,14014),
(35650,14234),
(35650,14248);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Teraptorjunges", QuestGiverTargetName_loc3="Teraptorjunges" WHERE Id=14473;

UPDATE quest_template SET QuestGiverPortrait=30187, QuestGiverTextWindow="Bomb-Throwing Monkey", QuestGiverTargetName="Bomb-Throwing Monkey" WHERE Id=14019;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Bombenwerfender Affe", QuestGiverTargetName_loc3="Bombenwerfender Affe" WHERE Id=14019;

UPDATE creature_template SET ScriptName="npc_bomb_throwing_monkey_34699" WHERE entry=34699;

delete from spell_linked_spell where spell_trigger=66142;
insert into spell_linked_spell values 
(66142, 8858, 1, "Bomb-Throwing Monkey");

UPDATE quest_template SET RequiredSourceItemId1=49028, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=14019;


delete from linked_respawn where guid=254315;

delete from gossip_menu where entry=10551;
insert into gossip_menu values 
(10551, 14598);

UPDATE creature_template SET gossip_menu_id=10551 WHERE entry=35780;

delete from gossip_menu where entry=10553;
insert into gossip_menu values 
(10553, 14809);

UPDATE creature_template SET gossip_menu_id=10553 WHERE entry=35805;

delete from npc_text where ID=14598;
insert into npc_text (ID, text0_0, prob0, em0_1, BroadcastTextID0) values 
(14598, "I don't know about you, $N, but I for one do not intend to be marooned on this island forever!$B$BIf only I'd stayed at the academy and learned how to use teleport magic....", 1, 1, 34952);

UPDATE creature_template SET gossip_menu_id=10552 WHERE entry=35786;

UPDATE npc_text SET BroadcastTextID0=34953 WHERE ID=14599;

UPDATE npc_text SET BroadcastTextID0=36453 WHERE ID=14981;

DELETE FROM gossip_menu WHERE entry=10805 and text_id=14981;
INSERT INTO gossip_menu VALUES (10805, 14981);

UPDATE creature_template SET gossip_menu_id=10805 WHERE entry=36496;

UPDATE gossip_menu_option SET OptionBroadcastTextID=2822, option_id=8, npc_option_npcflag=65536 WHERE menu_id=10805 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=4308, option_id=8, npc_option_npcflag=65536 WHERE menu_id=10805 AND id=1;

UPDATE creature_template SET gossip_menu_id=10549, dynamicflags=0 WHERE entry=35758;

DELETE FROM gossip_menu WHERE entry=11074 and text_id=15401;
INSERT INTO gossip_menu VALUES (11074, 15401);

UPDATE npc_text SET BroadcastTextID0=38605 WHERE ID=15401;

UPDATE creature_template SET gossip_menu_id=10554 WHERE entry=35806;

UPDATE creature_template SET gossip_menu_id=10554, dynamicflags=0 WHERE entry=35806;

UPDATE npc_text SET BroadcastTextID0=34957 WHERE ID=14603;

DELETE FROM gossip_menu WHERE entry=10554 and text_id=14603;
INSERT INTO gossip_menu VALUES (10554, 14603);

UPDATE creature_template SET gossip_menu_id=10555, dynamicflags=0 WHERE entry=35807;

DELETE FROM gossip_menu WHERE entry=10555 and text_id=14605;
INSERT INTO gossip_menu VALUES (10555, 14605);

UPDATE npc_text SET BroadcastTextID0=34959 WHERE ID=14605;

UPDATE creature_template SET gossip_menu_id=10550, dynamicflags=0 WHERE entry=35778;

DELETE FROM gossip_menu WHERE entry=10550 and text_id=14802;
INSERT INTO gossip_menu VALUES (10550, 14802);

UPDATE npc_text SET BroadcastTextID0=35974 WHERE ID=14802;

UPDATE creature_template SET dynamicflags=0 WHERE entry=35786;

UPDATE gossip_menu_option SET OptionBroadcastTextID=7658, npc_option_npcflag=51 WHERE menu_id=10552 AND id=0;

UPDATE gossip_menu_option SET option_id=5 WHERE menu_id=10552 AND id=0;

UPDATE creature_template SET dynamicflags=0 WHERE entry=35805;

DELETE FROM gossip_menu WHERE entry=10554 and text_id=14604;
INSERT INTO gossip_menu VALUES (10554, 14604);

UPDATE npc_text SET BroadcastTextID0=34958 WHERE ID=14604;



UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=1;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=68;
UPDATE npc_text SET BroadcastTextID0=7590 WHERE ID=197;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=328;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=384;
UPDATE npc_text SET BroadcastTextID0=8217 WHERE ID=401;
UPDATE npc_text SET BroadcastTextID0=2463 WHERE ID=520;
UPDATE npc_text SET BroadcastTextID0=2525 WHERE ID=558;
UPDATE npc_text SET BroadcastTextID0=2530 WHERE ID=565;
UPDATE npc_text SET BroadcastTextID0=2843 WHERE ID=838;
UPDATE npc_text SET BroadcastTextID0=2927 WHERE ID=906;
UPDATE npc_text SET BroadcastTextID0=2930 WHERE ID=908;
UPDATE npc_text SET BroadcastTextID0=2955 WHERE ID=921;
UPDATE npc_text SET BroadcastTextID0=2957 WHERE ID=923;
UPDATE npc_text SET BroadcastTextID0=2977 WHERE ID=934;
UPDATE npc_text SET BroadcastTextID0=3009 WHERE ID=940;
UPDATE npc_text SET BroadcastTextID0=3144 WHERE ID=1039;
UPDATE npc_text SET BroadcastTextID0=3146 WHERE ID=1040;
UPDATE npc_text SET BroadcastTextID0=3275 WHERE ID=1124;
UPDATE npc_text SET BroadcastTextID0=3305 WHERE ID=1160;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=1228;
UPDATE npc_text SET BroadcastTextID0=3474 WHERE ID=1303;
UPDATE npc_text SET BroadcastTextID0=3483 WHERE ID=1334;
UPDATE npc_text SET BroadcastTextID0=3486 WHERE ID=1337;
UPDATE npc_text SET BroadcastTextID0=3521 WHERE ID=1351;
UPDATE npc_text SET BroadcastTextID0=3561 WHERE ID=1371;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=1569;
UPDATE npc_text SET BroadcastTextID0=4248 WHERE ID=1814;
UPDATE npc_text SET BroadcastTextID0=4250 WHERE ID=1815;
UPDATE npc_text SET BroadcastTextID0=4255 WHERE ID=1817;
UPDATE npc_text SET BroadcastTextID0=4260 WHERE ID=1819;
UPDATE npc_text SET BroadcastTextID0=4309 WHERE ID=1853;
UPDATE npc_text SET BroadcastTextID0=4479 WHERE ID=1999;
UPDATE npc_text SET BroadcastTextID0=4550 WHERE ID=2133;
UPDATE npc_text SET BroadcastTextID0=4552 WHERE ID=2134;
UPDATE npc_text SET BroadcastTextID0=4604 WHERE ID=2236;
UPDATE npc_text SET BroadcastTextID0=4637 WHERE ID=2286;
UPDATE npc_text SET BroadcastTextID0=4645 WHERE ID=2314;
UPDATE npc_text SET BroadcastTextID0=4653 WHERE ID=2318;
UPDATE npc_text SET BroadcastTextID0=4735 WHERE ID=2475;
UPDATE npc_text SET BroadcastTextID0=4749 WHERE ID=2482;
UPDATE npc_text SET BroadcastTextID0=4901 WHERE ID=2606;
UPDATE npc_text SET BroadcastTextID0=4943 WHERE ID=2635;
UPDATE npc_text SET BroadcastTextID0=4957 WHERE ID=2638;
UPDATE npc_text SET BroadcastTextID0=5018 WHERE ID=2718;
UPDATE npc_text SET BroadcastTextID0=5083 WHERE ID=2762;
UPDATE npc_text SET BroadcastTextID0=5098 WHERE ID=2771;
UPDATE npc_text SET BroadcastTextID0=5101 WHERE ID=2772;
UPDATE npc_text SET BroadcastTextID0=5124 WHERE ID=2798;
UPDATE npc_text SET BroadcastTextID0=5139 WHERE ID=2804;
UPDATE npc_text SET BroadcastTextID0=5179 WHERE ID=2816;
UPDATE npc_text SET BroadcastTextID0=10620 WHERE ID=2818;
UPDATE npc_text SET BroadcastTextID0=5192 WHERE ID=2834;
UPDATE npc_text SET BroadcastTextID0=5189 WHERE ID=2835;
UPDATE npc_text SET BroadcastTextID0=5195 WHERE ID=2838;
UPDATE npc_text SET BroadcastTextID0=5206 WHERE ID=2843;
UPDATE npc_text SET BroadcastTextID0=5574 WHERE ID=3304;
UPDATE npc_text SET BroadcastTextID0=5582 WHERE ID=3308;
UPDATE npc_text SET BroadcastTextID0=5606 WHERE ID=3321;
UPDATE npc_text SET BroadcastTextID0=5608 WHERE ID=3334;
UPDATE npc_text SET BroadcastTextID0=5800 WHERE ID=3470;
UPDATE npc_text SET BroadcastTextID0=5854 WHERE ID=3522;
UPDATE npc_text SET BroadcastTextID0=5871 WHERE ID=3532;
UPDATE npc_text SET BroadcastTextID0=5970 WHERE ID=3560;
UPDATE npc_text SET BroadcastTextID0=5972 WHERE ID=3561;
UPDATE npc_text SET BroadcastTextID0=5980 WHERE ID=3565;
UPDATE npc_text SET BroadcastTextID0=5991 WHERE ID=3574;
UPDATE npc_text SET BroadcastTextID0=6018 WHERE ID=3584;
UPDATE npc_text SET BroadcastTextID0=6088 WHERE ID=3664;
UPDATE npc_text SET BroadcastTextID0=6114 WHERE ID=3669;
UPDATE npc_text SET BroadcastTextID0=6132 WHERE ID=3675;
UPDATE npc_text SET BroadcastTextID0=6229 WHERE ID=3753;
UPDATE npc_text SET BroadcastTextID0=6250 WHERE ID=3763;
UPDATE npc_text SET BroadcastTextID0=6267 WHERE ID=3794;
UPDATE npc_text SET BroadcastTextID0=6296 WHERE ID=3807;
UPDATE npc_text SET BroadcastTextID0=6345 WHERE ID=3815;
UPDATE npc_text SET BroadcastTextID0=6729 WHERE ID=4074;
UPDATE npc_text SET BroadcastTextID0=6870 WHERE ID=4135;
UPDATE npc_text SET BroadcastTextID0=6879 WHERE ID=4193;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=4258;
UPDATE npc_text SET BroadcastTextID0=7376 WHERE ID=4697;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=4732;
UPDATE npc_text SET BroadcastTextID0=7457 WHERE ID=4780;
UPDATE npc_text SET BroadcastTextID0=7458 WHERE ID=4781;
UPDATE npc_text SET BroadcastTextID0=7555 WHERE ID=4889;
UPDATE npc_text SET BroadcastTextID0=7559 WHERE ID=4891;
UPDATE npc_text SET BroadcastTextID0=7584 WHERE ID=4933;
UPDATE npc_text SET BroadcastTextID0=7644 WHERE ID=4996;
UPDATE npc_text SET BroadcastTextID0=7672 WHERE ID=5011;
UPDATE npc_text SET BroadcastTextID0=7674 WHERE ID=5012;
UPDATE npc_text SET BroadcastTextID0=7752 WHERE ID=5088;
UPDATE npc_text SET BroadcastTextID0=7827 WHERE ID=5143;
UPDATE npc_text SET BroadcastTextID0=7829 WHERE ID=5145;
UPDATE npc_text SET BroadcastTextID0=7832 WHERE ID=5148;
UPDATE npc_text SET BroadcastTextID0=7833 WHERE ID=5149;
UPDATE npc_text SET BroadcastTextID0=7834 WHERE ID=5150;
UPDATE npc_text SET BroadcastTextID0=7852 WHERE ID=5168;
UPDATE npc_text SET BroadcastTextID0=7860 WHERE ID=5176;
UPDATE npc_text SET BroadcastTextID0=7878 WHERE ID=5191;
UPDATE npc_text SET BroadcastTextID0=7893 WHERE ID=5206;
UPDATE npc_text SET BroadcastTextID0=7904 WHERE ID=5215;
UPDATE npc_text SET BroadcastTextID0=7914 WHERE ID=5225;
UPDATE npc_text SET BroadcastTextID0=7916 WHERE ID=5227;
UPDATE npc_text SET BroadcastTextID0=7931 WHERE ID=5242;
UPDATE npc_text SET BroadcastTextID0=7933 WHERE ID=5244;
UPDATE npc_text SET BroadcastTextID0=7938 WHERE ID=5249;
UPDATE npc_text SET BroadcastTextID0=7944 WHERE ID=5255;
UPDATE npc_text SET BroadcastTextID0=8037 WHERE ID=5373;
UPDATE npc_text SET BroadcastTextID0=8039 WHERE ID=5375;
UPDATE npc_text SET BroadcastTextID0=8178 WHERE ID=5557;
UPDATE npc_text SET BroadcastTextID0=8296 WHERE ID=5719;
UPDATE npc_text SET BroadcastTextID0=8343 WHERE ID=5797;
UPDATE npc_text SET BroadcastTextID0=8765 WHERE ID=6179;
UPDATE npc_text SET BroadcastTextID0=8918 WHERE ID=6334;
UPDATE npc_text SET BroadcastTextID0=11865 WHERE ID=6595;
UPDATE npc_text SET BroadcastTextID0=9399 WHERE ID=6906;
UPDATE npc_text SET BroadcastTextID0=9470 WHERE ID=6923;
UPDATE npc_text SET BroadcastTextID0=9656 WHERE ID=7010;
UPDATE npc_text SET BroadcastTextID0=9659 WHERE ID=7011;
UPDATE npc_text SET BroadcastTextID0=9721 WHERE ID=7032;
UPDATE npc_text SET BroadcastTextID0=9725 WHERE ID=7034;
UPDATE npc_text SET BroadcastTextID0=9846 WHERE ID=7134;
UPDATE npc_text SET BroadcastTextID0=9871 WHERE ID=7177;
UPDATE npc_text SET BroadcastTextID0=9881 WHERE ID=7183;
UPDATE npc_text SET BroadcastTextID0=9884 WHERE ID=7185;
UPDATE npc_text SET BroadcastTextID0=9892 WHERE ID=7187;
UPDATE npc_text SET BroadcastTextID0=9903 WHERE ID=7198;
UPDATE npc_text SET BroadcastTextID0=9905 WHERE ID=7199;
UPDATE npc_text SET BroadcastTextID0=9911 WHERE ID=7201;
UPDATE npc_text SET BroadcastTextID0=9914 WHERE ID=7203;
UPDATE npc_text SET BroadcastTextID0=9917 WHERE ID=7205;
UPDATE npc_text SET BroadcastTextID0=9920 WHERE ID=7207;
UPDATE npc_text SET BroadcastTextID0=9923 WHERE ID=7209;
UPDATE npc_text SET BroadcastTextID0=9927 WHERE ID=7212;
UPDATE npc_text SET BroadcastTextID0=9930 WHERE ID=7214;
UPDATE npc_text SET BroadcastTextID0=9939 WHERE ID=7219;
UPDATE npc_text SET BroadcastTextID0=9941 WHERE ID=7220;
UPDATE npc_text SET BroadcastTextID0=9950 WHERE ID=7226;
UPDATE npc_text SET BroadcastTextID0=9955 WHERE ID=7230;
UPDATE npc_text SET BroadcastTextID0=9981 WHERE ID=7242;
UPDATE npc_text SET BroadcastTextID0=9993 WHERE ID=7249;
UPDATE npc_text SET BroadcastTextID0=9998 WHERE ID=7252;
UPDATE npc_text SET BroadcastTextID0=10163 WHERE ID=7396;
UPDATE npc_text SET BroadcastTextID0=10166 WHERE ID=7399;
UPDATE npc_text SET BroadcastTextID0=10385 WHERE ID=7496;
UPDATE npc_text SET BroadcastTextID0=25280 WHERE ID=7530;
UPDATE npc_text SET BroadcastTextID0=10559 WHERE ID=7685;
UPDATE npc_text SET BroadcastTextID0=10562 WHERE ID=7687;
UPDATE npc_text SET BroadcastTextID0=10563 WHERE ID=7688;
UPDATE npc_text SET BroadcastTextID0=10565 WHERE ID=7690;
UPDATE npc_text SET BroadcastTextID0=10566 WHERE ID=7691;
UPDATE npc_text SET BroadcastTextID0=10571 WHERE ID=7696;
UPDATE npc_text SET BroadcastTextID0=10572 WHERE ID=7697;
UPDATE npc_text SET BroadcastTextID0=10576 WHERE ID=7701;
UPDATE npc_text SET BroadcastTextID0=10577 WHERE ID=7702;
UPDATE npc_text SET BroadcastTextID0=10578 WHERE ID=7703;
UPDATE npc_text SET BroadcastTextID0=10582 WHERE ID=7706;
UPDATE npc_text SET BroadcastTextID0=10584 WHERE ID=7707;
UPDATE npc_text SET BroadcastTextID0=10583 WHERE ID=7708;
UPDATE npc_text SET BroadcastTextID0=10585 WHERE ID=7709;
UPDATE npc_text SET BroadcastTextID0=10595 WHERE ID=7712;
UPDATE npc_text SET BroadcastTextID0=10600 WHERE ID=7714;
UPDATE npc_text SET BroadcastTextID0=10661 WHERE ID=7738;
UPDATE npc_text SET BroadcastTextID0=10671 WHERE ID=7740;
UPDATE npc_text SET BroadcastTextID0=10781 WHERE ID=7797;
UPDATE npc_text SET BroadcastTextID0=10811 WHERE ID=7808;
UPDATE npc_text SET BroadcastTextID0=10817 WHERE ID=7812;
UPDATE npc_text SET BroadcastTextID0=11068 WHERE ID=7903;
UPDATE npc_text SET BroadcastTextID0=14774 WHERE ID=7904;
UPDATE npc_text SET BroadcastTextID0=11338 WHERE ID=8071;
UPDATE npc_text SET BroadcastTextID0=11395 WHERE ID=8115;
UPDATE npc_text SET BroadcastTextID0=11396 WHERE ID=8116;
UPDATE npc_text SET BroadcastTextID0=11415 WHERE ID=8126;
UPDATE npc_text SET BroadcastTextID0=11420 WHERE ID=8127;
UPDATE npc_text SET BroadcastTextID0=11416 WHERE ID=8128;
UPDATE npc_text SET BroadcastTextID0=11418 WHERE ID=8130;
UPDATE npc_text SET BroadcastTextID0=11419 WHERE ID=8131;
UPDATE npc_text SET BroadcastTextID0=11421 WHERE ID=8132;
UPDATE npc_text SET BroadcastTextID0=11422 WHERE ID=8133;
UPDATE npc_text SET BroadcastTextID0=11551 WHERE ID=8174;
UPDATE npc_text SET BroadcastTextID0=11562 WHERE ID=8179;
UPDATE npc_text SET BroadcastTextID0=11579 WHERE ID=8186;
UPDATE npc_text SET BroadcastTextID0=11581 WHERE ID=8187;
UPDATE npc_text SET BroadcastTextID0=11587 WHERE ID=8190;
UPDATE npc_text SET BroadcastTextID0=11610 WHERE ID=8202;
UPDATE npc_text SET BroadcastTextID0=11811 WHERE ID=8303;
UPDATE npc_text SET BroadcastTextID0=11833 WHERE ID=8312;
UPDATE npc_text SET BroadcastTextID0=11904 WHERE ID=8333;
UPDATE npc_text SET BroadcastTextID0=11941 WHERE ID=8351;
UPDATE npc_text SET BroadcastTextID0=11942 WHERE ID=8352;
UPDATE npc_text SET BroadcastTextID0=11943 WHERE ID=8353;
UPDATE npc_text SET BroadcastTextID0=11961 WHERE ID=8363;
UPDATE npc_text SET BroadcastTextID0=12109 WHERE ID=8434;
UPDATE npc_text SET BroadcastTextID0=12180 WHERE ID=8471;
UPDATE npc_text SET BroadcastTextID0=12227 WHERE ID=8498;
UPDATE npc_text SET BroadcastTextID0=12229 WHERE ID=8499;
UPDATE npc_text SET BroadcastTextID0=12232 WHERE ID=8500;
UPDATE npc_text SET BroadcastTextID0=12235 WHERE ID=8502;
UPDATE npc_text SET BroadcastTextID0=12236 WHERE ID=8503;
UPDATE npc_text SET BroadcastTextID0=12247 WHERE ID=8507;
UPDATE npc_text SET BroadcastTextID0=12284 WHERE ID=8518;
UPDATE npc_text SET BroadcastTextID0=12292 WHERE ID=8522;
UPDATE npc_text SET BroadcastTextID0=12403 WHERE ID=8555;
UPDATE npc_text SET BroadcastTextID0=12435 WHERE ID=8573;
UPDATE npc_text SET BroadcastTextID0=12775 WHERE ID=8669;
UPDATE npc_text SET BroadcastTextID0=13143 WHERE ID=8713;
UPDATE npc_text SET BroadcastTextID0=50721 WHERE ID=8753;
UPDATE npc_text SET BroadcastTextID0=13547 WHERE ID=8823;
UPDATE npc_text SET BroadcastTextID0=13654 WHERE ID=8855;
UPDATE npc_text SET BroadcastTextID0=13738 WHERE ID=8870;
UPDATE npc_text SET BroadcastTextID0=13757 WHERE ID=8874;
UPDATE npc_text SET BroadcastTextID0=13766 WHERE ID=8876;
UPDATE npc_text SET BroadcastTextID0=13771 WHERE ID=8880;
UPDATE npc_text SET BroadcastTextID0=25280 WHERE ID=8934;
UPDATE npc_text SET BroadcastTextID0=14377 WHERE ID=9060;
UPDATE npc_text SET BroadcastTextID0=14432 WHERE ID=9082;
UPDATE npc_text SET BroadcastTextID0=14591 WHERE ID=9121;
UPDATE npc_text SET BroadcastTextID0=14983 WHERE ID=9271;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=9296;
UPDATE npc_text SET BroadcastTextID0=15260 WHERE ID=9342;
UPDATE npc_text SET BroadcastTextID0=15268 WHERE ID=9346;
UPDATE npc_text SET BroadcastTextID0=15775 WHERE ID=9510;
UPDATE npc_text SET BroadcastTextID0=15816 WHERE ID=9530;
UPDATE npc_text SET BroadcastTextID0=16460 WHERE ID=9780;
UPDATE npc_text SET BroadcastTextID0=16654 WHERE ID=9805;
UPDATE npc_text SET BroadcastTextID0=17412 WHERE ID=9921;
UPDATE npc_text SET BroadcastTextID0=17483 WHERE ID=9938;
UPDATE npc_text SET BroadcastTextID0=16444 WHERE ID=9962;
UPDATE npc_text SET BroadcastTextID0=17748 WHERE ID=9984;
UPDATE npc_text SET BroadcastTextID0=17750 WHERE ID=9986;
UPDATE npc_text SET BroadcastTextID0=17477 WHERE ID=9991;
UPDATE npc_text SET BroadcastTextID0=17948 WHERE ID=10020;
UPDATE npc_text SET BroadcastTextID0=18178 WHERE ID=10058;
UPDATE npc_text SET BroadcastTextID0=18246 WHERE ID=10065;
UPDATE npc_text SET BroadcastTextID0=18426 WHERE ID=10123;
UPDATE npc_text SET BroadcastTextID0=18827 WHERE ID=10278;
UPDATE npc_text SET BroadcastTextID0=18844 WHERE ID=10284;
UPDATE npc_text SET BroadcastTextID0=18849 WHERE ID=10287;
UPDATE npc_text SET BroadcastTextID0=18925 WHERE ID=10305;
UPDATE npc_text SET BroadcastTextID0=18927 WHERE ID=10307;
UPDATE npc_text SET BroadcastTextID0=19132 WHERE ID=10363;
UPDATE npc_text SET BroadcastTextID0=19134 WHERE ID=10365;
UPDATE npc_text SET BroadcastTextID0=19271 WHERE ID=10409;
UPDATE npc_text SET BroadcastTextID0=19427 WHERE ID=10452;
UPDATE npc_text SET BroadcastTextID0=19498 WHERE ID=10474;
UPDATE npc_text SET BroadcastTextID0=19243 WHERE ID=10528;
UPDATE npc_text SET BroadcastTextID0=19656 WHERE ID=10529;
UPDATE npc_text SET BroadcastTextID0=4959 WHERE ID=10547;
UPDATE npc_text SET BroadcastTextID0=7377 WHERE ID=10550;
UPDATE npc_text SET BroadcastTextID0=7376 WHERE ID=10551;
UPDATE npc_text SET BroadcastTextID0=4963 WHERE ID=10552;
UPDATE npc_text SET BroadcastTextID0=8106 WHERE ID=10555;
UPDATE npc_text SET BroadcastTextID0=8131 WHERE ID=10557;
UPDATE npc_text SET BroadcastTextID0=19802 WHERE ID=10601;
UPDATE npc_text SET BroadcastTextID0=19850 WHERE ID=10608;
UPDATE npc_text SET BroadcastTextID0=15246 WHERE ID=10724;
UPDATE npc_text SET BroadcastTextID0=16028 WHERE ID=10725;
UPDATE npc_text SET BroadcastTextID0=15964 WHERE ID=10726;
UPDATE npc_text SET BroadcastTextID0=20530 WHERE ID=10743;
UPDATE npc_text SET BroadcastTextID0=21801 WHERE ID=11057;
UPDATE npc_text SET BroadcastTextID0=21871 WHERE ID=11075;
UPDATE npc_text SET BroadcastTextID0=21872 WHERE ID=11076;
UPDATE npc_text SET BroadcastTextID0=22184 WHERE ID=11234;
UPDATE npc_text SET BroadcastTextID0=11295 WHERE ID=11295;
UPDATE npc_text SET BroadcastTextID0=22321 WHERE ID=11313;
UPDATE npc_text SET BroadcastTextID0=22323 WHERE ID=11314;
UPDATE npc_text SET BroadcastTextID0=22611 WHERE ID=11582;
UPDATE npc_text SET BroadcastTextID0=23377 WHERE ID=12076;
UPDATE npc_text SET BroadcastTextID0=23769 WHERE ID=12163;
UPDATE npc_text SET BroadcastTextID0=23782 WHERE ID=12165;
UPDATE npc_text SET BroadcastTextID0=23969 WHERE ID=12221;
UPDATE npc_text SET BroadcastTextID0=24297 WHERE ID=12335;
UPDATE npc_text SET BroadcastTextID0=24305 WHERE ID=12341;
UPDATE npc_text SET BroadcastTextID0=24306 WHERE ID=12342;
UPDATE npc_text SET BroadcastTextID0=25771 WHERE ID=12649;
UPDATE npc_text SET BroadcastTextID0=26260 WHERE ID=12751;
UPDATE npc_text SET BroadcastTextID0=26518 WHERE ID=12823;
UPDATE npc_text SET BroadcastTextID0=27093 WHERE ID=12950;
UPDATE npc_text SET BroadcastTextID0=27102 WHERE ID=12952;
UPDATE npc_text SET BroadcastTextID0=27139 WHERE ID=12971;
UPDATE npc_text SET BroadcastTextID0=27141 WHERE ID=12973;
UPDATE npc_text SET BroadcastTextID0=27165 WHERE ID=12977;
UPDATE npc_text SET BroadcastTextID0=27265 WHERE ID=12992;
UPDATE npc_text SET BroadcastTextID0=27267 WHERE ID=12993;
UPDATE npc_text SET BroadcastTextID0=27269 WHERE ID=12994;
UPDATE npc_text SET BroadcastTextID0=27471 WHERE ID=13059;
UPDATE npc_text SET BroadcastTextID0=27467 WHERE ID=13062;
UPDATE npc_text SET BroadcastTextID0=28080 WHERE ID=13237;
UPDATE npc_text SET BroadcastTextID0=28429 WHERE ID=13269;
UPDATE npc_text SET BroadcastTextID0=28644 WHERE ID=13324;
UPDATE npc_text SET BroadcastTextID0=29541 WHERE ID=13469;
UPDATE npc_text SET BroadcastTextID0=29581 WHERE ID=13472;
UPDATE npc_text SET BroadcastTextID0=29626 WHERE ID=13474;
UPDATE npc_text SET BroadcastTextID0=30433 WHERE ID=13615;
UPDATE npc_text SET BroadcastTextID0=30824 WHERE ID=13695;
UPDATE npc_text SET BroadcastTextID0=31208 WHERE ID=13797;
UPDATE npc_text SET BroadcastTextID0=31273 WHERE ID=13811;
UPDATE npc_text SET BroadcastTextID0=31559 WHERE ID=13889;
UPDATE npc_text SET BroadcastTextID0=31982 WHERE ID=13938;
UPDATE npc_text SET BroadcastTextID0=32096 WHERE ID=13972;
UPDATE npc_text SET BroadcastTextID0=32113 WHERE ID=13977;
UPDATE npc_text SET BroadcastTextID0=32365 WHERE ID=14053;
UPDATE npc_text SET BroadcastTextID0=33040 WHERE ID=14194;
UPDATE npc_text SET BroadcastTextID0=33177 WHERE ID=14261;
UPDATE npc_text SET BroadcastTextID0=33158 WHERE ID=14292;
UPDATE npc_text SET BroadcastTextID0=33162 WHERE ID=14296;
UPDATE npc_text SET BroadcastTextID0=33343 WHERE ID=14311;
UPDATE npc_text SET BroadcastTextID0=33350 WHERE ID=14316;
UPDATE npc_text SET BroadcastTextID0=43340 WHERE ID=14327;
UPDATE npc_text SET BroadcastTextID0=33409 WHERE ID=14332;
UPDATE npc_text SET BroadcastTextID0=33413 WHERE ID=14333;
UPDATE npc_text SET BroadcastTextID0=33450 WHERE ID=14339;
UPDATE npc_text SET BroadcastTextID0=69232 WHERE ID=14344;
UPDATE npc_text SET BroadcastTextID0=43340 WHERE ID=14347;
UPDATE npc_text SET BroadcastTextID0=33572 WHERE ID=14351;
UPDATE npc_text SET BroadcastTextID0=33591 WHERE ID=14358;
UPDATE npc_text SET BroadcastTextID0=33651 WHERE ID=14369;
UPDATE npc_text SET BroadcastTextID0=33918 WHERE ID=14424;
UPDATE npc_text SET BroadcastTextID0=34467 WHERE ID=14507;
UPDATE npc_text SET BroadcastTextID0=34472 WHERE ID=14510;
UPDATE npc_text SET BroadcastTextID0=34473 WHERE ID=14511;
UPDATE npc_text SET BroadcastTextID0=34487 WHERE ID=14518;
UPDATE npc_text SET BroadcastTextID0=34515 WHERE ID=14526;
UPDATE npc_text SET BroadcastTextID0=34546 WHERE ID=14531;
UPDATE npc_text SET BroadcastTextID0=34628 WHERE ID=14546;
UPDATE npc_text SET BroadcastTextID0=34637 WHERE ID=14547;
UPDATE npc_text SET BroadcastTextID0=34758 WHERE ID=14561;
UPDATE npc_text SET BroadcastTextID0=34790 WHERE ID=14565;
UPDATE npc_text SET BroadcastTextID0=34838 WHERE ID=14568;
UPDATE npc_text SET BroadcastTextID0=34843 WHERE ID=14572;
UPDATE npc_text SET BroadcastTextID0=34853 WHERE ID=14575;
UPDATE npc_text SET BroadcastTextID0=34869 WHERE ID=14579;
UPDATE npc_text SET BroadcastTextID0=34892 WHERE ID=14584;
UPDATE npc_text SET BroadcastTextID0=34949 WHERE ID=14595;
UPDATE npc_text SET BroadcastTextID0=34950 WHERE ID=14596;
UPDATE npc_text SET BroadcastTextID0=34951 WHERE ID=14597;
UPDATE npc_text SET BroadcastTextID0=35140 WHERE ID=14657;
UPDATE npc_text SET BroadcastTextID0=35221 WHERE ID=14672;
UPDATE npc_text SET BroadcastTextID0=35333 WHERE ID=14690;
UPDATE npc_text SET BroadcastTextID0=35501 WHERE ID=14735;
UPDATE npc_text SET BroadcastTextID0=35536 WHERE ID=14737;
UPDATE npc_text SET BroadcastTextID0=35565 WHERE ID=14740;
UPDATE npc_text SET BroadcastTextID0=35678 WHERE ID=14742;
UPDATE npc_text SET BroadcastTextID0=35774 WHERE ID=14744;
UPDATE npc_text SET BroadcastTextID0=35776 WHERE ID=14745;
UPDATE npc_text SET BroadcastTextID0=35778 WHERE ID=14746;
UPDATE npc_text SET BroadcastTextID0=35780 WHERE ID=14747;
UPDATE npc_text SET BroadcastTextID0=35782 WHERE ID=14748;
UPDATE npc_text SET BroadcastTextID0=35784 WHERE ID=14749;
UPDATE npc_text SET BroadcastTextID0=35953 WHERE ID=14789;
UPDATE npc_text SET BroadcastTextID0=35958 WHERE ID=14792;
UPDATE npc_text SET BroadcastTextID0=35962 WHERE ID=14795;
UPDATE npc_text SET BroadcastTextID0=35963 WHERE ID=14796;
UPDATE npc_text SET BroadcastTextID0=35966 WHERE ID=14799;
UPDATE npc_text SET BroadcastTextID0=35976 WHERE ID=14805;
UPDATE npc_text SET BroadcastTextID0=35978 WHERE ID=14806;
UPDATE npc_text SET BroadcastTextID0=36042 WHERE ID=14826;
UPDATE npc_text SET BroadcastTextID0=36057 WHERE ID=14834;
UPDATE npc_text SET BroadcastTextID0=36152 WHERE ID=14870;
UPDATE npc_text SET BroadcastTextID0=36188 WHERE ID=14879;
UPDATE npc_text SET BroadcastTextID0=36192 WHERE ID=14880;
UPDATE npc_text SET BroadcastTextID0=36205 WHERE ID=14886;
UPDATE npc_text SET BroadcastTextID0=36298 WHERE ID=14932;
UPDATE npc_text SET BroadcastTextID0=36332 WHERE ID=14942;
UPDATE npc_text SET BroadcastTextID0=49174 WHERE ID=14955;
UPDATE npc_text SET BroadcastTextID0=36371 WHERE ID=14956;
UPDATE npc_text SET BroadcastTextID0=36374 WHERE ID=14959;
UPDATE npc_text SET BroadcastTextID0=36386 WHERE ID=14961;
UPDATE npc_text SET BroadcastTextID0=36387 WHERE ID=14962;
UPDATE npc_text SET BroadcastTextID0=36400 WHERE ID=14966;
UPDATE npc_text SET BroadcastTextID0=36469 WHERE ID=14988;
UPDATE npc_text SET BroadcastTextID0=36472 WHERE ID=14991;
UPDATE npc_text SET BroadcastTextID0=36475 WHERE ID=14994;
UPDATE npc_text SET BroadcastTextID0=36476 WHERE ID=14995;
UPDATE npc_text SET BroadcastTextID0=36477 WHERE ID=14996;
UPDATE npc_text SET BroadcastTextID0=36479 WHERE ID=14998;
UPDATE npc_text SET BroadcastTextID0=36482 WHERE ID=15001;
UPDATE npc_text SET BroadcastTextID0=36486 WHERE ID=15002;
UPDATE npc_text SET BroadcastTextID0=36551 WHERE ID=15012;
UPDATE npc_text SET BroadcastTextID0=36578 WHERE ID=15021;
UPDATE npc_text SET BroadcastTextID0=36967 WHERE ID=15117;
UPDATE npc_text SET BroadcastTextID0=37011 WHERE ID=15131;
UPDATE npc_text SET BroadcastTextID0=37012 WHERE ID=15132;
UPDATE npc_text SET BroadcastTextID0=37025 WHERE ID=15134;
UPDATE npc_text SET BroadcastTextID0=37048 WHERE ID=15136;
UPDATE npc_text SET BroadcastTextID0=37057 WHERE ID=15137;
UPDATE npc_text SET BroadcastTextID0=37059 WHERE ID=15138;
UPDATE npc_text SET BroadcastTextID0=37060 WHERE ID=15139;
UPDATE npc_text SET BroadcastTextID0=37081 WHERE ID=15145;
UPDATE npc_text SET BroadcastTextID0=37116 WHERE ID=15152;
UPDATE npc_text SET BroadcastTextID0=37295 WHERE ID=15182;
UPDATE npc_text SET BroadcastTextID0=37462 WHERE ID=15196;
UPDATE npc_text SET BroadcastTextID0=37463 WHERE ID=15197;
UPDATE npc_text SET BroadcastTextID0=37464 WHERE ID=15198;
UPDATE npc_text SET BroadcastTextID0=37553 WHERE ID=15208;
UPDATE npc_text SET BroadcastTextID0=37652 WHERE ID=15220;
UPDATE npc_text SET BroadcastTextID0=37676 WHERE ID=15223;
UPDATE npc_text SET BroadcastTextID0=37719 WHERE ID=15227;
UPDATE npc_text SET BroadcastTextID0=37779 WHERE ID=15233;
UPDATE npc_text SET BroadcastTextID0=37798 WHERE ID=15236;
UPDATE npc_text SET BroadcastTextID0=37870 WHERE ID=15246;
UPDATE npc_text SET BroadcastTextID0=37961 WHERE ID=15267;
UPDATE npc_text SET BroadcastTextID0=37964 WHERE ID=15268;
UPDATE npc_text SET BroadcastTextID0=37967 WHERE ID=15270;
UPDATE npc_text SET BroadcastTextID0=38182 WHERE ID=15291;
UPDATE npc_text SET BroadcastTextID0=38248 WHERE ID=15302;
UPDATE npc_text SET BroadcastTextID0=38250 WHERE ID=15303;
UPDATE npc_text SET BroadcastTextID0=38307 WHERE ID=15313;
UPDATE npc_text SET BroadcastTextID0=38309 WHERE ID=15315;
UPDATE npc_text SET BroadcastTextID0=38312 WHERE ID=15317;
UPDATE npc_text SET BroadcastTextID0=38327 WHERE ID=15326;
UPDATE npc_text SET BroadcastTextID0=38390 WHERE ID=15343;
UPDATE npc_text SET BroadcastTextID0=38394 WHERE ID=15345;
UPDATE npc_text SET BroadcastTextID0=56602 WHERE ID=15347;
UPDATE npc_text SET BroadcastTextID0=38438 WHERE ID=15353;
UPDATE npc_text SET BroadcastTextID0=38443 WHERE ID=15354;
UPDATE npc_text SET BroadcastTextID0=38446 WHERE ID=15357;
UPDATE npc_text SET BroadcastTextID0=38449 WHERE ID=15360;
UPDATE npc_text SET BroadcastTextID0=38454 WHERE ID=15365;
UPDATE npc_text SET BroadcastTextID0=38463 WHERE ID=15369;
UPDATE npc_text SET BroadcastTextID0=38467 WHERE ID=15370;
UPDATE npc_text SET BroadcastTextID0=38481 WHERE ID=15375;
UPDATE npc_text SET BroadcastTextID0=38509 WHERE ID=15381;
UPDATE npc_text SET BroadcastTextID0=38531 WHERE ID=15387;
UPDATE npc_text SET BroadcastTextID0=38618 WHERE ID=15406;
UPDATE npc_text SET BroadcastTextID0=38650 WHERE ID=15411;
UPDATE npc_text SET BroadcastTextID0=38673 WHERE ID=15418;
UPDATE npc_text SET BroadcastTextID0=38723 WHERE ID=15428;
UPDATE npc_text SET BroadcastTextID0=38810 WHERE ID=15447;
UPDATE npc_text SET BroadcastTextID0=38814 WHERE ID=15452;
UPDATE npc_text SET BroadcastTextID0=38842 WHERE ID=15460;
UPDATE npc_text SET BroadcastTextID0=38843 WHERE ID=15461;
UPDATE npc_text SET BroadcastTextID0=38891 WHERE ID=15466;
UPDATE npc_text SET BroadcastTextID0=38963 WHERE ID=15483;
UPDATE npc_text SET BroadcastTextID0=39041 WHERE ID=15495;
UPDATE npc_text SET BroadcastTextID0=39040 WHERE ID=15496;
UPDATE npc_text SET BroadcastTextID0=39117 WHERE ID=15515;
UPDATE npc_text SET BroadcastTextID0=39120 WHERE ID=15517;
UPDATE npc_text SET BroadcastTextID0=39129 WHERE ID=15524;
UPDATE npc_text SET BroadcastTextID0=39191 WHERE ID=15538;
UPDATE npc_text SET BroadcastTextID0=39203 WHERE ID=15542;
UPDATE npc_text SET BroadcastTextID0=39206 WHERE ID=15544;
UPDATE npc_text SET BroadcastTextID0=39207 WHERE ID=15545;
UPDATE npc_text SET BroadcastTextID0=39209 WHERE ID=15547;
UPDATE npc_text SET BroadcastTextID0=39214 WHERE ID=15549;
UPDATE npc_text SET BroadcastTextID0=39217 WHERE ID=15551;
UPDATE npc_text SET BroadcastTextID0=39218 WHERE ID=15552;
UPDATE npc_text SET BroadcastTextID0=39307 WHERE ID=15575;
UPDATE npc_text SET BroadcastTextID0=39343 WHERE ID=15586;
UPDATE npc_text SET BroadcastTextID0=39346 WHERE ID=15589;
UPDATE npc_text SET BroadcastTextID0=39402 WHERE ID=15603;
UPDATE npc_text SET BroadcastTextID0=39418 WHERE ID=15608;
UPDATE npc_text SET BroadcastTextID0=39419 WHERE ID=15609;
UPDATE npc_text SET BroadcastTextID0=39482 WHERE ID=15623;
UPDATE npc_text SET BroadcastTextID0=39486 WHERE ID=15627;
UPDATE npc_text SET BroadcastTextID0=39490 WHERE ID=15630;
UPDATE npc_text SET BroadcastTextID0=39532 WHERE ID=15649;
UPDATE npc_text SET BroadcastTextID0=39534 WHERE ID=15651;
UPDATE npc_text SET BroadcastTextID0=39593 WHERE ID=15667;
UPDATE npc_text SET BroadcastTextID0=39597 WHERE ID=15669;
UPDATE npc_text SET BroadcastTextID0=39602 WHERE ID=15673;
UPDATE npc_text SET BroadcastTextID0=39603 WHERE ID=15674;
UPDATE npc_text SET BroadcastTextID0=39604 WHERE ID=15675;
UPDATE npc_text SET BroadcastTextID0=39608 WHERE ID=15679;
UPDATE npc_text SET BroadcastTextID0=39612 WHERE ID=15683;
UPDATE npc_text SET BroadcastTextID0=39613 WHERE ID=15684;
UPDATE npc_text SET BroadcastTextID0=39615 WHERE ID=15686;
UPDATE npc_text SET BroadcastTextID0=39616 WHERE ID=15687;
UPDATE npc_text SET BroadcastTextID0=39618 WHERE ID=15689;
UPDATE npc_text SET BroadcastTextID0=39621 WHERE ID=15692;
UPDATE npc_text SET BroadcastTextID0=39622 WHERE ID=15693;
UPDATE npc_text SET BroadcastTextID0=39623 WHERE ID=15694;
UPDATE npc_text SET BroadcastTextID0=39624 WHERE ID=15695;
UPDATE npc_text SET BroadcastTextID0=39633 WHERE ID=15697;
UPDATE npc_text SET BroadcastTextID0=39634 WHERE ID=15698;
UPDATE npc_text SET BroadcastTextID0=39635 WHERE ID=15699;
UPDATE npc_text SET BroadcastTextID0=39636 WHERE ID=15700;
UPDATE npc_text SET BroadcastTextID0=39668 WHERE ID=15704;
UPDATE npc_text SET BroadcastTextID0=39727 WHERE ID=15712;
UPDATE npc_text SET BroadcastTextID0=39736 WHERE ID=15714;
UPDATE npc_text SET BroadcastTextID0=39737 WHERE ID=15715;
UPDATE npc_text SET BroadcastTextID0=39765 WHERE ID=15730;
UPDATE npc_text SET BroadcastTextID0=39811 WHERE ID=15740;
UPDATE npc_text SET BroadcastTextID0=39840 WHERE ID=15750;
UPDATE npc_text SET BroadcastTextID0=39921 WHERE ID=15755;
UPDATE npc_text SET BroadcastTextID0=39984 WHERE ID=15770;
UPDATE npc_text SET BroadcastTextID0=40012 WHERE ID=15779;
UPDATE npc_text SET BroadcastTextID0=40024 WHERE ID=15784;
UPDATE npc_text SET BroadcastTextID0=40355 WHERE ID=15842;
UPDATE npc_text SET BroadcastTextID0=40383 WHERE ID=15845;
UPDATE npc_text SET BroadcastTextID0=40421 WHERE ID=15853;
UPDATE npc_text SET BroadcastTextID0=40424 WHERE ID=15855;
UPDATE npc_text SET BroadcastTextID0=40426 WHERE ID=15856;
UPDATE npc_text SET BroadcastTextID0=40428 WHERE ID=15857;
UPDATE npc_text SET BroadcastTextID0=40430 WHERE ID=15858;
UPDATE npc_text SET BroadcastTextID0=40432 WHERE ID=15859;
UPDATE npc_text SET BroadcastTextID0=40449 WHERE ID=15866;
UPDATE npc_text SET BroadcastTextID0=40482 WHERE ID=15877;
UPDATE npc_text SET BroadcastTextID0=40548 WHERE ID=15899;
UPDATE npc_text SET BroadcastTextID0=40591 WHERE ID=15906;
UPDATE npc_text SET BroadcastTextID0=40596 WHERE ID=15908;
UPDATE npc_text SET BroadcastTextID0=40663 WHERE ID=15922;
UPDATE npc_text SET BroadcastTextID0=40733 WHERE ID=15933;
UPDATE npc_text SET BroadcastTextID0=40767 WHERE ID=15937;
UPDATE npc_text SET BroadcastTextID0=40813 WHERE ID=15946;
UPDATE npc_text SET BroadcastTextID0=40901 WHERE ID=15956;
UPDATE npc_text SET BroadcastTextID0=40940 WHERE ID=15963;
UPDATE npc_text SET BroadcastTextID0=41038 WHERE ID=15978;
UPDATE npc_text SET BroadcastTextID0=41042 WHERE ID=15979;
UPDATE npc_text SET BroadcastTextID0=41054 WHERE ID=15981;
UPDATE npc_text SET BroadcastTextID0=41138 WHERE ID=16002;
UPDATE npc_text SET BroadcastTextID0=41151 WHERE ID=16008;
UPDATE npc_text SET BroadcastTextID0=41318 WHERE ID=16038;
UPDATE npc_text SET BroadcastTextID0=41320 WHERE ID=16040;
UPDATE npc_text SET BroadcastTextID0=41333 WHERE ID=16047;
UPDATE npc_text SET BroadcastTextID0=41356 WHERE ID=16055;
UPDATE npc_text SET BroadcastTextID0=41357 WHERE ID=16056;
UPDATE npc_text SET BroadcastTextID0=41364 WHERE ID=16060;
UPDATE npc_text SET BroadcastTextID0=41575 WHERE ID=16097;
UPDATE npc_text SET BroadcastTextID0=41582 WHERE ID=16099;
UPDATE npc_text SET BroadcastTextID0=41679 WHERE ID=16112;
UPDATE npc_text SET BroadcastTextID0=41676 WHERE ID=16114;
UPDATE npc_text SET BroadcastTextID0=41698 WHERE ID=16122;
UPDATE npc_text SET BroadcastTextID0=41761 WHERE ID=16140;
UPDATE npc_text SET BroadcastTextID0=42082 WHERE ID=16194;
UPDATE npc_text SET BroadcastTextID0=42086 WHERE ID=16197;
UPDATE npc_text SET BroadcastTextID0=42085 WHERE ID=16198;
UPDATE npc_text SET BroadcastTextID0=42230 WHERE ID=16215;
UPDATE npc_text SET BroadcastTextID0=42235 WHERE ID=16219;
UPDATE npc_text SET BroadcastTextID0=42245 WHERE ID=16222;
UPDATE npc_text SET BroadcastTextID0=42325 WHERE ID=16236;
UPDATE npc_text SET BroadcastTextID0=42337 WHERE ID=16241;
UPDATE npc_text SET BroadcastTextID0=42349 WHERE ID=16246;
UPDATE npc_text SET BroadcastTextID0=42494 WHERE ID=16269;
UPDATE npc_text SET BroadcastTextID0=42495 WHERE ID=16270;
UPDATE npc_text SET BroadcastTextID0=42527 WHERE ID=16275;
UPDATE npc_text SET BroadcastTextID0=42596 WHERE ID=16280;
UPDATE npc_text SET BroadcastTextID0=42720 WHERE ID=16297;
UPDATE npc_text SET BroadcastTextID0=42851 WHERE ID=16319;
UPDATE npc_text SET BroadcastTextID0=42863 WHERE ID=16324;
UPDATE npc_text SET BroadcastTextID0=42896 WHERE ID=16330;
UPDATE npc_text SET BroadcastTextID0=42910 WHERE ID=16334;
UPDATE npc_text SET BroadcastTextID0=42940 WHERE ID=16343;
UPDATE npc_text SET BroadcastTextID0=43199 WHERE ID=16375;
UPDATE npc_text SET BroadcastTextID0=43273 WHERE ID=16390;
UPDATE npc_text SET BroadcastTextID0=43282 WHERE ID=16393;
UPDATE npc_text SET BroadcastTextID0=43513 WHERE ID=16426;
UPDATE npc_text SET BroadcastTextID0=43834 WHERE ID=16491;
UPDATE npc_text SET BroadcastTextID0=43984 WHERE ID=16499;
UPDATE npc_text SET BroadcastTextID0=44301 WHERE ID=16510;
UPDATE npc_text SET BroadcastTextID0=44306 WHERE ID=16511;
UPDATE npc_text SET BroadcastTextID0=56602 WHERE ID=16536;
UPDATE npc_text SET BroadcastTextID0=44385 WHERE ID=16537;
UPDATE npc_text SET BroadcastTextID0=44402 WHERE ID=16542;
UPDATE npc_text SET BroadcastTextID0=44405 WHERE ID=16543;
UPDATE npc_text SET BroadcastTextID0=44426 WHERE ID=16547;
UPDATE npc_text SET BroadcastTextID0=44436 WHERE ID=16548;
UPDATE npc_text SET BroadcastTextID0=44441 WHERE ID=16550;
UPDATE npc_text SET BroadcastTextID0=44450 WHERE ID=16554;
UPDATE npc_text SET BroadcastTextID0=44453 WHERE ID=16557;
UPDATE npc_text SET BroadcastTextID0=44463 WHERE ID=16559;
UPDATE npc_text SET BroadcastTextID0=44494 WHERE ID=16569;
UPDATE npc_text SET BroadcastTextID0=44525 WHERE ID=16574;
UPDATE npc_text SET BroadcastTextID0=44540 WHERE ID=16581;
UPDATE npc_text SET BroadcastTextID0=44545 WHERE ID=16583;
UPDATE npc_text SET BroadcastTextID0=44552 WHERE ID=16586;
UPDATE npc_text SET BroadcastTextID0=44557 WHERE ID=16588;
UPDATE npc_text SET BroadcastTextID0=44572 WHERE ID=16595;
UPDATE npc_text SET BroadcastTextID0=44574 WHERE ID=16596;
UPDATE npc_text SET BroadcastTextID0=44611 WHERE ID=16609;
UPDATE npc_text SET BroadcastTextID0=45564 WHERE ID=16623;
UPDATE npc_text SET BroadcastTextID0=44644 WHERE ID=16624;
UPDATE npc_text SET BroadcastTextID0=44645 WHERE ID=16625;
UPDATE npc_text SET BroadcastTextID0=44729 WHERE ID=16638;
UPDATE npc_text SET BroadcastTextID0=44742 WHERE ID=16641;
UPDATE npc_text SET BroadcastTextID0=44743 WHERE ID=16642;
UPDATE npc_text SET BroadcastTextID0=44756 WHERE ID=16644;
UPDATE npc_text SET BroadcastTextID0=44809 WHERE ID=16661;
UPDATE npc_text SET BroadcastTextID0=44821 WHERE ID=16665;
UPDATE npc_text SET BroadcastTextID0=44871 WHERE ID=16672;
UPDATE npc_text SET BroadcastTextID0=44901 WHERE ID=16682;
UPDATE npc_text SET BroadcastTextID0=44945 WHERE ID=16691;
UPDATE npc_text SET BroadcastTextID0=45121 WHERE ID=16706;
UPDATE npc_text SET BroadcastTextID0=45125 WHERE ID=16716;
UPDATE npc_text SET BroadcastTextID0=45130 WHERE ID=16720;
UPDATE npc_text SET BroadcastTextID0=45276 WHERE ID=16751;
UPDATE npc_text SET BroadcastTextID0=45287 WHERE ID=16754;
UPDATE npc_text SET BroadcastTextID0=45290 WHERE ID=16756;
UPDATE npc_text SET BroadcastTextID0=45293 WHERE ID=16758;
UPDATE npc_text SET BroadcastTextID0=45295 WHERE ID=16759;
UPDATE npc_text SET BroadcastTextID0=45319 WHERE ID=16766;
UPDATE npc_text SET BroadcastTextID0=45320 WHERE ID=16767;
UPDATE npc_text SET BroadcastTextID0=45345 WHERE ID=16771;
UPDATE npc_text SET BroadcastTextID0=45373 WHERE ID=16784;
UPDATE npc_text SET BroadcastTextID0=45393 WHERE ID=16787;
UPDATE npc_text SET BroadcastTextID0=45397 WHERE ID=16790;
UPDATE npc_text SET BroadcastTextID0=45510 WHERE ID=16824;
UPDATE npc_text SET BroadcastTextID0=42041 WHERE ID=16829;
UPDATE npc_text SET BroadcastTextID0=45531 WHERE ID=16833;
UPDATE npc_text SET BroadcastTextID0=45564 WHERE ID=16845;
UPDATE npc_text SET BroadcastTextID0=45618 WHERE ID=16851;
UPDATE npc_text SET BroadcastTextID0=45795 WHERE ID=16880;
UPDATE npc_text SET BroadcastTextID0=45796 WHERE ID=16881;
UPDATE npc_text SET BroadcastTextID0=45799 WHERE ID=16884;
UPDATE npc_text SET BroadcastTextID0=45957 WHERE ID=16914;
UPDATE npc_text SET BroadcastTextID0=46055 WHERE ID=16938;
UPDATE npc_text SET BroadcastTextID0=46062 WHERE ID=16939;
UPDATE npc_text SET BroadcastTextID0=46097 WHERE ID=16948;
UPDATE npc_text SET BroadcastTextID0=46113 WHERE ID=16952;
UPDATE npc_text SET BroadcastTextID0=46115 WHERE ID=16954;
UPDATE npc_text SET BroadcastTextID0=46117 WHERE ID=16956;
UPDATE npc_text SET BroadcastTextID0=46128 WHERE ID=16959;
UPDATE npc_text SET BroadcastTextID0=50440 WHERE ID=16964;
UPDATE npc_text SET BroadcastTextID0=46163 WHERE ID=16967;
UPDATE npc_text SET BroadcastTextID0=46166 WHERE ID=16969;
UPDATE npc_text SET BroadcastTextID0=46179 WHERE ID=16974;
UPDATE npc_text SET BroadcastTextID0=46266 WHERE ID=16983;
UPDATE npc_text SET BroadcastTextID0=46318 WHERE ID=16985;
UPDATE npc_text SET BroadcastTextID0=46349 WHERE ID=16989;
UPDATE npc_text SET BroadcastTextID0=46435 WHERE ID=17016;
UPDATE npc_text SET BroadcastTextID0=46462 WHERE ID=17019;
UPDATE npc_text SET BroadcastTextID0=46469 WHERE ID=17020;
UPDATE npc_text SET BroadcastTextID0=46516 WHERE ID=17027;
UPDATE npc_text SET BroadcastTextID0=43700 WHERE ID=17029;
UPDATE npc_text SET BroadcastTextID0=46543 WHERE ID=17035;
UPDATE npc_text SET BroadcastTextID0=46629 WHERE ID=17045;
UPDATE npc_text SET BroadcastTextID0=67990 WHERE ID=17078;
UPDATE npc_text SET BroadcastTextID0=46841 WHERE ID=17079;
UPDATE npc_text SET BroadcastTextID0=47080 WHERE ID=17118;
UPDATE npc_text SET BroadcastTextID0=47274 WHERE ID=17161;
UPDATE npc_text SET BroadcastTextID0=47281 WHERE ID=17165;
UPDATE npc_text SET BroadcastTextID0=47895 WHERE ID=17166;
UPDATE npc_text SET BroadcastTextID0=47373 WHERE ID=17177;
UPDATE npc_text SET BroadcastTextID0=47503 WHERE ID=17200;
UPDATE npc_text SET BroadcastTextID0=47513 WHERE ID=17203;
UPDATE npc_text SET BroadcastTextID0=46267 WHERE ID=17204;
UPDATE npc_text SET BroadcastTextID0=47561 WHERE ID=17209;
UPDATE npc_text SET BroadcastTextID0=47571 WHERE ID=17213;
UPDATE npc_text SET BroadcastTextID0=47572 WHERE ID=17214;
UPDATE npc_text SET BroadcastTextID0=47604 WHERE ID=17227;
UPDATE npc_text SET BroadcastTextID0=47802 WHERE ID=17269;
UPDATE npc_text SET BroadcastTextID0=47803 WHERE ID=17270;
UPDATE npc_text SET BroadcastTextID0=47833 WHERE ID=17275;
UPDATE npc_text SET BroadcastTextID0=47890 WHERE ID=17291;
UPDATE npc_text SET BroadcastTextID0=47848 WHERE ID=17296;
UPDATE npc_text SET BroadcastTextID0=47964 WHERE ID=17305;
UPDATE npc_text SET BroadcastTextID0=47996 WHERE ID=17318;
UPDATE npc_text SET BroadcastTextID0=48043 WHERE ID=17330;
UPDATE npc_text SET BroadcastTextID0=48047 WHERE ID=17333;
UPDATE npc_text SET BroadcastTextID0=48049 WHERE ID=17334;
UPDATE npc_text SET BroadcastTextID0=48068 WHERE ID=17338;
UPDATE npc_text SET BroadcastTextID0=48096 WHERE ID=17347;
UPDATE npc_text SET BroadcastTextID0=48146 WHERE ID=17363;
UPDATE npc_text SET BroadcastTextID0=48251 WHERE ID=17397;
UPDATE npc_text SET BroadcastTextID0=48264 WHERE ID=17401;
UPDATE npc_text SET BroadcastTextID0=48302 WHERE ID=17408;
UPDATE npc_text SET BroadcastTextID0=48305 WHERE ID=17409;
UPDATE npc_text SET BroadcastTextID0=48347 WHERE ID=17416;
UPDATE npc_text SET BroadcastTextID0=48352 WHERE ID=17419;
UPDATE npc_text SET BroadcastTextID0=48355 WHERE ID=17422;
UPDATE npc_text SET BroadcastTextID0=48363 WHERE ID=17423;
UPDATE npc_text SET BroadcastTextID0=48395 WHERE ID=17431;
UPDATE npc_text SET BroadcastTextID0=48438 WHERE ID=17441;
UPDATE npc_text SET BroadcastTextID0=48458 WHERE ID=17446;
UPDATE npc_text SET BroadcastTextID0=48578 WHERE ID=17461;
UPDATE npc_text SET BroadcastTextID0=48608 WHERE ID=17468;
UPDATE npc_text SET BroadcastTextID0=48674 WHERE ID=17473;
UPDATE npc_text SET BroadcastTextID0=48810 WHERE ID=17498;
UPDATE npc_text SET BroadcastTextID0=48848 WHERE ID=17503;
UPDATE npc_text SET BroadcastTextID0=48887 WHERE ID=17514;
UPDATE npc_text SET BroadcastTextID0=48875 WHERE ID=17517;
UPDATE npc_text SET BroadcastTextID0=48959 WHERE ID=17521;
UPDATE npc_text SET BroadcastTextID0=49072 WHERE ID=17533;
UPDATE npc_text SET BroadcastTextID0=49078 WHERE ID=17534;
UPDATE npc_text SET BroadcastTextID0=49136 WHERE ID=17538;
UPDATE npc_text SET BroadcastTextID0=49139 WHERE ID=17541;
UPDATE npc_text SET BroadcastTextID0=49231 WHERE ID=17554;
UPDATE npc_text SET BroadcastTextID0=49240 WHERE ID=17556;
UPDATE npc_text SET BroadcastTextID0=49253 WHERE ID=17557;
UPDATE npc_text SET BroadcastTextID0=49355 WHERE ID=17572;
UPDATE npc_text SET BroadcastTextID0=49720 WHERE ID=17598;
UPDATE npc_text SET BroadcastTextID0=49766 WHERE ID=17608;
UPDATE npc_text SET BroadcastTextID0=49789 WHERE ID=17616;
UPDATE npc_text SET BroadcastTextID0=49975 WHERE ID=17659;
UPDATE npc_text SET BroadcastTextID0=50003 WHERE ID=17668;
UPDATE npc_text SET BroadcastTextID0=50014 WHERE ID=17671;
UPDATE npc_text SET BroadcastTextID0=50021 WHERE ID=17678;
UPDATE npc_text SET BroadcastTextID0=50024 WHERE ID=17681;
UPDATE npc_text SET BroadcastTextID0=50046 WHERE ID=17690;
UPDATE npc_text SET BroadcastTextID0=50047 WHERE ID=17691;
UPDATE npc_text SET BroadcastTextID0=50048 WHERE ID=17692;
UPDATE npc_text SET BroadcastTextID0=50049 WHERE ID=17693;
UPDATE npc_text SET BroadcastTextID0=50063 WHERE ID=17707;
UPDATE npc_text SET BroadcastTextID0=56604 WHERE ID=17711;
UPDATE npc_text SET BroadcastTextID0=50268 WHERE ID=17734;
UPDATE npc_text SET BroadcastTextID0=50312 WHERE ID=17740;
UPDATE npc_text SET BroadcastTextID0=50382 WHERE ID=17745;
UPDATE npc_text SET BroadcastTextID0=50398 WHERE ID=17746;
UPDATE npc_text SET BroadcastTextID0=50502 WHERE ID=17755;
UPDATE npc_text SET BroadcastTextID0=50624 WHERE ID=17772;
UPDATE npc_text SET BroadcastTextID0=50650 WHERE ID=17799;
UPDATE npc_text SET BroadcastTextID0=52379 WHERE ID=17800;
UPDATE npc_text SET BroadcastTextID0=72224 WHERE ID=17804;
UPDATE npc_text SET BroadcastTextID0=50695 WHERE ID=17816;
UPDATE npc_text SET BroadcastTextID0=50747 WHERE ID=17836;
UPDATE npc_text SET BroadcastTextID0=50748 WHERE ID=17837;
UPDATE npc_text SET BroadcastTextID0=50758 WHERE ID=17840;
UPDATE npc_text SET BroadcastTextID0=50793 WHERE ID=17849;
UPDATE npc_text SET BroadcastTextID0=50821 WHERE ID=17855;
UPDATE npc_text SET BroadcastTextID0=50901 WHERE ID=17878;
UPDATE npc_text SET BroadcastTextID0=50953 WHERE ID=17892;
UPDATE npc_text SET BroadcastTextID0=50991 WHERE ID=17897;
UPDATE npc_text SET BroadcastTextID0=51238 WHERE ID=17946;
UPDATE npc_text SET BroadcastTextID0=51263 WHERE ID=17950;
UPDATE npc_text SET BroadcastTextID0=51264 WHERE ID=17951;
UPDATE npc_text SET BroadcastTextID0=51385 WHERE ID=17972;
UPDATE npc_text SET BroadcastTextID0=51452 WHERE ID=17976;
UPDATE npc_text SET BroadcastTextID0=51470 WHERE ID=17983;
UPDATE npc_text SET BroadcastTextID0=51500 WHERE ID=17988;
UPDATE npc_text SET BroadcastTextID0=51520 WHERE ID=17990;
UPDATE npc_text SET BroadcastTextID0=51555 WHERE ID=17996;
UPDATE npc_text SET BroadcastTextID0=51566 WHERE ID=17999;
UPDATE npc_text SET BroadcastTextID0=51567 WHERE ID=18001;
UPDATE npc_text SET BroadcastTextID0=51579 WHERE ID=18002;
UPDATE npc_text SET BroadcastTextID0=51627 WHERE ID=18012;
UPDATE npc_text SET BroadcastTextID0=51871 WHERE ID=18041;
UPDATE npc_text SET BroadcastTextID0=51871 WHERE ID=18042;
UPDATE npc_text SET BroadcastTextID0=51882 WHERE ID=18043;
UPDATE npc_text SET BroadcastTextID0=51896 WHERE ID=18046;
UPDATE npc_text SET BroadcastTextID0=51906 WHERE ID=18050;
UPDATE npc_text SET BroadcastTextID0=51946 WHERE ID=18063;
UPDATE npc_text SET BroadcastTextID0=51948 WHERE ID=18064;
UPDATE npc_text SET BroadcastTextID0=51955 WHERE ID=18067;
UPDATE npc_text SET BroadcastTextID0=51958 WHERE ID=18070;
UPDATE npc_text SET BroadcastTextID0=51960 WHERE ID=18072;
UPDATE npc_text SET BroadcastTextID0=51969 WHERE ID=18076;
UPDATE npc_text SET BroadcastTextID0=52044 WHERE ID=18086;
UPDATE npc_text SET BroadcastTextID0=52053 WHERE ID=18090;
UPDATE npc_text SET BroadcastTextID0=10706 WHERE ID=18092;
UPDATE npc_text SET BroadcastTextID0=52056 WHERE ID=18093;
UPDATE npc_text SET BroadcastTextID0=52060 WHERE ID=18096;
UPDATE npc_text SET BroadcastTextID0=52070 WHERE ID=18104;
UPDATE npc_text SET BroadcastTextID0=52074 WHERE ID=18106;
UPDATE npc_text SET BroadcastTextID0=52131 WHERE ID=18116;
UPDATE npc_text SET BroadcastTextID0=52361 WHERE ID=18146;
UPDATE npc_text SET BroadcastTextID0=52367 WHERE ID=18150;
UPDATE npc_text SET BroadcastTextID0=52376 WHERE ID=18158;
UPDATE npc_text SET BroadcastTextID0=52377 WHERE ID=18159;
UPDATE npc_text SET BroadcastTextID0=52380 WHERE ID=18162;
UPDATE npc_text SET BroadcastTextID0=51731 WHERE ID=18165;
UPDATE npc_text SET BroadcastTextID0=52383 WHERE ID=18166;
UPDATE npc_text SET BroadcastTextID0=52384 WHERE ID=18167;
UPDATE npc_text SET BroadcastTextID0=14768 WHERE ID=18168;
UPDATE npc_text SET BroadcastTextID0=52386 WHERE ID=18170;
UPDATE npc_text SET BroadcastTextID0=52388 WHERE ID=18172;
UPDATE npc_text SET BroadcastTextID0=52390 WHERE ID=18174;
UPDATE npc_text SET BroadcastTextID0=52392 WHERE ID=18176;
UPDATE npc_text SET BroadcastTextID0=52460 WHERE ID=18189;
UPDATE npc_text SET BroadcastTextID0=52525 WHERE ID=18195;
UPDATE npc_text SET BroadcastTextID0=52538 WHERE ID=18200;
UPDATE npc_text SET BroadcastTextID0=52790 WHERE ID=18221;
UPDATE npc_text SET BroadcastTextID0=52914 WHERE ID=18243;
UPDATE npc_text SET BroadcastTextID0=52960 WHERE ID=18266;
UPDATE npc_text SET BroadcastTextID0=52965 WHERE ID=18268;
UPDATE npc_text SET BroadcastTextID0=53000 WHERE ID=18276;
UPDATE npc_text SET BroadcastTextID0=53037 WHERE ID=18286;
UPDATE npc_text SET BroadcastTextID0=53078 WHERE ID=18300;
UPDATE npc_text SET BroadcastTextID0=53079 WHERE ID=18301;
UPDATE npc_text SET BroadcastTextID0=53086 WHERE ID=18304;
UPDATE npc_text SET BroadcastTextID0=53118 WHERE ID=18314;
UPDATE npc_text SET BroadcastTextID0=62303 WHERE ID=18322;
UPDATE npc_text SET BroadcastTextID0=53188 WHERE ID=18329;
UPDATE npc_text SET BroadcastTextID0=53194 WHERE ID=18331;
UPDATE npc_text SET BroadcastTextID0=53290 WHERE ID=18347;
UPDATE npc_text SET BroadcastTextID0=53443 WHERE ID=18376;
UPDATE npc_text SET BroadcastTextID0=53700 WHERE ID=18429;
UPDATE npc_text SET BroadcastTextID0=53704 WHERE ID=18430;
UPDATE npc_text SET BroadcastTextID0=53824 WHERE ID=18472;
UPDATE npc_text SET BroadcastTextID0=54045 WHERE ID=18508;
UPDATE npc_text SET BroadcastTextID0=54122 WHERE ID=18514;
UPDATE npc_text SET BroadcastTextID0=54232 WHERE ID=18544;
UPDATE npc_text SET BroadcastTextID0=54224 WHERE ID=18550;
UPDATE npc_text SET BroadcastTextID0=54226 WHERE ID=18551;
UPDATE npc_text SET BroadcastTextID0=55137 WHERE ID=18698;
UPDATE npc_text SET BroadcastTextID0=55985 WHERE ID=18877;
UPDATE npc_text SET BroadcastTextID0=56178 WHERE ID=18879;
UPDATE npc_text SET BroadcastTextID0=56179 WHERE ID=18880;
UPDATE npc_text SET BroadcastTextID0=56587 WHERE ID=18954;
UPDATE npc_text SET BroadcastTextID0=56598 WHERE ID=18958;
UPDATE npc_text SET BroadcastTextID0=56602 WHERE ID=18959;
UPDATE npc_text SET BroadcastTextID0=56604 WHERE ID=18960;
UPDATE npc_text SET BroadcastTextID0=56609 WHERE ID=18962;
UPDATE npc_text SET BroadcastTextID0=56948 WHERE ID=19019;
UPDATE npc_text SET BroadcastTextID0=56957 WHERE ID=19024;
UPDATE npc_text SET BroadcastTextID0=18256 WHERE ID=20551;
UPDATE npc_text SET BroadcastTextID0=18249 WHERE ID=20564;
UPDATE npc_text SET BroadcastTextID0=18736 WHERE ID=21024;
UPDATE npc_text SET BroadcastTextID0=20641 WHERE ID=22932;
UPDATE npc_text SET BroadcastTextID0=31214 WHERE ID=31023;
UPDATE npc_text SET BroadcastTextID0=50429 WHERE ID=16777215;









UPDATE creature_template SET gossip_menu_id=1781 WHERE entry=233;
UPDATE creature_template SET gossip_menu_id=1 WHERE entry=234;
UPDATE creature_template SET gossip_menu_id=4941 WHERE entry=332;
UPDATE creature_template SET gossip_menu_id=6466 WHERE entry=347;
UPDATE creature_template SET gossip_menu_id=4466 WHERE entry=376;
UPDATE creature_template SET gossip_menu_id=4681 WHERE entry=460;
UPDATE creature_template SET gossip_menu_id=4503 WHERE entry=461;
UPDATE creature_template SET gossip_menu_id=685 WHERE entry=483;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=543;
UPDATE creature_template SET gossip_menu_id=10893 WHERE entry=786;
UPDATE creature_template SET gossip_menu_id=1262 WHERE entry=836;
UPDATE creature_template SET gossip_menu_id=6472 WHERE entry=907;
UPDATE creature_template SET gossip_menu_id=4676 WHERE entry=916;
UPDATE creature_template SET gossip_menu_id=4502 WHERE entry=918;
UPDATE creature_template SET gossip_menu_id=4664 WHERE entry=927;
UPDATE creature_template SET gossip_menu_id=4470 WHERE entry=928;
UPDATE creature_template SET gossip_menu_id=2745 WHERE entry=957;
UPDATE creature_template SET gossip_menu_id=523 WHERE entry=985;
UPDATE creature_template SET gossip_menu_id=4101 WHERE entry=987;
UPDATE creature_template SET gossip_menu_id=4642 WHERE entry=988;
UPDATE creature_template SET gossip_menu_id=11931 WHERE entry=1073;
UPDATE creature_template SET gossip_menu_id=140 WHERE entry=1139;
UPDATE creature_template SET gossip_menu_id=2801 WHERE entry=1154;
UPDATE creature_template SET gossip_menu_id=2831 WHERE entry=1156;
UPDATE creature_template SET gossip_menu_id=4110 WHERE entry=1215;
UPDATE creature_template SET gossip_menu_id=4007 WHERE entry=1231;
UPDATE creature_template SET gossip_menu_id=4677 WHERE entry=1232;
UPDATE creature_template SET gossip_menu_id=2741 WHERE entry=1241;
UPDATE creature_template SET gossip_menu_id=4001 WHERE entry=1261;
UPDATE creature_template SET gossip_menu_id=648 WHERE entry=1292;
UPDATE creature_template SET gossip_menu_id=687 WHERE entry=1298;
UPDATE creature_template SET gossip_menu_id=4262 WHERE entry=1300;
UPDATE creature_template SET gossip_menu_id=703 WHERE entry=1302;
UPDATE creature_template SET gossip_menu_id=703 WHERE entry=1303;
UPDATE creature_template SET gossip_menu_id=682 WHERE entry=1304;
UPDATE creature_template SET gossip_menu_id=701 WHERE entry=1305;
UPDATE creature_template SET gossip_menu_id=681 WHERE entry=1308;
UPDATE creature_template SET gossip_menu_id=681 WHERE entry=1309;
UPDATE creature_template SET gossip_menu_id=681 WHERE entry=1310;
UPDATE creature_template SET gossip_menu_id=700 WHERE entry=1311;
UPDATE creature_template SET gossip_menu_id=681 WHERE entry=1314;
UPDATE creature_template SET gossip_menu_id=4161 WHERE entry=1317;
UPDATE creature_template SET gossip_menu_id=688 WHERE entry=1319;
UPDATE creature_template SET gossip_menu_id=688 WHERE entry=1323;
UPDATE creature_template SET gossip_menu_id=690 WHERE entry=1324;
UPDATE creature_template SET gossip_menu_id=706 WHERE entry=1325;
UPDATE creature_template SET gossip_menu_id=705 WHERE entry=1326;
UPDATE creature_template SET gossip_menu_id=688 WHERE entry=1333;
UPDATE creature_template SET gossip_menu_id=689 WHERE entry=1339;
UPDATE creature_template SET gossip_menu_id=1632 WHERE entry=1340;
UPDATE creature_template SET gossip_menu_id=689 WHERE entry=1341;
UPDATE creature_template SET gossip_menu_id=694 WHERE entry=1343;
UPDATE creature_template SET gossip_menu_id=4353 WHERE entry=1346;
UPDATE creature_template SET gossip_menu_id=691 WHERE entry=1348;
UPDATE creature_template SET gossip_menu_id=691 WHERE entry=1349;
UPDATE creature_template SET gossip_menu_id=691 WHERE entry=1350;
UPDATE creature_template SET gossip_menu_id=692 WHERE entry=1351;
UPDATE creature_template SET gossip_menu_id=2782 WHERE entry=1383;
UPDATE creature_template SET gossip_menu_id=4208 WHERE entry=1385;
UPDATE creature_template SET gossip_menu_id=4134 WHERE entry=1386;
UPDATE creature_template SET gossip_menu_id=4658 WHERE entry=1411;
UPDATE creature_template SET gossip_menu_id=3501 WHERE entry=1694;
UPDATE creature_template SET gossip_menu_id=11874 WHERE entry=1747;
UPDATE creature_template SET gossip_menu_id=3502 WHERE entry=1855;
UPDATE creature_template SET gossip_menu_id=4322 WHERE entry=2057;
UPDATE creature_template SET gossip_menu_id=4046 WHERE entry=2079;
UPDATE creature_template SET gossip_menu_id=11499 WHERE entry=2104;
UPDATE creature_template SET gossip_menu_id=11788 WHERE entry=2153;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=2299;
UPDATE creature_template SET gossip_menu_id=6282 WHERE entry=2302;
UPDATE creature_template SET gossip_menu_id=657 WHERE entry=2327;
UPDATE creature_template SET gossip_menu_id=4004 WHERE entry=2357;
UPDATE creature_template SET gossip_menu_id=5542 WHERE entry=2393;
UPDATE creature_template SET gossip_menu_id=4356 WHERE entry=2399;
UPDATE creature_template SET gossip_menu_id=11673 WHERE entry=2464;
UPDATE creature_template SET gossip_menu_id=11674 WHERE entry=2465;
UPDATE creature_template SET gossip_menu_id=11744 WHERE entry=2487;
UPDATE creature_template SET gossip_menu_id=11727 WHERE entry=2491;
UPDATE creature_template SET gossip_menu_id=11675 WHERE entry=2497;
UPDATE creature_template SET gossip_menu_id=11743 WHERE entry=2663;
UPDATE creature_template SET gossip_menu_id=11881 WHERE entry=2700;
UPDATE creature_template SET gossip_menu_id=8846 WHERE entry=2708;
UPDATE creature_template SET gossip_menu_id=12636 WHERE entry=2771;
UPDATE creature_template SET gossip_menu_id=12131 WHERE entry=2785;
UPDATE creature_template SET gossip_menu_id=11712 WHERE entry=2789;
UPDATE creature_template SET gossip_menu_id=5856 WHERE entry=2798;
UPDATE creature_template SET gossip_menu_id=6462 WHERE entry=2804;
UPDATE creature_template SET gossip_menu_id=342 WHERE entry=2808;
UPDATE creature_template SET gossip_menu_id=5665 WHERE entry=2834;
UPDATE creature_template SET gossip_menu_id=2784 WHERE entry=2836;
UPDATE creature_template SET gossip_menu_id=4143 WHERE entry=2857;
UPDATE creature_template SET gossip_menu_id=4306 WHERE entry=2859;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=2879;
UPDATE creature_template SET gossip_menu_id=12202 WHERE entry=2920;
UPDATE creature_template SET gossip_menu_id=4045 WHERE entry=2980;
UPDATE creature_template SET gossip_menu_id=11006 WHERE entry=2981;
UPDATE creature_template SET gossip_menu_id=50000 WHERE entry=2993;
UPDATE creature_template SET gossip_menu_id=4351 WHERE entry=3004;
UPDATE creature_template SET gossip_menu_id=4242 WHERE entry=3007;
UPDATE creature_template SET gossip_menu_id=4187 WHERE entry=3008;
UPDATE creature_template SET gossip_menu_id=4128 WHERE entry=3009;
UPDATE creature_template SET gossip_menu_id=4165 WHERE entry=3011;
UPDATE creature_template SET gossip_menu_id=5854 WHERE entry=3026;
UPDATE creature_template SET gossip_menu_id=5665 WHERE entry=3028;
UPDATE creature_template SET gossip_menu_id=4528 WHERE entry=3030;
UPDATE creature_template SET gossip_menu_id=4530 WHERE entry=3031;
UPDATE creature_template SET gossip_menu_id=4529 WHERE entry=3032;
UPDATE creature_template SET gossip_menu_id=3921 WHERE entry=3033;
UPDATE creature_template SET gossip_menu_id=4606 WHERE entry=3034;
UPDATE creature_template SET gossip_menu_id=4607 WHERE entry=3036;
UPDATE creature_template SET gossip_menu_id=4011 WHERE entry=3038;
UPDATE creature_template SET gossip_menu_id=4023 WHERE entry=3039;
UPDATE creature_template SET gossip_menu_id=4524 WHERE entry=3040;
UPDATE creature_template SET gossip_menu_id=4526 WHERE entry=3041;
UPDATE creature_template SET gossip_menu_id=4525 WHERE entry=3042;
UPDATE creature_template SET gossip_menu_id=4527 WHERE entry=3043;
UPDATE creature_template SET gossip_menu_id=4533 WHERE entry=3044;
UPDATE creature_template SET gossip_menu_id=4531 WHERE entry=3045;
UPDATE creature_template SET gossip_menu_id=4532 WHERE entry=3046;
UPDATE creature_template SET gossip_menu_id=4535 WHERE entry=3049;
UPDATE creature_template SET gossip_menu_id=10181 WHERE entry=3079;
UPDATE creature_template SET gossip_menu_id=11790 WHERE entry=3139;
UPDATE creature_template SET gossip_menu_id=4643 WHERE entry=3156;
UPDATE creature_template SET gossip_menu_id=523 WHERE entry=3169;
UPDATE creature_template SET gossip_menu_id=4017 WHERE entry=3171;
UPDATE creature_template SET gossip_menu_id=4104 WHERE entry=3173;
UPDATE creature_template SET gossip_menu_id=8085 WHERE entry=3230;
UPDATE creature_template SET gossip_menu_id=12707 WHERE entry=3233;
UPDATE creature_template SET gossip_menu_id=4136 WHERE entry=3290;
UPDATE creature_template SET gossip_menu_id=11241 WHERE entry=3293;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=3306;
UPDATE creature_template SET gossip_menu_id=12056 WHERE entry=3322;
UPDATE creature_template SET gossip_menu_id=4603 WHERE entry=3324;
UPDATE creature_template SET gossip_menu_id=4604 WHERE entry=3325;
UPDATE creature_template SET gossip_menu_id=2384 WHERE entry=3326;
UPDATE creature_template SET gossip_menu_id=4741 WHERE entry=3332;
UPDATE creature_template SET gossip_menu_id=4168 WHERE entry=3345;
UPDATE creature_template SET gossip_menu_id=4509 WHERE entry=3353;
UPDATE creature_template SET gossip_menu_id=4511 WHERE entry=3354;
UPDATE creature_template SET gossip_menu_id=1626 WHERE entry=3370;
UPDATE creature_template SET gossip_menu_id=4761 WHERE entry=3373;
UPDATE creature_template SET gossip_menu_id=4747 WHERE entry=3399;
UPDATE creature_template SET gossip_menu_id=655 WHERE entry=3408;
UPDATE creature_template SET gossip_menu_id=11573 WHERE entry=3411;
UPDATE creature_template SET gossip_menu_id=11004 WHERE entry=3418;
UPDATE creature_template SET gossip_menu_id=10311 WHERE entry=3443;
UPDATE creature_template SET gossip_menu_id=10567 WHERE entry=3467;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=3545;
UPDATE creature_template SET gossip_menu_id=2749 WHERE entry=3557;
UPDATE creature_template SET gossip_menu_id=4695 WHERE entry=3596;
UPDATE creature_template SET gossip_menu_id=4688 WHERE entry=3597;
UPDATE creature_template SET gossip_menu_id=4009 WHERE entry=3601;
UPDATE creature_template SET gossip_menu_id=3923 WHERE entry=3602;
UPDATE creature_template SET gossip_menu_id=4111 WHERE entry=3603;
UPDATE creature_template SET gossip_menu_id=4156 WHERE entry=3606;
UPDATE creature_template SET gossip_menu_id=341 WHERE entry=3628;
UPDATE creature_template SET gossip_menu_id=5502 WHERE entry=3691;
UPDATE creature_template SET gossip_menu_id=10268 WHERE entry=3694;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=3698;
UPDATE creature_template SET gossip_menu_id=3644 WHERE entry=3706;
UPDATE creature_template SET gossip_menu_id=1201 WHERE entry=3836;
UPDATE creature_template SET gossip_menu_id=10313 WHERE entry=3845;
UPDATE creature_template SET gossip_menu_id=10312 WHERE entry=3846;
UPDATE creature_template SET gossip_menu_id=7406 WHERE entry=3848;
UPDATE creature_template SET gossip_menu_id=10181 WHERE entry=3881;
UPDATE creature_template SET gossip_menu_id=2561 WHERE entry=3885;
UPDATE creature_template SET gossip_menu_id=6459 WHERE entry=3890;
UPDATE creature_template SET gossip_menu_id=10522 WHERE entry=3916;
UPDATE creature_template SET gossip_menu_id=4092 WHERE entry=3963;
UPDATE creature_template SET gossip_menu_id=4117 WHERE entry=3964;
UPDATE creature_template SET gossip_menu_id=4211 WHERE entry=3967;
UPDATE creature_template SET gossip_menu_id=4578 WHERE entry=4089;
UPDATE creature_template SET gossip_menu_id=4621 WHERE entry=4138;
UPDATE creature_template SET gossip_menu_id=7487 WHERE entry=4161;
UPDATE creature_template SET gossip_menu_id=4263 WHERE entry=4193;
UPDATE creature_template SET gossip_menu_id=4304 WHERE entry=4200;
UPDATE creature_template SET gossip_menu_id=4241 WHERE entry=4212;
UPDATE creature_template SET gossip_menu_id=11778 WHERE entry=4265;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=4320;
UPDATE creature_template SET gossip_menu_id=4764 WHERE entry=4488;
UPDATE creature_template SET gossip_menu_id=4763 WHERE entry=4489;
UPDATE creature_template SET gossip_menu_id=8871 WHERE entry=4501;
UPDATE creature_template SET gossip_menu_id=12209 WHERE entry=4618;
UPDATE creature_template SET gossip_menu_id=4004 WHERE entry=4885;
UPDATE creature_template SET gossip_menu_id=12835 WHERE entry=4892;
UPDATE creature_template SET gossip_menu_id=12847 WHERE entry=4894;
UPDATE creature_template SET gossip_menu_id=541 WHERE entry=4895;
UPDATE creature_template SET gossip_menu_id=4122 WHERE entry=4900;
UPDATE creature_template SET gossip_menu_id=8840 WHERE entry=4921;
UPDATE creature_template SET gossip_menu_id=1186 WHERE entry=4926;
UPDATE creature_template SET gossip_menu_id=12846 WHERE entry=4941;
UPDATE creature_template SET gossip_menu_id=1161 WHERE entry=4944;
UPDATE creature_template SET gossip_menu_id=5301 WHERE entry=4967;
UPDATE creature_template SET gossip_menu_id=2465 WHERE entry=4968;
UPDATE creature_template SET gossip_menu_id=708 WHERE entry=4974;
UPDATE creature_template SET gossip_menu_id=8851 WHERE entry=4979;
UPDATE creature_template SET gossip_menu_id=685 WHERE entry=4981;
UPDATE creature_template SET gossip_menu_id=12093 WHERE entry=4984;
UPDATE creature_template SET gossip_menu_id=8793 WHERE entry=5086;
UPDATE creature_template SET gossip_menu_id=6464 WHERE entry=5118;
UPDATE creature_template SET gossip_menu_id=5462 WHERE entry=5130;
UPDATE creature_template SET gossip_menu_id=4160 WHERE entry=5157;
UPDATE creature_template SET gossip_menu_id=4748 WHERE entry=5159;
UPDATE creature_template SET gossip_menu_id=10392 WHERE entry=5193;
UPDATE creature_template SET gossip_menu_id=12848 WHERE entry=5388;
UPDATE creature_template SET gossip_menu_id=10771 WHERE entry=5395;
UPDATE creature_template SET gossip_menu_id=4468 WHERE entry=5484;
UPDATE creature_template SET gossip_menu_id=4467 WHERE entry=5489;
UPDATE creature_template SET gossip_menu_id=645 WHERE entry=5493;
UPDATE creature_template SET gossip_menu_id=685 WHERE entry=5494;
UPDATE creature_template SET gossip_menu_id=4505 WHERE entry=5495;
UPDATE creature_template SET gossip_menu_id=4504 WHERE entry=5496;
UPDATE creature_template SET gossip_menu_id=4484 WHERE entry=5498;
UPDATE creature_template SET gossip_menu_id=4201 WHERE entry=5499;
UPDATE creature_template SET gossip_menu_id=4112 WHERE entry=5500;
UPDATE creature_template SET gossip_menu_id=4694 WHERE entry=5501;
UPDATE creature_template SET gossip_menu_id=683 WHERE entry=5503;
UPDATE creature_template SET gossip_menu_id=4508 WHERE entry=5504;
UPDATE creature_template SET gossip_menu_id=4507 WHERE entry=5506;
UPDATE creature_template SET gossip_menu_id=693 WHERE entry=5509;
UPDATE creature_template SET gossip_menu_id=693 WHERE entry=5510;
UPDATE creature_template SET gossip_menu_id=581 WHERE entry=5511;
UPDATE creature_template SET gossip_menu_id=693 WHERE entry=5512;
UPDATE creature_template SET gossip_menu_id=693 WHERE entry=5514;
UPDATE creature_template SET gossip_menu_id=4474 WHERE entry=5515;
UPDATE creature_template SET gossip_menu_id=4473 WHERE entry=5516;
UPDATE creature_template SET gossip_menu_id=4472 WHERE entry=5517;
UPDATE creature_template SET gossip_menu_id=4146 WHERE entry=5518;
UPDATE creature_template SET gossip_menu_id=698 WHERE entry=5519;
UPDATE creature_template SET gossip_menu_id=4203 WHERE entry=5564;
UPDATE creature_template SET gossip_menu_id=4344 WHERE entry=5567;
UPDATE creature_template SET gossip_menu_id=900 WHERE entry=5594;
UPDATE creature_template SET gossip_menu_id=4682 WHERE entry=5612;
UPDATE creature_template SET gossip_menu_id=11017 WHERE entry=5627;
UPDATE creature_template SET gossip_menu_id=11714 WHERE entry=5636;
UPDATE creature_template SET gossip_menu_id=1629 WHERE entry=5769;
UPDATE creature_template SET gossip_menu_id=4186 WHERE entry=5784;
UPDATE creature_template SET gossip_menu_id=11431 WHERE entry=5835;
UPDATE creature_template SET gossip_menu_id=12271 WHERE entry=5843;
UPDATE creature_template SET gossip_menu_id=10031 WHERE entry=5875;
UPDATE creature_template SET gossip_menu_id=64 WHERE entry=5880;
UPDATE creature_template SET gossip_menu_id=1281 WHERE entry=5901;
UPDATE creature_template SET gossip_menu_id=5856 WHERE entry=5939;
UPDATE creature_template SET gossip_menu_id=5665 WHERE entry=5941;
UPDATE creature_template SET gossip_menu_id=5856 WHERE entry=5943;
UPDATE creature_template SET gossip_menu_id=4522 WHERE entry=5994;
UPDATE creature_template SET gossip_menu_id=4523 WHERE entry=6014;
UPDATE creature_template SET gossip_menu_id=4521 WHERE entry=6018;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=6026;
UPDATE creature_template SET gossip_menu_id=10526 WHERE entry=6091;
UPDATE creature_template SET gossip_menu_id=5641 WHERE entry=6122;
UPDATE creature_template SET gossip_menu_id=2385 WHERE entry=6251;
UPDATE creature_template SET gossip_menu_id=2603 WHERE entry=6266;
UPDATE creature_template SET gossip_menu_id=342 WHERE entry=6272;
UPDATE creature_template SET gossip_menu_id=2743 WHERE entry=6299;
UPDATE creature_template SET gossip_menu_id=12726 WHERE entry=6301;
UPDATE creature_template SET gossip_menu_id=2916 WHERE entry=6546;
UPDATE creature_template SET gossip_menu_id=1301 WHERE entry=6568;
UPDATE creature_template SET gossip_menu_id=231 WHERE entry=6626;
UPDATE creature_template SET gossip_menu_id=3984 WHERE entry=6707;
UPDATE creature_template SET gossip_menu_id=347 WHERE entry=6737;
UPDATE creature_template SET gossip_menu_id=1581 WHERE entry=6738;
UPDATE creature_template SET gossip_menu_id=4861 WHERE entry=6766;
UPDATE creature_template SET gossip_menu_id=10900 WHERE entry=6782;
UPDATE creature_template SET gossip_menu_id=10270 WHERE entry=6887;
UPDATE creature_template SET gossip_menu_id=6229 WHERE entry=7010;
UPDATE creature_template SET gossip_menu_id=1043 WHERE entry=7230;
UPDATE creature_template SET gossip_menu_id=1042 WHERE entry=7231;
UPDATE creature_template SET gossip_menu_id=1041 WHERE entry=7232;
UPDATE creature_template SET gossip_menu_id=752 WHERE entry=7363;
UPDATE creature_template SET gossip_menu_id=6468 WHERE entry=7427;
UPDATE creature_template SET gossip_menu_id=800 WHERE entry=7505;
UPDATE creature_template SET gossip_menu_id=820 WHERE entry=7506;
UPDATE creature_template SET gossip_menu_id=840 WHERE entry=7572;
UPDATE creature_template SET gossip_menu_id=941 WHERE entry=7604;
UPDATE creature_template SET gossip_menu_id=940 WHERE entry=7607;
UPDATE creature_template SET gossip_menu_id=1581 WHERE entry=7736;
UPDATE creature_template SET gossip_menu_id=345 WHERE entry=7744;
UPDATE creature_template SET gossip_menu_id=1761 WHERE entry=7766;
UPDATE creature_template SET gossip_menu_id=11876 WHERE entry=7770;
UPDATE creature_template SET gossip_menu_id=2851 WHERE entry=7776;
UPDATE creature_template SET gossip_menu_id=11487 WHERE entry=7783;
UPDATE creature_template SET gossip_menu_id=1965 WHERE entry=7852;
UPDATE creature_template SET gossip_menu_id=1964 WHERE entry=7854;
UPDATE creature_template SET gossip_menu_id=3067 WHERE entry=7866;
UPDATE creature_template SET gossip_menu_id=3070 WHERE entry=7868;
UPDATE creature_template SET gossip_menu_id=3072 WHERE entry=7870;
UPDATE creature_template SET gossip_menu_id=57000 WHERE entry=7918;
UPDATE creature_template SET gossip_menu_id=11390 WHERE entry=7937;
UPDATE creature_template SET gossip_menu_id=4133 WHERE entry=7948;
UPDATE creature_template SET gossip_menu_id=4164 WHERE entry=7949;
UPDATE creature_template SET gossip_menu_id=6565 WHERE entry=7951;
UPDATE creature_template SET gossip_menu_id=3162 WHERE entry=7952;
UPDATE creature_template SET gossip_menu_id=4016 WHERE entry=7954;
UPDATE creature_template SET gossip_menu_id=3186 WHERE entry=7955;
UPDATE creature_template SET gossip_menu_id=1080 WHERE entry=7998;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=8019;
UPDATE creature_template SET gossip_menu_id=1141 WHERE entry=8115;
UPDATE creature_template SET gossip_menu_id=1469 WHERE entry=8126;
UPDATE creature_template SET gossip_menu_id=4662 WHERE entry=8140;
UPDATE creature_template SET gossip_menu_id=4091 WHERE entry=8141;
UPDATE creature_template SET gossip_menu_id=4646 WHERE entry=8142;
UPDATE creature_template SET gossip_menu_id=4842 WHERE entry=8153;
UPDATE creature_template SET gossip_menu_id=5854 WHERE entry=8306;
UPDATE creature_template SET gossip_menu_id=4092 WHERE entry=8308;
UPDATE creature_template SET gossip_menu_id=12741 WHERE entry=8320;
UPDATE creature_template SET gossip_menu_id=1362 WHERE entry=8399;
UPDATE creature_template SET gossip_menu_id=10898 WHERE entry=8416;
UPDATE creature_template SET gossip_menu_id=2306 WHERE entry=8441;
UPDATE creature_template SET gossip_menu_id=1323 WHERE entry=8479;
UPDATE creature_template SET gossip_menu_id=1625 WHERE entry=8509;
UPDATE creature_template SET gossip_menu_id=1401 WHERE entry=8576;
UPDATE creature_template SET gossip_menu_id=1470 WHERE entry=8579;
UPDATE creature_template SET gossip_menu_id=10331 WHERE entry=8582;
UPDATE creature_template SET gossip_menu_id=10832 WHERE entry=8586;
UPDATE creature_template SET gossip_menu_id=1405 WHERE entry=8612;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=8664;
UPDATE creature_template SET gossip_menu_id=1961 WHERE entry=8737;
UPDATE creature_template SET gossip_menu_id=1483 WHERE entry=8767;
UPDATE creature_template SET gossip_menu_id=1541 WHERE entry=8816;
UPDATE creature_template SET gossip_menu_id=1822 WHERE entry=9021;
UPDATE creature_template SET gossip_menu_id=1941 WHERE entry=9034;
UPDATE creature_template SET gossip_menu_id=1943 WHERE entry=9035;
UPDATE creature_template SET gossip_menu_id=1944 WHERE entry=9036;
UPDATE creature_template SET gossip_menu_id=1945 WHERE entry=9037;
UPDATE creature_template SET gossip_menu_id=1946 WHERE entry=9038;
UPDATE creature_template SET gossip_menu_id=1947 WHERE entry=9039;
UPDATE creature_template SET gossip_menu_id=1948 WHERE entry=9040;
UPDATE creature_template SET gossip_menu_id=1662 WHERE entry=9047;
UPDATE creature_template SET gossip_menu_id=1681 WHERE entry=9076;
UPDATE creature_template SET gossip_menu_id=1701 WHERE entry=9087;
UPDATE creature_template SET gossip_menu_id=3142 WHERE entry=9116;
UPDATE creature_template SET gossip_menu_id=5630 WHERE entry=9118;
UPDATE creature_template SET gossip_menu_id=12662 WHERE entry=9177;
UPDATE creature_template SET gossip_menu_id=1914 WHERE entry=9299;
UPDATE creature_template SET gossip_menu_id=12743 WHERE entry=9316;
UPDATE creature_template SET gossip_menu_id=40060 WHERE entry=9459;
UPDATE creature_template SET gossip_menu_id=7956 WHERE entry=9460;
UPDATE creature_template SET gossip_menu_id=3925 WHERE entry=9465;
UPDATE creature_template SET gossip_menu_id=12128 WHERE entry=9503;
UPDATE creature_template SET gossip_menu_id=11618 WHERE entry=9540;
UPDATE creature_template SET gossip_menu_id=5541 WHERE entry=9544;
UPDATE creature_template SET gossip_menu_id=1962 WHERE entry=9545;
UPDATE creature_template SET gossip_menu_id=1966 WHERE entry=9554;
UPDATE creature_template SET gossip_menu_id=2061 WHERE entry=9563;
UPDATE creature_template SET gossip_menu_id=4844 WHERE entry=9584;
UPDATE creature_template SET gossip_menu_id=2464 WHERE entry=9676;
UPDATE creature_template SET gossip_menu_id=55002 WHERE entry=9937;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=9977;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=9980;
UPDATE creature_template SET gossip_menu_id=11971 WHERE entry=9988;
UPDATE creature_template SET gossip_menu_id=2362 WHERE entry=9990;
UPDATE creature_template SET gossip_menu_id=1966 WHERE entry=10043;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=10047;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=10059;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=10061;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=10086;
UPDATE creature_template SET gossip_menu_id=5481 WHERE entry=10182;
UPDATE creature_template SET gossip_menu_id=2562 WHERE entry=10216;
UPDATE creature_template SET gossip_menu_id=4863 WHERE entry=10219;
UPDATE creature_template SET gossip_menu_id=12663 WHERE entry=10260;
UPDATE creature_template SET gossip_menu_id=2602 WHERE entry=10267;
UPDATE creature_template SET gossip_menu_id=2703 WHERE entry=10307;
UPDATE creature_template SET gossip_menu_id=6461 WHERE entry=10360;
UPDATE creature_template SET gossip_menu_id=3649 WHERE entry=10433;
UPDATE creature_template SET gossip_menu_id=3647 WHERE entry=10475;
UPDATE creature_template SET gossip_menu_id=3062 WHERE entry=10578;
UPDATE creature_template SET gossip_menu_id=3130 WHERE entry=10618;
UPDATE creature_template SET gossip_menu_id=2871 WHERE entry=10668;
UPDATE creature_template SET gossip_menu_id=2921 WHERE entry=10739;
UPDATE creature_template SET gossip_menu_id=3063 WHERE entry=10740;
UPDATE creature_template SET gossip_menu_id=2951 WHERE entry=10776;
UPDATE creature_template SET gossip_menu_id=2961 WHERE entry=10778;
UPDATE creature_template SET gossip_menu_id=2943 WHERE entry=10782;
UPDATE creature_template SET gossip_menu_id=3382 WHERE entry=10839;
UPDATE creature_template SET gossip_menu_id=3441 WHERE entry=10857;
UPDATE creature_template SET gossip_menu_id=3043 WHERE entry=10917;
UPDATE creature_template SET gossip_menu_id=3049 WHERE entry=10918;
UPDATE creature_template SET gossip_menu_id=3074 WHERE entry=10922;
UPDATE creature_template SET gossip_menu_id=5482 WHERE entry=10929;
UPDATE creature_template SET gossip_menu_id=3861 WHERE entry=10936;
UPDATE creature_template SET gossip_menu_id=3922 WHERE entry=10945;
UPDATE creature_template SET gossip_menu_id=3129 WHERE entry=11016;
UPDATE creature_template SET gossip_menu_id=3128 WHERE entry=11019;
UPDATE creature_template SET gossip_menu_id=4139 WHERE entry=11026;
UPDATE creature_template SET gossip_menu_id=4138 WHERE entry=11037;
UPDATE creature_template SET gossip_menu_id=4355 WHERE entry=11052;
UPDATE creature_template SET gossip_menu_id=3183 WHERE entry=11055;
UPDATE creature_template SET gossip_menu_id=3141 WHERE entry=11064;
UPDATE creature_template SET gossip_menu_id=4159 WHERE entry=11066;
UPDATE creature_template SET gossip_menu_id=4153 WHERE entry=11068;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=11069;
UPDATE creature_template SET gossip_menu_id=4169 WHERE entry=11072;
UPDATE creature_template SET gossip_menu_id=4171 WHERE entry=11073;
UPDATE creature_template SET gossip_menu_id=4170 WHERE entry=11074;
UPDATE creature_template SET gossip_menu_id=12502 WHERE entry=11079;
UPDATE creature_template SET gossip_menu_id=4173 WHERE entry=11096;
UPDATE creature_template SET gossip_menu_id=4244 WHERE entry=11098;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=11119;
UPDATE creature_template SET gossip_menu_id=3187 WHERE entry=11176;
UPDATE creature_template SET gossip_menu_id=3202 WHERE entry=11178;
UPDATE creature_template SET gossip_menu_id=6090 WHERE entry=11191;
UPDATE creature_template SET gossip_menu_id=6089 WHERE entry=11192;
UPDATE creature_template SET gossip_menu_id=6091 WHERE entry=11193;
UPDATE creature_template SET gossip_menu_id=3310 WHERE entry=11216;
UPDATE creature_template SET gossip_menu_id=3362 WHERE entry=11277;
UPDATE creature_template SET gossip_menu_id=3363 WHERE entry=11279;
UPDATE creature_template SET gossip_menu_id=3363 WHERE entry=11281;
UPDATE creature_template SET gossip_menu_id=3372 WHERE entry=11286;
UPDATE creature_template SET gossip_menu_id=3381 WHERE entry=11316;
UPDATE creature_template SET gossip_menu_id=4025 WHERE entry=11317;
UPDATE creature_template SET gossip_menu_id=11393 WHERE entry=11390;
UPDATE creature_template SET gossip_menu_id=3643 WHERE entry=11397;
UPDATE creature_template SET gossip_menu_id=5746 WHERE entry=11441;
UPDATE creature_template SET gossip_menu_id=5746 WHERE entry=11444;
UPDATE creature_template SET gossip_menu_id=5602 WHERE entry=11491;
UPDATE creature_template SET gossip_menu_id=3481 WHERE entry=11548;
UPDATE creature_template SET gossip_menu_id=3963 WHERE entry=11626;
UPDATE creature_template SET gossip_menu_id=3650 WHERE entry=11627;
UPDATE creature_template SET gossip_menu_id=10438 WHERE entry=11701;
UPDATE creature_template SET gossip_menu_id=4084 WHERE entry=11799;
UPDATE creature_template SET gossip_menu_id=4041 WHERE entry=11800;
UPDATE creature_template SET gossip_menu_id=3901 WHERE entry=11802;
UPDATE creature_template SET gossip_menu_id=10329 WHERE entry=11806;
UPDATE creature_template SET gossip_menu_id=3661 WHERE entry=11833;
UPDATE creature_template SET gossip_menu_id=10889 WHERE entry=11857;
UPDATE creature_template SET gossip_menu_id=5266 WHERE entry=11869;
UPDATE creature_template SET gossip_menu_id=3962 WHERE entry=11878;
UPDATE creature_template SET gossip_menu_id=4093 WHERE entry=12018;
UPDATE creature_template SET gossip_menu_id=12019 WHERE entry=12029;
UPDATE creature_template SET gossip_menu_id=4066 WHERE entry=12031;
UPDATE creature_template SET gossip_menu_id=5241 WHERE entry=12096;
UPDATE creature_template SET gossip_menu_id=3862 WHERE entry=12144;
UPDATE creature_template SET gossip_menu_id=6474 WHERE entry=12198;
UPDATE creature_template SET gossip_menu_id=5304 WHERE entry=12238;
UPDATE creature_template SET gossip_menu_id=4003 WHERE entry=12245;
UPDATE creature_template SET gossip_menu_id=4002 WHERE entry=12246;
UPDATE creature_template SET gossip_menu_id=4162 WHERE entry=12340;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=12577;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=12578;
UPDATE creature_template SET gossip_menu_id=10434 WHERE entry=12616;
UPDATE creature_template SET gossip_menu_id=12237 WHERE entry=12636;
UPDATE creature_template SET gossip_menu_id=4357 WHERE entry=12716;
UPDATE creature_template SET gossip_menu_id=5161 WHERE entry=12724;
UPDATE creature_template SET gossip_menu_id=4441 WHERE entry=12737;
UPDATE creature_template SET gossip_menu_id=4401 WHERE entry=12757;
UPDATE creature_template SET gossip_menu_id=4981 WHERE entry=12863;
UPDATE creature_template SET gossip_menu_id=4601 WHERE entry=12866;
UPDATE creature_template SET gossip_menu_id=6445 WHERE entry=12919;
UPDATE creature_template SET gossip_menu_id=5382 WHERE entry=12939;
UPDATE creature_template SET gossip_menu_id=4841 WHERE entry=12997;
UPDATE creature_template SET gossip_menu_id=21212 WHERE entry=13000;
UPDATE creature_template SET gossip_menu_id=4845 WHERE entry=13018;
UPDATE creature_template SET gossip_menu_id=4922 WHERE entry=13085;
UPDATE creature_template SET gossip_menu_id=5124 WHERE entry=13176;
UPDATE creature_template SET gossip_menu_id=5065 WHERE entry=13278;
UPDATE creature_template SET gossip_menu_id=5061 WHERE entry=13283;
UPDATE creature_template SET gossip_menu_id=5109 WHERE entry=13322;
UPDATE creature_template SET gossip_menu_id=6768 WHERE entry=13418;
UPDATE creature_template SET gossip_menu_id=5181 WHERE entry=13420;
UPDATE creature_template SET gossip_menu_id=6769 WHERE entry=13433;
UPDATE creature_template SET gossip_menu_id=5181 WHERE entry=13434;
UPDATE creature_template SET gossip_menu_id=5181 WHERE entry=13435;
UPDATE creature_template SET gossip_menu_id=5232 WHERE entry=13445;
UPDATE creature_template SET gossip_menu_id=11997 WHERE entry=13476;
UPDATE creature_template SET gossip_menu_id=5521 WHERE entry=13697;
UPDATE creature_template SET gossip_menu_id=5303 WHERE entry=13699;
UPDATE creature_template SET gossip_menu_id=5349 WHERE entry=13716;
UPDATE creature_template SET gossip_menu_id=5321 WHERE entry=13717;
UPDATE creature_template SET gossip_menu_id=6261 WHERE entry=13776;
UPDATE creature_template SET gossip_menu_id=6262 WHERE entry=13777;
UPDATE creature_template SET gossip_menu_id=5441 WHERE entry=13840;
UPDATE creature_template SET gossip_menu_id=5442 WHERE entry=13841;
UPDATE creature_template SET gossip_menu_id=5602 WHERE entry=14241;
UPDATE creature_template SET gossip_menu_id=5734 WHERE entry=14321;
UPDATE creature_template SET gossip_menu_id=5721 WHERE entry=14322;
UPDATE creature_template SET gossip_menu_id=5733 WHERE entry=14323;
UPDATE creature_template SET gossip_menu_id=5742 WHERE entry=14324;
UPDATE creature_template SET gossip_menu_id=5739 WHERE entry=14325;
UPDATE creature_template SET gossip_menu_id=5735 WHERE entry=14326;
UPDATE creature_template SET gossip_menu_id=5667 WHERE entry=14338;
UPDATE creature_template SET gossip_menu_id=5708 WHERE entry=14353;
UPDATE creature_template SET gossip_menu_id=5710 WHERE entry=14354;
UPDATE creature_template SET gossip_menu_id=5747 WHERE entry=14368;
UPDATE creature_template SET gossip_menu_id=5737 WHERE entry=14369;
UPDATE creature_template SET gossip_menu_id=5741 WHERE entry=14374;
UPDATE creature_template SET gossip_menu_id=5755 WHERE entry=14381;
UPDATE creature_template SET gossip_menu_id=5756 WHERE entry=14382;
UPDATE creature_template SET gossip_menu_id=5748 WHERE entry=14383;
UPDATE creature_template SET gossip_menu_id=5752 WHERE entry=14392;
UPDATE creature_template SET gossip_menu_id=11738 WHERE entry=14395;
UPDATE creature_template SET gossip_menu_id=5818 WHERE entry=14437;
UPDATE creature_template SET gossip_menu_id=5820 WHERE entry=14444;
UPDATE creature_template SET gossip_menu_id=5849 WHERE entry=14450;
UPDATE creature_template SET gossip_menu_id=5848 WHERE entry=14451;
UPDATE creature_template SET gossip_menu_id=5845 WHERE entry=14469;
UPDATE creature_template SET gossip_menu_id=5868 WHERE entry=14527;
UPDATE creature_template SET gossip_menu_id=5869 WHERE entry=14528;
UPDATE creature_template SET gossip_menu_id=6041 WHERE entry=14722;
UPDATE creature_template SET gossip_menu_id=6034 WHERE entry=14727;
UPDATE creature_template SET gossip_menu_id=6037 WHERE entry=14728;
UPDATE creature_template SET gossip_menu_id=6059 WHERE entry=14731;
UPDATE creature_template SET gossip_menu_id=6523 WHERE entry=14733;
UPDATE creature_template SET gossip_menu_id=6085 WHERE entry=14737;
UPDATE creature_template SET gossip_menu_id=6083 WHERE entry=14738;
UPDATE creature_template SET gossip_menu_id=6086 WHERE entry=14739;
UPDATE creature_template SET gossip_menu_id=6087 WHERE entry=14740;
UPDATE creature_template SET gossip_menu_id=6088 WHERE entry=14741;
UPDATE creature_template SET gossip_menu_id=6092 WHERE entry=14742;
UPDATE creature_template SET gossip_menu_id=6524 WHERE entry=14781;
UPDATE creature_template SET gossip_menu_id=6182 WHERE entry=14823;
UPDATE creature_template SET gossip_menu_id=6184 WHERE entry=14827;
UPDATE creature_template SET gossip_menu_id=6183 WHERE entry=14828;
UPDATE creature_template SET gossip_menu_id=6161 WHERE entry=14829;
UPDATE creature_template SET gossip_menu_id=6223 WHERE entry=14832;
UPDATE creature_template SET gossip_menu_id=6224 WHERE entry=14833;
UPDATE creature_template SET gossip_menu_id=6225 WHERE entry=14841;
UPDATE creature_template SET gossip_menu_id=6213 WHERE entry=14842;
UPDATE creature_template SET gossip_menu_id=6230 WHERE entry=14844;
UPDATE creature_template SET gossip_menu_id=6234 WHERE entry=14845;
UPDATE creature_template SET gossip_menu_id=6233 WHERE entry=14846;
UPDATE creature_template SET gossip_menu_id=6201 WHERE entry=14849;
UPDATE creature_template SET gossip_menu_id=6232 WHERE entry=14866;
UPDATE creature_template SET gossip_menu_id=6227 WHERE entry=14871;
UPDATE creature_template SET gossip_menu_id=21262 WHERE entry=14905;
UPDATE creature_template SET gossip_menu_id=6467 WHERE entry=14942;
UPDATE creature_template SET gossip_menu_id=6460 WHERE entry=14981;
UPDATE creature_template SET gossip_menu_id=6463 WHERE entry=14982;
UPDATE creature_template SET gossip_menu_id=6323 WHERE entry=14983;
UPDATE creature_template SET gossip_menu_id=6324 WHERE entry=14984;
UPDATE creature_template SET gossip_menu_id=6478 WHERE entry=14990;
UPDATE creature_template SET gossip_menu_id=6470 WHERE entry=15006;
UPDATE creature_template SET gossip_menu_id=6473 WHERE entry=15008;
UPDATE creature_template SET gossip_menu_id=6343 WHERE entry=15011;
UPDATE creature_template SET gossip_menu_id=6342 WHERE entry=15012;
UPDATE creature_template SET gossip_menu_id=6361 WHERE entry=15021;
UPDATE creature_template SET gossip_menu_id=6362 WHERE entry=15022;
UPDATE creature_template SET gossip_menu_id=21258 WHERE entry=15042;
UPDATE creature_template SET gossip_menu_id=6421 WHERE entry=15077;
UPDATE creature_template SET gossip_menu_id=6514 WHERE entry=15078;
UPDATE creature_template SET gossip_menu_id=6447 WHERE entry=15079;
UPDATE creature_template SET gossip_menu_id=6510 WHERE entry=15102;
UPDATE creature_template SET gossip_menu_id=6492 WHERE entry=15105;
UPDATE creature_template SET gossip_menu_id=6525 WHERE entry=15174;
UPDATE creature_template SET gossip_menu_id=6526 WHERE entry=15175;
UPDATE creature_template SET gossip_menu_id=6528 WHERE entry=15179;
UPDATE creature_template SET gossip_menu_id=6529 WHERE entry=15180;
UPDATE creature_template SET gossip_menu_id=6530 WHERE entry=15181;
UPDATE creature_template SET gossip_menu_id=6531 WHERE entry=15182;
UPDATE creature_template SET gossip_menu_id=6532 WHERE entry=15183;
UPDATE creature_template SET gossip_menu_id=12129 WHERE entry=15187;
UPDATE creature_template SET gossip_menu_id=12125 WHERE entry=15188;
UPDATE creature_template SET gossip_menu_id=6541 WHERE entry=15191;
UPDATE creature_template SET gossip_menu_id=6539 WHERE entry=15192;
UPDATE creature_template SET gossip_menu_id=6596 WHERE entry=15194;
UPDATE creature_template SET gossip_menu_id=6564 WHERE entry=15270;
UPDATE creature_template SET gossip_menu_id=11902 WHERE entry=15278;
UPDATE creature_template SET gossip_menu_id=14137 WHERE entry=15280;
UPDATE creature_template SET gossip_menu_id=6570 WHERE entry=15281;
UPDATE creature_template SET gossip_menu_id=6567 WHERE entry=15282;
UPDATE creature_template SET gossip_menu_id=6568 WHERE entry=15293;
UPDATE creature_template SET gossip_menu_id=6573 WHERE entry=15301;
UPDATE creature_template SET gossip_menu_id=13064 WHERE entry=15303;
UPDATE creature_template SET gossip_menu_id=6583 WHERE entry=15306;
UPDATE creature_template SET gossip_menu_id=7324 WHERE entry=15397;
UPDATE creature_template SET gossip_menu_id=7255 WHERE entry=15398;
UPDATE creature_template SET gossip_menu_id=7344 WHERE entry=15399;
UPDATE creature_template SET gossip_menu_id=7256 WHERE entry=15400;
UPDATE creature_template SET gossip_menu_id=7325 WHERE entry=15401;
UPDATE creature_template SET gossip_menu_id=6940 WHERE entry=15403;
UPDATE creature_template SET gossip_menu_id=7196 WHERE entry=15404;
UPDATE creature_template SET gossip_menu_id=7234 WHERE entry=15405;
UPDATE creature_template SET gossip_menu_id=7141 WHERE entry=15416;
UPDATE creature_template SET gossip_menu_id=21310 WHERE entry=15420;
UPDATE creature_template SET gossip_menu_id=6623 WHERE entry=15443;
UPDATE creature_template SET gossip_menu_id=21276 WHERE entry=15481;
UPDATE creature_template SET gossip_menu_id=12670 WHERE entry=15494;
UPDATE creature_template SET gossip_menu_id=6928 WHERE entry=15498;
UPDATE creature_template SET gossip_menu_id=6927 WHERE entry=15500;
UPDATE creature_template SET gossip_menu_id=8376 WHERE entry=15501;
UPDATE creature_template SET gossip_menu_id=6796 WHERE entry=15540;
UPDATE creature_template SET gossip_menu_id=6687 WHERE entry=15612;
UPDATE creature_template SET gossip_menu_id=6926 WHERE entry=15613;
UPDATE creature_template SET gossip_menu_id=21251 WHERE entry=15664;
UPDATE creature_template SET gossip_menu_id=6931 WHERE entry=15694;
UPDATE creature_template SET gossip_menu_id=6933 WHERE entry=15719;
UPDATE creature_template SET gossip_menu_id=6791 WHERE entry=15722;
UPDATE creature_template SET gossip_menu_id=6802 WHERE entry=15732;
UPDATE creature_template SET gossip_menu_id=6813 WHERE entry=15760;
UPDATE creature_template SET gossip_menu_id=6917 WHERE entry=15864;
UPDATE creature_template SET gossip_menu_id=6918 WHERE entry=15895;
UPDATE creature_template SET gossip_menu_id=6923 WHERE entry=15903;
UPDATE creature_template SET gossip_menu_id=6930 WHERE entry=15905;
UPDATE creature_template SET gossip_menu_id=6929 WHERE entry=15906;
UPDATE creature_template SET gossip_menu_id=6934 WHERE entry=15907;
UPDATE creature_template SET gossip_menu_id=6932 WHERE entry=15908;
UPDATE creature_template SET gossip_menu_id=6924 WHERE entry=15909;
UPDATE creature_template SET gossip_menu_id=6937 WHERE entry=15920;
UPDATE creature_template SET gossip_menu_id=6938 WHERE entry=15921;
UPDATE creature_template SET gossip_menu_id=6939 WHERE entry=15924;
UPDATE creature_template SET gossip_menu_id=7140 WHERE entry=15939;
UPDATE creature_template SET gossip_menu_id=7247 WHERE entry=15942;
UPDATE creature_template SET gossip_menu_id=6942 WHERE entry=15951;
UPDATE creature_template SET gossip_menu_id=6943 WHERE entry=15969;
UPDATE creature_template SET gossip_menu_id=7479 WHERE entry=15970;
UPDATE creature_template SET gossip_menu_id=6981 WHERE entry=16002;
UPDATE creature_template SET gossip_menu_id=7070 WHERE entry=16012;
UPDATE creature_template SET gossip_menu_id=7083 WHERE entry=16014;
UPDATE creature_template SET gossip_menu_id=7046 WHERE entry=16015;
UPDATE creature_template SET gossip_menu_id=7091 WHERE entry=16031;
UPDATE creature_template SET gossip_menu_id=7084 WHERE entry=16032;
UPDATE creature_template SET gossip_menu_id=7054 WHERE entry=16075;
UPDATE creature_template SET gossip_menu_id=7045 WHERE entry=16091;
UPDATE creature_template SET gossip_menu_id=7099 WHERE entry=16112;
UPDATE creature_template SET gossip_menu_id=7098 WHERE entry=16113;
UPDATE creature_template SET gossip_menu_id=7100 WHERE entry=16114;
UPDATE creature_template SET gossip_menu_id=7097 WHERE entry=16115;
UPDATE creature_template SET gossip_menu_id=7101 WHERE entry=16131;
UPDATE creature_template SET gossip_menu_id=7102 WHERE entry=16132;
UPDATE creature_template SET gossip_menu_id=7105 WHERE entry=16133;
UPDATE creature_template SET gossip_menu_id=7116 WHERE entry=16144;
UPDATE creature_template SET gossip_menu_id=7117 WHERE entry=16147;
UPDATE creature_template SET gossip_menu_id=7524 WHERE entry=16160;
UPDATE creature_template SET gossip_menu_id=7524 WHERE entry=16161;
UPDATE creature_template SET gossip_menu_id=7143 WHERE entry=16169;
UPDATE creature_template SET gossip_menu_id=7155 WHERE entry=16183;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=16185;
UPDATE creature_template SET gossip_menu_id=7146 WHERE entry=16187;
UPDATE creature_template SET gossip_menu_id=7154 WHERE entry=16196;
UPDATE creature_template SET gossip_menu_id=7153 WHERE entry=16197;
UPDATE creature_template SET gossip_menu_id=7220 WHERE entry=16199;
UPDATE creature_template SET gossip_menu_id=7206 WHERE entry=16201;
UPDATE creature_template SET gossip_menu_id=7205 WHERE entry=16202;
UPDATE creature_template SET gossip_menu_id=7195 WHERE entry=16203;
UPDATE creature_template SET gossip_menu_id=7204 WHERE entry=16205;
UPDATE creature_template SET gossip_menu_id=7156 WHERE entry=16210;
UPDATE creature_template SET gossip_menu_id=7157 WHERE entry=16212;
UPDATE creature_template SET gossip_menu_id=7158 WHERE entry=16213;
UPDATE creature_template SET gossip_menu_id=7289 WHERE entry=16217;
UPDATE creature_template SET gossip_menu_id=7159 WHERE entry=16219;
UPDATE creature_template SET gossip_menu_id=7160 WHERE entry=16220;
UPDATE creature_template SET gossip_menu_id=7162 WHERE entry=16224;
UPDATE creature_template SET gossip_menu_id=7163 WHERE entry=16231;
UPDATE creature_template SET gossip_menu_id=7207 WHERE entry=16251;
UPDATE creature_template SET gossip_menu_id=7172 WHERE entry=16252;
UPDATE creature_template SET gossip_menu_id=7171 WHERE entry=16253;
UPDATE creature_template SET gossip_menu_id=7173 WHERE entry=16256;
UPDATE creature_template SET gossip_menu_id=10181 WHERE entry=16261;
UPDATE creature_template SET gossip_menu_id=7311 WHERE entry=16263;
UPDATE creature_template SET gossip_menu_id=8098 WHERE entry=16264;
UPDATE creature_template SET gossip_menu_id=7436 WHERE entry=16268;
UPDATE creature_template SET gossip_menu_id=14144 WHERE entry=16270;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=16271;
UPDATE creature_template SET gossip_menu_id=6647 WHERE entry=16275;
UPDATE creature_template SET gossip_menu_id=6650 WHERE entry=16279;
UPDATE creature_template SET gossip_menu_id=7174 WHERE entry=16283;
UPDATE creature_template SET gossip_menu_id=7175 WHERE entry=16284;
UPDATE creature_template SET gossip_menu_id=7183 WHERE entry=16288;
UPDATE creature_template SET gossip_menu_id=7188 WHERE entry=16289;
UPDATE creature_template SET gossip_menu_id=7192 WHERE entry=16293;
UPDATE creature_template SET gossip_menu_id=7214 WHERE entry=16362;
UPDATE creature_template SET gossip_menu_id=7215 WHERE entry=16365;
UPDATE creature_template SET gossip_menu_id=7524 WHERE entry=16366;
UPDATE creature_template SET gossip_menu_id=7524 WHERE entry=16367;
UPDATE creature_template SET gossip_menu_id=7219 WHERE entry=16376;
UPDATE creature_template SET gossip_menu_id=7235 WHERE entry=16397;
UPDATE creature_template SET gossip_menu_id=7236 WHERE entry=16399;
UPDATE creature_template SET gossip_menu_id=7239 WHERE entry=16417;
UPDATE creature_template SET gossip_menu_id=7237 WHERE entry=16418;
UPDATE creature_template SET gossip_menu_id=7244 WHERE entry=16443;
UPDATE creature_template SET gossip_menu_id=7245 WHERE entry=16444;
UPDATE creature_template SET gossip_menu_id=1581 WHERE entry=16458;
UPDATE creature_template SET gossip_menu_id=7250 WHERE entry=16462;
UPDATE creature_template SET gossip_menu_id=7253 WHERE entry=16463;
UPDATE creature_template SET gossip_menu_id=7251 WHERE entry=16464;
UPDATE creature_template SET gossip_menu_id=7305 WHERE entry=16477;
UPDATE creature_template SET gossip_menu_id=7259 WHERE entry=16480;
UPDATE creature_template SET gossip_menu_id=7304 WHERE entry=16514;
UPDATE creature_template SET gossip_menu_id=7775 WHERE entry=16519;
UPDATE creature_template SET gossip_menu_id=7287 WHERE entry=16528;
UPDATE creature_template SET gossip_menu_id=7288 WHERE entry=16542;
UPDATE creature_template SET gossip_menu_id=7418 WHERE entry=16543;
UPDATE creature_template SET gossip_menu_id=7303 WHERE entry=16554;
UPDATE creature_template SET gossip_menu_id=7334 WHERE entry=16574;
UPDATE creature_template SET gossip_menu_id=7335 WHERE entry=16576;
UPDATE creature_template SET gossip_menu_id=8760 WHERE entry=16583;
UPDATE creature_template SET gossip_menu_id=7333 WHERE entry=16584;
UPDATE creature_template SET gossip_menu_id=7810 WHERE entry=16588;
UPDATE creature_template SET gossip_menu_id=7291 WHERE entry=16603;
UPDATE creature_template SET gossip_menu_id=7811 WHERE entry=16615;
UPDATE creature_template SET gossip_menu_id=7811 WHERE entry=16616;
UPDATE creature_template SET gossip_menu_id=8612 WHERE entry=16621;
UPDATE creature_template SET gossip_menu_id=8733 WHERE entry=16642;
UPDATE creature_template SET gossip_menu_id=7566 WHERE entry=16646;
UPDATE creature_template SET gossip_menu_id=7437 WHERE entry=16647;
UPDATE creature_template SET gossip_menu_id=7566 WHERE entry=16648;
UPDATE creature_template SET gossip_menu_id=7451 WHERE entry=16665;
UPDATE creature_template SET gossip_menu_id=6652 WHERE entry=16672;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=16675;
UPDATE creature_template SET gossip_menu_id=5854 WHERE entry=16676;
UPDATE creature_template SET gossip_menu_id=6647 WHERE entry=16681;
UPDATE creature_template SET gossip_menu_id=8732 WHERE entry=16688;
UPDATE creature_template SET gossip_menu_id=8255 WHERE entry=16694;
UPDATE creature_template SET gossip_menu_id=8250 WHERE entry=16695;
UPDATE creature_template SET gossip_menu_id=8256 WHERE entry=16696;
UPDATE creature_template SET gossip_menu_id=8863 WHERE entry=16723;
UPDATE creature_template SET gossip_menu_id=7265 WHERE entry=16756;
UPDATE creature_template SET gossip_menu_id=7302 WHERE entry=16789;
UPDATE creature_template SET gossip_menu_id=7308 WHERE entry=16790;
UPDATE creature_template SET gossip_menu_id=7310 WHERE entry=16791;
UPDATE creature_template SET gossip_menu_id=7312 WHERE entry=16792;
UPDATE creature_template SET gossip_menu_id=7314 WHERE entry=16793;
UPDATE creature_template SET gossip_menu_id=7317 WHERE entry=16794;
UPDATE creature_template SET gossip_menu_id=7396 WHERE entry=16798;
UPDATE creature_template SET gossip_menu_id=8174 WHERE entry=16811;
UPDATE creature_template SET gossip_menu_id=8178 WHERE entry=16813;
UPDATE creature_template SET gossip_menu_id=8177 WHERE entry=16815;
UPDATE creature_template SET gossip_menu_id=8002 WHERE entry=16829;
UPDATE creature_template SET gossip_menu_id=7351 WHERE entry=16830;
UPDATE creature_template SET gossip_menu_id=7328 WHERE entry=16832;
UPDATE creature_template SET gossip_menu_id=7392 WHERE entry=16833;
UPDATE creature_template SET gossip_menu_id=7390 WHERE entry=16834;
UPDATE creature_template SET gossip_menu_id=7375 WHERE entry=16845;
UPDATE creature_template SET gossip_menu_id=7373 WHERE entry=16848;
UPDATE creature_template SET gossip_menu_id=7309 WHERE entry=16856;
UPDATE creature_template SET gossip_menu_id=7348 WHERE entry=16858;
UPDATE creature_template SET gossip_menu_id=7313 WHERE entry=16860;
UPDATE creature_template SET gossip_menu_id=7316 WHERE entry=16862;
UPDATE creature_template SET gossip_menu_id=7320 WHERE entry=16886;
UPDATE creature_template SET gossip_menu_id=7878 WHERE entry=16915;
UPDATE creature_template SET gossip_menu_id=7323 WHERE entry=16924;
UPDATE creature_template SET gossip_menu_id=8686 WHERE entry=17002;
UPDATE creature_template SET gossip_menu_id=7337 WHERE entry=17005;
UPDATE creature_template SET gossip_menu_id=7342 WHERE entry=17015;
UPDATE creature_template SET gossip_menu_id=7345 WHERE entry=17046;
UPDATE creature_template SET gossip_menu_id=7346 WHERE entry=17056;
UPDATE creature_template SET gossip_menu_id=7355 WHERE entry=17073;
UPDATE creature_template SET gossip_menu_id=7775 WHERE entry=17088;
UPDATE creature_template SET gossip_menu_id=7359 WHERE entry=17098;
UPDATE creature_template SET gossip_menu_id=7362 WHERE entry=17100;
UPDATE creature_template SET gossip_menu_id=7363 WHERE entry=17103;
UPDATE creature_template SET gossip_menu_id=7366 WHERE entry=17105;
UPDATE creature_template SET gossip_menu_id=7367 WHERE entry=17106;
UPDATE creature_template SET gossip_menu_id=7369 WHERE entry=17109;
UPDATE creature_template SET gossip_menu_id=7372 WHERE entry=17123;
UPDATE creature_template SET gossip_menu_id=7379 WHERE entry=17209;
UPDATE creature_template SET gossip_menu_id=12091 WHERE entry=17223;
UPDATE creature_template SET gossip_menu_id=7387 WHERE entry=17226;
UPDATE creature_template SET gossip_menu_id=7417 WHERE entry=17275;
UPDATE creature_template SET gossip_menu_id=7880 WHERE entry=17277;
UPDATE creature_template SET gossip_menu_id=7405 WHERE entry=17287;
UPDATE creature_template SET gossip_menu_id=7404 WHERE entry=17291;
UPDATE creature_template SET gossip_menu_id=7407 WHERE entry=17303;
UPDATE creature_template SET gossip_menu_id=7403 WHERE entry=17311;
UPDATE creature_template SET gossip_menu_id=7408 WHERE entry=17355;
UPDATE creature_template SET gossip_menu_id=7382 WHERE entry=17406;
UPDATE creature_template SET gossip_menu_id=7410 WHERE entry=17412;
UPDATE creature_template SET gossip_menu_id=7458 WHERE entry=17423;
UPDATE creature_template SET gossip_menu_id=7416 WHERE entry=17431;
UPDATE creature_template SET gossip_menu_id=7415 WHERE entry=17435;
UPDATE creature_template SET gossip_menu_id=7432 WHERE entry=17443;
UPDATE creature_template SET gossip_menu_id=7433 WHERE entry=17445;
UPDATE creature_template SET gossip_menu_id=7431 WHERE entry=17446;
UPDATE creature_template SET gossip_menu_id=7428 WHERE entry=17490;
UPDATE creature_template SET gossip_menu_id=7420 WHERE entry=17493;
UPDATE creature_template SET gossip_menu_id=7265 WHERE entry=17510;
UPDATE creature_template SET gossip_menu_id=7470 WHERE entry=17554;
UPDATE creature_template SET gossip_menu_id=7825 WHERE entry=17558;
UPDATE creature_template SET gossip_menu_id=7450 WHERE entry=17585;
UPDATE creature_template SET gossip_menu_id=7812 WHERE entry=17631;
UPDATE creature_template SET gossip_menu_id=7812 WHERE entry=17632;
UPDATE creature_template SET gossip_menu_id=7460 WHERE entry=17642;
UPDATE creature_template SET gossip_menu_id=7446 WHERE entry=17655;
UPDATE creature_template SET gossip_menu_id=7447 WHERE entry=17656;
UPDATE creature_template SET gossip_menu_id=7449 WHERE entry=17658;
UPDATE creature_template SET gossip_menu_id=7452 WHERE entry=17663;
UPDATE creature_template SET gossip_menu_id=7478 WHERE entry=17674;
UPDATE creature_template SET gossip_menu_id=7465 WHERE entry=17684;
UPDATE creature_template SET gossip_menu_id=7466 WHERE entry=17686;
UPDATE creature_template SET gossip_menu_id=7558 WHERE entry=17717;
UPDATE creature_template SET gossip_menu_id=9142 WHERE entry=17718;
UPDATE creature_template SET gossip_menu_id=1288 WHERE entry=17764;
UPDATE creature_template SET gossip_menu_id=7482 WHERE entry=17822;
UPDATE creature_template SET gossip_menu_id=7486 WHERE entry=17832;
UPDATE creature_template SET gossip_menu_id=7489 WHERE entry=17843;
UPDATE creature_template SET gossip_menu_id=7517 WHERE entry=17844;
UPDATE creature_template SET gossip_menu_id=7510 WHERE entry=17856;
UPDATE creature_template SET gossip_menu_id=7514 WHERE entry=17857;
UPDATE creature_template SET gossip_menu_id=7511 WHERE entry=17866;
UPDATE creature_template SET gossip_menu_id=7516 WHERE entry=17877;
UPDATE creature_template SET gossip_menu_id=7521 WHERE entry=17885;
UPDATE creature_template SET gossip_menu_id=7519 WHERE entry=17890;
UPDATE creature_template SET gossip_menu_id=7573 WHERE entry=17924;
UPDATE creature_template SET gossip_menu_id=7572 WHERE entry=17925;
UPDATE creature_template SET gossip_menu_id=7523 WHERE entry=17926;
UPDATE creature_template SET gossip_menu_id=7538 WHERE entry=17982;
UPDATE creature_template SET gossip_menu_id=7539 WHERE entry=17986;
UPDATE creature_template SET gossip_menu_id=7614 WHERE entry=18003;
UPDATE creature_template SET gossip_menu_id=7610 WHERE entry=18004;
UPDATE creature_template SET gossip_menu_id=7612 WHERE entry=18005;
UPDATE creature_template SET gossip_menu_id=7611 WHERE entry=18006;
UPDATE creature_template SET gossip_menu_id=7587 WHERE entry=18008;
UPDATE creature_template SET gossip_menu_id=7589 WHERE entry=18009;
UPDATE creature_template SET gossip_menu_id=7588 WHERE entry=18010;
UPDATE creature_template SET gossip_menu_id=7615 WHERE entry=18011;
UPDATE creature_template SET gossip_menu_id=7616 WHERE entry=18012;
UPDATE creature_template SET gossip_menu_id=7601 WHERE entry=18013;
UPDATE creature_template SET gossip_menu_id=7602 WHERE entry=18014;
UPDATE creature_template SET gossip_menu_id=7608 WHERE entry=18015;
UPDATE creature_template SET gossip_menu_id=7617 WHERE entry=18016;
UPDATE creature_template SET gossip_menu_id=7603 WHERE entry=18017;
UPDATE creature_template SET gossip_menu_id=7609 WHERE entry=18018;
UPDATE creature_template SET gossip_menu_id=7590 WHERE entry=18019;
UPDATE creature_template SET gossip_menu_id=7563 WHERE entry=18074;
UPDATE creature_template SET gossip_menu_id=7582 WHERE entry=18197;
UPDATE creature_template SET gossip_menu_id=7592 WHERE entry=18200;
UPDATE creature_template SET gossip_menu_id=7607 WHERE entry=18218;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=18244;
UPDATE creature_template SET gossip_menu_id=7856 WHERE entry=18245;
UPDATE creature_template SET gossip_menu_id=8441 WHERE entry=18253;
UPDATE creature_template SET gossip_menu_id=7675 WHERE entry=18261;
UPDATE creature_template SET gossip_menu_id=7625 WHERE entry=18265;
UPDATE creature_template SET gossip_menu_id=7893 WHERE entry=18267;
UPDATE creature_template SET gossip_menu_id=7626 WHERE entry=18276;
UPDATE creature_template SET gossip_menu_id=7723 WHERE entry=18333;
UPDATE creature_template SET gossip_menu_id=7631 WHERE entry=18335;
UPDATE creature_template SET gossip_menu_id=21290 WHERE entry=18351;
UPDATE creature_template SET gossip_menu_id=7674 WHERE entry=18369;
UPDATE creature_template SET gossip_menu_id=7739 WHERE entry=18383;
UPDATE creature_template SET gossip_menu_id=7750 WHERE entry=18384;
UPDATE creature_template SET gossip_menu_id=9096 WHERE entry=18408;
UPDATE creature_template SET gossip_menu_id=7719 WHERE entry=18417;
UPDATE creature_template SET gossip_menu_id=7692 WHERE entry=18424;
UPDATE creature_template SET gossip_menu_id=7872 WHERE entry=18439;
UPDATE creature_template SET gossip_menu_id=7697 WHERE entry=18447;
UPDATE creature_template SET gossip_menu_id=7699 WHERE entry=18471;
UPDATE creature_template SET gossip_menu_id=7703 WHERE entry=18480;
UPDATE creature_template SET gossip_menu_id=7704 WHERE entry=18482;
UPDATE creature_template SET gossip_menu_id=7712 WHERE entry=18542;
UPDATE creature_template SET gossip_menu_id=7722 WHERE entry=18564;
UPDATE creature_template SET gossip_menu_id=7751 WHERE entry=18565;
UPDATE creature_template SET gossip_menu_id=7754 WHERE entry=18566;
UPDATE creature_template SET gossip_menu_id=7724 WHERE entry=18581;
UPDATE creature_template SET gossip_menu_id=7730 WHERE entry=18586;
UPDATE creature_template SET gossip_menu_id=7732 WHERE entry=18588;
UPDATE creature_template SET gossip_menu_id=7734 WHERE entry=18596;
UPDATE creature_template SET gossip_menu_id=7747 WHERE entry=18653;
UPDATE creature_template SET gossip_menu_id=7746 WHERE entry=18705;
UPDATE creature_template SET gossip_menu_id=7774 WHERE entry=18712;
UPDATE creature_template SET gossip_menu_id=7772 WHERE entry=18714;
UPDATE creature_template SET gossip_menu_id=21253 WHERE entry=18715;
UPDATE creature_template SET gossip_menu_id=7759 WHERE entry=18716;
UPDATE creature_template SET gossip_menu_id=7757 WHERE entry=18717;
UPDATE creature_template SET gossip_menu_id=7760 WHERE entry=18719;
UPDATE creature_template SET gossip_menu_id=7776 WHERE entry=18720;
UPDATE creature_template SET gossip_menu_id=7691 WHERE entry=18748;
UPDATE creature_template SET gossip_menu_id=7821 WHERE entry=18760;
UPDATE creature_template SET gossip_menu_id=7832 WHERE entry=18803;
UPDATE creature_template SET gossip_menu_id=7838 WHERE entry=18816;
UPDATE creature_template SET gossip_menu_id=7839 WHERE entry=18817;
UPDATE creature_template SET gossip_menu_id=7841 WHERE entry=18822;
UPDATE creature_template SET gossip_menu_id=7852 WHERE entry=18887;
UPDATE creature_template SET gossip_menu_id=8494 WHERE entry=18897;
UPDATE creature_template SET gossip_menu_id=7288 WHERE entry=18905;
UPDATE creature_template SET gossip_menu_id=7855 WHERE entry=18907;
UPDATE creature_template SET gossip_menu_id=7481 WHERE entry=18908;
UPDATE creature_template SET gossip_menu_id=7857 WHERE entry=18913;
UPDATE creature_template SET gossip_menu_id=7481 WHERE entry=18914;
UPDATE creature_template SET gossip_menu_id=7938 WHERE entry=18930;
UPDATE creature_template SET gossip_menu_id=7939 WHERE entry=18931;
UPDATE creature_template SET gossip_menu_id=7864 WHERE entry=18947;
UPDATE creature_template SET gossip_menu_id=7859 WHERE entry=18985;
UPDATE creature_template SET gossip_menu_id=7881 WHERE entry=18997;
UPDATE creature_template SET gossip_menu_id=7882 WHERE entry=18998;
UPDATE creature_template SET gossip_menu_id=7883 WHERE entry=19001;
UPDATE creature_template SET gossip_menu_id=7886 WHERE entry=19012;
UPDATE creature_template SET gossip_menu_id=7887 WHERE entry=19014;
UPDATE creature_template SET gossip_menu_id=7888 WHERE entry=19017;
UPDATE creature_template SET gossip_menu_id=7889 WHERE entry=19019;
UPDATE creature_template SET gossip_menu_id=7890 WHERE entry=19021;
UPDATE creature_template SET gossip_menu_id=7936 WHERE entry=19133;
UPDATE creature_template SET gossip_menu_id=7941 WHERE entry=19141;
UPDATE creature_template SET gossip_menu_id=8988 WHERE entry=19148;
UPDATE creature_template SET gossip_menu_id=7944 WHERE entry=19158;
UPDATE creature_template SET gossip_menu_id=8988 WHERE entry=19172;
UPDATE creature_template SET gossip_menu_id=7925 WHERE entry=19175;
UPDATE creature_template SET gossip_menu_id=7935 WHERE entry=19177;
UPDATE creature_template SET gossip_menu_id=8988 WHERE entry=19178;
UPDATE creature_template SET gossip_menu_id=8522 WHERE entry=19184;
UPDATE creature_template SET gossip_menu_id=8460 WHERE entry=19185;
UPDATE creature_template SET gossip_menu_id=7981 WHERE entry=19217;
UPDATE creature_template SET gossip_menu_id=8086 WHERE entry=19253;
UPDATE creature_template SET gossip_menu_id=8069 WHERE entry=19254;
UPDATE creature_template SET gossip_menu_id=8087 WHERE entry=19255;
UPDATE creature_template SET gossip_menu_id=8091 WHERE entry=19256;
UPDATE creature_template SET gossip_menu_id=7955 WHERE entry=19273;
UPDATE creature_template SET gossip_menu_id=7957 WHERE entry=19315;
UPDATE creature_template SET gossip_menu_id=7958 WHERE entry=19332;
UPDATE creature_template SET gossip_menu_id=8386 WHERE entry=19333;
UPDATE creature_template SET gossip_menu_id=7809 WHERE entry=19341;
UPDATE creature_template SET gossip_menu_id=7960 WHERE entry=19344;
UPDATE creature_template SET gossip_menu_id=7965 WHERE entry=19367;
UPDATE creature_template SET gossip_menu_id=7967 WHERE entry=19401;
UPDATE creature_template SET gossip_menu_id=8074 WHERE entry=19466;
UPDATE creature_template SET gossip_menu_id=8112 WHERE entry=19467;
UPDATE creature_template SET gossip_menu_id=8006 WHERE entry=19468;
UPDATE creature_template SET gossip_menu_id=9856 WHERE entry=19471;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=19476;
UPDATE creature_template SET gossip_menu_id=5856 WHERE entry=19478;
UPDATE creature_template SET gossip_menu_id=7996 WHERE entry=19488;
UPDATE creature_template SET gossip_menu_id=7995 WHERE entry=19489;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=19558;
UPDATE creature_template SET gossip_menu_id=7991 WHERE entry=19569;
UPDATE creature_template SET gossip_menu_id=7994 WHERE entry=19578;
UPDATE creature_template SET gossip_menu_id=8001 WHERE entry=19617;
UPDATE creature_template SET gossip_menu_id=8003 WHERE entry=19634;
UPDATE creature_template SET gossip_menu_id=8024 WHERE entry=19644;
UPDATE creature_template SET gossip_menu_id=8008 WHERE entry=19645;
UPDATE creature_template SET gossip_menu_id=8020 WHERE entry=19669;
UPDATE creature_template SET gossip_menu_id=8021 WHERE entry=19679;
UPDATE creature_template SET gossip_menu_id=8027 WHERE entry=19690;
UPDATE creature_template SET gossip_menu_id=8030 WHERE entry=19709;
UPDATE creature_template SET gossip_menu_id=8032 WHERE entry=19728;
UPDATE creature_template SET gossip_menu_id=8035 WHERE entry=19772;
UPDATE creature_template SET gossip_menu_id=8034 WHERE entry=19773;
UPDATE creature_template SET gossip_menu_id=8380 WHERE entry=19775;
UPDATE creature_template SET gossip_menu_id=8040 WHERE entry=19830;
UPDATE creature_template SET gossip_menu_id=8041 WHERE entry=19831;
UPDATE creature_template SET gossip_menu_id=8037 WHERE entry=19832;
UPDATE creature_template SET gossip_menu_id=8038 WHERE entry=19840;
UPDATE creature_template SET gossip_menu_id=8048 WHERE entry=19880;
UPDATE creature_template SET gossip_menu_id=8075 WHERE entry=19905;
UPDATE creature_template SET gossip_menu_id=8078 WHERE entry=19907;
UPDATE creature_template SET gossip_menu_id=8077 WHERE entry=19908;
UPDATE creature_template SET gossip_menu_id=8076 WHERE entry=19910;
UPDATE creature_template SET gossip_menu_id=8234 WHERE entry=19935;
UPDATE creature_template SET gossip_menu_id=8054 WHERE entry=20066;
UPDATE creature_template SET gossip_menu_id=8055 WHERE entry=20067;
UPDATE creature_template SET gossip_menu_id=8056 WHERE entry=20068;
UPDATE creature_template SET gossip_menu_id=8071 WHERE entry=20071;
UPDATE creature_template SET gossip_menu_id=8057 WHERE entry=20080;
UPDATE creature_template SET gossip_menu_id=8058 WHERE entry=20081;
UPDATE creature_template SET gossip_menu_id=8059 WHERE entry=20082;
UPDATE creature_template SET gossip_menu_id=8083 WHERE entry=20084;
UPDATE creature_template SET gossip_menu_id=8063 WHERE entry=20092;
UPDATE creature_template SET gossip_menu_id=8068 WHERE entry=20110;
UPDATE creature_template SET gossip_menu_id=8070 WHERE entry=20112;
UPDATE creature_template SET gossip_menu_id=8258 WHERE entry=20118;
UPDATE creature_template SET gossip_menu_id=8253 WHERE entry=20119;
UPDATE creature_template SET gossip_menu_id=8257 WHERE entry=20120;
UPDATE creature_template SET gossip_menu_id=9131 WHERE entry=20124;
UPDATE creature_template SET gossip_menu_id=9132 WHERE entry=20125;
UPDATE creature_template SET gossip_menu_id=13039 WHERE entry=20130;
UPDATE creature_template SET gossip_menu_id=8081 WHERE entry=20159;
UPDATE creature_template SET gossip_menu_id=8082 WHERE entry=20162;
UPDATE creature_template SET gossip_menu_id=8084 WHERE entry=20194;
UPDATE creature_template SET gossip_menu_id=8093 WHERE entry=20227;
UPDATE creature_template SET gossip_menu_id=8097 WHERE entry=20233;
UPDATE creature_template SET gossip_menu_id=8100 WHERE entry=20236;
UPDATE creature_template SET gossip_menu_id=8261 WHERE entry=20269;
UPDATE creature_template SET gossip_menu_id=8263 WHERE entry=20271;
UPDATE creature_template SET gossip_menu_id=8264 WHERE entry=20272;
UPDATE creature_template SET gossip_menu_id=8265 WHERE entry=20273;
UPDATE creature_template SET gossip_menu_id=8262 WHERE entry=20274;
UPDATE creature_template SET gossip_menu_id=8260 WHERE entry=20276;
UPDATE creature_template SET gossip_menu_id=8124 WHERE entry=20278;
UPDATE creature_template SET gossip_menu_id=8101 WHERE entry=20281;
UPDATE creature_template SET gossip_menu_id=8266 WHERE entry=20339;
UPDATE creature_template SET gossip_menu_id=8106 WHERE entry=20389;
UPDATE creature_template SET gossip_menu_id=8107 WHERE entry=20393;
UPDATE creature_template SET gossip_menu_id=8267 WHERE entry=20395;
UPDATE creature_template SET gossip_menu_id=8046 WHERE entry=20397;
UPDATE creature_template SET gossip_menu_id=8110 WHERE entry=20407;
UPDATE creature_template SET gossip_menu_id=8120 WHERE entry=20448;
UPDATE creature_template SET gossip_menu_id=8180 WHERE entry=20449;
UPDATE creature_template SET gossip_menu_id=8183 WHERE entry=20450;
UPDATE creature_template SET gossip_menu_id=8126 WHERE entry=20463;
UPDATE creature_template SET gossip_menu_id=8118 WHERE entry=20470;
UPDATE creature_template SET gossip_menu_id=8119 WHERE entry=20471;
UPDATE creature_template SET gossip_menu_id=8127 WHERE entry=20518;
UPDATE creature_template SET gossip_menu_id=7499 WHERE entry=20548;
UPDATE creature_template SET gossip_menu_id=8128 WHERE entry=20551;
UPDATE creature_template SET gossip_menu_id=8336 WHERE entry=20563;
UPDATE creature_template SET gossip_menu_id=8214 WHERE entry=20780;
UPDATE creature_template SET gossip_menu_id=8231 WHERE entry=20810;
UPDATE creature_template SET gossip_menu_id=7674 WHERE entry=20812;
UPDATE creature_template SET gossip_menu_id=8229 WHERE entry=20903;
UPDATE creature_template SET gossip_menu_id=8207 WHERE entry=20907;
UPDATE creature_template SET gossip_menu_id=8216 WHERE entry=20920;
UPDATE creature_template SET gossip_menu_id=8310 WHERE entry=20977;
UPDATE creature_template SET gossip_menu_id=8228 WHERE entry=20985;
UPDATE creature_template SET gossip_menu_id=8232 WHERE entry=21006;
UPDATE creature_template SET gossip_menu_id=8233 WHERE entry=21007;
UPDATE creature_template SET gossip_menu_id=8238 WHERE entry=21024;
UPDATE creature_template SET gossip_menu_id=9114 WHERE entry=21088;
UPDATE creature_template SET gossip_menu_id=8375 WHERE entry=21110;
UPDATE creature_template SET gossip_menu_id=8239 WHERE entry=21117;
UPDATE creature_template SET gossip_menu_id=8388 WHERE entry=21118;
UPDATE creature_template SET gossip_menu_id=8243 WHERE entry=21145;
UPDATE creature_template SET gossip_menu_id=8244 WHERE entry=21147;
UPDATE creature_template SET gossip_menu_id=8249 WHERE entry=21172;
UPDATE creature_template SET gossip_menu_id=8269 WHERE entry=21257;
UPDATE creature_template SET gossip_menu_id=8271 WHERE entry=21277;
UPDATE creature_template SET gossip_menu_id=8272 WHERE entry=21279;
UPDATE creature_template SET gossip_menu_id=8274 WHERE entry=21283;
UPDATE creature_template SET gossip_menu_id=8283 WHERE entry=21311;
UPDATE creature_template SET gossip_menu_id=8446 WHERE entry=21382;
UPDATE creature_template SET gossip_menu_id=8446 WHERE entry=21383;
UPDATE creature_template SET gossip_menu_id=8303 WHERE entry=21460;
UPDATE creature_template SET gossip_menu_id=8400 WHERE entry=21465;
UPDATE creature_template SET gossip_menu_id=8308 WHERE entry=21493;
UPDATE creature_template SET gossip_menu_id=8446 WHERE entry=21637;
UPDATE creature_template SET gossip_menu_id=8346 WHERE entry=21664;
UPDATE creature_template SET gossip_menu_id=8350 WHERE entry=21685;
UPDATE creature_template SET gossip_menu_id=8351 WHERE entry=21690;
UPDATE creature_template SET gossip_menu_id=8352 WHERE entry=21691;
UPDATE creature_template SET gossip_menu_id=8371 WHERE entry=21725;
UPDATE creature_template SET gossip_menu_id=8355 WHERE entry=21726;
UPDATE creature_template SET gossip_menu_id=8356 WHERE entry=21727;
UPDATE creature_template SET gossip_menu_id=7949 WHERE entry=21744;
UPDATE creature_template SET gossip_menu_id=8362 WHERE entry=21747;
UPDATE creature_template SET gossip_menu_id=8368 WHERE entry=21752;
UPDATE creature_template SET gossip_menu_id=8370 WHERE entry=21755;
UPDATE creature_template SET gossip_menu_id=8443 WHERE entry=21769;
UPDATE creature_template SET gossip_menu_id=8385 WHERE entry=21824;
UPDATE creature_template SET gossip_menu_id=8406 WHERE entry=21950;
UPDATE creature_template SET gossip_menu_id=8429 WHERE entry=21981;
UPDATE creature_template SET gossip_menu_id=8432 WHERE entry=21983;
UPDATE creature_template SET gossip_menu_id=8525 WHERE entry=21984;
UPDATE creature_template SET gossip_menu_id=8511 WHERE entry=22004;
UPDATE creature_template SET gossip_menu_id=8431 WHERE entry=22007;
UPDATE creature_template SET gossip_menu_id=8436 WHERE entry=22019;
UPDATE creature_template SET gossip_menu_id=8447 WHERE entry=22020;
UPDATE creature_template SET gossip_menu_id=8449 WHERE entry=22024;
UPDATE creature_template SET gossip_menu_id=8508 WHERE entry=22053;
UPDATE creature_template SET gossip_menu_id=8490 WHERE entry=22099;
UPDATE creature_template SET gossip_menu_id=8491 WHERE entry=22103;
UPDATE creature_template SET gossip_menu_id=8495 WHERE entry=22107;
UPDATE creature_template SET gossip_menu_id=8493 WHERE entry=22113;
UPDATE creature_template SET gossip_menu_id=8496 WHERE entry=22149;
UPDATE creature_template SET gossip_menu_id=8500 WHERE entry=22211;
UPDATE creature_template SET gossip_menu_id=8506 WHERE entry=22215;
UPDATE creature_template SET gossip_menu_id=8505 WHERE entry=22231;
UPDATE creature_template SET gossip_menu_id=8524 WHERE entry=22258;
UPDATE creature_template SET gossip_menu_id=8723 WHERE entry=22264;
UPDATE creature_template SET gossip_menu_id=8717 WHERE entry=22266;
UPDATE creature_template SET gossip_menu_id=8716 WHERE entry=22270;
UPDATE creature_template SET gossip_menu_id=8722 WHERE entry=22271;
UPDATE creature_template SET gossip_menu_id=8513 WHERE entry=22312;
UPDATE creature_template SET gossip_menu_id=8559 WHERE entry=22364;
UPDATE creature_template SET gossip_menu_id=8529 WHERE entry=22386;
UPDATE creature_template SET gossip_menu_id=8536 WHERE entry=22423;
UPDATE creature_template SET gossip_menu_id=8542 WHERE entry=22427;
UPDATE creature_template SET gossip_menu_id=8554 WHERE entry=22432;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=22468;
UPDATE creature_template SET gossip_menu_id=5124 WHERE entry=22571;
UPDATE creature_template SET gossip_menu_id=5442 WHERE entry=22628;
UPDATE creature_template SET gossip_menu_id=6484 WHERE entry=22647;
UPDATE creature_template SET gossip_menu_id=6500 WHERE entry=22656;
UPDATE creature_template SET gossip_menu_id=5241 WHERE entry=22658;
UPDATE creature_template SET gossip_menu_id=6261 WHERE entry=22736;
UPDATE creature_template SET gossip_menu_id=6262 WHERE entry=22759;
UPDATE creature_template SET gossip_menu_id=8563 WHERE entry=22817;
UPDATE creature_template SET gossip_menu_id=8562 WHERE entry=22823;
UPDATE creature_template SET gossip_menu_id=8576 WHERE entry=22899;
UPDATE creature_template SET gossip_menu_id=8615 WHERE entry=22924;
UPDATE creature_template SET gossip_menu_id=8620 WHERE entry=22941;
UPDATE creature_template SET gossip_menu_id=8657 WHERE entry=22995;
UPDATE creature_template SET gossip_menu_id=8753 WHERE entry=23038;
UPDATE creature_template SET gossip_menu_id=8630 WHERE entry=23048;
UPDATE creature_template SET gossip_menu_id=8631 WHERE entry=23050;
UPDATE creature_template SET gossip_menu_id=8640 WHERE entry=23052;
UPDATE creature_template SET gossip_menu_id=8640 WHERE entry=23053;
UPDATE creature_template SET gossip_menu_id=8725 WHERE entry=23093;
UPDATE creature_template SET gossip_menu_id=8721 WHERE entry=23110;
UPDATE creature_template SET gossip_menu_id=8724 WHERE entry=23112;
UPDATE creature_template SET gossip_menu_id=8642 WHERE entry=23120;
UPDATE creature_template SET gossip_menu_id=8737 WHERE entry=23208;
UPDATE creature_template SET gossip_menu_id=8681 WHERE entry=23233;
UPDATE creature_template SET gossip_menu_id=8679 WHERE entry=23253;
UPDATE creature_template SET gossip_menu_id=8663 WHERE entry=23268;
UPDATE creature_template SET gossip_menu_id=8680 WHERE entry=23300;
UPDATE creature_template SET gossip_menu_id=8667 WHERE entry=23306;
UPDATE creature_template SET gossip_menu_id=8701 WHERE entry=23309;
UPDATE creature_template SET gossip_menu_id=8678 WHERE entry=23316;
UPDATE creature_template SET gossip_menu_id=8669 WHERE entry=23334;
UPDATE creature_template SET gossip_menu_id=8670 WHERE entry=23335;
UPDATE creature_template SET gossip_menu_id=8683 WHERE entry=23363;
UPDATE creature_template SET gossip_menu_id=8710 WHERE entry=23396;
UPDATE creature_template SET gossip_menu_id=8718 WHERE entry=23413;
UPDATE creature_template SET gossip_menu_id=8719 WHERE entry=23415;
UPDATE creature_template SET gossip_menu_id=8726 WHERE entry=23428;
UPDATE creature_template SET gossip_menu_id=8741 WHERE entry=23461;
UPDATE creature_template SET gossip_menu_id=8738 WHERE entry=23462;
UPDATE creature_template SET gossip_menu_id=8743 WHERE entry=23465;
UPDATE creature_template SET gossip_menu_id=8736 WHERE entry=23473;
UPDATE creature_template SET gossip_menu_id=9006 WHERE entry=23486;
UPDATE creature_template SET gossip_menu_id=8972 WHERE entry=23533;
UPDATE creature_template SET gossip_menu_id=8775 WHERE entry=23559;
UPDATE creature_template SET gossip_menu_id=12517 WHERE entry=23566;
UPDATE creature_template SET gossip_menu_id=8761 WHERE entry=23567;
UPDATE creature_template SET gossip_menu_id=8788 WHERE entry=23568;
UPDATE creature_template SET gossip_menu_id=8837 WHERE entry=23569;
UPDATE creature_template SET gossip_menu_id=8801 WHERE entry=23579;
UPDATE creature_template SET gossip_menu_id=8811 WHERE entry=23600;
UPDATE creature_template SET gossip_menu_id=8812 WHERE entry=23601;
UPDATE creature_template SET gossip_menu_id=8762 WHERE entry=23602;
UPDATE creature_template SET gossip_menu_id=8782 WHERE entry=23704;
UPDATE creature_template SET gossip_menu_id=8786 WHERE entry=23713;
UPDATE creature_template SET gossip_menu_id=8789 WHERE entry=23718;
UPDATE creature_template SET gossip_menu_id=8787 WHERE entry=23723;
UPDATE creature_template SET gossip_menu_id=8806 WHERE entry=23731;
UPDATE creature_template SET gossip_menu_id=8805 WHERE entry=23733;
UPDATE creature_template SET gossip_menu_id=8852 WHERE entry=23749;
UPDATE creature_template SET gossip_menu_id=8799 WHERE entry=23790;
UPDATE creature_template SET gossip_menu_id=8830 WHERE entry=23797;
UPDATE creature_template SET gossip_menu_id=8831 WHERE entry=23835;
UPDATE creature_template SET gossip_menu_id=11387 WHERE entry=23872;
UPDATE creature_template SET gossip_menu_id=8853 WHERE entry=23888;
UPDATE creature_template SET gossip_menu_id=8826 WHERE entry=23896;
UPDATE creature_template SET gossip_menu_id=8835 WHERE entry=23949;
UPDATE creature_template SET gossip_menu_id=8836 WHERE entry=23950;
UPDATE creature_template SET gossip_menu_id=8834 WHERE entry=23951;
UPDATE creature_template SET gossip_menu_id=8874 WHERE entry=23999;
UPDATE creature_template SET gossip_menu_id=8927 WHERE entry=24001;
UPDATE creature_template SET gossip_menu_id=8881 WHERE entry=24024;
UPDATE creature_template SET gossip_menu_id=8885 WHERE entry=24038;
UPDATE creature_template SET gossip_menu_id=8886 WHERE entry=24060;
UPDATE creature_template SET gossip_menu_id=8895 WHERE entry=24111;
UPDATE creature_template SET gossip_menu_id=8899 WHERE entry=24130;
UPDATE creature_template SET gossip_menu_id=348 WHERE entry=24149;
UPDATE creature_template SET gossip_menu_id=8912 WHERE entry=24208;
UPDATE creature_template SET gossip_menu_id=8968 WHERE entry=24495;
UPDATE creature_template SET gossip_menu_id=8976 WHERE entry=24497;
UPDATE creature_template SET gossip_menu_id=8971 WHERE entry=24501;
UPDATE creature_template SET gossip_menu_id=8763 WHERE entry=24519;
UPDATE creature_template SET gossip_menu_id=9016 WHERE entry=24657;
UPDATE creature_template SET gossip_menu_id=8999 WHERE entry=24711;
UPDATE creature_template SET gossip_menu_id=9004 WHERE entry=24727;
UPDATE creature_template SET gossip_menu_id=9038 WHERE entry=24833;
UPDATE creature_template SET gossip_menu_id=9036 WHERE entry=24835;
UPDATE creature_template SET gossip_menu_id=9029 WHERE entry=24836;
UPDATE creature_template SET gossip_menu_id=9031 WHERE entry=24837;
UPDATE creature_template SET gossip_menu_id=9033 WHERE entry=24838;
UPDATE creature_template SET gossip_menu_id=9034 WHERE entry=24839;
UPDATE creature_template SET gossip_menu_id=9032 WHERE entry=24840;
UPDATE creature_template SET gossip_menu_id=9037 WHERE entry=24841;
UPDATE creature_template SET gossip_menu_id=9037 WHERE entry=24842;
UPDATE creature_template SET gossip_menu_id=9035 WHERE entry=24881;
UPDATE creature_template SET gossip_menu_id=9051 WHERE entry=24937;
UPDATE creature_template SET gossip_menu_id=9052 WHERE entry=24965;
UPDATE creature_template SET gossip_menu_id=9050 WHERE entry=24975;
UPDATE creature_template SET gossip_menu_id=9059 WHERE entry=24996;
UPDATE creature_template SET gossip_menu_id=9059 WHERE entry=24997;
UPDATE creature_template SET gossip_menu_id=9068 WHERE entry=25009;
UPDATE creature_template SET gossip_menu_id=9066 WHERE entry=25011;
UPDATE creature_template SET gossip_menu_id=9072 WHERE entry=25013;
UPDATE creature_template SET gossip_menu_id=9072 WHERE entry=25014;
UPDATE creature_template SET gossip_menu_id=9067 WHERE entry=25015;
UPDATE creature_template SET gossip_menu_id=9071 WHERE entry=25016;
UPDATE creature_template SET gossip_menu_id=9069 WHERE entry=25017;
UPDATE creature_template SET gossip_menu_id=9070 WHERE entry=25018;
UPDATE creature_template SET gossip_menu_id=9054 WHERE entry=25021;
UPDATE creature_template SET gossip_menu_id=9056 WHERE entry=25022;
UPDATE creature_template SET gossip_menu_id=9057 WHERE entry=25023;
UPDATE creature_template SET gossip_menu_id=9054 WHERE entry=25024;
UPDATE creature_template SET gossip_menu_id=9077 WHERE entry=25025;
UPDATE creature_template SET gossip_menu_id=9126 WHERE entry=25032;
UPDATE creature_template SET gossip_menu_id=9087 WHERE entry=25046;
UPDATE creature_template SET gossip_menu_id=9079 WHERE entry=25053;
UPDATE creature_template SET gossip_menu_id=9064 WHERE entry=25057;
UPDATE creature_template SET gossip_menu_id=9062 WHERE entry=25059;
UPDATE creature_template SET gossip_menu_id=9063 WHERE entry=25061;
UPDATE creature_template SET gossip_menu_id=9127 WHERE entry=25069;
UPDATE creature_template SET gossip_menu_id=9088 WHERE entry=25088;
UPDATE creature_template SET gossip_menu_id=9084 WHERE entry=25099;
UPDATE creature_template SET gossip_menu_id=9111 WHERE entry=25108;
UPDATE creature_template SET gossip_menu_id=9115 WHERE entry=25112;
UPDATE creature_template SET gossip_menu_id=9105 WHERE entry=25169;
UPDATE creature_template SET gossip_menu_id=9138 WHERE entry=25198;
UPDATE creature_template SET gossip_menu_id=9133 WHERE entry=25199;
UPDATE creature_template SET gossip_menu_id=9134 WHERE entry=25205;
UPDATE creature_template SET gossip_menu_id=9130 WHERE entry=25206;
UPDATE creature_template SET gossip_menu_id=9137 WHERE entry=25208;
UPDATE creature_template SET gossip_menu_id=9143 WHERE entry=25236;
UPDATE creature_template SET gossip_menu_id=9218 WHERE entry=25248;
UPDATE creature_template SET gossip_menu_id=9223 WHERE entry=25251;
UPDATE creature_template SET gossip_menu_id=9216 WHERE entry=25285;
UPDATE creature_template SET gossip_menu_id=9160 WHERE entry=25335;
UPDATE creature_template SET gossip_menu_id=9153 WHERE entry=25336;
UPDATE creature_template SET gossip_menu_id=9154 WHERE entry=25339;
UPDATE creature_template SET gossip_menu_id=9155 WHERE entry=25342;
UPDATE creature_template SET gossip_menu_id=9156 WHERE entry=25343;
UPDATE creature_template SET gossip_menu_id=9158 WHERE entry=25374;
UPDATE creature_template SET gossip_menu_id=9159 WHERE entry=25376;
UPDATE creature_template SET gossip_menu_id=9185 WHERE entry=25381;
UPDATE creature_template SET gossip_menu_id=9247 WHERE entry=25395;
UPDATE creature_template SET gossip_menu_id=9186 WHERE entry=25435;
UPDATE creature_template SET gossip_menu_id=9170 WHERE entry=25589;
UPDATE creature_template SET gossip_menu_id=9172 WHERE entry=25602;
UPDATE creature_template SET gossip_menu_id=9173 WHERE entry=25604;
UPDATE creature_template SET gossip_menu_id=9215 WHERE entry=25816;
UPDATE creature_template SET gossip_menu_id=9187 WHERE entry=25825;
UPDATE creature_template SET gossip_menu_id=9219 WHERE entry=25828;
UPDATE creature_template SET gossip_menu_id=9198 WHERE entry=25950;
UPDATE creature_template SET gossip_menu_id=9224 WHERE entry=26083;
UPDATE creature_template SET gossip_menu_id=9214 WHERE entry=26084;
UPDATE creature_template SET gossip_menu_id=9210 WHERE entry=26085;
UPDATE creature_template SET gossip_menu_id=9495 WHERE entry=26110;
UPDATE creature_template SET gossip_menu_id=9248 WHERE entry=26158;
UPDATE creature_template SET gossip_menu_id=9417 WHERE entry=26170;
UPDATE creature_template SET gossip_menu_id=9262 WHERE entry=26206;
UPDATE creature_template SET gossip_menu_id=9280 WHERE entry=26219;
UPDATE creature_template SET gossip_menu_id=9617 WHERE entry=26379;
UPDATE creature_template SET gossip_menu_id=9428 WHERE entry=26415;
UPDATE creature_template SET gossip_menu_id=9301 WHERE entry=26422;
UPDATE creature_template SET gossip_menu_id=9604 WHERE entry=26424;
UPDATE creature_template SET gossip_menu_id=9455 WHERE entry=26443;
UPDATE creature_template SET gossip_menu_id=9513 WHERE entry=26471;
UPDATE creature_template SET gossip_menu_id=9452 WHERE entry=26473;
UPDATE creature_template SET gossip_menu_id=9622 WHERE entry=26519;
UPDATE creature_template SET gossip_menu_id=9342 WHERE entry=26546;
UPDATE creature_template SET gossip_menu_id=9416 WHERE entry=26604;
UPDATE creature_template SET gossip_menu_id=9420 WHERE entry=26647;
UPDATE creature_template SET gossip_menu_id=9451 WHERE entry=26659;
UPDATE creature_template SET gossip_menu_id=9690 WHERE entry=26664;
UPDATE creature_template SET gossip_menu_id=10258 WHERE entry=26666;
UPDATE creature_template SET gossip_menu_id=9511 WHERE entry=26673;
UPDATE creature_template SET gossip_menu_id=344 WHERE entry=26680;
UPDATE creature_template SET gossip_menu_id=9614 WHERE entry=26709;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=26721;
UPDATE creature_template SET gossip_menu_id=9431 WHERE entry=26814;
UPDATE creature_template SET gossip_menu_id=9785 WHERE entry=26853;
UPDATE creature_template SET gossip_menu_id=9571 WHERE entry=26860;
UPDATE creature_template SET gossip_menu_id=9633 WHERE entry=26868;
UPDATE creature_template SET gossip_menu_id=9985 WHERE entry=26905;
UPDATE creature_template SET gossip_menu_id=10116 WHERE entry=26914;
UPDATE creature_template SET gossip_menu_id=9879 WHERE entry=26916;
UPDATE creature_template SET gossip_menu_id=10220 WHERE entry=26924;
UPDATE creature_template SET gossip_menu_id=9770 WHERE entry=26935;
UPDATE creature_template SET gossip_menu_id=9576 WHERE entry=26944;
UPDATE creature_template SET gossip_menu_id=10115 WHERE entry=26969;
UPDATE creature_template SET gossip_menu_id=9988 WHERE entry=26972;
UPDATE creature_template SET gossip_menu_id=9851 WHERE entry=26973;
UPDATE creature_template SET gossip_menu_id=9879 WHERE entry=26977;
UPDATE creature_template SET gossip_menu_id=9893 WHERE entry=26982;
UPDATE creature_template SET gossip_menu_id=9460 WHERE entry=26985;
UPDATE creature_template SET gossip_menu_id=348 WHERE entry=27027;
UPDATE creature_template SET gossip_menu_id=9632 WHERE entry=27037;
UPDATE creature_template SET gossip_menu_id=9476 WHERE entry=27052;
UPDATE creature_template SET gossip_menu_id=9475 WHERE entry=27060;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=27065;
UPDATE creature_template SET gossip_menu_id=9477 WHERE entry=27125;
UPDATE creature_template SET gossip_menu_id=9483 WHERE entry=27172;
UPDATE creature_template SET gossip_menu_id=9481 WHERE entry=27215;
UPDATE creature_template SET gossip_menu_id=9577 WHERE entry=27216;
UPDATE creature_template SET gossip_menu_id=9544 WHERE entry=27224;
UPDATE creature_template SET gossip_menu_id=9543 WHERE entry=27225;
UPDATE creature_template SET gossip_menu_id=9541 WHERE entry=27226;
UPDATE creature_template SET gossip_menu_id=9545 WHERE entry=27229;
UPDATE creature_template SET gossip_menu_id=9540 WHERE entry=27243;
UPDATE creature_template SET gossip_menu_id=9486 WHERE entry=27255;
UPDATE creature_template SET gossip_menu_id=9490 WHERE entry=27262;
UPDATE creature_template SET gossip_menu_id=9562 WHERE entry=27318;
UPDATE creature_template SET gossip_menu_id=9542 WHERE entry=27347;
UPDATE creature_template SET gossip_menu_id=9519 WHERE entry=27388;
UPDATE creature_template SET gossip_menu_id=9517 WHERE entry=27398;
UPDATE creature_template SET gossip_menu_id=21251 WHERE entry=27414;
UPDATE creature_template SET gossip_menu_id=9554 WHERE entry=27489;
UPDATE creature_template SET gossip_menu_id=9550 WHERE entry=27495;
UPDATE creature_template SET gossip_menu_id=9590 WHERE entry=27565;
UPDATE creature_template SET gossip_menu_id=9580 WHERE entry=27704;
UPDATE creature_template SET gossip_menu_id=9720 WHERE entry=27801;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27806;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27810;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27811;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27812;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27814;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27815;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27816;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27817;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27818;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27819;
UPDATE creature_template SET gossip_menu_id=9549 WHERE entry=27820;
UPDATE creature_template SET gossip_menu_id=9619 WHERE entry=27914;
UPDATE creature_template SET gossip_menu_id=9877 WHERE entry=27928;
UPDATE creature_template SET gossip_menu_id=9742 WHERE entry=28027;
UPDATE creature_template SET gossip_menu_id=9635 WHERE entry=28033;
UPDATE creature_template SET gossip_menu_id=9640 WHERE entry=28041;
UPDATE creature_template SET gossip_menu_id=9641 WHERE entry=28042;
UPDATE creature_template SET gossip_menu_id=9804 WHERE entry=28046;
UPDATE creature_template SET gossip_menu_id=9647 WHERE entry=28048;
UPDATE creature_template SET gossip_menu_id=9645 WHERE entry=28049;
UPDATE creature_template SET gossip_menu_id=9644 WHERE entry=28050;
UPDATE creature_template SET gossip_menu_id=9643 WHERE entry=28051;
UPDATE creature_template SET gossip_menu_id=9639 WHERE entry=28059;
UPDATE creature_template SET gossip_menu_id=9646 WHERE entry=28060;
UPDATE creature_template SET gossip_menu_id=9648 WHERE entry=28067;
UPDATE creature_template SET gossip_menu_id=9740 WHERE entry=28082;
UPDATE creature_template SET gossip_menu_id=9744 WHERE entry=28107;
UPDATE creature_template SET gossip_menu_id=9728 WHERE entry=28113;
UPDATE creature_template SET gossip_menu_id=9743 WHERE entry=28114;
UPDATE creature_template SET gossip_menu_id=9746 WHERE entry=28122;
UPDATE creature_template SET gossip_menu_id=9741 WHERE entry=28138;
UPDATE creature_template SET gossip_menu_id=9655 WHERE entry=28141;
UPDATE creature_template SET gossip_menu_id=9657 WHERE entry=28143;
UPDATE creature_template SET gossip_menu_id=9665 WHERE entry=28209;
UPDATE creature_template SET gossip_menu_id=9666 WHERE entry=28210;
UPDATE creature_template SET gossip_menu_id=9748 WHERE entry=28216;
UPDATE creature_template SET gossip_menu_id=9677 WHERE entry=28217;
UPDATE creature_template SET gossip_menu_id=9674 WHERE entry=28298;
UPDATE creature_template SET gossip_menu_id=9675 WHERE entry=28309;
UPDATE creature_template SET gossip_menu_id=9678 WHERE entry=28315;
UPDATE creature_template SET gossip_menu_id=9723 WHERE entry=28374;
UPDATE creature_template SET gossip_menu_id=9685 WHERE entry=28375;
UPDATE creature_template SET gossip_menu_id=9688 WHERE entry=28376;
UPDATE creature_template SET gossip_menu_id=9765 WHERE entry=28406;
UPDATE creature_template SET gossip_menu_id=9693 WHERE entry=28474;
UPDATE creature_template SET gossip_menu_id=9731 WHERE entry=28503;
UPDATE creature_template SET gossip_menu_id=9715 WHERE entry=28561;
UPDATE creature_template SET gossip_menu_id=12600 WHERE entry=28571;
UPDATE creature_template SET gossip_menu_id=12598 WHERE entry=28572;
UPDATE creature_template SET gossip_menu_id=9717 WHERE entry=28589;
UPDATE creature_template SET gossip_menu_id=9724 WHERE entry=28604;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=28621;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=28623;
UPDATE creature_template SET gossip_menu_id=9732 WHERE entry=28666;
UPDATE creature_template SET gossip_menu_id=9873 WHERE entry=28701;
UPDATE creature_template SET gossip_menu_id=10627 WHERE entry=28703;
UPDATE creature_template SET gossip_menu_id=9750 WHERE entry=28746;
UPDATE creature_template SET gossip_menu_id=9735 WHERE entry=28760;
UPDATE creature_template SET gossip_menu_id=9738 WHERE entry=28771;
UPDATE creature_template SET gossip_menu_id=9838 WHERE entry=28774;
UPDATE creature_template SET gossip_menu_id=9832 WHERE entry=28776;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=28790;
UPDATE creature_template SET gossip_menu_id=9752 WHERE entry=28888;
UPDATE creature_template SET gossip_menu_id=9751 WHERE entry=28908;
UPDATE creature_template SET gossip_menu_id=9758 WHERE entry=28910;
UPDATE creature_template SET gossip_menu_id=9762 WHERE entry=28912;
UPDATE creature_template SET gossip_menu_id=9769 WHERE entry=28914;
UPDATE creature_template SET gossip_menu_id=9754 WHERE entry=28919;
UPDATE creature_template SET gossip_menu_id=9755 WHERE entry=28943;
UPDATE creature_template SET gossip_menu_id=9778 WHERE entry=29006;
UPDATE creature_template SET gossip_menu_id=9766 WHERE entry=29043;
UPDATE creature_template SET gossip_menu_id=9781 WHERE entry=29143;
UPDATE creature_template SET gossip_menu_id=9781 WHERE entry=29145;
UPDATE creature_template SET gossip_menu_id=9774 WHERE entry=29146;
UPDATE creature_template SET gossip_menu_id=9775 WHERE entry=29149;
UPDATE creature_template SET gossip_menu_id=9780 WHERE entry=29155;
UPDATE creature_template SET gossip_menu_id=9780 WHERE entry=29159;
UPDATE creature_template SET gossip_menu_id=9780 WHERE entry=29160;
UPDATE creature_template SET gossip_menu_id=9780 WHERE entry=29162;
UPDATE creature_template SET gossip_menu_id=9795 WHERE entry=29173;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=29250;
UPDATE creature_template SET gossip_menu_id=54000 WHERE entry=29327;
UPDATE creature_template SET gossip_menu_id=9806 WHERE entry=29344;
UPDATE creature_template SET gossip_menu_id=9871 WHERE entry=29384;
UPDATE creature_template SET gossip_menu_id=9813 WHERE entry=29396;
UPDATE creature_template SET gossip_menu_id=9918 WHERE entry=29430;
UPDATE creature_template SET gossip_menu_id=9859 WHERE entry=29434;
UPDATE creature_template SET gossip_menu_id=9924 WHERE entry=29445;
UPDATE creature_template SET gossip_menu_id=10180 WHERE entry=29478;
UPDATE creature_template SET gossip_menu_id=9913 WHERE entry=29481;
UPDATE creature_template SET gossip_menu_id=9814 WHERE entry=29551;
UPDATE creature_template SET gossip_menu_id=9822 WHERE entry=29592;
UPDATE creature_template SET gossip_menu_id=9834 WHERE entry=29611;
UPDATE creature_template SET gossip_menu_id=9831 WHERE entry=29631;
UPDATE creature_template SET gossip_menu_id=9830 WHERE entry=29667;
UPDATE creature_template SET gossip_menu_id=9827 WHERE entry=29668;
UPDATE creature_template SET gossip_menu_id=9828 WHERE entry=29669;
UPDATE creature_template SET gossip_menu_id=9829 WHERE entry=29670;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=29671;
UPDATE creature_template SET gossip_menu_id=9830 WHERE entry=29672;
UPDATE creature_template SET gossip_menu_id=9827 WHERE entry=29673;
UPDATE creature_template SET gossip_menu_id=9828 WHERE entry=29674;
UPDATE creature_template SET gossip_menu_id=9829 WHERE entry=29675;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=29676;
UPDATE creature_template SET gossip_menu_id=9848 WHERE entry=29688;
UPDATE creature_template SET gossip_menu_id=9861 WHERE entry=29689;
UPDATE creature_template SET gossip_menu_id=9823 WHERE entry=29725;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=29740;
UPDATE creature_template SET gossip_menu_id=9914 WHERE entry=29839;
UPDATE creature_template SET gossip_menu_id=1582 WHERE entry=29944;
UPDATE creature_template SET gossip_menu_id=9868 WHERE entry=29963;
UPDATE creature_template SET gossip_menu_id=344 WHERE entry=29971;
UPDATE creature_template SET gossip_menu_id=10108 WHERE entry=29997;
UPDATE creature_template SET gossip_menu_id=9900 WHERE entry=30105;
UPDATE creature_template SET gossip_menu_id=9880 WHERE entry=30190;
UPDATE creature_template SET gossip_menu_id=9922 WHERE entry=30227;
UPDATE creature_template SET gossip_menu_id=8073 WHERE entry=30231;
UPDATE creature_template SET gossip_menu_id=9906 WHERE entry=30395;
UPDATE creature_template SET gossip_menu_id=9904 WHERE entry=30400;
UPDATE creature_template SET gossip_menu_id=9915 WHERE entry=30481;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30567;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=30578;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=30579;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=30580;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=30581;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30582;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30583;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30584;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30586;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=30587;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=30590;
UPDATE creature_template SET gossip_menu_id=9999 WHERE entry=30596;
UPDATE creature_template SET gossip_menu_id=9995 WHERE entry=30677;
UPDATE creature_template SET gossip_menu_id=10107 WHERE entry=30708;
UPDATE creature_template SET gossip_menu_id=10217 WHERE entry=30824;
UPDATE creature_template SET gossip_menu_id=10174 WHERE entry=30825;
UPDATE creature_template SET gossip_menu_id=10009 WHERE entry=30871;
UPDATE creature_template SET gossip_menu_id=10112 WHERE entry=30944;
UPDATE creature_template SET gossip_menu_id=10023 WHERE entry=31044;
UPDATE creature_template SET gossip_menu_id=10188 WHERE entry=31051;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=31078;
UPDATE creature_template SET gossip_menu_id=10027 WHERE entry=31084;
UPDATE creature_template SET gossip_menu_id=10026 WHERE entry=31085;
UPDATE creature_template SET gossip_menu_id=10229 WHERE entry=31091;
UPDATE creature_template SET gossip_menu_id=10208 WHERE entry=31109;
UPDATE creature_template SET gossip_menu_id=21289 WHERE entry=31111;
UPDATE creature_template SET gossip_menu_id=10029 WHERE entry=31115;
UPDATE creature_template SET gossip_menu_id=10147 WHERE entry=31136;
UPDATE creature_template SET gossip_menu_id=9695 WHERE entry=31210;
UPDATE creature_template SET gossip_menu_id=10038 WHERE entry=31261;
UPDATE creature_template SET gossip_menu_id=10040 WHERE entry=31304;
UPDATE creature_template SET gossip_menu_id=10179 WHERE entry=31333;
UPDATE creature_template SET gossip_menu_id=10119 WHERE entry=31648;
UPDATE creature_template SET gossip_menu_id=10120 WHERE entry=31720;
UPDATE creature_template SET gossip_menu_id=10120 WHERE entry=31723;
UPDATE creature_template SET gossip_menu_id=10120 WHERE entry=31724;
UPDATE creature_template SET gossip_menu_id=10135 WHERE entry=31737;
UPDATE creature_template SET gossip_menu_id=10122 WHERE entry=31776;
UPDATE creature_template SET gossip_menu_id=10123 WHERE entry=31781;
UPDATE creature_template SET gossip_menu_id=10125 WHERE entry=31808;
UPDATE creature_template SET gossip_menu_id=6261 WHERE entry=31961;
UPDATE creature_template SET gossip_menu_id=6484 WHERE entry=31979;
UPDATE creature_template SET gossip_menu_id=5442 WHERE entry=32032;
UPDATE creature_template SET gossip_menu_id=6262 WHERE entry=32076;
UPDATE creature_template SET gossip_menu_id=5124 WHERE entry=32080;
UPDATE creature_template SET gossip_menu_id=6500 WHERE entry=32092;
UPDATE creature_template SET gossip_menu_id=5241 WHERE entry=32099;
UPDATE creature_template SET gossip_menu_id=10200 WHERE entry=32239;
UPDATE creature_template SET gossip_menu_id=10171 WHERE entry=32301;
UPDATE creature_template SET gossip_menu_id=10172 WHERE entry=32302;
UPDATE creature_template SET gossip_menu_id=10189 WHERE entry=32346;
UPDATE creature_template SET gossip_menu_id=10194 WHERE entry=32401;
UPDATE creature_template SET gossip_menu_id=10203 WHERE entry=32524;
UPDATE creature_template SET gossip_menu_id=10281 WHERE entry=32540;
UPDATE creature_template SET gossip_menu_id=9828 WHERE entry=32616;
UPDATE creature_template SET gossip_menu_id=9828 WHERE entry=32617;
UPDATE creature_template SET gossip_menu_id=9827 WHERE entry=32618;
UPDATE creature_template SET gossip_menu_id=9827 WHERE entry=32619;
UPDATE creature_template SET gossip_menu_id=9829 WHERE entry=32620;
UPDATE creature_template SET gossip_menu_id=9829 WHERE entry=32621;
UPDATE creature_template SET gossip_menu_id=9981 WHERE entry=32622;
UPDATE creature_template SET gossip_menu_id=9983 WHERE entry=32623;
UPDATE creature_template SET gossip_menu_id=9830 WHERE entry=32624;
UPDATE creature_template SET gossip_menu_id=9830 WHERE entry=32625;
UPDATE creature_template SET gossip_menu_id=9203 WHERE entry=32803;
UPDATE creature_template SET gossip_menu_id=9203 WHERE entry=32804;
UPDATE creature_template SET gossip_menu_id=10257 WHERE entry=32836;
UPDATE creature_template SET gossip_menu_id=10480 WHERE entry=32963;
UPDATE creature_template SET gossip_menu_id=10321 WHERE entry=32971;
UPDATE creature_template SET gossip_menu_id=10482 WHERE entry=32978;
UPDATE creature_template SET gossip_menu_id=12726 WHERE entry=32979;
UPDATE creature_template SET gossip_menu_id=10269 WHERE entry=32987;
UPDATE creature_template SET gossip_menu_id=10479 WHERE entry=33048;
UPDATE creature_template SET gossip_menu_id=10490 WHERE entry=33072;
UPDATE creature_template SET gossip_menu_id=10483 WHERE entry=33091;
UPDATE creature_template SET gossip_menu_id=10309 WHERE entry=33187;
UPDATE creature_template SET gossip_menu_id=10310 WHERE entry=33204;
UPDATE creature_template SET gossip_menu_id=10318 WHERE entry=33238;
UPDATE creature_template SET gossip_menu_id=10317 WHERE entry=33239;
UPDATE creature_template SET gossip_menu_id=10376 WHERE entry=33335;
UPDATE creature_template SET gossip_menu_id=10429 WHERE entry=33359;
UPDATE creature_template SET gossip_menu_id=10341 WHERE entry=33454;
UPDATE creature_template SET gossip_menu_id=10504 WHERE entry=33532;
UPDATE creature_template SET gossip_menu_id=10503 WHERE entry=33533;
UPDATE creature_template SET gossip_menu_id=10393 WHERE entry=33957;
UPDATE creature_template SET gossip_menu_id=8903 WHERE entry=33971;
UPDATE creature_template SET gossip_menu_id=10408 WHERE entry=33996;
UPDATE creature_template SET gossip_menu_id=10484 WHERE entry=34205;
UPDATE creature_template SET gossip_menu_id=10478 WHERE entry=34244;
UPDATE creature_template SET gossip_menu_id=10517 WHERE entry=34249;
UPDATE creature_template SET gossip_menu_id=10494 WHERE entry=34289;
UPDATE creature_template SET gossip_menu_id=10495 WHERE entry=34290;
UPDATE creature_template SET gossip_menu_id=10493 WHERE entry=34292;
UPDATE creature_template SET gossip_menu_id=10486 WHERE entry=34301;
UPDATE creature_template SET gossip_menu_id=10497 WHERE entry=34320;
UPDATE creature_template SET gossip_menu_id=10499 WHERE entry=34340;
UPDATE creature_template SET gossip_menu_id=11853 WHERE entry=34342;
UPDATE creature_template SET gossip_menu_id=10498 WHERE entry=34343;
UPDATE creature_template SET gossip_menu_id=11445 WHERE entry=34354;
UPDATE creature_template SET gossip_menu_id=10509 WHERE entry=34392;
UPDATE creature_template SET gossip_menu_id=10516 WHERE entry=34402;
UPDATE creature_template SET gossip_menu_id=10515 WHERE entry=34403;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34435;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34476;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34477;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34478;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34479;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34480;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34481;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34482;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34483;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=34484;
UPDATE creature_template SET gossip_menu_id=10520 WHERE entry=34513;
UPDATE creature_template SET gossip_menu_id=10524 WHERE entry=34528;
UPDATE creature_template SET gossip_menu_id=10528 WHERE entry=34578;
UPDATE creature_template SET gossip_menu_id=10532 WHERE entry=34608;
UPDATE creature_template SET gossip_menu_id=10540 WHERE entry=34626;
UPDATE creature_template SET gossip_menu_id=10545 WHERE entry=34634;
UPDATE creature_template SET gossip_menu_id=10575 WHERE entry=34654;
UPDATE creature_template SET gossip_menu_id=10675 WHERE entry=34673;
UPDATE creature_template SET gossip_menu_id=10548 WHERE entry=34674;
UPDATE creature_template SET gossip_menu_id=10683 WHERE entry=34689;
UPDATE creature_template SET gossip_menu_id=10686 WHERE entry=34693;
UPDATE creature_template SET gossip_menu_id=10684 WHERE entry=34695;
UPDATE creature_template SET gossip_menu_id=10681 WHERE entry=34696;
UPDATE creature_template SET gossip_menu_id=10821 WHERE entry=34697;
UPDATE creature_template SET gossip_menu_id=12757 WHERE entry=34698;
UPDATE creature_template SET gossip_menu_id=10559 WHERE entry=34719;
UPDATE creature_template SET gossip_menu_id=10558 WHERE entry=34721;
UPDATE creature_template SET gossip_menu_id=10563 WHERE entry=34723;
UPDATE creature_template SET gossip_menu_id=10556 WHERE entry=34754;
UPDATE creature_template SET gossip_menu_id=10564 WHERE entry=34761;
UPDATE creature_template SET gossip_menu_id=10566 WHERE entry=34766;
UPDATE creature_template SET gossip_menu_id=10689 WHERE entry=34771;
UPDATE creature_template SET gossip_menu_id=10599 WHERE entry=34816;
UPDATE creature_template SET gossip_menu_id=10613 WHERE entry=34872;
UPDATE creature_template SET gossip_menu_id=10595 WHERE entry=34874;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=34948;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=34949;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=34950;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=34951;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=34952;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=34953;
UPDATE creature_template SET gossip_menu_id=10605 WHERE entry=34976;
UPDATE creature_template SET gossip_menu_id=10606 WHERE entry=34997;
UPDATE creature_template SET gossip_menu_id=10606 WHERE entry=34998;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=35017;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=35019;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=35020;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=35021;
UPDATE creature_template SET gossip_menu_id=10602 WHERE entry=35022;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=35023;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=35024;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=35025;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=35026;
UPDATE creature_template SET gossip_menu_id=10601 WHERE entry=35027;
UPDATE creature_template SET gossip_menu_id=10609 WHERE entry=35035;
UPDATE creature_template SET gossip_menu_id=10631 WHERE entry=35073;
UPDATE creature_template SET gossip_menu_id=10641 WHERE entry=35087;
UPDATE creature_template SET gossip_menu_id=10640 WHERE entry=35091;
UPDATE creature_template SET gossip_menu_id=11346 WHERE entry=35222;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35243;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35244;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35246;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35247;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35248;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35249;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35250;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35251;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35252;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35253;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35254;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35256;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35258;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35259;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35260;
UPDATE creature_template SET gossip_menu_id=34435 WHERE entry=35261;
UPDATE creature_template SET gossip_menu_id=7260 WHERE entry=35281;
UPDATE creature_template SET gossip_menu_id=10638 WHERE entry=35364;
UPDATE creature_template SET gossip_menu_id=10638 WHERE entry=35365;
UPDATE creature_template SET gossip_menu_id=10668 WHERE entry=35646;
UPDATE creature_template SET gossip_menu_id=10671 WHERE entry=35650;
UPDATE creature_template SET gossip_menu_id=10690 WHERE entry=35657;
UPDATE creature_template SET gossip_menu_id=10678 WHERE entry=35766;
UPDATE creature_template SET gossip_menu_id=10679 WHERE entry=35770;
UPDATE creature_template SET gossip_menu_id=10701 WHERE entry=35893;
UPDATE creature_template SET gossip_menu_id=10797 WHERE entry=36077;
UPDATE creature_template SET gossip_menu_id=10709 WHERE entry=36095;
UPDATE creature_template SET gossip_menu_id=10710 WHERE entry=36097;
UPDATE creature_template SET gossip_menu_id=10713 WHERE entry=36115;
UPDATE creature_template SET gossip_menu_id=10714 WHERE entry=36117;
UPDATE creature_template SET gossip_menu_id=10716 WHERE entry=36127;
UPDATE creature_template SET gossip_menu_id=10718 WHERE entry=36145;
UPDATE creature_template SET gossip_menu_id=10724 WHERE entry=36161;
UPDATE creature_template SET gossip_menu_id=10720 WHERE entry=36180;
UPDATE creature_template SET gossip_menu_id=10721 WHERE entry=36184;
UPDATE creature_template SET gossip_menu_id=10722 WHERE entry=36186;
UPDATE creature_template SET gossip_menu_id=10847 WHERE entry=36296;
UPDATE creature_template SET gossip_menu_id=10789 WHERE entry=36404;
UPDATE creature_template SET gossip_menu_id=10790 WHERE entry=36406;
UPDATE creature_template SET gossip_menu_id=10792 WHERE entry=36417;
UPDATE creature_template SET gossip_menu_id=10793 WHERE entry=36418;
UPDATE creature_template SET gossip_menu_id=10794 WHERE entry=36428;
UPDATE creature_template SET gossip_menu_id=10795 WHERE entry=36429;
UPDATE creature_template SET gossip_menu_id=10722 WHERE entry=36463;
UPDATE creature_template SET gossip_menu_id=10814 WHERE entry=36518;
UPDATE creature_template SET gossip_menu_id=10815 WHERE entry=36519;
UPDATE creature_template SET gossip_menu_id=10816 WHERE entry=36520;
UPDATE creature_template SET gossip_menu_id=10817 WHERE entry=36521;
UPDATE creature_template SET gossip_menu_id=10818 WHERE entry=36523;
UPDATE creature_template SET gossip_menu_id=10819 WHERE entry=36524;
UPDATE creature_template SET gossip_menu_id=10555 WHERE entry=36525;
UPDATE creature_template SET gossip_menu_id=10824 WHERE entry=36596;
UPDATE creature_template SET gossip_menu_id=5851 WHERE entry=36648;
UPDATE creature_template SET gossip_menu_id=11008 WHERE entry=36694;
UPDATE creature_template SET gossip_menu_id=10844 WHERE entry=36730;
UPDATE creature_template SET gossip_menu_id=10854 WHERE entry=36856;
UPDATE creature_template SET gossip_menu_id=10852 WHERE entry=36919;
UPDATE creature_template SET gossip_menu_id=10954 WHERE entry=36939;
UPDATE creature_template SET gossip_menu_id=10892 WHERE entry=37087;
UPDATE creature_template SET gossip_menu_id=10879 WHERE entry=37115;
UPDATE creature_template SET gossip_menu_id=10878 WHERE entry=37121;
UPDATE creature_template SET gossip_menu_id=10888 WHERE entry=37138;
UPDATE creature_template SET gossip_menu_id=10895 WHERE entry=37154;
UPDATE creature_template SET gossip_menu_id=10899 WHERE entry=37218;
UPDATE creature_template SET gossip_menu_id=10950 WHERE entry=37223;
UPDATE creature_template SET gossip_menu_id=6261 WHERE entry=37279;
UPDATE creature_template SET gossip_menu_id=6484 WHERE entry=37298;
UPDATE creature_template SET gossip_menu_id=5442 WHERE entry=37352;
UPDATE creature_template SET gossip_menu_id=6262 WHERE entry=37397;
UPDATE creature_template SET gossip_menu_id=6500 WHERE entry=37413;
UPDATE creature_template SET gossip_menu_id=10903 WHERE entry=37500;
UPDATE creature_template SET gossip_menu_id=10904 WHERE entry=37515;
UPDATE creature_template SET gossip_menu_id=10905 WHERE entry=37516;
UPDATE creature_template SET gossip_menu_id=10909 WHERE entry=37554;
UPDATE creature_template SET gossip_menu_id=10925 WHERE entry=37580;
UPDATE creature_template SET gossip_menu_id=10925 WHERE entry=37581;
UPDATE creature_template SET gossip_menu_id=10923 WHERE entry=37591;
UPDATE creature_template SET gossip_menu_id=10922 WHERE entry=37592;
UPDATE creature_template SET gossip_menu_id=10923 WHERE entry=37606;
UPDATE creature_template SET gossip_menu_id=10925 WHERE entry=37614;
UPDATE creature_template SET gossip_menu_id=10971 WHERE entry=37633;
UPDATE creature_template SET gossip_menu_id=10990 WHERE entry=37671;
UPDATE creature_template SET gossip_menu_id=10921 WHERE entry=37675;
UPDATE creature_template SET gossip_menu_id=10936 WHERE entry=37679;
UPDATE creature_template SET gossip_menu_id=12469 WHERE entry=37708;
UPDATE creature_template SET gossip_menu_id=12468 WHERE entry=37709;
UPDATE creature_template SET gossip_menu_id=12470 WHERE entry=37710;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=37724;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=37737;
UPDATE creature_template SET gossip_menu_id=10992 WHERE entry=37742;
UPDATE creature_template SET gossip_menu_id=10935 WHERE entry=37811;
UPDATE creature_template SET gossip_menu_id=11019 WHERE entry=37812;
UPDATE creature_template SET gossip_menu_id=11155 WHERE entry=37835;
UPDATE creature_template SET gossip_menu_id=10940 WHERE entry=37847;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=37887;
UPDATE creature_template SET gossip_menu_id=10949 WHERE entry=37904;
UPDATE creature_template SET gossip_menu_id=10964 WHERE entry=37910;
UPDATE creature_template SET gossip_menu_id=11130 WHERE entry=37987;
UPDATE creature_template SET gossip_menu_id=10961 WHERE entry=38033;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38039;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38040;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38041;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38042;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38043;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38044;
UPDATE creature_template SET gossip_menu_id=10948 WHERE entry=38045;
UPDATE creature_template SET gossip_menu_id=10990 WHERE entry=38065;
UPDATE creature_template SET gossip_menu_id=10969 WHERE entry=38140;
UPDATE creature_template SET gossip_menu_id=10954 WHERE entry=38156;
UPDATE creature_template SET gossip_menu_id=10875 WHERE entry=38157;
UPDATE creature_template SET gossip_menu_id=11007 WHERE entry=38208;
UPDATE creature_template SET gossip_menu_id=10985 WHERE entry=38244;
UPDATE creature_template SET gossip_menu_id=10986 WHERE entry=38245;
UPDATE creature_template SET gossip_menu_id=10987 WHERE entry=38246;
UPDATE creature_template SET gossip_menu_id=10991 WHERE entry=38293;
UPDATE creature_template SET gossip_menu_id=10991 WHERE entry=38295;
UPDATE creature_template SET gossip_menu_id=11005 WHERE entry=38314;
UPDATE creature_template SET gossip_menu_id=11012 WHERE entry=38378;
UPDATE creature_template SET gossip_menu_id=11107 WHERE entry=38437;
UPDATE creature_template SET gossip_menu_id=11032 WHERE entry=38501;
UPDATE creature_template SET gossip_menu_id=11061 WHERE entry=38553;
UPDATE creature_template SET gossip_menu_id=12661 WHERE entry=38578;
UPDATE creature_template SET gossip_menu_id=11065 WHERE entry=38606;
UPDATE creature_template SET gossip_menu_id=10954 WHERE entry=38637;
UPDATE creature_template SET gossip_menu_id=10954 WHERE entry=38638;
UPDATE creature_template SET gossip_menu_id=10875 WHERE entry=38639;
UPDATE creature_template SET gossip_menu_id=10875 WHERE entry=38640;
UPDATE creature_template SET gossip_menu_id=11069 WHERE entry=38706;
UPDATE creature_template SET gossip_menu_id=11402 WHERE entry=38714;
UPDATE creature_template SET gossip_menu_id=11032 WHERE entry=38717;
UPDATE creature_template SET gossip_menu_id=11094 WHERE entry=38856;
UPDATE creature_template SET gossip_menu_id=11111 WHERE entry=38927;
UPDATE creature_template SET gossip_menu_id=10993 WHERE entry=38995;
UPDATE creature_template SET gossip_menu_id=11223 WHERE entry=39063;
UPDATE creature_template SET gossip_menu_id=11161 WHERE entry=39065;
UPDATE creature_template SET gossip_menu_id=11166 WHERE entry=39066;
UPDATE creature_template SET gossip_menu_id=11180 WHERE entry=39178;
UPDATE creature_template SET gossip_menu_id=11192 WHERE entry=39271;
UPDATE creature_template SET gossip_menu_id=11323 WHERE entry=39275;
UPDATE creature_template SET gossip_menu_id=11195 WHERE entry=39341;
UPDATE creature_template SET gossip_menu_id=11229 WHERE entry=39351;
UPDATE creature_template SET gossip_menu_id=11230 WHERE entry=39352;
UPDATE creature_template SET gossip_menu_id=11206 WHERE entry=39372;
UPDATE creature_template SET gossip_menu_id=11211 WHERE entry=39396;
UPDATE creature_template SET gossip_menu_id=11233 WHERE entry=39590;
UPDATE creature_template SET gossip_menu_id=11236 WHERE entry=39594;
UPDATE creature_template SET gossip_menu_id=12594 WHERE entry=39605;
UPDATE creature_template SET gossip_menu_id=11245 WHERE entry=39609;
UPDATE creature_template SET gossip_menu_id=11271 WHERE entry=39615;
UPDATE creature_template SET gossip_menu_id=11408 WHERE entry=40027;
UPDATE creature_template SET gossip_menu_id=11341 WHERE entry=40184;
UPDATE creature_template SET gossip_menu_id=11345 WHERE entry=40204;
UPDATE creature_template SET gossip_menu_id=11371 WHERE entry=40344;
UPDATE creature_template SET gossip_menu_id=21257 WHERE entry=40352;
UPDATE creature_template SET gossip_menu_id=11391 WHERE entry=40391;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=40405;
UPDATE creature_template SET gossip_menu_id=11386 WHERE entry=40438;
UPDATE creature_template SET gossip_menu_id=11383 WHERE entry=40441;
UPDATE creature_template SET gossip_menu_id=11392 WHERE entry=40475;
UPDATE creature_template SET gossip_menu_id=11393 WHERE entry=40478;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=40552;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=40553;
UPDATE creature_template SET gossip_menu_id=11403 WHERE entry=40554;
UPDATE creature_template SET gossip_menu_id=7524 WHERE entry=40572;
UPDATE creature_template SET gossip_menu_id=11426 WHERE entry=40580;
UPDATE creature_template SET gossip_menu_id=4746 WHERE entry=40589;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=40809;
UPDATE creature_template SET gossip_menu_id=11435 WHERE entry=40832;
UPDATE creature_template SET gossip_menu_id=11459 WHERE entry=40896;
UPDATE creature_template SET gossip_menu_id=1581 WHERE entry=40898;
UPDATE creature_template SET gossip_menu_id=11467 WHERE entry=40908;
UPDATE creature_template SET gossip_menu_id=11519 WHERE entry=40950;
UPDATE creature_template SET gossip_menu_id=11453 WHERE entry=41053;
UPDATE creature_template SET gossip_menu_id=11465 WHERE entry=41054;
UPDATE creature_template SET gossip_menu_id=11475 WHERE entry=41086;
UPDATE creature_template SET gossip_menu_id=11498 WHERE entry=41128;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=41140;
UPDATE creature_template SET gossip_menu_id=11472 WHERE entry=41190;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=41214;
UPDATE creature_template SET gossip_menu_id=11500 WHERE entry=41229;
UPDATE creature_template SET gossip_menu_id=11479 WHERE entry=41265;
UPDATE creature_template SET gossip_menu_id=11506 WHERE entry=41274;
UPDATE creature_template SET gossip_menu_id=11505 WHERE entry=41275;
UPDATE creature_template SET gossip_menu_id=11504 WHERE entry=41286;
UPDATE creature_template SET gossip_menu_id=11480 WHERE entry=41297;
UPDATE creature_template SET gossip_menu_id=11483 WHERE entry=41307;
UPDATE creature_template SET gossip_menu_id=11491 WHERE entry=41354;
UPDATE creature_template SET gossip_menu_id=11993 WHERE entry=41392;
UPDATE creature_template SET gossip_menu_id=11501 WHERE entry=41411;
UPDATE creature_template SET gossip_menu_id=11502 WHERE entry=41412;
UPDATE creature_template SET gossip_menu_id=11503 WHERE entry=41413;
UPDATE creature_template SET gossip_menu_id=11655 WHERE entry=41415;
UPDATE creature_template SET gossip_menu_id=12675 WHERE entry=41435;
UPDATE creature_template SET gossip_menu_id=11518 WHERE entry=41441;
UPDATE creature_template SET gossip_menu_id=11529 WHERE entry=41487;
UPDATE creature_template SET gossip_menu_id=11527 WHERE entry=41488;
UPDATE creature_template SET gossip_menu_id=10181 WHERE entry=41490;
UPDATE creature_template SET gossip_menu_id=1581 WHERE entry=41491;
UPDATE creature_template SET gossip_menu_id=11638 WHERE entry=41503;
UPDATE creature_template SET gossip_menu_id=11682 WHERE entry=41786;
UPDATE creature_template SET gossip_menu_id=11567 WHERE entry=41944;
UPDATE creature_template SET gossip_menu_id=11566 WHERE entry=41949;
UPDATE creature_template SET gossip_menu_id=11584 WHERE entry=41966;
UPDATE creature_template SET gossip_menu_id=11583 WHERE entry=42088;
UPDATE creature_template SET gossip_menu_id=11587 WHERE entry=42130;
UPDATE creature_template SET gossip_menu_id=11619 WHERE entry=42299;
UPDATE creature_template SET gossip_menu_id=11614 WHERE entry=42317;
UPDATE creature_template SET gossip_menu_id=11617 WHERE entry=42323;
UPDATE creature_template SET gossip_menu_id=11620 WHERE entry=42331;
UPDATE creature_template SET gossip_menu_id=11635 WHERE entry=42383;
UPDATE creature_template SET gossip_menu_id=11779 WHERE entry=42497;
UPDATE creature_template SET gossip_menu_id=11637 WHERE entry=42506;
UPDATE creature_template SET gossip_menu_id=12634 WHERE entry=42553;
UPDATE creature_template SET gossip_menu_id=11643 WHERE entry=42612;
UPDATE creature_template SET gossip_menu_id=11644 WHERE entry=42613;
UPDATE creature_template SET gossip_menu_id=11645 WHERE entry=42618;
UPDATE creature_template SET gossip_menu_id=11646 WHERE entry=42622;
UPDATE creature_template SET gossip_menu_id=11649 WHERE entry=42624;
UPDATE creature_template SET gossip_menu_id=11668 WHERE entry=42641;
UPDATE creature_template SET gossip_menu_id=11685 WHERE entry=42642;
UPDATE creature_template SET gossip_menu_id=11656 WHERE entry=42708;
UPDATE creature_template SET gossip_menu_id=11662 WHERE entry=42849;
UPDATE creature_template SET gossip_menu_id=12452 WHERE entry=42898;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=43001;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=43004;
UPDATE creature_template SET gossip_menu_id=11810 WHERE entry=43006;
UPDATE creature_template SET gossip_menu_id=14199 WHERE entry=43010;
UPDATE creature_template SET gossip_menu_id=11817 WHERE entry=43011;
UPDATE creature_template SET gossip_menu_id=14199 WHERE entry=43012;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=43013;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=43015;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=43017;
UPDATE creature_template SET gossip_menu_id=11791 WHERE entry=43042;
UPDATE creature_template SET gossip_menu_id=11681 WHERE entry=43062;
UPDATE creature_template SET gossip_menu_id=11705 WHERE entry=43217;
UPDATE creature_template SET gossip_menu_id=11720 WHERE entry=43221;
UPDATE creature_template SET gossip_menu_id=11726 WHERE entry=43239;
UPDATE creature_template SET gossip_menu_id=12647 WHERE entry=43299;
UPDATE creature_template SET gossip_menu_id=347 WHERE entry=43420;
UPDATE creature_template SET gossip_menu_id=8519 WHERE entry=43428;
UPDATE creature_template SET gossip_menu_id=11831 WHERE entry=43455;
UPDATE creature_template SET gossip_menu_id=12529 WHERE entry=43464;
UPDATE creature_template SET gossip_menu_id=11741 WHERE entry=43505;
UPDATE creature_template SET gossip_menu_id=11777 WHERE entry=43701;
UPDATE creature_template SET gossip_menu_id=11769 WHERE entry=43730;
UPDATE creature_template SET gossip_menu_id=11770 WHERE entry=43731;
UPDATE creature_template SET gossip_menu_id=11764 WHERE entry=43739;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=43766;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=43795;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=43796;
UPDATE creature_template SET gossip_menu_id=699 WHERE entry=43840;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=43870;
UPDATE creature_template SET gossip_menu_id=12821 WHERE entry=43881;
UPDATE creature_template SET gossip_menu_id=12821 WHERE entry=43883;
UPDATE creature_template SET gossip_menu_id=12821 WHERE entry=43892;
UPDATE creature_template SET gossip_menu_id=349 WHERE entry=43945;
UPDATE creature_template SET gossip_menu_id=1582 WHERE entry=43946;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=43982;
UPDATE creature_template SET gossip_menu_id=347 WHERE entry=43993;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=43994;
UPDATE creature_template SET gossip_menu_id=11785 WHERE entry=44017;
UPDATE creature_template SET gossip_menu_id=11792 WHERE entry=44018;
UPDATE creature_template SET gossip_menu_id=342 WHERE entry=44019;
UPDATE creature_template SET gossip_menu_id=11787 WHERE entry=44021;
UPDATE creature_template SET gossip_menu_id=11801 WHERE entry=44083;
UPDATE creature_template SET gossip_menu_id=11802 WHERE entry=44084;
UPDATE creature_template SET gossip_menu_id=11809 WHERE entry=44158;
UPDATE creature_template SET gossip_menu_id=342 WHERE entry=44177;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=44231;
UPDATE creature_template SET gossip_menu_id=11821 WHERE entry=44238;
UPDATE creature_template SET gossip_menu_id=11817 WHERE entry=44249;
UPDATE creature_template SET gossip_menu_id=344 WHERE entry=44270;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=44330;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=44335;
UPDATE creature_template SET gossip_menu_id=11930 WHERE entry=44345;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=44349;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=44354;
UPDATE creature_template SET gossip_menu_id=11824 WHERE entry=44380;
UPDATE creature_template SET gossip_menu_id=11895 WHERE entry=44453;
UPDATE creature_template SET gossip_menu_id=11911 WHERE entry=44454;
UPDATE creature_template SET gossip_menu_id=11898 WHERE entry=44472;
UPDATE creature_template SET gossip_menu_id=11861 WHERE entry=44582;
UPDATE creature_template SET gossip_menu_id=11875 WHERE entry=44723;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=44725;
UPDATE creature_template SET gossip_menu_id=4463 WHERE entry=44726;
UPDATE creature_template SET gossip_menu_id=11766 WHERE entry=44735;
UPDATE creature_template SET gossip_menu_id=11878 WHERE entry=44740;
UPDATE creature_template SET gossip_menu_id=11879 WHERE entry=44743;
UPDATE creature_template SET gossip_menu_id=8521 WHERE entry=44781;
UPDATE creature_template SET gossip_menu_id=4351 WHERE entry=44783;
UPDATE creature_template SET gossip_menu_id=344 WHERE entry=44785;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=44788;
UPDATE creature_template SET gossip_menu_id=11896 WHERE entry=44869;
UPDATE creature_template SET gossip_menu_id=12152 WHERE entry=44877;
UPDATE creature_template SET gossip_menu_id=12152 WHERE entry=44878;
UPDATE creature_template SET gossip_menu_id=12443 WHERE entry=44975;
UPDATE creature_template SET gossip_menu_id=11906 WHERE entry=44978;
UPDATE creature_template SET gossip_menu_id=11908 WHERE entry=44983;
UPDATE creature_template SET gossip_menu_id=11969 WHERE entry=45015;
UPDATE creature_template SET gossip_menu_id=11912 WHERE entry=45019;
UPDATE creature_template SET gossip_menu_id=11913 WHERE entry=45023;
UPDATE creature_template SET gossip_menu_id=4105 WHERE entry=45029;
UPDATE creature_template SET gossip_menu_id=45068 WHERE entry=45068;
UPDATE creature_template SET gossip_menu_id=45069 WHERE entry=45069;
UPDATE creature_template SET gossip_menu_id=45070 WHERE entry=45070;
UPDATE creature_template SET gossip_menu_id=45071 WHERE entry=45071;
UPDATE creature_template SET gossip_menu_id=45072 WHERE entry=45072;
UPDATE creature_template SET gossip_menu_id=45073 WHERE entry=45073;
UPDATE creature_template SET gossip_menu_id=45068 WHERE entry=45074;
UPDATE creature_template SET gossip_menu_id=45069 WHERE entry=45075;
UPDATE creature_template SET gossip_menu_id=45073 WHERE entry=45076;
UPDATE creature_template SET gossip_menu_id=45072 WHERE entry=45077;
UPDATE creature_template SET gossip_menu_id=45070 WHERE entry=45078;
UPDATE creature_template SET gossip_menu_id=45071 WHERE entry=45079;
UPDATE creature_template SET gossip_menu_id=11919 WHERE entry=45086;
UPDATE creature_template SET gossip_menu_id=12050 WHERE entry=45095;
UPDATE creature_template SET gossip_menu_id=4521 WHERE entry=45137;
UPDATE creature_template SET gossip_menu_id=11932 WHERE entry=45138;
UPDATE creature_template SET gossip_menu_id=11934 WHERE entry=45148;
UPDATE creature_template SET gossip_menu_id=11936 WHERE entry=45149;
UPDATE creature_template SET gossip_menu_id=11940 WHERE entry=45151;
UPDATE creature_template SET gossip_menu_id=11942 WHERE entry=45152;
UPDATE creature_template SET gossip_menu_id=11951 WHERE entry=45211;
UPDATE creature_template SET gossip_menu_id=11970 WHERE entry=45226;
UPDATE creature_template SET gossip_menu_id=12563 WHERE entry=45244;
UPDATE creature_template SET gossip_menu_id=6649 WHERE entry=45337;
UPDATE creature_template SET gossip_menu_id=4544 WHERE entry=45339;
UPDATE creature_template SET gossip_menu_id=12010 WHERE entry=45347;
UPDATE creature_template SET gossip_menu_id=12034 WHERE entry=45451;
UPDATE creature_template SET gossip_menu_id=12033 WHERE entry=45500;
UPDATE creature_template SET gossip_menu_id=4351 WHERE entry=45559;
UPDATE creature_template SET gossip_menu_id=12040 WHERE entry=45563;
UPDATE creature_template SET gossip_menu_id=12344 WHERE entry=45709;
UPDATE creature_template SET gossip_menu_id=12048 WHERE entry=45713;
UPDATE creature_template SET gossip_menu_id=12049 WHERE entry=45714;
UPDATE creature_template SET gossip_menu_id=12051 WHERE entry=45717;
UPDATE creature_template SET gossip_menu_id=12052 WHERE entry=45718;
UPDATE creature_template SET gossip_menu_id=12053 WHERE entry=45720;
UPDATE creature_template SET gossip_menu_id=12054 WHERE entry=45752;
UPDATE creature_template SET gossip_menu_id=12103 WHERE entry=45786;
UPDATE creature_template SET gossip_menu_id=12106 WHERE entry=45789;
UPDATE creature_template SET gossip_menu_id=1951 WHERE entry=45814;
UPDATE creature_template SET gossip_menu_id=1951 WHERE entry=45827;
UPDATE creature_template SET gossip_menu_id=12061 WHERE entry=45831;
UPDATE creature_template SET gossip_menu_id=12058 WHERE entry=45874;
UPDATE creature_template SET gossip_menu_id=12462 WHERE entry=46006;
UPDATE creature_template SET gossip_menu_id=12081 WHERE entry=46022;
UPDATE creature_template SET gossip_menu_id=12084 WHERE entry=46078;
UPDATE creature_template SET gossip_menu_id=12085 WHERE entry=46082;
UPDATE creature_template SET gossip_menu_id=13329 WHERE entry=46180;
UPDATE creature_template SET gossip_menu_id=13330 WHERE entry=46181;
UPDATE creature_template SET gossip_menu_id=12100 WHERE entry=46269;
UPDATE creature_template SET gossip_menu_id=12346 WHERE entry=46274;
UPDATE creature_template SET gossip_menu_id=12104 WHERE entry=46293;
UPDATE creature_template SET gossip_menu_id=7690 WHERE entry=46357;
UPDATE creature_template SET gossip_menu_id=1582 WHERE entry=46642;
UPDATE creature_template SET gossip_menu_id=12229 WHERE entry=46650;
UPDATE creature_template SET gossip_menu_id=12148 WHERE entry=46654;
UPDATE creature_template SET gossip_menu_id=10181 WHERE entry=46659;
UPDATE creature_template SET gossip_menu_id=12151 WHERE entry=46667;
UPDATE creature_template SET gossip_menu_id=7691 WHERE entry=46741;
UPDATE creature_template SET gossip_menu_id=12149 WHERE entry=46760;
UPDATE creature_template SET gossip_menu_id=12146 WHERE entry=46768;
UPDATE creature_template SET gossip_menu_id=12147 WHERE entry=46769;
UPDATE creature_template SET gossip_menu_id=12225 WHERE entry=46930;
UPDATE creature_template SET gossip_menu_id=11817 WHERE entry=46983;
UPDATE creature_template SET gossip_menu_id=141 WHERE entry=47233;
UPDATE creature_template SET gossip_menu_id=12420 WHERE entry=47240;
UPDATE creature_template SET gossip_menu_id=12233 WHERE entry=47246;
UPDATE creature_template SET gossip_menu_id=12233 WHERE entry=47247;
UPDATE creature_template SET gossip_menu_id=12233 WHERE entry=47248;
UPDATE creature_template SET gossip_menu_id=12347 WHERE entry=47250;
UPDATE creature_template SET gossip_menu_id=12240 WHERE entry=47321;
UPDATE creature_template SET gossip_menu_id=9868 WHERE entry=47334;
UPDATE creature_template SET gossip_menu_id=9868 WHERE entry=47367;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=47368;
UPDATE creature_template SET gossip_menu_id=12260 WHERE entry=47383;
UPDATE creature_template SET gossip_menu_id=12186 WHERE entry=47419;
UPDATE creature_template SET gossip_menu_id=12180 WHERE entry=47420;
UPDATE creature_template SET gossip_menu_id=12265 WHERE entry=47434;
UPDATE creature_template SET gossip_menu_id=11821 WHERE entry=47569;
UPDATE creature_template SET gossip_menu_id=12410 WHERE entry=47571;
UPDATE creature_template SET gossip_menu_id=11821 WHERE entry=47572;
UPDATE creature_template SET gossip_menu_id=13329 WHERE entry=47584;
UPDATE creature_template SET gossip_menu_id=13330 WHERE entry=47589;
UPDATE creature_template SET gossip_menu_id=12331 WHERE entry=47718;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=47764;
UPDATE creature_template SET gossip_menu_id=12341 WHERE entry=47767;
UPDATE creature_template SET gossip_menu_id=4783 WHERE entry=47771;
UPDATE creature_template SET gossip_menu_id=12341 WHERE entry=47788;
UPDATE creature_template SET gossip_menu_id=6944 WHERE entry=47875;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=47934;
UPDATE creature_template SET gossip_menu_id=12376 WHERE entry=48001;
UPDATE creature_template SET gossip_menu_id=12437 WHERE entry=48033;
UPDATE creature_template SET gossip_menu_id=9868 WHERE entry=48054;
UPDATE creature_template SET gossip_menu_id=9821 WHERE entry=48055;
UPDATE creature_template SET gossip_menu_id=9868 WHERE entry=48093;
UPDATE creature_template SET gossip_menu_id=12422 WHERE entry=48250;
UPDATE creature_template SET gossip_menu_id=12421 WHERE entry=48254;
UPDATE creature_template SET gossip_menu_id=12419 WHERE entry=48255;
UPDATE creature_template SET gossip_menu_id=12435 WHERE entry=48306;
UPDATE creature_template SET gossip_menu_id=12434 WHERE entry=48307;
UPDATE creature_template SET gossip_menu_id=12439 WHERE entry=48510;
UPDATE creature_template SET gossip_menu_id=9848 WHERE entry=48617;
UPDATE creature_template SET gossip_menu_id=12458 WHERE entry=48726;
UPDATE creature_template SET gossip_menu_id=12464 WHERE entry=48948;
UPDATE creature_template SET gossip_menu_id=12475 WHERE entry=48949;
UPDATE creature_template SET gossip_menu_id=12475 WHERE entry=48961;
UPDATE creature_template SET gossip_menu_id=12593 WHERE entry=48965;
UPDATE creature_template SET gossip_menu_id=12476 WHERE entry=49150;
UPDATE creature_template SET gossip_menu_id=12503 WHERE entry=49407;
UPDATE creature_template SET gossip_menu_id=10605 WHERE entry=49573;
UPDATE creature_template SET gossip_menu_id=12511 WHERE entry=49635;
UPDATE creature_template SET gossip_menu_id=12590 WHERE entry=49687;
UPDATE creature_template SET gossip_menu_id=12513 WHERE entry=49736;
UPDATE creature_template SET gossip_menu_id=12516 WHERE entry=49741;
UPDATE creature_template SET gossip_menu_id=12517 WHERE entry=49745;
UPDATE creature_template SET gossip_menu_id=4666 WHERE entry=49749;
UPDATE creature_template SET gossip_menu_id=12522 WHERE entry=49769;
UPDATE creature_template SET gossip_menu_id=12523 WHERE entry=49781;
UPDATE creature_template SET gossip_menu_id=12524 WHERE entry=49782;
UPDATE creature_template SET gossip_menu_id=3642 WHERE entry=49784;
UPDATE creature_template SET gossip_menu_id=12525 WHERE entry=49786;
UPDATE creature_template SET gossip_menu_id=12526 WHERE entry=49791;
UPDATE creature_template SET gossip_menu_id=12528 WHERE entry=49806;
UPDATE creature_template SET gossip_menu_id=12529 WHERE entry=49808;
UPDATE creature_template SET gossip_menu_id=12530 WHERE entry=49856;
UPDATE creature_template SET gossip_menu_id=12053 WHERE entry=49895;
UPDATE creature_template SET gossip_menu_id=12049 WHERE entry=49896;
UPDATE creature_template SET gossip_menu_id=12052 WHERE entry=49900;
UPDATE creature_template SET gossip_menu_id=12596 WHERE entry=49934;
UPDATE creature_template SET gossip_menu_id=12536 WHERE entry=49939;
UPDATE creature_template SET gossip_menu_id=12537 WHERE entry=49940;
UPDATE creature_template SET gossip_menu_id=12539 WHERE entry=49942;
UPDATE creature_template SET gossip_menu_id=4463 WHERE entry=49968;
UPDATE creature_template SET gossip_menu_id=11932 WHERE entry=49998;
UPDATE creature_template SET gossip_menu_id=3644 WHERE entry=50001;
UPDATE creature_template SET gossip_menu_id=11933 WHERE entry=50002;
UPDATE creature_template SET gossip_menu_id=11912 WHERE entry=50006;
UPDATE creature_template SET gossip_menu_id=12050 WHERE entry=50015;
UPDATE creature_template SET gossip_menu_id=4104 WHERE entry=50022;
UPDATE creature_template SET gossip_menu_id=12543 WHERE entry=50027;
UPDATE creature_template SET gossip_menu_id=4602 WHERE entry=50028;
UPDATE creature_template SET gossip_menu_id=12233 WHERE entry=50029;
UPDATE creature_template SET gossip_menu_id=3644 WHERE entry=50031;
UPDATE creature_template SET gossip_menu_id=12341 WHERE entry=50032;
UPDATE creature_template SET gossip_menu_id=523 WHERE entry=50033;
UPDATE creature_template SET gossip_menu_id=11877 WHERE entry=50034;
UPDATE creature_template SET gossip_menu_id=11767 WHERE entry=50035;
UPDATE creature_template SET gossip_menu_id=12552 WHERE entry=50043;
UPDATE creature_template SET gossip_menu_id=12642 WHERE entry=50480;
UPDATE creature_template SET gossip_menu_id=11817 WHERE entry=50497;
UPDATE creature_template SET gossip_menu_id=12517 WHERE entry=50498;
UPDATE creature_template SET gossip_menu_id=12513 WHERE entry=50500;
UPDATE creature_template SET gossip_menu_id=12714 WHERE entry=50501;
UPDATE creature_template SET gossip_menu_id=12882 WHERE entry=50502;
UPDATE creature_template SET gossip_menu_id=12537 WHERE entry=50504;
UPDATE creature_template SET gossip_menu_id=12539 WHERE entry=50505;
UPDATE creature_template SET gossip_menu_id=12539 WHERE entry=50506;
UPDATE creature_template SET gossip_menu_id=12539 WHERE entry=50507;
UPDATE creature_template SET gossip_menu_id=12606 WHERE entry=50690;
UPDATE creature_template SET gossip_menu_id=4103 WHERE entry=51637;
UPDATE creature_template SET gossip_menu_id=12706 WHERE entry=51664;
UPDATE creature_template SET gossip_menu_id=12725 WHERE entry=51997;
UPDATE creature_template SET gossip_menu_id=12793 WHERE entry=52190;
UPDATE creature_template SET gossip_menu_id=12754 WHERE entry=52207;
UPDATE creature_template SET gossip_menu_id=7357 WHERE entry=52292;
UPDATE creature_template SET gossip_menu_id=12755 WHERE entry=52335;
UPDATE creature_template SET gossip_menu_id=12759 WHERE entry=52358;
UPDATE creature_template SET gossip_menu_id=8517 WHERE entry=52636;
UPDATE creature_template SET gossip_menu_id=8521 WHERE entry=52640;
UPDATE creature_template SET gossip_menu_id=7690 WHERE entry=52642;
UPDATE creature_template SET gossip_menu_id=13014 WHERE entry=52651;
UPDATE creature_template SET gossip_menu_id=7815 WHERE entry=52657;
UPDATE creature_template SET gossip_menu_id=12642 WHERE entry=52658;
UPDATE creature_template SET gossip_menu_id=12759 WHERE entry=52809;
UPDATE creature_template SET gossip_menu_id=12803 WHERE entry=53081;
UPDATE creature_template SET gossip_menu_id=12841 WHERE entry=53403;
UPDATE creature_template SET gossip_menu_id=12845 WHERE entry=53404;
UPDATE creature_template SET gossip_menu_id=12529 WHERE entry=53405;
UPDATE creature_template SET gossip_menu_id=12843 WHERE entry=53410;
UPDATE creature_template SET gossip_menu_id=12844 WHERE entry=53415;
UPDATE creature_template SET gossip_menu_id=12850 WHERE entry=53421;
UPDATE creature_template SET gossip_menu_id=12852 WHERE entry=53436;
UPDATE creature_template SET gossip_menu_id=12838 WHERE entry=54232;
UPDATE creature_template SET gossip_menu_id=13012 WHERE entry=54485;
UPDATE creature_template SET gossip_menu_id=13018 WHERE entry=54601;
UPDATE creature_template SET gossip_menu_id=13075 WHERE entry=55396;
UPDATE creature_template SET gossip_menu_id=13210 WHERE entry=56041;
UPDATE creature_template SET gossip_menu_id=13352 WHERE entry=57850;








DELETE FROM npc_text WHERE ID=6;
INSERT INTO npc_text (ID) VALUE (6);
UPDATE npc_text SET Text0_0="Hundreds of various diagrams and schematics begin to take shape on the pages of the book. You recognize some of the diagrams while others remain foreign but familiar.", Text0_1="Hundreds of various diagrams and schematics begin to take shape on the pages of the book. You recognize some of the diagrams while others remain foreign but familiar.", BroadcastTextID0=11875 WHERE ID=6;

DELETE FROM npc_text WHERE ID=7;
INSERT INTO npc_text (ID) VALUE (7);
UPDATE npc_text SET Text0_0="The assortment of images, shapes, and markings come together before your eyes. The book seems to know your skill with leatherworking and offers you a choice - but be warned - you may only select one and once you have done so, may not change your mind!:", Text0_1="The assortment of images, shapes, and markings come together before your eyes. The book seems to know your skill with leatherworking and offers you a choice - but be warned - you may only select one and once you have done so, may not change your mind!:", BroadcastTextID0=11892 WHERE ID=7;

DELETE FROM npc_text WHERE ID=18;
INSERT INTO npc_text (ID) VALUE (18);
UPDATE npc_text SET Text0_0="Stay by my side, $N. We may have need of one another.", BroadcastTextID0=56609, prob0=1 WHERE ID=18;

DELETE FROM npc_text WHERE ID=24;
INSERT INTO npc_text (ID) VALUE (24);
UPDATE npc_text SET Text0_0="Ah, $N! A little bird told me you would be coming.$B$BThat's how Aviana sends messages around.", BroadcastTextID0=40543, prob0=1, em0_0=3, em0_1=3, em0_2=3, em0_3=3, em0_4=3, em0_5=3 WHERE ID=24;

DELETE FROM npc_text WHERE ID=34;
INSERT INTO npc_text (ID) VALUE (34);
UPDATE npc_text SET Text0_0="Which profession?", Text0_1="Which profession?", BroadcastTextID0=6775, lang0=1, prob0=100 WHERE ID=34;

DELETE FROM npc_text WHERE ID=42;
INSERT INTO npc_text (ID) VALUE (42);
UPDATE npc_text SET Text0_0="Deathwing has returned. He's seized Grim Batol and much of the highlands, and I feel near powerless to stop him.$B$BSoon, our queen shall arrive, and together we shall put the once Earthwarder in his place.", BroadcastTextID0=46055, prob0=1 WHERE ID=42;

DELETE FROM npc_text WHERE ID=48;
INSERT INTO npc_text (ID) VALUE (48);
UPDATE npc_text SET Text0_0="How may I help you?", Text0_1="How may I help you?", BroadcastTextID0=62303, Text1_0="How may I help you?", Text1_1="How may I help you?", BroadcastTextID1=30864, Text2_0="How may I help you?", Text2_1="How may I help you?", BroadcastTextID2=30864, em2_0=3, em2_1=3, em2_2=3, em2_3=3, em2_4=3, em2_5=3 WHERE ID=48;

DELETE FROM npc_text WHERE ID=82;
INSERT INTO npc_text (ID) VALUE (82);
UPDATE npc_text SET Text0_0="Serve the Dragonmaw and you will be handsomely rewarded, $c.", BroadcastTextID0=50398 WHERE ID=82;

DELETE FROM npc_text WHERE ID=107;
INSERT INTO npc_text (ID) VALUE (107);
UPDATE npc_text SET Text0_1="Yeah? Whadya", BroadcastTextID0=36370 WHERE ID=107;

DELETE FROM npc_text WHERE ID=134;
INSERT INTO npc_text (ID) VALUE (134);
UPDATE npc_text SET Text0_0="The Horde war machine needs you!", BroadcastTextID0=46528, prob0=1 WHERE ID=134;

DELETE FROM npc_text WHERE ID=141;
INSERT INTO npc_text (ID) VALUE (141);
UPDATE npc_text SET Text0_1="I am new to the burdens of leadership. I should've seen Narkrall's insubordination coming. Instead I am cleaning up his mess.$B$BI don't know how Garrosh Hellscream does it. He must possess great strength to hold together a force as diverse as the Horde... I should like to know him more.", BroadcastTextID0=47896, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=141;

DELETE FROM npc_text WHERE ID=153;
INSERT INTO npc_text (ID) VALUE (153);
UPDATE npc_text SET Text0_0="Heya, $g champ : lady;. What's shakin'?", BroadcastTextID0=50704, em0_0=6, em0_1=6, em0_2=6, em0_3=6, em0_4=6, em0_5=6 WHERE ID=153;

DELETE FROM npc_text WHERE ID=158;
INSERT INTO npc_text (ID) VALUE (158);
UPDATE npc_text SET Text0_1="Welcome, $c.$B$BHyjal burns and the world I've spent my life protecting is on the brink of oblivion.$B$BTell me: Have you ever heard of Tyrus Blackhorn?", BroadcastTextID0=39998 WHERE ID=158;

DELETE FROM npc_text WHERE ID=166;
INSERT INTO npc_text (ID) VALUE (166);
UPDATE npc_text SET Text0_0="We came here for war.$B$BThey gave it to us.", BroadcastTextID0=53249 WHERE ID=166;

DELETE FROM npc_text WHERE ID=185;
INSERT INTO npc_text (ID) VALUE (185);
UPDATE npc_text SET Text0_0="You may rest here, if you like. The Temple of Earth is under our care, now.", BroadcastTextID0=45514, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=185;

DELETE FROM npc_text WHERE ID=194;
INSERT INTO npc_text (ID) VALUE (194);
UPDATE npc_text SET Text0_0="Welcome to my Inn, weary traveler. What can I do for you?", Text0_1="Welcome to my Inn, weary traveler. What can I do for you?", BroadcastTextID0=16967, em0_0=396, em0_1=396, em0_2=396, em0_3=396, em0_4=396, em0_5=396 WHERE ID=194;

DELETE FROM npc_text WHERE ID=215;
INSERT INTO npc_text (ID) VALUE (215);
UPDATE npc_text SET Text0_1="We've long held out hope of redeeming the Earthwarden and his children. At some point, we must have the wisdom to realize that no amount of redemption can atone for the destruction these dragons are unleashing upon the world.$B$BAt some point, we are forced to intervene.", BroadcastTextID0=48153 WHERE ID=215;

DELETE FROM npc_text WHERE ID=225;
INSERT INTO npc_text (ID) VALUE (225);
UPDATE npc_text SET Text0_0="In all my days, $r, I've never seen such a thing...", BroadcastTextID0=41575, Text1_0="We are poorly equipped to do battle here.$b$bPreparations must be made...", BroadcastTextID1=41576, prob1=1 WHERE ID=225;

DELETE FROM npc_text WHERE ID=246;
INSERT INTO npc_text (ID) VALUE (246);
UPDATE npc_text SET Text0_0="Let's get out there and put those stone troggs back into the ground, $r!", BroadcastTextID0=43197, prob0=1 WHERE ID=246;

DELETE FROM npc_text WHERE ID=247;
INSERT INTO npc_text (ID) VALUE (247);
UPDATE npc_text SET Text0_0="I need you out on the front, $N.$B$BYou're going to make the difference. We'll crush the stone troggs once and for all.$B$BWe must rescue King Oremantle!", BroadcastTextID0=43199, prob0=1, em0_0=396, em0_1=396, em0_2=396, em0_3=396, em0_4=396, em0_5=396 WHERE ID=247;

DELETE FROM npc_text WHERE ID=248;
INSERT INTO npc_text (ID) VALUE (248);
UPDATE npc_text SET Text0_0="<Clay grumbles and sneers.>$B$BDamn kids these days.", BroadcastTextID0=43201 WHERE ID=248;

DELETE FROM npc_text WHERE ID=1244;
INSERT INTO npc_text (ID) VALUE (1244);
UPDATE npc_text SET Text0_0="Well, if it isn't a young, bristling $c, no doubt drawn here by talk of my exploits in fields of battle!$B$BNo time for stories now, for there are great, important deeds that need doing!  So if you're looking for glory, then luck shines on you today...", Text0_1="Well, if it isn't a young, bristling $c, no doubt drawn here by talk of my exploits in fields of battle!$B$BNo time for stories now, for there are great, important deeds that need doing!  So if you're looking for glory, then luck shines on you today...", prob0=1 WHERE ID=1244;

DELETE FROM npc_text WHERE ID=3841;
INSERT INTO npc_text (ID) VALUE (3841);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=3841;

DELETE FROM npc_text WHERE ID=6157;
INSERT INTO npc_text (ID) VALUE (6157);
UPDATE npc_text SET Text0_0="Hey there, friend. My name's Remy. I'm from Redridge to the east, and came here looking for business, looking for business. You got any...got any??", Text0_1="Hey there, friend. My name's Remy. I'm from Redridge to the east, and came here looking for business, looking for business. You got any...got any??", prob0=1 WHERE ID=6157;

DELETE FROM npc_text WHERE ID=7774;
INSERT INTO npc_text (ID) VALUE (7774);
UPDATE npc_text SET Text0_0="A thunderous voice bellows from the stone...$B$BGreetings, commander. What news of Silithus do you bring the Lords of the Council?", Text0_1="A thunderous voice bellows from the stone...$B$BGreetings, commander. What news of Silithus do you bring the Lords of the Council?", BroadcastTextID0=10706, prob0=1 WHERE ID=7774;

DELETE FROM npc_text WHERE ID=8955;
INSERT INTO npc_text (ID) VALUE (8955);
UPDATE npc_text SET Text0_0="Are you ready, $n?", BroadcastTextID0=14012, prob0=1 WHERE ID=8955;

DELETE FROM npc_text WHERE ID=9068;
INSERT INTO npc_text (ID) VALUE (9068);
UPDATE npc_text SET Text0_0="How did you learn about the ore? Not even the Baron knew...$B$BTake the cursed things. They've brought me nothing but misfortune anyway. I hid them IN the stables just off the courtyard.$B$B<A low growl begins TO emanate FROM the back of Landen's throat.>", BroadcastTextID0=14393, prob0=1, em0_0=20, em0_1=20, em0_2=20, em0_3=20, em0_4=20, em0_5=20 WHERE ID=9068;

DELETE FROM npc_text WHERE ID=14289;
INSERT INTO npc_text (ID) VALUE (14289);
UPDATE npc_text SET Text0_0="<Allyndia's body bobs gently in the surf. It appears that she's been dead for some time.>", Text0_1="<Allyndia's body bobs gently in the surf. It appears that she's been dead for some time.>", BroadcastTextID0=33146, prob0=1 WHERE ID=14289;

DELETE FROM npc_text WHERE ID=14569;
INSERT INTO npc_text (ID) VALUE (14569);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=14569;

DELETE FROM npc_text WHERE ID=14699;
INSERT INTO npc_text (ID) VALUE (14699);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=14699;

DELETE FROM npc_text WHERE ID=14701;
INSERT INTO npc_text (ID) VALUE (14701);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=14701;

DELETE FROM npc_text WHERE ID=14704;
INSERT INTO npc_text (ID) VALUE (14704);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=14704;

DELETE FROM npc_text WHERE ID=14863;
INSERT INTO npc_text (ID) VALUE (14863);
UPDATE npc_text SET Text0_0="I'm leaving for the next rendezvous point in a few seconds.", BroadcastTextID0=36127, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=14863;

DELETE FROM npc_text WHERE ID=14954;
INSERT INTO npc_text (ID) VALUE (14954);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=14954;

DELETE FROM npc_text WHERE ID=14957;
INSERT INTO npc_text (ID) VALUE (14957);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=14957;

DELETE FROM npc_text WHERE ID=15362;
INSERT INTO npc_text (ID) VALUE (15362);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=15362;

DELETE FROM npc_text WHERE ID=15382;
INSERT INTO npc_text (ID) VALUE (15382);
UPDATE npc_text SET Text0_1="He's truly gone, isn't he?$b$bI... I can feel it.", BroadcastTextID0=38510, prob0=1, Text1_1="Was there truly no way to save him?$b$bI fear I shall always wonder.", BroadcastTextID1=38511, prob1=1 WHERE ID=15382;

DELETE FROM npc_text WHERE ID=15427;
INSERT INTO npc_text (ID) VALUE (15427);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15427;

DELETE FROM npc_text WHERE ID=15520;
INSERT INTO npc_text (ID) VALUE (15520);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15520;

DELETE FROM npc_text WHERE ID=15521;
INSERT INTO npc_text (ID) VALUE (15521);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15521;

DELETE FROM npc_text WHERE ID=15522;
INSERT INTO npc_text (ID) VALUE (15522);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15522;

DELETE FROM npc_text WHERE ID=15525;
INSERT INTO npc_text (ID) VALUE (15525);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15525;

DELETE FROM npc_text WHERE ID=15546;
INSERT INTO npc_text (ID) VALUE (15546);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15546;

DELETE FROM npc_text WHERE ID=15587;
INSERT INTO npc_text (ID) VALUE (15587);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15587;

DELETE FROM npc_text WHERE ID=15619;
INSERT INTO npc_text (ID) VALUE (15619);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15619;

DELETE FROM npc_text WHERE ID=15682;
INSERT INTO npc_text (ID) VALUE (15682);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15682;

DELETE FROM npc_text WHERE ID=15737;
INSERT INTO npc_text (ID) VALUE (15737);
UPDATE npc_text SET Text0_0="Hi. Yeah, I know. I got captured again.$B$BI don't want to talk about it.$B$BYou ready?", BroadcastTextID0=39805, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=15737;

DELETE FROM npc_text WHERE ID=15739;
INSERT INTO npc_text (ID) VALUE (15739);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=15739;

DELETE FROM npc_text WHERE ID=15841;
INSERT INTO npc_text (ID) VALUE (15841);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15841;

DELETE FROM npc_text WHERE ID=15904;
INSERT INTO npc_text (ID) VALUE (15904);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=15904;

DELETE FROM npc_text WHERE ID=16221;
INSERT INTO npc_text (ID) VALUE (16221);
UPDATE npc_text SET Text0_1="Greetings, $N. I can offer you training in the way of the mage.", BroadcastTextID0=42243, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=16221;

DELETE FROM npc_text WHERE ID=16231;
INSERT INTO npc_text (ID) VALUE (16231);
UPDATE npc_text SET Text0_0="<These baby Rockpool murlocs look toward the ocean.>", BroadcastTextID0=42289, prob0=1 WHERE ID=16231;

DELETE FROM npc_text WHERE ID=16271;
INSERT INTO npc_text (ID) VALUE (16271);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=16271;

DELETE FROM npc_text WHERE ID=16396;
INSERT INTO npc_text (ID) VALUE (16396);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=16396;

DELETE FROM npc_text WHERE ID=16660;
INSERT INTO npc_text (ID) VALUE (16660);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=16660;

DELETE FROM npc_text WHERE ID=16776;
INSERT INTO npc_text (ID) VALUE (16776);
UPDATE npc_text SET Text0_0="Thought I couldn't handle them? Don't let my size be follin' ya. Anyway, thanks for the hand.", BroadcastTextID0=45356, prob0=1 WHERE ID=16776;

DELETE FROM npc_text WHERE ID=16817;
INSERT INTO npc_text (ID) VALUE (16817);
UPDATE npc_text SET Text0_1="Welcome ta Moonglade, $c. All be welcome 'ere, as long as ya be keepin' the sacred peace.", BroadcastTextID0=45479, prob0=1 WHERE ID=16817;

DELETE FROM npc_text WHERE ID=16859;
INSERT INTO npc_text (ID) VALUE (16859);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=16859;

DELETE FROM npc_text WHERE ID=16953;
INSERT INTO npc_text (ID) VALUE (16953);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=16953;

DELETE FROM npc_text WHERE ID=16955;
INSERT INTO npc_text (ID) VALUE (16955);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=16955;

DELETE FROM npc_text WHERE ID=17300;
INSERT INTO npc_text (ID) VALUE (17300);
UPDATE npc_text SET Text0_0="Ye'll find an Arcane Reforger in Gimble's shop, Thistlefuzz Arcanery, right by the Gryphon Master at The Great Forge.$B$BHe's one o' them long-lost Highborne elves, but he'll do ye right.", Text0_1="Ye'll find an Arcane Reforger in Gimble's shop, Thistlefuzz Arcanery, right by the Gryphon Master at The Great Forge.$B$BHe's one o' them long-lost Highborne elves, but he'll do ye right.", BroadcastTextID0=47935, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=17300;

DELETE FROM npc_text WHERE ID=17368;
INSERT INTO npc_text (ID) VALUE (17368);
UPDATE npc_text SET Text0_1="Oh... I wish I'd never come to this place!", BroadcastTextID0=48163, prob0=1 WHERE ID=17368;

DELETE FROM npc_text WHERE ID=17369;
INSERT INTO npc_text (ID) VALUE (17369);
UPDATE npc_text SET Text0_0="How did I ever get myself into this?!", BroadcastTextID0=48164, prob0=1 WHERE ID=17369;

DELETE FROM npc_text WHERE ID=17372;
INSERT INTO npc_text (ID) VALUE (17372);
UPDATE npc_text SET Text0_1="This is all too much to bear.$b$bI wish I had the nerve to... <sob>.", BroadcastTextID0=48167, prob0=1 WHERE ID=17372;

DELETE FROM npc_text WHERE ID=17482;
INSERT INTO npc_text (ID) VALUE (17482);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=17482;

DELETE FROM npc_text WHERE ID=17492;
INSERT INTO npc_text (ID) VALUE (17492);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=17492;

DELETE FROM npc_text WHERE ID=17519;
INSERT INTO npc_text (ID) VALUE (17519);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=17519;

DELETE FROM npc_text WHERE ID=17531;
INSERT INTO npc_text (ID) VALUE (17531);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=17531;

DELETE FROM npc_text WHERE ID=17639;
INSERT INTO npc_text (ID) VALUE (17639);
UPDATE npc_text SET Text0_0="This is the longest day of my life.", BroadcastTextID0=49887, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=17639;

DELETE FROM npc_text WHERE ID=17701;
INSERT INTO npc_text (ID) VALUE (17701);
UPDATE npc_text SET Text0_0="MISSING TEXT", prob0=100 WHERE ID=17701;

DELETE FROM npc_text WHERE ID=18145;
INSERT INTO npc_text (ID) VALUE (18145);
UPDATE npc_text SET Text0_0="We have managed to defend this point, and much of it is thanks to you.$B$BYou have managed to recruit a valuable ally to our ranks, however, the enemy continues to assail us without relent.$B$BWe must hold our ground or lose what we have fought so hard to gain.", BroadcastTextID0=52360, prob0=1 WHERE ID=18145;

DELETE FROM npc_text WHERE ID=18169;
INSERT INTO npc_text (ID) VALUE (18169);
UPDATE npc_text SET Text0_0="Do you prefer guns or bows?", Text0_1="Do you prefer guns or bows?", BroadcastTextID0=52385, prob0=1 WHERE ID=18169;

DELETE FROM npc_text WHERE ID=18197;
INSERT INTO npc_text (ID) VALUE (18197);
UPDATE npc_text SET Text0_1="$N, I am not surprised to see you here. I always thought you were my brightest pupil. I am honored to fight alongside you, my friend.", BroadcastTextID0=52528, prob0=1 WHERE ID=18197;

DELETE FROM npc_text WHERE ID=18238;
INSERT INTO npc_text (ID) VALUE (18238);
UPDATE npc_text SET Text0_0="If there's one thing I know, it's that you can always count on a good friend. If you have such a person in your life, cherish them well.", BroadcastTextID0=52892, prob0=1 WHERE ID=18238;

DELETE FROM npc_text WHERE ID=18241;
INSERT INTO npc_text (ID) VALUE (18241);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=18241;

DELETE FROM npc_text WHERE ID=18242;
INSERT INTO npc_text (ID) VALUE (18242);
UPDATE npc_text SET Text0_0="Do you know how many supplies it takes to support an army, $N? We need weapons, food, shelter, bandages...and that's just to start.$B$BThe supplies will not stock themselves. Ask Matoclaw if you're looking for ways to help. She will put you to use.", BroadcastTextID0=52912, prob0=1 WHERE ID=18242;

DELETE FROM npc_text WHERE ID=18262;
INSERT INTO npc_text (ID) VALUE (18262);
UPDATE npc_text SET Text0_1="Fandral Staghelm has returned as a ... \"Druid of the Flame?\"$B$BI fear one of my own may be implicated in this betrayal!", BroadcastTextID0=52956, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=18262;

DELETE FROM npc_text WHERE ID=18263;
INSERT INTO npc_text (ID) VALUE (18263);
UPDATE npc_text SET Text0_0="Yes, $c, things appear bleak. But know that even as things appear to unravel, they do so with a greater purpose.$B$B<Despite his comforting words, Nozdormu looks stricken, if not ill.>", BroadcastTextID0=52957, prob0=1, em0_0=1, em0_1=1, em0_2=1, em0_3=1, em0_4=1, em0_5=1 WHERE ID=18263;

DELETE FROM npc_text WHERE ID=18264;
INSERT INTO npc_text (ID) VALUE (18264);
UPDATE npc_text SET Text0_0="I wish I could aid you in your plight, mortal. But the blue dragonflight is in disarray, and there are other urgent matters here at the World Tree that I've been sent to investigate...", BroadcastTextID0=52958, prob0=1, em0_0=6, em0_1=6, em0_2=6, em0_3=6, em0_4=6, em0_5=6 WHERE ID=18264;

DELETE FROM npc_text WHERE ID=18265;
INSERT INTO npc_text (ID) VALUE (18265);
UPDATE npc_text SET Text0_1="The world-shaman - shattered by the hand of Fandral Staghelm?$B$BGreater powers are at work here. Ragnaros has pushed his strength farther into this realm than I would have imagined.$B$BThe Firelord must be stopped!", BroadcastTextID0=52959, prob0=1, em0_0=5, em0_1=5, em0_2=5, em0_3=5, em0_4=5, em0_5=5 WHERE ID=18265;

DELETE FROM npc_text WHERE ID=18317;
INSERT INTO npc_text (ID) VALUE (18317);
UPDATE npc_text SET Text0_0="No more games for you.", Text0_1="No more games for you.", BroadcastTextID0=53125, prob0=1, em0_0=274, em0_1=274, em0_2=274, em0_3=274, em0_4=274, em0_5=274, Text1_0="Whaddya want now?", Text1_1="Whaddya want now?", BroadcastTextID1=53126, prob1=1, em1_0=6, em1_1=6, em1_2=6, em1_3=6, em1_4=6, em1_5=6, Text2_0="Step aside and let some others have a chance to play.", Text2_1="Step aside and let some others have a chance to play.", BroadcastTextID2=53127, prob2=1, em2_0=397, em2_1=397, em2_2=397, em2_3=397, em2_4=397, em2_5=397 WHERE ID=18317;

DELETE FROM npc_text WHERE ID=18377;
INSERT INTO npc_text (ID) VALUE (18377);
UPDATE npc_text SET Text0_0="Need TXT YTDB", prob0=100 WHERE ID=18377;

DELETE FROM npc_text WHERE ID=18560;
INSERT INTO npc_text (ID) VALUE (18560);
UPDATE npc_text SET Text0_0="We just wait for guide.", Text0_1="We just wait for guide.", BroadcastTextID0=54326, prob0=1, em0_0=396, em0_1=396, em0_2=396, em0_3=396, em0_4=396, em0_5=396, Text1_0="We hope guide gets here soon.", Text1_1="We hope guide gets here soon.", BroadcastTextID1=54327, prob1=1, em1_0=1, em1_1=1, em1_2=1, em1_3=1, em1_4=1, em1_5=1 WHERE ID=18560;

DELETE FROM npc_text WHERE ID=18562;
INSERT INTO npc_text (ID) VALUE (18562);
UPDATE npc_text SET Text0_0="Are you here to lead the tour?", Text0_1="Are you here to lead the tour?", BroadcastTextID0=54330, prob0=1, em0_0=396, em0_1=396, em0_2=396, em0_3=396, em0_4=396, em0_5=396, Text1_0="Are you my tour guide?", Text1_1="Are you my tour guide?", BroadcastTextID1=54331, prob1=1, em1_0=396, em1_1=396, em1_2=396, em1_3=396, em1_4=396, em1_5=396 WHERE ID=18562;

DELETE FROM npc_text WHERE ID=18618;
INSERT INTO npc_text (ID) VALUE (18618);
UPDATE npc_text SET Text0_1="Oh, a visitor.  I don't get many visitors out here.$B$BHungry? I've cooked MANY delightful things, my dear.$B$BNo, no, not the fish. Those are for when I can't catch anything tastier, sweetling.", BroadcastTextID0=54664, prob0=1, em0_0=397, em0_1=397, em0_2=397, em0_3=397, em0_4=397, em0_5=397 WHERE ID=18618;

DELETE FROM npc_text WHERE ID=19889;
INSERT INTO npc_text (ID) VALUE (19889);
UPDATE npc_text SET Text0_0="How may I help you?", Text0_1="How may I help you?", BroadcastTextID0=61023, prob0=1 WHERE ID=19889;

DELETE FROM npc_text WHERE ID=20038;
INSERT INTO npc_text (ID) VALUE (20038);
UPDATE npc_text SET BroadcastTextID0=61847, prob0=1 WHERE ID=20038;

DELETE FROM npc_text WHERE ID=22594;
INSERT INTO npc_text (ID) VALUE (22594);
UPDATE npc_text SET BroadcastTextID0=74286, prob0=1 WHERE ID=22594;

DELETE FROM npc_text WHERE ID=50000;
INSERT INTO npc_text (ID) VALUE (50000);
UPDATE npc_text SET Text0_0="The land has been good to our people, $c. We must be thankful for our good fortune." WHERE ID=50000;

DELETE FROM npc_text WHERE ID=50081;
INSERT INTO npc_text (ID) VALUE (50081);
UPDATE npc_text SET Text0_0="You may unlearn your current Class SPecialization for a price, so that you may select a new one.$B$BThis will become more expensive each additional time you do so.", Text0_1="You may unlearn your current Class SPecialization for a price, so that you may select a new one.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50081;

DELETE FROM npc_text WHERE ID=50083;
INSERT INTO npc_text (ID) VALUE (50083);
UPDATE npc_text SET Text0_0="You may unlearn all of your current Talents for a price, so that you may select a new ones.$B$BThis will become more expensive each additional time you do so.", Text0_1="You may unlearn all of your current Talents for a price, so that you may select a new ones.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50083;

DELETE FROM npc_text WHERE ID=50084;
INSERT INTO npc_text (ID) VALUE (50084);
UPDATE npc_text SET Text0_0="You may empty all of your current Glyph slots for a price, so that you may select a new ones.$B$BThis will become more expensive each additional time you do so.", Text0_1="You may empty all of your current Glyph slots for a price, so that you may select a new ones.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50084;

DELETE FROM npc_text WHERE ID=50086;
INSERT INTO npc_text (ID) VALUE (50086);
UPDATE npc_text SET Text0_0="At level 10 you will choose a Class Specialization.$B$BIf you later decide to choose a different Class Specialization, you may reset your previous choice here for a price.$B$BThis will become more expensive each additional time you do so.", Text0_1="At level 10 you will choose a Class Specialization.$B$BIf you later decide to choose a different Class Specialization, you may reset your previous choice here for a price.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50086;

DELETE FROM npc_text WHERE ID=50087;
INSERT INTO npc_text (ID) VALUE (50087);
UPDATE npc_text SET Text0_0="At level 15 you will choose your first Talent.$B$BIf you later decide to choose different Talents, you may reset your previous choices here for a price.$B$BThis will become more expensive each additional time you do so.", Text0_1="At level 15 you will choose your first Talent.$B$BIf you later decide to choose different Talents, you may reset your previous choices here for a price.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50087;

DELETE FROM npc_text WHERE ID=50088;
INSERT INTO npc_text (ID) VALUE (50088);
UPDATE npc_text SET Text0_0="At level 25 you will begin to use Glyphs.$B$BIf you later decide to replace your chosen Glyphs, you may reset them here for a price.$B$BThis will become more expensive each additional time you do so.", Text0_1="At level 25 you will begin to use Glyphs.$B$BIf you later decide to replace your chosen Glyphs, you may reset them here for a price.$B$BThis will become more expensive each additional time you do so.", prob0=100 WHERE ID=50088;

DELETE FROM npc_text WHERE ID=50089;
INSERT INTO npc_text (ID) VALUE (50089);
UPDATE npc_text SET Text0_0="At level 30 you can learn Dual Specialization, which allows you to keep two active Class Specialization, Talent, and Glyph sets and easily switch between them.$B$BYou also will have seperate glyph panes and action bars for each set.$B$BSwitching between the two sets cannot be done while in combat and will consume your available resources.", Text0_1="At level 30 you can learn Dual Specialization, which allows you to keep two active Class Specialization, Talent, and Glyph sets and easily switch between them.$B$BYou also will have seperate glyph panes and action bars for each set.$B$BSwitching between the two sets cannot be done while in combat and will consume your available resources.", prob0=100 WHERE ID=50089;

DELETE FROM npc_text WHERE ID=53371;
INSERT INTO npc_text (ID) VALUE (53371);
UPDATE npc_text SET Text0_0="Your deeds shall live on forever in the memories of every blue dragon, $N." WHERE ID=53371;

DELETE FROM npc_text WHERE ID=53466;
INSERT INTO npc_text (ID) VALUE (53466);
UPDATE npc_text SET Text0_0="Your deeds shall live on forever in the memories of every blue dragon, $N." WHERE ID=53466;

DELETE FROM npc_text WHERE ID=55488;
INSERT INTO npc_text (ID) VALUE (55488);
UPDATE npc_text SET Text0_0="Lost. Stolen! This is a terrible blow. Terrible!" WHERE ID=55488;

DELETE FROM npc_text WHERE ID=56314;
INSERT INTO npc_text (ID) VALUE (56314);
UPDATE npc_text SET Text0_0="%N! Great work decoding the message. Let's get to the bottom of this. $B Are you ready to fly?" WHERE ID=56314;

DELETE FROM npc_text WHERE ID=57800;
INSERT INTO npc_text (ID) VALUE (57800);
UPDATE npc_text SET Text0_0="I'll do it for 10 000 gold." WHERE ID=57800;



DELETE FROM gossip_menu WHERE entry=24 AND text_id=521;
INSERT INTO gossip_menu VALUES (24, 521);
DELETE FROM gossip_menu WHERE entry=141 AND text_id=638;
INSERT INTO gossip_menu VALUES (141, 638);
DELETE FROM gossip_menu WHERE entry=231 AND text_id=720;
INSERT INTO gossip_menu VALUES (231, 720);
DELETE FROM gossip_menu WHERE entry=232 AND text_id=738;
INSERT INTO gossip_menu VALUES (232, 738);
DELETE FROM gossip_menu WHERE entry=694 AND text_id=1244;
INSERT INTO gossip_menu VALUES (694, 1244);
DELETE FROM gossip_menu WHERE entry=943 AND text_id=1521;
INSERT INTO gossip_menu VALUES (943, 1521);
DELETE FROM gossip_menu WHERE entry=944 AND text_id=1646;
INSERT INTO gossip_menu VALUES (944, 1646);
DELETE FROM gossip_menu WHERE entry=1202 AND text_id=1834;
INSERT INTO gossip_menu VALUES (1202, 1834);
DELETE FROM gossip_menu WHERE entry=1203 AND text_id=1835;
INSERT INTO gossip_menu VALUES (1203, 1835);
DELETE FROM gossip_menu WHERE entry=1204 AND text_id=1836;
INSERT INTO gossip_menu VALUES (1204, 1836);
DELETE FROM gossip_menu WHERE entry=1205 AND text_id=1837;
INSERT INTO gossip_menu VALUES (1205, 1837);
DELETE FROM gossip_menu WHERE entry=1206 AND text_id=1838;
INSERT INTO gossip_menu VALUES (1206, 1838);
DELETE FROM gossip_menu WHERE entry=1441 AND text_id=2114;
INSERT INTO gossip_menu VALUES (1441, 2114);
DELETE FROM gossip_menu WHERE entry=1483 AND text_id=2155;
INSERT INTO gossip_menu VALUES (1483, 2155);
DELETE FROM gossip_menu WHERE entry=1641 AND text_id=3073;
INSERT INTO gossip_menu VALUES (1641, 3073);
DELETE FROM gossip_menu WHERE entry=1665 AND text_id=2318;
INSERT INTO gossip_menu VALUES (1665, 2318);
DELETE FROM gossip_menu WHERE entry=1761 AND text_id=2394;
INSERT INTO gossip_menu VALUES (1761, 2394);
DELETE FROM gossip_menu WHERE entry=2184 AND text_id=2833;
INSERT INTO gossip_menu VALUES (2184, 2833);
DELETE FROM gossip_menu WHERE entry=2202 AND text_id=2834;
INSERT INTO gossip_menu VALUES (2202, 2834);
DELETE FROM gossip_menu WHERE entry=2203 AND text_id=2836;
INSERT INTO gossip_menu VALUES (2203, 2836);
DELETE FROM gossip_menu WHERE entry=2204 AND text_id=2837;
INSERT INTO gossip_menu VALUES (2204, 2837);
DELETE FROM gossip_menu WHERE entry=2205 AND text_id=2838;
INSERT INTO gossip_menu VALUES (2205, 2838);
DELETE FROM gossip_menu WHERE entry=2386 AND text_id=3056;
INSERT INTO gossip_menu VALUES (2386, 3056);
DELETE FROM gossip_menu WHERE entry=2721 AND text_id=3380;
INSERT INTO gossip_menu VALUES (2721, 3380);
DELETE FROM gossip_menu WHERE entry=2723 AND text_id=3382;
INSERT INTO gossip_menu VALUES (2723, 3382);
DELETE FROM gossip_menu WHERE entry=2724 AND text_id=3383;
INSERT INTO gossip_menu VALUES (2724, 3383);
DELETE FROM gossip_menu WHERE entry=2743 AND text_id=3398;
INSERT INTO gossip_menu VALUES (2743, 3398);
DELETE FROM gossip_menu WHERE entry=2743 AND text_id=3399;
INSERT INTO gossip_menu VALUES (2743, 3399);
DELETE FROM gossip_menu WHERE entry=2751 AND text_id=3424;
INSERT INTO gossip_menu VALUES (2751, 3424);
DELETE FROM gossip_menu WHERE entry=2752 AND text_id=3425;
INSERT INTO gossip_menu VALUES (2752, 3425);
DELETE FROM gossip_menu WHERE entry=2831 AND text_id=3522;
INSERT INTO gossip_menu VALUES (2831, 3522);
DELETE FROM gossip_menu WHERE entry=2831 AND text_id=3525;
INSERT INTO gossip_menu VALUES (2831, 3525);
DELETE FROM gossip_menu WHERE entry=2871 AND text_id=3557;
INSERT INTO gossip_menu VALUES (2871, 3557);
DELETE FROM gossip_menu WHERE entry=2872 AND text_id=3558;
INSERT INTO gossip_menu VALUES (2872, 3558);
DELETE FROM gossip_menu WHERE entry=2944 AND text_id=3656;
INSERT INTO gossip_menu VALUES (2944, 3656);
DELETE FROM gossip_menu WHERE entry=3161 AND text_id=3841;
INSERT INTO gossip_menu VALUES (3161, 3841);
DELETE FROM gossip_menu WHERE entry=3642 AND text_id=4437;
INSERT INTO gossip_menu VALUES (3642, 4437);
DELETE FROM gossip_menu WHERE entry=3665 AND text_id=5733;
INSERT INTO gossip_menu VALUES (3665, 5733);
DELETE FROM gossip_menu WHERE entry=3666 AND text_id=5734;
INSERT INTO gossip_menu VALUES (3666, 5734);
DELETE FROM gossip_menu WHERE entry=3667 AND text_id=5735;
INSERT INTO gossip_menu VALUES (3667, 5735);
DELETE FROM gossip_menu WHERE entry=3668 AND text_id=5736;
INSERT INTO gossip_menu VALUES (3668, 5736);
DELETE FROM gossip_menu WHERE entry=3669 AND text_id=5737;
INSERT INTO gossip_menu VALUES (3669, 5737);
DELETE FROM gossip_menu WHERE entry=3670 AND text_id=5738;
INSERT INTO gossip_menu VALUES (3670, 5738);
DELETE FROM gossip_menu WHERE entry=3781 AND text_id=6846;
INSERT INTO gossip_menu VALUES (3781, 6846);
DELETE FROM gossip_menu WHERE entry=3881 AND text_id=4721;
INSERT INTO gossip_menu VALUES (3881, 4721);
DELETE FROM gossip_menu WHERE entry=3882 AND text_id=4719;
INSERT INTO gossip_menu VALUES (3882, 4719);
DELETE FROM gossip_menu WHERE entry=3883 AND text_id=4733;
INSERT INTO gossip_menu VALUES (3883, 4733);
DELETE FROM gossip_menu WHERE entry=3884 AND text_id=4734;
INSERT INTO gossip_menu VALUES (3884, 4734);
DELETE FROM gossip_menu WHERE entry=3885 AND text_id=4735;
INSERT INTO gossip_menu VALUES (3885, 4735);
DELETE FROM gossip_menu WHERE entry=4011 AND text_id=4867;
INSERT INTO gossip_menu VALUES (4011, 4867);
DELETE FROM gossip_menu WHERE entry=4091 AND text_id=4993;
INSERT INTO gossip_menu VALUES (4091, 4993);
DELETE FROM gossip_menu WHERE entry=4110 AND text_id=5013;
INSERT INTO gossip_menu VALUES (4110, 5013);
DELETE FROM gossip_menu WHERE entry=4110 AND text_id=5014;
INSERT INTO gossip_menu VALUES (4110, 5014);
DELETE FROM gossip_menu WHERE entry=4111 AND text_id=5022;
INSERT INTO gossip_menu VALUES (4111, 5022);
DELETE FROM gossip_menu WHERE entry=4111 AND text_id=5023;
INSERT INTO gossip_menu VALUES (4111, 5023);
DELETE FROM gossip_menu WHERE entry=4117 AND text_id=5051;
INSERT INTO gossip_menu VALUES (4117, 5051);
DELETE FROM gossip_menu WHERE entry=4117 AND text_id=5059;
INSERT INTO gossip_menu VALUES (4117, 5059);
DELETE FROM gossip_menu WHERE entry=4186 AND text_id=5288;
INSERT INTO gossip_menu VALUES (4186, 5288);
DELETE FROM gossip_menu WHERE entry=4223 AND text_id=5373;
INSERT INTO gossip_menu VALUES (4223, 5373);
DELETE FROM gossip_menu WHERE entry=4224 AND text_id=5374;
INSERT INTO gossip_menu VALUES (4224, 5374);
DELETE FROM gossip_menu WHERE entry=4225 AND text_id=5375;
INSERT INTO gossip_menu VALUES (4225, 5375);
DELETE FROM gossip_menu WHERE entry=4226 AND text_id=5376;
INSERT INTO gossip_menu VALUES (4226, 5376);
DELETE FROM gossip_menu WHERE entry=4263 AND text_id=5419;
INSERT INTO gossip_menu VALUES (4263, 5419);
DELETE FROM gossip_menu WHERE entry=4263 AND text_id=5421;
INSERT INTO gossip_menu VALUES (4263, 5421);
DELETE FROM gossip_menu WHERE entry=4463 AND text_id=3976;
INSERT INTO gossip_menu VALUES (4463, 3976);
DELETE FROM gossip_menu WHERE entry=4463 AND text_id=3977;
INSERT INTO gossip_menu VALUES (4463, 3977);
DELETE FROM gossip_menu WHERE entry=4570 AND text_id=1215;
INSERT INTO gossip_menu VALUES (4570, 1215);
DELETE FROM gossip_menu WHERE entry=4576 AND text_id=4795;
INSERT INTO gossip_menu VALUES (4576, 4795);
DELETE FROM gossip_menu WHERE entry=4578 AND text_id=1217;
INSERT INTO gossip_menu VALUES (4578, 1217);
DELETE FROM gossip_menu WHERE entry=4579 AND text_id=1217;
INSERT INTO gossip_menu VALUES (4579, 1217);
DELETE FROM gossip_menu WHERE entry=4581 AND text_id=1217;
INSERT INTO gossip_menu VALUES (4581, 1217);
DELETE FROM gossip_menu WHERE entry=4646 AND text_id=5716;
INSERT INTO gossip_menu VALUES (4646, 5716);
DELETE FROM gossip_menu WHERE entry=4690 AND text_id=4793;
INSERT INTO gossip_menu VALUES (4690, 4793);
DELETE FROM gossip_menu WHERE entry=4696 AND text_id=1217;
INSERT INTO gossip_menu VALUES (4696, 1217);
DELETE FROM gossip_menu WHERE entry=4697 AND text_id=1217;
INSERT INTO gossip_menu VALUES (4697, 1217);
DELETE FROM gossip_menu WHERE entry=5002 AND text_id=6058;
INSERT INTO gossip_menu VALUES (5002, 6058);
DELETE FROM gossip_menu WHERE entry=5003 AND text_id=6061;
INSERT INTO gossip_menu VALUES (5003, 6061);
DELETE FROM gossip_menu WHERE entry=5032 AND text_id=6157;
INSERT INTO gossip_menu VALUES (5032, 6157);
DELETE FROM gossip_menu WHERE entry=5065 AND text_id=6109;
INSERT INTO gossip_menu VALUES (5065, 6109);
DELETE FROM gossip_menu WHERE entry=5065 AND text_id=6158;
INSERT INTO gossip_menu VALUES (5065, 6158);
DELETE FROM gossip_menu WHERE entry=5065 AND text_id=8541;
INSERT INTO gossip_menu VALUES (5065, 8541);
DELETE FROM gossip_menu WHERE entry=5065 AND text_id=8542;
INSERT INTO gossip_menu VALUES (5065, 8542);
DELETE FROM gossip_menu WHERE entry=5223 AND text_id=6236;
INSERT INTO gossip_menu VALUES (5223, 6236);
DELETE FROM gossip_menu WHERE entry=5225 AND text_id=6805;
INSERT INTO gossip_menu VALUES (5225, 6805);
DELETE FROM gossip_menu WHERE entry=5227 AND text_id=6242;
INSERT INTO gossip_menu VALUES (5227, 6242);
DELETE FROM gossip_menu WHERE entry=5621 AND text_id=6714;
INSERT INTO gossip_menu VALUES (5621, 6714);
DELETE FROM gossip_menu WHERE entry=5668 AND text_id=6875;
INSERT INTO gossip_menu VALUES (5668, 6875);
DELETE FROM gossip_menu WHERE entry=5669 AND text_id=6798;
INSERT INTO gossip_menu VALUES (5669, 6798);
DELETE FROM gossip_menu WHERE entry=5670 AND text_id=6807;
INSERT INTO gossip_menu VALUES (5670, 6807);
DELETE FROM gossip_menu WHERE entry=5671 AND text_id=6810;
INSERT INTO gossip_menu VALUES (5671, 6810);
DELETE FROM gossip_menu WHERE entry=5673 AND text_id=6796;
INSERT INTO gossip_menu VALUES (5673, 6796);
DELETE FROM gossip_menu WHERE entry=5674 AND text_id=6797;
INSERT INTO gossip_menu VALUES (5674, 6797);
DELETE FROM gossip_menu WHERE entry=5676 AND text_id=6813;
INSERT INTO gossip_menu VALUES (5676, 6813);
DELETE FROM gossip_menu WHERE entry=5677 AND text_id=6816;
INSERT INTO gossip_menu VALUES (5677, 6816);
DELETE FROM gossip_menu WHERE entry=5678 AND text_id=6819;
INSERT INTO gossip_menu VALUES (5678, 6819);
DELETE FROM gossip_menu WHERE entry=5679 AND text_id=6822;
INSERT INTO gossip_menu VALUES (5679, 6822);
DELETE FROM gossip_menu WHERE entry=5680 AND text_id=6826;
INSERT INTO gossip_menu VALUES (5680, 6826);
DELETE FROM gossip_menu WHERE entry=5681 AND text_id=6829;
INSERT INTO gossip_menu VALUES (5681, 6829);
DELETE FROM gossip_menu WHERE entry=5682 AND text_id=6832;
INSERT INTO gossip_menu VALUES (5682, 6832);
DELETE FROM gossip_menu WHERE entry=5683 AND text_id=6835;
INSERT INTO gossip_menu VALUES (5683, 6835);
DELETE FROM gossip_menu WHERE entry=5684 AND text_id=6838;
INSERT INTO gossip_menu VALUES (5684, 6838);
DELETE FROM gossip_menu WHERE entry=5692 AND text_id=6854;
INSERT INTO gossip_menu VALUES (5692, 6854);
DELETE FROM gossip_menu WHERE entry=5693 AND text_id=6859;
INSERT INTO gossip_menu VALUES (5693, 6859);
DELETE FROM gossip_menu WHERE entry=5695 AND text_id=6865;
INSERT INTO gossip_menu VALUES (5695, 6865);
DELETE FROM gossip_menu WHERE entry=5697 AND text_id=6863;
INSERT INTO gossip_menu VALUES (5697, 6863);
DELETE FROM gossip_menu WHERE entry=5699 AND text_id=6861;
INSERT INTO gossip_menu VALUES (5699, 6861);
DELETE FROM gossip_menu WHERE entry=5705 AND text_id=6871;
INSERT INTO gossip_menu VALUES (5705, 6871);
DELETE FROM gossip_menu WHERE entry=5706 AND text_id=6873;
INSERT INTO gossip_menu VALUES (5706, 6873);
DELETE FROM gossip_menu WHERE entry=5709 AND text_id=6878;
INSERT INTO gossip_menu VALUES (5709, 6878);
DELETE FROM gossip_menu WHERE entry=5709 AND text_id=6879;
INSERT INTO gossip_menu VALUES (5709, 6879);
DELETE FROM gossip_menu WHERE entry=5709 AND text_id=6880;
INSERT INTO gossip_menu VALUES (5709, 6880);
DELETE FROM gossip_menu WHERE entry=5709 AND text_id=6881;
INSERT INTO gossip_menu VALUES (5709, 6881);
DELETE FROM gossip_menu WHERE entry=5733 AND text_id=6905;
INSERT INTO gossip_menu VALUES (5733, 6905);
DELETE FROM gossip_menu WHERE entry=5733 AND text_id=6906;
INSERT INTO gossip_menu VALUES (5733, 6906);
DELETE FROM gossip_menu WHERE entry=5734 AND text_id=6903;
INSERT INTO gossip_menu VALUES (5734, 6903);
DELETE FROM gossip_menu WHERE entry=5734 AND text_id=6904;
INSERT INTO gossip_menu VALUES (5734, 6904);
DELETE FROM gossip_menu WHERE entry=5735 AND text_id=6907;
INSERT INTO gossip_menu VALUES (5735, 6907);
DELETE FROM gossip_menu WHERE entry=5735 AND text_id=6908;
INSERT INTO gossip_menu VALUES (5735, 6908);
DELETE FROM gossip_menu WHERE entry=5738 AND text_id=6915;
INSERT INTO gossip_menu VALUES (5738, 6915);
DELETE FROM gossip_menu WHERE entry=5739 AND text_id=6913;
INSERT INTO gossip_menu VALUES (5739, 6913);
DELETE FROM gossip_menu WHERE entry=6024 AND text_id=6935;
INSERT INTO gossip_menu VALUES (6024, 6935);
DELETE FROM gossip_menu WHERE entry=6161 AND text_id=7399;
INSERT INTO gossip_menu VALUES (6161, 7399);
DELETE FROM gossip_menu WHERE entry=6182 AND text_id=7335;
INSERT INTO gossip_menu VALUES (6182, 7335);
DELETE FROM gossip_menu WHERE entry=6444 AND text_id=7640;
INSERT INTO gossip_menu VALUES (6444, 7640);
DELETE FROM gossip_menu WHERE entry=6454 AND text_id=7645;
INSERT INTO gossip_menu VALUES (6454, 7645);
DELETE FROM gossip_menu WHERE entry=6480 AND text_id=7678;
INSERT INTO gossip_menu VALUES (6480, 7678);
DELETE FROM gossip_menu WHERE entry=6482 AND text_id=7678;
INSERT INTO gossip_menu VALUES (6482, 7678);
DELETE FROM gossip_menu WHERE entry=6502 AND text_id=7699;
INSERT INTO gossip_menu VALUES (6502, 7699);
DELETE FROM gossip_menu WHERE entry=6543 AND text_id=7774;
INSERT INTO gossip_menu VALUES (6543, 7774);
DELETE FROM gossip_menu WHERE entry=6592 AND text_id=7810;
INSERT INTO gossip_menu VALUES (6592, 7810);
DELETE FROM gossip_menu WHERE entry=7058 AND text_id=6;
INSERT INTO gossip_menu VALUES (7058, 6);
DELETE FROM gossip_menu WHERE entry=7058 AND text_id=7;
INSERT INTO gossip_menu VALUES (7058, 7);
DELETE FROM gossip_menu WHERE entry=7139 AND text_id=10741;
INSERT INTO gossip_menu VALUES (7139, 10741);
DELETE FROM gossip_menu WHERE entry=7178 AND text_id=8740;
INSERT INTO gossip_menu VALUES (7178, 8740);
DELETE FROM gossip_menu WHERE entry=7178 AND text_id=10378;
INSERT INTO gossip_menu VALUES (7178, 10378);
DELETE FROM gossip_menu WHERE entry=7415 AND text_id=8955;
INSERT INTO gossip_menu VALUES (7415, 8955);
DELETE FROM gossip_menu WHERE entry=7482 AND text_id=9067;
INSERT INTO gossip_menu VALUES (7482, 9067);
DELETE FROM gossip_menu WHERE entry=7483 AND text_id=9068;
INSERT INTO gossip_menu VALUES (7483, 9068);
DELETE FROM gossip_menu WHERE entry=7556 AND text_id=9169;
INSERT INTO gossip_menu VALUES (7556, 9169);
DELETE FROM gossip_menu WHERE entry=7859 AND text_id=9621;
INSERT INTO gossip_menu VALUES (7859, 9621);
DELETE FROM gossip_menu WHERE entry=7875 AND text_id=9639;
INSERT INTO gossip_menu VALUES (7875, 9639);
DELETE FROM gossip_menu WHERE entry=8039 AND text_id=9927;
INSERT INTO gossip_menu VALUES (8039, 9927);
DELETE FROM gossip_menu WHERE entry=8040 AND text_id=9926;
INSERT INTO gossip_menu VALUES (8040, 9926);
DELETE FROM gossip_menu WHERE entry=8041 AND text_id=9929;
INSERT INTO gossip_menu VALUES (8041, 9929);
DELETE FROM gossip_menu WHERE entry=8042 AND text_id=9930;
INSERT INTO gossip_menu VALUES (8042, 9930);
DELETE FROM gossip_menu WHERE entry=8045 AND text_id=9934;
INSERT INTO gossip_menu VALUES (8045, 9934);
DELETE FROM gossip_menu WHERE entry=8046 AND text_id=9931;
INSERT INTO gossip_menu VALUES (8046, 9931);
DELETE FROM gossip_menu WHERE entry=8228 AND text_id=10232;
INSERT INTO gossip_menu VALUES (8228, 10232);
DELETE FROM gossip_menu WHERE entry=8287 AND text_id=10327;
INSERT INTO gossip_menu VALUES (8287, 10327);
DELETE FROM gossip_menu WHERE entry=8297 AND text_id=10350;
INSERT INTO gossip_menu VALUES (8297, 10350);
DELETE FROM gossip_menu WHERE entry=8311 AND text_id=10375;
INSERT INTO gossip_menu VALUES (8311, 10375);
DELETE FROM gossip_menu WHERE entry=8350 AND text_id=10421;
INSERT INTO gossip_menu VALUES (8350, 10421);
DELETE FROM gossip_menu WHERE entry=8463 AND text_id=10572;
INSERT INTO gossip_menu VALUES (8463, 10572);
DELETE FROM gossip_menu WHERE entry=8494 AND text_id=10214;
INSERT INTO gossip_menu VALUES (8494, 10214);
DELETE FROM gossip_menu WHERE entry=8534 AND text_id=10676;
INSERT INTO gossip_menu VALUES (8534, 10676);
DELETE FROM gossip_menu WHERE entry=8564 AND text_id=10733;
INSERT INTO gossip_menu VALUES (8564, 10733);
DELETE FROM gossip_menu WHERE entry=8816 AND text_id=11324;
INSERT INTO gossip_menu VALUES (8816, 11324);
DELETE FROM gossip_menu WHERE entry=8875 AND text_id=11580;
INSERT INTO gossip_menu VALUES (8875, 11580);
DELETE FROM gossip_menu WHERE entry=8917 AND text_id=11851;
INSERT INTO gossip_menu VALUES (8917, 11851);
DELETE FROM gossip_menu WHERE entry=8920 AND text_id=11872;
INSERT INTO gossip_menu VALUES (8920, 11872);
DELETE FROM gossip_menu WHERE entry=8932 AND text_id=12135;
INSERT INTO gossip_menu VALUES (8932, 12135);
DELETE FROM gossip_menu WHERE entry=8935 AND text_id=11956;
INSERT INTO gossip_menu VALUES (8935, 11956);
DELETE FROM gossip_menu WHERE entry=8936 AND text_id=11957;
INSERT INTO gossip_menu VALUES (8936, 11957);
DELETE FROM gossip_menu WHERE entry=8938 AND text_id=11959;
INSERT INTO gossip_menu VALUES (8938, 11959);
DELETE FROM gossip_menu WHERE entry=8939 AND text_id=11960;
INSERT INTO gossip_menu VALUES (8939, 11960);
DELETE FROM gossip_menu WHERE entry=8940 AND text_id=11961;
INSERT INTO gossip_menu VALUES (8940, 11961);
DELETE FROM gossip_menu WHERE entry=8941 AND text_id=11962;
INSERT INTO gossip_menu VALUES (8941, 11962);
DELETE FROM gossip_menu WHERE entry=8942 AND text_id=11963;
INSERT INTO gossip_menu VALUES (8942, 11963);
DELETE FROM gossip_menu WHERE entry=8943 AND text_id=11964;
INSERT INTO gossip_menu VALUES (8943, 11964);
DELETE FROM gossip_menu WHERE entry=8944 AND text_id=11965;
INSERT INTO gossip_menu VALUES (8944, 11965);
DELETE FROM gossip_menu WHERE entry=8945 AND text_id=11966;
INSERT INTO gossip_menu VALUES (8945, 11966);
DELETE FROM gossip_menu WHERE entry=9253 AND text_id=12566;
INSERT INTO gossip_menu VALUES (9253, 12566);
DELETE FROM gossip_menu WHERE entry=9253 AND text_id=12591;
INSERT INTO gossip_menu VALUES (9253, 12591);
DELETE FROM gossip_menu WHERE entry=9259 AND text_id=12524;
INSERT INTO gossip_menu VALUES (9259, 12524);
DELETE FROM gossip_menu WHERE entry=9260 AND text_id=12524;
INSERT INTO gossip_menu VALUES (9260, 12524);
DELETE FROM gossip_menu WHERE entry=9262 AND text_id=12577;
INSERT INTO gossip_menu VALUES (9262, 12577);
DELETE FROM gossip_menu WHERE entry=9495 AND text_id=12780;
INSERT INTO gossip_menu VALUES (9495, 12780);
DELETE FROM gossip_menu WHERE entry=9600 AND text_id=12958;
INSERT INTO gossip_menu VALUES (9600, 12958);
DELETE FROM gossip_menu WHERE entry=9619 AND text_id=13005;
INSERT INTO gossip_menu VALUES (9619, 13005);
DELETE FROM gossip_menu WHERE entry=9620 AND text_id=13006;
INSERT INTO gossip_menu VALUES (9620, 13006);
DELETE FROM gossip_menu WHERE entry=9628 AND text_id=14149;
INSERT INTO gossip_menu VALUES (9628, 14149);
DELETE FROM gossip_menu WHERE entry=9859 AND text_id=13651;
INSERT INTO gossip_menu VALUES (9859, 13651);
DELETE FROM gossip_menu WHERE entry=10127 AND text_id=14061;
INSERT INTO gossip_menu VALUES (10127, 14061);
DELETE FROM gossip_menu WHERE entry=10133 AND text_id=14069;
INSERT INTO gossip_menu VALUES (10133, 14069);
DELETE FROM gossip_menu WHERE entry=10195 AND text_id=14141;
INSERT INTO gossip_menu VALUES (10195, 14141);
DELETE FROM gossip_menu WHERE entry=10196 AND text_id=14143;
INSERT INTO gossip_menu VALUES (10196, 14143);
DELETE FROM gossip_menu WHERE entry=10200 AND text_id=14160;
INSERT INTO gossip_menu VALUES (10200, 14160);
DELETE FROM gossip_menu WHERE entry=10204 AND text_id=14168;
INSERT INTO gossip_menu VALUES (10204, 14168);
DELETE FROM gossip_menu WHERE entry=10204 AND text_id=14169;
INSERT INTO gossip_menu VALUES (10204, 14169);
DELETE FROM gossip_menu WHERE entry=10263 AND text_id=14289;
INSERT INTO gossip_menu VALUES (10263, 14289);
DELETE FROM gossip_menu WHERE entry=10286 AND text_id=14290;
INSERT INTO gossip_menu VALUES (10286, 14290);
DELETE FROM gossip_menu WHERE entry=10287 AND text_id=14291;
INSERT INTO gossip_menu VALUES (10287, 14291);
DELETE FROM gossip_menu WHERE entry=10292 AND text_id=14296;
INSERT INTO gossip_menu VALUES (10292, 14296);
DELETE FROM gossip_menu WHERE entry=10317 AND text_id=14372;
INSERT INTO gossip_menu VALUES (10317, 14372);
DELETE FROM gossip_menu WHERE entry=10332 AND text_id=14325;
INSERT INTO gossip_menu VALUES (10332, 14325);
DELETE FROM gossip_menu WHERE entry=10334 AND text_id=14325;
INSERT INTO gossip_menu VALUES (10334, 14325);
DELETE FROM gossip_menu WHERE entry=10387 AND text_id=14420;
INSERT INTO gossip_menu VALUES (10387, 14420);
DELETE FROM gossip_menu WHERE entry=10393 AND text_id=14428;
INSERT INTO gossip_menu VALUES (10393, 14428);
DELETE FROM gossip_menu WHERE entry=10430 AND text_id=14468;
INSERT INTO gossip_menu VALUES (10430, 14468);
DELETE FROM gossip_menu WHERE entry=10433 AND text_id=14471;
INSERT INTO gossip_menu VALUES (10433, 14471);
DELETE FROM gossip_menu WHERE entry=10468 AND text_id=14492;
INSERT INTO gossip_menu VALUES (10468, 14492);
DELETE FROM gossip_menu WHERE entry=10469 AND text_id=14492;
INSERT INTO gossip_menu VALUES (10469, 14492);
DELETE FROM gossip_menu WHERE entry=10470 AND text_id=14492;
INSERT INTO gossip_menu VALUES (10470, 14492);
DELETE FROM gossip_menu WHERE entry=10472 AND text_id=14492;
INSERT INTO gossip_menu VALUES (10472, 14492);
DELETE FROM gossip_menu WHERE entry=10473 AND text_id=14492;
INSERT INTO gossip_menu VALUES (10473, 14492);
DELETE FROM gossip_menu WHERE entry=10476 AND text_id=14497;
INSERT INTO gossip_menu VALUES (10476, 14497);
DELETE FROM gossip_menu WHERE entry=10496 AND text_id=14526;
INSERT INTO gossip_menu VALUES (10496, 14526);
DELETE FROM gossip_menu WHERE entry=10506 AND text_id=14538;
INSERT INTO gossip_menu VALUES (10506, 14538);
DELETE FROM gossip_menu WHERE entry=10522 AND text_id=14556;
INSERT INTO gossip_menu VALUES (10522, 14556);
DELETE FROM gossip_menu WHERE entry=10529 AND text_id=14569;
INSERT INTO gossip_menu VALUES (10529, 14569);
DELETE FROM gossip_menu WHERE entry=10530 AND text_id=14568;
INSERT INTO gossip_menu VALUES (10530, 14568);
DELETE FROM gossip_menu WHERE entry=10532 AND text_id=14572;
INSERT INTO gossip_menu VALUES (10532, 14572);
DELETE FROM gossip_menu WHERE entry=10541 AND text_id=14580;
INSERT INTO gossip_menu VALUES (10541, 14580);
DELETE FROM gossip_menu WHERE entry=10551 AND text_id=14597;
INSERT INTO gossip_menu VALUES (10551, 14597);
DELETE FROM gossip_menu WHERE entry=10552 AND text_id=14600;
INSERT INTO gossip_menu VALUES (10552, 14600);
DELETE FROM gossip_menu WHERE entry=10569 AND text_id=14627;
INSERT INTO gossip_menu VALUES (10569, 14627);
DELETE FROM gossip_menu WHERE entry=10570 AND text_id=14628;
INSERT INTO gossip_menu VALUES (10570, 14628);
DELETE FROM gossip_menu WHERE entry=10571 AND text_id=14630;
INSERT INTO gossip_menu VALUES (10571, 14630);
DELETE FROM gossip_menu WHERE entry=10576 AND text_id=14634;
INSERT INTO gossip_menu VALUES (10576, 14634);
DELETE FROM gossip_menu WHERE entry=10577 AND text_id=14635;
INSERT INTO gossip_menu VALUES (10577, 14635);
DELETE FROM gossip_menu WHERE entry=10578 AND text_id=14636;
INSERT INTO gossip_menu VALUES (10578, 14636);
DELETE FROM gossip_menu WHERE entry=10582 AND text_id=14640;
INSERT INTO gossip_menu VALUES (10582, 14640);
DELETE FROM gossip_menu WHERE entry=10585 AND text_id=14643;
INSERT INTO gossip_menu VALUES (10585, 14643);
DELETE FROM gossip_menu WHERE entry=10588 AND text_id=14647;
INSERT INTO gossip_menu VALUES (10588, 14647);
DELETE FROM gossip_menu WHERE entry=10614 AND text_id=14738;
INSERT INTO gossip_menu VALUES (10614, 14738);
DELETE FROM gossip_menu WHERE entry=10620 AND text_id=14699;
INSERT INTO gossip_menu VALUES (10620, 14699);
DELETE FROM gossip_menu WHERE entry=10622 AND text_id=14701;
INSERT INTO gossip_menu VALUES (10622, 14701);
DELETE FROM gossip_menu WHERE entry=10624 AND text_id=14704;
INSERT INTO gossip_menu VALUES (10624, 14704);
DELETE FROM gossip_menu WHERE entry=10635 AND text_id=14729;
INSERT INTO gossip_menu VALUES (10635, 14729);
DELETE FROM gossip_menu WHERE entry=10711 AND text_id=14868;
INSERT INTO gossip_menu VALUES (10711, 14868);
DELETE FROM gossip_menu WHERE entry=10713 AND text_id=14870;
INSERT INTO gossip_menu VALUES (10713, 14870);
DELETE FROM gossip_menu WHERE entry=10720 AND text_id=14879;
INSERT INTO gossip_menu VALUES (10720, 14879);
DELETE FROM gossip_menu WHERE entry=10721 AND text_id=14880;
INSERT INTO gossip_menu VALUES (10721, 14880);
DELETE FROM gossip_menu WHERE entry=10722 AND text_id=14881;
INSERT INTO gossip_menu VALUES (10722, 14881);
DELETE FROM gossip_menu WHERE entry=10769 AND text_id=14931;
INSERT INTO gossip_menu VALUES (10769, 14931);
DELETE FROM gossip_menu WHERE entry=10769 AND text_id=14933;
INSERT INTO gossip_menu VALUES (10769, 14933);
DELETE FROM gossip_menu WHERE entry=10789 AND text_id=14954;
INSERT INTO gossip_menu VALUES (10789, 14954);
DELETE FROM gossip_menu WHERE entry=10790 AND text_id=14957;
INSERT INTO gossip_menu VALUES (10790, 14957);
DELETE FROM gossip_menu WHERE entry=10791 AND text_id=14959;
INSERT INTO gossip_menu VALUES (10791, 14959);
DELETE FROM gossip_menu WHERE entry=10793 AND text_id=14962;
INSERT INTO gossip_menu VALUES (10793, 14962);
DELETE FROM gossip_menu WHERE entry=10794 AND text_id=14965;
INSERT INTO gossip_menu VALUES (10794, 14965);
DELETE FROM gossip_menu WHERE entry=10795 AND text_id=14966;
INSERT INTO gossip_menu VALUES (10795, 14966);
DELETE FROM gossip_menu WHERE entry=10808 AND text_id=14985;
INSERT INTO gossip_menu VALUES (10808, 14985);
DELETE FROM gossip_menu WHERE entry=10814 AND text_id=14988;
INSERT INTO gossip_menu VALUES (10814, 14988);
DELETE FROM gossip_menu WHERE entry=10815 AND text_id=14990;
INSERT INTO gossip_menu VALUES (10815, 14990);
DELETE FROM gossip_menu WHERE entry=10816 AND text_id=14992;
INSERT INTO gossip_menu VALUES (10816, 14992);
DELETE FROM gossip_menu WHERE entry=10817 AND text_id=14995;
INSERT INTO gossip_menu VALUES (10817, 14995);
DELETE FROM gossip_menu WHERE entry=10818 AND text_id=14996;
INSERT INTO gossip_menu VALUES (10818, 14996);
DELETE FROM gossip_menu WHERE entry=10819 AND text_id=14998;
INSERT INTO gossip_menu VALUES (10819, 14998);
DELETE FROM gossip_menu WHERE entry=10821 AND text_id=15000;
INSERT INTO gossip_menu VALUES (10821, 15000);
DELETE FROM gossip_menu WHERE entry=10885 AND text_id=15123;
INSERT INTO gossip_menu VALUES (10885, 15123);
DELETE FROM gossip_menu WHERE entry=10903 AND text_id=15148;
INSERT INTO gossip_menu VALUES (10903, 15148);
DELETE FROM gossip_menu WHERE entry=10944 AND text_id=15412;
INSERT INTO gossip_menu VALUES (10944, 15412);
DELETE FROM gossip_menu WHERE entry=10954 AND text_id=15219;
INSERT INTO gossip_menu VALUES (10954, 15219);
DELETE FROM gossip_menu WHERE entry=11023 AND text_id=15326;
INSERT INTO gossip_menu VALUES (11023, 15326);
DELETE FROM gossip_menu WHERE entry=11029 AND text_id=15332;
INSERT INTO gossip_menu VALUES (11029, 15332);
DELETE FROM gossip_menu WHERE entry=11049 AND text_id=15362;
INSERT INTO gossip_menu VALUES (11049, 15362);
DELETE FROM gossip_menu WHERE entry=11065 AND text_id=15382;
INSERT INTO gossip_menu VALUES (11065, 15382);
DELETE FROM gossip_menu WHERE entry=11066 AND text_id=15385;
INSERT INTO gossip_menu VALUES (11066, 15385);
DELETE FROM gossip_menu WHERE entry=11076 AND text_id=15404;
INSERT INTO gossip_menu VALUES (11076, 15404);
DELETE FROM gossip_menu WHERE entry=11078 AND text_id=15406;
INSERT INTO gossip_menu VALUES (11078, 15406);
DELETE FROM gossip_menu WHERE entry=11087 AND text_id=15427;
INSERT INTO gossip_menu VALUES (11087, 15427);
DELETE FROM gossip_menu WHERE entry=11090 AND text_id=15431;
INSERT INTO gossip_menu VALUES (11090, 15431);
DELETE FROM gossip_menu WHERE entry=11105 AND text_id=15455;
INSERT INTO gossip_menu VALUES (11105, 15455);
DELETE FROM gossip_menu WHERE entry=11108 AND text_id=15459;
INSERT INTO gossip_menu VALUES (11108, 15459);
DELETE FROM gossip_menu WHERE entry=11108 AND text_id=15482;
INSERT INTO gossip_menu VALUES (11108, 15482);
DELETE FROM gossip_menu WHERE entry=11113 AND text_id=15471;
INSERT INTO gossip_menu VALUES (11113, 15471);
DELETE FROM gossip_menu WHERE entry=11115 AND text_id=15473;
INSERT INTO gossip_menu VALUES (11115, 15473);
DELETE FROM gossip_menu WHERE entry=11116 AND text_id=15474;
INSERT INTO gossip_menu VALUES (11116, 15474);
DELETE FROM gossip_menu WHERE entry=11117 AND text_id=15476;
INSERT INTO gossip_menu VALUES (11117, 15476);
DELETE FROM gossip_menu WHERE entry=11118 AND text_id=15475;
INSERT INTO gossip_menu VALUES (11118, 15475);
DELETE FROM gossip_menu WHERE entry=11119 AND text_id=15477;
INSERT INTO gossip_menu VALUES (11119, 15477);
DELETE FROM gossip_menu WHERE entry=11120 AND text_id=15478;
INSERT INTO gossip_menu VALUES (11120, 15478);
DELETE FROM gossip_menu WHERE entry=11121 AND text_id=15479;
INSERT INTO gossip_menu VALUES (11121, 15479);
DELETE FROM gossip_menu WHERE entry=11122 AND text_id=15480;
INSERT INTO gossip_menu VALUES (11122, 15480);
DELETE FROM gossip_menu WHERE entry=11128 AND text_id=15481;
INSERT INTO gossip_menu VALUES (11128, 15481);
DELETE FROM gossip_menu WHERE entry=11129 AND text_id=15483;
INSERT INTO gossip_menu VALUES (11129, 15483);
DELETE FROM gossip_menu WHERE entry=11133 AND text_id=15486;
INSERT INTO gossip_menu VALUES (11133, 15486);
DELETE FROM gossip_menu WHERE entry=11134 AND text_id=15487;
INSERT INTO gossip_menu VALUES (11134, 15487);
DELETE FROM gossip_menu WHERE entry=11135 AND text_id=15488;
INSERT INTO gossip_menu VALUES (11135, 15488);
DELETE FROM gossip_menu WHERE entry=11138 AND text_id=15495;
INSERT INTO gossip_menu VALUES (11138, 15495);
DELETE FROM gossip_menu WHERE entry=11138 AND text_id=15496;
INSERT INTO gossip_menu VALUES (11138, 15496);
DELETE FROM gossip_menu WHERE entry=11138 AND text_id=15514;
INSERT INTO gossip_menu VALUES (11138, 15514);
DELETE FROM gossip_menu WHERE entry=11138 AND text_id=15515;
INSERT INTO gossip_menu VALUES (11138, 15515);
DELETE FROM gossip_menu WHERE entry=11140 AND text_id=15501;
INSERT INTO gossip_menu VALUES (11140, 15501);
DELETE FROM gossip_menu WHERE entry=11141 AND text_id=15504;
INSERT INTO gossip_menu VALUES (11141, 15504);
DELETE FROM gossip_menu WHERE entry=11142 AND text_id=15508;
INSERT INTO gossip_menu VALUES (11142, 15508);
DELETE FROM gossip_menu WHERE entry=11146 AND text_id=15516;
INSERT INTO gossip_menu VALUES (11146, 15516);
DELETE FROM gossip_menu WHERE entry=11147 AND text_id=15517;
INSERT INTO gossip_menu VALUES (11147, 15517);
DELETE FROM gossip_menu WHERE entry=11147 AND text_id=15518;
INSERT INTO gossip_menu VALUES (11147, 15518);
DELETE FROM gossip_menu WHERE entry=11148 AND text_id=15519;
INSERT INTO gossip_menu VALUES (11148, 15519);
DELETE FROM gossip_menu WHERE entry=11149 AND text_id=15520;
INSERT INTO gossip_menu VALUES (11149, 15520);
DELETE FROM gossip_menu WHERE entry=11150 AND text_id=15521;
INSERT INTO gossip_menu VALUES (11150, 15521);
DELETE FROM gossip_menu WHERE entry=11151 AND text_id=15522;
INSERT INTO gossip_menu VALUES (11151, 15522);
DELETE FROM gossip_menu WHERE entry=11153 AND text_id=15525;
INSERT INTO gossip_menu VALUES (11153, 15525);
DELETE FROM gossip_menu WHERE entry=11158 AND text_id=15530;
INSERT INTO gossip_menu VALUES (11158, 15530);
DELETE FROM gossip_menu WHERE entry=11158 AND text_id=15537;
INSERT INTO gossip_menu VALUES (11158, 15537);
DELETE FROM gossip_menu WHERE entry=11158 AND text_id=15538;
INSERT INTO gossip_menu VALUES (11158, 15538);
DELETE FROM gossip_menu WHERE entry=11158 AND text_id=15539;
INSERT INTO gossip_menu VALUES (11158, 15539);
DELETE FROM gossip_menu WHERE entry=11161 AND text_id=15534;
INSERT INTO gossip_menu VALUES (11161, 15534);
DELETE FROM gossip_menu WHERE entry=11166 AND text_id=15542;
INSERT INTO gossip_menu VALUES (11166, 15542);
DELETE FROM gossip_menu WHERE entry=11167 AND text_id=15543;
INSERT INTO gossip_menu VALUES (11167, 15543);
DELETE FROM gossip_menu WHERE entry=11168 AND text_id=15544;
INSERT INTO gossip_menu VALUES (11168, 15544);
DELETE FROM gossip_menu WHERE entry=11169 AND text_id=15545;
INSERT INTO gossip_menu VALUES (11169, 15545);
DELETE FROM gossip_menu WHERE entry=11170 AND text_id=15546;
INSERT INTO gossip_menu VALUES (11170, 15546);
DELETE FROM gossip_menu WHERE entry=11172 AND text_id=15549;
INSERT INTO gossip_menu VALUES (11172, 15549);
DELETE FROM gossip_menu WHERE entry=11173 AND text_id=15550;
INSERT INTO gossip_menu VALUES (11173, 15550);
DELETE FROM gossip_menu WHERE entry=11174 AND text_id=15551;
INSERT INTO gossip_menu VALUES (11174, 15551);
DELETE FROM gossip_menu WHERE entry=11175 AND text_id=15552;
INSERT INTO gossip_menu VALUES (11175, 15552);
DELETE FROM gossip_menu WHERE entry=11175 AND text_id=15554;
INSERT INTO gossip_menu VALUES (11175, 15554);
DELETE FROM gossip_menu WHERE entry=11182 AND text_id=15564;
INSERT INTO gossip_menu VALUES (11182, 15564);
DELETE FROM gossip_menu WHERE entry=11182 AND text_id=15590;
INSERT INTO gossip_menu VALUES (11182, 15590);
DELETE FROM gossip_menu WHERE entry=11184 AND text_id=15566;
INSERT INTO gossip_menu VALUES (11184, 15566);
DELETE FROM gossip_menu WHERE entry=11195 AND text_id=15585;
INSERT INTO gossip_menu VALUES (11195, 15585);
DELETE FROM gossip_menu WHERE entry=11196 AND text_id=15586;
INSERT INTO gossip_menu VALUES (11196, 15586);
DELETE FROM gossip_menu WHERE entry=11196 AND text_id=15587;
INSERT INTO gossip_menu VALUES (11196, 15587);
DELETE FROM gossip_menu WHERE entry=11196 AND text_id=15588;
INSERT INTO gossip_menu VALUES (11196, 15588);
DELETE FROM gossip_menu WHERE entry=11196 AND text_id=15589;
INSERT INTO gossip_menu VALUES (11196, 15589);
DELETE FROM gossip_menu WHERE entry=11198 AND text_id=15595;
INSERT INTO gossip_menu VALUES (11198, 15595);
DELETE FROM gossip_menu WHERE entry=11199 AND text_id=15597;
INSERT INTO gossip_menu VALUES (11199, 15597);
DELETE FROM gossip_menu WHERE entry=11200 AND text_id=15598;
INSERT INTO gossip_menu VALUES (11200, 15598);
DELETE FROM gossip_menu WHERE entry=11201 AND text_id=15599;
INSERT INTO gossip_menu VALUES (11201, 15599);
DELETE FROM gossip_menu WHERE entry=11202 AND text_id=15600;
INSERT INTO gossip_menu VALUES (11202, 15600);
DELETE FROM gossip_menu WHERE entry=11212 AND text_id=15616;
INSERT INTO gossip_menu VALUES (11212, 15616);
DELETE FROM gossip_menu WHERE entry=11213 AND text_id=15619;
INSERT INTO gossip_menu VALUES (11213, 15619);
DELETE FROM gossip_menu WHERE entry=11217 AND text_id=15623;
INSERT INTO gossip_menu VALUES (11217, 15623);
DELETE FROM gossip_menu WHERE entry=11220 AND text_id=15627;
INSERT INTO gossip_menu VALUES (11220, 15627);
DELETE FROM gossip_menu WHERE entry=11223 AND text_id=15630;
INSERT INTO gossip_menu VALUES (11223, 15630);
DELETE FROM gossip_menu WHERE entry=11224 AND text_id=15631;
INSERT INTO gossip_menu VALUES (11224, 15631);
DELETE FROM gossip_menu WHERE entry=11243 AND text_id=15667;
INSERT INTO gossip_menu VALUES (11243, 15667);
DELETE FROM gossip_menu WHERE entry=11244 AND text_id=15701;
INSERT INTO gossip_menu VALUES (11244, 15701);
DELETE FROM gossip_menu WHERE entry=11246 AND text_id=15670;
INSERT INTO gossip_menu VALUES (11246, 15670);
DELETE FROM gossip_menu WHERE entry=11248 AND text_id=15672;
INSERT INTO gossip_menu VALUES (11248, 15672);
DELETE FROM gossip_menu WHERE entry=11249 AND text_id=15673;
INSERT INTO gossip_menu VALUES (11249, 15673);
DELETE FROM gossip_menu WHERE entry=11250 AND text_id=15674;
INSERT INTO gossip_menu VALUES (11250, 15674);
DELETE FROM gossip_menu WHERE entry=11251 AND text_id=15675;
INSERT INTO gossip_menu VALUES (11251, 15675);
DELETE FROM gossip_menu WHERE entry=11253 AND text_id=15677;
INSERT INTO gossip_menu VALUES (11253, 15677);
DELETE FROM gossip_menu WHERE entry=11255 AND text_id=15679;
INSERT INTO gossip_menu VALUES (11255, 15679);
DELETE FROM gossip_menu WHERE entry=11256 AND text_id=15680;
INSERT INTO gossip_menu VALUES (11256, 15680);
DELETE FROM gossip_menu WHERE entry=11258 AND text_id=15682;
INSERT INTO gossip_menu VALUES (11258, 15682);
DELETE FROM gossip_menu WHERE entry=11259 AND text_id=15683;
INSERT INTO gossip_menu VALUES (11259, 15683);
DELETE FROM gossip_menu WHERE entry=11260 AND text_id=15684;
INSERT INTO gossip_menu VALUES (11260, 15684);
DELETE FROM gossip_menu WHERE entry=11261 AND text_id=15685;
INSERT INTO gossip_menu VALUES (11261, 15685);
DELETE FROM gossip_menu WHERE entry=11262 AND text_id=15686;
INSERT INTO gossip_menu VALUES (11262, 15686);
DELETE FROM gossip_menu WHERE entry=11263 AND text_id=15687;
INSERT INTO gossip_menu VALUES (11263, 15687);
DELETE FROM gossip_menu WHERE entry=11264 AND text_id=15688;
INSERT INTO gossip_menu VALUES (11264, 15688);
DELETE FROM gossip_menu WHERE entry=11265 AND text_id=15689;
INSERT INTO gossip_menu VALUES (11265, 15689);
DELETE FROM gossip_menu WHERE entry=11266 AND text_id=15690;
INSERT INTO gossip_menu VALUES (11266, 15690);
DELETE FROM gossip_menu WHERE entry=11267 AND text_id=15691;
INSERT INTO gossip_menu VALUES (11267, 15691);
DELETE FROM gossip_menu WHERE entry=11268 AND text_id=15692;
INSERT INTO gossip_menu VALUES (11268, 15692);
DELETE FROM gossip_menu WHERE entry=11269 AND text_id=15693;
INSERT INTO gossip_menu VALUES (11269, 15693);
DELETE FROM gossip_menu WHERE entry=11270 AND text_id=15694;
INSERT INTO gossip_menu VALUES (11270, 15694);
DELETE FROM gossip_menu WHERE entry=11271 AND text_id=15695;
INSERT INTO gossip_menu VALUES (11271, 15695);
DELETE FROM gossip_menu WHERE entry=11272 AND text_id=15696;
INSERT INTO gossip_menu VALUES (11272, 15696);
DELETE FROM gossip_menu WHERE entry=11273 AND text_id=15697;
INSERT INTO gossip_menu VALUES (11273, 15697);
DELETE FROM gossip_menu WHERE entry=11274 AND text_id=15698;
INSERT INTO gossip_menu VALUES (11274, 15698);
DELETE FROM gossip_menu WHERE entry=11275 AND text_id=15699;
INSERT INTO gossip_menu VALUES (11275, 15699);
DELETE FROM gossip_menu WHERE entry=11276 AND text_id=15700;
INSERT INTO gossip_menu VALUES (11276, 15700);
DELETE FROM gossip_menu WHERE entry=11295 AND text_id=15739;
INSERT INTO gossip_menu VALUES (11295, 15739);
DELETE FROM gossip_menu WHERE entry=11327 AND text_id=15783;
INSERT INTO gossip_menu VALUES (11327, 15783);
DELETE FROM gossip_menu WHERE entry=11347 AND text_id=15808;
INSERT INTO gossip_menu VALUES (11347, 15808);
DELETE FROM gossip_menu WHERE entry=11349 AND text_id=15816;
INSERT INTO gossip_menu VALUES (11349, 15816);
DELETE FROM gossip_menu WHERE entry=11364 AND text_id=15838;
INSERT INTO gossip_menu VALUES (11364, 15838);
DELETE FROM gossip_menu WHERE entry=11370 AND text_id=15841;
INSERT INTO gossip_menu VALUES (11370, 15841);
DELETE FROM gossip_menu WHERE entry=11373 AND text_id=7778;
INSERT INTO gossip_menu VALUES (11373, 7778);
DELETE FROM gossip_menu WHERE entry=11374 AND text_id=15845;
INSERT INTO gossip_menu VALUES (11374, 15845);
DELETE FROM gossip_menu WHERE entry=11376 AND text_id=15847;
INSERT INTO gossip_menu VALUES (11376, 15847);
DELETE FROM gossip_menu WHERE entry=11381 AND text_id=15851;
INSERT INTO gossip_menu VALUES (11381, 15851);
DELETE FROM gossip_menu WHERE entry=11397 AND text_id=15877;
INSERT INTO gossip_menu VALUES (11397, 15877);
DELETE FROM gossip_menu WHERE entry=11398 AND text_id=15876;
INSERT INTO gossip_menu VALUES (11398, 15876);
DELETE FROM gossip_menu WHERE entry=11418 AND text_id=15898;
INSERT INTO gossip_menu VALUES (11418, 15898);
DELETE FROM gossip_menu WHERE entry=11421 AND text_id=15904;
INSERT INTO gossip_menu VALUES (11421, 15904);
DELETE FROM gossip_menu WHERE entry=11428 AND text_id=15915;
INSERT INTO gossip_menu VALUES (11428, 15915);
DELETE FROM gossip_menu WHERE entry=11474 AND text_id=16008;
INSERT INTO gossip_menu VALUES (11474, 16008);
DELETE FROM gossip_menu WHERE entry=11477 AND text_id=16014;
INSERT INTO gossip_menu VALUES (11477, 16014);
DELETE FROM gossip_menu WHERE entry=11489 AND text_id=16033;
INSERT INTO gossip_menu VALUES (11489, 16033);
DELETE FROM gossip_menu WHERE entry=11508 AND text_id=16062;
INSERT INTO gossip_menu VALUES (11508, 16062);
DELETE FROM gossip_menu WHERE entry=11509 AND text_id=16061;
INSERT INTO gossip_menu VALUES (11509, 16061);
DELETE FROM gossip_menu WHERE entry=11510 AND text_id=16064;
INSERT INTO gossip_menu VALUES (11510, 16064);
DELETE FROM gossip_menu WHERE entry=11511 AND text_id=16063;
INSERT INTO gossip_menu VALUES (11511, 16063);
DELETE FROM gossip_menu WHERE entry=11513 AND text_id=16067;
INSERT INTO gossip_menu VALUES (11513, 16067);
DELETE FROM gossip_menu WHERE entry=11514 AND text_id=16066;
INSERT INTO gossip_menu VALUES (11514, 16066);
DELETE FROM gossip_menu WHERE entry=11523 AND text_id=16077;
INSERT INTO gossip_menu VALUES (11523, 16077);
DELETE FROM gossip_menu WHERE entry=11542 AND text_id=16113;
INSERT INTO gossip_menu VALUES (11542, 16113);
DELETE FROM gossip_menu WHERE entry=11543 AND text_id=16114;
INSERT INTO gossip_menu VALUES (11543, 16114);
DELETE FROM gossip_menu WHERE entry=11598 AND text_id=16193;
INSERT INTO gossip_menu VALUES (11598, 16193);
DELETE FROM gossip_menu WHERE entry=11599 AND text_id=16194;
INSERT INTO gossip_menu VALUES (11599, 16194);
DELETE FROM gossip_menu WHERE entry=11601 AND text_id=16195;
INSERT INTO gossip_menu VALUES (11601, 16195);
DELETE FROM gossip_menu WHERE entry=11614 AND text_id=16215;
INSERT INTO gossip_menu VALUES (11614, 16215);
DELETE FROM gossip_menu WHERE entry=11648 AND text_id=16271;
INSERT INTO gossip_menu VALUES (11648, 16271);
DELETE FROM gossip_menu WHERE entry=11680 AND text_id=16343;
INSERT INTO gossip_menu VALUES (11680, 16343);
DELETE FROM gossip_menu WHERE entry=11715 AND text_id=16394;
INSERT INTO gossip_menu VALUES (11715, 16394);
DELETE FROM gossip_menu WHERE entry=11716 AND text_id=16396;
INSERT INTO gossip_menu VALUES (11716, 16396);
DELETE FROM gossip_menu WHERE entry=11716 AND text_id=16660;
INSERT INTO gossip_menu VALUES (11716, 16660);
DELETE FROM gossip_menu WHERE entry=11719 AND text_id=7778;
INSERT INTO gossip_menu VALUES (11719, 7778);
DELETE FROM gossip_menu WHERE entry=11829 AND text_id=16586;
INSERT INTO gossip_menu VALUES (11829, 16586);
DELETE FROM gossip_menu WHERE entry=11859 AND text_id=16621;
INSERT INTO gossip_menu VALUES (11859, 16621);
DELETE FROM gossip_menu WHERE entry=11906 AND text_id=16714;
INSERT INTO gossip_menu VALUES (11906, 16714);
DELETE FROM gossip_menu WHERE entry=11918 AND text_id=16733;
INSERT INTO gossip_menu VALUES (11918, 16733);
DELETE FROM gossip_menu WHERE entry=11948 AND text_id=16775;
INSERT INTO gossip_menu VALUES (11948, 16775);
DELETE FROM gossip_menu WHERE entry=11949 AND text_id=16776;
INSERT INTO gossip_menu VALUES (11949, 16776);
DELETE FROM gossip_menu WHERE entry=11950 AND text_id=16777;
INSERT INTO gossip_menu VALUES (11950, 16777);
DELETE FROM gossip_menu WHERE entry=12023 AND text_id=16849;
INSERT INTO gossip_menu VALUES (12023, 16849);
DELETE FROM gossip_menu WHERE entry=12026 AND text_id=16858;
INSERT INTO gossip_menu VALUES (12026, 16858);
DELETE FROM gossip_menu WHERE entry=12027 AND text_id=16859;
INSERT INTO gossip_menu VALUES (12027, 16859);
DELETE FROM gossip_menu WHERE entry=12030 AND text_id=16862;
INSERT INTO gossip_menu VALUES (12030, 16862);
DELETE FROM gossip_menu WHERE entry=12039 AND text_id=3301;
INSERT INTO gossip_menu VALUES (12039, 3301);
DELETE FROM gossip_menu WHERE entry=12041 AND text_id=16871;
INSERT INTO gossip_menu VALUES (12041, 16871);
DELETE FROM gossip_menu WHERE entry=12043 AND text_id=16873;
INSERT INTO gossip_menu VALUES (12043, 16873);
DELETE FROM gossip_menu WHERE entry=12044 AND text_id=16874;
INSERT INTO gossip_menu VALUES (12044, 16874);
DELETE FROM gossip_menu WHERE entry=12057 AND text_id=16906;
INSERT INTO gossip_menu VALUES (12057, 16906);
DELETE FROM gossip_menu WHERE entry=12060 AND text_id=16908;
INSERT INTO gossip_menu VALUES (12060, 16908);
DELETE FROM gossip_menu WHERE entry=12066 AND text_id=16923;
INSERT INTO gossip_menu VALUES (12066, 16923);
DELETE FROM gossip_menu WHERE entry=12077 AND text_id=16953;
INSERT INTO gossip_menu VALUES (12077, 16953);
DELETE FROM gossip_menu WHERE entry=12078 AND text_id=16954;
INSERT INTO gossip_menu VALUES (12078, 16954);
DELETE FROM gossip_menu WHERE entry=12079 AND text_id=16955;
INSERT INTO gossip_menu VALUES (12079, 16955);
DELETE FROM gossip_menu WHERE entry=12080 AND text_id=16951;
INSERT INTO gossip_menu VALUES (12080, 16951);
DELETE FROM gossip_menu WHERE entry=12082 AND text_id=16957;
INSERT INTO gossip_menu VALUES (12082, 16957);
DELETE FROM gossip_menu WHERE entry=12083 AND text_id=16959;
INSERT INTO gossip_menu VALUES (12083, 16959);
DELETE FROM gossip_menu WHERE entry=12088 AND text_id=16969;
INSERT INTO gossip_menu VALUES (12088, 16969);
DELETE FROM gossip_menu WHERE entry=12088 AND text_id=16970;
INSERT INTO gossip_menu VALUES (12088, 16970);
DELETE FROM gossip_menu WHERE entry=12098 AND text_id=16986;
INSERT INTO gossip_menu VALUES (12098, 16986);
DELETE FROM gossip_menu WHERE entry=12107 AND text_id=16998;
INSERT INTO gossip_menu VALUES (12107, 16998);
DELETE FROM gossip_menu WHERE entry=12130 AND text_id=17036;
INSERT INTO gossip_menu VALUES (12130, 17036);
DELETE FROM gossip_menu WHERE entry=12135 AND text_id=17013;
INSERT INTO gossip_menu VALUES (12135, 17013);
DELETE FROM gossip_menu WHERE entry=12136 AND text_id=17012;
INSERT INTO gossip_menu VALUES (12136, 17012);
DELETE FROM gossip_menu WHERE entry=12137 AND text_id=17011;
INSERT INTO gossip_menu VALUES (12137, 17011);
DELETE FROM gossip_menu WHERE entry=12205 AND text_id=17143;
INSERT INTO gossip_menu VALUES (12205, 17143);
DELETE FROM gossip_menu WHERE entry=12206 AND text_id=17143;
INSERT INTO gossip_menu VALUES (12206, 17143);
DELETE FROM gossip_menu WHERE entry=12207 AND text_id=17143;
INSERT INTO gossip_menu VALUES (12207, 17143);
DELETE FROM gossip_menu WHERE entry=12241 AND text_id=16771;
INSERT INTO gossip_menu VALUES (12241, 16771);
DELETE FROM gossip_menu WHERE entry=12252 AND text_id=17214;
INSERT INTO gossip_menu VALUES (12252, 17214);
DELETE FROM gossip_menu WHERE entry=12255 AND text_id=17216;
INSERT INTO gossip_menu VALUES (12255, 17216);
DELETE FROM gossip_menu WHERE entry=12264 AND text_id=17226;
INSERT INTO gossip_menu VALUES (12264, 17226);
DELETE FROM gossip_menu WHERE entry=12303 AND text_id=17296;
INSERT INTO gossip_menu VALUES (12303, 17296);
DELETE FROM gossip_menu WHERE entry=12307 AND text_id=17300;
INSERT INTO gossip_menu VALUES (12307, 17300);
DELETE FROM gossip_menu WHERE entry=12312 AND text_id=17307;
INSERT INTO gossip_menu VALUES (12312, 17307);
DELETE FROM gossip_menu WHERE entry=12313 AND text_id=17308;
INSERT INTO gossip_menu VALUES (12313, 17308);
DELETE FROM gossip_menu WHERE entry=12320 AND text_id=17315;
INSERT INTO gossip_menu VALUES (12320, 17315);
DELETE FROM gossip_menu WHERE entry=12323 AND text_id=17318;
INSERT INTO gossip_menu VALUES (12323, 17318);
DELETE FROM gossip_menu WHERE entry=12355 AND text_id=17360;
INSERT INTO gossip_menu VALUES (12355, 17360);
DELETE FROM gossip_menu WHERE entry=12364 AND text_id=17368;
INSERT INTO gossip_menu VALUES (12364, 17368);
DELETE FROM gossip_menu WHERE entry=12365 AND text_id=17369;
INSERT INTO gossip_menu VALUES (12365, 17369);
DELETE FROM gossip_menu WHERE entry=12366 AND text_id=17370;
INSERT INTO gossip_menu VALUES (12366, 17370);
DELETE FROM gossip_menu WHERE entry=12368 AND text_id=17372;
INSERT INTO gossip_menu VALUES (12368, 17372);
DELETE FROM gossip_menu WHERE entry=12392 AND text_id=17419;
INSERT INTO gossip_menu VALUES (12392, 17419);
DELETE FROM gossip_menu WHERE entry=12394 AND text_id=17421;
INSERT INTO gossip_menu VALUES (12394, 17421);
DELETE FROM gossip_menu WHERE entry=12395 AND text_id=17422;
INSERT INTO gossip_menu VALUES (12395, 17422);
DELETE FROM gossip_menu WHERE entry=12412 AND text_id=17451;
INSERT INTO gossip_menu VALUES (12412, 17451);
DELETE FROM gossip_menu WHERE entry=12431 AND text_id=17482;
INSERT INTO gossip_menu VALUES (12431, 17482);
DELETE FROM gossip_menu WHERE entry=12432 AND text_id=17483;
INSERT INTO gossip_menu VALUES (12432, 17483);
DELETE FROM gossip_menu WHERE entry=12440 AND text_id=17492;
INSERT INTO gossip_menu VALUES (12440, 17492);
DELETE FROM gossip_menu WHERE entry=12458 AND text_id=17519;
INSERT INTO gossip_menu VALUES (12458, 17519);
DELETE FROM gossip_menu WHERE entry=12459 AND text_id=17521;
INSERT INTO gossip_menu VALUES (12459, 17521);
DELETE FROM gossip_menu WHERE entry=12463 AND text_id=17531;
INSERT INTO gossip_menu VALUES (12463, 17531);
DELETE FROM gossip_menu WHERE entry=12466 AND text_id=17537;
INSERT INTO gossip_menu VALUES (12466, 17537);
DELETE FROM gossip_menu WHERE entry=12467 AND text_id=17538;
INSERT INTO gossip_menu VALUES (12467, 17538);
DELETE FROM gossip_menu WHERE entry=12469 AND text_id=17541;
INSERT INTO gossip_menu VALUES (12469, 17541);
DELETE FROM gossip_menu WHERE entry=12470 AND text_id=17542;
INSERT INTO gossip_menu VALUES (12470, 17542);
DELETE FROM gossip_menu WHERE entry=12476 AND text_id=17552;
INSERT INTO gossip_menu VALUES (12476, 17552);
DELETE FROM gossip_menu WHERE entry=12478 AND text_id=17554;
INSERT INTO gossip_menu VALUES (12478, 17554);
DELETE FROM gossip_menu WHERE entry=12498 AND text_id=17583;
INSERT INTO gossip_menu VALUES (12498, 17583);
DELETE FROM gossip_menu WHERE entry=12541 AND text_id=17619;
INSERT INTO gossip_menu VALUES (12541, 17619);
DELETE FROM gossip_menu WHERE entry=12567 AND text_id=17666;
INSERT INTO gossip_menu VALUES (12567, 17666);
DELETE FROM gossip_menu WHERE entry=12572 AND text_id=17671;
INSERT INTO gossip_menu VALUES (12572, 17671);
DELETE FROM gossip_menu WHERE entry=12576 AND text_id=17682;
INSERT INTO gossip_menu VALUES (12576, 17682);
DELETE FROM gossip_menu WHERE entry=12578 AND text_id=17686;
INSERT INTO gossip_menu VALUES (12578, 17686);
DELETE FROM gossip_menu WHERE entry=12579 AND text_id=17687;
INSERT INTO gossip_menu VALUES (12579, 17687);
DELETE FROM gossip_menu WHERE entry=12584 AND text_id=17696;
INSERT INTO gossip_menu VALUES (12584, 17696);
DELETE FROM gossip_menu WHERE entry=12586 AND text_id=17700;
INSERT INTO gossip_menu VALUES (12586, 17700);
DELETE FROM gossip_menu WHERE entry=12587 AND text_id=17701;
INSERT INTO gossip_menu VALUES (12587, 17701);
DELETE FROM gossip_menu WHERE entry=12588 AND text_id=17704;
INSERT INTO gossip_menu VALUES (12588, 17704);
DELETE FROM gossip_menu WHERE entry=12604 AND text_id=17742;
INSERT INTO gossip_menu VALUES (12604, 17742);
DELETE FROM gossip_menu WHERE entry=12645 AND text_id=16399;
INSERT INTO gossip_menu VALUES (12645, 16399);
DELETE FROM gossip_menu WHERE entry=12674 AND text_id=17818;
INSERT INTO gossip_menu VALUES (12674, 17818);
DELETE FROM gossip_menu WHERE entry=12687 AND text_id=12374;
INSERT INTO gossip_menu VALUES (12687, 12374);
DELETE FROM gossip_menu WHERE entry=12688 AND text_id=12374;
INSERT INTO gossip_menu VALUES (12688, 12374);
DELETE FROM gossip_menu WHERE entry=12695 AND text_id=12374;
INSERT INTO gossip_menu VALUES (12695, 12374);
DELETE FROM gossip_menu WHERE entry=12705 AND text_id=17836;
INSERT INTO gossip_menu VALUES (12705, 17836);
DELETE FROM gossip_menu WHERE entry=12714 AND text_id=4433;
INSERT INTO gossip_menu VALUES (12714, 4433);
DELETE FROM gossip_menu WHERE entry=12717 AND text_id=17849;
INSERT INTO gossip_menu VALUES (12717, 17849);
DELETE FROM gossip_menu WHERE entry=12797 AND text_id=17989;
INSERT INTO gossip_menu VALUES (12797, 17989);
DELETE FROM gossip_menu WHERE entry=12802 AND text_id=18001;
INSERT INTO gossip_menu VALUES (12802, 18001);
DELETE FROM gossip_menu WHERE entry=12821 AND text_id=5720;
INSERT INTO gossip_menu VALUES (12821, 5720);
DELETE FROM gossip_menu WHERE entry=12836 AND text_id=18044;
INSERT INTO gossip_menu VALUES (12836, 18044);
DELETE FROM gossip_menu WHERE entry=12837 AND text_id=18045;
INSERT INTO gossip_menu VALUES (12837, 18045);
DELETE FROM gossip_menu WHERE entry=12889 AND text_id=18131;
INSERT INTO gossip_menu VALUES (12889, 18131);
DELETE FROM gossip_menu WHERE entry=12890 AND text_id=18130;
INSERT INTO gossip_menu VALUES (12890, 18130);
DELETE FROM gossip_menu WHERE entry=12895 AND text_id=18137;
INSERT INTO gossip_menu VALUES (12895, 18137);
DELETE FROM gossip_menu WHERE entry=12903 AND text_id=18145;
INSERT INTO gossip_menu VALUES (12903, 18145);
DELETE FROM gossip_menu WHERE entry=12931 AND text_id=18189;
INSERT INTO gossip_menu VALUES (12931, 18189);
DELETE FROM gossip_menu WHERE entry=12937 AND text_id=18200;
INSERT INTO gossip_menu VALUES (12937, 18200);
DELETE FROM gossip_menu WHERE entry=12951 AND text_id=18222;
INSERT INTO gossip_menu VALUES (12951, 18222);
DELETE FROM gossip_menu WHERE entry=12952 AND text_id=18224;
INSERT INTO gossip_menu VALUES (12952, 18224);
DELETE FROM gossip_menu WHERE entry=12965 AND text_id=18238;
INSERT INTO gossip_menu VALUES (12965, 18238);
DELETE FROM gossip_menu WHERE entry=12967 AND text_id=18241;
INSERT INTO gossip_menu VALUES (12967, 18241);
DELETE FROM gossip_menu WHERE entry=12969 AND text_id=18242;
INSERT INTO gossip_menu VALUES (12969, 18242);
DELETE FROM gossip_menu WHERE entry=12971 AND text_id=18244;
INSERT INTO gossip_menu VALUES (12971, 18244);
DELETE FROM gossip_menu WHERE entry=12986 AND text_id=18262;
INSERT INTO gossip_menu VALUES (12986, 18262);
DELETE FROM gossip_menu WHERE entry=12987 AND text_id=18263;
INSERT INTO gossip_menu VALUES (12987, 18263);
DELETE FROM gossip_menu WHERE entry=12988 AND text_id=18264;
INSERT INTO gossip_menu VALUES (12988, 18264);
DELETE FROM gossip_menu WHERE entry=12989 AND text_id=18265;
INSERT INTO gossip_menu VALUES (12989, 18265);
DELETE FROM gossip_menu WHERE entry=13024 AND text_id=18295;
INSERT INTO gossip_menu VALUES (13024, 18295);
DELETE FROM gossip_menu WHERE entry=13075 AND text_id=18362;
INSERT INTO gossip_menu VALUES (13075, 18362);
DELETE FROM gossip_menu WHERE entry=13086 AND text_id=18377;
INSERT INTO gossip_menu VALUES (13086, 18377);
DELETE FROM gossip_menu WHERE entry=13096 AND text_id=18390;
INSERT INTO gossip_menu VALUES (13096, 18390);
DELETE FROM gossip_menu WHERE entry=13131 AND text_id=18472;
INSERT INTO gossip_menu VALUES (13131, 18472);
DELETE FROM gossip_menu WHERE entry=13160 AND text_id=55488;
INSERT INTO gossip_menu VALUES (13160, 55488);
DELETE FROM gossip_menu WHERE entry=13166 AND text_id=18560;
INSERT INTO gossip_menu VALUES (13166, 18560);
DELETE FROM gossip_menu WHERE entry=13168 AND text_id=18562;
INSERT INTO gossip_menu VALUES (13168, 18562);
DELETE FROM gossip_menu WHERE entry=13210 AND text_id=18618;
INSERT INTO gossip_menu VALUES (13210, 18618);
DELETE FROM gossip_menu WHERE entry=13275 AND text_id=18740;
INSERT INTO gossip_menu VALUES (13275, 18740);
DELETE FROM gossip_menu WHERE entry=13294 AND text_id=18799;
INSERT INTO gossip_menu VALUES (13294, 18799);
DELETE FROM gossip_menu WHERE entry=13322 AND text_id=18867;
INSERT INTO gossip_menu VALUES (13322, 18867);
DELETE FROM gossip_menu WHERE entry=13329 AND text_id=18879;
INSERT INTO gossip_menu VALUES (13329, 18879);
DELETE FROM gossip_menu WHERE entry=13331 AND text_id=18879;
INSERT INTO gossip_menu VALUES (13331, 18879);
DELETE FROM gossip_menu WHERE entry=13341 AND text_id=18904;
INSERT INTO gossip_menu VALUES (13341, 18904);
DELETE FROM gossip_menu WHERE entry=13359 AND text_id=18958;
INSERT INTO gossip_menu VALUES (13359, 18958);
DELETE FROM gossip_menu WHERE entry=13373 AND text_id=18978;
INSERT INTO gossip_menu VALUES (13373, 18978);
DELETE FROM gossip_menu WHERE entry=13868 AND text_id=20038;
INSERT INTO gossip_menu VALUES (13868, 20038);
DELETE FROM gossip_menu WHERE entry=14136 AND text_id=9192;
INSERT INTO gossip_menu VALUES (14136, 9192);
DELETE FROM gossip_menu WHERE entry=14136 AND text_id=9191;
INSERT INTO gossip_menu VALUES (14136, 9191);
DELETE FROM gossip_menu WHERE entry=14137 AND text_id=9193;
INSERT INTO gossip_menu VALUES (14137, 9193);
DELETE FROM gossip_menu WHERE entry=14137 AND text_id=7904;
INSERT INTO gossip_menu VALUES (14137, 7904);
DELETE FROM gossip_menu WHERE entry=14138 AND text_id=7903;
INSERT INTO gossip_menu VALUES (14138, 7903);
DELETE FROM gossip_menu WHERE entry=14138 AND text_id=7882;
INSERT INTO gossip_menu VALUES (14138, 7882);
DELETE FROM gossip_menu WHERE entry=14139 AND text_id=9186;
INSERT INTO gossip_menu VALUES (14139, 9186);
DELETE FROM gossip_menu WHERE entry=14139 AND text_id=9007;
INSERT INTO gossip_menu VALUES (14139, 9007);
DELETE FROM gossip_menu WHERE entry=14140 AND text_id=9187;
INSERT INTO gossip_menu VALUES (14140, 9187);
DELETE FROM gossip_menu WHERE entry=14140 AND text_id=9188;
INSERT INTO gossip_menu VALUES (14140, 9188);
DELETE FROM gossip_menu WHERE entry=14141 AND text_id=9189;
INSERT INTO gossip_menu VALUES (14141, 9189);
DELETE FROM gossip_menu WHERE entry=14141 AND text_id=9190;
INSERT INTO gossip_menu VALUES (14141, 9190);
DELETE FROM gossip_menu WHERE entry=14142 AND text_id=9185;
INSERT INTO gossip_menu VALUES (14142, 9185);
DELETE FROM gossip_menu WHERE entry=14144 AND text_id=9189;
INSERT INTO gossip_menu VALUES (14144, 9189);
DELETE FROM gossip_menu WHERE entry=14199 AND text_id=16540;
INSERT INTO gossip_menu VALUES (14199, 16540);
DELETE FROM gossip_menu WHERE entry=14199 AND text_id=16541;
INSERT INTO gossip_menu VALUES (14199, 16541);
DELETE FROM gossip_menu WHERE entry=15145 AND text_id=21709;
INSERT INTO gossip_menu VALUES (15145, 21709);
DELETE FROM gossip_menu WHERE entry=15734 AND text_id=22594;
INSERT INTO gossip_menu VALUES (15734, 22594);
DELETE FROM gossip_menu WHERE entry=20087 AND text_id=50087;
INSERT INTO gossip_menu VALUES (20087, 50087);
DELETE FROM gossip_menu WHERE entry=20089 AND text_id=50089;
INSERT INTO gossip_menu VALUES (20089, 50089);
DELETE FROM gossip_menu WHERE entry=21221 AND text_id=4793;
INSERT INTO gossip_menu VALUES (21221, 4793);
DELETE FROM gossip_menu WHERE entry=21252 AND text_id=8077;
INSERT INTO gossip_menu VALUES (21252, 8077);
DELETE FROM gossip_menu WHERE entry=21253 AND text_id=9520;
INSERT INTO gossip_menu VALUES (21253, 9520);
DELETE FROM gossip_menu WHERE entry=40060 AND text_id=2493;
INSERT INTO gossip_menu VALUES (40060, 2493);
DELETE FROM gossip_menu WHERE entry=45068 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45068, 14063);
DELETE FROM gossip_menu WHERE entry=45069 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45069, 14063);
DELETE FROM gossip_menu WHERE entry=45070 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45070, 14063);
DELETE FROM gossip_menu WHERE entry=45071 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45071, 14063);
DELETE FROM gossip_menu WHERE entry=45072 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45072, 14063);
DELETE FROM gossip_menu WHERE entry=45073 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45073, 14063);
DELETE FROM gossip_menu WHERE entry=45074 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45074, 14063);
DELETE FROM gossip_menu WHERE entry=45075 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45075, 14063);
DELETE FROM gossip_menu WHERE entry=45076 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45076, 14063);
DELETE FROM gossip_menu WHERE entry=45077 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45077, 14063);
DELETE FROM gossip_menu WHERE entry=45078 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45078, 14063);
DELETE FROM gossip_menu WHERE entry=45079 AND text_id=14063;
INSERT INTO gossip_menu VALUES (45079, 14063);
DELETE FROM gossip_menu WHERE entry=50000 AND text_id=50000;
INSERT INTO gossip_menu VALUES (50000, 50000);
DELETE FROM gossip_menu WHERE entry=53371 AND text_id=53371;
INSERT INTO gossip_menu VALUES (53371, 53371);
DELETE FROM gossip_menu WHERE entry=53466 AND text_id=53466;
INSERT INTO gossip_menu VALUES (53466, 53466);
DELETE FROM gossip_menu WHERE entry=56314 AND text_id=56314;
INSERT INTO gossip_menu VALUES (56314, 56314);
DELETE FROM gossip_menu WHERE entry=57000 AND text_id=1674;
INSERT INTO gossip_menu VALUES (57000, 1674);
DELETE FROM gossip_menu WHERE entry=57001 AND text_id=1675;
INSERT INTO gossip_menu VALUES (57001, 1675);
DELETE FROM gossip_menu WHERE entry=57002 AND text_id=1676;
INSERT INTO gossip_menu VALUES (57002, 1676);
DELETE FROM gossip_menu WHERE entry=57003 AND text_id=1677;
INSERT INTO gossip_menu VALUES (57003, 1677);
DELETE FROM gossip_menu WHERE entry=57004 AND text_id=1678;
INSERT INTO gossip_menu VALUES (57004, 1678);
DELETE FROM gossip_menu WHERE entry=57005 AND text_id=1679;
INSERT INTO gossip_menu VALUES (57005, 1679);
DELETE FROM gossip_menu WHERE entry=57800 AND text_id=57800;
INSERT INTO gossip_menu VALUES (57800, 57800);





delete from gossip_menu_option where menu_id=1;

delete from gossip_menu where entry>= 57800;

delete from gossip_menu where entry=42386 and text_id=921062;
delete from gossip_menu where entry=37552 and text_id=537552;

DELETE FROM gossip_menu WHERE entry=10550 and text_id=14803;
INSERT INTO gossip_menu VALUES (10550, 14803);

UPDATE gossip_menu_option SET OptionBroadcastTextID=2544 WHERE menu_id=10550 AND id=0;

DELETE FROM gossip_menu WHERE entry=10553 and text_id=14810;
INSERT INTO gossip_menu VALUES (10553, 14810);

delete from npc_text where ID=14810;
insert into npc_text (ID) values (14810);
UPDATE npc_text SET text0_1="We're... er, I mean the Light, is going to need a lot of gold, now more than ever.$B$BSpeaking of which, do you need any training?", BroadcastTextID0=35983, prob0=1, em0_0=1 WHERE ID=14810;

delete from npc_text where ID=14606;
insert into npc_text (ID) values (14606);
UPDATE npc_text SET text0_1="Warrior-Matic NX-01 is online.$B$BPlease insert coins for training.", BroadcastTextID0=34960, prob0=1 WHERE ID=14606;

DELETE FROM gossip_menu WHERE entry=10555 and text_id=14606;
INSERT INTO gossip_menu VALUES (10555, 14606);

DELETE FROM gossip_menu WHERE entry=10549 and text_id=14594;
INSERT INTO gossip_menu VALUES (10549, 14594);

delete from npc_text where ID=14594;
insert into npc_text (ID) values (14594);
UPDATE npc_text SET text0_1="Hey, $N, good to see you. These monkeys are driving me insane!$B$BWhat do you need?", BroadcastTextID0=34946 WHERE ID=14594;

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10555;
insert into conditions values 
(14, 10555, 14605, 0, 0, 15, 0, 1534, 0, 0, 0, 0, 0, "", "is not warrier class"),
(14, 10555, 14606, 0, 0, 15, 0,    1, 0, 0, 0, 0, 0, "", "is warrier class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10549;
insert into conditions values 
(14, 10549, 14593, 0, 0, 15, 0, 1531, 0, 0, 0, 0, 0, "", "is not hunter class"),
(14, 10549, 14594, 0, 0, 15, 0,    4, 0, 0, 0, 0, 0, "", "is hunter class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10554;
insert into conditions values 
(14, 10554, 14603, 0, 0, 15, 0, 1527, 0, 0, 0, 0, 0, "", "is not rogue class"),
(14, 10554, 14604, 0, 0, 15, 0,    8, 0, 0, 0, 0, 0, "", "is rogue class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10553;
insert into conditions values 
(14, 10553, 14809, 0, 0, 15, 0, 1519, 0, 0, 0, 0, 0, "", "is not Priest class"),
(14, 10553, 14810, 0, 0, 15, 0,   16, 0, 0, 0, 0, 0, "", "is Priest class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10552;
insert into conditions values 
(14, 10552, 14599, 0, 0, 15, 0, 1471, 0, 0, 0, 0, 0, "", "is not Shaman class"),
(14, 10552, 14600, 0, 0, 15, 0,   64, 0, 0, 0, 0, 0, "", "is Shaman class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10551;
insert into conditions values 
(14, 10551, 14597, 0, 0, 15, 0, 1407, 0, 0, 0, 0, 0, "", "is not mage class"),
(14, 10551, 14598, 0, 0, 15, 0,  128, 0, 0, 0, 0, 0, "", "is mage class");

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=10550;
insert into conditions values 
(14, 10550, 14802, 0, 0, 15, 0, 1279, 0, 0, 0, 0, 0, "", "is not warlock class"),
(14, 10550, 14803, 0, 0, 15, 0,  256, 0, 0, 0, 0, 0, "", "is warlock class");










UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168800;

UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168801;

UPDATE creature_template SET InhabitType=4 WHERE entry=39169;

update creature set MovementType=2 where guid=249461;

delete from creature_addon where guid=249461;
insert into creature_addon values 
(249461, 249461, 0, 0, 1, 0, "73558 73561 76354");

DELETE FROM waypoint_data WHERE id=249461;
INSERT INTO waypoint_data VALUES 
(249461, 1, 559.0062, 3129.964, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 2, 560.0029, 3130.044, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 3, 326.5816, 3279.51, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 4, 382.7708, 3216.926, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 5, 482.934, 3142.681, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 6, 579.6129, 3132.812, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 7, 666.1511, 3179.648, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 8, 718.8976, 3261.208, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 9, 723.8906, 3347.63, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 10, 678.632, 3452.148, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 11, 580.7639, 3507.673, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 12, 449.382, 3560.323, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 13, 318.5156, 3572.397, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 14, 247.0243, 3493.674, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 15, 260.033, 3397.564, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 16, 326.5816, 3279.51, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 17, 352.5559, 3244.171, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 18, 382.7708, 3216.926, 20.72534, 0, 0, 0, 0, 0, 0);

UPDATE creature_template_addon SET auras="" WHERE entry=35810;

UPDATE creature_addon SET auras="" WHERE guid in (246036, 246037, 246038, 248205, 248206, 248207);

UPDATE creature_template SET unit_flags=294912, unit_flags2=2048 WHERE entry=35810;

UPDATE gossip_menu_option SET option_id=1, npc_option_npcflag=1, OptionBroadcastTextID=36520, action_menu_id=10823 WHERE menu_id=10677 AND id=1;

UPDATE creature_template SET gossip_menu_id=10677, dynamicflags=0, ScriptName="npc_foreman_dampwick_35769" WHERE entry=35769;

delete from conditions where SourceTypeOrReferenceId=15  and SourceGroup=10677 and SourceEntry=1;
insert into conditions values 
(15, 10677, 1, 0, 0, 28, 0, 14248, 0, 0, 0, 0, 0, "", "Refresh my Memory: quest 14248 completed"),
(15, 10677, 1, 0, 0, 8, 0, 14248, 0, 0, 1, 0, 0, "",  "Refresh my Memory: quest 14248 not rewardet");

UPDATE creature SET MovementType=2 WHERE guid=246038;
UPDATE creature_addon SET path_id=246038 WHERE guid=246038;

DELETE FROM waypoint_data WHERE id=246038;
INSERT INTO waypoint_data VALUES 
(246038, 0, 490.440, 2972.38, 8.043484, 0.906249, 0, 0, 0, 0, 0),
(246038, 1, 490.328, 2972.63, 8.043484, 0.906249, 5000, 0, 0, 0, 0),
(246038, 2, 488.877, 2978.847, 7.925544, 1.858938, 0, 0, 0, 0, 0),
(246038, 3, 486.2259, 2979.748, 7.851083, 2.813982, 0, 0, 0, 0, 0),
(246038, 4, 485.2679, 2978.036, 7.930794, 4.32823, 5000, 0, 0, 0, 0),
(246038, 5, 486.2259, 2979.748, 7.851083, 2.813982, 0, 0, 0, 0, 0),
(246038, 6, 488.877, 2978.847, 7.925544, 1.858938, 0, 0, 0, 0, 0);

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14021;
UPDATE quest_template SET Flags=262144, SpecialFlags=0 WHERE Id=14021;

UPDATE quest_template SET PrevQuestId=14248 WHERE Id=14031;

UPDATE creature_template_addon SET path_id=0 WHERE entry=35813;

UPDATE creature_template SET MovementType=0 WHERE entry=35813;

UPDATE creature_template SET ScriptName="npc_frightened_miner_35813" WHERE entry=35813;

delete from creature_queststarter where id=35769 and quest=14031;

DELETE FROM waypoint_data WHERE id=3581301;
INSERT INTO waypoint_data VALUES 
(3581301, 0, 493.008850, 2975.830566, 7.926551, 0.964395, 0, 0, 0, 100, 0),
(3581301, 1, 505.048004, 2986.213135, 7.264693, 0.697359, 0, 0, 0, 100, 0),
(3581301, 2, 519.035706, 2969.260498, 8.533081, 5.488284, 0, 0, 0, 100, 0),
(3581301, 3, 540.347900, 2948.988770, 4.148690, 5.637507, 0, 0, 0, 100, 0);

delete from conditions where SourceTypeOrReferenceId=19  and SourceGroup=0 and SourceEntry=14031;
insert into conditions values 
(19, 0, 14031, 0, 0, 9, 0, 14021, 0, 0, 0, 0, 0, "", "Allow accept 14031 after 14021 taken");

DELETE FROM waypoint_data WHERE id=3581302;
INSERT INTO waypoint_data VALUES 
(3581302, 0, 552.432800, 2937.236572, 1.571852, 5.437247, 0, 0, 0, 100, 0),
(3581302, 1, 563.873352, 2933.236816, 0.304662, 5.959532, 0, 0, 0, 100, 0),
(3581302, 2, 574.958923, 2950.648926, -0.871740, 1.011521, 0, 0, 0, 100, 0),
(3581302, 3, 582.405334, 2959.478027, -2.108325, 0.870150, 0, 0, 0, 100, 0),
(3581302, 4, 589.242859, 2963.726807, -2.587548, 0.555990, 0, 0, 0, 100, 0),
(3581302, 5, 589.342773, 2964.532715, -2.464861, 1.741942, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581303;
INSERT INTO waypoint_data VALUES 
(3581303, 0, 598.932373, 2956.018311, -5.171926, 5.500074, 0, 0, 0, 100, 0),
(3581303, 1, 589.653931, 2937.744141, -7.592101, 4.314123, 0, 0, 0, 100, 0),
(3581303, 2, 584.266357, 2929.844482, -6.687585, 4.113848, 0, 0, 0, 100, 0),
(3581303, 3, 574.325500, 2907.105469, -7.570318, 4.506544, 0, 0, 0, 100, 0),
(3581303, 4, 575.571838, 2906.467773, -7.290232, 5.574685, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581304;
INSERT INTO waypoint_data VALUES 
(3581304, 0, 575.254578, 2915.179199, -7.424442, 2.248593, 0, 0, 0, 100, 0),
(3581304, 1, 568.493896, 2918.540527, -6.926721, 3.006502, 0, 0, 0, 100, 0),
(3581304, 2, 563.509521, 2894.124268, -9.127908, 4.498757, 0, 0, 0, 100, 0),
(3581304, 3, 570.895386, 2881.191895, -8.941821, 5.229178, 0, 0, 0, 100, 0),
(3581304, 4, 589.367859, 2869.831787, -7.200697, 5.731833, 0, 0, 0, 100, 0),
(3581304, 5, 606.872986, 2860.528076, -6.730551, 5.794664, 0, 0, 0, 100, 0),
(3581304, 6, 608.440063, 2857.149902, -7.145034, 5.072102, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581305;
INSERT INTO waypoint_data VALUES 
(3581305, 0, 621.382935, 2888.383789, -4.491171, 1.235363, 0, 0, 0, 100, 0),
(3581305, 1, 625.539978, 2912.528564, -1.920422, 1.400297, 0, 0, 0, 100, 0),
(3581305, 2, 635.507141, 2922.693604, -0.679687, 0.811248, 0, 0, 0, 100, 0),
(3581305, 3, 654.337280, 2931.954346, 0.180412, 0.489235, 0, 0, 0, 100, 0),
(3581305, 4, 666.322205, 2947.070557, -0.068140, 1.031160, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581306;
INSERT INTO waypoint_data VALUES 
(3581306, 0, 660.770020, 2940.163330, 0.073123, 4.035314, 0, 1, 0, 100, 0),
(3581306, 1, 655.257446, 2936.646973, 0.649165, 3.709374, 0, 1, 0, 100, 0),
(3581306, 2, 626.537354, 2912.329102, -1.972860, 3.897870, 0, 1, 0, 100, 0),
(3581306, 3, 617.258362, 2878.102539, -4.873388, 4.447648, 0, 1, 0, 100, 0),
(3581306, 4, 607.747620, 2871.329346, -5.575698, 3.760426, 0, 1, 0, 100, 0),
(3581306, 5, 574.772766, 2887.711426, -7.991757, 2.680503, 0, 1, 0, 100, 0),
(3581306, 6, 567.091003, 2904.979736, -8.285954, 1.989353, 0, 1, 0, 100, 0),
(3581306, 7, 583.231628, 2926.404053, -6.645783, 0.925138, 0, 1, 0, 100, 0),
(3581306, 8, 599.777161, 2952.090332, -6.146738, 0.999751, 0, 1, 0, 100, 0),
(3581306, 9, 588.531677, 2961.839111, -2.787853, 2.460592, 0, 1, 0, 100, 0),
(3581306, 10, 576.072510, 2955.392822, -1.200582, 3.619055, 0, 1, 0, 100, 0),
(3581306, 11, 561.765686, 2933.269531, 0.424554, 4.078513, 0, 1, 0, 100, 0),
(3581306, 12, 551.877625, 2937.384277, 1.642743, 2.747263, 0, 1, 0, 100, 0),
(3581306, 13, 518.457947, 2971.775391, 8.817685, 2.331002, 0, 1, 0, 100, 0),
(3581306, 14, 502.113647, 2986.438232, 7.374378, 2.448811, 0, 1, 0, 100, 0),
(3581306, 15, 488.268585, 2972.944580, 8.162946, 3.992119, 0, 1, 0, 100, 0);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Verängstigter Minenarbeiter", QuestGiverTargetName_loc3="Verängstigter Minenarbeiter" WHERE Id=14021;

UPDATE creature_template SET unit_flags=33555200 WHERE entry=35814;

UPDATE creature_template SET AIName="", ScriptName="npc_capturing_the_unknown_bunny" WHERE entry in (37872, 37895, 37896, 37897);

delete from smart_scripts where entryorguid in (37872, 37895, 37896, 37897);

UPDATE item_template SET FlagsExtra=196673 WHERE entry=49887;

DELETE FROM  spell_linked_spell WHERE spell_trigger=70649 AND spell_effect=92169;

delete from spell_scripts where id=68280;

delete from spell_linked_spell where spell_trigger in (68280, 68281);

