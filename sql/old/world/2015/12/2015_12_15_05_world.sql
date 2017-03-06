

update creature_template set faction=28 where entry=42825;

-- spawned from script.
delete from creature where id=39835;

-- spawned from script.
delete from creature where id=52791;

-- spawned from script.
delete from creature where id=40708;

-- spawned from script.
delete from creature where id=40660;

-- flying to deep, in lava..
update creature set position_z=685.518 where guid=120246 and id=39833;

-- change phase
update creature set phaseMask=8388608 where id=40650;

-- wrong '?'
delete from quest_poi_points where questId=25810;
delete from quest_poi where questId=25810;

update npc_text set BroadcastTextID0=40543 where ID=15896;
update npc_text set BroadcastTextID0=40544 where ID=15897;

DELETE FROM phase_area WHERE areaId=5050;
DELETE FROM phase_area WHERE areaId=616;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(616, 0, 25523, 25525, 74, 74, 1, "Hatchery start and Flight in the Firelands"),
(616, 1, 25525, 25544, 74, 74, 1, "Hatchery Wave one"),
(616, 2, 25544, 25560, 74, 74, 1, "Hatchery Wave two"),
(616, 3, 25560, 25832, 74, 64, 0, "Hatchery Egg Wave");

delete from phase_definitions where zoneId=5050;
delete from phase_definitions where zoneId=616 and entry between 0 and 4;
insert into phase_definitions values
(616, 0, 33554433, 194, 719, 683, 0, "Hatchery start and Flight in the Firelands"), --  33554433 phaseMask
(616, 1, 16777217, 193, 719, 683, 0, "Hatchery Wave one"), -- 16777217
(616, 2,  8388609, 192, 719, 683, 0, "Hatchery Wave two"), -- 8388609
(616, 3,  4194305, 191, 719, 683, 0, "Hatchery Egg Wave"); -- 4194305

update npc_text set BroadcastTextID0=50266 where ID=17731;

UPDATE quest_template SET Method=2, Flags=136, SpecialFlags=0 WHERE Id=25523;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Farden Klauenwürger in der Brutstätte auf dem Hyjal zurück. Drückt die Taste 'Flattern', damit Euer Reittier mit den Flügeln schlägt!", QuestGiverTextWindow_loc3="Wächterflagge besuchen", QuestGiverTargetName_loc3="Wächterflagge" WHERE Id=25523;

UPDATE creature_template SET spell1=74183 WHERE entry=40719;
UPDATE creature_template SET spell1=74183, spell4=0 WHERE entry=39710;

UPDATE creature_template SET VehicleId=156 WHERE entry=40720;

UPDATE quest_template SET Method=2, Flags=1052808 WHERE Id=25525;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Farden Klauenwürger in der Brutstätte zurück.", QuestGiverTextWindow_loc3="Zwielichtritter", QuestGiverTargetName_loc3="Zwielichtritter" WHERE Id=25525;

UPDATE quest_template SET Method=2, Flags=1052808 WHERE Id=25544;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Farden Klauenwürger in der Brutstätte zurück.", QuestGiverTextWindow_loc3="Zwielichttjoster", QuestGiverTargetName_loc3="Zwielichttjoster" WHERE Id=25544;

UPDATE quest_template SET Method=2, Flags=3149960 WHERE Id=25560;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Farden Klauenwürger in der Brutstätte zurück.", QuestGiverTextWindow_loc3="Eier der Feuerlande", QuestGiverTargetName_loc3="Eier der Feuerlande" WHERE Id=25560;

-- from sniff 15595 and 14333
delete from npc_spellclick_spells where npc_entry=39730 and spell_id=74293;
delete from npc_spellclick_spells where npc_entry=39736 and spell_id=74305;
delete from npc_spellclick_spells where npc_entry=39737 and spell_id=74304;
delete from npc_spellclick_spells where npc_entry=39738 and spell_id=74308;
delete from npc_spellclick_spells where npc_entry=39997 and spell_id=74618;
delete from npc_spellclick_spells where npc_entry=39998 and spell_id=74618;
delete from npc_spellclick_spells where npc_entry=39999 and spell_id=74654;
delete from npc_spellclick_spells where npc_entry=40190 and spell_id=43671;
delete from npc_spellclick_spells where npc_entry=40240 and spell_id=75140;
delete from npc_spellclick_spells where npc_entry=40340 and spell_id=75570;
delete from npc_spellclick_spells where npc_entry=40720 and spell_id=90102; -- old value
delete from npc_spellclick_spells where npc_entry=40720 and spell_id=75935;
delete from npc_spellclick_spells where npc_entry=40723 and spell_id=90102; -- old value
delete from npc_spellclick_spells where npc_entry=40723 and spell_id=75943;

INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(39730, 74293, 1, 0),
(39736, 74305, 1, 0),
(39737, 74304, 1, 0),
(39738, 74308, 1, 0),
(39997, 74618, 1, 0),
(39998, 74618, 1, 0),
(39999, 74654, 1, 0),
(40190, 43671, 1, 0),
(40240, 75140, 1, 0),
(40340, 75570, 1, 0),
(40720, 75935, 1, 0),
(40723, 75943, 1, 0);

delete from spell_script_names where spell_id=74183;
insert into spell_script_names values
(74183, "spell_gen_flap");

delete from vehicle_template_accessory where entry=52359 and accessory_entry=52361;
delete from vehicle_template_accessory where entry=50523 and accessory_entry=50525;
delete from vehicle_template_accessory where entry=40121 and accessory_entry=40107;
delete from vehicle_template_accessory where entry=39833 and accessory_entry=39835;
delete from vehicle_template_accessory where entry=40650 and accessory_entry=40660;
delete from vehicle_template_accessory where entry=39789 and accessory_entry=39640;
delete from vehicle_template_accessory where entry=39839 and accessory_entry=39838;
delete from vehicle_template_accessory where entry=40573 and accessory_entry=40575;
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(52359, 52361, 0, 0, "Toy Cart - Toy Cart Bunny", 6, 30000), -- Toy Cart - Toy Cart Bunny
(50523, 50525, 0, 0, "Kyle Radue - Chris Miller", 6, 30000), -- Kyle Radue - Chris Miller
(40121, 40107, 0, 0, "Thol'embaar Summon Bunny - Thol'embaar", 6, 30000), -- Thol'embaar Summon Bunny - Thol'embaar
(39833, 39835, 0, 0, "Twilight Buzzard - Twilight Knight Rider", 6, 30000), -- Twilight Buzzard - Twilight Knight Rider
(40650, 40660, 0, 0, "Twilight Firebird - Twilight Lancer", 6, 30000), -- Twilight Firebird - Twilight Lancer
(39789, 39640, 0, 0, "Kristoff's Chain Vehicle - Kristoff Manheim", 6, 30000), -- Kristoff's Chain Vehicle - Kristoff Manheim
(39839, 39838, 0, 0, "Twilight Stormwaker - Twilight Stormwaker", 6, 30000), -- Twilight Stormwaker - Twilight Stormwaker
(40573, 40575, 1, 0, "Twilight Stormwaker - Twilight Stormwaker", 6, 30000); -- Twilight Stormwaker - Twilight Stormwaker

delete from creature_text where entry=40107 and groupid between 0 and 1;
insert into creature_text values
(40107, 0, 0, "Fool of a mortal. Flesh burns.", 12, 0, 100, 0, 0, 0, "", 40055),
(40107, 1, 0, "Others will come... the age of mortals... has passed.", 12, 0, 100, 0, 0, 0, "", 40078);

delete from creature_text where entry=40578 and groupid between 0 and 3;
insert into creature_text values
(40578, 0, 0, "Grab a Lance from the Racks", 42, 0, 100, 0, 0, 0, "", 47644),
(40578, 1, 0, "Equip the Lance", 42, 0, 100, 0, 0, 0, "", 47645),
(40578, 2, 0, "Mount One of Aviana's Guardians", 42, 0, 100, 0, 0, 0, "", 47646),
(40578, 3, 0, "Don't forget to replace your main weapon!", 42, 0, 100, 0, 0, 0, "", 47739);

delete from creature_text where entry=39710 and groupid between 0 and 6;
insert into creature_text values
(39710, 0, 0, "Press Flap to Flap Your Wings!", 42, 0, 100, 0, 0, 0, "", 40557),
(39710, 1, 0, "Wave One:", 42, 0, 100, 0, 0, 0, "", 40558),
(39710, 2, 0, "Prepare to Joust, Buzzard Bait!", 42, 0, 100, 0, 0, 0, "", 40559),
(39710, 3, 0, "Wave Two:", 42, 0, 100, 0, 0, 0, "", 40664),
(39710, 4, 0, "The sky is falling!", 42, 0, 100, 0, 0, 0, "", 40665),
(39710, 5, 0, "Egg Wave:", 42, 0, 100, 0, 0, 0, "", 40666),
(39710, 6, 0, "Destroy the Firelands Eggs!", 42, 0, 100, 0, 0, 0, "", 40667);

update gameobject set phasemask=33554432 where id=202973;
update gameobject set phasemask=33554432 where id=202972;

