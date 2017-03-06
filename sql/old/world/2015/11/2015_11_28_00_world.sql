
-- quest 13949
UPDATE locales_quest SET EndText_loc3="" WHERE Id=13949;
UPDATE quest_template SET RequiredNpcOrGo1=53613, RequiredNpcOrGoCount1=1 WHERE Id=13949;
UPDATE quest_template SET RequiredSourceItemId1=0, RequiredSourceItemCount1=0, RequiredItemId1=46714, RequiredItemCount1=1 WHERE Id=13949;

update creature_template set gossip_menu_id=10514, AIName="", ScriptName="npc_halga_bloodeye_34258" where entry=34258;

update gossip_menu_option set OptionBroadcastTextID=34629, npc_option_npcflag=1, option_id=1 where  menu_id=10514 and id=0;

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=10514 and ConditionTypeOrReference=9 and ConditionValue1=13949;
insert into conditions values
(15, 10514, 0, 0, 0, 9, 0, 13949, 0, 0, 0, 0, 0, "", "");

delete from creature where id in (34430, 34432);

delete from creature where guid in (117197, 117198, 117199, 117200, 117201, 117202, 117203, 117204, 117205, 117207, 117208, 117209);
delete from creature where guid in (117213, 117217, 117218, 117219, 117220, 117221, 117222, 117223);

delete from spell_script_names where spell_id=65485;
insert into spell_script_names values (65485, "spell_mount_caravan_kodo_cue_65485");

delete from spell_script_names where spell_id=101668;
insert into spell_script_names values (101668, "spell_calling_the_caravan_101668");

delete from creature_text where entry=34258 and groupid in (0, 1);
delete from creature_text where entry=34438 and groupid in (0);
delete from creature_text where entry=34431 and groupid in (0);
insert into creature_text values
(34258, 0, 0, "Mount up, $N! Do not fail me.", 12, 0, 100, 0, 0, 0, "", 34630),
(34258, 1, 0, "Head 'em up! Move 'em out!", 12, 0, 100, 0, 0, 0, "", 34626),
(34438, 0, 0, "Defend the Caravan Kodo!", 42, 0, 100, 0, 0, 0, "", 34625),
(34431, 0, 0, "Excellent work! I'll unload the goods. You should check in with Kranal Fiss.", 12, 0, 100, 0, 0, 0, "", 34667);

update creature_template set AIName="", ScriptName="npc_lead_caravan_kodo_34430" where entry=34430;
update creature_template set AIName="", ScriptName="npc_balgor_whipshank_34431" where entry=34431;
update creature_template set AIName="", ScriptName="npc_razormane_raider_34487" where entry=34487;
update creature_template set spell1=65479, AIName="", ScriptName="npc_riding_shotgun_34438" where entry=34438;

delete from npc_spellclick_spells where npc_entry=34430;
insert into npc_spellclick_spells values (34430, 65485, 1, 0);

-- console error
delete from creature_addon where guid=88407;

delete from creature where id=5907 and guid=129239;
delete from creature where id=34523 and guid=116558;
delete from creature where id=34346 and guid=138742;

