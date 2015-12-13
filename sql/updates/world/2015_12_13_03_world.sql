
-- should be dead
update creature_template_addon set auras="29266" where entry=42259;

-- spawned by spell
delete from creature where id in (46940, 46941, 46942, 46943);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Stellvertreter Rainer hat wiederholt um Hilfe gebeten...", QuestGiverTargetName_loc3="Stellvertreter Rainer" WHERE Id=239;

delete from creature_queststarter where id=963 and quest=239;
