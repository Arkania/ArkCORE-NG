
-- fix issue #241
delete from npc_spellclick_spells where npc_entry=47297;
insert into npc_spellclick_spells values
(47297, 46598, 1, 0);

DELETE FROM creature_template_addon WHERE entry=42693;
INSERT INTO creature_template_addon VALUES 
(42693, 0, 0, 50331648, 1, 0, "");

