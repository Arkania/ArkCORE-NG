

SET @ENTRY=43458;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid` in (0,1,2,3,4,5) AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(@ENTRY, 0, 0, "Danforth, berichtet.", 12, 1, 0, 0, 43592),
(@ENTRY, 1, 0, "Krakauer?", 12, 1, 0, 0, 43594),
(@ENTRY, 2, 0, "Jorgensen, was könnt Ihr uns über Renders Tal sagen?", 12, 1, 0, 0, 43597),
(@ENTRY, 3, 0, "Todesfalle? Messner, ich habe einen Plan. Ich benötige etwas Zephyrium.", 12, 1, 0, 0, 43599),
(@ENTRY, 4, 0, "Das ist nicht mein Problem, Messner. Macht schon.", 12, 1, 0, 0, 43601),
(@ENTRY, 5, 0, "$n, packt Eure Sachen zusammen. Ich schicke Euch ins Feld.", 12, 1, 0, 0, 43602);

SET @ENTRY=43459;
DELETE FROM `creature_text` WHERE `entry`=@ENTRY AND `groupid`=0 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(@ENTRY, 0, 0, "Zephyrium? Woher zum Teufel soll ich Zephyrium besorgen, Johnny?", 12, 6, 0, 0, 43600);

update creature_text set emote=274 where entry=43460 AND groupid=0 AND id=0;
update creature_text set emote=274 where entry=43462 AND groupid=0 AND id=0;
update creature_text set emote=1 where entry=43461 AND groupid in (0,1) AND id=0;


