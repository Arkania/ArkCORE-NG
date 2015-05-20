
delete from creature_queststarter where id=38300 and quest=24812;

update creature_template set faction=126, npcflag=3, baseattacktime=2000 where entry=52980;

delete from creature_queststarter where id=52980;
insert into creature_queststarter values
(52980, 29221),
(52980, 29223);

delete from creature_questender where id=52980;
insert into creature_questender values
(52980, 29220),
(52980, 29221);

delete from creature_queststarter where id=19253 and quest=9407;
