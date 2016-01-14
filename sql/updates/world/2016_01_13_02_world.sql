
delete from item_loot_template where entry=35348 and item=34109;
insert into item_loot_template values
(35348, 34109, 1, 1, 0, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId = 15 AND SourceGroup=9123 AND SourceEntry=0 AND ConditionTypeOrReference=1 AND ConditionValue1=24755; 
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 1 AND SourceGroup=31673 AND SourceEntry=43228 AND ConditionTypeOrReference=1 AND ConditionValue1=57940; 
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 15 AND SourceGroup=21215 AND SourceEntry=0 AND ConditionTypeOrReference=23 AND ConditionValue1=1638; 
DELETE FROM conditions WHERE SourceTypeOrReferenceId = 15 AND SourceGroup=21215 AND SourceEntry=0 AND ConditionTypeOrReference=1 AND ConditionValue1=24755; 
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceGroup=0 AND SourceEntry=78838 AND ConditionTypeOrReference=18 AND ConditionValue2=42235; 
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceGroup=0 AND SourceEntry=78838 AND ConditionTypeOrReference=18 AND ConditionValue1=1;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceGroup=1 AND SourceEntry=52867 AND ConditionTypeOrReference=31 AND ConditionValue1=3;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceGroup=0 AND SourceEntry=80208 AND ConditionTypeOrReference=18 AND ConditionValue1=1;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=13 AND SourceGroup=0 AND SourceEntry=88646 AND ConditionTypeOrReference=31 AND ConditionValue1=5;
DELETE FROM conditions WHERE SourceTypeOrReferenceId=18 AND SourceGroup=0 AND SourceEntry=33278 AND ConditionTypeOrReference=24 AND ConditionValue1=1;

delete from spell_script_names where ScriptName="spell_dru_empowered_touch" and spell_id in (5185, 8936, 50464);
insert into spell_script_names values 
(5185, "spell_dru_empowered_touch"),
(8936, "spell_dru_empowered_touch"),
(50464, "spell_dru_empowered_touch");

delete from spell_script_names where ScriptName="spell_bloodlust" and spell_id=2825;
insert into spell_script_names values 
(2825, "spell_bloodlust");

delete from spell_script_names where ScriptName="spell_heroism" and spell_id=32182;
insert into spell_script_names values 
(32182, "spell_heroism");

delete from spell_script_names where ScriptName="spell_time_warp" and spell_id=80353;
insert into spell_script_names values 
(80353, "spell_time_warp");

delete from spell_script_names where ScriptName="spell_ancient_hysteria" and spell_id=90355;
insert into spell_script_names values 
(90355, "spell_ancient_hysteria");




