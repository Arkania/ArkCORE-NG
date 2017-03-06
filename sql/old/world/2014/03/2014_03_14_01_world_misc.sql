

delete from creature_text where entry=44086;
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) values
(44086,0,0,"My children are in Stormglen alone! I have to get to them!",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate"),
(44086,0,1,"You can\'t do this to us!",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate"),
(44086,1,0,"What... what are those things on the rooftops?",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate"),
(44086,1,1,"They told us Gilneas City was safe...",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Military distrcit"),
(44086,1,2,"What\'s going on? I thought I saw something on the rooftops.",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate"),
(44086,2,0,"We have to get out of here! The howling gets louder every night.",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Military distrcit");

delete from creature_text where entry=34864;
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) values
(34864,0,0,"No one\'s allowed to leave. Prince Liam\'s orders.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate"),
(34864,1,0,"Stay calm. We have everything under control.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate"),
(34864,2,0,"It isn\'t safe to leave, there\'s something lurking out there in the woods.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate");

update creature_addon set emote=0 where guid in(240529,240530,240542,240543,240544,240545,240546,240547,240548,240602);