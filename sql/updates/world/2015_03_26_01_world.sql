
update quest_template set Method=2, RequiredSourceItemId1=52283, RequiredSourceItemCount1=1,RequiredSourceItemId4=0, RequiredSourceItemCount4=0 where Id=24623;

delete from creature_queststarter where id=39157 and quest=24623;

update creature_template set AIName="", ScriptName="npc_lost_bloodtalon_hatchling" where entry=39157;

SET @GUID:=90057;
SET @ID:=37989;
SET @PATHID:=90057;

DELETE FROM `creature` WHERE `guid`=@GUID AND `id`=@ID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`curhealth`,`MovementType`) VALUES 
(@GUID, @ID,1,1,1,31292,-1609.99,-5362.79,3.79,0.90,300,71,2);

DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`) VALUES 
(@GUID,@PATHID);

DELETE FROM `waypoint_data` WHERE `id`=@PATHID;
INSERT INTO `waypoint_data` 
(`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`) VALUES 
(@PATHID,1,-1592.48,-5369.92,2.81,0.00,0,0,0,100),
(@PATHID,2,-1593.47,-5369.74,2.81,0.00,0,0,0,100),
(@PATHID,3,-1612.69,-5366.18,3.24,0.00,0,0,0,100),
(@PATHID,4,-1609.57,-5362.27,3.87,0.00,0,0,0,100),
(@PATHID,5,-1607.08,-5359.13,4.62,0.00,0,0,0,100),
(@PATHID,6,-1604.59,-5356.00,5.24,0.00,0,0,0,100),
(@PATHID,7,-1600.85,-5351.30,5.87,0.00,0,0,0,100),
(@PATHID,8,-1599.41,-5349.48,6.14,0.00,0,0,0,100),
(@PATHID,9,-1599.41,-5349.48,6.14,0.00,0,0,0,100);

update creature_template set AIName="", ScriptName="npc_swiftclaw_37989" where entry=37989;
update creature_template set AIName="", ScriptName="npc_swiftclaw_38002" where entry=38002;


