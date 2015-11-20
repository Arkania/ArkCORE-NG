
update creature set spawndist=0, MovementType=0 where id=3389;
delete from smart_scripts where entryorguid=3389;
update creature_template set AIName="" where entry=3389;

delete from creature_text where entry=3389 and groupid=2;
update creature_text set BroadcastTextID=4926 where entry=3389 and groupid=0 and id=0;

update gossip_menu_option set OptionBroadcastTextID=4793 where menu_id=23615 and id=0;

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=23615 and SourceEntry=0 and ConditionTypeOrReference=9 and ConditionValue1=4021;
insert into conditions value
(15, 23615, 0, 0, 0, 9, 0, 4021, 0, 0, 0, 0, 0, "", "");

UPDATE quest_template SET PrevQuestId=852 WHERE Id=4021;

delete from creature where id in (34715, 34718, 34719, 34721) and map=1;
delete from creature where guid in (278001, 278003, 278004, 278005);

delete from creature where id=3475;

UPDATE quest_template SET RequiredSourceItemId1=10327, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount4=0 WHERE Id=881;

delete from spell_script_names where spell_id=12189;
insert into spell_script_names values
(12189, "spell_summon_echeyakee");

update npc_text set BroadcasttextID0=51307 where ID=17960;

UPDATE locales_quest SET CompletedText_loc3="Bringt Helbrims Forschungsergebnisse zu Sashya in Ratschet im Nördlichen Brachland." WHERE Id=13999;

delete from gameobject where guid=10;
insert into gameobject values
(10, 164651, 1, 1, 1, -14.7305, -2378.33, 91.6835, 0.0126479, 0, 0, 0.00632389, 0.99998, 300, 0, 1);



