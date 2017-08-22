

update quest_template set RequiredNpcOrGo1=-201792, RequiredNpcOrGoCount1=4 where ID=24569;

UPDATE creature_template SET maxlevel=17 WHERE entry=584;

DELETE FROM creature WHERE id=584 AND guid=648;

UPDATE quest_template SET PrevQuestId=26571 WHERE Id=26573;

UPDATE quest_template SET PrevQuestId=26573 WHERE Id=26607;

update creature_loot_template set chance=100 where entry=43329 and item=58954;

update creature_loot_template set chance=100 where entry=43327 and item=58953;

DELETE FROM creature WHERE id=43184 AND guid=288857;
INSERT INTO creature VALUES 
(288857, 43184, 0, 0, 0, 1, 169, 0, 0, 0, -9203.84, -2155.79, 57.187, 6.565, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_template_addon WHERE entry=43184;

DELETE FROM creature_addon WHERE guid in (269875, 288857);
INSERT INTO creature_addon VALUES 
(269875, 0, 0, 0, 1, 0, 0, 0, 0, "80816"),
(288857, 0, 0, 0, 1, 0, 0, 0, 0, "81201");

UPDATE creature_template SET npcflag=16777216, unit_flags=256, unit_flags2=2099200 WHERE entry=43443;

DELETE FROM creature_template_addon WHERE entry=43443;
INSERT INTO creature_template_addon VALUES 
(43443, 0, 0, 65536, 1, 0, 0, 0, 0, "");

delete from npc_spellclick_spells where npc_entry=43443;
insert into npc_spellclick_spells values
(43443, 81243, 1, 0),
(43443, 46598, 0, 0);

delete from conditions where SourceTypeOrReferenceId=18 and SourceGroup=43443 and SourceEntry=81243;
insert into conditions values 
(18, 43443, 81243, 0, 0, 9, 0, 26616, 0, 0, 0, 0, 0, "", "ship can only be targeted, when quest is taken.");

delete from vehicle_template_accessory where entry=43443;
insert into vehicle_template_accessory values 
(43443, 43445, 4, 1, "D Combanie Bravo on riverboat", 6, 30000),
(43443, 43446, 3, 1, "K Combanie Bravo on riverboat", 6, 30000),
(43443, 43447, 2, 1, "J Combanie Bravo on riverboat", 6, 30000),
(43443, 43448, 1, 1, "M Combanie Bravo on riverboat", 6, 30000),
(43443, 43449, 0, 1, "JK Combanie Bravo on riverboat", 6, 30000);

delete from npc_spellclick_spells where npc_entry in (43445, 43446, 43447, 43448, 43449);
insert into npc_spellclick_spells values
(43445, 46598, 0, 0),
(43446, 46598, 0, 0),
(43447, 46598, 0, 0),
(43448, 46598, 0, 0),
(43449, 46598, 0, 0);

delete from creature where guid in (9352, 9353, 9354, 9355, 9356);

delete from vehicle_template_accessory where entry=43450;
insert into vehicle_template_accessory values 
(43450, 43435, 4, 1, "D Combanie Bravo on riverboat", 6, 30000),
(43450, 43434, 3, 1, "K Combanie Bravo on riverboat", 6, 30000),
(43450, 43433, 2, 1, "J Combanie Bravo on riverboat", 6, 30000),
(43450, 43432, 1, 1, "M Combanie Bravo on riverboat", 6, 30000),
(43450, 43457, 0, 1, "JK Combanie Bravo on riverboat", 6, 30000);

delete from npc_spellclick_spells where npc_entry in (43450, 43432, 43433, 43434, 43435,43457);
insert into npc_spellclick_spells values
(43450, 46598, 0, 0),
(43432, 46598, 0, 0),
(43433, 46598, 0, 0),
(43434, 46598, 0, 0),
(43435, 46598, 0, 0),
(43457, 46598, 0, 0);

update creature_template_addon set auras="" where entry in (43432, 43433, 43434, 43435);

DELETE FROM creature_template_addon WHERE entry=43457;
INSERT INTO creature_template_addon VALUES 
(43457, 0, 0, 0, 0, 0, 0, 0, 0, "");

DELETE FROM creature_template_addon WHERE entry=43450;
INSERT INTO creature_template_addon VALUES 
(43450, 0, 0, 0, 0, 0, 0, 0, 0, "");

UPDATE quest_template SET PrevQuestId=26726 WHERE Id=28416;

UPDATE quest_template SET PrevQuestId=26616 WHERE Id=26636;

UPDATE quest_template SET PrevQuestId=26616 WHERE Id=26637;

UPDATE quest_template SET PrevQuestId=26616 WHERE Id=26638;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Jäger des Schwarzfels", QuestGiverTargetName_loc3="Jäger des Schwarzfels" WHERE Id=26638;

UPDATE creature SET position_x=-9676.11, position_y=-2841.606, position_z=54.2812 WHERE guid=11251;
UPDATE creature SET orientation=.1047 WHERE guid=11251;

UPDATE creature_template_addon SET aiAnimKit=770 WHERE entry=43508;
UPDATE creature_template SET InhabitType=4 WHERE entry=43508;

UPDATE creature_template SET npcflag=2, unit_flags=33600, unit_flags2=34817, dynamicflags=64 WHERE entry=43508;

UPDATE quest_template SET NextQuestId=26640, ExclusiveGroup=-26636, NextQuestIdChain=26640 WHERE Id=26636;

UPDATE quest_template SET NextQuestId=26640, ExclusiveGroup=-26636, NextQuestIdChain=26640 WHERE Id=26637;

UPDATE quest_template SET NextQuestId=26640, ExclusiveGroup=-26636, NextQuestIdChain=26640 WHERE Id=26638;

UPDATE quest_template SET ExclusiveGroup=-26636 WHERE Id=26639;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Kriegsgefangene", QuestGiverTargetName_loc3="Kriegsgefangene" WHERE Id=26646;

UPDATE quest_template SET QuestGiverTextWindow="Prisoner of War", QuestGiverTargetName="Prisoner of War" WHERE Id=26646;

UPDATE item_template SET Flags=196609 WHERE entry=60384

