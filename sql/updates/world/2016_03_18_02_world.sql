
-- quest 14279 Flash Heal
UPDATE quest_template SET RequiredSpell=2061, Method=2, Flags=524288 WHERE Id=14279;

update gossip_menu_option set option_id=5 where menu_id=10700 and id=0;

delete from spell_script_names where spell_id=2061;
insert into spell_script_names values
(2061, "spell_pri_flash_heal_2061");

