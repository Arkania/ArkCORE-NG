
-- duskhaven > exodus..

UPDATE gameobject SET phaseId=186 WHERE guid=167137;

UPDATE creature SET phaseId=186 WHERE id=37805;

UPDATE creature SET phaseId=186 WHERE guid=251528;

UPDATE creature SET phaseId=186 WHERE guid=251527;

UPDATE creature SET phaseId=186, spawntimesecs=120, spawndist=0, MovementType=0 WHERE guid=251553;

UPDATE creature_template SET ScriptName="npc_crash_survivor_37067" WHERE entry=37067;

UPDATE creature_template SET ScriptName="npc_swamp_crocolisk_37078" WHERE entry=37078;

DELETE FROM creature_text WHERE entry=37065;
INSERT INTO creature_text VALUES 
(37065, 0, 0, "Just in time, $N.  Here come the Forsaken.", 12, 0, 100, 0, 0, 19605, "", 37410),
(37065, 1, 0, "You will come no further, Forsaken scum!  By the war banner of the ancient Greymane clan, I expel you from our ancestral lands!", 14, 0, 100, 0, 0, 19606, "Prince Liam Greymane", 37411);

delete from creature_equip_template where entry=37805;
insert into creature_equip_template values 
(37805, 1, 25160, 0, 0);

delete from creature_equip_template where entry=37806;
insert into creature_equip_template values 
(37806, 1, 25160, 0, 0);

delete from creature_equip_template where entry=37808;
insert into creature_equip_template values 
(37808, 1, 57214, 0, 0);

DELETE FROM creature_text WHERE entry=36294 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(36294, 1, 0, "You puny thief!  Koroth find you!  Koroth smash your face in!", 14, 0, 100, 0, 0, 0, "Koroth the Hillbreaker", 36913);

UPDATE gameobject_template SET name="Koroth's Banner", ScriptName="go_koroths_banner_201594" WHERE entry=201594;

UPDATE gameobject SET spawntimesecs=120 WHERE guid=167136;


