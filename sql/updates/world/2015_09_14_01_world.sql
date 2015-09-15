
update playercreateinfo set map=654 where race=22 and zone =4714;

delete from phase_definitions where zoneId=4755;
insert into phase_definitions values
(4755, 0, 1, 0, 638, 0, "Gilneas player startposition"),
(4755, 1, 2, 0, 638, 1, "Gilneas phase 2"),
(4755, 2, 4, 0, 638, 0, "Gilneas phase 4"); 
-- (4755, 3, 8, 0, 638, 0, "Gilneas phase 8"), -- prepared
-- (4755, 4, 10, 0, 638, 0, "Gilneas phase 10"),
-- (4755, 5, 1024, 0, 638, 0, "Gilneas phase 1024");

delete from conditions where SourceTypeOrReferenceId=25 and SourceGroup=4755 and SourceEntry in (0,1,2,3,4,5);
insert into conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition, ScriptName, comment) values
(25, 4755, 0, 14, 14091, 0, "", "let phase 1 until quest 14091 taken"),
(25, 4755, 1, 8, 14091, 0, "", "start phase 2 when quest 14091 taken"),
(25, 4755, 2, 8, 14159, 0, "", "start phase 4 when quest 14159 taken");
-- (25, 4755, 2, 8, 14221, 0, "", "Activate Gilneas Phase 4 on Never Surrender, Sometimes Retreat quest completion"),  prepared..


-- 8 QUESTREWARDED 
-- 9 QUESTTAKEN 
-- 14 QUEST_NONE
