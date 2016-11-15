

UPDATE creature_template SET type_flags=2147483680, ScriptName="npc_mechachicken_38224" WHERE entry=38224;

UPDATE creature_template_addon SET auras="71416 95913" WHERE entry=38224;

UPDATE creature SET spawntimesecs=120 WHERE guid=246213;

UPDATE creature_template_addon SET auras="71409 95914" WHERE entry=38227;

delete from creature_loot_template where entry=38227;

DELETE FROM gameobject_loot_template WHERE Entry=201977;
INSERT INTO gameobject_loot_template VALUES 
(201977, 50261, 0, 100, 1, 1, 0, 1, 1, ""); 

delete from creature where guid=249609 and id=38227;

UPDATE creature_template SET ScriptName="npc_the_biggest_egg_ever_spell_visual_38227" WHERE entry=38227;

UPDATE creature SET MovementType=2 WHERE guid=246213;

DELETE FROM creature_addon WHERE guid=246213;
INSERT INTO creature_addon VALUES 
(246213, 246213, 0, 0, 1, 0, "71416 95913");

DELETE FROM waypoint_data WHERE id=246213;
INSERT INTO waypoint_data VALUES 
(246213, 0, 1223.610, 2426.895, 1.347963, 3.876992, 10000, 0, 0, 100, 0),
(246213, 1, 1204.711, 2410.368, 0.680684, 3.904481, 10000, 0, 0, 100, 0),
(246213, 2, 1222.439, 2340.025, 1.553607, 5.369254, 10000, 0, 0, 100, 0),
(246213, 3, 1252.023, 2365.667, 1.174277, 1.037783, 10000, 0, 0, 100, 0),
(246213, 4, 1261.992, 2387.686, 1.194683, 1.155592, 10000, 0, 0, 100, 0);

delete from creature where id=38124 and guid in (245298, 248383, 248385, 248387, 248388);

UPDATE quest_template SET Flags=524288, SpecialFlags=4 WHERE Id=24817;

UPDATE creature_template SET AIName="", ScriptName="npc_assistant_greely_38124" WHERE entry=38124;

delete from smart_scripts where entryorguid=38124;

UPDATE quest_template SET Flags=524288, SpecialFlags=4, RequiredNpcOrGo1=36682, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=1, RequiredNpcOrGoCount2=0 WHERE Id=24817;

UPDATE quest_template SET Flags=524288, SpecialFlags=4, RequiredNpcOrGo1=36683, RequiredNpcOrGoCount1=1, RequiredNpcOrGo2=36682, RequiredNpcOrGoCount2=1  WHERE Id=24817;

UPDATE creature SET spawntimesecs=300 WHERE guid=245373;

UPDATE gossip_menu_option SET OptionBroadcastTextID=2583 WHERE menu_id=11009 AND id=0;

UPDATE quest_template SET NextQuestId=24864, RequiredNpcOrGo1=-202133, RequiredNpcOrGoCount1=10 WHERE Id=24858;

UPDATE gameobject SET phaseIds="180" WHERE guid=168994;

UPDATE creature_template SET ScriptName="npc_megs_dreadshredder_38432" WHERE entry=38432;

UPDATE creature_template SET ScriptName="npc_brett_coins_mcquid_38381" WHERE entry=38381;

update gameobject set phaseIds="180" where id= 202133;

UPDATE gameobject_template SET flags=4, data5=1 WHERE entry=202133;

UPDATE gameobject_template SET ScriptName="go_naga_banner_202133" WHERE entry=202133;





