
-- update from roger and me..

-- creature edit to make them kneel, moving while laying down looks silly.
UPDATE creature_addon SET bytes1=8,bytes2=257 WHERE guid IN(138717,138921,138526,115716,71924,70599);

 -- added some creature say,
DELETE FROM `creature_text` WHERE `entry`=33266;
insert into creature_text values
(33266, 0, 0, "Blood and thunder, $R!", 12, 0, 100, 0, 0, 0, "", 33419),
(33266, 0, 1, "For the Horde!", 12, 0, 100, 0, 0, 0, "", 33420),
(33266, 0, 2, "Death to the Alliance!", 12, 0, 100, 0, 0, 0, "", 33421),
(33266, 0, 3, "Many thanks, $C!", 12, 0, 100, 0, 0, 0, "", 33422);

update creature_template set AIName="", ScriptName="" where entry=3397;
delete from smart_scripts where entryorguid=3397;

update creature_template set AIName="", ScriptName="" where entry=3275;
delete from smart_scripts where entryorguid=3275;

update creature_template set AIName="", ScriptName="" where entry=3274;
delete from smart_scripts where entryorguid=3274;

update creature_template set AIName="", ScriptName="npc_wyneth_34846" where entry=34846;
delete from smart_scripts where entryorguid=34846;
update creature set spawndist=0, MovementType=0 where id=34846;

delete from creature where id=3395;
delete from smart_scripts where entryorguid=3395;

update creature set spawndist=0, MovementType=0 where guid=129693;

delete from creature_text where entry=3395;
insert into creature_text values
(3395, 0, 0, "I am summoned!  Intruders, come to my tent and face your death!", 14, 1, 100, 0, 0, 0, "Verog the Dervish", 1079);

update creature_template set AIName="", ScriptName="npc_verog_the_dervish_3395" where entry=3395;

update gameobject_template set data0=70 where entry=152618;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Meldet Euch bei Dorak südlich des Fernwachtaußenpostens im Nördlichen Brachland.", QuestGiverTextWindow_loc3="Angeketteter Wolf", QuestGiverTargetName_loc3="Angeketteter Wolf" WHERE Id=13878;

delete from creature where id=5198 and guid=83639;

update creature set modelid=17188 where id=34287;
update creature_template set faction=35, AIName="", ScriptName="npc_chain_origin_34287" where entry=34287;
update creature_template set faction=35, AIName="", ScriptName="npc_trapped_wolf_34285" where entry=34285;

update gameobject_template set AIName="", ScriptName="go_wolf_chains" where entry in (195001, 195003, 195004);

SET @PATHID=1165501;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, -5.189373, -3628.974, 27.33608, 0.893084, 0, 1),
(@PATHID, 1, 5.766781, -3615.141, 27.23636, 0.889157, 0, 1),
(@PATHID, 2, 20.17663, -3548.328, 28.73955, 1.368249, 0, 1);

delete from quest_poi where questId=13878;
insert into quest_poi values
(13878, 0, 0, 1, 11, 0, 0, 3);

delete from quest_poi_points where questId=13878 and id=1;

update creature set spawndist=15, MovementType=1 where id=3246;
