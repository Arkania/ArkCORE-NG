

update creature_template set questItem3=58952 where entry=615;

DELETE FROM `creature_addon` WHERE (`guid`=33772);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (33772, 0, 0, 0, 1, 0, '80815 80816');

update quest_template set SourceSpellId=81004 where Id=26586;

SET @WP=341780;
SET @CGUID=34178;

UPDATE creature SET MovementType=2 WHERE guid=@CGUID;UPDATE creature_addon SET path_id=@WP WHERE guid=@CGUID;
update creature_addon set path_id=@WP where guid=@CGUID;

DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9166.21,-2740.42,88.7916,0.0,0,0,0,100),
(@WP,1,-9150.57,-2723.75,88.77946,0.0,0,0,0,100),
(@WP,2,-9158.66,-2702.11,88.77946,0.0,0,0,0,100),
(@WP,3,-9148.28,-2719.36,88.77946,0.0,0,0,0,100),
(@WP,4,-9153.93,-2728.32,88.77946,0.0,0,0,0,100),
(@WP,5,-9169.42,-2742.76,88.78236,0.0,0,0,0,100),
(@WP,6,-9174.83,-2753.66,88.78236,0.0,0,0,0,100),
(@WP,7,-9177.35,-2762.76,88.78236,0.0,0,0,0,100),
(@WP,8,-9183.65,-2770.92,88.73804,0.0,0,0,0,100);

SET @ENTRY=43300;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 11 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Is that the best you can do?",12,43434),
(@ENTRY,1,0,"You know, I've always wondered why they call themselves orcs.",12,43451),
(@ENTRY,2,0,"It's an ugly word, you know? It's a word I'd use to describe defecating. For example:",12,43452),
(@ENTRY,3,0,"After that Pilgrim's Bounty dinner, I took a huge smelly orc.",12,43453),
(@ENTRY,4,0,"I remember this one time, Keeshan and I were out fishing at the Lakeshire bridge and Keeshan farted. Don't think Oslow ever forgave Keeshan for that one...",12,43456),
(@ENTRY,5,0,"You know, Keeshan lost his wife to Blackrock orcs. He was never the same after that day. Was like the sun just set on his life. Darkness, lady. Pure darkness.",12,43457),
(@ENTRY,6,0,"They called us the Bravo Company. When things needed killin', we did the spillin'... of blood.",12,43458),
(@ENTRY,7,0,"Messner is a master of fire magic. We invite him to all of our barbecues.",12,43459),
(@ENTRY,8,0,"Jorgensen is real dainty, by the way. He's a paladin, so be careful what you say around him or you're liable to make him cry.",12,43460),
(@ENTRY,9,0,"So I hear Varian Wrynn is back. That true? Sorry, I'm a bit out of the loop.",12,43461),
(@ENTRY,10,0,"You ever notice how sarcastic the people living in Redridge are? Sometimes I feel like I just want to take a blow torch to that jackass Solomon's town hall.",12,43462),
(@ENTRY,11,0,"You got it, Johnny!",12,43525);

SET @ENTRY=43272;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 5 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"You orcs are gonna be sorry when I get out of here.",12,43405),
(@ENTRY,1,0,"Welcome to hell!",12,43440),
(@ENTRY,2,0,"Toe up...",12,43441),
(@ENTRY,3,0,"You know, I kept hearing the Blackrock orcs talk about the return of Hellscream to the Horde. What's that all about? Isn't Hellscream dead?",12,43470),
(@ENTRY,4,0,"I'm probably the most important member of this team, being a paladin and all.",12,43471),
(@ENTRY,5,0,"Real funny, Danforth.",12,43561);

SET @ENTRY=43303;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 3 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"And just like that, you're dead!",12,43437),
(@ENTRY,1,0,"Wait'll these orcs get a load of us. Bravo Company BACK IN BUSINESS!",12,43472),
(@ENTRY,2,0,"It's weird. My butt hurts. Not sure why.",12,43475),
(@ENTRY,3,0,"When this is all over, I'm taking a vacation.",12,43478);

SET @ENTRY=43302;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 6 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"You know, I've always wondered why they call themselves orcs.",12,43451),
(@ENTRY,1,0,"It's an ugly word, you know? It's a word I'd use to describe defecating. For example:",12,43452),
(@ENTRY,2,0,"After that Pilgrim's Bounty dinner, I took a huge smelly orc.",12,43453),
(@ENTRY,3,0,"You know, Keeshan lost his wife to Blackrock orcs. He was never the same after that day. Was like the sun just set on his life. Darkness, $g man:lady;. Pure darkness.",12,43457),
(@ENTRY,4,0,"Messner is a master of fire magic. We invite him to all of our barbecues.",12,43459),
(@ENTRY,5,0,"Jorgensen is real dainty, by the way. He's a paladin, so be careful what you say around him or you're liable to make him cry.",12,43460),
(@ENTRY,6,0,"Can't believe we're putting the old team back together. All thanks to you, $n.",12,43468);

