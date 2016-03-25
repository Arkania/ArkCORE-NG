
-- fix issue #112 part 1
update creature_template set gossip_menu_id=12180 where entry=48619;

-- fix issue #112 part 2
update creature_template set AIName="", ScriptName="npc_vile_fin_puddlejumper_1543" where entry=1543;
update creature_template set AIName="", ScriptName="npc_vile_fin_minor_oracle_1544" where entry=1544;

update creature_template set AIName="", ScriptName="npc_captured_vile_fin_puddlejumper_38923" where entry=38923;
update creature_template set AIName="", ScriptName="npc_captured_vile_fin_minor_oracle_39078" where entry=39078;

update creature_template set AIName="", ScriptName="npc_sedrick_calston_38925" where entry=38925;

delete from spell_script_names where spell_id=73108;
insert into spell_script_names values
(73108, "spell_murloc_leash_73108");

UPDATE creature_template SET KillCredit1=0 WHERE entry=39078;

delete from item_script_names where Id=52059;
insert into item_script_names values
(52059, "item_murloc_leash_52059");

-- fix issue #112 part 3
update gossip_menu_option set OptionBroadcastTextID=39176, option_id=3, npc_option_npcflag=4739 where menu_id=11159 and id=0;

