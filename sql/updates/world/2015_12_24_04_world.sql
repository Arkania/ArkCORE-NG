
-- hyjal - hatchery
update creature_template set AIName="", ScriptName="npc_farden_talonshrike_40578" where entry=40578;
update creature_template set AIName="", ScriptName="vehicle_avianas_guardian_39710" where entry in (39710, 40719);

delete from spell_script_names where spell_id in (75935, 75943);
insert into spell_script_names values
(75935, "spell_mount_75935"),
(75943, "spell_mount_75935");

UPDATE quest_template SET PrevQuestId=25560 WHERE Id=29177;

delete from creature_text where entry=40719;
insert into creature_text values
(40719, 0, 0, "Press Flap to Flap Your Wings!", 42, 0, 100, 0, 0, 0, "", 40557);



