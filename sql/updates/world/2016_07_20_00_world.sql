

DELETE FROM creature_template_addon WHERE entry=38507;
INSERT INTO creature_template_addon VALUES 
(38507, 0, 0, 0, 1, 0, "");

UPDATE creature_template SET MovementType=0 WHERE entry=38507;

delete from waypoint_data where id in (3850701, 3850702, 3850703, 3850704, 3850705, 3850706);
INSERT INTO `waypoint_data` VALUES 
(3850701, 0, -1623.235, 1617.035, 19.97187, 4.575241, 0, 1, 0, 0, 0), 
(3850701, 1, -1624.289, 1605.623, 20.74269, 5.337074, 0, 1, 0, 0, 0), 

(3850702, 0, -1589.44, 1607.08, 21.5989, 0, 0, 1, 0, 100, 0), -- jump landing
(3850702, 1, -1588.55, 1606.71, 21.5989, 0, 0, 1, 0, 100, 0), -- wait before gate

(3850703, 0, -1586.86, 1612.12, 21.5938, 0, 0, 1, 0, 100, 0), 
(3850703, 1, -1583.96, 1617.84, 20.6476, 0, 0, 1, 0, 100, 0), 
(3850703, 2, -1570.64, 1618.98, 20.6031, 0, 0, 1, 0, 100, 0), 
(3850703, 3, -1553.42, 1620.73, 20.7936, 0, 0, 1, 0, 100, 0), -- wait on wall, jump

(3850704, 0, -1548.65, 1618.41, 23.1788, 0, 0, 1, 0, 100, 0), 
(3850704, 1, -1546.69, 1616.66, 20.5702, 0, 0, 1, 0, 100, 0), 
(3850704, 2, -1514.13, 1599.58, 20.4857, 0, 0, 1, 0, 100, 0), 
(3850704, 3, -1500.37, 1582.93, 20.4857, 0, 0, 1, 0, 100, 0), 
(3850704, 4, -1496.07, 1573.47, 20.4857, 0, 0, 1, 0, 100, 0), 
(3850704, 5, -1491.17, 1575.8, 20.4857, 0, 0, 1, 0, 100, 0), -- wait on wall 2, listen to forsaken

(3850705, 0, -1491.75, 1577.63, 20.4869, 0, 0, 1, 0, 100, 0), 
(3850705, 1, -1508.6, 1585.36, 21.1645, 0, 0, 1, 0, 100, 0), 
(3850705, 2, -1513, 1586.07, 22.9593, 0, 0, 1, 0, 100, 0), 
(3850705, 3, -1518.9, 1586.12, 25.3814, 0, 0, 1, 0, 100, 0), 
(3850705, 4, -1528.26, 1585.74, 26.5368, 0, 0, 1, 0, 100, 0), 
(3850705, 5, -1535.76, 1582.02, 26.9762, 0, 0, 1, 0, 100, 0), 
(3850705, 6, -1535.76, 1582.02, 26.9762, 0, 0, 1, 0, 100, 0), 
(3850705, 7, -1537.27, 1580.22, 27.704, 0, 0, 1, 0, 100, 0), 
(3850705, 8, -1537.27, 1580.22, 27.704, 0, 0, 1, 0, 100, 0), 
(3850705, 9, -1539.09, 1578.09, 28.5757, 0, 0, 1, 0, 100, 0), 
(3850705, 10, -1541.38, 1575.43, 29.2073, 0, 0, 1, 0, 100, 0), 
(3850705, 11, -1549.64, 1567.13, 29.2208, 0, 0, 1, 0, 100, 0), 
(3850705, 12, -1549.64, 1567.13, 29.2208, 0, 0, 1, 0, 100, 0), 
(3850705, 13, -1555.67, 1570.57, 29.191, 0, 0, 1, 0, 100, 0), 
(3850705, 14, -1555.67, 1570.57, 29.191, 0, 0, 1, 0, 100, 0), 
(3850705, 15, -1567.43, 1559.65, 29.1903, 0, 0, 1, 0, 100, 0), 
(3850705, 16, -1567.43, 1559.65, 29.1903, 0, 0, 1, 0, 100, 0), 
(3850705, 17, -1565.01, 1552.39, 29.2225, 0, 0, 1, 0, 100, 0), 
(3850705, 18, -1565.01, 1552.39, 29.2225, 0, 0, 1, 0, 100, 0), 
(3850705, 19, -1571.41, 1545.11, 29.2021, 0, 0, 1, 0, 100, 0), 
(3850705, 20, -1583.74, 1534.37, 29.2224, 0, 0, 1, 0, 100, 0), 
(3850705, 21, -1590.25, 1528.49, 29.2297, 0, 0, 1, 0, 100, 0), 
(3850705, 22, -1598.51, 1526.85, 29.2366, 0, 0, 1, 0, 100, 0), 
(3850705, 23, -1612.35, 1533.04, 29.23, 0, 0, 1, 0, 100, 0), -- jump in water, say hide

(3850706, 0, -1614.5, 1533.9, 31.5553, 0, 0, 1, 0, 100, 0), 
(3850706, 1, -1616.72, 1533.24, 27.2708, 0, 0, 1, 0, 100, 0), 
(3850706, 2, -1616.72, 1533.24, 27.2708, 0, 0, 1, 0, 100, 0); -- listen to sylvanas

