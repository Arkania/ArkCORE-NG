
UPDATE creature_template SET ScriptName="npc_moonbrook_player_trigger_43515" WHERE entry=43515;

DELETE FROM creature_text WHERE entry=43515 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(43515, 1, 0, "Follow the trail of homeless to the Deadmines dungeon entrance.", 42, 0, 100, 0, 0, 0, "Moonbrook Player Trigger", 43612);

DELETE FROM creature_text WHERE entry=42699;
INSERT INTO creature_text VALUES 
(42699, 0, 0, "There's nowhere left to hide, VanCleef! The Defias are THROUGH!", 14, 0, 100, 22, 0, 0, "Alliance Warrior yells", 42593),
(42699, 1, 0, "We're here to finish this! Face us, coward!", 14, 0, 100, 397, 0, 0, "Alliance Warrior yells", 42594),
(42699, 2, 0, "Victory for the Alliance! Glory to Stormwind!", 14, 0, 100, 5, 0, 0, "Alliance Warrior yells", 42602),
(42699, 3, 0, "Let us return to Sentinel Hill, allies, and inform Gryan of VanCleef's demise!", 12, 0, 100, 396, 0, 0, "Alliance Warrior says", 42603);

DELETE FROM creature_text WHERE entry=42698;
INSERT INTO creature_text VALUES 
(42698, 0, 0, "%s jumps out of the shadows!", 16, 0, 100, 0, 0, 0, "Defias Blackguard", 1327);

DELETE FROM creature_text WHERE entry=42697;
INSERT INTO creature_text VALUES 
(42697, 0, 0, "None may callenge the Brotherhood!", 14, 0, 100, 5, 0, 5780, "Edwin van Cleef yells", 42595),
(42697, 1, 0, "%s calls more of his allies out of the shadows", 16, 0, 100, 0, 0, 0, "Edwin van Cleef MonsterEmote", 1048),
(42697, 2, 0, "Lapdogs, all of you!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 6063),
(42697, 3, 0, "Fools! Our cause is righteous!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 6064),
(42697, 4, 0, "The Brotherhood shall prevail!", 14, 0, 100, 0, 0, 0, "Edwin van Cleef yells", 6065);

DELETE FROM creature_text WHERE entry=42371;
INSERT INTO creature_text VALUES 
(42371, 0, 0, "Daddy...", 12, 0, 100, 0, 0, 0, "Vanessa van Cleef says", 42604);

DELETE FROM waypoint_data WHERE id=4237100;
INSERT INTO waypoint_data VALUES 
(4237100, 0, -82.94046, -819.675, 39.62264, 0, 0, 0, 0, 100, 0),
(4237100, 1, -84.28472, -819.6649, 39.60331, 0, 0, 0, 0, 100, 0),
(4237100, 2, -83.28472, -819.6649, 39.60331, 0, 0, 0, 0, 100, 0),
(4237100, 3, -79.30035, -819.7813, 39.82702, 0, 0, 0, 0, 100, 0),
(4237100, 4, -74.83334, -819.8941, 40.20089, 0, 0, 0, 0, 100, 0),
(4237100, 5, -74.83334, -819.8941, 40.20089, 0, 0, 0, 0, 100, 0),
(4237100, 6, -70.08977, -820.5098, 40.77253, 0, 0, 0, 0, 100, 0),
(4237100, 7, -67.84621, -821.1254, 40.84417, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4269900;
INSERT INTO waypoint_data VALUES 
(4269900, 0, -63.56937, -819.5765, 41.2412, 0, 0, 0, 0, 100, 0),
(4269900, 1, -65.17618, -829.6771, 41.15453, 0, 0, 0, 0, 100, 0),
(4269900, 2, -65.78299, -839.7778, 41.06787, 0, 0, 0, 0, 100, 0),
(4269900, 3, -67.7309, -845.127, 32.6046, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4270000;
INSERT INTO waypoint_data VALUES 
(4270000, 0, -62.84618, -820.1375, 41.30676, 0, 0, 0, 0, 100, 0),
(4270000, 1, -61.30417, -826.679, 41.53063, 0, 0, 0, 0, 100, 0),
(4270000, 2, -63.05417, -836.679, 41.53063, 0, 0, 0, 0, 100, 0),
(4270000, 3, -63.76215, -839.7205, 41.2545, 0, 0, 0, 0, 100, 0),
(4270000, 4, -63.8767, -845.486, 32.9145, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4270100;
INSERT INTO waypoint_data VALUES 
(4270100, 0, -62.91118, -821.7435, 41.30499, 0, 0, 0, 0, 100, 0),
(4270100, 1, -66.62847, -839.632, 40.98961, 0, 0, 0, 0, 100, 0),
(4270100, 2, -66.1233, -845.115, 32.724, 0, 0, 0, 0, 100, 0),
(4270100, 3, -62.51983, -831.6877, 41.6473, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4270200;
INSERT INTO waypoint_data VALUES 
(4270200, 0, -63.03794, -820.5649, 41.28989, 0, 0, 0, 0, 100, 0),
(4270200, 1, -62.64757, -839.6285, 41.35745, 0, 0, 0, 0, 100, 0),
(4270200, 2, -63.1632, -844.773, 32.9248, 0, 0, 0, 0, 100, 0),
(4270200, 3, -60.59276, -831.0967, 41.82367, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4270300;
INSERT INTO waypoint_data VALUES 
(4270300, 0, -63.83944, -819.2853, 41.21694, 0, 0, 0, 0, 100, 0),
(4270300, 1, -63.16104, -824.7407, 41.42934, 0, 0, 0, 0, 100, 0),
(4270300, 2, -63.91104, -830.7407, 41.42934, 0, 0, 0, 0, 100, 0),
(4270300, 3, -64.98264, -839.6962, 41.14175, 0, 0, 0, 0, 100, 0),
(4270300, 4, -63.9601, -845.21, 32.8916, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4269700;
INSERT INTO waypoint_data VALUES 
(4269700, 0, -79.7884, -819.5851, 40.12569, 0, 0, 0, 0, 100, 0),
(4269700, 1, -76.5384, -819.5851, 40.12569, 0, 0, 0, 0, 100, 0),
(4269700, 2, -69.5384, -819.3351, 40.87569, 0, 0, 0, 0, 100, 0),
(4269700, 3, -66.70701, -819.2744, 40.95092, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4269801;
INSERT INTO waypoint_data VALUES 
(4269801, 0, -76.25556, -818.0201, 40.48545, 0, 0, 1, 0, 100, 0),
(4269801, 1, -72.25556, -817.2701, 40.48545, 0, 0, 1, 0, 100, 0),
(4269801, 2, -70.25556, -816.5201, 40.73545, 0, 0, 1, 0, 100, 0),
(4269801, 3, -66.70383, -816.943, 40.95212, 0, 0, 1, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=4269802;
INSERT INTO waypoint_data VALUES 
(4269802, 0, -76.25556, -821.0201, 40.48545, 0, 0, 1, 0, 100, 0),
(4269802, 1, -72.25556, -821.2701, 40.48545, 0, 0, 1, 0, 100, 0),
(4269802, 2, -70.25556, -821.5201, 40.73545, 0, 0, 1, 0, 100, 0),
(4269802, 3, -66.70383, -821.943, 40.95212, 0, 0, 1, 0, 100, 0);





