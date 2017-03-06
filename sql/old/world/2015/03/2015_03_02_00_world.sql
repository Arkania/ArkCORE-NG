
update quest_template set NextQuestIdChain=25126 where Id=25152;
update quest_template set NextQuestIdChain=0 where Id=25126;
update quest_template set NextQuestIdChain=0, PrevQuestId=25126 where Id=25172;

update quest_template set PrevQuestId=25127, NextQuestIdChain=25147 where Id=2383;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25139 where Id=3087;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25141 where Id=3088;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25143 where Id=3089;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25145 where Id=3090;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25129 where Id=25128;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25132 where Id=25131;
update quest_template set PrevQuestId=25127, NextQuestIdChain=25149 where Id=25138;

update quest_template set PrevQuestId=25128, NextQuestIdChain=25130 where Id=25129;
update quest_template set PrevQuestId=25131 where Id=25132;

