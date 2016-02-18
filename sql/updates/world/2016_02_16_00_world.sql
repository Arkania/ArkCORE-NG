
DELETE FROM spell_area WHERE spell=89270 AND area=980;
INSERT INTO spell_area (spell, area, quest_start, quest_end, aura_spell, racemask, gender, autocast, quest_start_status, quest_end_status) VALUES 
(89270, 980, 27003, 27922, 0, 0, 2, 1, 74, 11);

update creature_template_addon set auras="80797" where entry=46514;


