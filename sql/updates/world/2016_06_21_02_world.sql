
UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=29608;

UPDATE gossip_menu_option SET OptionBroadcastTextID=53141 WHERE menu_id=13046 AND id=0;

UPDATE npc_text SET BroadcastTextID0=53142 WHERE ID=18321;

UPDATE creature_template SET gossip_menu_id=13046 WHERE entry=26879;

delete from smart_scripts where entryorguid=26879;

UPDATE creature_template SET AIName="", ScriptName="npc_tomas_riverwell_26879" WHERE entry=26879;

UPDATE creature_template SET gossip_menu_id=13045, AIName="", ScriptName="npc_pricilla_winterwind_23736" WHERE entry=23736;

DELETE FROM gossip_menu WHERE entry=13045 and text_id=18320;
INSERT INTO gossip_menu VALUES (13045, 18320);

UPDATE npc_text SET BroadcastTextID0=53140 WHERE ID=18320;

UPDATE gossip_menu_option SET OptionBroadcastTextID=53141 WHERE menu_id=13045 AND id=0;

delete from smart_scripts where entryorguid=23736;

delete from gameobject_template where entry=187894;
INSERT INTO `gameobject_template` VALUES 
(187894, 8, 0, 'Borean Crossroads Spell Focus', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 1498, 20, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 1);

UPDATE gossip_menu_option SET option_id=4, npc_option_npcflag=8192 WHERE menu_id=13046 AND id=0;

UPDATE gossip_menu_option SET option_id=4, npc_option_npcflag=8192 WHERE menu_id=13045 AND id=0;



