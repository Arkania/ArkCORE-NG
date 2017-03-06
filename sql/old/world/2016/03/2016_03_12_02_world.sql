
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Lord Godfrey im Militärviertel in Gilneas." WHERE Id=14293;

update creature_template_addon set path_id=0 where entry=35905;
update creature_template set MovementType=0 where entry=35905;

DELETE FROM script_waypoint WHERE entry=35905;
INSERT INTO `script_waypoint` VALUES 
(35905, 0, -1791.55, 1381.92, 19.8183, 0, NULL),
(35905, 1, -1791.55, 1381.92, 19.8183, 0, NULL),
(35905, 2, -1772.75, 1361.92, 19.6939, 0, NULL),
(35905, 3, -1759.41, 1357.74, 19.9291, 0, NULL),
(35905, 4, -1713.19, 1347.35, 19.6855, 0, NULL),
(35905, 5, -1706.18, 1347.33, 19.9, 0, NULL),
(35905, 6, -1668.35, 1348.68, 15.1382, 0, NULL),
(35905, 7, -1664.11, 1356.47, 15.1351, 0, NULL),
(35905, 8, -1678.52, 1360.17, 15.1359, 0, NULL),
(35905, 9, -1702.23, 1353.7, 19.2279, 0, NULL),
(35905, 10, -1742.5, 1366.78, 19.9632, 0, NULL),
(35905, 11, -1762.66, 1390.97, 19.9748, 0, NULL),
(35905, 12, -1774.7, 1431.09, 19.7806, 0, NULL),
(35905, 13, -1774.7, 1431.09, 19.7806, 0, NULL);

update creature_template set ScriptName="" where entry=35753;

update creature_text set BroadcastTextID=36078 where entry=35905 and groupid=1;

delete from creature_text where entry=35753 and groupid=1;

UPDATE quest_template SET RequiredNpcOrGo1=35753 WHERE Id=14293;

DELETE FROM spell_area WHERE spell=49416 AND area=4757;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(49416, 4757, 14093, 14222, 0, 0, 2, 1, 75, 11);

DELETE FROM spell_phase WHERE spell_id=72872;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(72872, 8, 638, 683);

update creature set spawndist=0,  MovementType=0 where id=44470;

update npc_text set BroadcastTextID0=36072 where ID=14844;
update npc_text set BroadcastTextID0=36073 where ID=14845;

update gossip_menu_option set OptionBroadcastTextID=36067 where menu_id=10700 and id=0;

delete from creature where guid=250049 and id=35230;

delete from creature where guid=250050 and id=35231;

delete from creature where guid=240598 and id=35911;

update creature set position_x=-1740.59, position_y=1663.13, position_z=20.56363, orientation=4.886922 where guid=250945;

delete from creature where guid=240814 and id=35552;

update creature set position_x=-1735.88, position_y=1656.62, position_z=20.56363, orientation=2.129302 where guid=250285;

update creature set map=654 where guid=251108 and id=35551;

delete from creature where guid=10434 and id=35374;
INSERT INTO `creature` VALUES 
(10434, 35374, 654, 1, 8, 11686, 0, -1734.95, 1663.09, 20.5636, 0, 500, 0, 0, 1, 0, 0, 0, 0, 0);

update creature_text set emote=274, BroadcastTextID=36104 where entry=35552 and groupid=1;
update creature_text set emote=66, BroadcastTextID=36105 where entry=35552 and groupid=2;

update creature_text set emote=1, sound=19720, BroadcastTextID=36108 where entry=35911 and groupid=2;

delete from creature_text where entry=35911 and groupid=1;

delete from creature where guid=241300 and id=44427;
update creature set id=44427, position_x=-1735.25, position_y=1653.8, position_z=20.49, orientation=2.129 where guid=271066 and id=44428;

update creature_template set AIName="", ScriptName="" where entry in (44427, 44459);
update creature_template set AIName="", ScriptName="npc_king_genn_greymane_35911" where entry=35911;
update creature_template set AIName="", ScriptName="npc_sister_almyra_44468" where entry=44468;
update creature_template set AIName="", ScriptName="npc_rebel_cannon_35317" where entry=35317;
update creature_template set AIName="", ScriptName="npc_lord_darius_crowley_35230" where entry=35230;
update creature_template set AIName="", ScriptName="npc_crowley_horse_35231" where entry=35231;
update creature_template set AIName="", ScriptName="npc_northgate_rebel_36057" where entry=36057;
update creature_template set AIName="", ScriptName="npc_frenzied_stalker_35627" where entry=35627;
update creature_template set AIName="", ScriptName="npc_northgate_rebel_41015" where entry=41015;

