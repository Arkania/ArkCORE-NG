
UPDATE locales_quest SET OfferRewardText_loc3="Ihr müsst diese Notiz nach Sturmwind bringen? Das ist kein Problem, Ihr könnt einen meiner Greifen nehmen!", RequestItemsText_loc3="Ihr seht aus, als hättet Ihr es eilig. Tja, dann seid Ihr hier genau richtig!" WHERE Id=26393;

UPDATE locales_quest SET OfferRewardText_loc3="Ah, eine Notiz von Schmied Argus? Es überrascht mich gar nicht, dass er mehr Ausrüstung braucht. Heutzutage gibt es so viele neue Rekruten.$B$BIch danke Euch, $N. Hier habt Ihr etwas Geld für Eure Reisespesen.", RequestItemsText_loc3="Ihr seid gereist, ja? Seid Ihr an irgendwelchen interessanten Orten gewesen?" WHERE Id=26394;

UPDATE locales_quest SET OfferRewardText_loc3="Eine Kiste für Goldhain, eh? Seid Ihr schon mal in Goldhain gewesen? Falls ja, ist das kein Problem. Ich habe viele Greifen ausgebildet, damit sie diese Route fliegen können!", RequestItemsText_loc3="Ist das Schweiß auf Eurer Stirn, $Gder Herr:die Dame;? Ihr habt Euch beim Laufen zu sehr verausgabt. Nehmt nächstes Mal einen Greifen!" WHERE Id=26395;

UPDATE locales_quest SET OfferRewardText_loc3="Wunderbar, Ihr habt die Rüstungen gebracht! Wir werden sie sofort unter denen verteilen, die sie brauchen.$B$BVielen Dank, $N. Ihr wart uns wirklich eine große Hilfe. Und jetzt, da Ihr Euch ein wenig mit den Greifen vertraut gemacht habt, hoffe ich, dass Ihr öfter kommt und Goldhain unterstützt!", RequestItemsText_loc3="Ihr seid zurück aus Sturmwind? Hat Osric die Rüstungen geschickt?" WHERE Id=26396;

UPDATE locales_quest SET OfferRewardText_loc3="<Ariok wirft einen Blick in die Kiste.>$B$BGut, gut, gut. Wir können weitermachen. Der Krieg trägt uns nach Osten, weg vom Schwarzfels... vorerst.", RequestItemsText_loc3="Sieht aus, als wärt Ihr mit Gorzeeki gut zurecht gekommen.", CompletedText_loc3="Nachrich für Ariok am Flammensternposten in der Brennenden Steppe." WHERE Id=28425;

UPDATE quest_template SET SourceSpellId=0 WHERE Id=26378;
UPDATE quest_template SET SourceSpellId=0 WHERE Id=28562;

DELETE FROM spell_area WHERE spell=79489 and area=40 and quest_start=0;
DELETE FROM spell_area WHERE spell=79489 and area=40 and quest_start=26378;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(79489, 40, 26378, 26232, 74, 9, 0, 0, 1);

DELETE FROM spell_area WHERE spell=79489 and area=40 and quest_start=28562;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(79489, 40, 28562, 26232, 74, 9, 0, 0, 1);

DELETE FROM spell_area WHERE spell=79489 and area=40 and quest_start=184;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(79489, 40, 184, 26232, 74, 9, 0, 0, 1);

-- console error
delete from creature_addon where guid=87101;

UPDATE locales_quest SET OfferRewardText_loc3="Wir haben nicht viel Verstärkungen in der letzter Zeit gesehen. Wir können jedes Paar Hände gebrauchen", RequestItemsText_loc3="." WHERE Id=28565;


