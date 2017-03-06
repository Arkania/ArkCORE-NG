
delete from creature_addon where guid=254346;

delete from gameobject where guid=169095 and id=202104;

UPDATE creature_template_addon SET auras="66727" WHERE entry=38111;

delete from gossip_menu where entry=11568;
insert into gossip_menu values
(11568, 16143);

DELETE FROM gossip_menu_option WHERE menu_id=11568;
INSERT INTO gossip_menu_option VALUES 
(11568, 0, 5, "Make this inn your home.", 2822, 8, 65536, 0, 0, 0, 0, 0, "", 0),
(11568, 1, 0, "What can I do at an inn?", 4308, 1, 1, 11570, 0, 0, 0, 0, "", 0);

DELETE FROM gossip_menu_option WHERE menu_id=11570;
INSERT INTO gossip_menu_option VALUES 
(11570, 0, 0, "When you stay at an inn, you rest very comfortably.  Because of this, you will become \"well rested\" much more quickly than you would in the wilderness.  When you are well rested, you learn more from experience.$B$BYou may also speak with any innkeeper to get a hearthstone, and can later use the hearthstone in order to quickly return to that inn.", 4309, 8, 65536, 0, 0, 0, 0, 0, "", 0);

DELETE FROM creature WHERE id=38409 AND guid=945;
INSERT INTO creature VALUES 
(945, 38409, 648, 0, 0, 1, "", 443, 0, 0, 912.889, 2357.54, 5.2628, 3.22886, 120, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE quest_template SET PrevQuestId=24924 WHERE Id=24929;

UPDATE quest_template SET PrevQuestId=24924 WHERE Id=24925;

UPDATE quest_template SET PrevQuestId=24744 WHERE Id=24816;

UPDATE quest_template SET PrevQuestId=25110 WHERE Id=25122;

UPDATE quest_template SET PrevQuestId=25110, NextQuestIdChain=25125 WHERE Id=25123;

UPDATE quest_template SET NextQuestIdChain=25184 WHERE Id=25125;

UPDATE quest_template SET PrevQuestId=25213 WHERE Id=25243;

UPDATE quest_template SET PrevQuestId=25213 WHERE Id=25244;

UPDATE quest_template SET PrevQuestId=25213 WHERE Id=25243;

UPDATE quest_template SET PrevQuestId=25243 WHERE Id=25251;

UPDATE quest_template SET NextQuestIdChain=25066 WHERE Id=25024;

UPDATE quest_template SET PrevQuestId=25023, NextQuestId=25066 WHERE Id=25058;

delete from creature_queststarter where id in (1737, 38120) and quest=27139;

UPDATE quest_template SET Method=2, Flags=524288, QuestGiverPortrait=30969 WHERE Id=24671;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Wilde Glucken", QuestGiverTargetName_loc3="Wilde Glucken" WHERE Id=24671;

UPDATE quest_template SET QuestGiverTextWindow="Wild Cluckers", QuestGiverTargetName="Wild Cluckers" WHERE Id=24671;

UPDATE creature_template SET AIName="", ScriptName="npc_wild_clucker_38111" WHERE entry=38111;

DELETE FROM creature WHERE guid IN (945, 2000, 2001);
INSERT INTO creature VALUES 
(2000, 38409, 648, 4720, 4871, 1, "", 444, 0, 1, 913.690, 2357.08, 5.17122, 3.40152, 300, 0, 0, 102, 0, 0, 0, 0, 0), 
(2001, 38409, 648, 4720, 4871, 1, "", 444, 0, 1, 912.240, 2356.23, 5.33573, 0.63691, 300, 0, 0,  86, 0, 0, 0, 0, 0), 
( 945, 38409, 648, 4720, 4871, 1, "", 444, 0, 0, 911.817, 2358.12, 5.19424, 5.66347, 120, 0, 0,   0, 0, 0, 0, 0, 0);

UPDATE creature_template SET gossip_menu_id=0 WHERE entry=38409;

UPDATE creature_template SET npcflag=1 WHERE entry=38111;

delete from smart_scripts where entryorguid=38111;

update gameobject set phaseIds="180" where id=201972;

delete from smart_scripts where entryorguid=38195;

UPDATE gameobject_template SET ScriptName="go_raptor_trap_201972" WHERE entry=201972;

UPDATE gameobject_template SET ScriptName="go_raptor_egg_201974" WHERE entry=201974;

UPDATE creature_template SET AIName="", ScriptName="npc_wild_clucker_egg_38195" WHERE entry=38195;

UPDATE creature_template SET faction=2204, unit_flags=33555208, unit_flags2=34816 WHERE entry=38195;

DELETE FROM creature_template_addon WHERE entry=38195;
INSERT INTO creature_template_addon VALUES 
(38195, 0, 0, 0, 1, 0, "71355");

UPDATE creature_template SET ScriptName="npc_spiny_raptor_38187" WHERE entry=38187;

delete from spell_script_names where spell_id=68445;
insert into spell_script_names values 
(68445, "spell_lightning_strike_68445");

UPDATE gameobject_template SET flags=4 WHERE entry=201972;

UPDATE gameobject_loot_template SET QuestRequired=1 WHERE entry=201974 AND item=50239;

UPDATE gameobject_template SET data8=24741 WHERE entry=201974;



