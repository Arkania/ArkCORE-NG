
UPDATE quest_template SET Flags=262144 WHERE Id=27003;

update creature_template set AIName="", ScriptName="npc_beam_target_bunny_46661" where entry=46661;
update creature_template set AIName="", ScriptName="npc_adarrah_46533" where entry=46533;
update creature_template set AIName="", ScriptName="npc_lady_humps_46536" where entry=46536;
update creature_template set AIName="", ScriptName="" where entry=46554;
update creature_template set AIName="", ScriptName="npc_uldum_caravan_harness_46596" where entry=46596;

UPDATE creature_template SET npcflag=16777216 WHERE entry=46536;
delete from npc_spellclick_spells where npc_entry=46536;
insert into npc_spellclick_spells values
(46536,  89270, 1, 0);

delete from creature_text where entry=46533 and groupid in (0, 1);
insert into creature_text values
(46533, 0, 0, "No, no, silly $R...", 12, 0, 100, 11, 0, 0, "", 46688),
(46533, 1, 0, "No one rides the Lady!", 12, 0, 100, 274, 0, 0, "", 46689);

delete from vehicle_template_accessory where entry=46596;
insert into vehicle_template_accessory values
(46596, 46534, 4, 1, "Domesticated Kodo", 7, 0),
(46596, 46544, 0, 1, "Turgore", 7, 0),
(46596, 46545, 3, 1, "Harkor", 7, 0),
(46596, 46547, 5, 1, "Tanzar", 7, 0),
(46596, 46548, 2, 1, "Kurzel", 7, 0);

delete from npc_spellclick_spells where npc_entry in (46534, 46544, 46545, 46547, 46548, 46596);
insert into npc_spellclick_spells values
(46534, 46598, 0, 0),
(46544, 46598, 0, 0),
(46545, 46598, 0, 0),
(46547, 46598, 0, 0),
(46548, 46598, 0, 0),
(46596, 46598, 0, 0);

UPDATE creature_template SET unit_flags=256 WHERE entry=46534;
UPDATE creature_template SET unit_flags=256 WHERE entry=46596;

delete from creature_text where entry=46539 and groupid in (0);
insert into creature_text values
(46539, 0, 0, "Ahoy!", 12, 0, 100, 70, 0, 21174, "", 46715);

update creature_template set equipment_id=46538 where entry=46538;

delete from vehicle_template_accessory where entry=46538;
insert into vehicle_template_accessory values
(46538, 46539, 0, 1, "Budd", 8, 60000);

delete from npc_spellclick_spells where npc_entry in (46538, 46539);
insert into npc_spellclick_spells values
(46538, 46598, 0, 0),
(46539, 46598, 0, 0);

update creature_template set equipment_id=46540 where entry=46540;

delete from vehicle_template_accessory where entry=46540;
insert into vehicle_template_accessory values
(46540, 46541, 0, 1, "Samir", 8, 60000);

delete from npc_spellclick_spells where npc_entry in (46540, 46541);
insert into npc_spellclick_spells values
(46540, 46598, 0, 0),
(46541, 46598, 0, 0);

update creature_template set equipment_id=46543 where entry=46543;

delete from vehicle_template_accessory where entry=46543;
insert into vehicle_template_accessory values
(46543, 46542, 0, 1, "Mack", 8, 60000);

delete from npc_spellclick_spells where npc_entry in (46542, 46543);
insert into npc_spellclick_spells values
(46542, 46598, 0, 0),
(46543, 46598, 0, 0);

update creature_template set InhabitType=4 where entry=46557;

