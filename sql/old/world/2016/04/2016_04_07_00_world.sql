
-- fix issue #117 
-- fix quest 27093
UPDATE locales_quest SET OfferRewardText_loc3="Lok'tar, $N. Sobald die Wirkung des Biers nachlässt, werden meine Orcs bereit sein!", QuestGiverTextWindow_loc3="Orcischer Seebär", QuestGiverTargetName_loc3="Orcischer Seebär" WHERE Id=27093;

-- fix quest 27082
UPDATE creature_template SET questItem2=60793 WHERE entry=1797;

UPDATE creature_template SET questItem1=60793 WHERE entry=1766;

-- fix quest 27093
UPDATE creature_template SET KillCredit1=44942, AIName="", ScriptName="npc_webbed_victim_44941" WHERE entry=44941;

UPDATE creature_template SET AIName="", ScriptName="npc_orc_sea_dog_44942" WHERE entry=44942;

delete from creature where id=44367 and guid in (35268, 35445);

SET @GUID=35079;
SET @PATHID=3507900;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@PATHID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, 825.8362, 1733.786, 20.72032, 4.716283, 3000, 0),
(@PATHID, 1, 825.8362, 1733.786, 20.72068, 4.716283, 0, 0),
(@PATHID, 2, 840.331, 1691.791, 22.34454, 5.09327, 0, 0),
(@PATHID, 3, 851.1736, 1623.977, 26.9407, 4.865506, 0, 0),
(@PATHID, 4, 858.0442, 1595.982, 31.51273, 4.955827, 0, 0),
(@PATHID, 5, 859.2785, 1516.975, 37.02961, 4.72021, 0, 0),
(@PATHID, 6, 873.3595, 1501.376, 37.26314, 6.11429, 0, 0),
(@PATHID, 7, 934.127, 1486.814, 39.0592, 6.051459, 0, 0),
(@PATHID, 8, 966.7885, 1464.315, 43.54084, 5.721591, 0, 0),
(@PATHID, 9, 1048.756, 1438.957, 44.29601, 5.992551, 0, 0),
(@PATHID, 10, 1063.853, 1445.349, 42.60586, 0.400514, 0, 0),
(@PATHID, 11, 1088.398, 1454.294, 37.98888, 3.691335, 0, 0),
(@PATHID, 12, 1109.851, 1463.938, 34.44845, 3.557819, 0, 0),
(@PATHID, 13, 1159.101, 1485.275, 35.12709, 0.459419, 0, 0),
(@PATHID, 14, 1181.833, 1531.138, 34.72274, 1.225182, 0, 0),
(@PATHID, 15, 1182.29, 1595.618, 24.83682, 4.154723, 0, 0),
(@PATHID, 16, 1184.991, 1642.799, 23.69606, 1.547196, 3000, 0),
(@PATHID, 17, 1182.29, 1595.618, 24.83682, 4.154723, 0, 0),
(@PATHID, 18, 1181.833, 1531.138, 34.72274, 1.225182, 0, 0),
(@PATHID, 19, 1159.101, 1485.275, 35.12709, 0.459419, 0, 0),
(@PATHID, 20, 1109.851, 1463.938, 34.44845, 3.557819, 0, 0),
(@PATHID, 21, 1088.398, 1454.294, 37.98888, 3.691335, 0, 0),
(@PATHID, 22, 1063.853, 1445.349, 42.60586, 0.400514, 0, 0),
(@PATHID, 23, 1048.756, 1438.957, 44.29601, 5.992551, 0, 0),
(@PATHID, 24, 966.7885, 1464.315, 43.54084, 5.721591, 0, 0),
(@PATHID, 25, 934.127, 1486.814, 39.0592, 6.051459, 0, 0),
(@PATHID, 26, 873.3595, 1501.376, 37.26314, 6.11429, 0, 0),
(@PATHID, 27, 859.2785, 1516.975, 37.02961, 4.72021, 0, 0),
(@PATHID, 28, 858.0442, 1595.982, 31.51273, 4.955827, 0, 0),
(@PATHID, 29, 851.1736, 1623.977, 26.9407, 4.865506, 0, 0),
(@PATHID, 30, 840.331, 1691.791, 22.34454, 5.09327, 0, 0),
(@PATHID, 31, 825.8362, 1733.786, 20.72068, 4.716283, 0, 0);

update creature set spawndist=0, MovementType=0 where guid=50099 and id=44906;

delete from creature where id=1780 and modelid=34167;

delete from creature where id=2529;

-- fix quest 27088
UPDATE locales_quest SET OfferRewardText_loc3="<Apotheker Wurmschmutz lacht wie irre.>$B$BGab es daran jemals Zweifel? Ein Ettin kann der Wissenschaft nicht das Wasser reichen!", QuestGiverTextWindow_loc3="Waldettin", QuestGiverTargetName_loc3="Waldettin" WHERE Id=27088;

update gameobject set position_x=932.62, position_y=1647.67, position_z=31.54, orientation=0.34 where guid=80860 and id=1730;

UPDATE quest_template SET RequiredSourceItemId1=60808, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount4=0 WHERE Id=27088;

UPDATE creature_template SET KillCredit1=0, AIName="", ScriptName="npc_forest_ettin_44367" WHERE entry=44367;

DELETE FROM creature_addon WHERE guid=35769;
DELETE FROM creature_addon WHERE guid=35690;
DELETE FROM creature_addon WHERE guid=35656;
DELETE FROM creature_addon WHERE guid=35638;
DELETE FROM creature_addon WHERE guid=35616;
DELETE FROM creature_addon WHERE guid=35579;
DELETE FROM creature_addon WHERE guid=35504;
DELETE FROM creature_addon WHERE guid=35445;
DELETE FROM creature_addon WHERE guid=35408;
DELETE FROM creature_addon WHERE guid=35285;
DELETE FROM creature_addon WHERE guid=35268;
DELETE FROM creature_addon WHERE guid=35240;
DELETE FROM creature_addon WHERE guid=35131;
DELETE FROM creature_addon WHERE guid=35061;
DELETE FROM creature_addon WHERE guid=34974;
DELETE FROM creature_addon WHERE guid=34970;
DELETE FROM creature_addon WHERE guid=34819;
DELETE FROM creature_addon WHERE guid=34775;
DELETE FROM creature_addon WHERE guid=34763;
DELETE FROM creature_addon WHERE guid=34748;
DELETE FROM creature_addon WHERE guid=34654;
DELETE FROM creature_addon WHERE guid=34541;
DELETE FROM creature_addon WHERE guid=50389;
DELETE FROM creature_addon WHERE guid=36426;

delete from spell_script_names where spell_id=83904;
insert into spell_script_names values
(83904, "spell_reverse_cast_ride_vehicle_83904");

update creature set spawntimesecs=120 where id=44367;



