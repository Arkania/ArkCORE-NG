

UPDATE creature_template  SET ScriptName="npc_wounded_brave_45199" WHERE entry=45199;

UPDATE gossip_menu_option SET OptionBroadcastTextID=0, option_id=5, npc_option_npcflag=16 WHERE menu_id=11766 AND id=0;

UPDATE quest_template  SET RequiredNpcOrGo1=44175 WHERE Id=27067;

UPDATE quest_template  SET RequiredNpcOrGo1=44175 WHERE Id=27066;
