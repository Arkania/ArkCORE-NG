

update creature_template set InhabitType=4 where entry in (52025, 25161);
delete from smart_scripts where entryorguid in (4845, 5225, 5243, 5253, 5261, 5263, 14445, 44311, 46068, 46424, 46656);

delete from creature_equip_template where entry=1191;


