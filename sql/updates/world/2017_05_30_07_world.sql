
-- deepholm

DELETE FROM creature_equip_template WHERE (`entry`=44371 AND `ID`=1) OR (`entry`=44351 AND `ID`=1) OR (`entry`=44152 AND `ID`=1) OR (`entry`=44151 AND `ID`=1) OR (`entry`=43898 AND `ID`=1);
INSERT INTO creature_equip_template (`entry`, `ID`, `ItemEntry1`, `ItemEntry2`, `ItemEntry3`) VALUES
(44371, 1, 56913, 56913, 0), -- Yuldris Smolderfury
(44351, 1, 42939, 56174, 0), -- Stormcaller Jalara
(44152, 1, 33276, 0, 0), -- Flint Oremantle
(44151, 1, 41982, 41982, 0), -- Bouldergut
(43898, 1, 33276, 0, 0); -- Flint Oremantle

delete from vehicle_template_accessory where entry in (42962, 42962, 42887, 43046, 45024, 45004, 42788, 44352, 44353, 43952, 43509, 48640, 42543, 48642, 44136, 43116);

INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(42962, 42964, 1, 1, 'Stormbeak - Mor''norokk the Hateful', 6, 0), -- Stormbeak - Mor'norokk the Hateful
(42962, 42965, 0, 1, 'Stormbeak - Stormcaller Mylra', 6, 0), -- Stormbeak - Stormcaller Mylra
(42887, 42892, 0, 1, 'Stormbeak - Stormcaller Mylra', 6, 0), -- Stormbeak - Stormcaller Mylra
(43046, 43044, 0, 1, 'Unexploded Artillery Shell Mount - Unexploded Artillery Shell', 6, 0), -- Unexploded Artillery Shell Mount - Unexploded Artillery Shell
(45024, 45027, 0, 1, 'Wyvern - Aggra', 6, 0), -- Wyvern - Aggra
(45004, 45028, 0, 1, 'Wyvern - Aggra', 6, 0), -- Wyvern - Aggra
(42788, 47170, 0, 1, 'Hargoth Dimblaze - Therazane Siege Arrow Bunny, 1', 6, 0), -- Hargoth Dimblaze - Therazane Siege Arrow Bunny, 1
(44352, 47173, 0, 1, 'Tawn Winterbluff - Therazane Siege Arrow Bunny, 3', 6, 0), -- Tawn Winterbluff - Therazane Siege Arrow Bunny, 3
(44353, 47172, 0, 1, 'Stormcaller Mylra - Therazane Siege Arrow Bunny, 2', 6, 0), -- Stormcaller Mylra - Therazane Siege Arrow Bunny, 2
(43952, 45064, 0, 1, 'Earthen Catapult - Catapult Driver', 6, 0), -- Earthen Catapult - Catapult Driver
(43509, 43635, 0, 1, 'Earthen Catapult - Catapult Driver', 6, 0), -- Earthen Catapult - Catapult Driver
(48640, 48639, 0, 1, 'Enormous Gyreworm Bunny - Ruby Gemstone Cluster', 6, 0), -- Enormous Gyreworm Bunny - Ruby Gemstone Cluster
(42543, 42711, 0, 1, 'Crystal Gorged Basilisk - Verlok Basilisk Rider', 6, 0), -- Crystal Gorged Basilisk - Verlok Basilisk Rider
(48642, 48639, 0, 1, 'Enormous Gyreworm Bunny - Ruby Gemstone Cluster', 6, 0), -- Enormous Gyreworm Bunny - Ruby Gemstone Cluster
(44136, 44135, 0, 1, 'Zoltrik''s Pyremaw - Zoltrik Drakebane', 6, 0), -- Zoltrik's Pyremaw - Zoltrik Drakebane
(43116, 43182, 7, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 6, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 5, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 4, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 3, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 2, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 1, 1, 'Pebble - Petrified Stone Bat', 6, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 0, 1, 'Pebble - Petrified Stone Bat', 6, 0); -- Pebble - Petrified Stone Bat



