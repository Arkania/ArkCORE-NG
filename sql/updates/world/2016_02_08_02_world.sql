
update conditions set ConditionTypeOrReference=8 where SourceTypeOrReferenceId=15 and SourceGroup=7938 and SourceEntry=0 and SourceId=0;
update conditions set ConditionTypeOrReference=9 where SourceTypeOrReferenceId=15 and SourceGroup=7938 and SourceEntry=1 and SourceId=0;

DELETE FROM creature_addon WHERE guid=39481;

delete from conditions where SourceTypeOrReferenceId=13 and SourceGroup=0 and SourceEntry=89557;
delete from conditions where SourceTypeOrReferenceId=13 and SourceGroup=0 and SourceEntry=89089;

delete from quest_poi where questId=31013 and id=0 and objIndex=0;
delete from quest_poi where questId=32249 and id=0 and objIndex=-1;