DELETE FROM creature_text where entry in (38507, 38530, 38533, 38537, 38611, 38617);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES 
(38507, 0, 0, "Let us go at once.  We will track Sylvanas down.  For Gilneas!", 12, 0, 100, 15, 0, 0, "tobias", 38399), 
(38507, 1, 0, "Let\'s do our best not to be seen!", 12, 0, 100, 0, 0, 0, "tobias", 38401), 
(38507, 2, 0, "Did you hear that? Sylvanas is headed to the cathedral. Let\'s hurry!", 12, 0, 100, 0, 0, 0, "tobias", 38402), 
(38507, 3, 0, "Quick, hide in the water!", 12, 0, 100, 0, 0, 0, "tobias", 38403), 
(38530, 0, 0, "You can assure Garrosh that this is a minor setback.  Our victory in Gilneas will be absolute.", 12, 0, 100, 1, 0, 20492, "Sylvanas", 38422),
(38530, 1, 0, "You'd do well to watch your tone, General.  Neither you nor Garrosh have anything to worry about.  We've ceased all production of the Plague, as he ordered.  We'd never deploy it without his permission.", 12, 0, 100, 0, 0, 20493, "Sylvanas", 38423),
(38530, 2, 0, "Go with honor, General.", 12, 0, 100, 0, 0, 20494, "Sylvanas", 38424),
(38530, 3, 0, "What kind of question is that?  Of course we're deploying the Plague as planned!  Let the Gilneans enjoy their small victory.  Not even their bones will remain by tomorrow.", 12, 0, 100, 0, 0, 20495, "Sylvanas", 38425),
(38533, 0, 0, "It appears you\'re losing control of Gilneas, Sylvanas.  Garrosh fears he\'s going to have to carry out this invasion himself.", 12, 0, 100, 1, 0, 22620, "warhowl", 38426), 
(38533, 1, 0, "You sound very confident, your Majesty. I sincerely hope you do not plan to use the plague. Garrosh has expllicitely forbidden it.", 12, 0, 100, 0, 0, 22621, "warhowl", 38427), 
(38533, 2, 0, "I will deliver my report to our leader, then. By your leave, my lady.", 12, 0, 100, 0, 0, 22622, "warhowl", 38428), 
(38537, 0, 0, "My Lady!  Should I order my men to stop the deployment of the Plague?  Or are we to continue as planned?", 12, 0, 100, 66, 0, 20917, "crenshaw", 38440), 
(38537, 1, 0, "As you wish!", 12, 0, 100, 0, 0, 20918, "crenshaw", 38441), 
(38611, 0, 0, "Follow Tobias Mistmantle into the Cathedral District.", 41, 0, 100, 0, 0, 0, "Lorna", 38400), 
(38617, 0, 0, "Make sure everything is ready.  The orcs\' emissary is ready to meet Sylvanas inside the cathedral.", 14, 0, 100, 1, 0, 0, "Forsaken General", 38514);

delete from creature where id=38781 and guid in (26553, 26560, 26556, 26564, 26565, 26559, 26558, 26561, 26563, 26562);

update creature set phaseMask=2097152 where id in (38616, 38617, 38618);

DELETE FROM creature_addon WHERE guid=26553;

DELETE FROM creature_addon WHERE guid=26556;

UPDATE quest_template SET NextQuestIdChain=24903, RequiredNpcOrGo1=38530, RequiredNpcOrGoCount1=1, ObjectiveText1="Overheard the Banshee Queen." WHERE Id=24902;

UPDATE locales_quest SET ObjectiveText1_loc3="Belauscht die Bansheekönigin." WHERE Id=24902;

UPDATE creature_template SET npcflag=2, unit_flags=32776, ScriptName="npc_tobias_mistmantle_38507" WHERE entry=38507;

UPDATE creature_template_addon SET path_id=3850701, bytes2=1 WHERE entry=38507;

UPDATE creature_template SET ScriptName="npc_lady_sylvanas_windrunner_38530" WHERE entry=38530;

delete from phase_definitions where zoneId=4755;
INSERT INTO `phase_definitions` VALUES 
(4755, 0, 1, 0, 638, 683, 1, "Gilneas player startposition"),
(4755, 1, 2, 0, 638, 683, 1, "Gilneas player startposition"),
(4755, 2, 262144, 0, 656, 679, 1, "The fight for gilneas"),
(4755, 3, 524288, 0, 656, 679, 1, "(Vengeance or Survival) to (Patriarch\'s Blessing)"),
(4755, 4, 1048576, 0, 656, 679, 1, "(Patriarch\'s Blessing) to (They Have Allies, But So Do We)"),
(4755, 5, 2097152, 0, 656, 679, 1, "The Hunt For Sylvanas"),
(4755, 6, 4194304, 0, 656, 679, 1, "(They Have Allies, But So Do We) to (not set)");

delete from phase_area where areaId=4755;
INSERT INTO `phase_area` VALUES 
(4755, 0, 14078, 14091, 75, 1, 0, "Gilneas phase 1"),
(4755, 1, 14091, 14159, 66, 11, 0, "Gilneas phase 2"),
(4755, 2, 24676, 24904, 74, 11, 1, "Gilneas City Battle"),
(4755, 3, 24902, 24679, 64, 11, 1, "(Vengeance or Survival) to (Patriarch\'s Blessing)"),
(4755, 4, 24679, 24681, 64, 9, 1, "(Patriarch\'s Blessing) to (They Have Allies, But So Do We)"),
(4755, 5, 24904, 24902, 64, 11, 1, "The Hunt For Sylvanas"),
(4755, 6, 24681, 99999, 66, 11, 1, "(They Have Allies, But So Do We) to (not set)");






