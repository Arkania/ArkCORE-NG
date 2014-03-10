
-- this part is to append arkdb database strukture to the old NG structure.
-- this can only run one's !!!

ALTER TABLE creature_template ADD COLUMN trainer_spell INT(11) UNSIGNED NOT NULL Default '0' AFTER trainer_type;
ALTER TABLE creature_template ADD COLUMN equipment_id INT(11) UNSIGNED NOT NULL Default '0' AFTER RegenHealth;
ALTER TABLE command ADD COLUMN security TINYINT(3) UNSIGNED NOT NULL Default '0' AFTER name;
ALTER TABLE quest_template ADD COLUMN RequiredSpellCast1 MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER RequiredSpell;
ALTER TABLE quest_template ADD COLUMN RequiredSpellCast2 MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER RequiredSpellCast1;
ALTER TABLE quest_template ADD COLUMN RequiredSpellCast3 MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER RequiredSpellCast2;
ALTER TABLE quest_template ADD COLUMN RequiredSpellCast4 MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER RequiredSpellCast3;
insert into creature_equip_template values (2,1,5956,0,0);
ALTER TABLE quest_template ADD COLUMN StartScript MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER OfferRewardEmoteDelay4;
ALTER TABLE quest_template ADD COLUMN CompleteScript MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER StartScript;
RENAME TABLE game_event_seasonal_questrelation TO game_event_seasonal_queststarter
ALTER TABLE lfg_dungeon_rewards ADD COLUMN firstMoneyVar INT(10) NOT NULL Default '0' AFTER firstQuestId;
ALTER TABLE lfg_dungeon_rewards ADD COLUMN firstXpVar INT(10) NOT NULL Default '0' AFTER firstMoneyVar;
ALTER TABLE lfg_dungeon_rewards ADD COLUMN otherMoneyVar INT(10) NOT NULL Default '0' AFTER otherQuestId;
ALTER TABLE lfg_dungeon_rewards ADD COLUMN otherXpVar INT(10) NOT NULL Default '0' AFTER otherMoneyVar;

ALTER TABLE spell_area ADD COLUMN quest_start_active TINYINT(1) UNSIGNED NOT NULL Default '0' AFTER quest_start;
-- missig.. this column is primary key 4!! pls change it manuelly

RENAME TABLE areatrigger_involvedrelation TO areatrigger_questender

ALTER TABLE transports ADD COLUMN period MEDIUMINT(8) UNSIGNED NOT NULL Default '0' AFTER name;

-- now some tables are still missing for NG
-- for fixing this, copy missing tables from NG database to Arkdb 

