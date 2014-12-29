
delete from creature_queststarter where id=42497 and quest=26230;
delete from creature_questender where id=42497 and quest=26230;

insert into creature_queststarter value (42497, 26230);
insert into creature_questender value (42497, 26230);

update creature_template set npcflag=3 where entry=42497;

update creature_template set questItem1=57787 where entry=834;

delete from creature_addon where guid=13617;
insert into creature_addon values (13617,0,0,65636,1,431,"79343");

