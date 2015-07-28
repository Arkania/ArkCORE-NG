
-- aradne G=37194 E=50372
update creature set MovementType=2 where guid=37194 and id=50372;
update creature_template set MovementType=0 where entry=50372;

insert ignore creature_addon (guid) value (37194);
update creature_addon set path_id=3719400 where guid=37194;

delete from waypoints where entry=50372;

delete from waypoint_data where id=3719400;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay) values
(3719400, 0, 1683.915, 1686.05, 140.0524, 0),
(3719400, 1, 1686.316, 1687.927, 140.6193, 0),
(3719400, 2, 1691.38, 1681.877, 141.2154, 0),
(3719400, 3, 1700.74, 1681.656, 141.103, 0),
(3719400, 4, 1708.035, 1690.964, 139.9632, 0),
(3719400, 5, 1707.568, 1700.717, 136.3973, 12000), --
(3719400, 6, 1697.666, 1689.334, 137.5208 , 0),
(3719400, 7, 1696.539, 1681.868, 137.2926, 12000),
(3719400, 8, 1694.957, 1677.693, 138.2509, 0),
(3719400, 9, 1691.339, 1673.193, 139.5167, 0),
(3719400, 10, 1683, 1671.122, 142.7538, 0),
(3719400, 11, 1674.201, 1673.691, 144.2937, 0),
(3719400, 12, 1674.004, 1684.535, 145.5765, 12000), --
(3719400, 13, 1677.028, 1695.885, 145.1395, 0),
(3719400, 14, 1682.517, 1695.972, 144.0367, 0),
(3719400, 15, 1686.727, 1693.24, 142.2619, 0),
(3719400, 16, 1687.33, 1688.234, 140.8931, 0),
(3719400, 17, 1683.915, 1686.05, 140.0524, 12000), --
(3719400, 18, 1686.316, 1687.927, 140.6193, 0),
(3719400, 19, 1691.38, 1681.877, 141.2154, 0),
(3719400, 20, 1700.74, 1681.656, 141.103, 0),
(3719400, 21, 1708.035, 1690.964, 139.9632, 0),
(3719400, 22, 1707.568, 1700.717, 136.3973, 12000), --
(3719400, 23, 1697.666, 1689.334, 137.5208, 0),
(3719400, 24, 1704.867, 1697.775, 136.959, 0),
(3719400, 25, 1699.867, 1692.025, 137.459, 12000); --

-- 50374  spawned by script..
delete from creature where guid=37391 and id=50374;
delete from creature_addon where guid=37391;


delete from waypoint_data where id=5037401;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(5037401, 0, 1696.866577, 1666.722290, 132.884918, 0, 1),
(5037401, 1, 1704.655029, 1647.453857, 126.386261, 0, 1),
(5037401, 2, 1719.316895, 1633.910156, 121.058296, 0, 1),
(5037401, 3, 1734.232300, 1626.148682, 117.692345, 0, 1),
(5037401, 4, 1764.471313, 1600.582520, 109.555061, 0, 1),
(5037401, 5, 1839.401367, 1585.156616, 93.975357, 0, 1); 

delete from waypoint_data where id=5037402;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(5037402, 0, 1696.866577, 1666.722290, 132.884918, 0, 1),
(5037402, 1, 1704.655029, 1647.453857, 126.386261, 0, 1),
(5037402, 2, 1719.316895, 1633.910156, 121.058296, 0, 1),
(5037402, 3, 1734.232300, 1626.148682, 117.692345, 0, 1),
(5037402, 4, 1764.471313, 1600.582520, 109.555061, 0, 1),
(5037402, 5, 1839.401367, 1585.156616, 93.975357, 0, 1); 


