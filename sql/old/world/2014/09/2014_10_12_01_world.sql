
SET NAMES 'utf8';

delete from spell_threat where entry=72;

delete from battleground_template where id in (100,101,102);

-- SmartAIMgr::LoadSmartAIFromDB: Creature entry (3547600) does not exist, skipped loading.
delete from smart_scripts where entryorguid=3547600 and source_type=0;

-- SmartAIMgr::LoadSmartAIFromDB: Creature entry (47847) does not exist, skipped loading.  are entry of 5.xx
delete from smart_scripts where entryorguid in (47847,59073,67789,68480,68481,72870);

-- SmartAIMgr::LoadSmartAIFromDB: Creature guid (399978) does not exist, skipped loading.
delete from smart_scripts where entryorguid in (-399978,-399977,-113880);

delete from spell_script_names where ScriptName="spell_igb_rocket_pack" and spell_id=68721;
insert into spell_script_names values (68721,"spell_igb_rocket_pack");

delete from spell_script_names where ScriptName="spell_igb_rocket_pack_useable" and spell_id=70348;
insert into spell_script_names values (70348,"spell_igb_rocket_pack_useable");

delete from spell_script_names where ScriptName="spell_igb_on_gunship_deck" and spell_id in (70120,70121);
insert into spell_script_names values (70120,"spell_igb_on_gunship_deck");
insert into spell_script_names values (70121,"spell_igb_on_gunship_deck");

delete from spell_script_names where ScriptName="spell_igb_periodic_trigger_with_power_cost" and spell_id in (69470,69487);
insert into spell_script_names values (69470,"spell_igb_periodic_trigger_with_power_cost");
insert into spell_script_names values (69487,"spell_igb_periodic_trigger_with_power_cost");

delete from spell_script_names where ScriptName="spell_igb_cannon_blast" and spell_id in (69399,70172);
insert into spell_script_names values (69399,"spell_igb_cannon_blast");
insert into spell_script_names values (70172,"spell_igb_cannon_blast");

delete from spell_script_names where ScriptName="spell_igb_incinerating_blast" and spell_id in (69402,70175);
insert into spell_script_names values (69402,"spell_igb_incinerating_blast");
insert into spell_script_names values (70175,"spell_igb_incinerating_blast");

delete from spell_script_names where ScriptName="spell_igb_overheat" and spell_id=69487;
insert into spell_script_names values (69487,"spell_igb_overheat");

delete from spell_script_names where ScriptName="spell_igb_below_zero" and spell_id=69705;
insert into spell_script_names values (69705,"spell_igb_below_zero");

delete from spell_script_names where ScriptName="spell_igb_teleport_to_enemy_ship" and spell_id=70104;
insert into spell_script_names values (70104,"spell_igb_teleport_to_enemy_ship");

delete from spell_script_names where ScriptName="spell_igb_burning_pitch_selector" and spell_id in (70397,70403);
insert into spell_script_names values (70397,"spell_igb_burning_pitch_selector");
insert into spell_script_names values (70403,"spell_igb_burning_pitch_selector");

delete from spell_script_names where ScriptName="spell_igb_burning_pitch" and spell_id in (71335,71339);
insert into spell_script_names values (71335,"spell_igb_burning_pitch");
insert into spell_script_names values (71339,"spell_igb_burning_pitch");

delete from spell_script_names where ScriptName="spell_igb_rocket_artillery" and spell_id in (69678,70609);
insert into spell_script_names values (69678,"spell_igb_rocket_artillery");
insert into spell_script_names values (70609,"spell_igb_rocket_artillery");

delete from spell_script_names where ScriptName="spell_igb_rocket_artillery_explosion" and spell_id=69679;
insert into spell_script_names values (69679,"spell_igb_rocket_artillery_explosion");

delete from spell_script_names where ScriptName="spell_igb_gunship_fall_teleport" and spell_id=67335;
insert into spell_script_names values (67335,"spell_igb_gunship_fall_teleport");

