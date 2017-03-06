SET @GUID=109168;
SET @PATHID=10916800;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@PATHID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@PATHID, 0, -2384.866, -944.3442, -9.322654, 4.325328, 2000),
(@PATHID, 1, -2367.602, -886.9946, -9.424393, 1.274053, 0),
(@PATHID, 2, -2364.115, -836.5189, -9.218373, 1.501819, 0),
(@PATHID, 3, -2345.402, -766.9584, -9.424819, 1.360447, 0),
(@PATHID, 4, -2340.066, -684.9167, -9.290969, 1.466476, 0),
(@PATHID, 5, -2330.063, -654.7618, -9.420129, 1.250491, 0),
(@PATHID, 6, -2290.652, -581.6403, -9.29825, 1.077703, 0),
(@PATHID, 7, -2247.932, -553.0558, -9.578753, 0.614318, 2000),
(@PATHID, 8, -2290.652, -581.6403, -9.29825, 1.077703, 0),
(@PATHID, 9, -2330.063, -654.7618, -9.420129, 1.250491, 0),
(@PATHID, 10, -2340.066, -684.9167, -9.290969, 1.466476, 0),
(@PATHID, 11, -2345.402, -766.9584, -9.424819, 1.360447, 0),
(@PATHID, 12, -2364.115, -836.5189, -9.218373, 1.501819, 0),
(@PATHID, 13, -2367.602, -886.9946, -9.424393, 1.274053, 0);

delete from quest_poi where questId=24459;
delete from quest_poi_points where questId=24459;

UPDATE quest_template SET PrevQuestId=751 WHERE Id=26179;
UPDATE quest_template SET PrevQuestId=751 WHERE Id=764;
UPDATE quest_template SET PrevQuestId=751 WHERE Id=765;
UPDATE quest_template SET PrevQuestId=751 WHERE Id=26180;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Morin Wolkenpirscher in Mulgore zurück.", QuestGiverTextWindow_loc3="Tagelöhner der Venture Co.", QuestGiverTargetName_loc3="Tagelöhner der Venture Co." WHERE Id=26179;

delete from creature_queststarter where id=2988 and quest in (764,765);

delete from creature where id=2976 and guid in (75660, 75686, 75680, 75684);
delete from creature where id=2977 and guid in (75698, 75700);
delete from creature where id=2959 and guid in (75096, 75162, 75081, 75119, 75095, 75166, 75160, 75130, 75131);
delete from creature where id=3035 and guid in (76066, 76048, 76011, 76010, 76005, 76007, 75996, 76053, 76089, 76083, 88407);

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Maur Regenrufer im Dorf der Bluthufe in Mulgore zurück." WHERE Id=26188;

UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=3035;
UPDATE creature_template SET mindmg=10, maxdmg=14.0000, attackpower=38, baseattacktime=2000, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=2959;
UPDATE creature_template SET mindmg=9, maxdmg=12, attackpower=36, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=2969;
UPDATE creature_template SET mindmg=9, maxdmg=12, attackpower=36, rangeattacktime=2000, minrangedmg=6, maxrangedmg=8 WHERE entry=2976;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=2977;
UPDATE creature_template SET mindmg=7, maxdmg=9, attackpower=34, rangeattacktime=2000, minrangedmg=4, maxrangedmg=6 WHERE entry=2956;
UPDATE creature_template SET mindmg=7, maxdmg=9, attackpower=34, rangeattacktime=2000, minrangedmg=4, maxrangedmg=6 WHERE entry=2970;
UPDATE creature_template SET mindmg=17, maxdmg=20, attackpower=46, rangeattacktime=2000, minrangedmg=11, maxrangedmg=17 WHERE entry=2974;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10, rangedattackpower=100 WHERE entry=2989;
UPDATE creature_template SET mindmg=7, maxdmg=9, attackpower=34, rangeattacktime=2000, minrangedmg=4, maxrangedmg=6 WHERE entry=2958;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10, rangedattackpower=10 WHERE entry=36869;
UPDATE creature_template SET mindmg=8, maxdmg=11, attackpower=30, rangeattacktime=2000, minrangedmg=5, maxrangedmg=8 WHERE entry=36845;
UPDATE creature_template SET mindmg=8, maxdmg=12, attackpower=16, rangeattacktime=2000, minrangedmg=8, maxrangedmg=11, rangedattackpower=11 WHERE entry=2990;
UPDATE creature_template SET mindmg=11, maxdmg=15, attackpower=40, rangeattacktime=2000, minrangedmg=8, maxrangedmg=11 WHERE entry=2957;
UPDATE creature_template SET mindmg=10, maxdmg=13, attackpower=32, rangeattacktime=2000, minrangedmg=6, maxrangedmg=9 WHERE entry=2963;
UPDATE creature_template SET mindmg=8, maxdmg=9, attackpower=38, rangeattacktime=2000, minrangedmg=8, maxrangedmg=9, rangedattackpower=38 WHERE entry=2962;
UPDATE creature_template SET mindmg=8, maxdmg=13, attackpower=17, rangeattacktime=2000, minrangedmg=9, maxrangedmg=12, rangedattackpower=12 WHERE entry=2964;
UPDATE creature_template SET mindmg=12, maxdmg=16, attackpower=38, rangeattacktime=2000, minrangedmg=8, maxrangedmg=12 WHERE entry=2965;
UPDATE creature_template SET mindmg=11, maxdmg=15, attackpower=40, rangeattacktime=2000, minrangedmg=8, maxrangedmg=11 WHERE entry=3566;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, rangeattacktime=2000, minrangedmg=9, maxrangedmg=13 WHERE entry=2960;
UPDATE creature_template SET mindmg=11, maxdmg=15, attackpower=40, rangeattacktime=2000, minrangedmg=8, maxrangedmg=11 WHERE entry=2971;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=2979;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, rangeattacktime=2000, minrangedmg=7, maxrangedmg=10 WHERE entry=2978;
UPDATE creature_template SET mindmg=3, maxdmg=4, attackpower=28, rangeattacktime=2000, minrangedmg=1, maxrangedmg=2 WHERE entry=4166;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, minrangedmg=9, maxrangedmg=13 WHERE entry=3232;
UPDATE creature_template SET mindmg=10, maxdmg=14, attackpower=38, minrangedmg=7, maxrangedmg=10 WHERE entry=5787;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, rangeattacktime=2000, minrangedmg=9, maxrangedmg=13, rangedattackpower=100 WHERE entry=2968;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, minrangedmg=9, maxrangedmg=13 WHERE entry=37178;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, minrangedmg=9, maxrangedmg=13 WHERE entry=36931;
UPDATE creature_template SET mindmg=13, maxdmg=17, attackpower=42, minrangedmg=9, maxrangedmg=13 WHERE entry=37175;
UPDATE creature_template SET mindmg=2, maxdmg=2, attackpower=24, rangeattacktime=2000, minrangedmg=1, maxrangedmg=1 WHERE entry=37062;