delete from creature_text where entry=50374;
insert into creature_text values 
(50374, 0, 0, "What...what's happening to me? Why have you done this to me?", 12, 0, 100, 0, 0, 0, "Risen Dead", 50194),
(50374, 1, 0, "I should be dead and to death I will return!", 12, 0, 100, 0, 0, 0, "Risen Dead", 50195),
(50374, 2, 0, "I... I don't remember... Why have you done this?", 12, 0, 100, 6, 0, 0, "Risen Dead", 50198),
(50374, 3, 0, "What magic is this that turn back the hand of death?", 12, 0, 100, 6, 0, 0, "Risen Dead", 50197),
(50374, 3, 1, "I never asked for this! Leave me alone!", 12, 0, 100, 0, 0, 0, "Risen Dead", 50201),
(50374, 4, 0, "This is Lady Sylvanas's doing?", 12, 0, 100, 6, 0, 0, "Risen Dead", 50196),
(50374, 4, 1, "What use has the Dark Lady for me?", 12, 0, 100, 6, 0, 0, "Risen Dead", 50199),
(50374, 5, 0, "If the Banshee Queen has offered me this chance, I will gladly serve.", 12, 0, 100, 0, 0, 0, "Risen Dead", 50200),
(50374, 7, 0, "%s enrages and transforms into a Mindless Zombie and runs away.", 16, 0, 100, 0, 0, 0, "Risen Dead", 0),
(50374, 8, 0, "%s commits suicide.", 16, 0, 100, 0, 0, 0, "Risen Dead", 0),
(50374, 9, 0, "%s walks off towards the barracks.", 16, 0, 100, 0, 0, 0, "Risen Dead", 0);

-- mordo G:50373 E:1568
update creature_template set AIName="", Scriptname="npc_undertaker_mordo" where entry=1568;

update creature_text set BroadcastTextID=50126 where entry=1568 and groupid=0 and id=0;
update creature_text set BroadcastTextID=50127 where entry=1568 and groupid=1 and id=0;
update creature_text set BroadcastTextID=50128 where entry=50414 and groupid=0 and id=0;

delete from waypoint_data where id=5041401;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(5041401, 0, 1692.516, 1673.46, 134.938, 0, 0),
(5041401, 1, 1694.266, 1669.96, 134.188, 0, 0),
(5041401, 2, 1695.516, 1667.21, 133.438, 0, 0),
(5041401, 3, 1696.516, 1665.46, 132.938, 0, 0),
(5041401, 4, 1697.516, 1662.96, 132.188, 0, 0),
(5041401, 5, 1698.266, 1661.21, 131.438, 0, 0),
(5041401, 6, 1699.266, 1659.46, 130.688, 0, 0),
(5041401, 7, 1700.516, 1656.71, 129.938, 0, 0),
(5041401, 8, 1701.266, 1654.96, 129.188, 0, 0),
(5041401, 9, 1702.266, 1652.96, 128.688, 0, 0),
(5041401, 10, 1703.016, 1651.21, 127.938, 0, 0),
(5041401, 11, 1719.316, 1633.91, 121.058, 0, 0),
(5041401, 12, 1734.232, 1626.14, 117.692, 0, 0),
(5041401, 13, 1764.471, 1600.58, 109.555, 0, 0),
(5041401, 14, 1839.401, 1585.15,  93.975, 0, 0); 

-- darnell 49141 spawned by script 
update creature_template set AIName="", Scriptname="npc_darnell_49141" where entry=49141;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Totengräber Mordo bei den Gräbern von Todesend in Tirisfal zurück." WHERE Id=28608;

delete from creature_queststarter where quest=24960 and id in (38895, 49230, 49231);

update creature_template set AIName="", ScriptName="npc_marshal_redpath_49230" where entry=49230;
update creature_template set AIName="", ScriptName="npc_valdred_moray_49231" where entry=49231;
update creature_template set AIName="", ScriptName="npc_lilian_voss_38895" where entry=38895;

update gossip_menu_option set OptionBroadcastTextID=49339 where menu_id=17564 and id=0;
update gossip_menu_option set OptionBroadcastTextID=49340 where menu_id=17565 and id=0;
update gossip_menu_option set OptionBroadcastTextID=49346 where menu_id=17566 and id=0;
update gossip_menu_option set OptionBroadcastTextID=49347 where menu_id=17567 and id=0;
update gossip_menu_option set OptionBroadcastTextID=49353 where menu_id=12487 and id=0;
update gossip_menu_option set OptionBroadcastTextID=49352 where menu_id=12488 and id=0;

