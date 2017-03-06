
update gossip_menu_option set OptionBroadcastTextID=42071,option_icon=2,option_id=4,npc_option_npcflag=8192 where menu_id=4360 and id=1;

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=4360 and SourceEntry=1 and ConditionTypeOrReference=9 and ConditionValue1=26131;
insert into conditions value
(15,4360,1,0,0,9,0,26131,0,0,0,0,0,"","Gossip option requires quest taken but not complete");

UPDATE quest_template SET RequiredNpcOrGo1=1960, RequiredNpcOrGoCount1=1,ObjectiveText1="Speak to Pilot Hammerfoot" WHERE Id=26131;

update creature_template set AIName="",ScriptName="npc_pilot_hammerfoot" where entry=1960;

