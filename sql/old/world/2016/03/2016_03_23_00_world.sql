
-- misc duskhaven
UPDATE quest_template SET PrevQuestId=14320, RewardSpell=0 WHERE Id=14321;

DELETE FROM spell_phase WHERE spell_id=68481;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(68481, 4096, 638, 683);
 
DELETE FROM spell_phase WHERE spell_id=68482;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(68482, 8192, 638, 683);

DELETE FROM spell_phase WHERE spell_id=68483;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(68483, 16384, 655, 683);

update creature_template set AIName="", Scriptname="npc_gwen_armstead_34571" where entry=34571;

UPDATE quest_template SET PrevQuestId=14336 WHERE Id=14347;

UPDATE quest_template SET PrevQuestId=14336 WHERE Id=14348;

update npc_text set BroadcastTextID0=36319 where ID=14938;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Eindringling der Verlassenen", QuestGiverTargetName_loc3="Eindringling der Verlassenen" WHERE Id=14347;

UPDATE quest_template SET Flags=8, QuestGiverTextWindow="Horrid Abomination", QuestGiverTargetName="Horrid Abomination" WHERE Id=14348;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Entsetzliche Monstrosität", QuestGiverTargetName_loc3="Entsetzliche Monstrosität" WHERE Id=14348;

UPDATE quest_template SET PrevQuestId=14347 WHERE Id=14366;

delete from spell_script_names where spell_id=69094;
insert into spell_script_names values
(69094, "spell_cast_keg_69094");

update creature set spawntimesecs=120 where id=36231;

delete from creature_text where entry=36231;
INSERT INTO `creature_text` VALUES (36231, 0, 0, "GAH!!!!  I CAN'T SEE IN HERE!!!!", 12, 0, 100, 0, 0, 20908, "Abo 1", 36310);
INSERT INTO `creature_text` VALUES (36231, 0, 1, "Barrel smell like gunpowder...", 12, 0, 100, 0, 0, 20909, "Abo 2", 36311);
INSERT INTO `creature_text` VALUES (36231, 0, 2, "This not be good...", 12, 0, 100, 0, 0, 20910, "Abo 3", 36312);
INSERT INTO `creature_text` VALUES (36231, 0, 3, "Uh-oh... this gonna hurts me...", 12, 0, 100, 0, 0, 20911, "Abo 4 ", 36313);
INSERT INTO `creature_text` VALUES (36231, 0, 4, "I gots bad feeling...", 12, 0, 100, 0, 0, 20912, "Abo 5", 36314);
INSERT INTO `creature_text` VALUES (36231, 0, 5, "Get back here!  I smashes you!", 12, 0, 100, 0, 0, 20913, "Abo 6", 36315);

delete from quest_poi where  questId in (14367, 14395, 14396) and id=0 and objIndex=-1;

update creature set spawndist=0, MovementType=0 where id=36693;

delete from gameobject where guid=166835 and id=196411;

update gameobject set phaseMask=28672 where guid=166844 and id=196404;

delete from gameobject where guid=166843 and id=206693;

update gameobject_template set faction=114, flags=32 where entry in (196404, 196411);

UPDATE quest_template SET PrevQuestId=14386 WHERE Id=14396;

UPDATE quest_template SET PrevQuestId=14367 WHERE Id=14369;

UPDATE quest_template SET PrevQuestId=14367 WHERE Id=14382;

UPDATE quest_template SET PrevQuestId=14367 WHERE Id=14368;

update npc_text set BroadcastTextID0=36556 where ID=15013;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Kämpfer der Verlassenen", QuestGiverTargetName_loc3="Kämpfer der Verlassenen" WHERE Id=14369;

delete from creature_text where entry=36289 and groupid=0 and id=2;
update creature_text set groupid=1, id=0 where entry=36289 and groupid=0 and id=1;

delete from creature_text where entry=36289;
INSERT INTO `creature_text` VALUES (36289, 0, 0, "Your mother's in the basement next door.  Get to her now!", 12, 0, 100, 0, 0, 0, "", 36328);
INSERT INTO `creature_text` VALUES (36289, 1, 0, "Don't hurt me!  I was just looking for my sisters!  I think Ashley's inside that house!", 12, 0, 100, 0, 0, 0, "", 36324);

delete from creature_text where entry=36288;
INSERT INTO `creature_text` VALUES (36288, 0, 0, "Join the others inside the basement next door.  Hurry!", 12, 0, 100, 0, 0, 0, "", 36331);
INSERT INTO `creature_text` VALUES (36288, 1, 0, "Are you one of the good worgen, $Gmister:ma'am;?  Did you see Cynthia hiding in the sheds outside?", 12, 0, 100, 0, 0, 0, "", 36326);

delete from creature_text where entry=36287;
INSERT INTO `creature_text` VALUES (36287, 0, 0, "It's not safe here.  Go to the Allens' basement.", 12, 0, 100, 0, 0, 0, "", 36329);
INSERT INTO `creature_text` VALUES (36287, 1, 0, "You are scary!  I just want my mommy!", 12, 0, 100, 0, 0, 0, "", 36325);

delete from smart_scripts where entryorguid in (36287, 36288, 36289);

