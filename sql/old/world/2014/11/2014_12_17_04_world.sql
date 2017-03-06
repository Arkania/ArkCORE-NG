
update quest_template set Method=2, SpecialFlags=0,Flags=0,RequiredRaces=2098253,CompletedText="" where Id=26394;
delete from creature_queststarter where id=1323 and quest=26394; 
