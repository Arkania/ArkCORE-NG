
update creature set phaseId=231 where guid in (146177, 146180, 146182, 146185, 146186, 146188, 146190, 146191, 146192, 146193, 146194, 146197, 146198);

update creature set phaseId=231 where guid in (146199, 146200, 146201, 146203, 146204, 146205, 146207, 146208, 146209, 146211, 146212, 146213, 146216);

update creature set phaseId=231 where guid in (146217, 146218, 146219, 146227, 146228, 146231, 146232, 146235, 146237, 146239, 146240, 146241, 146260);

update gameobject set phaseId=231 where guid=189815;

delete from pool_template where entry in (14529, 14538, 14539, 14540, 14541, 14530, 14531, 14532, 14533, 14534, 14535, 14536, 14537);

delete from pool_creature where pool_entry in (14529, 14538, 14539, 14540, 14541, 14530, 14531, 14532, 14533, 14534, 14535, 14536, 14537);

DELETE FROM creature_addon WHERE guid in (146177, 146180, 146182, 146185, 146186, 146188, 146190, 146191, 146192, 146193, 146194, 146197, 146198);

DELETE FROM creature_addon WHERE guid in (146199, 146200, 146201, 146203, 146204, 146205, 146207, 146208, 146209, 146211, 146212, 146213, 146216);

DELETE FROM creature_addon WHERE guid in (146217, 146218, 146219, 146227, 146228, 146231, 146232, 146235, 146237, 146239, 146240, 146241, 146260);

INSERT INTO creature_addon VALUES 
(146177, 0, 0, 0, 1, 0, "29266"),
(146180, 0, 0, 0, 1, 0, "29266"),
(146182, 0, 0, 0, 1, 0, "29266"),
(146185, 0, 0, 0, 1, 0, "29266"),
(146186, 0, 0, 0, 1, 0, "29266"),
(146188, 0, 0, 0, 1, 0, "29266"),
(146190, 0, 0, 0, 1, 0, "29266"),
(146191, 0, 0, 0, 1, 0, "29266"),
(146192, 0, 0, 0, 1, 0, "29266"),
(146193, 0, 0, 0, 1, 0, "29266"),
(146194, 0, 0, 0, 1, 0, "29266"),
(146197, 0, 0, 0, 1, 0, "29266"),
(146198, 0, 0, 0, 1, 0, "29266"),
(146199, 0, 0, 0, 1, 0, "29266"),
(146200, 0, 0, 0, 1, 0, "29266"),
(146201, 0, 0, 0, 1, 0, "29266"),
(146203, 0, 0, 0, 1, 0, "29266"),
(146204, 0, 0, 0, 1, 0, "29266"),
(146205, 0, 0, 0, 1, 0, "29266"),
(146207, 0, 0, 0, 1, 0, "29266"),
(146208, 0, 0, 0, 1, 0, "29266"),
(146209, 0, 0, 0, 1, 0, "29266"),
(146211, 0, 0, 0, 1, 0, "29266"),
(146212, 0, 0, 0, 1, 0, "29266"),
(146213, 0, 0, 0, 1, 0, "29266 6433"),
(146216, 0, 0, 0, 1, 0, "29266"),
(146217, 0, 0, 0, 1, 0, "29266"),
(146218, 0, 0, 0, 1, 0, "29266"),
(146219, 0, 0, 0, 1, 0, "29266"),
(146227, 0, 0, 0, 1, 0, "29266"),
(146228, 0, 0, 0, 1, 0, "29266"),
(146231, 0, 0, 0, 1, 0, "29266"),
(146232, 0, 0, 0, 1, 0, "29266"),
(146235, 0, 0, 0, 1, 0, "29266"),
(146237, 0, 0, 0, 1, 0, "29266"),
(146239, 0, 0, 0, 1, 0, "29266"),
(146240, 0, 0, 0, 1, 0, "29266"),
(146241, 0, 0, 0, 1, 0, "29266"),
(146260, 0, 0, 0, 1, 0, "29266");


