
delete from creature_addon where guid in (237994, 238012, 238013, 238057, 238099, 238261, 238262, 239014, 239015, 239016);
insert into creature_addon values 
(237994, 0, 0, 0, 1, 0, "29266"),
(238012, 0, 0, 0, 1, 0, "29266"),
(238013, 0, 0, 0, 1, 0, "29266"),
(238261, 0, 0, 0, 1, 0, "29266"),
(238262, 0, 0, 0, 1, 0, "29266"),
(239014, 0, 0, 0, 1, 0, "29266"),
(239015, 0, 0, 0, 1, 0, "29266"),
(239016, 0, 0, 0, 1, 0, "29266");

delete from creature where guid in (238057, 238099);

update creature set curhealth=1, curmana=0, spawndist=0, MovementType=0, unit_flags=262144, dynamicflags=41 where guid in 
(237994, 238012, 238013, 238261, 238262, 239014, 239015, 239016);

UPDATE quest_template SET PrevQuestId=12720 WHERE Id=12723;

UPDATE quest_template SET PrevQuestId=12723 WHERE Id=12725;

UPDATE quest_template SET PrevQuestId=12751 WHERE Id=12754;

delete from creature where id=54386;


DELETE FROM creature_text WHERE entry=29001;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(29001, 0, 0, "The Crusade will purge your kind from this world!", 14, 0, 100, 0, 0, 0, 29215, "high inquisitor valroth start"),
(29001, 1, 0, "It seems that I'll need to deal with you myself. The High Inquisitor comes for you, Scourge!", 14, 0, 100, 0, 0, 0, 29216, "high inquisitor valroth SAY_VALROTH_AGGRO"),
(29001, 2, 0, "You have come seeking deliverance? I have come to deliver!", 12, 0, 100, 0, 0, 0, 29222, "high inquisitor valroth SAY_VALROTH_RAND"),
(29001, 2, 1, "LIGHT PURGE YOU!", 12, 0, 100, 0, 0, 0, 29221, "high inquisitor valroth SAY_VALROTH_RAND"),
(29001, 2, 2, "Coward!", 12, 0, 100, 0, 0, 0, 29219, "high inquisitor valroth SAY_VALROTH_RAND"),
(29001, 3, 0, "%s's remains fall to the ground.", 16, 0, 100, 0, 0, 0, 29223, "high inquisitor valroth SAY_VALROTH_DEATH");

delete from creature where guid=239097;





