
-- vashj'ir

DELETE FROM creature_equip_template WHERE entry in (40510, 41878, 41871, 41252, 42096, 29016, 1976, 68, 41869, 39638, 39664, 42875, 42876, 42878, 42726, 40643, 41607);
DELETE FROM creature_equip_template WHERE entry in (41795, 41731, 41517, 41526, 41527, 40646, 41466, 41494, 41495, 42058, 41569, 41537, 41457, 42074, 41476, 41115, 40978); 
INSERT INTO creature_equip_template (`entry`, `ID`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES
(40510, 1, 54541, 0, 0),
(41878, 1, 2182, 2182, 0),
(41871, 1, 9659, 9659, 0),
(41252, 1, 51898, 0, 0),
(42096, 1, 1899, 143, 0),
(29016, 1, 1903, 0, 0),
(29016, 2, 31824, 0, 0),
(1976, 1, 2715, 143, 2551),
(1976, 2, 1899, 143, 2551),
(68, 1, 1899, 143, 2551),
(68, 2, 2715, 143, 2551),
(41869, 1, 51898, 0, 0), -- Erunak Stonespeaker
(39638, 1, 49341, 2445, 0), -- Azsh'ir Patroller
(39664, 1, 19946, 0, 0), -- Glimmerdeep Tidehunter
(42875, 1, 57243, 0, 15460), -- Miriam Brassbomb
(42876, 1, 1911, 0, 0), -- Frell "Fixit" Fastbolt
(42878, 1, 0, 12853, 0), -- Salena Madeux
(42726, 1, 2182, 2182, 0), -- Earthwatcher Shaman
(40643, 1, 0, 851, 0), -- Admiral Dvorek
(40643, 2, 851, 851, 0), -- Admiral Dvorek
(41607, 9, 28914, 0, 0), -- Idra'kess Warlord
(41795, 1, 29679, 0, 0), -- Idra'kess Mistress
(41731, 1, 37917, 0, 0), -- Overseer Idra'kess
(41607, 8, 14879, 0, 0), -- Idra'kess Warlord
(41607, 7, 5746, 0, 0), -- Idra'kess Warlord
(41607, 6, 11838, 0, 0), -- Idra'kess Warlord
(41607, 5, 14535, 0, 0), -- Idra'kess Warlord
(41607, 4, 25234, 0, 0), -- Idra'kess Warlord
(41607, 3, 2023, 0, 0), -- Idra'kess Warlord
(41607, 2, 5747, 0, 0), -- Idra'kess Warlord
(41607, 1, 5745, 0, 0), -- Idra'kess Warlord
(41517, 1, 3368, 0, 37130), -- Idra'kess Harpooner
(41526, 1, 11343, 0, 0), -- Enslaved Horde Mage
(41527, 1, 11365, 0, 0), -- Enslaved Alliance Mage
(40646, 1, 5285, 0, 0), -- Glimmerdeep Diver
(41466, 1, 34880, 1984, 0), -- Idra'kess Sentinel
(41494, 1, 2901, 0, 0),
(41495, 1, 2901, 0, 0),
(42058, 1, 56578, 0, 0),
(41569, 1, 34817, 0, 0),
(41537, 1, 52523, 0, 0),
(41457, 1, 25234, 0, 0),
(42074, 1, 34183, 0, 0),
(41476, 1, 37917, 0, 0),
(41115, 1, 34820, 0, 0),
(40978, 1, 34183, 0, 0);

DELETE FROM creature_equip_template WHERE entry in (40275, 40221, 40174, 40382, 40161, 40366, 41227, 40315, 41652, 39874, 39411, 39877, 41347, 41341, 41344, 40983, 39885);
DELETE FROM creature_equip_template WHERE entry in (41018, 41038, 41530, 41549, 41037, 40105, 41248, 40732, 40736, 40735, 40729, 40734, 40730, 40731, 40733, 40738, 40739);
DELETE FROM creature_equip_template WHERE entry in (40744, 40740, 40746, 40741, 40742, 40737, 40680, 40810, 40677, 36915, 40811, 39662, 39478, 42103, 42021);

INSERT INTO creature_equip_template (`entry`, `ID`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES
(40275, 8, 5747, 0, 0), -- Zin'jatar Ravager
(40275, 7, 11838, 0, 0), -- Zin'jatar Ravager
(40275, 6, 2023, 0, 0), -- Zin'jatar Ravager
(40275, 5, 14535, 0, 0), -- Zin'jatar Ravager
(40275, 4, 25234, 0, 0), -- Zin'jatar Ravager
(40275, 3, 28914, 0, 0), -- Zin'jatar Ravager
(40275, 2, 5746, 0, 0), -- Zin'jatar Ravager
(40275, 1, 5745, 0, 0), -- Zin'jatar Ravager
(40221, 1, 52689, 52689, 0), -- Toshe Chaosrender
(40174, 8, 11838, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 7, 2023, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 6, 28914, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 5, 14879, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 4, 5747, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 3, 5746, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 2, 14535, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40174, 1, 25234, 0, 0), -- Fleeing Zin'jatar Fathom-Stalker
(40382, 5, 5746, 0, 0), -- Zin'jatar Fathom-Stalker
(40382, 4, 25234, 0, 0), -- Zin'jatar Fathom-Stalker
(40382, 3, 14535, 0, 0), -- Zin'jatar Fathom-Stalker
(40382, 2, 11838, 0, 0), -- Zin'jatar Fathom-Stalker
(40382, 1, 28914, 0, 0), -- Zin'jatar Fathom-Stalker
(40161, 1, 54541, 0, 0), -- Fathom-Lord Zin'jatar
(40366, 1, 52689, 52689, 0), -- Toshe Chaosrender
(41227, 8, 28914, 0, 0), -- Azsh'ir Infantry
(41227, 7, 25234, 0, 0), -- Azsh'ir Infantry
(41227, 6, 5747, 0, 0), -- Azsh'ir Infantry
(41227, 5, 2023, 0, 0), -- Azsh'ir Infantry
(41227, 4, 14879, 0, 0), -- Azsh'ir Infantry
(41227, 3, 5746, 0, 0), -- Azsh'ir Infantry
(41227, 2, 14535, 0, 0), -- Azsh'ir Infantry
(41227, 1, 11838, 0, 0), -- Azsh'ir Infantry
(40315, 1, 37917, 0, 0), -- Naz'jar Honor Guard
(41652, 2, 57130, 0, 0), -- Twilight Champion
(41652, 1, 57129, 0, 0), -- Twilight Champion
(39874, 1, 22213, 13629, 0), -- Derth Firesinger
(39411, 1, 22213, 33210, 0), -- Earthen Ring Shaman
(39877, 1, 52689, 52689, 0), -- Toshe Chaosrender
(41347, 1, 51898, 0, 0), -- Moanah Stormhoof
(41341, 1, 51898, 0, 0), -- Erunak Stonespeaker
(41344, 1, 51898, 0, 0), -- Rendel Firetongue
(40983, 1, 2717, 0, 0), -- Mack Fearsen
(39885, 1, 2717, 0, 0), -- Mack Fearsen
(41018, 1, 35587, 0, 0), -- King Gurboggle
(41038, 1, 0, 0, 37692), -- Undead Officer
(41530, 1, 62139, 0, 0), -- Warden Azjakir
(41549, 1, 54541, 0, 0), -- Zin'jatar Overseer
(41037, 1, 3319, 0, 0), -- Salty Dog
(40105, 1, 51898, 0, 0), -- Erunak Stonespeaker
(41248, 1, 51898, 0, 0), -- Moanah Stormhoof
(40732, 1, 54965, 143, 0), -- Stormwind Seal
(40736, 1, 51898, 0, 0), -- Erunak Stonespeaker
(40735, 1, 54965, 143, 0), -- Stormwind Seal
(40729, 1, 45951, 0, 0), -- Captain Taylor
(40734, 1, 54965, 143, 0), -- Stormwind Seal
(40730, 1, 54965, 143, 0), -- Stormwind Seal
(40731, 1, 54965, 143, 0), -- Stormwind Seal
(40733, 1, 54965, 143, 0), -- Stormwind Seal
(40738, 1, 54965, 143, 0), -- Stormwind Seal
(40739, 1, 54965, 143, 0), -- Stormwind Seal
(40744, 1, 54965, 143, 0), -- Stormwind Seal
(40740, 1, 54965, 143, 0), -- Stormwind Seal
(40746, 1, 51898, 0, 0), -- Erunak Stonespeaker
(40741, 1, 54965, 143, 0), -- Stormwind Seal
(40742, 1, 54965, 143, 0), -- Stormwind Seal
(40737, 1, 45951, 0, 0), -- Captain Taylor
(40680, 1, 1899, 143, 0), -- Stormwind Soldier
(40810, 1, 0, 143, 0), -- Gilblin Scavenger
(40677, 1, 54965, 0, 0), -- Gilblin Scavenger
(36915, 1, 51898, 0, 0), -- Erunak Stonespeaker
(40811, 1, 25184, 0, 0), -- Gilblin Scavenger
(39662, 1, 1899, 143, 0), -- Drowning Soldier
(39478, 1, 2717, 0, 0), -- Mack Fearsen
(42103, 1, 1899, 143, 0), -- Captain Taylor
(42021, 1, 1899, 143, 0); -- Stormwind Soldier

DELETE FROM creature_equip_template WHERE entry in (42065, 42025, 42073, 42075, 41994, 42057, 42048, 41256, 41515, 41513, 42068, 41521, 41512, 41118, 41516, 42066, 41456, 41979);
DELETE FROM creature_equip_template WHERE entry in (46468, 46470, 41117, 41049, 41120, 41106, 42295, 41514, 41108, 41102, 44424, 40989, 40911, 42453, 41228, 39602, 41995, 41999);
DELETE FROM creature_equip_template WHERE entry in (41566, 41606, 45462, 42488, 42676, 42911, 42910, 41874, 42909, 43983, 42071, 41455, 42072, 41780, 41281, 42549, 41249, 41519);

INSERT INTO creature_equip_template (`entry`, `ID`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES
(42065, 1, 37917, 0, 0), -- Naz'jar Honor Guard
(42025, 7, 5745, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 6, 28914, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 5, 14879, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 4, 5747, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 3, 11838, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 2, 2023, 0, 0), -- Zin'jatar Depth-Hunter
(42025, 1, 14535, 0, 0), -- Zin'jatar Depth-Hunter
(42073, 1, 54541, 0, 0), -- Fathom-Lord Zin'jatar
(42075, 1, 34183, 0, 0), -- Fathom-Stalker Azjentus
(41994, 1, 34816, 34816, 0), -- Kvaldir Painreaver
(42057, 1, 34816, 0, 0), -- Kvaldir Bonesnapper
(42048, 4, 5747, 0, 0), -- Sira'kess Zealot
(42048, 3, 11838, 0, 0), -- Sira'kess Zealot
(42048, 2, 28914, 0, 0), -- Sira'kess Zealot
(42048, 1, 5745, 0, 0), -- Sira'kess Zealot
(41256, 4, 28914, 0, 0), -- Alliance Assault Volunteer
(41256, 3, 5746, 0, 0), -- Alliance Assault Volunteer
(41256, 2, 25234, 0, 0), -- Alliance Assault Volunteer
(41256, 1, 2023, 0, 0), -- Alliance Assault Volunteer
(41515, 7, 5746, 0, 0), -- Azsh'ir Infantry
(41515, 6, 14879, 0, 0), -- Azsh'ir Infantry
(41515, 5, 2023, 0, 0), -- Azsh'ir Infantry
(41515, 4, 25234, 0, 0), -- Azsh'ir Infantry
(41515, 3, 11838, 0, 0), -- Azsh'ir Infantry
(41515, 2, 14535, 0, 0), -- Azsh'ir Infantry
(41515, 1, 5747, 0, 0), -- Azsh'ir Infantry
(41513, 9, 28914, 0, 0), -- Sira'kess Guardian
(41513, 8, 25234, 0, 0), -- Sira'kess Guardian
(41513, 7, 2023, 0, 0), -- Sira'kess Guardian
(41513, 6, 5747, 0, 0), -- Sira'kess Guardian
(41513, 5, 14879, 0, 0), -- Sira'kess Guardian
(41513, 4, 14535, 0, 0), -- Sira'kess Guardian
(41513, 3, 5746, 0, 0), -- Sira'kess Guardian
(41513, 2, 11838, 0, 0), -- Sira'kess Guardian
(41513, 1, 5745, 0, 0), -- Sira'kess Guardian
(42068, 8, 28914, 0, 0), -- Naz'jar Serpent Guard
(42068, 7, 2023, 0, 0), -- Naz'jar Serpent Guard
(42068, 6, 5747, 0, 0), -- Naz'jar Serpent Guard
(42068, 5, 14535, 0, 0), -- Naz'jar Serpent Guard
(42068, 4, 14879, 0, 0), -- Naz'jar Serpent Guard
(42068, 3, 11838, 0, 0), -- Naz'jar Serpent Guard
(42068, 2, 25234, 0, 0), -- Naz'jar Serpent Guard
(42068, 1, 5746, 0, 0), -- Naz'jar Serpent Guard
(41521, 7, 2023, 0, 0), -- Naz'jar Serpent Guard
(41521, 6, 5746, 0, 0), -- Naz'jar Serpent Guard
(41521, 5, 11838, 0, 0), -- Naz'jar Serpent Guard
(41521, 4, 25234, 0, 0), -- Naz'jar Serpent Guard
(41521, 3, 28914, 0, 0), -- Naz'jar Serpent Guard
(41521, 2, 14535, 0, 0), -- Naz'jar Serpent Guard
(41521, 1, 5745, 0, 0), -- Naz'jar Serpent Guard
(41512, 8, 5746, 0, 0), -- Idra'kess Sentinel
(41512, 7, 11838, 0, 0), -- Idra'kess Sentinel
(41512, 6, 14879, 0, 0), -- Idra'kess Sentinel
(41512, 5, 25234, 0, 0), -- Idra'kess Sentinel
(41512, 4, 5747, 0, 0), -- Idra'kess Sentinel
(41512, 3, 2023, 0, 0), -- Idra'kess Sentinel
(41512, 2, 14535, 0, 0), -- Idra'kess Sentinel
(41512, 1, 28914, 0, 0), -- Idra'kess Sentinel
(41118, 6, 5747, 0, 0), -- Zin'jatar Warrior
(41118, 5, 5746, 0, 0), -- Zin'jatar Warrior
(41118, 4, 2023, 0, 0), -- Zin'jatar Warrior
(41118, 3, 28914, 0, 0), -- Zin'jatar Warrior
(41118, 2, 25234, 0, 0), -- Zin'jatar Warrior
(41118, 1, 5745, 0, 0), -- Zin'jatar Warrior
(41516, 1, 5746, 0, 0), -- Azsh'ir Soldier
(42066, 1, 0, 0, 31325), -- Naz'jar Spitfire
(41456, 1, 32841, 0, 0), -- Lady Sira'kess
(41979, 1, 37917, 0, 0), -- Naz'jar Honor Guard
(46468, 1, 5285, 0, 55318), -- Horde Lookout
(46470, 1, 5285, 0, 55318), -- Alliance Lookout
(41117, 1, 5282, 0, 0), -- Sira'kess Sea Witch
(41049, 1, 54541, 0, 0), -- Fathom-Lord Zin'jatar
(41120, 1, 5283, 0, 14105), -- Zin'jatar Stormsiren
(41106, 1, 57018, 57017, 0), -- Kvaldir Wasteroamer
(42295, 1, 32841, 0, 0), -- Lady Sira'kess
(41514, 1, 37917, 0, 0), -- Naz'jar Honor Guard
(41108, 1, 52689, 52525, 28539), -- Kvaldir Plunderer
(41102, 1, 34818, 0, 0), -- Kvaldir Pillager
(44424, 1, 54820, 0, 0), -- Naz'jar Battlemaiden
(40989, 1, 5746, 0, 0), -- Azsh'ir Raider
(40911, 1, 15810, 0, 0), -- Redgill Scavenger
(42453, 1, 49311, 0, 0), -- Azsh'ir Abyss Priestess
(41228, 1, 28965, 0, 0), -- Naz'jar Serpent Guard
(39602, 1, 34820, 0, 0), -- Kvaldir Marauder
(41995, 1, 34816, 34816, 0), -- Kvaldir Reckoner
(41999, 1, 37917, 0, 0), -- Naz'jar Honor Guard
(41566, 1, 0, 16788, 0), -- Muckskin Scrounger
(41606, 1, 52523, 0, 0), -- Kvaldir Seahorror
(45462, 1, 52689, 52689, 0), -- Toshe Chaosrender
(42488, 1, 31824, 0, 0), -- Chief Engineer Yoon
(42676, 1, 31824, 0, 0), -- Chief Engineer Petibas
(42911, 1, 57243, 0, 2507), -- Larok
(42910, 1, 0, 12853, 0), -- Roxa
(41874, 1, 9659, 9659, 0), -- Earthwatcher Shaman
(42909, 1, 1911, 0, 0), -- Ginna Gearcrank
(43983, 1, 49341, 2445, 0), -- Azsh'ir Manhunter
(42071, 1, 32841, 0, 0), -- Lady Sira'kess
(41455, 1, 37917, 0, 0), -- Overseer Idra'kess
(42072, 1, 54541, 0, 0), -- Fathom-Lord Zin'jatar
(41780, 1, 5285, 0, 55318), -- Horde Lookout
(41281, 1, 5285, 0, 0), -- Injured Assault Volunteer
(42549, 1, 57785, 0, 0), -- Azsh'ir Archaean
(41249, 1, 57830, 0, 0), -- Azsh'ir Soldier
(41519, 1, 38210, 0, 0); -- Azsh'ir Sentry











