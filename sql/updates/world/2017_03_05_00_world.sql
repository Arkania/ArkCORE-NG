UPDATE creature_equip_template SET id=1 WHERE entry=35234;
DELETE FROM creature_addon WHERE guid=285379;
UPDATE quest_template SET SpecialFlags=2 WHERE id in (9611, 9625, 9678, 9713, 9926, 10004, 10211, 10231, 10299, 10198, 10344, 10406, 10409, 10525, 10297, 10594, 9836);
UPDATE `creature_template` SET `ScriptName`='npc_sally_salvager_sandscrew_37761' WHERE `entry`='37761';
UPDATE `creature_template` SET `ScriptName`='npc_brett_coins_mcquid_37762' WHERE `entry`='37762';
UPDATE `creature_template` SET `ScriptName`='npc_injured_employee_48305' WHERE `entry`='48305';