SET @ENTRY=43457;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 7 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Take us out, Messner.",12,43524),
(@ENTRY,1,0,"We're here, everybody out!",12,43526),
(@ENTRY,2,0,"Danforth, report.",12,43592),
(@ENTRY,3,0,"Krakauer?",12,43594),
(@ENTRY,4,0,"Jorgensen, what do you have on Render's Valley?",12,43597),
(@ENTRY,5,0,"Death trap, eh? Messner, I got a plan. Gonna need some seaforium.",12,43599),
(@ENTRY,6,0,"Not my problem, Messner. Make it happen.",12,43601),
(@ENTRY,7,0,"$n, get your crap ready. I'm sending you out into the field.",12,43602);

SET @ENTRY=43432;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"You got it, Johnny!",12,43525),
(@ENTRY,1,0,"Seaforium? Where the hell am I gonna get seaforium from, Johnny?",12,43600);

SET @ENTRY=43462;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 0 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"The Blackrock orcs blew up the bridge leading to Stonewatch Keep. Frontal assault is out of the question.",12,43593);

SET @ENTRY=43461;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Two ways to get behind enemy lines, Johnny. Three if you count bein' dead.",12,43595),
(@ENTRY,1,0,"North through Alther's Mill, but we'd have to cut through an army of bloodthirsty worgs or south through Render's Valley.",12,43596);

SET @ENTRY=43460;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 0 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Blackrocks all over the damned place, Johnny. One main tower at the choke and two smaller huts. It's a death trap.",12,43598);

SET @ENTRY=43594;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 3 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Activate your Bravo Company Field Kit now.|TInterface\Icons\INV_MISC_ENGGIZMOS_20.BLP:16|t$BStealth your party using Camouflage.|TInterface\Icons\SPELL_NATURE_PROTECTIONFORMNATURE.BLP:16|t",12,43652),
(@ENTRY,1,0,"We're nearing Render's Valley. These orcs are tough! Make sure you are camo'd!|TInterface\Icons\SPELL_NATURE_PROTECTIONFORMNATURE.BLP:16|t",12,43653),
(@ENTRY,2,0,"Create a distraction so that you and Jorgensen can slip by unnoticed.|TInterface\Icons\ABILITY_ROGUE_BLOODYEYE.BLP:16|t",12,43654),
(@ENTRY,3,0,"Sometimes you just need to take out one target. Use chloroform while behind the enemy!|TInterface\Icons\SPELL_NATURE_SLEEP.BLP:16|t",12,43655);

-- what is this for player text?
-- sender player Chat type: RaidBossWhisper (42)
-- 44418 Marschgepäck der Kompanie Bravo AKTIV. Neue Fähigkeiten stehen jetzt auf Eurer Aktionsleiste zur Verfügung.$B$BSchaltet Marschgepäck der Kompanie Bravo aus zur DEAKTIVIERUNG.
-- 44419 Marschgepäck der Kompanie Bravo AKTIV. 'Zephyrium platzieren' steht jetzt in Eurer Aktionsleiste zur Verfügung.$BSchaltet das Marschgepäck der Kompanie Bravo aus zur DEAKTIVIERUNG.

SET @ENTRY=43546;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 5 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"My heals really don't have the 'OOMPH' that they used to, $n. You know what I'm saying?",12,43658),
(@ENTRY,1,0,"I don't know, maybe the grass really is greener on the other side. You know? Krakauer and Danforth really kick butt as warriors. Maybe I should drop this paladin thing and try out being a warrior.",12,43661),
(@ENTRY,2,0,"One time, Keeshan told me that he could take on five of me at once. Why am I so weak?",12,43668),
(@ENTRY,3,0,"Make sure we always have camouflage up. The orcs in Render's Valley will kill us both if we're spotted.",12,43670),
(@ENTRY,4,0,"While camouflaged, we are harder to detect when we are BEHIND creatures.",12,43674),
(@ENTRY,5,0,"Once in a while we'll come up against a lone orc that stands between us and victory. Chloroform is often best used in those situations. Just remember to apply chloroform we have to be behind the enemy.",12,43678);

