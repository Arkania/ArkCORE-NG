
delete from creature_queststarter where id=13018 and quest=6662;

update quest_template set PrevQuestId=6661 where Id=6662;
update quest_template set RequiredNpcOrGo1=13017,RequiredNpcOrGoCount1=5 where Id=6661;



