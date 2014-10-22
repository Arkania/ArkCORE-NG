
-- Quest: Pack Your Bags 24492

update creature_template set AIName="", ScriptName="npc_hands_springsprocket" where entry=6782;

update gameobject_template set data8=24492 where entry=201704;
update gameobject_template set data8=24492 where entry=201705;
update gameobject_template set data0=43, data6=-1, data8=24492, data14=0 where entry=201706;

delete from gameobject_loot_template where entry=201706;
insert into gameobject_loot_template values (201706,49754,100,1,0,1,1);

update creature_template set AIName="", ScriptName="npc_milos_gyro_spawned" where entry=37198;
UPDATE creature_template SET npcflag=33554432,InhabitType=7 WHERE entry=37198;

delete from creature_text where entry=37198 and groupid between 0 and 6;
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) values 
(37198,0,0,"<static> Is this thing on? Hello?",12,0,100,0,0,0,"Text during flying"),
(37198,1,0,"Ahh, there you are. Hello! I figured that, while you're flying to Kharanos, I'd give you some data about what's going on outside of Coldridge Valley.",12,0,100,0,0,0,"Text during flying"),
(37198,2,0,"And if you'll look to your left, you'll see that the gnomes have retaken Gnomeregan. Hooray for us!",12,0,100,0,0,0,"Text during flying"),
(37198,3,0,"If you thought you had problems with trolls in Coldridge, wait 'til you get to Kharanos! That big cataclysm got the trolls all stirred up out here.",12,0,100,0,0,0,"Text during flying"),
(37198,4,0,"It seems you Coldridge folks are dreadfully under-informed about the events of the last few days.",12,0,100,0,0,0,"Text during flying"),
(37198,5,0,"There's plenty else going on out here, too. We've opened up the path to the airport, there's rumors of Dark Irons in the east... oh, and I think something weird is going on with that dwarf king, Magni. Might want to check it out.",12,0,100,0,0,0,"Text during flying"),
(37198,6,0,"And here we are! Welcome to Kharanos! Watch your step on the way out.",12,0,100,0,0,0,"Text during flying");