delete from npc_spellclick_spells where npc_entry=44427;
insert into npc_spellclick_spells values
(44427, 56685, 1, 0);

update creature_template set spell1=67063, spell2=0, VehicleId=463 where entry=35231;

delete from spell_script_names where spell_id=67063;
insert into spell_script_names values
(67063, "spell_throw_torch_67063");

delete from spell_script_names where spell_id=56685;
insert into spell_script_names values
(56685, "spell_csa_dummy_effect_56685");

delete from waypoints where entry=35230;
delete from script_waypoint where entry=35230;
delete from waypoint_data where id=35230;
delete from waypoint_data where id in (352301, 352302);
delete from waypoints where entry=35231;
delete from script_waypoint where entry=35231;
delete from waypoint_data where id=35231;
delete from waypoint_data where id in (352311, 352312);
delete from npc_spellclick_spells where npc_entry in (35230, 35231);
delete from vehicle_template_accessory where entry=35231;


delete from waypoint_data where id in (352311, 352312);
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) VALUES 
-- (35231, 1, -1731.11, 1657.33, 20.4903, 0, 1),
(352311, 0, -1712.26, 1670.87, 20.6324, 0, 1),
(352311, 1, -1700.72, 1685.12, 20.3758, 0, 1),
(352311, 2, -1686.64, 1686.72, 20.7086, 0, 1),
(352311, 3, -1671.13, 1672.5, 20.4866, 0, 1),
(352311, 4, -1667.06, 1658.26, 20.4888, 0, 1),
(352311, 5, -1664.75, 1634.22, 20.4888, 0, 1),
(352311, 6, -1669.33, 1615.6, 20.4888, 0, 1),
(352311, 7, -1682.95, 1599.3, 20.4854, 0, 1),
(352311, 8, -1702.26, 1592.65, 20.4854, 0, 1),
(352311, 9, -1728.57, 1591.32, 20.4854, 0, 1),
(352311, 10, -1716.22, 1624.68, 20.4858, 0, 1),
(352311, 11, -1705.6, 1647.77, 20.4885, 0, 1),
(352311, 12, -1695.95, 1668.75, 20.6271, 0, 1),
(352311, 13, -1679.98, 1696.54, 20.489, 0, 1),
(352311, 14, -1656.29, 1710.24, 20.4994, 0, 1),
(352311, 15, -1618.84, 1711.39, 22.5229, 0, 1),
(352311, 16, -1589.21, 1710.98, 20.4851, 0, 1),
-- (35231, xx, -1571.23, 1710.034, 20.485, 0, 1),
(352312, 0, -1565.22, 1708.6, 20.4852, 0, 1),
(352312, 1, -1553.66, 1694.52, 20.4852, 0, 1),
(352312, 2, -1549.95, 1661.44, 20.4852, 0, 1),
(352312, 3, -1540.47, 1637.87, 21.2308, 0, 1),
(352312, 4, -1529.52, 1623.19, 20.4856, 0, 1),
(352312, 5, -1502.9, 1633.84, 20.4856, 0, 1),
(352312, 6, -1485.12, 1660.34, 20.4856, 0, 1),
(352312, 7, -1464.95, 1661.05, 20.4856, 0, 1),
(352312, 8, -1452.47, 1648.57, 20.4856, 0, 1),
(352312, 9, -1456.38, 1621.7, 20.4856, 0, 1),
(352312, 10, -1475.1, 1601.02, 20.4856, 0, 1),
(352312, 11, -1490.21, 1590.57, 20.4859, 0, 1),
(352312, 12, -1511.12, 1580.3, 23.5709, 0, 1),
(352312, 13, -1532.57, 1576.8, 27.4071, 0, 1),
(352312, 14, -1541.88, 1574.54, 29.2069, 0, 1);

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Tobias Dunstmantel bei der Kathedrale des Erwachenden Lichts in Gilneas." WHERE Id=14212;

UPDATE quest_template SET RequiredNpcOrGoCount1=30 WHERE Id=14212;

update creature set spawntimesecs=120 where id in (35229, 35618);

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Tobias Dunstmantel außerhalb der Kathedrale des Erwachenden Lichts in Gilneas zurück." WHERE Id=14218;

delete from creature where id in (44429);
delete from creature where guid in (240815);

delete from creature where map=638 and id in (35566, 36057, 41015);

update creature set phaseMask=1024 where id=41015;

update creature_template_addon set auras=67503 where entry=35230;

update npc_text set BroadcastTextID0=50710 where ID=17819;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lord Darius Crowley in der Kathedrale des Erwachenden Lichts in Gilneas zurück." WHERE Id=14222;

