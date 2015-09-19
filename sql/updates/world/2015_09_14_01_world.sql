
update playercreateinfo set map=654 where race=22 and zone =4714;

delete from phase_definitions where zoneId=4755;
insert into phase_definitions values
(4755, 0, 1, 0, 638, 1, "Gilneas player startposition"),
(4755, 1, 2, 0, 638, 1, "Gilneas phase 2"),
(4755, 2, 4, 0, 638, 0, "Gilneas phase 4"),
(4755, 3, 8, 0, 638, 1, "Gilneas phase 8");
-- (4755, 4, 10, 0, 638, 0, "Gilneas phase 10"),
-- (4755, 5, 1024, 0, 638, 0, "Gilneas phase 1024");

delete from conditions where SourceTypeOrReferenceId=25 and SourceGroup=4755;

