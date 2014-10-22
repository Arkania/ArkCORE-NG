
-- josiah_avery_worgen_phase8 is spawned from player
delete from creature where guid=240756;

-- set spell from script
update quest_template set RewardSpellCast=0 where Id=14159;

-- wrong quest level
UPDATE quest_template SET Level=2,MinLevel=1 WHERE Id=14276;

-- wrong quest chain
UPDATE quest_template SET PrevQuestId=14290 WHERE Id=24930;

-- no move for creature
UPDATE creature_template SET unit_flags=33028 WHERE entry=35077;

-- pinfo fix from reppz
delete from arkcore_string where entry in (453,550,548,549,714,716);
insert into arkcore_string (entry, content_default) values 
(453, "│Player %s %s (guid: %u)"),
(550, "Mute time remaining: %s, By: %s, Reason: %s"),
(548, "Player%s %s (guid: %u) Account: %s (id: %u) Email: %s GMLevel: %u Last IP: %s Last login: %s Latency: %ums"),
(549, "Race: %s Class: %s Played time: %s Level: %u Money: %ug%us%uc"),
(714, "│ Account: %s (ID: %u), GMLevel: %u"),
(716, "│ Last Login: %s (Failed Logins: %u)");

-- delete old names.. 
delete from command where name = "reload creature_involvedrelation";
delete from command where name = "reload creature_questrelation";
delete from command where name = "reload gameobject_involvedrelation";
delete from command where name = "reload gameobject_questrelation";
delete from command where name = "reload areatrigger_involvedrelation";
delete from command where name = "reload trinity_string";





