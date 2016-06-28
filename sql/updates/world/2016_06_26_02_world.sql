
-- quest 10047
UPDATE quest_template SET RequiredNpcOrGo1=-182789, RequiredNpcOrGoCount1=8, RequiredItemId1=25889, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=10047;

-- quest 10919
UPDATE quest_template SET Method=2 WHERE Id=10919;

UPDATE locales_quest SET Objectives_loc3="Folgt Fei Fei.... " WHERE Id=10919;

UPDATE quest_template SET Method=2, Objectives="Follow Fei Fei....", OfferRewardText="<Fei Fei barks happily and grabs the doggy treat.  He looks left and right... deciding where he should hide this new treasure...>", RequestItemsText="Fei Fei looks at you expectantly..." WHERE Id=10919;

delete from creature_queststarter where quest=9492;

delete from creature_questender where quest=9492;

UPDATE locales_quest SET Title_loc3="Die Eroberung der Zitadelle", Objectives_loc3="Sprecht mit Vorhutsspäher Chadwick im Höllenfeuerbollwerk.", Details_loc3="Die Legion steht auf der einen, die Höllenorcs auf der anderen Seite. Sie werden die Ehrenfeste in Kürze überrennen, wenn wir nichts unternehmen.$B$BMacht Euch auf nach Westen zum Höllenfeuerbollwerk und sprecht dort mit Vorhutsspäher Chadwick. Die Mission, die er leitet, wird der Allianz den Weg in die Zitadelle ebnen.", OfferRewardText_loc3="Altumus ist wirklich ein Juwel. Aber wir werden hier nur lebend herauskommen, wenn wir im Bollwerk siegreich sind." WHERE Id=29543;

UPDATE locales_quest SET Title_loc3="Die Eroberung der Zitadelle", Objectives_loc3="Sprecht mit Steingardist Stok'ton im Höllenfeuerbollwerk.", Details_loc3="Die Legion steht auf der einen, die Höllenorcs auf der anderen Seite. Sie werden Thrallmar überrennen, wenn wir nichts unternehmen.$B$BMacht Euch auf den Weg nach Westen zum Höllenfeuerbollwerk und sprecht mit Steingardist Stok'ton. Die Geheimmission, die er leitet, wird der Horde den Weg in die Zitadelle ebnen.", OfferRewardText_loc3="Schädelbrecher ist nicht gerade freundlich, aber er weiß, was er tut. Und für Euch gibt es auch genug Arbeit." WHERE Id=29542;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10142;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=10442;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=10443;

UPDATE creature_template SET dmg_multiplier=1 WHERE entry=20599;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10351;

UPDATE quest_template SET Method=2, PrevQuestId=10349, RequiredItemId1=29478, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=10351;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10159;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=12993;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Tobender Koloss", QuestGiverTargetName_loc3="Tobender Koloss" WHERE Id=10132;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=9372;

UPDATE quest_template SET PrevQuestId=10442 WHERE Id=9372;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Stachelklauenfelshetzer", QuestGiverTargetName_loc3="Stachelklauenfelshetzer" WHERE Id=9385;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=9417;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Bulliger Hölleneber", QuestGiverTargetName_loc3="Bulliger Hölleneber" WHERE Id=10255;

UPDATE locales_quest SET EndText_loc3="auf der Höllenfeuerhalbinsel zurück.", QuestGiverTextWindow_loc3="Aggonis", QuestGiverTargetName_loc3="Aggonis" WHERE Id=9427;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=9383;

delete from creature where guid=10762;
INSERT INTO `creature` VALUES (10762, 17000, 530, 1, 1, 0, 0, 428.704, 3438.84, 62.325, 2.43781, 300, 0, 0, 8844, 2620, 0, 0, 0, 0);

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Orc der Knochenmalmer", QuestGiverTargetName_loc3="Orc der Knochenmalmer" WHERE Id=10482;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10050;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10055;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10483;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10078;

