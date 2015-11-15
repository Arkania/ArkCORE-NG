
-- quest=905
UPDATE locales_quest SET EndText_loc3="", ObjectiveText2_loc3="Besucht das gelbe Raptornest", ObjectiveText3_loc3="Besucht das blaue Raptornest", ObjectiveText4_loc3="" WHERE Id=905;

UPDATE quest_template SET RequiredNpcOrGo1=34962, RequiredNpcOrGo2=34963, RequiredNpcOrGo3=34964, RequiredNpcOrGo4=0, RequiredNpcOrGoCount1=1, RequiredNpcOrGoCount4=0, ObjectiveText4="" WHERE Id=905;

UPDATE `creature_template` SET `AIName`='', ScriptName="" WHERE `entry` IN(34962,34963,34964);

update gameobject_template set AIName="", ScriptName="go_red_raptor_nest_6906" where entry=6906;
update gameobject_template set AIName="", ScriptName="go_blue_raptor_nest_6907" where entry=6907;
update gameobject_template set AIName="", ScriptName="go_yellow_raptor_nest_6908" where entry=6908;
 
delete from creature where guid in (116853, 116854, 116855);
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (34962,34963,34964);
delete from conditions where SourceTypeOrReferenceId=13 and SourceGroup=2 and SourceEntry=5316 and ConditionValue2 in (34962, 34963, 34964);
 
