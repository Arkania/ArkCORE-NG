
UPDATE quest_template SET RequiredNpcOrGo1=38989, RequiredNpcOrGoCount1=1, ObjectiveText1="Speak to Jornun." WHERE Id=25035;
UPDATE quest_template SET RequiredNpcOrGo2=38442, RequiredNpcOrGoCount2=1, ObjectiveText2="Seek out Morakki." WHERE Id=25035;

update creature_template set gossip_menu_id=11131, npcflag=3, AIName="", ScriptName="npc_jornun_38989" where entry=38989;
update gossip_menu_option set OptionBroadcastTextID=38979 where menu_id=11131 and id=0;

update creature_template set AIName="", ScriptName="npc_morakki_38442" where entry=38442;

