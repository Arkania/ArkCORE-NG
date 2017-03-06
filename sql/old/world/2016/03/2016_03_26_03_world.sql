

-- fix issue #116 part 5
UPDATE locales_quest SET OfferRewardText_loc3="Als Ihr die Ruinen des Lagers betrachtet, hört Ihr ein Flüstern hinter Euch.$B$B<Ich könnte Euch jetzt sofort töten, wenn ich wollte. Passt besser auf Euch auf, $R.>", CompletedText_loc3="Kehrt zu Hochexekutor Derrington am Bollwerk in Tirisfall zurück." WHERE Id=25010;

UPDATE quest_template SET QuestGiverPortrait=31304 WHERE Id=25046;

UPDATE locales_quest SET OfferRewardText_loc3="Von der Wiege über die Bahre in den Untod folgen wir alle unserem eigenen Weg. Die mancher sind leichter als andere. Es hört sich an, als wäre der Weg dieses Mädchens Voss bis jetzt hart gewesen.$B$BHoffentlich entschließt sie sich am Ende, uns beizutreten und der Dunklen Fürstin zu folgen. Mit Macht wie ihrer könnten wir unglaubliches leisten.$B$BÜbrigens, $N... großartige Arbeit da draußen. Wenn Ihr jemals Zeit und Lust habt, habe ich vielleicht etwas Arbeit in den Pestländern für Euch.", CompletedText_loc3="Kehrt zu Hochexekutor Derrington am Bollwerk in Tirisfall zurück." WHERE Id=25046;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Hohepriester Benedictus Voss", QuestGiverTargetName_loc3="Hohepriester Voss" WHERE Id=25046;

UPDATE quest_template SET SourceSpellId=73306 WHERE Id=25046;

update creature_template set AIName="", ScriptName="npc_lilian_voss_39038" where entry=39038;
update creature_template set AIName="", ScriptName="" where entry=39097; -- Benedictus
update creature_template set AIName="", ScriptName="" where entry=1660; -- BodyGuard
update creature_template set AIName="", ScriptName="" where entry=1665; -- Melrache

delete from smart_scripts where entryorguid in (4284, 4285); 
update creature_template set AIName="" where entry in (4284, 4285);

delete from spell_script_names where spell_id=73307;
insert into spell_script_names values
(73307, "spell_lilians_brain_burst_73307");

delete from spell_script_names where spell_id=73308;
insert into spell_script_names values
(73308, "spell_lilians_shadow_hop_73308");

delete from spell_script_names where spell_id=73309;
insert into spell_script_names values
(73309, "spell_lilians_death_grip_73309");

update creature_text set type=12 where entry in (1535, 1536, 1537, 1538, 1539, 1540) and type=0;

SET @Scarlet1:=   1538;
SET @Scarlet2:=   1540;
SET @Scarlet3:=   1539;
SET @Scarlet4:=   1537;
SET @Scarlet5:=   1536;
SET @Scarlet6:=   1535;

UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet1;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet2;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet3;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet4;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet5;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@Scarlet6;

DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet1 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet2 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet3 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet4 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet5 AND `source_type` = 0;
DELETE FROM `smart_scripts` WHERE `entryorguid` = @Scarlet6 AND `source_type` = 0;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(@Scarlet1, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet2, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet3, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet4, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet5, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet6, 0, 0, 0, 4, 0, 100, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Scarlet - On Aggro - talk'),
(@Scarlet1, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 10000, 10000, 11, 64431, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet1 - IC - CAST Death Grip'),
(@Scarlet1, 0, 2, 0, 0, 0, 100, 0, 4000, 4000, 18000, 18000, 11, 75967, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet1 - IC - CAST Whirlwind'),
(@Scarlet2, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 10000, 10000, 11, 64431, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet2 - IC - CAST Death Grip'),
(@Scarlet2, 0, 2, 0, 0, 0, 100, 0, 2000, 2000, 180000, 180000, 11, 7164, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet2 - IC - CAST Defensive Stance'),
(@Scarlet2, 0, 3, 0, 0, 0, 100, 0, 5000, 5000, 8000, 8000, 11, 11972, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet2 - IC - CAST Shield Bash'),
(@Scarlet3, 0, 1, 0, 0, 0, 100, 0, 1000, 1000, 10000, 10000, 11, 64431, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet3 - IC - CAST Death Grip'),
(@Scarlet3, 0, 2, 0, 0, 0, 100, 0, 2000, 2000, 30000, 30000, 11, 12544, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet3 - IC - CAST Frost Armor'),
(@Scarlet3, 0, 3, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 11, 13322, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet3 - IC - CAST Frostbolt'),
(@Scarlet4, 0, 1, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 11, 84535, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet4 - IC - CAST Zealotry'),
(@Scarlet5, 0, 1, 0, 0, 0, 100, 0, 5000, 5000, 4000, 4000, 11, 9053, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet5 - IC - CAST Fireball'),
(@Scarlet6, 0, 1, 0, 0, 0, 100, 0, 5000, 5000, 5000, 5000, 11, 57846, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Scarlet6 - IC - CAST Heroic Strike');

SET @GUID=3903801;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 3059.823, -559.4528, 126.3512, 0.037286, 500, 0),
(@GUID, 1, 3061.642, -559.3849, 126.6539, 0.037286, 0, 0),
(@GUID, 2, 3075.395, -558.8719, 126.7179, 0.037286, 0, 0),
(@GUID, 3, 3075.395, -558.8719, 126.7179, 0.037286, 500, 0);

SET @GUID=3903802;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, 3075.395, -558.8719, 126.7179, 3.312397, 500, 0),
(@GUID, 1, 3063.028, -559.3329, 126.715, 3.174953, 0, 0),
(@GUID, 2, 3039.041, -560.8643, 121.656, 3.210295, 0, 0),
(@GUID, 3, 3039.041, -560.8643, 121.656, 3.210295, 500, 0);




