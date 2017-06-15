


DELETE FROM creature_template_addon WHERE `entry` IN (62922 /*62922 (Crimson Shale Hatchling)*/, 62181 /*62181 (Topaz Shale Hatchling)*/, 62916 /*62916 (Fungal Moth)*/, 62118 /*62118 (Twilight Beetle)*/, 62117 /*62117 (Twilight Spider)*/, 62915 /*62915 (Emerald Shale Hatchling)*/, 62182 /*62182 (Amethyst Shale Hatchling)*/, 62925 /*62925 (Crystal Beetle)*/, 66804 /*66804 (Crystallus)*/, 66805 /*66805 (Ruby)*/, 66802 /*66802 (Fracture)*/, 66815 /*66815 (Bordin Steadyfist)*/, 62924 /*62924 (Deepholm Cockroach)*/);
INSERT INTO creature_template_addon (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(62922, 0, 0, 0, 1, 0, ''), -- 62922 (Crimson Shale Hatchling)
(62181, 0, 0, 0, 1, 0, ''), -- 62181 (Topaz Shale Hatchling)
(62916, 0, 0, 50331648, 1, 0, ''), -- 62916 (Fungal Moth)
(62118, 0, 0, 0, 1, 0, ''), -- 62118 (Twilight Beetle)
(62117, 0, 0, 0, 1, 0, ''), -- 62117 (Twilight Spider)
(62915, 0, 0, 0, 1, 0, ''), -- 62915 (Emerald Shale Hatchling)
(62182, 0, 0, 0, 1, 0, ''), -- 62182 (Amethyst Shale Hatchling)
(62925, 0, 0, 0, 1, 0, ''), -- 62925 (Crystal Beetle)
(66804, 0, 0, 0, 1, 0, ''), -- 66804 (Crystallus)
(66805, 0, 0, 0, 1, 0, ''), -- 66805 (Ruby)
(66802, 0, 0, 0, 1, 0, ''), -- 66802 (Fracture)
(66815, 0, 0, 0, 257, 0, ''), -- 66815 (Bordin Steadyfist)
(62924, 0, 0, 0, 1, 0, ''); -- 62924 (Deepholm Cockroach)

DELETE FROM creature_template_addon WHERE `entry` IN (66815 /*66815 (Bordin Steadyfist)*/, 66802 /*66802 (Fracture)*/, 66804 /*66804 (Crystallus)*/, 66805 /*66805 (Ruby)*/, 62915 /*62915 (Emerald Shale Hatchling)*/, 62916 /*62916 (Fungal Moth)*/, 62924 /*62924 (Deepholm Cockroach)*/, 62925 /*62925 (Crystal Beetle)*/);
INSERT INTO creature_template_addon (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(66815, 0, 0, 0, 257, 0, ''), -- 66815 (Bordin Steadyfist)
(66802, 0, 0, 0, 1, 0, ''), -- 66802 (Fracture)
(66804, 0, 0, 0, 1, 0, ''), -- 66804 (Crystallus)
(66805, 0, 0, 0, 1, 0, ''), -- 66805 (Ruby)
(62915, 0, 0, 0, 1, 0, ''), -- 62915 (Emerald Shale Hatchling)
(62916, 0, 0, 50331648, 1, 0, ''), -- 62916 (Fungal Moth)
(62924, 0, 0, 0, 1, 0, ''), -- 62924 (Deepholm Cockroach)
(62925, 0, 0, 0, 1, 0, ''); -- 62925 (Crystal Beetle)

DELETE FROM creature_template_addon WHERE `entry` IN (66802 /*66802 (Fracture)*/, 66815 /*66815 (Bordin Steadyfist)*/, 66805 /*66805 (Ruby)*/, 66804 /*66804 (Crystallus)*/, 62117 /*62117 (Twilight Spider)*/, 62181 /*62181 (Topaz Shale Hatchling)*/, 62182 /*62182 (Amethyst Shale Hatchling)*/, 62927 /*62927 (Crimson Geode)*/, 62922 /*62922 (Crimson Shale Hatchling)*/, 62924 /*62924 (Deepholm Cockroach)*/, 62915 /*62915 (Emerald Shale Hatchling)*/, 62118 /*62118 (Twilight Beetle)*/, 62925 /*62925 (Crystal Beetle)*/);
INSERT INTO creature_template_addon (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES
(66802, 0, 0, 0, 1, 0, ''), -- 66802 (Fracture)
(66815, 0, 0, 0, 257, 0, ''), -- 66815 (Bordin Steadyfist)
(66805, 0, 0, 0, 1, 0, ''), -- 66805 (Ruby)
(66804, 0, 0, 0, 1, 0, ''), -- 66804 (Crystallus)
(62117, 0, 0, 0, 1, 0, ''), -- 62117 (Twilight Spider)
(62181, 0, 0, 0, 1, 0, ''), -- 62181 (Topaz Shale Hatchling)
(62182, 0, 0, 0, 1, 0, ''), -- 62182 (Amethyst Shale Hatchling)
(62927, 0, 0, 33554432, 1, 0, ''), -- 62927 (Crimson Geode)
(62922, 0, 0, 0, 1, 0, ''), -- 62922 (Crimson Shale Hatchling)
(62924, 0, 0, 0, 1, 0, ''), -- 62924 (Deepholm Cockroach)
(62915, 0, 0, 0, 1, 0, ''), -- 62915 (Emerald Shale Hatchling)
(62118, 0, 0, 0, 1, 0, ''), -- 62118 (Twilight Beetle)
(62925, 0, 0, 0, 1, 0, ''); -- 62925 (Crystal Beetle)

UPDATE creature_template_addon SET `auras`='36032' WHERE `entry`=44619; -- Arcane Charge
UPDATE creature_template_addon SET `auras`='79892 82571 82526' WHERE `entry`=43170; -- Cosmetic - Shaman Rocks
UPDATE creature_template_addon SET `auras`='79849 83810 83811' WHERE `entry`=44855; -- Molten Armor -- Cosmetic - Fire Channel -- Cosmetic - Water Channel
UPDATE creature_template_addon SET `auras`='61424' WHERE `entry`=32638; -- Traveler's Tundra Mammoth
UPDATE creature_template_addon SET `auras`='61424' WHERE `entry`=32639; -- Traveler's Tundra Mammoth
UPDATE creature_template_addon SET `bytes1`=262144, `auras`='29266 28559' WHERE `entry`=45364; -- Permanent Feign Death, Untrackable
UPDATE creature_template_addon SET `auras`='100803' WHERE `entry`=53739; -- Impetuous
UPDATE creature_template_addon SET `bytes1`=50331648 WHERE `entry`=43254; -- Wild Energy Passive
UPDATE creature_template_addon SET `auras`='83305 83323' WHERE `entry`=43397; -- Generic Quest Invisibility 11 -- Generic Quest Invisibility 12
UPDATE creature_template_addon SET `auras`='84667 78148 78150' WHERE `entry`=45036; -- Generic Quest Invisibility 16, Windfury, Flametongue Weapon
UPDATE creature_template_addon SET `auras`='84667 78148 78150' WHERE `entry`=45035; -- Generic Quest Invisibility 16, Windfury, Flametongue Weapon
UPDATE creature_template_addon SET `auras`='84667 78148 78150' WHERE `entry`=45039; -- Generic Quest Invisibility 16, Windfury, Flametongue Weapon
UPDATE creature_template_addon SET `auras`='82887 12550' WHERE `entry`=44358; -- Exhausted, Lightning Shield
UPDATE creature_template_addon SET `bytes1`=8,`auras`='82887 79949' WHERE `entry`=44352; -- Exhausted, Water Shield
UPDATE creature_template_addon SET `auras`='78148 78150 83458' WHERE `entry`=44371; -- Windfury, Flametongue Weapon -- No Mana Cost, Mana Regen
UPDATE creature_template_addon SET `auras`='82887 78148 78150' WHERE `entry`=42788; -- Exhausted, Windfury, Flametongue Weapon
UPDATE creature_template_addon SET `auras`='83458 79949' WHERE `entry`=42730; -- No Mana Cost, Mana Regen, Water Shield
UPDATE creature_template_addon SET `auras`='79949' WHERE `entry`=42731; -- Water Shield
UPDATE creature_template_addon SET `auras`='78148 78150 83458' WHERE `entry`=44350; -- Windfury, Flametongue Weapon
UPDATE creature_template_addon SET `auras`='79949 83458' WHERE `entry`=44351; -- Water Shield -- No Mana Cost, Mana Regen
UPDATE creature_template_addon SET `bytes1`=65536, `auras`='79977 79976 79972' WHERE `entry`=43232; -- Blessing of Might,, Retribution Aura, Seal of Truth
UPDATE creature_template_addon SET `mount`=45448, `auras`='29266' WHERE `entry`=43250; -- Permanent Feign Death
UPDATE creature_template_addon SET `auras`='29266' WHERE `entry`=43134; -- Permanent Feign Death
UPDATE creature_template_addon SET `auras`='29266' WHERE `entry`=43174; -- Permanent Feign Death
UPDATE creature_template_addon SET `auras`='83458 79949' WHERE `entry`=44673; -- No Mana Cost, Mana Regen, Water Shield
UPDATE creature_template_addon SET `auras`='79927 83458' WHERE `entry`=44668; -- Earth Shield, No Mana Cost, Mana Regen
UPDATE creature_template_addon SET `auras`='82839 82840' WHERE `entry`=44686; -- Hardened, Vulnerable
UPDATE creature_template_addon SET `auras`='83458' WHERE `entry`=44678; -- No Mana Cost, Mana Regen
UPDATE creature_template_addon SET `auras`='79949' WHERE `entry`=44672; -- Water Shield
UPDATE creature_template_addon SET `auras`='83458 12550' WHERE `entry`=44685; -- Lightning Shield
UPDATE creature_template_addon SET `auras`='82727' WHERE `entry`=44208; -- Twilight Strafe Master
UPDATE creature_template_addon SET `auras`='36513' WHERE `entry`=42824; -- Intangible Presence
UPDATE creature_template_addon SET `auras`='79949' WHERE `entry`=43503; -- Water Shield
UPDATE creature_template_addon SET `auras`='82887 79949' WHERE `entry`=44353; -- Exhausted, Water Shield
UPDATE creature_template_addon SET `auras`='12550 80852' WHERE `entry`=44363; -- Lightning Shield, Generic Quest Invisibility 10
UPDATE creature_template_addon SET `auras`='82360' WHERE `entry`=43984; -- Deactivated
UPDATE creature_template_addon SET `auras`='29266 51126' WHERE `entry`=43995; -- Permanent Feign Death
UPDATE creature_template_addon SET `bytes2`=1 WHERE `entry`=43430; 
UPDATE creature_template_addon SET `bytes2`=1 WHERE `entry`=43537; 
UPDATE creature_template_addon SET `auras`='81710' WHERE `entry`=43662; -- Fracture
UPDATE creature_template_addon SET `bytes1`=50331648, `auras`='82869' WHERE `entry`=44289; -- Twilight Snare
UPDATE creature_template_addon SET `auras`='83852' WHERE `entry`=44148; -- Twilight Snare
UPDATE creature_template_addon SET `auras`='12544' WHERE `entry`=43992; -- Frost Armor
UPDATE creature_template_addon SET `auras`='79865' WHERE `entry`=44875; -- Frost Armor
UPDATE creature_template_addon SET `bytes1`=50331648 WHERE `entry`=44189; 
UPDATE creature_template_addon SET `auras`='79690' WHERE `entry`=42925; -- Tunnel Passive
UPDATE creature_template_addon SET `auras`='79927' WHERE `entry`=43169; -- Earth Shield
UPDATE creature_template_addon SET `auras`='81238 81154' WHERE `entry`=43229; -- Cosmetic - State Dead, Battlefront Triage: Loot FX
UPDATE creature_template_addon SET `auras`='29266 63227' WHERE `entry`=43228; -- Permanent Feign Death
UPDATE creature_template_addon SET `auras`='29266' WHERE `entry`=43234; -- Permanent Feign Death
UPDATE creature_template_addon SET `auras`='83740' WHERE `entry`=44889; -- Cosmetic - Fire Beam State Base
UPDATE creature_template_addon SET `bytes2`=1, `auras`='58951' WHERE `entry`=43032; -- Permanent Feign Death
UPDATE creature_template_addon SET `bytes2`=1, `auras`='58951' WHERE `entry`=43048; -- Permanent Feign Death
UPDATE creature_template_addon SET `bytes1`=65536, `bytes2`=1, `auras`='84063' WHERE `entry`=43036; -- Cosmetic - State Dead (Animation Kit)
UPDATE creature_template_addon SET `auras`='84667 79949' WHERE `entry`=45037; -- Generic Quest Invisibility 16, Water Shield
UPDATE creature_template_addon SET `auras`='83305 83323 84667' WHERE `entry`=53738; -- Generic Quest Invisibility 11 Generic Quest Invisibility 12, Generic Quest Invisibility 16
UPDATE creature_template_addon SET `auras`='83238 80485' WHERE `entry`=28332; -- White Black Hole, White Mist Retrieve Channel
UPDATE creature_template_addon SET `auras`='99628 80852' WHERE `entry`=53649; -- Thrall's Water Aura, Generic Quest Invisibility 10
UPDATE creature_template_addon SET `bytes1`=65536, `auras`='80797 77064' WHERE `entry`=41178; -- Generic Quest Invisibility 5, Tower Beam
UPDATE creature_template_addon SET `auras`='80797' WHERE `entry`=45423; -- Generic Quest Invisibility 5
UPDATE creature_template_addon SET `auras`='32783' WHERE `entry`=47320; -- Arcane Channeling
UPDATE creature_template_addon SET `auras`='82020' WHERE `entry`=43840; -- High Class
UPDATE creature_template_addon SET `auras`='18950' WHERE `entry`=14439; -- Invisibility and Stealth Detection
UPDATE creature_template_addon SET `bytes1`=65536 WHERE `entry`=24110; 
UPDATE creature_template_addon SET `auras`='63227' WHERE `entry`=44849; -- Enrage
UPDATE creature_template_addon SET `auras`='32064' WHERE `entry`=44769; -- Battle Shout
UPDATE creature_template_addon SET `auras`='78148 78150 83458' WHERE `entry`=44675; -- Windfury, Flametongue Weapon, No Mana Cost, Mana Regen
UPDATE creature_template_addon SET `auras`='29266' WHERE `entry`=42916; -- Permanent Feign Death
UPDATE creature_template_addon SET `bytes1`=65536 WHERE `entry`=45034; -- Windfury, Flametongue Weapon, Generic Quest Invisibility 11
UPDATE creature_template_addon SET `bytes1`=65536, `auras`='83305 79949' WHERE `entry`=44634; -- Generic Quest Invisibility 11, Water Shield
UPDATE creature_template_addon SET `bytes1`=65536, `auras`='83305 31765' WHERE `entry`=44646; -- Generic Quest Invisibility 11, Lightning Shield
UPDATE creature_template_addon SET `bytes1`=65539 WHERE `entry`=44631; -- Windfury, Flametongue Weapon, Generic Quest Invisibility 11
UPDATE creature_template_addon SET `auras`='83305 79949' WHERE `entry`=44633; -- Generic Quest Invisibility 11, Water Shield
UPDATE creature_template_addon SET `auras`='83305 79949' WHERE `entry`=44642; -- Generic Quest Invisibility 11, Water Shield
UPDATE creature_template_addon SET `bytes1`=65544 WHERE `entry`=43836; -- Generic Quest Invisibility 11
UPDATE creature_template_addon SET `auras`='81717 79949' WHERE `entry`=43809; -- Generic Quest Invisibility 14, Water Shield
UPDATE creature_template_addon SET `auras`='95366 80852' WHERE `entry`=42465; -- Therazane Base, Generic Quest Invisibility 10
UPDATE creature_template_addon SET `auras`='80852 83323' WHERE `entry`=42470; -- Generic Quest Invisibility 10
UPDATE creature_template_addon SET `auras`='84020' WHERE `entry`=44973; -- Generic Quest Invisibility 13
UPDATE creature_template_addon SET `auras`='79949' WHERE `entry`=43514; -- Water Shield
UPDATE creature_template_addon SET `auras`='80660' WHERE `entry`=42524; -- Jaspertip Acid
UPDATE creature_template_addon SET `auras`='80660' WHERE `entry`=42525; -- Jaspertip Acid
UPDATE creature_template_addon SET `auras`='81086' WHERE `entry`=42711; -- Ride Vehicle Hardcoded, Trogg Mushroom Shield, White (Back)
UPDATE creature_template_addon SET `auras`='79690' WHERE `entry`=44257; -- Tunnel Passive
UPDATE creature_template_addon SET `bytes1`=8 WHERE `entry`=42823; 
UPDATE creature_template_addon SET `auras`='87864 87871' WHERE `entry`=47172; -- Ride Vehicle Hardcoded, Large Blue Arrow, Generic Quest Invisibility 21
UPDATE creature_template_addon SET `auras`='87864 85813' WHERE `entry`=47170; -- Ride Vehicle Hardcoded, Large Blue Arrow, Generic Quest Invisibility 20
UPDATE creature_template_addon SET `auras`='87864 87872' WHERE `entry`=47173; -- Ride Vehicle Hardcoded, Large Blue Arrow, Generic Quest Invisibility 22
UPDATE creature_template_addon SET `bytes1`=65536, `auras`='80852' WHERE `entry`=40789; -- Generic Quest Invisibility 10


