
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Rudelführer Ivar Blutfang zurück." WHERE Id=27917;

delete from gameobject where guid in (20922, 20941, 20942);

update gameobject_template set AIName="", ScriptName="go_prison_lever_18900" where entry=18900;
update gameobject_template set AIName="", ScriptName="go_prison_door_18934" where entry=18934;
update gameobject_template set AIName="", ScriptName="go_prison_lever_18901" where entry=18901;
update gameobject_template set AIName="", ScriptName="go_prison_door_18935" where entry=18935;
update gameobject_template set AIName="", ScriptName="go_prison_lever_101811" where entry=101811;
update gameobject_template set AIName="", ScriptName="go_prison_door_18936" where entry=18936;
update gameobject_template set AIName="", ScriptName="go_courtyard_door_18895" where entry=18895;

delete from gossip_menu_option where menu_id in (21213, 21214) and id=0;
insert into gossip_menu_option value
(21213, 0, 0, "Follow me and I'll open the courtyard door for you.",1331, 1, 1, 0, 0, 0, 0, 0, "", 0),
(21214, 0, 0, "Follow me and I'll open the courtyard door for you.",1331, 1, 1, 0, 0, 0, 0, 0, "", 0);

update creature set spawntimesecs=7200 where guid=145321;

delete from script_waypoint where entry in (3849, 3850) and pointid in (13, 14, 15);
insert into script_waypoint values
(3849, 13, -241.13, 2154.56, 90.624, 8000, "SAY_POST2_DOOR_AD"),
(3849, 14, -241.13, 2154.56, 90.624, 2000, "SAY_POST2_DOOR_AD"),
(3849, 15, -241.13, 2154.56, 90.624, 25000, "SAY_POST2_DOOR_AD"),
(3850, 13, -241.13, 2154.56, 90.624, 8000, "SAY_POST_DOOR_AS"),
(3850, 14, -241.13, 2154.56, 90.624, 2000, "SAY_POST_DOOR_AS"),
(3850, 15, -241.13, 2154.56, 90.624, 25000, "SAY_POST_DOOR_AS");

-- http://www.wowhead.com/quest=13166/the-battle-for-the-ebon-hold
update creature_template set AIName="", ScriptName="npc_highlord_darion_mograine_31084" where entry=31084;

update spell_target_position set target_position_x=-9056.42, target_position_y=441.39, target_position_z=93.05, target_orientation=0.61 where id=17334;

-- fix some console errors

delete from creature_equip_template where entry in (190001, 3432314, 3432314);

delete from creature_addon where guid in (35869, 35639, 34621);

delete from linked_respawn where guid in (145314, 145323, 145324, 145407, 145408, 199725);

delete from creature_queststarter where id=3432314 and quest=25179;

delete from creature_questender where id=3432314 and quest=25179;

