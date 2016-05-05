

-- quest 29438 He Shoots, He Scores!
-- npc 14841 Rinling
UPDATE creature_template SET gossip_menu_id=0, AIName="", ScriptName="npc_rinling_14841" WHERE entry=14841;

delete from gossip_menu_option where menu_id=6225;
INSERT INTO `gossip_menu_option` VALUES 
(6225, 0, 0, "How does the Shooting Gallery work?", 53329, 1, 1, 0, 0, 0, 0, 0, '', 0),
(6225, 1, 0, "Let\'s shoot! |cFF0008E8(Darkmoon Game Token)|r", 53042, 1, 1, 0, 0, 0, 0, 0, '', 0),
(6225, 2, 0, "Let\'s shoot! |cFF0008E8(Darkmoon Game Token)|r", 53042, 1, 1, 0, 0, 0, 0, 0, '', 0);

-- questgiver Gelvas Grimegate
delete from creature_queststarter where id=14828 and quest in (7905, 7930, 7931, 7932, 7933, 7934, 7935, 7936, 7940, 7981, 9249);

-- questgiver 14832 Kerri Hicks
delete from creature_queststarter where id=14832 and quest in (7889, 7890, 7891, 7892, 7893, 7939);

UPDATE quest_template SET Level=1 WHERE Id=29433;

UPDATE locales_quest SET OfferRewardText_loc3="Habt Ihr Euch Herausforderungen gesucht oder einfach nur Eber auf einem Feld abgeschlachtet?$B$BIch bin aus gutem Grund die Stärkste.$B$BVielleicht werde ich Euch eines Tages zeigen, wie stark ich wirklich bin, $C. Bis dahin müsst Ihr Euch weiter anstrengen, aber vergesst nicht, ab und zu eine Pause zu machen.$B$BSo wie jetzt zum Beispiel. Hier, genießt den Dunkelmond-Jahrmarkt." WHERE Id=29433;

-- questgiver 14829 Yebb Neblegear
UPDATE quest_template SET Level=1 WHERE Id=29508;

delete from creature_queststarter where id=14829 and quest in (7899, 7900, 7901, 7902, 7903, 7943, 8222, 8223);

-- npc=54485 jessica rogers
UPDATE creature_template SET gossip_menu_id=0, AIName="", ScriptName="npc_jessica_rogers_54485" WHERE entry=54485;

update creature_addon set bytes2=1, auras="101696" where guid=270424;

UPDATE creature_template SET AIName="", ScriptName="npc_dubenko_54490" WHERE entry=54490;

delete from creature_addon where guid in (270448, 270445, 270443);

update creature set MovementType=0 where id=54518 and guid in (270448, 270445, 270443);

-- chronos
delete from creature_queststarter where id=14833 and quest in (7881, 7882, 7883, 7884, 7885, 7941);

-- morja
UPDATE locales_quest SET RequestItemsText_loc3="Ich bin so froh, dass Jubjub wieder da ist. Die Kleine liebt Dunkeleisenbier so sehr, dass sie, als mein Vorrat zuneige ging, weggerannt ist, um mehr davon zu suchen.$B$BJetzt, da Jubjub zurück ist, versuche ich, so viel Bier wie möglich zu kriegen! Ich möchte nicht, dass sie wieder wegläuft, wisst Ihr?$B$BHabt Ihr vielleicht etwas Dunkeleisenbier dabei? Wenn ja, gebe ich Euch eines von Jubjubs Froscheiern für einen Krug Dunkeleisenbier..." WHERE Id=7946;

UPDATE quest_template SET Method=2, Level=1, RequestItemsText="I'm so happy Jubjub is no longer lost.  She loves Dark Iron ale so much that when I ran out... she ran away to find more!$B$BNow that Jubjub's back, I want as much ale as I can get!  I won't want her to run away again!$B$BDo you have any Dark Iron Ale?  If you do, then I'll trade you one of Jubjub's frog eggs for a mug..." WHERE Id=7946;

delete from creature_queststarter where id=14871 and quest=7946;
 
update creature_template set AIName="", ScriptName="npc_morja_14871" where entry=14871;
 
SET @GUID=27036001;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4204.738, 6223.438, 13.11736, 4.229351, 0, 0),
(@GUID, 1, -4208.465, 6219.545, 13.11736, 4.614199, 3000, 0),
(@GUID, 2, -4209.27, 6215.017, 13.16154, 4.551367, 2000, 0),
(@GUID, 3, -4208.152, 6220.754, 13.11791, 1.378353, 2000, 0),
(@GUID, 4, -4199.87, 6228.883, 13.11791, 1.547214, 0, 0);

SET @GUID=27036002;
DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4197.104, 6220.236, 13.11699, 5.171834, 0, 0),
(@GUID, 1, -4188.646, 6211.639, 13.73279, 6.012206, 3000, 0),
(@GUID, 2, -4198.166, 6220.54, 13.11736, 2.210879, 2000, 0),
(@GUID, 3, -4199.87, 6228.883, 13.11791, 1.547214, 0, 0);



