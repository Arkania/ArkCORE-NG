
-- quest 26543
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Bringt das Fleisch einer monströsen Muschel zu Razgar in Orgrimmar." WHERE Id=26543;

-- quest 26556
UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gute Arbeit, $N. Dank dieser Exemplare werden wir herausfinden, was in der giftigen Suppe dort vorgeht.", RequestItemsText_loc3="Habt Ihr ein paar Exemplare geangelt?", CompletedText_loc3="Liefert die giftigen Pfützenfische bei Razgar in Orgrimmar ab." WHERE Id=26556;

-- quest 13116
UPDATE locales_quest SET EndText_loc3="" WHERE Id=13116;
UPDATE quest_template SET RequiredSourceItemId1=43143, RequiredSourceItemId2=0, RequiredSourceItemCount1=4, RequiredSourceItemCount2=0 WHERE Id=13116;

-- quest 13571
UPDATE quest_template SET PrevQuestId=12645 WHERE Id=13571;

-- quest 12645
UPDATE locales_quest SET EndText_loc3="" WHERE Id=12645;
UPDATE quest_template SET RequiredSourceItemId1=38697, RequiredSourceItemId3=0, RequiredSourceItemCount1=1, RequiredSourceItemCount3=0 WHERE Id=12645;

-- quest 11576
UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Spaltkliffanomalie", QuestGiverTargetName_loc3="Spaltkliffanomalie" WHERE Id=11576;
UPDATE quest_template SET Method=2, Flags=128 WHERE Id=11576;

-- quest 11582
UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Kluftanomalie", QuestGiverTargetName_loc3="Kluftanomalie" WHERE Id=11582;

-- quest 12728
UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Höhlenanomalien", QuestGiverTargetName_loc3="Höhlenanomalien" WHERE Id=12728;

-- quest 24803
UPDATE quest_template SET Flags=8192, SpecialFlags=1 WHERE Id=24803;
UPDATE locales_quest SET OfferRewardText_loc3="Stehen Sie nicht einfach nur da! Gibt mir den Hai und ich werde Euch zum Gewinner erklären!" WHERE Id=24803;

-- quest 24806
UPDATE quest_template SET Flags=8192, SpecialFlags=1 WHERE Id=24806;
UPDATE locales_quest SET OfferRewardText_loc3="Ich fürchte, wir haben für heute schon einen Sieger, $Gjunger:junge; $N. Wenn Ihr jedoch einen Hai bringt, sorge ich dafür, dass er wieder ins Wasser kommt, und dafür habe ich dann vielleicht eine Kleinigkeit für Euch...", RequestItemsText_loc3="" WHERE Id=24806;


