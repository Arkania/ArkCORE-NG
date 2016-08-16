
DELETE FROM creature WHERE guid IN (250085, 245774, 245820);
INSERT INTO creature VALUES 
(250085, 34668, 648, 1, 192, 0, 0, -7857.33, 1842.98, 7.50448, 6.00393, 300, 0, 0, 102, 0, 0, 0, 0, 0), 
(245774, 34668, 648, 1, 15, 0, 0, -8423.85, 1365.88, 104.677, 4.68622, 300, 0, 0, 102, 0, 0, 0, 0, 0), 
(245820, 34668, 648, 1, 240, 0, 0, -8423.26, 1324.7, 101.912, 1.59908, 300, 0, 0, 102, 0, 0, 0, 0, 0);

delete from creature where id=37598;

delete from gameobject where id in (202850);

update gameobject set phaseMask=112 where guid in (168248, 168249, 168251);

update gameobject set phaseMask=127 where guid in (168606, 168210, 168366, 168368, 168403, 168402, 168405, 168373, 168212, 168370, 168214, 168376, 168199, 168217, 168369);

update gameobject set phaseMask=127 where guid in (168372, 168407, 168367, 168406, 168404, 168493, 168211, 168435, 168218, 168375, 168215, 168374, 168216, 168213, 168371);

UPDATE creature SET phaseMask=1 WHERE id=37203;

UPDATE creature SET modelid=11686 WHERE guid=248976;

UPDATE gameobject SET phaseMask=64 WHERE id=207751;

UPDATE creature SET phaseMask=64 WHERE id=37602;

UPDATE creature SET phaseMask=120 WHERE id=37708;
UPDATE creature SET phaseMask=120 WHERE id=37709;
UPDATE creature SET phaseMask=120 WHERE id=37710;

UPDATE gameobject SET phaseMask=112 WHERE id=201736;
UPDATE gameobject SET phaseMask=112 WHERE id=188215 and guid=168405;

UPDATE creature SET phaseMask=31 WHERE id=35239;
UPDATE creature SET phaseMask=31 WHERE id=48494;
UPDATE creature SET phaseMask=31 WHERE id=48496;
UPDATE creature SET phaseMask=31 WHERE id=49150;

DELETE FROM creature_text WHERE entry=34692;
INSERT INTO creature_text VALUES 
(34692, 0, 0, "I really should charge you for that.", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36721),
(34692, 0, 1, "Light be with you... for the very low price of a one silver tithe!", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36722),
(34692, 0, 2, "Nothing wrong with a little drive-by fortitude!", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36723),
(34692, 0, 3, "Hope you don't mind the extra fortitude, boss-$G man : lady;.", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36724),
(34692, 0, 4, "That one's free of charge, $G sir : ma'am;.", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36725),
(34692, 0, 5, "I was wondering when I'd see you again, $N.", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36726),
(34692, 0, 6, "It's not much, but it just might keep your green skin intact.", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36727),
(34692, 0, 7, "Just wanted to let you know that we're all counting on you!", 12, 0, 100, 0, 0, 0, "Sister Goldskimmer", 36728);

DELETE FROM creature_text WHERE entry=34830 AND groupid=0 AND id=7;
INSERT INTO creature_text VALUES 
(34830, 0, 7, "Ouch! Dat hurt!", 12, 0, 100, 5, 0, 12007, "Defiant Troll", 40314);

UPDATE creature_text SET emote=5, sound=12007 WHERE entry=34830 AND groupid=0 AND id=3;

UPDATE creature_text SET emote=5, sound=12007 WHERE entry=34830 AND groupid=0 AND id=5;

UPDATE creature_text SET emote=5, sound=12007 WHERE entry=34830 AND groupid=0 AND id=1;

DELETE FROM creature_text WHERE entry=37804;
INSERT INTO creature_text VALUES 
(37804, 0, 0, "Drink Kaja'Cola!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37246),
(37804, 0, 1, "Take the Kaja'Cola Taste Test Challenge!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37403),
(37804, 0, 2, "Kaja'Cola! It gives you IDEAS!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37404),
(37804, 0, 3, "Kaja'Cola! Jinxy the Weasel says, Drink it... or else!", 14, 0, 100, 0, 0, 0, "", 37405),
(37804, 0, 4, "Kaja'Cola is a proud sponsor of the Bilgewater Buccaneers!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37406),
(37804, 0, 5, "Kaja'Cola! When your tinkering has to be second to none!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37407);

DELETE FROM creature_text WHERE entry=34872 AND groupid=3 AND id=0;
INSERT INTO creature_text VALUES 
(34872, 3, 0, "You! Yes, you! Get back to work!", 14, 0, 100, 0, 0, 0, "Foreman Dampwick", 35907);

DELETE FROM creature_text WHERE entry=35304;
INSERT INTO creature_text VALUES 
(35304, 0, 0, "Hey deres, boss.", 14, 0, 100, 3, 0, 0, "Brute Enforcer", 40213),
(35304, 0, 1, "Yous be careful. Trolls bad!", 14, 0, 100, 1, 0, 0, "Brute Enforcer", 40214),
(35304, 0, 2, "Why we not gets no Kaja'Cola? We wants to have ideas!", 14, 0, 100, 6, 0, 0, "Brute Enforcer", 40215),
(35304, 0, 3, "We watch dem trolls real good!", 14, 0, 100, 1, 0, 0, "Brute Enforcer", 40216),
(35304, 0, 4, "Trolls been saying stuff, boss.", 14, 0, 100, 1, 0, 0, "Brute Enforcer", 40217),
(35304, 0, 5, "You wants us go bash bad trolls?", 14, 0, 100, 6, 0, 0, "Brute Enforcer", 40218),
(35304, 0, 6, "Dem trolls wanna fight?", 14, 0, 100, 6, 0, 0, "Brute Enforcer", 40219);

DELETE FROM creature_text WHERE entry=34872 AND groupid=4 AND id=0;
INSERT INTO creature_text VALUES 
(34872, 4, 0, "Worthless! You're all just worthless! I'm afraid we're going to have dump you all into the Maelstrom!", 14, 0, 100, 0, 0, 0, "Foreman Dampwick", 35911);