delete from spell_script_names where ScriptName="spell_igb_check_for_players" and spell_id=70331;
insert into spell_script_names values (70331,"spell_igb_check_for_players");

delete from spell_script_names where ScriptName="spell_igb_teleport_players_on_victory" and spell_id=72340;
insert into spell_script_names values (72340,"spell_igb_teleport_players_on_victory");

-- http://www.wowhead.com/npc=43391
update creature_template set AIName="",ScriptName="npc_millhouse_manastorm_sc" where entry=43391;

delete from spell_script_names where ScriptName="spell_gen_eject_all_passengers" and spell_id in (50630,63109,68576);
insert into spell_script_names values (50630,"spell_gen_eject_all_passengers");
insert into spell_script_names values (63109,"spell_gen_eject_all_passengers");
insert into spell_script_names values (68576,"spell_gen_eject_all_passengers");

delete from spell_script_names where ScriptName="spell_pal_judgement" and spell_id=20271;
insert into spell_script_names values (20271,"spell_pal_judgement");

delete from spell_script_names where ScriptName="spell_pal_templar_s_verdict" and spell_id=85256;
insert into spell_script_names values (85256,"spell_pal_templar_s_verdict");

delete from spell_script_names where ScriptName="spell_magmaw_massive_crash" and spell_id=88253;
insert into spell_script_names values (88253,"spell_magmaw_massive_crash");

delete from spell_script_names where ScriptName="spell_twilight_shadow_weaver_shadow_weave" and spell_id=90673;
insert into spell_script_names values (90673,"spell_twilight_shadow_weaver_shadow_weave");

delete from spell_script_names where ScriptName="spell_twilight_thundercaller_electric_blast" and spell_id=82973;
insert into spell_script_names values (82973,"spell_twilight_thundercaller_electric_blast");

delete from spell_script_names where ScriptName="spell_throngus_pick_weapon" and spell_id=75000;
insert into spell_script_names values (75000,"spell_throngus_pick_weapon");

delete from spell_script_names where ScriptName="spell_erudax_shadow_gale" and spell_id=75664;
insert into spell_script_names values (75664,"spell_erudax_shadow_gale");

delete from spell_script_names where ScriptName="spell_bad_intentions" and spell_id=83113;
insert into spell_script_names values (83113,"spell_bad_intentions");

update creature_template set QuestItem1=0 where QuestItem1=4161536;

update creature_equip_template set id=1 where id=0;

update creature_template set faction_A=1216,faction_H=1216 where entry=37234;
update creature_template set faction_A=1214,faction_H=1214,npcflag=3 where entry=37364;
update creature_template set faction_A=1214,faction_H=1214,npcflag=3 where entry=37346;
update creature_template set npcflag=0 where entry=37269;
update creature_template set exp=1 where entry=22620;
update creature_template set npcflag=641 where entry=22651;
update creature_template set npcflag=3201 where entry=22652;
update creature_template set npcflag=3201 where entry=22660;
update creature_template set npcflag=641 where entry=22655;
update creature_template set type=6 where entry=3865;
update creature_template set npcflag=641 where entry=22654;
update creature_template set type=9 where entry=643;
update creature_template set AIName="" where entry=42698;
update creature_template set exp=2 where entry=49664;
update creature_template set npcflag=3 where entry=37369;
update creature_template set exp=1 where entry=22709;
update creature_template set exp=1 where entry=22705;
update creature_template set npcflag=3 where entry=37268;
update creature_template set faction_A=1216,faction_H=1216 where entry=37450;
update creature_template set faction_A=1214,faction_H=1214 where entry=37451;
update creature_template set faction_A=1214,faction_H=1214 where entry=37251;
update creature_template set faction_A=1216,faction_H=1216 where entry=37250;
update creature_template set npcflag=3 where entry=37335;
update creature_template set npcflag=3 where entry=37483;
update creature_template set AIName="" where entry=29021;
update creature_template set AIName="" where entry=29024;
update creature_template set AIName="" where entry=29022;
update creature_template set AIName="" where entry=29023;





















