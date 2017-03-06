

UPDATE creature_template SET faction=2204, unit_flags=8, unit_flags2=67584, VehicleId=582 WHERE entry=37179;

delete from npc_spellclick_spells where npc_entry=37179;
insert into npc_spellclick_spells values 
(37179, 70016, 0, 0);

UPDATE creature_template SET AIName="", ScriptName="npc_coach_crosscheck_37106" WHERE entry=37106;

DELETE FROM creature_text WHERE entry=37106;
INSERT INTO creature_text VALUES 
(37106, 0, 0, "You gotta hurry, kid. We gotta get you into the game. But first, we gotta get the parts for that shredder!", 12, 0, 100, 5, 0, 0, "", 49025),
(37106, 1, 0, "Get into that shredder and win the game. The Bilgewater Cartel's counting on you!", 12, 0, 100, 0, 0, 0, "Coach Crosscheck Say", 49026),
(37106, 2, 0, "You got the juice, kid. That's for sure! Too bad that dragon had to come and ruin everything. No matter. You made us proud. Now get back to headquarters.", 12, 0, 100, 4, 0, 0, "Coach Crosscheck", 49027),
(37106, 3, 0, "Why did the ground start shaking?", 41, 0, 100, 0, 0, 0, "quest", 0);

UPDATE creature_template SET AIName="", ScriptName="npc_bilgewater_buccaneer_37179" WHERE entry=37179;

UPDATE creature_template SET AIName="", ScriptName="npc_steamwheedle_shark_37114" WHERE entry=37114;

UPDATE creature_template SET gossip_menu_id=10884 WHERE entry=37106;

