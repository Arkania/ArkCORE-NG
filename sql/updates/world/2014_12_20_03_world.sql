

delete from spell_area where spell=79489 and area=40;
insert into spell_area (spell,area,quest_end,gender,autocast,quest_end_status) values
(79489,40,26232,2,1,9); -- detect quest invis 0		Lou's Parting Thoughts

delete from spell_area where spell=79229 and area=40;
insert into spell_area (spell,area,quest_start,quest_end,gender,autocast,quest_start_status,quest_end_status) values
(79229,40,26215,26232,2,1,8,9); -- detect quest invis 1		Lou's Parting Thoughts

delete from spell_area where spell=79341 and area=40;
insert into spell_area (spell,area,quest_start,quest_end,gender,autocast,quest_start_status,quest_end_status) values
(79341,40,26232,26236,2,1,72,11); -- detect quest invis 2		Lou's Parting Thoughts  TO  Shakedown at the Saldean's

delete from spell_area where spell=79498 and area=40;
insert into spell_area (spell,area,quest_start,quest_end,gender,autocast,quest_start_status,quest_end_status) values
(79498,40,26215,0,2,1,43,0); -- detect quest invis 3 		Meet Two-Shoed Lou (and open end)

update creature_template set faction_A=15,faction_H=15,npcflag=2,AIName="", ScriptName="npc_two_shoued_lou_alive" where entry=42405;
update creature_template set faction_A=15,faction_H=15 where entry=42560;
update creature_template_addon set auras="79343 79372 29266" where entry=42560;

update creature_template set AIName="", ScriptName="npc_shadowy_figure" where entry=42515;

delete from creature_queststarter where id=42498 and quest=26229;
insert into creature_queststarter values (42498,26229);

update creature_template set faction_A=15,faction_H=15,npcflag=2 where entry=42498;

update creature set phaseMask=1 where id in (42558,42559,42386,42384,42560);
