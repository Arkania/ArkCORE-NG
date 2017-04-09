
update creature_loot_template set chance=46.4832 where entry=34884 and item=117;
update creature_loot_template set chance=24.8862 where entry=34884 and item=159;
update creature_loot_template set chance=7.7989 where entry=34884 and item=805;
update creature_loot_template set chance=5.9164 where entry=34884 and item=5571;
update creature_loot_template set chance=5.151 where entry=34884 and item=828;
update creature_loot_template set chance=4.9648 where entry=34884 and item=5572;
update creature_loot_template set chance=4.7373 where entry=34884 and item=4496;

UPDATE quest_template SET NextQuestIdChain=14091 WHERE Id=14078; 
UPDATE quest_template SET NextQuestIdChain=14099 WHERE Id=14093; 
UPDATE quest_template SET NextQuestIdChain=14099 WHERE Id=14098; 
UPDATE quest_template SET NextQuestIdChain=14276 WHERE Id=14275; 
UPDATE quest_template SET NextQuestIdChain=14290 WHERE Id=14276; 
UPDATE quest_template SET NextQuestIdChain=14157 WHERE Id=14290; 
UPDATE quest_template SET NextQuestIdChain=28850 WHERE Id=14157; 
UPDATE quest_template SET NextQuestIdChain=14154 WHERE Id=28850; 
UPDATE quest_template SET NextQuestIdChain=26129 WHERE Id=14154; 
UPDATE quest_template SET NextQuestIdChain=14214 WHERE Id=14204; 
UPDATE quest_template SET NextQuestIdChain=14293 WHERE Id=14214; 
UPDATE quest_template SET NextQuestIdChain=14218 WHERE Id=14212; 
UPDATE quest_template SET NextQuestIdChain=14221 WHERE Id=14218; 
UPDATE quest_template SET NextQuestIdChain=14222 WHERE Id=14221; 
UPDATE quest_template SET NextQuestIdChain=14320 WHERE Id=14313; 
UPDATE quest_template SET NextQuestIdChain=14336 WHERE Id=14321; 
UPDATE quest_template SET NextQuestIdChain=14366 WHERE Id=14347; 
UPDATE quest_template SET NextQuestIdChain=14366 WHERE Id=14348; 
UPDATE quest_template SET NextQuestIdChain=14367 WHERE Id=14366; 
UPDATE quest_template SET NextQuestIdChain=14395 WHERE Id=14396; 
UPDATE quest_template SET NextQuestIdChain=14397 WHERE Id=14395; 
UPDATE quest_template SET NextQuestIdChain=14399 WHERE Id=14398; 
UPDATE quest_template SET NextQuestIdChain=14416 WHERE Id=14406; 
UPDATE quest_template SET NextQuestIdChain=14463 WHERE Id=14416; 
UPDATE quest_template SET NextQuestIdChain=14405 WHERE Id=14404; 
UPDATE quest_template SET NextQuestIdChain=14400 WHERE Id=14399; 
UPDATE quest_template SET NextQuestIdChain=14401 WHERE Id=14400; 
UPDATE quest_template SET NextQuestIdChain=14402 WHERE Id=14401; 
UPDATE quest_template SET NextQuestIdChain=14465 WHERE Id=14402; 
UPDATE quest_template SET NextQuestIdChain=14466 WHERE Id=14465; 
UPDATE quest_template SET NextQuestIdChain=24468 WHERE Id=24438; 
UPDATE quest_template SET NextQuestIdChain=24472 WHERE Id=24468; 
UPDATE quest_template SET NextQuestIdChain=24484 WHERE Id=24483; 
UPDATE quest_template SET NextQuestIdChain=24501 WHERE Id=24484; 
UPDATE quest_template SET NextQuestIdChain=24616 WHERE Id=24578; 
UPDATE quest_template SET NextQuestIdChain=24617 WHERE Id=24616; 
UPDATE quest_template SET NextQuestIdChain=24627 WHERE Id=24617; 
UPDATE quest_template SET NextQuestIdChain=24593 WHERE Id=24646; 
UPDATE quest_template SET NextQuestIdChain=24673 WHERE Id=24593; 
UPDATE quest_template SET NextQuestIdChain=24672 WHERE Id=24673; 
UPDATE quest_template SET NextQuestIdChain=24592 WHERE Id=24672; 
UPDATE quest_template SET NextQuestIdChain=24575 WHERE Id=24677; 

