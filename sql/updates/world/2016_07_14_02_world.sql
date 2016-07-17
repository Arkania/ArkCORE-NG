
UPDATE creature_template SET npcflag=16777216, mechanic_immune_mask=16384 WHERE entry=38424;

delete from npc_spellclick_spells where npc_entry=38424;
insert into npc_spellclick_spells values
(38424, 46598, 1, 0); -- 38424	72009	1	0

UPDATE creature_template SET npcflag=16777216, mechanic_immune_mask=16384 WHERE entry=38424;

DELETE FROM creature_text WHERE entry=38218 and groupid=7 and id in (0,1,2,3);
INSERT INTO creature_text VALUES 
(38218, 7, 0, "Gilneas will prevail!", 12, 0, 100, 0, 0, 0, "", 38493),
(38218, 7, 1, "Your time is up, Forsaken scum!", 12, 0, 100, 0, 0, 0, "", 38494),
(38218, 7, 2, "Attack!", 12, 0, 100, 0, 0, 0, "", 38495),
(38218, 7, 3, "Push them back!", 12, 0, 100, 0, 0, 0, "", 38496);

DELETE FROM creature_text WHERE entry=38218 AND groupid=8 AND id=1;
INSERT INTO creature_text VALUES 
(38218, 8, 1, "Abominations are blocking the way towards the military district!  This won't be easy.", 12, 0, 100, 0, 0, 19609, "Prince Liam Greymane Say", 38362);

DELETE FROM creature_text WHERE entry=38218 AND groupid=9 AND id=1;
INSERT INTO creature_text VALUES 
(38218, 9, 1, "You're a sight for sore eyes, Lorna.  Let's get those cannons manned!  The rest of you, lure the abominations into the open!", 14, 0, 100, 0, 0, 19610, "Prince Liam Greymane Say", 38345);

UPDATE creature_template SET ScriptName="npc_dark_ranger_elite_38464" WHERE entry=38464;

UPDATE creature_template SET ScriptName="npc_vile_abomination_38420" WHERE entry=38420;

UPDATE creature_template SET ScriptName="npc_freed_emberstone_villager_38425" WHERE entry=38425;

delete from creature_equip_template where entry=38425 and id=1;
insert into creature_equip_template values 
(38425, 1, 0, 0, 2552);

UPDATE creature_template SET unit_flags=32768, unit_flags2=0, RegenHealth=0 WHERE entry=47859;

DELETE FROM creature_text WHERE entry=38331 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(38331, 0, 0, "Gorerot crush puny worgen!", 14, 0, 100, 0, 0, 20914, "Goreroth", 38251);

DELETE FROM creature_text WHERE entry=38415 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38415, 1, 0, "Let us join your father's force's, Liam.  They'll need our help against Sylvanas.", 14, 0, 100, 0, 1, 19500, "say", 38361);

DELETE FROM creature_text WHERE entry=38470 AND groupid=1;
INSERT INTO creature_text VALUES 
(38470, 1, 0, "LIAM!!  NO!!!", 14, 0, 100, 0, 0, 19727, "", 38485);

DELETE FROM creature_text WHERE entry=38469 AND groupid=3 AND id=0;
INSERT INTO creature_text VALUES 
(38469, 3, 0, "Let's see how brave Gilneas gets on without its stubborn leader!", 12, 0, 100, 0, 0, 0, "Lady Sylvanas Windrunner Say", 38368);

DELETE FROM creature WHERE id=38415 AND guid=18595;
INSERT INTO creature VALUES 
(18595, 38415, 654, 1, 262144, 0, 0, -1773.54, 1341.46, 19.786, 0.94, 90, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_text WHERE entry=38426;
INSERT INTO creature_text VALUES 
(38426, 0, 0, "The villagers were thankful to have Emberstone back.  They brought us a little something to help against the Forsaken!", 14, 0, 100, 0, 0, 19684, "", 38322);

UPDATE creature_template SET ScriptName="npc_gorerot_38331" WHERE entry=38331;

DELETE FROM creature_text WHERE entry=38218 AND groupid=10 AND id=0;
INSERT INTO creature_text VALUES 
(38218, 10, 0, "Crowley's troops are up ahead!  Press on!", 14, 0, 100, 0, 0, 19611, "Prince Liam Greymane Say", 38360);

delete from creature_equip_template where entry=38426 and id=1;
insert into creature_equip_template values 
(38426, 1, 10616, 0, 15460);

delete from creature_text where entry=38331 and groupid=1;

DELETE FROM creature WHERE id=38474 AND guid=251894;
INSERT INTO creature VALUES 
(251894, 38474, 654, 1, 262144, 30502, 0, -1634.616, 1632.859, 21.21159, 4.44084, 90, 0, 0, 0, 0, 0, 0, 0, 0);

delete from creature_addon where guid= 251894;
insert into creature_addon values 
(251894, 0, 0, 0, 0, 0,"");

DELETE FROM waypoint_data WHERE id=251894;
DELETE FROM waypoint_data WHERE id=3847401;
INSERT INTO waypoint_data VALUES 
(3847401, 0, -1634.873, 1636.791, 21.12881, 4.689035, 0, 1, 0, 0, 0),
(3847401, 1, -1635.782, 1621.483, 20.42826, 3.177146, 0, 1, 0, 0, 0),
(3847401, 2, -1661.025, 1620.674, 20.48856, 3.188927, 0, 1, 0, 0, 0),
(3847401, 3, -1679.490, 1618.253, 20.48856, 3.361714, 0, 1, 0, 0, 0);

DELETE FROM creature_text WHERE entry=38474;
INSERT INTO creature_text VALUES 
(38474, 0, 0, "FATHER!!!", 14, 0, 100, 0, 0, 19612, "Prince Liam Greymane Yell", 38369),
(38474, 1, 0, "I've been spotted!  $N incoming! Help!", 14, 0, 100, 0, 0, 19612, "", 486),
(38474, 2, 0, "We did it, father...", 12, 0, 100, 0, 0, 20562, "Prince Liam Greymane Say", 38371),
(38474, 3, 0, "We took back our city... we took back...", 12, 0, 100, 0, 0, 20563, "Prince Liam Greymane Say", 38372);

UPDATE creature_template SET AIName="" WHERE entry=38474;

delete from smart_scripts where entryorguid=38474;

UPDATE creature SET phaseMask=2883584 WHERE guid in (252029, 252033, 252034);






