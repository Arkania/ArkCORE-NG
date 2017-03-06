
update creature set phaseGroups='379' where id=48806;

delete from creature where guid=249027 and id=36613;

DELETE FROM creature_queststarter WHERE quest IN(14153,14113) AND id=34668;
DELETE FROM creature_queststarter WHERE quest IN(14153,14113) AND id=35175;

update quest_template set prevQuestId=14070 where id in(26711,26712);
update quest_template set prevQuestId=26712 where id =14113;
update quest_template set prevQuestId=26711 where id =14153;

UPDATE quest_template SET RequiredGender=1 WHERE Id in (14109, 14113, 26712);
UPDATE quest_template SET RequiredGender=0 WHERE Id in (14110, 14153, 26711);

update gossip_menu_option set option_id=1,npc_option_npcflag=1  where menu_id in(10620,10622,10624);

DELETE FROM `npc_vendor` WHERE `entry`IN(35126,35128,35130);
update `creature_template` set `npcflag`=1,`AIName`='SmartAI' where `entry` IN(35126,35128,35130);

-- SAI for quest The New You, https://cata-twinhead.twinstar.cz/?quest=14109
delete from smart_scripts where entryorguid=35126 and event_type=62 and event_param1=10620;
delete from smart_scripts where entryorguid=35128 and event_type=62 and event_param1=10622;
delete from smart_scripts where entryorguid=35130 and event_type=62 and event_param1=10624;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(35126,0,0,0,62,0,100,0,10620,0,0,0,85,66780,0,0,0,0,0,7,0,0,0,0,0,0,0,'Gappy - on gossip - create bling.'),
(35128,0,0,0,62,0,100,0,10622,0,0,0,85,66781,0,0,0,0,0,7,0,0,0,0,0,0,0,'Szabo-on gossip-cross cast create hip new outfit'),
(35130,0,0,0,62,0,100,0,10624,0,0,0,85,66782,0,0,0,0,0,7,0,0,0,0,0,0,0,'Speckles - on gossip - create shades.');

UPDATE gameobject_template SET ScriptName="go_disco_ball_201591" WHERE entry=201591;

UPDATE creature_template SET AIName="", ScriptName="npc_tunneling_worm_34865" WHERE entry=34865;

delete from smart_scripts where entryorguid=34865;

delete from smart_scripts where entryorguid=34957;

delete from smart_scripts where entryorguid=34958;

delete from smart_scripts where entryorguid=34959;

UPDATE creature_template SET ScriptName="npc_warrior_matic_nx__34697" WHERE entry=34697;

update creature_template set gossip_menu_id=10685 where entry=34692;


