
update version set db_version="ArkDB 7.9.11 - 2016-JAN-01 for ArkCORE4 NG";

UPDATE creature_template SET InhabitType=4 WHERE entry=53394;

update npc_trainer set reqlevel=20 where spell=57755;

delete from npc_spellclick_spells where npc_entry=52359 and spell_id=96847;


