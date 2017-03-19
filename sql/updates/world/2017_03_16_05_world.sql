
-- fix issues #242
DELETE FROM creature_text WHERE entry=41379;
INSERT INTO creature_text VALUES 
(41379, 0, 0, "Ha ha ha ha ha! The heroes have made it to the glorious finale. I take it you are in good spirits? Prepared for the final battle? Then gaze now upon my ultimate creation! RISE, SISTER!", 14, 0, 100, 1, 0, 20066, "Lord Victor Nefarius Say", 41762),
(41379, 1, 0, "Cowards! Face the brood mother or face DIRE consequences!", 14, 0, 0, 0, 0, 23372, "VO_BD_Nefarian_MaloriakIntro0", 43520),
(41379, 2, 0, "Behold the brood mother, Onyxia, REBORN! Perhaps my finest work.", 14, 0, 0, 22, 0, 23370, "VO_BD_Nefarian_Maloriak01", 49416),
(41379, 3, 0, "My dearest sibling, do you hunger? THEN FEAST UPON OUR ENEMIES!", 14, 0, 0, 22, 0, 23371, "VO_BD_Nefarian_MaloriakDead01", 49417);

UPDATE creature_template SET speed_walk=1.6, speed_run=.85714, unit_class=4, unit_flags=32768, VehicleId=846, mechanic_immune_mask=8388624 WHERE entry=41918;