update npc_text set BroadcastTextID0=49334 where ID=17564;
update npc_text set BroadcastTextID0=49335 where ID=17565;
update npc_text set BroadcastTextID0=49343 where ID=17566;
update npc_text set BroadcastTextID0=49344 where ID=17567;
update npc_text set BroadcastTextID0=49348 where ID=17569;
update npc_text set BroadcastTextID0=49349 where ID=17570;

update creature_text set BroadcastTextID=50326 where entry=49230 and groupid=0 and id=0;
update creature_text set BroadcastTextID=49345, groupid=1, id=0 where entry=49230 and groupid=0 and id=1;
delete from creature_text where entry=49231 and groupid=0 and id=1;
update creature_text set BroadcastTextID=49408 where entry=49231 and groupid=0 and id=0;
update creature_text set BroadcastTextID=49351 where entry=49231 and groupid=1 and id=0;
update creature_text set BroadcastTextID=49337 where entry=38895 and groupid=0 and id=0;
update creature_text set BroadcastTextID=38982, groupid=1, id=0 where entry=38895 and groupid=0 and id=1;

update creature set position_x=1753.89, position_y=1640.63, position_z=117.495, spawntimesecs=120 where guid=12904;

delete from waypoint_data where id=4923001;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(4923001, 0, 1757.029663, 1633.649658, 115.811920, 0, 1),
(4923001, 1, 1757.372559, 1618.554565, 113.989738, 0, 1),
(4923001, 2, 1757.884277, 1606.427612, 111.253128, 0, 1),
(4923001, 3, 1758.078613, 1595.230103, 111.725334, 0, 1),
(4923001, 4, 1757.452515, 1583.321655, 111.495621, 0, 1),
(4923001, 5, 1752.008179, 1557.963501, 114.146751, 0, 1),
(4923001, 6, 1754.536621, 1548.741211, 114.063171, 0, 1),
(4923001, 7, 1768.712036, 1530.326660, 113.186867, 0, 1);

update creature set spawntimesecs=120 where guid=26658;

delete from waypoint_data where id=3889501;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(3889501, 0, 1752.812134, 1654.563965, 119.830139, 0, 1),
(3889501, 1, 1757.029663, 1633.649658, 115.811920, 0, 1),
(3889501, 2, 1757.372559, 1618.554565, 113.989738, 0, 1),
(3889501, 3, 1757.884277, 1606.427612, 111.253128, 0, 1),
(3889501, 4, 1758.078613, 1595.230103, 111.725334, 0, 1),
(3889501, 5, 1757.452515, 1583.321655, 111.495621, 0, 1),
(3889501, 6, 1752.008179, 1557.963501, 114.146751, 0, 1),
(3889501, 7, 1754.536621, 1548.741211, 114.063171, 0, 1),
(3889501, 8, 1768.712036, 1530.326660, 113.186867, 0, 1);

update creature set spawntimesecs=120 where guid=26665;

delete from waypoint_data where id=4923101;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(4923101, 0, 1736.803955, 1702.434814, 128.085632, 0, 1),
(4923101, 1, 1727.346436, 1697.857544, 128.217163, 0, 1),
(4923101, 2, 1720.289185, 1693.729248, 131.422379, 0, 1),
(4923101, 3, 1713.864746, 1689.297119, 133.295822, 0, 1),
(4923101, 4, 1705.453857, 1681.018433, 133.751022, 0, 1),
(4923101, 5, 1700.136719, 1675.276123, 134.248505, 0, 1),
(4923101, 6, 1687.036133, 1664.714111, 133.506210, 0, 1),
(4923101, 7, 1676.103394, 1663.843506, 137.068909, 0, 1),
(4923101, 8, 1663.309814, 1663.338867, 141.850845, 0, 1);

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Verwalter Caice bei den Gräbern von Todesend in Tirisfal zurück." WHERE Id=24960;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Todeswache Saltain in Todesend in Tirisfal zurück.", QuestGiverTextWindow_loc3="Leichnam der Scharlachroten", QuestGiverTargetName_loc3="Leichnam der Scharlachroten" WHERE Id=26800;

