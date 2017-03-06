
update quest_template set NextQuestIdChain=0 where Id=26639;

update quest_template set flags=0, SpecialFlags=0 where Id=26646;
update quest_template set RequiredSourceItemId1=60384, RequiredSourceItemCount1=1 where Id=26646;
update quest_template set RequiredSourceItemId2=59261, RequiredSourceItemCount2=1 where Id=26646;
update quest_template set RequiredSourceItemId3=0, RequiredSourceItemCount3=0 where Id=26646;
update quest_template set RequiredSourceItemId4=0, RequiredSourceItemCount4=0 where Id=26646;

update creature_template set AIName="", ScriptName="npc_jorgensen_43546" where entry=43546;
update creature_template set AIName="", ScriptName="npc_munitions_dump" where entry=43589;
update creature_template set AIName="", ScriptName="npc_blackrock_tower" where entry=43590;
update creature_template set AIName="", ScriptName="npc_bravo_company_trigger" where entry=43594;

update gameobject_template set Data0=1691 where entry=204437;

SET @ENTRY=43594;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid`=4 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(@ENTRY, 4, 0, "Bravo Company Field Kit ACTIVE. New abilities are now available on your action bar.$BToggle Bravo Company Field Kit to DEACTIVATE.", 42, 0, 0, 0, 44418);

update creature_text set type=42 where entry=@ENTRY and groupid between 0 and 4 and id=0;

SET @ENTRY=7013;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid`=0 AND `id`in (0,1,2,3);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(@ENTRY, 0, 0, "Ag throm'k ruk kazum", 12, 0, 0, 0, 0),
(@ENTRY, 0, 1, "Grom Lok zug zil'no", 12, 0, 0, 0, 0),
(@ENTRY, 0, 2, "n tov'nokaz kil Moth'kazoroth Moguna Tov'osh", 41, 0, 0, 0, 0),
(@ENTRY, 0, 3, "Nakaz kil Zugas zug Moth'kazoroth", 12, 0, 0, 0, 0);

update gameobject_template set AIName="", ScriptName="go_blackrock_holding_pen" where entry=204435;
update gameobject_template set AIName="", ScriptName="go_blackrock_holding_pen" where entry=204441;
update gameobject_template set AIName="", ScriptName="go_blackrock_holding_pen" where entry=204442;

update quest_template set RequiredSourceItemId1=60385, RequiredSourceItemCount1=1 where Id=26651;
update quest_template set RequiredSourceItemId4=0, RequiredSourceItemCount4=0 where Id=26651;

delete from gameobject where guid in (216215,216216);
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(216215, 301069, 0, 1, 1, -9722.23, -3117.51, 60.2717, 3.09557, 0, 0, 0.999735, 0.0230078, 300, 0, 1),
(216216, 301069, 0, 1, 1, -9738.88, -3185.51, 81.996, 0.330976, 0, 0, 0.164734, 0.986338, 300, 0, 1);

delete from creature where guid in (16747,34523,45716,45801,66405,80705);

update creature_template set AIName="", ScriptName="npc_blackrock_grunt" where entry=440;
update creature_template set AIName="", ScriptName="npc_blackrock_outrunner" where entry=485;
update creature_template set AIName="", ScriptName="npc_blackrock_guard" where entry=7013;
update creature_template set AIName="", ScriptName="npc_blackrock_drake_rider" where entry=43533;
update creature_template set AIName="", ScriptName="npc_blackrock_warden" where entry=43535;

delete from spell_script_names where spell_id=82585;
insert into spell_script_names values (82585,"spell_plant_seaforium");

update gameobject_template set AIName="", ScriptName="go_blackrock_tower_or_munitions_hut" where entry=301069;

update quest_template set SourceItemId=60384, SourceItemCount=1 where Id=26646;   -- core is fixed
update quest_template set SourceItemId=60385, SourceItemCount=1 where Id=26651;   -- core is fixed




