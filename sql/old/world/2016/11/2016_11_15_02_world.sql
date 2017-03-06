

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Das ist Ihr Anführer?! Kümmert Euch darum!", QuestGiverTargetName_loc3="Gesichtsloser" WHERE Id=24868;

UPDATE creature_template_addon SET bytes2=1 WHERE entry=38455;

UPDATE creature_template SET minlevel=9, maxlevel=9, faction=2204, unit_flags=33288, ScriptName="npc_ace_38455" WHERE entry=38455;

DELETE FROM waypoint_data WHERE id in (3845501, 3845502, 3845503);
INSERT INTO waypoint_data VALUES 
(3845501, 0, 679.691589, 2022.908813, 49.275860, 3.847952, 0, 0, 0, 100, 0),
(3845502, 0, 669.849487, 2006.799316, 41.468044, 3.498447, 0, 1, 0, 100, 0),
(3845502, 1, 611.755127, 1982.499512, 14.328700, 3.573060, 0, 1, 0, 100, 0),
(3845502, 2, 504.871338, 2005.877319,  1.819739, 2.901546, 0, 1, 0, 100, 0),
(3845502, 3, 452.308990, 1985.922607, -0.413136, 3.525938, 0, 1, 0, 100, 0),
(3845502, 4, 401.283722, 1960.726440, -0.513732, 3.274610, 0, 1, 0, 100, 0),
(3845502, 5, 348.688629, 1950.589111, -0.513723, 3.333515, 0, 1, 0, 100, 0),
(3845502, 6, 279.717621, 1940.724121, -0.512193, 3.129311, 0, 1, 0, 100, 0),
(3845502, 7, 174.641388, 1942.054077,  4.250042, 3.207851, 0, 1, 0, 100, 0),
(3845503, 0, 174.641388, 1942.054077,  4.250042, 3.207851, 0, 1, 0, 100, 0),
(3845503, 1, 279.717621, 1940.724121, -0.512193, 3.129311, 0, 1, 0, 100, 0);

UPDATE creature SET spawndist=0, MovementType=0, spawntimesecs=120 WHERE guid=249616;

UPDATE creature_template SET gossip_menu_id=0 WHERE entry=38441;

delete from smart_scripts where entryorguid=44579;

update creature_template set npcflag=0 where entry=28468;

UPDATE creature_template SET unit_flags=768 WHERE entry=38457;

UPDATE creature_template_addon SET bytes1=0, auras="72126 72055" WHERE entry=38448;  -- 33554441

UPDATE creature_template SET ScriptName="npc_faceless_of_the_deep_38448" WHERE entry=38448;

UPDATE creature SET position_z=8.1499, spawntimesecs=120 WHERE guid=246669;



