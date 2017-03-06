
UPDATE creature_template_addon SET bytes2=257 WHERE entry=38150;

delete from npc_spellclick_spells where npc_entry=38150 and spell_id=71238;
insert into npc_spellclick_spells value 
(38150, 71238, 1, 0);

UPDATE creature_template SET npcflag=16777216, unit_flags=16384, unit_flags2=0, type_flags=131080, faction=35, VehicleId=0, mechanic_immune_mask=16384 WHERE entry=38150;

DELETE FROM creature WHERE id=38150 AND guid=202751;
INSERT INTO creature VALUES 
(202751, 38150, 654, 1, 14155776, 0, 0, -1274.21, 2109.97, 4.98116, 2.55929, 300, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature_template SET faction=2203, npcflag=16777216, unit_flags=16392 WHERE entry=37927;

delete from npc_spellclick_spells where npc_entry=37927 and spell_id=68503;
insert into npc_spellclick_spells value 
(37927, 68503, 1, 0);

delete from creature where id=37927;

UPDATE creature SET phaseMask=14155776 WHERE guid=202751;

DELETE FROM phase_definitions WHERE zoneId=4714 AND entry=6;
INSERT INTO phase_definitions VALUES 
(4714, 6, 4194304, 0, 656, 679, 1, "(They Have Allies, But So Do We) to (not set)");

DELETE FROM phase_area WHERE areaId=4714 AND entry=6;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 6, 24681, 99999, 66, 11, 1, "(They Have Allies, But So Do We) to (not set)");

UPDATE quest_template SET Method=2, Flags=2097288 WHERE Id=26706;

delete from npc_spellclick_spells where npc_entry=43747 and spell_id=81877;
insert into npc_spellclick_spells value 
(43747, 81877, 1, 0);

UPDATE creature_template SET npcflag=0, VehicleId=0 WHERE entry=43747;

UPDATE creature SET phaseMask=14155776 WHERE guid=253070;

delete from creature_queststarter where id=43749 and quest=30002;

delete from creature_questender where id=43749 and quest=30002;

DELETE FROM creature_text WHERE entry=43749;
INSERT INTO creature_text VALUES 
(43749, 0, 0, "We must bide our time.  They won't know what hit them.", 12, 0, 100, 0, 0, 0, "Tobias", 43816),
(43749, 1, 0, "Patience, friends.  We will strike soon.", 12, 0, 100, 0, 0, 0, "Tobias", 43838);

DELETE FROM creature_text WHERE entry=43749;
INSERT INTO creature_text VALUES 
(43749, 0, 0, "Time to go!", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43813),
(43749, 0, 1, "Hop on a hippogryph, now's our chance!", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43814),
(43749, 1, 0, "We'll set flight once everyone is ready.", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43837),
(43749, 1, 1, "Patience, friends.  We will strike soon.", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43838),
(43749, 1, 2, "Hold your horses, friend.  We'll hit them when we're all ready.", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43839),
(43749, 1, 3, "Let's give everyone time to gather.  We'll need a handful of people to come with us.", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43840),
(43749, 1, 4, "We must wait for the right time to strike!", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43815),
(43749, 1, 5, "We must bide our time.  They won't know what hit them.", 12, 0, 100, 0, 0, 0, "Tobias Mistmantle", 43816);

DELETE FROM creature_text WHERE entry=43566;
INSERT INTO creature_text VALUES 
(43566, 0, 0, "The villagers were thankfull to have Emberstone back. They brought us a little something to help against the Forsaken!", 14, 0, 100, 0, 0, 19684, "Lorna Crowley", 0),
(43566, 1, 0, "Air guard, attack!! Strafe them now, while they cannot maneuver!", 14, 0, 100, 0, 0, 19687, "Lorna Crowley", 42206),
(43566, 2, 0, "Attack!", 12, 0, 100, 0, 0, 19687, "Lorna Crowley", 43696),
(43566, 3, 0, "Secure the rafters!", 12, 0, 100, 0, 0, 19688, "Lorna Crowley", 43697),
(43566, 4, 0, "I want two sharpshooters to stay behind and cover the deck.  Everyone else, use the ropes to rappel down.  Let's give them hell!", 12, 0, 100, 0, 0, 19689, "Lorna Crowley", 43698),
(43566, 5, 0, "We've got the explosives  in the furnace room.  Just hold them off now!", 12, 0, 100, 0, 0, 19692, "Lorna Crowley", 43699),
(43566, 6, 0, "Hands up, greenskins!  My men will give you your new bearing.  You try anything funny and we'll fill you with lead.", 12, 0, 100, 0, 0, 19690, "Lorna Crowley", 43817),
(43566, 7, 0, "The rest of you, follow me downstairs!", 12, 0, 100, 0, 0, 19691, "Lorna Crowley", 43818),
(43566, 8, 0, "That's... one big orc.", 12, 0, 100, 0, 0, 19693, "Lorna Crowley", 44221),
(43566, 9, 0, "It's about to blow, jump on the Wyverns!", 12, 0, 100, 0, 0, 19694, "Lorna Crowley", 44222);

DELETE FROM creature_template_addon WHERE entry=43751;
INSERT INTO creature_template_addon VALUES 
(43751, 0, 0, 50331648, 1, 0, "");

UPDATE creature_template SET unit_flags=8, Type=9 WHERE entry=43751;

delete from npc_spellclick_spells where npc_entry=43751 and spell_id=46598;
insert into npc_spellclick_spells value 
(43751, 46598, 1, 0);

DELETE FROM creature WHERE guid=253070;
INSERT INTO creature VALUES 
(253070, 43749, 654, 1, 14155776, 0, 0, -1292.4, 2127.3, 5.54655, 3.22922, 500, 0, 0, 42, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43566 AND guid=251963;
INSERT INTO creature VALUES 
(251963, 43566, 749, 1, 14155776, 33474, 0, 6.8365, 0.0783, 84.797, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43764 AND guid=251938;
INSERT INTO creature VALUES 
(251938, 43764, 749, 1, 14155776, 33503, 0, 53.9098, 0.689094, 30.1788, 3.35103, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43767 AND guid=251939;
INSERT INTO creature VALUES 
(251939, 43767, 749, 1, 14155776, 33505, 0, 53.5231, -2.70909, 30.1788, 2.75762, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=42141; 
INSERT INTO creature VALUES 
(251940, 42141, 749, 1, 4194304, 0, 1, -2.08453, 23.9422, 89.9943, 1.69297, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251941, 42141, 749, 1, 4194304, 0, 1, -44.9259, 6.98739, 12.4255, 0, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251942, 42141, 749, 1, 4194304, 0, 1, 30.6456, -30.7163, 89.8455, 4.57276, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251943, 42141, 749, 1, 4194304, 0, 1, 10.6788, -25.0886, 89.9489, 4.24115, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251944, 42141, 749, 1, 4194304, 0, 1, 4.20127, -9.64648, 85.2608, 2.86234, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251945, 42141, 749, 1, 4194304, 0, 1, 0.115611, 25.2395, 89.9887, 2.86234, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251946, 42141, 749, 1, 4194304, 0, 1, -8.64439, -27.1678, 90.0169, 2.86234, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251947, 42141, 749, 1, 4194304, 0, 1, 2.52693, 8.763, 84.8803, 2.86234, 120, 0, 0, 1, 0, 0, 0, 0, 0), 
(251948, 42141, 749, 1, 4194304, 0, 1, 13.197, 24.5043, 89.9376, 3.64774, 120, 0, 0, 1, 0, 0, 0, 0, 0);


