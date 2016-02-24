

update creature_template set npcflag=16777216, unit_flags=262976, AIName="", ScriptName="npc_drowned_thunder_lizard_39464" where entry=39464;

DELETE FROM `smart_scripts` WHERE `entryorguid`=39464 AND `source_type`=0;

delete from npc_spellclick_spells where npc_entry=39464 and spell_id=80948;

update item_template set class=12, spellid_1=73945 where entry=52574;

