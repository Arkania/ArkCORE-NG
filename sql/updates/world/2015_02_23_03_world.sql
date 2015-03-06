
update creature_template set AIName="", ScriptName="boss_pit_lord_argaloth" where entry in (47120, 51350);

update creature_template set AIName="", ScriptName="npc_felflames" where entry=47829;

delete from spell_script_names where spell_id in (88954, 95173);
insert into spell_script_names values 
(88954, "spell_argaloth_consuming_darkness"),
(95173, "spell_argaloth_consuming_darkness");

delete from spell_script_names where spell_id in (88942, 95172);
insert into spell_script_names values 
(88942, "spell_argaloth_meteor_slash"),
(95172, "spell_argaloth_meteor_slash");


