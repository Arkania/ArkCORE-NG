
delete from creature_text where entry=34851 and groupid=0 and id=0;
insert into creature_text values(34851,0,0,"What...what are those things on the rooftops?",12,0,100,0,0,0,"say");

delete from creature_text where entry=34864 and groupid=0 and id between 0 and 2;
insert into creature_text values(34864,0,0,"No one\'s allowed to leave. Prince Liam\'s orders.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate");
insert into creature_text values(34864,0,1,"Stay calm. We have everything under control.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate");
insert into creature_text values(34864,0,2,"It isn\'t safe to leave, there\'s something lurking out there in the woods.",12,0,100,0,0,0,"SAY_GILNEAS_CITY_GUARD_1 - At gate");

delete from creature_text where entry=34981 and groupid=0 and id between 0 and 7;
insert into creature_text values(34981,0,0,"Protect me, please!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,1,"What in the world? Let\'s get out of here!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,2,"Worgen! Worgen everywhere!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,3,"Flee! They\'re everywhere!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,4,"No time to Waste!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,5,"This place isn\'t safe. Let\'s Leave!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,6,"Let\'s go!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");
insert into creature_text values(34981,0,7,"Thank you!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - No worgen behind");

delete from creature_text where entry=44086 and groupid=0 and id between 0 and 3;
insert into creature_text values(44086,0,0,"What\'s going on? I thought I saw something on the rooftops.",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate");
insert into creature_text values(44086,0,1,"My children are in Stormglen alone! I have to get to them!",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate");
insert into creature_text values(44086,0,2,"You can\'t do this to us!",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate");
insert into creature_text values(44086,0,3,"What... what are those things on the rooftops?",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Phase 1 at gate");

delete from creature_text where entry=44086 and groupid=1 and id between 0 and 1;
insert into creature_text values(44086,1,0,"We have to get out of here! The howling gets louder every night.",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Military distrcit");
insert into creature_text values(44086,1,1,"They told us Gilneas City was safe...",12,0,100,0,0,0,"SAY_PANICKED_CITIZEN - Military distrcit");

delete from creature_text where entry=35836 and groupid=0 and id between 0 and 4;
insert into creature_text values(35836,0,0,"I don\'t want to die!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - Worgen behind");
insert into creature_text values(35836,0,1,"There\'s one after me!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - Worgen behind");
insert into creature_text values(35836,0,2,"It\'s coming right for me!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - Worgen behind");
insert into creature_text values(35836,0,3,"Help!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - Worgen behind");
insert into creature_text values(35836,0,4,"Help me, please!",12,0,100,0,0,0,"SAY_FRIGHTENED_CITIZEN - Worgen behind");

update creature_text set sound=19616 where entry=34850 and groupid=1 and id=0;
update creature_text set sound=19614 where entry=34850 and groupid=2 and id=0;

