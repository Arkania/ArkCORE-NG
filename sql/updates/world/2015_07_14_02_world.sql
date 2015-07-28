
update creature_template set AIName="", ScriptName="npc_ascended_flameseeker" where entry=39415;
update creature_template set AIName="", ScriptName="npc_ascended_rockbreaker" where entry=40272;
update creature_template set AIName="", ScriptName="npc_ascended_waterlasher" where entry=40273;
update creature_template set AIName="", ScriptName="npc_ascended_windwalker" where entry=39414;
update creature_template set AIName="", ScriptName="npc_azureborne_guardian" where entry=39854;
update creature_template set AIName="", ScriptName="npc_azureborne_seer" where entry=39855;
update creature_template set AIName="", ScriptName="npc_azureborne_seer" where entry=40291;
update creature_template set AIName="", ScriptName="npc_azureborne_warlord" where entry=39909;
update creature_template set AIName="", ScriptName="npc_crimsonborne_guardian" where entry=39381;
update creature_template set AIName="", ScriptName="npc_crimsonborne_seer" where entry=39405;
update creature_template set AIName="", ScriptName="npc_crimsonborne_seer" where entry=40290;
update creature_template set AIName="", ScriptName="npc_crimsonborne_warlord" where entry=39626;
update creature_template set AIName="", ScriptName="npc_enslaved_burning_ember" where entry=39892;
update creature_template set AIName="", ScriptName="npc_enslaved_rock_elemental" where entry=39900;
update creature_template set AIName="", ScriptName="npc_enslaved_gronn_brute" where entry=40166;
update creature_template set AIName="", ScriptName="npc_faceless_corruptor" where entry=48844;
update creature_template set AIName="", ScriptName="npc_faceless_corruptor" where entry=40600;
update creature_template set AIName="", ScriptName="npc_faceless_corruptor" where entry=39392;
update creature_template set AIName="", ScriptName="npc_faceless_corruptor" where entry=57749;
update creature_template set AIName="", ScriptName="npc_trogg_dweller" where entry=39450;
update creature_template set AIName="", ScriptName="npc_trogg_dweller" where entry=45467;
update creature_template set AIName="", ScriptName="npc_twilight_armsmaster" where entry=40306;
update creature_template set AIName="", ScriptName="npc_twilight_armsmaster" where entry=41073;
update creature_template set AIName="", ScriptName="npc_twilight_beguiler" where entry=40167;
update creature_template set AIName="", ScriptName="npc_twilight_drake_gb" where entry=39390;
update creature_template set AIName="", ScriptName="npc_twilight_drake_gb" where entry=41095;
update creature_template set AIName="", ScriptName="npc_twilight_earthshaper" where entry=39890;
update creature_template set AIName="", ScriptName="npc_twilight_enforcer" where entry=39956;
update creature_template set AIName="", ScriptName="npc_twilight_enforcer" where entry=40448;
update creature_template set AIName="", ScriptName="npc_twilight_firecatcher" where entry=39870;
update creature_template set AIName="", ScriptName="npc_twilight_shadow_weaver" where entry=39954;
update creature_template set AIName="", ScriptName="npc_twilight_stormbreaker" where entry=39962;
update creature_template set AIName="", ScriptName="npc_twilight_thundercaller" where entry=40270;
update creature_template set AIName="", ScriptName="npc_twilight_wyrmcaller" where entry=39873;
update creature_template set AIName="", ScriptName="npc_twilight_war_mage" where entry=40268;
update creature_template set AIName="", ScriptName="npc_ascended_rockbreaker_fissure" where entry=40272;
update creature_template set AIName="", ScriptName="npc_crimsonborne_warlord_empowering_flames" where entry=41045;

delete from spell_script_names where spell_id in (76411, 82973, 90673);
insert into spell_script_names values
(76411, "spell_twilight_enforcer_meat_grinder"),
(82973, "spell_twilight_thundercaller_electric_blast"),
(90673, "spell_twilight_shadow_weaver_shadow_weave");

delete from spell_script_names where spell_id in (-50294, -49158, -49145, -33851, 58597, 69366, 74936);

update creature_text set BroadcastTextID=21960 where entry=22949 and groupid=1 and id=0;
update creature_text set BroadcastTextID=21739 where entry=22949 and groupid=3 and id=0;
update creature_text set BroadcastTextID=21736 where entry=22949 and groupid=5 and id=0;

update creature_text set BroadcastTextID=18725 where entry=19220 and groupid=3 and id=0;
update creature_text set BroadcastTextID=20042 where entry=19220 and groupid=4 and id=0;

update creature_text set sound=0 where entry=19220 and groupid=1 and id=1;