SET @ENTRY=43571;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 0 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"We're free! RUN FOR YOUR LIVES!",12,43638);

SET @ENTRY=43590;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"You have successfully planted the seaforium at the munitions hut.",42,43646),
(@ENTRY,1,0,"You have successfully planted the seaforium at the Blackrock tower.",42,43647);

SET @ENTRY=43610;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 0 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Johnny, you do realize that we just blew up half of Redridge, right?",12,43784);

SET @ENTRY=43611;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 2 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Redridge'll heal, but them orcs sure won't...",12,43786),
(@ENTRY,1,0,"Heads up! PAYLOAD INCOMING!",12,43807),
(@ENTRY,2,0,"Troteman.",12,43809);

SET @ENTRY=43744;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 17 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Redridge'll heal, but them orcs sure won't...",12,43786),
(@ENTRY,1,0,"Heads up! PAYLOAD INCOMING!",12,43807),
(@ENTRY,2,0,"Troteman.",12,43809),
(@ENTRY,3,0,"AAHHHHHHHHH!!!!",14,43822),
(@ENTRY,4,0,"AAHHHHHHHHHHHHHHHHHH!!!!",14,43823),
(@ENTRY,5,0,"AAAAAAAAAAAHHHHHHHHHHHHH!!!!",14,43824),
(@ENTRY,6,0,"BLOOD AND THUNDER, RIGHT!?",14,43825),
(@ENTRY,7,0,"I CAN'T FIND YOUR LEGS, JOEY! I CAN'T FIND YOUR DAMNED LEGS!",14,43826),
(@ENTRY,8,0,"AAAHHHH!",14,43827),
(@ENTRY,9,0,"RUN TO YOUR DARK GODS, YOU FILTHY ANIMALS!",14,43828),
(@ENTRY,10,0,"THERE ARE NO FRIENDLY CIVILIANS!",14,43829),
(@ENTRY,11,0,"FEEL THE THUNDER!",12,44130),
(@ENTRY,12,0,"WAR IS IN MY BLOOD!",12,44127),
(@ENTRY,13,0,"You brought this on yourself!",12,44128),
(@ENTRY,14,0,"Shoulda just left us alone.",12,44129),
(@ENTRY,15,0,"You're nothing!",12,44131),
(@ENTRY,16,0,"Your pain excites me!",12,44132),
(@ENTRY,17,0,"You gutless bastard! You've killed 'em all! Now I kill you!",14,44210);

SET @ENTRY=43607;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 17 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Where the hell did this come from?",12,43808),
(@ENTRY,1,0,"Troteman?",12,43810);

SET @ENTRY=43728;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 0 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"",12,43811);

SET @ENTRY=429;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Grrrr... fresh meat!",12,1870),
(@ENTRY,0,1,"More bones to gnaw on...",12,1871),
(@ENTRY,1,0,"%s attempts to run away in fear!",16,1150);

SET @ENTRY=568;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Grrrr... fresh meat!",12,1870),
(@ENTRY,0,1,"More bones to gnaw on...",12,1871),
(@ENTRY,1,0,"%s attempts to run away in fear!",16,1150);

SET @ENTRY=431;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Grrrr... fresh meat!",12,1870),
(@ENTRY,0,1,"More bones to gnaw on...",12,1871),
(@ENTRY,1,0,"%s attempts to run away in fear!",16,2125);

SET @ENTRY=432;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 1;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"Grrrr... fresh meat!",12,1870),
(@ENTRY,0,1,"More bones to gnaw on...",12,1871),
(@ENTRY,1,0,"%s attempts to run away in fear!",16,1191);

SET @ENTRY=397;
DELETE FROM creature_text where entry=@ENTRY AND groupid BETWEEN 0 AND 5 AND id=0;
INSERT INTO creature_text 
(entry,groupid,id,text,type,BroadcastTextID) VALUES 
(@ENTRY,0,0,"The pathway to damnation awaits...",12,43800),
(@ENTRY,1,0,"You realize not the error of your ways, but soon you will cower before Darkblaze.",12,43801),
(@ENTRY,2,0,"MINION, to my aid!",14,43806),
(@ENTRY,3,0,"Did you truly believe that the orcs had the presence of mind required to plan an invasion of this magnitude?",12,44172),
(@ENTRY,4,0,"The Bravo Company, all present and accounted for...",12,44173),
(@ENTRY,5,0,"No matter. You will die now, a paltry offering to Deathwing as our march upon Stormwind begins.",12,44174);


