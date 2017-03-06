
UPDATE creature_template SET ScriptName="npc_bruno_flameretardant_34835" WHERE entry=34835;

UPDATE creature_template SET AIName="", ScriptName="npc_frankie_gearslipper_34876" WHERE entry=34876;

UPDATE creature_template SET AIName="", ScriptName="npc_jack_the_hammer_34877" WHERE entry=34877;

UPDATE creature_template SET AIName="", ScriptName="npc_sudsy_magee_34878" WHERE entry=34878;

delete from smart_scripts where entryorguid in (34876, 34877, 34878);

UPDATE creature_template SET gossip_menu_id=11360, faction=2204, npcflag=1, unit_flags=32776, unit_flags2=33556480 WHERE entry=34959;

UPDATE creature_template SET gossip_menu_id=10633, faction=2204, npcflag=1, unit_flags=32776, unit_flags2=33622016 WHERE entry=34958;

UPDATE creature_template SET gossip_menu_id=11358, faction=2204, npcflag=1, unit_flags=32776, unit_flags2=33556480 WHERE entry=34957;

delete from gossip_menu where entry = 10633;
insert into gossip_menu values 
(10633, 14726);

delete from npc_text where id=14726;
insert into npc_text (ID, text0_0, BroadcastTextID0) values
(14726, "<You can't quite make out what Gobber is saying with all of the food that is stuffed in his mouth. You're pretty sure that it's a thanks, however.>", 35468);

delete from creature_queststarter where id in (34957, 34958, 34959);

update arkcore_string set content_default="Selected object:\n|cffffffff|Hgameobject:%d|h[%s]|h|r GUID: %u ID: %u\nX: %f Y: %f Z: %f MapId: %u\nOrientation: %f\nPhaseIds %s" where entry=524;

update arkcore_string set content_loc3="Ausgewähltes Objekt:\n|cffffffff|Hgameobject:%d|h[%s]|h|r GUID: %u ID: %u\nX: %f Y: %f Z: %f MapId: %u\nOrientierung: %f\nPhaseIDs %s" where entry=524;

update creature set spawntimesecs=120 where id in (34835, 34876, 34877, 34878);