update creature_template set npcflag=16777218, AIName="", ScriptName="npc_scarlet_corpse_49340" where entry=49340;

delete from creature_template_addon where entry=49340;

INSERT IGNORE INTO creature_addon (guid) SELECT guid FROM creature WHERE id=49340;

update creature_addon set auras="29266 92230" where guid in (select guid from creature where id=49340);

update creature_template set AIName="", ScriptName="npc_darnell_49337" where entry=49337;

update creature_template set AIName="", ScriptName="npc_deathguard_saltain" where entry=1740;

update creature set spawntimesecs=120 where id=49340;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Schattenpriester Sarvis in Todesend in Tirisfal zurück." WHERE Id=26801;

update quest_template set PrevQuestId=24971 where Id=24972;

UPDATE locales_quest SET OfferRewardText_loc3="Ich werde hier sein, um Euch zu unterrichten, während Ihr Erfahrungen sammelt... Sucht mich auf, wann immer Euch danach ist. Ich verlange ein kleines Entgeld, aber Ihr werdet es für das Gelernte nicht bereuen.$B$BGeht nun und testet Eure Fähigkeiten. Je mehr Erfahrung Ihr sammelt, um so mehr Wissen wird sich Euch erschließen. Ich kann nicht alles mit Euch hier besprechen. Ihr solltet Euch jedoch darüber im Klaren sein, dass Sylvanas für $C mit Eurer Raffinesse auch zukünftig Bedarf hat.$B$BIhr werdet das Rückgrat unserer Rettung darstellen. Vergesst das nicht.", RequestItemsText_loc3="Ah, da seid Ihr ja. Gut. Ich habe mitbekommen, dass ein paar andere dem 'Tod' entkommen und in die Stadt geflüchtet sind. Vielleicht wird sich auch dieser Widerstand in der Zukunft auszahlen.$B$BIhr solltet Sylvanas für Eure Freiheit danken... Freiheit von Eurem Körper und Geist. Auch wenn Ihr weiterhin von der Seuche und ihren Auswirkungen befallen seid, so könnt Ihr Euch nun doch frei bewegen." WHERE Id=24962;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ihr scheint eine Art Begabung zu haben, SN. Das ist gut. Ich kann Euch ja auch nicht alles selbst beibringen.$B$BGeht und übt, was wir heute durchgenommen haben. Kehrt zu mir zurück, wenn Ihr stärker seid; wir werden dann weitere Tricks und Fähigkeiten durchnehmen.", CompletedText_loc3="Kehrt zu Xavier dem Jäger in Todesend in Tirisfal zurück.", QuestGiverTextWindow_loc3="Trainings Attrappe", QuestGiverTargetName_loc3="Trainings Attrappe" WHERE Id=24964;

UPDATE locales_quest SET CompletedText_loc3="Sprecht mit Novizin Elreth in Todesend in Tirisfal." WHERE Id=28651;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Novize Elreth in Todesend in Tirisfal zurück." WHERE Id=24961;

update npc_text set BroadcastTextID0=38980 where ID=15486;
update gossip_menu_option set OptionBroadcastTextID=38981 where menu_id=15486 and id=0;
update creature_text set BroadcastTextID=38982 where entry=38910 and groupid=0 and id=0;
update creature_template set AIName="", ScriptName="npc_lilian_voss_38910" where entry=38910;

delete from waypoint_data where id=3891001;
insert into waypoint_data (id, point, position_x, position_y, position_z, delay, move_flag) values
(3891001, 0, 1860.040283, 1557.487305, 94.785637, 0, 1),
(3891001, 1, 1860.057739, 1558.537231, 94.637047, 0, 1),
(3891001, 2, 1859.764526, 1560.499146, 94.296356, 0, 1),
(3891001, 3, 1861.173340, 1567.141357, 94.312439, 0, 1),
(3891001, 4, 1860.629639, 1578.342163, 94.193100, 0, 1),
(3891001, 5, 1860.558472, 1579.880493, 93.630783, 0, 1),
(3891001, 6, 1874.814941, 1587.513794, 90.745476, 0, 1),
(3891001, 7, 1921.579590, 1584.919678, 83.634308, 0, 1);



