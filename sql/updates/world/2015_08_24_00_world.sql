
-- delete non blizzlike 
delete from creature_template where entry=3432314;
delete from creature_template where entry=987655;
delete from creature_template where entry=190001;

delete from creature where id=987655;
delete from creature where id=100000;
update creature set id=54473 where id=190001;

delete from creature_addon where guid in (237877,239014, 239015, 239016);

delete from smart_scripts where entryorguid in (45375, 47135, 47138, 47140, 24656);

