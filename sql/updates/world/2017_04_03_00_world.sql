
DELETE FROM creature WHERE id=234 AND guid=4018;

DELETE FROM phase_definitions WHERE zoneId=40;
INSERT INTO phase_definitions VALUES 
(40, 0, 232, 0, 0, 683, 1, "Quest 26322, Rise of the Brotherhood, Westfall - Sentinel Hill"),
(40, 1, 226, 0, 0, 683, 0, "Quest 26322, Westfall - Sentinel Hill burn, Part 2");

DELETE FROM phase_area WHERE areaId=40;
INSERT INTO phase_area VALUES 
(40, 0, 26322, 26322, 74, 11, 1,"Quest 26322, Rise of the Brotherhood, Westfall - Sentinel Hill"),
(40, 1, 26322, 26761, 66, 11, 0,"Quest 26322, 'A Vision of the Past', Westfall - Sentinel Hill");

update creature set ModelId=26241 where id=42771;

UPDATE creature_template SET ScriptName="npc_rise_of_the_brotherhood_event_dummy_42771" WHERE entry=42771;

delete from spell_script_names where spell_id=79723;
insert into spell_script_names values 
(79723, "spell_tie_up_good_guys_79723");

update creature_text set emote=25 where entry=42749 and groupid in (0,4);

update creature_text set emote=22 where entry=42749 and groupid=3;

update creature_text set emote=5 where entry=42750 and groupid=5;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=4106;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 4106, 0, 28, 26322, 0),
(15, 4106, 1, 28, 26322, 0);

update creature set id=234, phaseId=226 WHERE id=42750 AND guid=6716;

