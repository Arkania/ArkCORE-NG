
SET @PATHID=3457701;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, 203.2264, -2930.814, 92.53939, 0, 0, 1),
(@PATHID, 1, 201.3559, -2925.632, 92.59977, 0, 0, 1),
(@PATHID, 2, 186.191, -2916.007, 93.44816, 0, 0, 1),
(@PATHID, 3, 170.3924, -2905.245, 92.42078, 0, 0, 1),
(@PATHID, 4, 156.0156, -2894.384, 92.18156, 0, 0, 1),
(@PATHID, 5, 144.566, -2885.118, 92.5294, 0, 0, 1),
(@PATHID, 6, 133.6649, -2876.151, 91.85372, 0, 0, 1),
(@PATHID, 7, 122.7743, -2867.283, 91.66902, 0, 0, 1),
(@PATHID, 8, 110.7118, -2854.8, 95.84363, 0, 0, 1),
(@PATHID, 9, 100.783, -2842.003, 95.84571, 0, 0, 1),
(@PATHID, 10, 85.98785, -2822.71, 95.83396, 0, 0, 1),
(@PATHID, 11, 72.30556, -2803.283, 95.85462, 0, 0, 1),
(@PATHID, 12, 59.14931, -2785.519, 96.1252, 0, 0, 1),
(@PATHID, 13, 46.82292, -2769.253, 94.56284, 0, 0, 1),
(@PATHID, 14, 28.07118, -2747.729, 91.98183, 0, 0, 1),
(@PATHID, 15, 2.890625, -2727.547, 91.67077, 0, 0, 1),
(@PATHID, 16, -31.15625, -2708.503, 93.59576, 0, 0, 1),
(@PATHID, 17, -58.55382, -2697.359, 95.72238, 0, 0, 1),
(@PATHID, 18, -95.57986, -2687.859, 95.83234, 0, 0, 1),
(@PATHID, 19, -137.3542, -2683.128, 94.66044, 0, 0, 1),
(@PATHID, 20, -174.1528, -2680.778, 93.07629, 0, 0, 1),
(@PATHID, 21, -200.4809, -2681.925, 94.90981, 0, 0, 1),
(@PATHID, 22, -231.0504, -2683.094, 95.93831, 0, 0, 1),
(@PATHID, 23, -259.8854, -2683.245, 95.53184, 0, 0, 1),
(@PATHID, 24, -289.4375, -2682.257, 93.01896, 0, 0, 1),
(@PATHID, 25, -316.6129, -2680.644, 93.66322, 0, 0, 1),
(@PATHID, 26, -342.2361, -2680.701, 95.92309, 0, 0, 1),
(@PATHID, 27, -398.5141, -2678.161, 95.66409, 0, 0, 1);

update gossip_menu_option set OptionBroadcastTextID=34817 where menu_id=10528 and id=0;

update npc_text set BroadcastTextID0=34816 where id=14566;

update creature_template set AIName="", ScriptName="npc_rocco_whipshank_34578" where entry=34578;
update creature_template set AIName="", ScriptName="npc_head_caravan_kodo_34577" where entry=34577;
update creature_template set AIName="", ScriptName="vehicle_hotseat_34582" where entry=34582;
update creature_template set AIName="", ScriptName="vehicle_burning_blade_mount_34593" where entry=34593;
update creature_template set AIName="", ScriptName="npc_burning_blade_raider_34594" where entry=34594;

delete from creature_text where entry=34578 and groupid=0;
insert into creature_text values 
(34578, 0, 0, "There she is. Mount up!", 12, 0, 100, 0, 0, 0, "", 34818);

update creature_template_addon set auras="" where entry=34576;

UPDATE creature_template SET unit_flags=0, unit_flags2=2048 WHERE entry=34576;

delete from npc_spellclick_spells where npc_entry=34577;
insert into npc_spellclick_spells values
(34577, 65669, 1 ,0);

delete from spell_script_names where spell_id=65669;
insert into spell_script_names values
(65669, "spell_mount_caravan_kodo_cue_part2_65669");

UPDATE creature_template SET spell1=66427, spell2=65704 WHERE entry=34582;

delete from creature_text where entry=34578 and groupid=1;
insert into creature_text values 
(34578, 1, 0, "Ride hard and show no mercy!", 12, 0, 100, 0, 0, 0, "", 35138);

delete from creature_text where entry=34582 and groupid=0;
insert into creature_text values 
(34582, 0, 0, "Defend the Caravan Kodo!", 42, 0, 100, 0, 0, 0, "", 34625);

delete from creature_text where entry=34431 and groupid in (1, 2);
insert into creature_text values 
(34431, 1, 0, "The Burning Blade? What are they doing here? Shoot to kill!", 12, 0, 100, 0, 0, 0, "", 35139),
(34431, 2, 0, "Incredible shooting! I'll try to calm the animals down. Report to Thork, he will want to know of this attack.", 12, 0, 100, 0, 0, 0, "", 34821);

delete from creature where id=34593;

UPDATE creature_template SET minlevel=11, maxlevel=12, mindmg=17, maxdmg=22, attackpower=46, baseattacktime=2000, rangeattacktime=2000, minrangedmg=11, maxrangedmg=17 WHERE entry=34594;

UPDATE quest_template SET RequiredNpcOrGo1=53572, RequiredNpcOrGoCount1=1, EndText="", ObjectiveText1="Crossroads Caravan Escorted" WHERE Id=13975;
UPDATE locales_quest SET EndText_loc3="", ObjectiveText1_loc3="Die Karawane zum Wegekreuz begleitet" WHERE Id=13975;






