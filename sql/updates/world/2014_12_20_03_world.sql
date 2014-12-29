
-- this spell_area is alpha for spell 3, 4, dungeon2 and see_quest_invis_1/apply_quest_invis_2
DELETE FROM `spell_area` WHERE `spell`=79489 AND `area`=40 AND `quest_start`=0 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79489, 40, 0, 26232, 0, 0, 2, 1, 64, 9);

DELETE FROM `spell_area` WHERE `spell`=79229 AND `area`=40 AND `quest_start`=26215 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79229, 40, 26215, 26232, 0, 0, 2, 1, 74, 9);

DELETE FROM `spell_area` WHERE `spell`=79341 AND `area`=40 AND `quest_start`=26232 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79341, 40, 26232, 26236, 0, 0, 2, 1, 66, 11);

DELETE FROM `spell_area` WHERE `spell`=79498 AND `area`=40 AND `quest_start`=26236 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79498, 40, 26236, 26761, 0, 0, 2, 1, 64, 11);

DELETE FROM `spell_area` WHERE `spell`=101419 AND `area`=40 AND `quest_start`=26279 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(101419, 40, 26279, 26761, 0, 0, 2, 1, 74, 11);

DELETE FROM `spell_area` WHERE `spell`=79550 AND `area`=40 AND `quest_start`=26279 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79550, 40, 26279, 26761, 0, 0, 2, 1, 74, 11);

DELETE FROM `spell_area` WHERE `spell`=79346 AND `area`=40 AND `quest_start`=26279 AND `aura_spell`=0 AND `gender`=2 AND `racemask`=0;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(79346, 40, 26279, 26761, 0, 0, 2, 1, 74, 11);

delete from spell_area where spell=65141 and area in (108,109);

update creature_template set faction_A=15,faction_H=15,npcflag=2,AIName="", ScriptName="npc_two_shoued_lou_alive" where entry=42405;
update creature_template set faction_A=15,faction_H=15,npcflag=2 where entry=42560;
update creature_template_addon set auras="79343 79372 29266" where entry=42560;

update creature_template set AIName="", ScriptName="npc_shadowy_figure" where entry=42515;

delete from creature_queststarter where id=42498 and quest=26229;
insert into creature_queststarter values (42498,26229);

update creature_template set faction_A=15,faction_H=15,npcflag=2 where entry=42498;

update creature set phaseMask=1 where id in (42558,42559,42386,42384,42560);