UPDATE quest_template SET Method=2 WHERE Id=10078;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Plündernde Krustenbohrer", QuestGiverTargetName_loc3="Plündernde Krustenbohrer" WHERE Id=9355;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Pioniere der Gan'arg", QuestGiverTargetName_loc3="Pioniere der Gan'arg" WHERE Id=10079;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Pioniere der Gan'arg", QuestGiverTargetName_loc3="Pioniere der Gan'arg" WHERE Id=10214;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10143;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10792;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10895;

UPDATE quest_template SET Method=2, Flags=0 WHERE Id=10895;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10146;

UPDATE quest_template SET Method=2, Flags=0 WHERE Id=10146;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10099;

UPDATE quest_template SET Flags=136 WHERE Id=10100;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10057;

update creature_loot_template set chance=75 where item=30157 and entry in (16871, 16873, 16907, 19422, 19424, 19442, 19457);

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10485;

UPDATE locales_quest SET Title_loc3="Krieg im Bollwerk", Objectives_loc3="Tötet Wachhabenden Gargolmar, Vazruden den Herold und Vazrudens Drachen Nazan. Bringt Gargolmars Hand und Nazans Kopf zu Vorhutsspäher Chadwick.", Details_loc3="Die Verteidigung der Höllenfeuerzitadelle hängt in erster Linie vom Bollwerk ab, das als eine Art Frühwarnsystem dient.$B$BBeseitigt Wachhabenden Gargolmar und Vazruden den Herold. Ohne sie wird die Eroberung des Bollwerks ein Kinderspiel sein.", OfferRewardText_loc3="Ich wusste, dass ich auf Euch zählen kann!$B$BIhre Streitkräfte sind nun führerlos. Die Invasion kann beginnen.", RequestItemsText_loc3="Wart Ihr erfolgreich? Von dieser Mission hängt sehr viel ab, $N.", CompletedText_loc3="Kehrt zu Vorhutsspäher Chadwick im Höllenfeuerbollwerk zurück.", QuestGiverTextWindow_loc3="Vorsichtige Annäherung.", QuestGiverTargetName_loc3="Nazan" WHERE Id=29528;

UPDATE quest_template SET Flags=136, RequiredRaces=2098253 WHERE Id=29528;

UPDATE locales_quest SET OfferRewardText_loc3="Sehr gut! Langfristig wird dieser Angriff weit schwerwiegendere Konsequenzen haben als der Tod von ein paar Orcs.", RequestItemsText_loc3="Wie viele Vorräte konntet Ihr mitnehmen?" WHERE Id=29594;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=29594;

UPDATE locales_quest SET Title_loc3="Dämonen in der Zitadelle", Objectives_loc3="Tötet Omor den Narbenlosen und bringt seinen Huf zu Vorhutsspäher Chadwick.", Details_loc3="Einer unserer Späher berichtet, er habe irgendwo im Bollwerk einen Agenten der Brennenden Legion gesehen. Wenn das stimmt, laufen wir Gefahr, dass die Ehrenfeste von zwei Seiten angegriffen wird!$B$BWenn Ihr diesen Teufel findet, dann bringt ihn um.", OfferRewardText_loc3="Dann ist es also wahr. Die Höllenorcs und die Brennende Legion arbeiten auf irgendeine Weise zusammen.", RequestItemsText_loc3="Habt Ihr dort drinnen Dämonen entdeckt?", CompletedText_loc3="Kehrt zu Vorhutsspäher Chadwick im Höllenfeuerbollwerk zurück." WHERE Id=29529;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=29529;

update creature_loot_template set chance=100 where entry=17308 and item=23886;

update creature_loot_template set chance=100 where entry=17306 and item=23881;

update gameobject_template set data1=209348 where entry=209348;

delete from gameobject_loot_template where entry in (209347, 209348) and item=72160;
INSERT INTO `gameobject_loot_template` VALUES (209348, 72160, 0, 100, 1, 1, 0, 1, 1, NULL);
INSERT INTO `gameobject_loot_template` VALUES (209347, 72160, 0, 100, 1, 1, 0, 1, 1, '');

delete from creature_loot_template where entry=17306 and item=23886;
INSERT INTO `creature_loot_template` VALUES (17306, 23886, 0, 100, 1, 1, 0, 1, 1, '');



