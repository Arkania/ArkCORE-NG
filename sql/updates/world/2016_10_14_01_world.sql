
UPDATE locales_quest SET QuestGiverTextWindow_loc3="Überlebender Goblin", QuestGiverTargetName_loc3="Überlebender Goblin" WHERE Id=14001;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Überlebender Goblin", QuestGiverTargetName_loc3="Überlebender Goblin" WHERE Id=14474;

DELETE FROM creature_text WHERE entry=36600 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(36600, 1, 0, "Yeah, there's tons of people still trapped in the escape pods, boss. Oh, wait. I guess you're not the boss anymore. Anyways, they're all probably going to drown if you don't get them out.", 12, 0, 100, 0, 0, 0, "Geargrinder Gizmo", 49824);

delete from creature where id=34748;

UPDATE gameobject_template SET data1=0, data2=0, data5=0, data10=0, data24=14474, data25=14001 WHERE entry=195188;

UPDATE quest_template SET RequiredNpcOrGo2=0, RequiredNpcOrGoCount2=0 WHERE Id=14001;
UPDATE quest_template SET RequiredNpcOrGo2=0, RequiredNpcOrGoCount2=0 WHERE Id=14474;

UPDATE gameobject_template SET ScriptName="go_goblin_escape_pod_195188" WHERE entry=195188;

UPDATE creature_template SET ScriptName="npc_goblin_survivor_34748" WHERE entry=34748;

UPDATE creature_template SET ScriptName="npc_trade_prince_gallywix_35649" WHERE entry=35649;

DELETE FROM creature_text WHERE entry=34748;
INSERT INTO creature_text VALUES 
(34748, 0, 0, "What, are you crazy?! Trying to blow me to smithereens like that!", 12, 0, 100, 5, 0, 0, "Goblin Survivor", 35002),
(34748, 0, 1, "$N, it's you! Thanks, $G man : sweetie;!", 12, 0, 100, 5, 0, 0, "", 35003),
(34748, 0, 2, "Blowing open my escape pod. I like your style, $N!", 12, 0, 100, 25, 0, 0, "Goblin Survivor", 35004),
(34748, 0, 3, "$N? I heard you were dead.", 12, 0, 100, 6, 0, 0, "Goblin Survivor", 35005),
(34748, 0, 4, "Couldn't you have just used a crowbar?", 12, 0, 100, 6, 0, 0, "Goblin Survivor", 35006),
(34748, 0, 5, "$N! Please tell me that monster, the Trade Prince, didn't survive?!", 12, 0, 100, 4, 0, 0, "Goblin Survivor", 35007),
(34748, 0, 6, "Thanks, $N. You still owe me that money, $G man : lady;!", 12, 0, 100, 1, 0, 0, "Goblin Survivor", 35008),
(34748, 0, 7, "What were those Alliance ships doing firing at us?! Did I see a Horde ship, too?", 12, 0, 100, 5, 0, 0, "Goblin Survivor", 35009);

delete from event_scripts where id=195188;

UPDATE creature_text SET sound=19562 WHERE entry=35649 AND groupid=0 AND id=0;

DELETE FROM creature_template_addon WHERE entry=35649;
INSERT INTO creature_template_addon VALUES 
(35649, 0, 0, 50331648, 1, 0, "37744");

UPDATE creature_template SET minlevel=85, maxlevel=85, faction=2204, unit_flags=32776, InhabitType=6 WHERE entry=35649;

UPDATE creature_template SET InhabitType=6 WHERE entry=34748;

UPDATE quest_template SET PrevQuestId=14248, NextQuestId=0, ExclusiveGroup=0, Method=2 WHERE Id=14031;

UPDATE quest_template SET PrevQuestId=14248, NextQuestId=0, ExclusiveGroup=0 WHERE Id=14233;

UPDATE quest_template SET NextQuestIdChain=14248 WHERE Id=14014;

UPDATE quest_template SET PrevQuestId=14031 WHERE Id=14234;

