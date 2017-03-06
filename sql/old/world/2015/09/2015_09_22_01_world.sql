
UPDATE creature_template SET unit_flags=33024 WHERE entry=34916;

update creature set phaseMask=2 where id in (35839, 35872, 35874, 35869, 35871, 35870, 35873);

delete from creature where guid=278400;
delete from creature where id=38853;
insert into creature values 
(278398, 38853, 654, 1, 1, 30289, 0, -1670.77, 2530.31, 97.4407, 4.38078, 300, 0, 0, 285,   690, 0, 0, 0, 0),
(278399, 38853, 654, 1, 2, 30289, 0, -1634.89, 1301.66, 19.6629, 2.32874, 300, 0, 0, 285, 16506, 0, 0, 0, 0),
(253413, 38853, 654, 1, 2, 30289, 0, -2228.94, 1809.93, 11.9376, 6.26355, 500, 0, 0, 306,     0, 0, 0, 0, 0),
(278400, 35118, 654, 1, 2,     0, 0, -1671.38, 1397.05, 52.2869, 3.83672, 300, 0, 0,  55,     0, 0, 0, 0, 0);

update creature set phaseMask=2 where id in (35118, 35112, 35115, 50371, 35081, 35077, 35123, 35124);

delete from creature where guid in (250215, 250197, 250198, 250278, 250279, 250280, 250281);
delete from creature where guid in (250751, 250752, 250754, 250755, 250756, 250764, 250765, 250766, 250767, 250768);

update creature_template_addon set bytes1=1 where entry=38853;

update creature set MovementType=1, spawndist=4 where guid in (251349, 251352, 251364, 251365, 251369, 251370, 251371);
update creature set MovementType=1, spawndist=4 where guid in (251373, 2513768, 251380, 251383, 251386, 251387, 251416);

update creature_template set AIName="", ScriptName="" where entry in (35840);

update gossip_menu_option set OptionBroadcastTextID=8097, option_id=3, npc_option_npcflag=128 where menu_id=10841;

UPDATE quest_template SET PrevQuestId=14276 WHERE Id=14290;





