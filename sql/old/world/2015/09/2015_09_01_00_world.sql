
-- http://www.wowhead.com/npc=25315/kiljaeden
UPDATE creature_template SET unit_flags=32832 WHERE entry=25315;

DELETE FROM creature_text WHERE entry=46964;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(46964, 0, 0, "That bitch Sylvanas sent you too,did she?No matter,your journey ends in agony.", 14, 0, 100, 0, 0, 0, 48835, "on Aggro Text"),
(46964, 1, 0, "Lord Godfrey begins to cast Pistol Barrage!", 41, 0, 100, 0, 0, 0, 50242, "on Cast Text"),
(46964, 2, 0, "I thank you for the clearn death.I would not of done the same... ", 14, 0, 100, 0, 0, 0, 48838, "on Death Text");


DELETE FROM creature_text WHERE entry=3887;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(3887, 0, 0, "Leave this accursed place at once!", 14, 0, 100, 0, 0, 0, 48821, "on Aggro Text"),
(3887, 1, 0, "This death is only a temporary respite from my curse.", 14, 0, 100, 0, 0, 0, 48823, "on Death Text");


DELETE FROM creature_text WHERE entry=1287;
INSERT INTO creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, BroadcastTextID, comment) VALUES 
(1287, 0, 0, "Welcome!", 12, 0, 0, 1, 300, 0, 43339, ""),
(1287, 0, 1, "Greetings, $c.", 12, 0, 0, 1, 400, 0, 43340, ""),
(1287, 0, 2, "Greetings! Please have a look around.", 12, 0, 0, 1, 400, 0, 43341, ""),
(1287, 0, 3, "Let me know if you need help finding anything, $c.", 12, 0, 0, 1, 400, 0, 43342, ""),
(1287, 0, 4, "Welcome. May I help you find something?", 12, 0, 0, 1, 400, 0, 43343, ""),
(1287, 0, 5, "Greetings.", 12, 0, 0, 1, 400, 0, 43344, ""),
(1287, 0, 6, "Welcome.", 12, 0, 0, 1, 100, 0, 43345, "");

UPDATE quest_template SET Method=2, PrevQuestId=29411 WHERE Id=29413;
UPDATE locales_quest SET Title_loc3="Die unheimliche Kiste", Details_loc3="Nach ihr ist gesucht worden, sie wurde gestohlen und verkauft. Jeder, der versucht hat, die in ihr enthaltene Magie anzuzapfen, musste erleben, dass sich diese Macht gegen ihn wandte.$B$BUnd doch erscheint die Kiste selbst unversehrt zu sein und erfüllt von magischer Energie. Von Zeit zu Zeit zittert und hüpft sie, als ob ihr Inhalt lebendig wäre.$B$BSie scheint an Euch gebunden zu sein und jetzt gehört sie Euch." WHERE Id=29413;

UPDATE quest_template SET Method=2 WHERE Id=29429;
UPDATE locales_quest SET Title_loc3="Die unheimliche Kiste", Details_loc3="Nach ihr ist gesucht worden, sie wurde gestohlen und verkauft. Jeder, der versucht hat, die in ihr enthaltene Magie anzuzapfen, musste erleben, dass sich diese Macht gegen ihn wandte.$B$BUnd doch erscheint die Kiste selbst unversehrt zu sein und erfüllt von magischer Energie. Von Zeit zu Zeit zittert und hüpft sie, als ob ihr Inhalt lebendig wäre.$B$BSie scheint an Euch gebunden zu sein und jetzt gehört sie Euch." WHERE Id=29429;

update locales_creature_text set text_loc3="Rüstungen zu verkaufen, kommt näher!" where entry=1291 and groupid=0 and id=0;
update locales_creature_text set text_loc3="Es sind neue Rüstungen aus Kalimdor eeingetroffen. Kommt und seht was ich für euch habe!" where entry=1291 and groupid=0 and id=1;

update game_event set start_time="2015-10-18 10:00:00", end_time="2020-11-01 10:00:00", occurence=475000, length=20160 where eventEntry=12;