UPDATE quest_template SET NextQuestIdChain=14222, RewardSpellCast=81040 WHERE Id=14221;

UPDATE quest_template SET RewardSpellCast=0, Flags=2621440 WHERE Id=14222; -- RewardSpellCast should be 93477, but video not present error..

update creature set phaseMask=1032 where guid=250288 and id=35566;

DELETE FROM spell_phase WHERE spell_id=76642;
INSERT INTO spell_phase (spell_id, phasemask, terrainswapmap, worldmapareaswap) VALUES 
(76642, 1024, 638, 683);

delete from creature where map=638 and id=35627;
update creature set phasemask=1024, spawntimesecs=120 where id=35627;

update creature set phaseMask=1032 where guid in (250679, 250680) and id=36057;

delete from phase_area where areaId in (4714, 4755);
INSERT INTO `phase_area` VALUES (4714, 0, 14078, 14091, 11, 11, 0, 'Gilneas phase 1');
INSERT INTO `phase_area` VALUES (4714, 1, 14091, 14159, 74, 11, 0, 'Gilneas phase 2');
INSERT INTO `phase_area` VALUES (4755, 0, 14078, 14078, 75, 11, 0, 'Gilneas phase 1');
INSERT INTO `phase_area` VALUES (4755, 1, 14091, 14159, 64, 11, 0, 'Gilneas phase 2');

delete from phase_definitions where zoneId in (4714, 4755);
INSERT INTO `phase_definitions` VALUES (4714, 0, 1, 0, 638, 683, 1, 'Gilneas player startposition');
INSERT INTO `phase_definitions` VALUES (4714, 1, 2, 0, 638, 683, 1, 'Gilneas phase 2');
INSERT INTO `phase_definitions` VALUES (4755, 0, 1, 0, 638, 683, 1, 'Gilneas player startposition');
INSERT INTO `phase_definitions` VALUES (4755, 1, 2, 0, 638, 683, 1, 'Gilneas player startposition');

delete from creature where guid=251034 and id=36797;


-- in same secound..
-- Spell ID: 93477 (Play Movie) from quest 14222 reward
-- Spell ID: 94293 (Enable Worgen Altered Form)
-- Spell ID: 98274 (Force Worgen Altered Form)
-- Spell ID: 97709 (Altered Form)
-- Spell ID: 98274 (Force Worgen Altered Form)
-- Spell ID: 76642 (Hideous Bite Wound)
-- ServerToClient: SMSG_SET_PHASE_SHIFT (0x02A2) Length: 33 ConnIdx: 0 EP:  Time: 08/06/2014 22:11:24.000 Number: 150220
-- ServerToClient: SMSG_MOVE_TELEPORT (0x0B39) Length: 28 ConnIdx: 0 EP:  Time: 08/06/2014 22:11:24.000 Number: 150224
--  Position: X: -1818.4 Y: 2294.25 Z: 42.2135 O: 3.246661
-- Spell ID: 68630 (Curse of the Worgen)
-- Spell ID: 94053 (Fade to Black)  [0] Max Duration: 5000
-- Spell ID: 69123 (Curse of the Worgen)
--  Summoned GUID: Full: 0xF1308DEB00030663 Type: Creature Entry: 36331 (Krennan Aranas) Low: 198243
-- Spell ID: 68630 (Curse of the Worgen)
-- ServerToClient: SMSG_INIT_WORLD_STATES (0x1560) Length: 15 ConnIdx: 0 EP:  Time: 08/06/2014 22:11:24.000 Number: 150232
--  Map ID: 654 (Gilneas2)  Area Id: 4714 (Gilneas)  Zone Id: 4786




-- 35230	Lord Darius Crowley			npc_bloodfang_stalker_phase8		spawned via a script Number: 122601
-- 35317	Rebel Cannon				npc_rebel_cannon_phase8				vor der kathedrahle
-- 35911*	King Genn Greymane			npc_king_genn_greymane2_phase8
-- 36057	Northgate Rebel				npc_northgate_rebel2_phase8
-- 41015	Northgate Rebel				npc_northgate_rebel1_phase8
-- 44427*	Crowley's Horse				npc_crowley_horse_phase8
-- 44428	Crowley's Horse				npc_crowley_horse_1round_phase8
-- 44459*	Celestine of the Harvest	npc_celestine_of_the_harvest_phase8
-- 44468*	Sister Almyra				npc_sister_almyra_phase8
-- 50420	Gilneas - Cannon Camera		npc_cannon_camera_phase8
-- 50474	Gilneas City Guard			npc_gilneas_city_guard_phase8

















  