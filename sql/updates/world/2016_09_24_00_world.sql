
UPDATE quest_template SET Method=2, RequiredRaces=0, NextQuestId=24520, ExclusiveGroup=0 WHERE Id=24503; 

UPDATE quest_template SET Method=0, Flags=0, RequiredRaces=0 WHERE Id=28414; 

UPDATE creature_template SET type_flags=4256 WHERE entry=34957;
UPDATE creature_template SET type_flags=4256 WHERE entry=34958;
UPDATE creature_template SET type_flags=4256 WHERE entry=34959;


DELETE FROM creature_text WHERE entry=34957;
INSERT INTO creature_text VALUES 
(34957, 0, 0, "Go for the face! Go for the face!", 12, 0, 100, 0, 0, 0, "Ace Say", 35385),
(34957, 0, 1, "Is this the deadbeat?", 12, 0, 100, 0, 0, 0, "Ace Say", 35386),
(34957, 0, 2, "Get 'em!", 12, 0, 100, 0, 0, 0, "Ace Say", 35387),
(34957, 0, 3, "I never liked you anyway!", 12, 0, 100, 0, 0, 0, "Ace Say", 35388),
(34957, 0, 4, "It's payback time!", 12, 0, 100, 0, 0, 0, "Ace Say", 35389),
(34957, 0, 5, "You do NOT mess with us!", 12, 0, 100, 0, 0, 0, "Ace Say", 35390),
(34957, 0, 6, "You lookin' at me?", 12, 0, 100, 0, 0, 0, "Ace Say", 35391),
(34957, 0, 7, "I been waitin' all day for this!", 12, 0, 100, 0, 0, 0, "Ace Say", 35392),
(34957, 1, 0, "What was that thing, $G dude : toots;?", 12, 0, 100, 0, 0, 0, "Ace Say", 48862);

DELETE FROM creature_text WHERE entry=34959;
INSERT INTO creature_text VALUES 
(34959, 0, 0, "Go for the face! Go for the face!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35385),
(34959, 0, 1, "Is this the deadbeat?", 12, 0, 100, 0, 0, 0, "Izzy Say", 35386),
(34959, 0, 2, "Get 'em!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35387),
(34959, 0, 3, "I never liked you anyway!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35388),
(34959, 0, 4, "It's payback time!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35389),
(34959, 0, 5, "You do NOT mess with us!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35390),
(34959, 0, 6, "You lookin' at me?", 12, 0, 100, 0, 0, 0, "Izzy Say", 35391),
(34959, 0, 7, "I been waitin' all day for this!", 12, 0, 100, 0, 0, 0, "Izzy Say", 35392),
(34959, 1, 0, "Why's the ground shaking, $N?!", 12, 0, 100, 0, 0, 0, "Izzy Say", 48861);




	