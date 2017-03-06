
-- fix issue #133
UPDATE creature_template SET gossip_menu_id=0, npcflag=16777216, AIName="", ScriptName="npc_drowning_watchman_36440" WHERE entry=36440;
update creature_template_addon set auras=68730 where entry=36440;

delete from npc_spellclick_spells where npc_entry=36440 and spell_id=68735;
insert into npc_spellclick_spells values
(36440, 68735, 1, 0);

delete from creature_text where entry=36440 and groupid=0;
insert into creature_text values
(36440, 0, 0, "Thank you... *gasp*   I owe you my life.", 12, 0, 100, 0, 0, 0, "", 36417),
(36440, 0, 1, "I... I thought I was a goner.  Thanks.", 12, 0, 100, 0, 0, 0, "", 36418),
(36440, 0, 2, "The land gave way from under our feet...  I thought I was dead.  I owe you one.", 12, 0, 100, 0, 0, 0, "", 36419);

