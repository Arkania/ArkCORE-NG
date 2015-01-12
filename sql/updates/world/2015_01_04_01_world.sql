
delete from gameobject where guid=404398 and id=301066;
insert into gameobject (guid,id,map,position_x,position_y,position_z) values
(404398,301066,36,-15.7351,-380.341,61.2262);	

update creature_template set AIName="", ScriptName="npc_vision_of_the_past" where entry=42693;

update creature_template set faction_A=35, faction_H=35 where entry=42693;
update creature_template set InhabitType=7, npcflag=33554432, unit_flags=131840 where entry=42693;

SET @MGUID=426930;
DELETE FROM `waypoint_data` WHERE `id`=@MGUID;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`delay`,`move_flag`) VALUES
(@MGUID, 1, -96.52084, -701.32290, 26.23725, 0, 0),
(@MGUID, 2, -72.31250, -732.91840, 34.70948, 0, 0),
(@MGUID, 3, -40.28125, -763.78300, 43.54280, 0, 0),
(@MGUID, 4, -2.12500, -818.70140, 57.04280, 0, 0),
(@MGUID, 5, -27.65799, -850.71010, 57.04280, 0, 0),
(@MGUID, 6, -63.17188, -829.31770, 47.68164, 0, 0);	

delete from creature_text where entry=42693 and groupid=0 and id=0;
insert into creature_text values 
(42693, 0, 0, "|cFF768EBD5 Years ago...|r |TInterface\QuestFrame\UI-QUESTLOG-BOOKICON.BLP:32|t", 42, 0, 100, 0, 0, 0, "talk Vision of the past", 0);

delete from creature_text where entry=42699 and groupid in(0,1,2,3) and id=0;
insert into creature_text values 
(42699, 0, 0, "Victory for the Alliance! Glory to Stormwind!", 14, 0, 100, 0, 0, 0, "Alliance Warrior yells", 0),
(42699, 1, 0, "Let us return to Sentinel Hill, allies, and inform Gryan of VanCleef's demise!", 12, 0, 100, 0, 0, 0, "Alliance Warrior says", 0),
(42699, 2, 0, "There's nowhere left to hide, VanCleef! The Defias are THROUGH!", 14, 0, 100, 0, 0, 0, "Alliance Warrior yells", 0),
(42699, 3, 0, "We're here to finish this! Face us, coward!", 14, 0, 100, 0, 0, 0, "Alliance Warrior yells", 0);

delete from creature_text where entry=42697 and groupid in(0,1,2,3,4) and id=0;
insert into creature_text values 
(42697, 0, 0, "None may callenge the Brotherhood!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 0),
(42697, 1, 0, "%s ruft weitere Verbündete aus den Schatten.", 16, 0, 100, 0, 0, 0, "Edwin van Cleef MonsterEmote", 0),
(42697, 2, 0, "Lapdogs, all of you!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 0),
(42697, 3, 0, "Fools! Our cause is righteous!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 0),
(42697, 4, 0, "The Brotherhood shall prevail!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 0);

delete from creature_text where entry=42698 and groupid in(0) and id=0;
insert into creature_text values 
(42698, 0, 0, "%s jumps out of the shadows!", 16, 0, 100, 0, 0, 0, "Defias Blackguard", 0);

delete from creature_text where entry=42371 and groupid in(0) and id=0;
insert into creature_text values 
(42371, 0, 0, "Daddy...", 16, 0, 100, 0, 0, 0, "Vanessa van Cleef says", 0);

update creature_template set AIName="", ScriptName="npc_edwin_van_cleef" where entry=42697;





