
-- next part in sen'jin
UPDATE creature_template SET InhabitType=3 WHERE entry=40416;

UPDATE quest_template SET Method=2, PrevQuestId=8312, Flags=0, SpecialFlags=0 WHERE Id in (8354, 8358, 8359, 8360);

UPDATE quest_template SET Method=2, PrevQuestId=8311, Flags=0, SpecialFlags=0 WHERE Id in (8353, 8355, 8356, 8357);

UPDATE locales_quest SET OfferRewardText_loc3="Willkommen, junger $R. Ihr kommt mit glühenden Empfehlungen, Mann. Es ist gut, Euch endlich in Person zu treffen." WHERE Id=25073;