DELETE FROM creature_loot_template WHERE Entry=35463;
INSERT INTO creature_loot_template VALUES 
(35463, 117, 0, 49.331, 0, 1, 0, 1, 1, ""), 
(35463, 159, 0, 24.3746, 0, 1, 0, 1, 1, ""), 
(35463, 769, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 805, 0, 4.4503, 0, 1, 0, 1, 1, ""), 
(35463, 828, 0, 6.1664, 0, 1, 0, 1, 1, ""), 
(35463, 1414, 0, 0.0436, 0, 1, 0, 1, 1, ""), 
(35463, 1419, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 1427, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 2589, 0, 0.1597, 0, 1, 0, 1, 1, ""), 
(35463, 2773, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 2924, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 4496, 0, 5.032, 0, 1, 0, 1, 1, ""), 
(35463, 5523, 0, 0.0436, 0, 1, 0, 1, 1, ""), 
(35463, 5571, 0, 5.4974, 0, 1, 0, 1, 1, ""), 
(35463, 5572, 0, 5.3229, 0, 1, 0, 1, 1, ""), 
(35463, 20772, 0, 0.0145, 0, 1, 0, 1, 1, ""), 
(35463, 46896, 0, 0.0145, 0, 1, 0, 1, 1, ""); 

UPDATE gameobject SET phaseGroup=401 WHERE guid=166796;

update gameobject set phaseId=0, phasegroup=401 where guid in (166774);

delete from spell_phase where spell_id in (72870, 72872, 76642);

INSERT INTO `spell_phase` VALUES (72870, 0, 171, 0, 638, 683, 'Worgen Bite');

INSERT INTO `spell_phase` VALUES (72872, 0, 172, 0, 638, 683, 'Infected Bite');

INSERT INTO `spell_phase` VALUES (76642, 0, 179, 0, 638, 683, 'Hideous Bite Wound');

UPDATE creature_template SET minlevel=4, maxlevel=4, unit_flags=8 WHERE entry=35231;

delete from npc_spellclick_spells where npc_entry=44427;
insert into npc_spellclick_spells values 
(44427, 67766, 2, 0);

delete from npc_spellclick_spells where npc_entry=35231;
insert into npc_spellclick_spells values 
(35231, 46598, 1, 0);

delete from vehicle_template_accessory where entry = 35231;
insert into vehicle_template_accessory values 
(35231, 35230, 1, 1, "darius crowlew and horse", 7, 0);

UPDATE quest_template SET NextQuestIdChain=14221 WHERE Id=14221;

delete from creature where id=36332 and guid in (24377, 24647);

DELETE FROM phase_definitions WHERE zoneId=4714 AND entry in (7, 8);
INSERT INTO phase_definitions VALUES 
(4714, 7, 169, 0, 638, 683, 1, "Duskhaven start phase 169"),
(4714, 8, 181, 0, 638, 683, 1, "Duskhaven start phase 181");

DELETE FROM phase_area WHERE areaId=4714 AND entry in (7, 8);
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 7, 14222, 14375, 64, 11, 1, "Duskhaven start phase 169"),
(4714, 8, 14375, 14336, 64, 1, 1, "Duskhaven start phase 181");

update creature set phaseId=169, phaseGroup=0 where id in (36330, 36331, 36332);

delete from creature where id=36798 and guid in (10771, 10772);





