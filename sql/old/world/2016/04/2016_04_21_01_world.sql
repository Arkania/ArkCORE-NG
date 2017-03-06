
-- fix issue #134
update creature set position_x=-1901.85, position_y=2255.92, position_z=42.4066 where id=36452 and guid=24487;

update npc_text set BroadcastTextID0=36593 where id=15025;

delete from creature where id=36452 and guid=24987;

UPDATE quest_template SET PrevQuestId=14401 WHERE Id=14402;

UPDATE quest_template SET PrevQuestId=14400 WHERE Id=14401;

UPDATE quest_template SET PrevQuestId=14404 WHERE Id=14412;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Schiffbrüchige Verlassene", QuestGiverTargetName_loc3="Schiffbrüchige Verlassene" WHERE Id=14412;

UPDATE quest_template SET PrevQuestId=14403 WHERE Id=14404;

UPDATE quest_template SET PrevQuestId=14397 WHERE Id=14403;

UPDATE locales_quest SET Title_loc3="Pferde für Dämmerhafen", Objectives_loc3="Sprecht mit Gwen Armstead in Dämmerhafen.", Details_loc3="Die Pferde gerettet zu haben, könnte bedeuten, dass auch die Stadt gerettet ist. Es gibt zwar ausreichend Karren in Dämmerhafen, aber nicht genügend Pferde, um sie zu ziehen.$B$BGeht und sagt Bürgermeisterin Armstead, dass die Pferde, die Ihr gerettet habt, zu ihrer Verfügung stehen.$B$BIch bereite alles vor und stoße dann bald zu Euch.", OfferRewardText_loc3="Fantastische Arbeit, $N. Ich denke ich spreche für alle, wenn ich sage, je schneller wir hier rauskommen, desto besser." WHERE Id=14463;

UPDATE quest_template SET PrevQuestId=14416 WHERE Id=14463;

UPDATE quest_template SET PrevQuestId=14406 WHERE Id=14416;

UPDATE quest_template SET PrevQuestId=14397 WHERE Id=14398;

DELETE FROM creature_addon WHERE guid=166070;
DELETE FROM creature_addon WHERE guid=166066;
DELETE FROM creature_addon WHERE guid=161836;

delete from game_event_creature where guid in (45642, 45643, 45647, 128147, 161836, 166066, 166070);

delete from game_event_gameobject where guid in (180999);

delete from quest_poi where questId=14403 and id=0;
