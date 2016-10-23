
delete from creature where guid in (246087, 246047, 246782);

UPDATE `creature` SET `spawndist`=0,`MovementType`=0 WHERE id=35995;

update creature set spawndist=0, MovementType=0 where id=35995;

update creature set spawndist=0, MovementType=0 where id=35896;

update creature set position_x=602.054, position_y=2783.78, position_z=88.7381, orientation=1.35851	where guid=246783;

delete from creature where id=36042;

UPDATE creature SET phaseIds="179" WHERE guid in (246052, 246744);
update creature set phaseIds="179" where id=36463;

delete from pool_template where entry=14542;
insert into pool_template values
(14542, 1, "Gobber, show one of two");

delete from pool_creature where pool_entry=14542;
insert into pool_creature values
(246082, 14542, 50, "Gobber 1"),
(247588, 14542, 50, "Gobber 2");

UPDATE creature SET phaseIds="170" WHERE guid in (246091, 246092);

UPDATE `gameobject` SET phaseids="170 171 172 179" WHERE `guid` in (168791, 168793, 168794, 168875);



