
-- quest 28084

UPDATE quest_template SET Method=2, PrevQuestId=26004, Flags=65536 WHERE Id=28084;

UPDATE locales_quest SET Title_loc3="Die Macht der Krom'gar", OfferRewardText_loc3="Ihr habt jetzt Zugang zum Vorratslager der Krom'gar, $N! Für ein geringes Entgeld verkaufe ich Euch Kampfausrüstung, die Euch beim Vernichten Eurer Feinde dienlich sein wird! Es hängt von Eurem Rang in der Armee ab, welche Waren ich Euch verkaufen kann. Besucht mein Geschäft, wann immer Ihr einen neuen Rang erhaltet.$B$BLOK'TAR OGAR!" WHERE Id=28084;

-- quest 26059

UPDATE quest_template SET PrevQuestId=26058 WHERE Id=26059;

UPDATE locales_quest SET OfferRewardText_loc3="Wie ich sehe, schickt Krom'gar den Besten!$B$BGut, wir haben viel zu tun. Die dreckige Allianz hat ein Abkommen mit den Grimmtotem unterzeichnet. Jetzt müssen wir die Angriffe beider Streitkräfte abwehren.$B$BWir haben nicht genügend Soldaten im Hochwipfeltal und können es nicht mehr lange gegen die konzentrierten Angriffe unserer Feinde verteidigen. Wir haben nur noch eine Hoffnung: VOODOO!" WHERE Id=26059;

-- 26060

UPDATE quest_template SET PrevQuestId=26059 WHERE Id=26060;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Hervorragend. Sobald ich die Zutaten habe, werde ich sie vermischen und den Voodoo entfesseln! Gnade unseren Feinden!", RequestItemsText_loc3="Ich brauche das Klippenstürmerherz.", CompletedText_loc3="Kehrt zu Hexendoktor Jin'Zil in Malaka'jin im Steinkrallengebirge zurück." WHERE Id=26060;

-- 26061

UPDATE quest_template SET PrevQuestId=26059 WHERE Id=26061;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Hervorragend. Sobald ich die Zutaten habe, werde ich sie vermischen und den Voodoo entfesseln! Gnade unseren Feinden!", RequestItemsText_loc3="Ich brauche Widderhörner des Steinkrallengebirges!", CompletedText_loc3="Kehrt zu Hexendoktor Jin'Zil in Malaka'jin im Steinkrallengebirge zurück." WHERE Id=26061;

-- 26064

UPDATE quest_template SET PrevQuestId=26059 WHERE Id=26064;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Danke, $N. Diese Eier reichen für eine Woche.", RequestItemsText_loc3="Ich brauche Eier!", CompletedText_loc3="Kehrt zu Denni'ka in Malaka'jin im Steinkrallengebirge zurück." WHERE Id=26064;

-- 26010

UPDATE quest_template SET PrevQuestId=26004 WHERE Id=26010;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Lok'tar! Allianzschweine!$B$B<Oberanführer Krom'gar spuckt auf den Boden.>$B$BGenießt Euren Sieg, er wird nicht lange währen. Euer Mut hat uns Zeit verschafft, aber mehr nicht.", CompletedText_loc3="Kehrt zu Oberanführer Krom'gar in der Feste Krom'gar im Steinkrallengebirge zurück.", QuestGiverTextWindow_loc3="Zelt der Nordwacht", QuestGiverTargetName_loc3="Zelt der Nordwacht" WHERE Id=26010;

-- 26086

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht. Jetzt, da sie ausgeschaltet wurden, habe ich keine Ausreden mehr.$B$BBald muss ich mich Thassarian im Kampf stellen, für Ehre und für Andorhal.", CompletedText_loc3="Kehrt zurück zu Koltira Todesweber in Andorhal in den Westlichen Pestländern.", QuestGiverTextWindow_loc3="Truppenkommandant von Andorhal", QuestGiverTargetName_loc3="Truppenkommandant von Andorhal" WHERE Id=27086;

-- 27199

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Thassarian in Andorhal in den Westlichen Pestländern zurück.", QuestGiverTextWindow_loc3="Kriegshauptmann der Todeswache", QuestGiverTargetName_loc3="Kriegshauptmann der Todeswache" WHERE Id=27199;

-- 26020

UPDATE locales_quest SET OfferRewardText_loc3="Ausreichend motiviert? Was... was soll das heißen? Hört mal zu, Unteroffizier, ich habe einen eingebauten Überlebensmechanismus namens Eigeninteresse. Das heißt, es ist in meinem eigenen Interesse, NICHT ZU STERBEN. Allerdings kann ich die Kanonen nicht ohne die richtigen Materialien reparieren." WHERE Id=26020;

-- 26044

UPDATE locales_quest SET OfferRewardText_loc3="Äh... Na ja, das ist ganz einfach... IN DIESER HÖHLE WIMMELT ES VON SEELENLOSEN MORDMASCHINEN!" WHERE Id=26044;

-- 26045

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ich fasse es nicht! Ihr habt die Teile bekommen und seid nicht gestorben. Wieso seid Ihr nur Unteroffizier?", RequestItemsText_loc3="Wie läuft die Jagd?", CompletedText_loc3="Kehrt zu Unteroffizier Dontrag in den Ausufernden Tiefen im Steinkrallengebirge zurück." WHERE Id=26045;

-- 26011

UPDATE quest_template SET PrevQuestId=26010 WHERE Id=26011;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Habt Ihr verdächtige Dokumente in Paltrows Lager gefunden? Vielleicht an seiner verwesenden Leiche? Jeder Hinweis auf die Angriffsmuster der Allianz wären bei der Schlacht ums Steinkrallengebirge von Vorteil.", CompletedText_loc3="Kehrt zu Herrin der Spione Anara in der Feste Krom'gar im Steinkrallengebirge zurück.", QuestGiverTextWindow_loc3="Marschall Paltrow", QuestGiverTargetName_loc3="Marschall Paltrow" WHERE Id=26011;

-- 26026

UPDATE quest_template SET PrevQuestId=26011 WHERE Id=26026;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="<Clarissa klatscht aufgeregt.>$B$BHerr Rosie, dir geht es gleich wieder gut! Hurra!$B$B<Clarissa setzt die Teile, die Ihr gefunden habt, routiniert in 'Rosie' ein.>$B$BOh, Herr Rosie! Ich wusste es!", RequestItemsText_loc3="Herr Rosie ist so traurig. Wir müssen ihn wieder fröhlich machen!", CompletedText_loc3="Kehrt zu Clarissa in der Feste Krom'gar im Steinkrallengebirge zurück" WHERE Id=26026;

-- 26043

UPDATE quest_template SET PrevQuestId=26026 WHERE Id=26043;

UPDATE locales_quest SET OfferRewardText_loc3="Ein Beweis für die Macht der Horde!", RequestItemsText_loc3="Was wünscht Ihr?", CompletedText_loc3="Gebt Felskiefers riesigen Zahn bei der Herrin der Spione Anara ab." WHERE Id=26043;