DELETE FROM creature WHERE id=657 AND guid=6722;
INSERT INTO creature VALUES 
(6722, 657, 36, 0, 0, 3, 231, 0, 0, 0, -60.324, -731.8401, 9.032983, 2.129302, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6722;

INSERT INTO creature_addon VALUES 
(6722, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=6817;
INSERT INTO creature VALUES 
(6817, 657, 36, 0, 0, 3, 231, 0, 0, 0, -96.44043, -721.125, 8.531245, 3.944444, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6817;

INSERT INTO creature_addon VALUES 
(6817, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=6886;
INSERT INTO creature VALUES 
(6886, 657, 36, 0, 0, 3, 231, 0, 0, 0, -103.6993, -722.2738, 8.723626, 4.956735, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6886;

INSERT INTO creature_addon VALUES 
(6886, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=6930;
INSERT INTO creature VALUES 
(6930, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -79.45508, -729.1056, 9.127749, 1.53589, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6930;

INSERT INTO creature_addon VALUES 
(6930, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=6935;
INSERT INTO creature VALUES 
(6935, 657, 36, 0, 0, 3, 231, 0, 0, 0, -41.06592, -730.6678, 9.128899, 4.625123, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6935;

INSERT INTO creature_addon VALUES 
(6935, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=6940;
INSERT INTO creature VALUES 
(6940, 657, 36, 0, 0, 3, 231, 0, 0, 0, -32.14719, -727.7289, 8.616197, 0.5759587, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6940;

INSERT INTO creature_addon VALUES 
(6940, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=6951;
INSERT INTO creature VALUES 
(6951, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -83.13623, -776.0989, 26.92174, 0.2268928, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6951;

INSERT INTO creature_addon VALUES 
(6951, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=6955;
INSERT INTO creature VALUES 
(6955, 657, 36, 0, 0, 3, 231, 0, 0, 0, -75.41987, -783.7542, 26.45467, 3.01942, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=6955;

INSERT INTO creature_addon VALUES 
(6955, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7018;
INSERT INTO creature VALUES 
(7018, 657, 36, 0, 0, 3, 231, 0, 0, 0, -57.31386, -783.428, 18.19203, 2.565634, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7018;

INSERT INTO creature_addon VALUES 
(7018, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=7085;
INSERT INTO creature VALUES 
(7085, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -105.6016, -793.749, 28.19328, 5.201081, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7085;

INSERT INTO creature_addon VALUES 
(7085, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7104;
INSERT INTO creature VALUES 
(7104, 657, 36, 0, 0, 3, 231, 0, 0, 0, -110.961, -795.7646, 17.1208, 2.146755, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7104;

INSERT INTO creature_addon VALUES 
(7104, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7107;
INSERT INTO creature VALUES 
(7107, 657, 36, 0, 0, 3, 231, 0, 0, 0, -9.918023, -740.4199, 9.010332, 2.059489, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7107;

INSERT INTO creature_addon VALUES 
(7107, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7157;
INSERT INTO creature VALUES 
(7157, 657, 36, 0, 0, 3, 231, 0, 0, 0, -41.58344, -788.5656, 18.79488, 4.869469, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7157;

INSERT INTO creature_addon VALUES 
(7157, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7219;
INSERT INTO creature VALUES 
(7219, 657, 36, 0, 0, 3, 231, 0, 0, 0, -41.9822, -798.9504, 39.49167, 5.916666, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7219;

INSERT INTO creature_addon VALUES 
(7219, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=7221;
INSERT INTO creature VALUES 
(7221, 657, 36, 0, 0, 3, 231, 0, 0, 0, 6.701226, -766.3807, 9.713189, 2.251475, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=7221;

INSERT INTO creature_addon VALUES 
(7221, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=9089;
INSERT INTO creature VALUES 
(9089, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -21.87397, -802.9406, 19.76329, 1.727876, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=9089;

INSERT INTO creature_addon VALUES 
(9089, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=10755;
INSERT INTO creature VALUES 
(10755, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -116.1847, -837.8405, 17.12631, 3.752458, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=10755;

INSERT INTO creature_addon VALUES 
(10755, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=1732 AND guid=23423;
INSERT INTO creature VALUES 
(23423, 1732, 36, 0, 0, 3, 231, 0, 0, 0, -19.51221, -830.9886, 19.89779, 5.899213, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=23423;

INSERT INTO creature_addon VALUES 
(23423, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42287;
INSERT INTO creature VALUES 
(42287, 657, 36, 0, 0, 3, 231, 0, 0, 0, -20.79747, -835.3904, 19.74278, 3.630285, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42287;

INSERT INTO creature_addon VALUES 
(42287, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42308;
INSERT INTO creature VALUES 
(42308, 657, 36, 0, 0, 3, 231, 0, 0, 0, -85.11046, -856.5533, 17.3856, 3.368485, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42308;

INSERT INTO creature_addon VALUES 
(42308, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42322;
INSERT INTO creature VALUES 
(42322, 657, 36, 0, 0, 3, 231, 0, 0, 0, -141.8611, -874.6312, 1.583545, 4.031711, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42322;

INSERT INTO creature_addon VALUES 
(42322, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42326;
INSERT INTO creature VALUES 
(42326, 657, 36, 0, 0, 3, 231, 0, 0, 0, -154.9963, -891.8146, 5.643324, 3.054326, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42326;

INSERT INTO creature_addon VALUES 
(42326, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42335;
INSERT INTO creature VALUES 
(42335, 657, 36, 0, 0, 3, 231, 0, 0, 0, -146.1408, -906.0359, 8.178946, 4.049164, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42335;

INSERT INTO creature_addon VALUES 
(42335, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42342;
INSERT INTO creature VALUES 
(42342, 657, 36, 0, 0, 3, 231, 0, 0, 0, -153.1819, -908.9996, 8.727186, 2.617994, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42342;

INSERT INTO creature_addon VALUES 
(42342, 0, 0, 0, 1, 0, "29266");

DELETE FROM creature WHERE id=657 AND guid=42392;
INSERT INTO creature VALUES 
(42392, 657, 36, 0, 0, 3, 231, 0, 0, 0, -149.1771, -918.8044, 12.4227, 2.408554, 120, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM creature_addon WHERE guid=42392;

INSERT INTO creature_addon VALUES 
(42392, 0, 0, 0, 1, 0, "29266");





