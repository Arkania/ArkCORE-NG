
-- helloween is now done by core script..
delete from conditions where SourceTypeOrReferenceId=15 and ConditionValue1=24755 and SourceGroup in (7497, 7301, 347, 7855, 6059, 7324, 7856, 9614, 9112, 7869, 7857);

delete from item_loot_template where entry=34863 and item=34109;
insert into item_loot_template values
(34863, 34109, 1, 1, 0, 1, 1);

-- no worldstate has value 24755
DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=7468 AND SourceEntry=0 AND ConditionTypeOrReference=11 AND ConditionValue1=24755;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=6525 AND SourceEntry=0 AND ConditionTypeOrReference=11 AND ConditionValue1=24755;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=2890 AND SourceEntry=0 AND ConditionTypeOrReference=11 AND ConditionValue1=24755;

-- no ErrorTextId if ErrorType=0
UPDATE conditions SET ErrorTextId=0 WHERE SourceTypeOrReferenceId=17 AND SourceEntry = 65728 AND ConditionTypeOrReference=27 AND ErrorType=0 AND ErrorTextId=66; 
UPDATE conditions SET ErrorTextId=0 WHERE SourceTypeOrReferenceId=17 AND SourceEntry = 65729 AND ConditionTypeOrReference=27 AND ErrorType=0 AND ErrorTextId=66; 
UPDATE conditions SET ErrorTextId=0 WHERE SourceTypeOrReferenceId=17 AND SourceEntry = 54732 AND ConditionTypeOrReference=25 AND ErrorType=0 AND ErrorTextId=77; 

-- console error
update quest_template set Method=0 where Id in (8002, 7922, 8293, 7521, 7923, 7924, 7925, 8568, 8296, 9459, 9482);


