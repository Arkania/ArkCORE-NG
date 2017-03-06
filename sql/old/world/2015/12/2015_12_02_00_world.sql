
delete from creature_formations where leaderGUID=116096;
insert into creature_formations values
(116096, 116096, 0, 0, 0, 0, 0),
(116096, 138661, 6, 126, 0, 0, 0),
(116096, 138863, 6, 162, 0, 0, 0),
(116096, 115655, 6, 198, 0, 0, 0),
(116096, 115871, 6, 234, 0, 0, 0);

delete from creature_formations where leaderGUID=129243;
insert into creature_formations values
(129243, 129243, 0, 0, 0, 0, 0),
(129243, 129446, 6, 126, 0, 0, 0),
(129243, 129447, 6, 162, 0, 0, 0),
(129243, 129448, 6, 198, 0, 0, 0),
(129243, 129449, 6, 234, 0, 0, 0);

delete from smart_scripts where entryorguid in (6906, 6907, 6908, 6910, 7023, 7175, 7206, 7291, 8658, 9978, 10052, 11486, 11487, 11488, 11489, 11490, 11492, 11496, 11501, 11517, 11518, 11519, 11520, 11561, 11680, 12319);
delete from smart_scripts where entryorguid in (13280, 14321, 14322, 14323, 14324, 14325, 14326, 14327, 14354, 15277, 16425, 16593, 17612, 18855, 18927, 19169, 22982, 23208, 23257, 23334, 23335, 23368, 23392, 26428, 29021);
delete from smart_scripts where entryorguid in (29022, 29023, 29024, 30736, 33854, 34430, 35167, 36231, 36845, 39388, 40008, 40011, 40013, 40448, 40597, 40633, 42698, 44404, 44648, 44715, 44752, 46209, 46210, 46211, 48832);
delete from smart_scripts where entryorguid in (48936, 479010, 3904800);

-- https://cata-twinhead.twinstar.cz/?quest=13961
update creature_template set gossip_menu_id=10519, AIName="", Scriptname="npc_razormane_pillager_34503" where entry=34503;

update gossip_menu_option set OptionBroadcastTextID=34693, option_id=1, npc_option_npcflag=1 where menu_id=10519;

update creature_template set AIName="", Scriptname="npc_hogtied_razormane_34514" where entry=34514;

delete from areatrigger_scripts where entry=5465;
insert into areatrigger_scripts values
(5465, "at_groldoms_farm_5465");

-- no fire here and now.. we change to unused phase
delete from creature where guid=138742;
insert into creature values 
(138742, 34346, 1, 1, 2, 20024, 0, 268.755, -3048.26, 99.0182, 3.36848, 500, 0, 0, 42, 0, 0, 0, 0, 0); -- 328, 20024

