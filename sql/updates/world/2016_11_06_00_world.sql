

UPDATE creature_template SET AIName="", ScriptName="npc_elm_general_purpose_bunny_23837" WHERE entry=23837;

UPDATE creature SET areaId=4781, zoneId=4720, phaseIds="179", position_x=850.2563, position_y=2755.958, position_z=116.8384, orientation=1.4696 WHERE guid=246072;

UPDATE quest_template SET QuestGiverPortrait=30177, Flags=262144 WHERE Id=14244;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Raketenschleuder", QuestGiverTargetName_loc3="Raketenschleuder" WHERE Id=14244;

UPDATE quest_template SET QuestGiverTextWindow="Rocket Sling", QuestGiverTargetName="Rocket Sling" WHERE Id=14244;

UPDATE creature SET phaseIds="179" WHERE id=36470;

UPDATE creature_template SET ScriptName="npc_warrior_matic_nx__36525" WHERE entry=36525;

UPDATE creature_template SET ScriptName="npc_sassy_hardwrench_36425" WHERE entry=36425;

UPDATE creature_template SET ScriptName="npc_orc_survivor_36421" WHERE entry=36421;

UPDATE creature_template SET ScriptName="npc_trade_prince_gallywix_36513" WHERE entry=36513;

UPDATE creature_text SET comment="Trade Prinz Gallywix" WHERE entry=36513 AND groupid=0 AND id=0;

UPDATE creature_text SET emote=25, comment="Trade Prinz Gallywix" WHERE entry=36513 AND groupid=1 AND id=0;

delete from creature where guid =246048 and id=36513;

UPDATE gameobject_template SET ScriptName="go_rocket_sling_196439" WHERE entry=196439;

UPDATE creature_template SET ScriptName="npc_sling_rocket_36514" WHERE entry=36514;

UPDATE creature_template SET minlevel=10, maxlevel=10, unit_flags=33555200, VehicleId=525, InhabitType=4 WHERE entry=36514;

DELETE FROM creature_template_addon WHERE entry=36514;
INSERT INTO creature_template_addon VALUES 
(36514, 0, 0, 50331648, 1, 0, "");

DELETE FROM waypoint_data WHERE id=3651401;
INSERT INTO waypoint_data VALUES 
(3651401, 0, 878.42, 2740.18, 130.8673, 0, 0, 1, 0, 0, 0),
(3651401, 1, 882.4566, 2726.064, 146.0856, 0, 0, 1, 0, 0, 0),
(3651401, 2, 890.9149, 2697.69, 164.5292, 0, 0, 1, 0, 0, 0),
(3651401, 3, 916.3698, 2591.611, 207.5022, 0, 0, 1, 0, 0, 0),
(3651401, 4, 928.4583, 2538.972, 196.3079, 0, 0, 1, 0, 0, 0),
(3651401, 5, 932.9393, 2506.701, 167.4186, 0, 0, 1, 0, 0, 0);

UPDATE creature_template SET minlevel=10, maxlevel=10, faction=2204, unit_flags=776, InhabitType=4, ScriptName="npc_sling_rocket_36505" WHERE entry=36505;
UPDATE creature_template SET speed_run=3.5 WHERE entry=36505;

DELETE FROM creature_template_addon WHERE entry=36505;
INSERT INTO creature_template_addon VALUES 
(36505, 0, 0, 50331648, 1, 0, "");

DELETE FROM waypoint_data WHERE id=3650501;
INSERT INTO waypoint_data VALUES 
(3650501, 0, 878.42, 2740.18, 130.8673, 0, 0, 1, 0, 0, 0),
(3650501, 1, 882.4566, 2726.064, 146.0856, 0, 0, 1, 0, 0, 0),
(3650501, 2, 890.9149, 2697.69, 164.5292, 0, 0, 1, 0, 0, 0),
(3650501, 3, 916.3698, 2591.611, 207.5022, 0, 0, 1, 0, 0, 0),
(3650501, 4, 928.4583, 2538.972, 196.3079, 0, 0, 1, 0, 0, 0),
(3650501, 5, 932.9393, 2506.701, 167.4186, 0, 0, 1, 0, 0, 0),
(3650501, 6, 941.3195, 2463.62, 111.2246, 0, 0, 1, 0, 0, 0),
(3650501, 7, 945.6337, 2440.615, 69.7246, 0, 0, 1, 0, 0, 0),
(3650501, 8, 945.2621, 2396.825, 4.585697, 0, 0, 1, 0, 0, 0);

delete from smart_scripts where entryorguid=23837;
delete from smart_scripts where entryorguid=-214368;
delete from smart_scripts where entryorguid=-203329;
delete from smart_scripts where entryorguid=-203328;


