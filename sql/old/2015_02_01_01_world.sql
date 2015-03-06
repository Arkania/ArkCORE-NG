
update creature_template set InhabitType=4 where entry=43275;

update quest_template set Flags=11534336, SpecialFlags=2 where Id=26512;
update quest_template set ObjectiveText1="Go to the Lakeshire Graveyard", RequiredNpcOrGo1=47971, RequiredNpcOrGoCount1=1, RequiredSpellCast1=0  where Id=26512;
update quest_template set ObjectiveText2="", RequiredNpcOrGo2=81769, RequiredNpcOrGoCount2=0, RequiredSpellCast2=81769  where Id=26512;

update quest_template set Flags=8912896, SpecialFlags=4 where Id=26573;

update quest_template set PrevQuestId=26568 where Id in (26569,26570,26571);
update quest_template set PrevQuestId=26514 where Id=26519;

delete from creature where guid=269875 and id=43184;
insert INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(269875, 43184, 0, 1, 1, 0, 0, -9203.84, -2155.79, 57.187, 6.565, 120, 0, 0, 1, 0, 0, 0, 0, 0);

DELETE FROM `creature_addon` WHERE (`guid`=269875);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (269875, 0, 0, 0, 0, 0, "81201");

update creature set spawntimesecs=120 where id in (43248,43249);



