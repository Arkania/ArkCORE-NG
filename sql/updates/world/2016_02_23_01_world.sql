
-- spawned from script
delete from creature where id=39465;

delete from npc_spellclick_spells where npc_entry=39464 and spell_id=73945;
insert into npc_spellclick_spells values
(39464, 73945, 1, 0);

