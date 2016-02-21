
DELETE FROM spell_area WHERE area=5420 ;
DELETE FROM spell_area WHERE area=5599;

DELETE FROM spell_area WHERE spell=59073 AND area=5420;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(59073, 5420, 27003, 27922, 0, 0, 2, 1, 74, 11);

DELETE FROM spell_area WHERE spell=59073 AND area=5599;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(59073, 5599, 27003, 27922, 0, 0, 2, 1, 74, 11);

DELETE FROM spell_area WHERE spell=49416 AND area=5599;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(49416, 5599, 27003, 27922, 0, 0, 2, 1, 74, 11);

delete from creature_text where entry=46538 and groupid in (0);
insert into creature_text values
(46538, 0, 0, "Ahoy!", 12, 0, 100, 70, 0, 21174, "", 46715);

delete from phase_area where areaId=5420;
insert into phase_area values
(5420, 0, 27003, 27922, 74, 64, 0, "escape to uldum, video part 2");

delete from phase_definitions where zoneId=5420 and entry=0;
insert into phase_definitions values
(5420, 0, 2, 0, 0, 0, 0, "escape to uldum, video part 2");

