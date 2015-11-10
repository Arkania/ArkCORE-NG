
update game_event set occurence=525600 where eventEntry=12;

delete from conditions where SourceTypeOrReferenceId=13 and SourceGroup=1 and SourceEntry=71520;
delete from conditions where SourceTypeOrReferenceId=17 and SourceGroup=0 and SourceEntry=71507;
delete from smart_scripts where entryorguid=38289 and source_type=0 and id=0;