update creature_template set AIName="", ScriptName="npc_cynthia_36267" where entry=36287;
update creature_template set AIName="", ScriptName="npc_james_36268" where entry=36288;
update creature_template set AIName="", ScriptName="npc_ashley_36269" where entry=36289;

delete from gossip_menu where entry in (36287, 36288, 36289);
delete from gossip_menu_option where menu_id in (36287, 36288, 36289);

delete from creature where guid=270315 and id=34793;

UPDATE creature_template SET npcflag=16777216, unit_flags2=4196352, VehicleId=516 WHERE entry=36283;
UPDATE creature_template SET faction=1735, spell2=0, mechanic_immune_mask=16384 WHERE entry=36283;

delete from creature where guid between 116836 and 116860 and id=36286;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(116836, 36286, 654, 1, 65535, 11686, 0, -2238.09, 2557.53, 20.4911, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116837, 36286, 654, 1, 65535, 11686, 0, -2229.24, 2565.48, 8.74696, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116838, 36286, 654, 1, 65535, 11686, 0, -2215.69, 2580.56, 14.6174, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116839, 36286, 654, 1, 65535, 11686, 0, -2202.28, 2589.49, 19.6422, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116840, 36286, 654, 1, 65535, 11686, 0, -2149.63, 2644.01, 26.5928, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116841, 36286, 654, 1, 65535, 11686, 0, -2137.02, 2655.3, 20.1049, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116842, 36286, 654, 1, 65535, 11686, 0, -2127.53, 2664.09, 8.33806, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116843, 36286, 654, 1, 65535, 11686, 0, -2114.29, 2679.66, 14.2676, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116844, 36286, 654, 1, 65535, 11686, 0, -2101.91, 2688.91, 19.3181, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116845, 36286, 654, 1, 65535, 11686, 0, -1945.19, 2524.12, 1.48521, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116846, 36286, 654, 1, 65535, 11686, 0, -1939.78, 2562.5, 14.4454, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116847, 36286, 654, 1, 65535, 11686, 0, -1935.31, 2556.95, 21.4788, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116848, 36286, 654, 1, 65535, 11686, 0, -1934, 2565.76, 24.5374, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116849, 36286, 654, 1, 65535, 11686, 0, -1921.34, 2557.3, 30.927, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116850, 36286, 654, 1, 65535, 11686, 0, -1918.36, 2578.03, 1.59042, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116851, 36286, 654, 1, 65535, 11686, 0, -1914.4, 2517.61, 2.25322, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116852, 36286, 654, 1, 65535, 11686, 0, -1893.56, 2561.07, 1.55054, 0, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116853, 36286, 654, 1, 65535, 11686, 0, -1865.78, 2545.12, 31.4739, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116854, 36286, 654, 1, 65535, 11686, 0, -1858.74, 2560.08, 15.8903, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116855, 36286, 654, 1, 65535, 11686, 0, -1853.79, 2553.17, 12.6827, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116856, 36286, 654, 1, 65535, 11686, 0, -1954.322021, 2597.588135, 1.393246, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116857, 36286, 654, 1, 65535, 11686, 0, -1996.017944, 2528.118652, 1.392167, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116858, 36286, 654, 1, 65535, 11686, 0, -2056.107422, 2470.821289, 2.936605, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116859, 36286, 654, 1, 65535, 11686, 0, -2015.068848, 2576.249268, -3.299848, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0),
(116860, 36286, 654, 1, 65535, 11686, 0, -2086.064453, 2451.008545, 7.420637, 4.2586, 300, 3, 0, 4120, 0, 1, 0, 0, 0);

delete from npc_spellclick_spells where npc_entry=36283;
insert into npc_spellclick_spells values 
(36283, 46598, 0, 0); -- for forsaken passenger

delete from npc_spellclick_spells where npc_entry=36292;
insert into npc_spellclick_spells values 
(36292, 46598, 0, 0); -- for forsaken passenger

delete from vehicle_template_accessory where entry=36283 and accessory_entry=36292;
INSERT INTO `vehicle_template_accessory` VALUES (36283, 36292, 0, 0, 'Forsaken Catapult', 6, 30000); -- seat 0

update creature_template set AIName="", ScriptName="npc_forsaken_catapult_36283" where entry=36283;

delete from spell_script_names where spell_id=68659;
insert into spell_script_names values 
(68659,"spell_launch_68659");

delete from spell_script_names where spell_id=68591;
insert into spell_script_names values 
(68591,"spell_fire_boulder_68591");

delete from creature where guid in (252212,252210,212213,252208,252204,252203,252205,251031,252200,252198,252199);
delete from creature where guid in (252201,252202,252172,252193,252194,252192,252190,252191,252189,252196,252197,252195);

delete from creature where id=36809;

DELETE FROM creature_addon WHERE guid=212213;

update creature set spawntimesecs=120 where id in (36283, 36312);

delete from creature where guid in (252156, 252159);

delete from creature where id in (36405, 36409);

update creature set phaseMask=10241 where id=36198;

update creature_template set AIName="", ScriptName="npc_mastiff_36405" where entry=36405;

update creature_template set AIName="", ScriptName="npc_mastiff_36409" where entry=36409;



