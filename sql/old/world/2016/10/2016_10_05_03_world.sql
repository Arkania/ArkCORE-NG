
DELETE FROM creature WHERE id=34874 AND guid=16744;
INSERT INTO creature VALUES 
(16744, 34874, 648, 0, 0, 1, "384 ", 29472, 0, -8435.33, 1316.88, 102.632, 0.959931, 300, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=35054 AND guid=16745;
INSERT INTO creature VALUES 
(16745, 35054, 648, 0, 0, 1, "384 ", 29555, 1, -8377.3, 1335.13, 102.397, 4.41568, 300, 0, 0, 0, 0, 0, 0, 0, 0);

UPDATE creature SET phaseIds="383 384 " WHERE guid=13300;

delete from creature where guid=248973 and id=37680;

UPDATE creature SET phaseIds="378 379 380 381 382 383 " WHERE guid=245821;

DELETE FROM gameobject WHERE id=201745;
	
UPDATE creature_template SET minlevel=5, maxlevel=5, faction=2204, unit_flags=32776 WHERE entry=37598;

UPDATE creature_template SET faction=2204, unit_flags=33554688 WHERE entry=37599;

delete from event_scripts where id=201734;

UPDATE gameobject_template SET data2=0 WHERE entry=201734;

delete from creature where id=37599;

UPDATE creature_template SET npcflag=16777219 WHERE entry=37598;
UPDATE creature_template SET npcflag=0 WHERE entry=37599;

delete from npc_spellclick_spells where npc_entry=37598;
insert into npc_spellclick_spells values 
(37598, 46598, 1, 0);

delete from npc_spellclick_spells where npc_entry=37599;
insert into npc_spellclick_spells values 
(37599, 46598, 1, 0);

delete from vehicle_template_accessory where entry = 37598;
insert into vehicle_template_accessory values 
(37598, 37599, 0, 1, "Gasbot", 6, 30000),
(37598, 37599, 1, 1, "Gasbot", 6, 30000),
(37598, 37599, 2, 1, "Gasbot", 6, 30000),
(37598, 37599, 3, 1, "Gasbot", 6, 30000);

UPDATE creature_template SET ScriptName="npc_gasbot_37598" WHERE entry=37598;

DELETE FROM creature_template_addon WHERE entry=37598;

UPDATE creature_template SET InhabitType=4 WHERE entry=37599;

DELETE FROM creature_template_addon WHERE entry=37599;
INSERT INTO creature_template_addon VALUES 
(37599, 0, 0, 50331648, 1, 0, "");

UPDATE gameobject_template SET ScriptName="go_447_fire_201745" WHERE entry=201745;

UPDATE gameobject_template SET ScriptName="go_gasbot_control_panel_201736" WHERE entry=201736;


