

DELETE FROM creature_text WHERE entry=48051;
INSERT INTO creature_text VALUES 
(48051, 1, 0, "I bring you back from the brink of death, $Gbrother:sister;. We are in need of your aid!", 12, 0, 100, 1, 0, 0, "Thrall", 48336),
(48051, 2, 0, "NOBUNDO! NOOO!", 12, 0, 100, 0, 0, 0, "Thrall", 48377),
(48051, 3, 0, "You will die this day, Earthwarder! $n will see to it!", 14, 0, 100, 0, 0, 0, "Thrall", 48379),
(48051, 4, 0, "Aggra... this can't be... this has gone too far...", 12, 0, 100, 0, 0, 0, "Thrall", 48380),
(48051, 5, 0, "Do something, you useless $r. My allies are giving their lives for you!", 12, 0, 100, 0, 0, 0, "Thrall", 48381),
(48051, 6, 0, "Muln falls! And the Earthen Ring dies with him.", 12, 0, 100, 0, 0, 0, "Thrall", 48382),
(48051, 7, 0, "You've failed us all, $n. Deathwing has won. The world is doomed.", 12, 0, 100, 0, 0, 0, "Thrall", 48383),
(48051, 8, 0, "We're surrounded! Its defenses are too great. $n! Wake up!", 12, 0, 100, 0, 0, 0, "Thrall", 48386);

delete from creature_equip_template where entry=45006 and id=2;

delete from smart_scripts where entryorguid=45005;

UPDATE creature_template SET AIName="", ScriptName="npc_wyvern_45005" WHERE entry=45005;

delete from creature_equip_template where entry=45028 and id=1;
insert into creature_equip_template values 
(45028, 1, 58137, 57763, 0); 

DELETE FROM creature_text WHERE entry=45006;
INSERT INTO creature_text VALUES 
(45006, 1, 0, "I hope you have a strong stomach.  Travelling through the breach is not for the weak.", 12, 0, 100, 0, 0, 22606, "Aggra", 45169),
(45006, 2, 0, "We're at the center of the Maelstrom, the rift between Deepholm and Azeroth.  Watch as it threatens to tear your world apart!", 12, 0, 100, 0, 0, 22607, "Aggra", 45170),
(45006, 3, 0, "Let us hope Thrall and the others can contain it while you're inside.", 12, 0, 100, 0, 0, 22608, "Aggra", 45171),
(45006, 4, 0, "This is it!  Brace yourself!", 14, 0, 100, 0, 0, 22609, "Aggra", 45172),
(45006, 5, 0, "You made it!  Good!", 12, 0, 100, 4, 0, 22610, "Aggra", 45175),
(45006, 6, 0, "This is the Temple of Earth.  It's the most important structure in Deepholm.", 12, 0, 100, 0, 0, 22611, "Aggra", 45176),
(45006, 7, 0, "There was once a Titan-made stone inside.  It was known as the World Pillar.  The name was literal.  It bore the weight of all the elemental and magnetic forces in Deepholm.", 12, 0, 100, 0, 0, 22612, "Aggra", 45180),
(45006, 8, 0, "It was shattered when Deathwing broke through the dome above and created the rift between the two worlds.  All of Deepholm is going to collapse into Azeroth if we do not put the World Pillar back together.", 12, 0, 100, 0, 0, 22613, "Aggra", 45182),
(45006, 9, 0, "The first fragment was going to be delivered to us by a Horde gunship known as the Storm's Fury.  It never made it here.", 12, 0, 100, 0, 0, 22614, "Aggra", 45186),
(45006, 10, 0, "We've taken control of the temple and we're containing as much of the damage as we can.  Go inside and speak to Maruut; he's in charge.", 12, 0, 100, 0, 0, 22615, "Aggra", 45187),
(45006, 11, 0, "We are all counting on you.", 12, 0, 100, 0, 0, 22616, "Aggra", 45191);

DELETE FROM creature_equip_template WHERE entry=43138;
INSERT INTO creature_equip_template VALUES 
(43138, 1, 49198, 0, 0), -- Stonehearth Defender
(43138, 2, 39447, 0, 0), -- Stonehearth Defender
(43138, 3, 57125, 0, 0), -- Stonehearth Defender
(43138, 4, 56172, 0, 0), -- Stonehearth Defender
(43138, 5, 57011, 0, 0), -- Stonehearth Defender
(43138, 6, 57009, 0, 0), -- Stonehearth Defender
(43138, 7, 41980, 0, 0), -- Stonehearth Defender
(43138, 8, 57186, 0, 0); -- Stonehearth Defender

DELETE FROM creature_equip_template WHERE entry=43229;
INSERT INTO creature_equip_template VALUES 
(43229, 1, 57125, 0, 0), -- Injured Earthen
(43229, 2, 42165, 0, 0), -- Injured Earthen
(43229, 3, 57011, 0, 0), -- Injured Earthen
(43229, 4, 49198, 0, 0), -- Injured Earthen
(43229, 5, 39447, 0, 0), -- Injured Earthen
(43229, 6, 57186, 0, 0), -- Injured Earthen
(43229, 7, 56172, 0, 0), -- Injured Earthen
(43229, 8, 57009, 0, 0); -- Injured Earthen

DELETE FROM creature_equip_template WHERE entry=43232;
INSERT INTO creature_equip_template VALUES 
(43232, 1, 41980, 0, 0), -- Earthen Champion
(43232, 2, 49198, 0, 0), -- Earthen Champion
(43232, 3, 56172, 0, 0), -- Earthen Champion
(43232, 4, 39447, 0, 0), -- Earthen Champion
(43232, 5, 57011, 0, 0), -- Earthen Champion
(43232, 6, 57009, 0, 0), -- Earthen Champion
(43232, 7, 57125, 0, 0), -- Earthen Champion
(43232, 8, 57186, 0, 0); -- Earthen Champion

DELETE FROM creature_equip_template WHERE entry=44855;
INSERT INTO creature_equip_template VALUES 
(44855, 1, 60759, 0, 0),
(44855, 2, 60208, 0, 0); -- Twilight Cryptomancer

DELETE FROM creature_equip_template WHERE entry=44998;
INSERT INTO creature_equip_template VALUES 
(44998, 1, 58804, 0, 0); -- Earthen Ring Shaman

DELETE FROM creature_equip_template WHERE entry=44956;
INSERT INTO creature_equip_template VALUES 
(44956, 1, 58137, 57763, 0); -- Stormcaller Mylra

DELETE FROM creature_equip_template WHERE entry=42892;
INSERT INTO creature_equip_template VALUES 
(42892, 1, 58137, 57763, 0); -- Stormcaller Mylra

DELETE FROM creature_equip_template WHERE entry=43405;
INSERT INTO creature_equip_template VALUES 
(43405, 1, 39749, 0, 0); -- Mariahn the Soulcleanser

DELETE FROM creature_equip_template WHERE entry=43397;
INSERT INTO creature_equip_template VALUES 
(43397, 1, 39749, 0, 0); -- Seer Kormo

DELETE FROM creature_equip_template WHERE entry=42573;
INSERT INTO creature_equip_template VALUES 
(42573, 1, 50050, 23907, 0); -- Earthcaller Yevaa

DELETE FROM creature_equip_template WHERE entry=43065;
INSERT INTO creature_equip_template VALUES 
(43065, 1, 27862, 0, 0); -- Maruut Stonebinder

DELETE FROM creature_equip_template WHERE entry=51060;
INSERT INTO creature_equip_template VALUES 
(51060,1,1908,0,0);

DELETE FROM creature_equip_template WHERE entry=51065;
INSERT INTO creature_equip_template VALUES 
(51065,1,27862,0,0);

DELETE FROM creature_text WHERE entry=44936;
INSERT INTO creature_text VALUES 
(44936, 1, 0, "You no take crate!", 14, 0, 100, 0, 0, 0, "Murkstone Trogg", 45324);

DELETE FROM creature_text WHERE entry=45099;
INSERT INTO creature_text VALUES 
(45099, 1, 0, "Deepholm? I hate this place. Wait... you're not Initiate Goldmine!", 14, 0, 100, 0, 0, 0, "Magmatooth", 45238);

DELETE FROM creature_text WHERE entry=42757;
INSERT INTO creature_text VALUES 
(42757, 1, 0, "Twilight scum!  You did this to us!", 12, 0, 100, 0, 0, 0, "Slain Crew Member's Spirit", 42637);

DELETE FROM creature_text WHERE entry=43032;
INSERT INTO creature_text VALUES 
(43032, 1, 0, "The cannoneer's hands are black with gunpowder.", 42, 0, 100, 0, 0, 0, "Slain Cannoneer", 42916);

DELETE FROM creature_text WHERE entry=43082;
INSERT INTO creature_text VALUES 
(43082, 1, 0, "Thanks... this'll give us a couple more hours of not running into the rocks.  No guarantees after that.", 12, 0, 100, 0, 0, 0, "First Mate Moody", 45325);

DELETE FROM creature_text WHERE entry=51434;
INSERT INTO creature_text VALUES 
(51434, 1, 0, "The fragment is now in the dragon's custody, ma'am.", 12, 0, 100, 0, 0, 20886, "Millhouse Manastorm", 45013);

DELETE FROM creature_text WHERE entry=43047;
INSERT INTO creature_text VALUES 
(43047, 1, 0, "I am ready to meet with your so-called Earthcaller.", 12, 0, 100, 1, 0, 0, "Flint Oremantle", 42941);

DELETE FROM creature_text WHERE entry=44148;
INSERT INTO creature_text VALUES 
(44148, 1, 0, "You hear rustling of heavy wings in the distance.  The matriarch approaches!", 42, 0, 100, 0, 0, 0, "Stonescale Matriarch", 45016);

DELETE FROM creature_text WHERE entry=44967;
INSERT INTO creature_text VALUES 
(44967, 1, 0, "No! I won't let you interfere!  My transformation is not yet complete!", 12, 0, 100, 0, 0, 0, "Maziel", 45152);

DELETE FROM creature_text WHERE entry=42573;
INSERT INTO creature_text VALUES 
(42573, 1, 0, "What have we here, $n?", 12, 0, 100, 0, 0, 0, "Earthcaller Yevaa", 42927);

DELETE FROM creature_text WHERE entry=43048;
INSERT INTO creature_text VALUES 
(43048, 1, 0, "The Captain's Log lies nearby.", 42, 0, 100, 0, 0, 0, "Captain Skullshatter", 42930);

DELETE FROM creature_text WHERE entry=42801;
INSERT INTO creature_text VALUES 
(42801, 1, 0, "Ok, ok, I give up!  I'll tell you everything!", 12, 0, 100, 0, 0, 20988, "Mor'norokk the Hateful", 42813);

DELETE FROM creature_text WHERE entry=44289;
INSERT INTO creature_text VALUES 
(44289, 0, 0, "Abyssion is casting a powerful Shadow Nova, seek cover!", 41, 0, 100, 0, 0, 0, "Abyssion", 44528),
(44289, 1, 0, "Abyssion is approaching.  Get ready!", 42, 0, 100, 0, 0, 0, "Abyssion", 45148);

DELETE FROM creature_text WHERE entry=43346;
INSERT INTO creature_text VALUES 
(43346, 1, 0, "I thought we'd killed everybody... Mor'norokk should be pleased with this!", 12, 0, 100, 0, 0, 0, "Twilight Saboteur", 43377);

DELETE FROM creature_text WHERE entry=42747;
INSERT INTO creature_text VALUES 
(42747, 1, 0, "Everyone started dropping like flies... everyone who ate the rations.", 12, 0, 100, 0, 0, 0, "Slain Crew Member's Spirit", 42636);

DELETE FROM creature_text WHERE entry=44956;
INSERT INTO creature_text VALUES 
(44956, 1, 0, "He's coming.  Get ready, lads!", 14, 0, 100, 0, 0, 0, "Stormcaller Mylra", 45100);

DELETE FROM creature_text WHERE entry=47195;
INSERT INTO creature_text VALUES 
(47195, 1, 0, "$C, over here.", 12, 0, 100, 0, 0, 0, "Slate Quicksand", 44485);

DELETE FROM creature_text WHERE entry=42574;
INSERT INTO creature_text VALUES 
(42574, 1, 0, "Eureka!", 12, 0, 100, 0, 0, 0, "Initiate Goldmine", 43515);

DELETE FROM creature_text WHERE entry=43026;
INSERT INTO creature_text VALUES 
(43026, 1, 0, "You do not belong here!", 12, 0, 100, 0, 0, 0, "Deepstone Elemental", 42903);

DELETE FROM creature_text WHERE entry=44881;
INSERT INTO creature_text VALUES 
(44881, 1, 0, "Forgemaster!  I've been informed the enemy has disrupted your operations.  Where is the fragment?", 14, 0, 100, 0, 0, 21623, "High Priestess Azil", 45010);

DELETE FROM creature_text WHERE entry=45027;
INSERT INTO creature_text VALUES 
(45027, 1, 0, "You made it!  Good!", 12, 0, 100, 4, 0, 22610, "Aggra", 45175);

DELETE FROM creature_text WHERE entry=43044;
INSERT INTO creature_text VALUES 
(43044, 1, 0, "The shell's markings read: \"STORMWIND ROYAL INDUSTRIES\"", 42, 0, 100, 0, 0, 0, "Unexploded Artillery Shell", 42942);

DELETE FROM creature_text WHERE entry=44768;
INSERT INTO creature_text VALUES 
(44768, 1, 0, "Thank you... I wish I could help you find the forgemaster.", 12, 0, 100, 0, 0, 0, "Enslaved Miner", 44848);

DELETE FROM creature_text WHERE entry=42892;
INSERT INTO creature_text VALUES 
(42892, 1, 0, "Over here, you ugly whale!", 12, 0, 100, 0, 0, 21001, "Stormcaller Mylra", 42799);

DELETE FROM creature_text WHERE entry=44879;
INSERT INTO creature_text VALUES 
(44879, 1, 0, "Here she comes, boss!", 14, 0, 100, 0, 0, 0, "Ogre Bodyguard", 45075);

DELETE FROM creature_text WHERE entry=42965;
INSERT INTO creature_text VALUES 
(42965, 1, 0, "All right, sunshine.  Time to spill your guts before I spill 'em for ya!", 12, 0, 100, 0, 0, 21003, "Stormcaller Mylra", 43166);

DELETE FROM creature_text WHERE entry=42964;
INSERT INTO creature_text VALUES 
(42964, 1, 0, "Wait!  You can't do this!  You people must have a code of honor or something!", 14, 0, 100, 0, 0, 20992, "Mor'norokk the Hateful", 43167);

delete from vehicle_template_accessory where entry=42962 and accessory_entry=42964;
delete from vehicle_template_accessory where entry=42962 and accessory_entry=42965;
delete from vehicle_template_accessory where entry=42887 and accessory_entry=42892;
delete from vehicle_template_accessory where entry=43046 and accessory_entry=43044;
delete from vehicle_template_accessory where entry=45024 and accessory_entry=45027;
delete from vehicle_template_accessory where entry=45004 and accessory_entry=45028;

INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(42962, 42964, 1, 1, 'Stormbeak - Mor''norokk the Hateful', 7, 0), -- Stormbeak - Mor'norokk the Hateful
(42962, 42965, 0, 1, 'Stormbeak - Stormcaller Mylra', 7, 0), -- Stormbeak - Stormcaller Mylra
(42887, 42892, 0, 1, 'Stormbeak - Stormcaller Mylra', 7, 0), -- Stormbeak - Stormcaller Mylra
(43046, 43044, 0, 1, 'Unexploded Artillery Shell Mount - Unexploded Artillery Shell', 7, 0), -- Unexploded Artillery Shell Mount - Unexploded Artillery Shell
(45024, 45027, 0, 1, 'Wyvern - Aggra', 7, 0), -- Wyvern - Aggra
(45004, 45028, 0, 1, 'Wyvern - Aggra', 7, 0); -- Wyvern - Aggra

DELETE FROM gossip_menu_option WHERE menu_id=12009 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(12009, 0, 0, "I've come at your call, Stonemother.", 45522, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM creature_text WHERE entry=42781;
INSERT INTO creature_text VALUES 
(42781, 1, 0, "The line is secured to his ankle.  Pull away to trip him!", 42, 0, 100, 0, 0, 0, "Servant of Therazane", 42798);

DELETE FROM creature_text WHERE entry=44153;
INSERT INTO creature_text VALUES 
(44153, 1, 0, "Let me out of these chains! I'll reduce you to rubble!", 14, 0, 100, 0, 0, 0, "Stonefather Oremantle", 44422);

DELETE FROM creature_text WHERE entry=44353;
INSERT INTO creature_text VALUES 
(44353, 1, 0, "By the elements... that one... just wouldn't die...", 12, 0, 100, 396, 0, 0, "Stormcaller Mylra", 42683);

DELETE FROM creature_text WHERE entry=43229;
INSERT INTO creature_text VALUES 
(43229, 1, 0, "Don't worry about me. We have to rescue the king!", 12, 0, 100, 5, 0, 0, "Injured Earthen", 43418);

DELETE FROM creature_text WHERE entry=44143;
INSERT INTO creature_text VALUES 
(44143, 1, 0, "Don't forget to grab a war guardian, $n.", 12, 0, 100, 0, 0, 0, "Slate Quicksand", 44417);

DELETE FROM creature_text WHERE entry=43897;
INSERT INTO creature_text VALUES 
(43897, 1, 0, "$n, you're going to want to fly over these giants and stone troggs. Don't try to ride through them.", 12, 0, 100, 0, 0, 0, "Pyrium Lodestone", 44350);

DELETE FROM creature_text WHERE entry=43898;
INSERT INTO creature_text VALUES 
(43898, 1, 0, "$n? It's about time you got here. What kept you? My father's life is in jeopardy!", 12, 0, 100, 0, 0, 0, "Flint Oremantle", 44324);

DELETE FROM creature_text WHERE entry=42573 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(42573, 2, 0, "$n, you've returned! Is that the middle fragment?", 12, 0, 100, 0, 0, 0, "Earthcaller Yevaa", 44976);

DELETE FROM creature_text WHERE entry=43984 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(43984, 1, 0, "Reactivated.", 12, 0, 100, 0, 0, 0, "Deactivated War Construct", 44354);

DELETE FROM creature_text WHERE entry=47197;
INSERT INTO creature_text VALUES 
(47197, 1, 0, "Huzzah!", 14, 0, 100, 0, 0, 0, "Flint Oremantle", 47296);

DELETE FROM creature_text WHERE entry=42479;
INSERT INTO creature_text VALUES 
(42479, 1, 0, "The line is secured to his ankle.  Pull away to trip him!", 42, 0, 100, 0, 0, 0, "Servant of Therazane", 42798);

DELETE FROM creature_text WHERE entry=43635;
INSERT INTO creature_text VALUES 
(43635, 1, 0, "Alright, here we go!", 14, 0, 100, 25, 0, 0, "Catapult Driver", 45199);

DELETE FROM creature_text WHERE entry=43160;
INSERT INTO creature_text VALUES 
(43160, 1, 0, "Do you want to live forever?", 14, 0, 100, 0, 0, 0, "Earthbreaker Dolomite", 43146);

DELETE FROM creature_text WHERE entry=44204;
INSERT INTO creature_text VALUES 
(44204, 1, 0, "All hail, $n! Huzzah!", 14, 0, 100, 0, 0, 0, "Stonefather Oremantle", 47295);

DELETE FROM creature_text WHERE entry=24288;
INSERT INTO creature_text VALUES 
(24288, 1, 0, "Stone troggs are attacking!", 42, 0, 100, 0, 0, 0, "ELM General Purpose Bunny Hide Body", 45178);

DELETE FROM creature_text WHERE entry=43456;
INSERT INTO creature_text VALUES 
(43456, 1, 0, "PULVERIZE!", 14, 0, 100, 0, 0, 0, "Troggzor the Earthinator", 43547);

DELETE FROM creature_text WHERE entry=44835;
INSERT INTO creature_text VALUES 
(44835, 1, 0, "You will be destroyed!", 14, 0, 100, 0, 0, 0, "Haethen Kaul", 44974);

DELETE FROM creature_text WHERE entry=44152;
INSERT INTO creature_text VALUES 
(44152, 1, 0, "$n! You're a sight for sore eyes. Get over here and give me a hand, would you?", 14, 0, 100, 0, 0, 0, "Flint Oremantle", 44430);

DELETE FROM creature_text WHERE entry=43071;
INSERT INTO creature_text VALUES 
(43071, 1, 0, "Indeed!", 12, 0, 100, 0, 0, 0, "Crag Rockcrusher", 47297);

DELETE FROM creature_text WHERE entry=45043;
INSERT INTO creature_text VALUES 
(45043, 1, 0, "Let me know when you're ready, $n.", 12, 0, 100, 0, 0, 0, "Peak Grindstone", 45278);

DELETE FROM creature_text WHERE entry=43168;
INSERT INTO creature_text VALUES 
(43168, 1, 0, "One of Clay's catapult teams is broken down on the front. $n, I need you to get some parts from him and get that catapult back in the fight!", 12, 0, 100, 0, 0, 0, "Gravel Longslab", 47195);

delete from vehicle_template_accessory where entry=42788 and accessory_entry=47170;
delete from vehicle_template_accessory where entry=44352 and accessory_entry=47173;
delete from vehicle_template_accessory where entry=44353 and accessory_entry=47172;
delete from vehicle_template_accessory where entry=43952 and accessory_entry=45064;
delete from vehicle_template_accessory where entry=43509 and accessory_entry=43635;

INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(42788, 47170, 0, 1, 'Hargoth Dimblaze - Therazane Siege Arrow Bunny, 1', 7, 0), -- Hargoth Dimblaze - Therazane Siege Arrow Bunny, 1
(44352, 47173, 0, 1, 'Tawn Winterbluff - Therazane Siege Arrow Bunny, 3', 7, 0), -- Tawn Winterbluff - Therazane Siege Arrow Bunny, 3
(44353, 47172, 0, 1, 'Stormcaller Mylra - Therazane Siege Arrow Bunny, 2', 7, 0), -- Stormcaller Mylra - Therazane Siege Arrow Bunny, 2
(43952, 45064, 0, 1, 'Earthen Catapult - Catapult Driver', 7, 0), -- Earthen Catapult - Catapult Driver
(43509, 43635, 0, 1, 'Earthen Catapult - Catapult Driver', 7, 0); -- Earthen Catapult - Catapult Driver

DELETE FROM creature_equip_template WHERE entry=44802;
INSERT INTO creature_equip_template VALUES 
(44802, 1, 4090, 0, 0), -- Prospector Brewer
(44802, 2, 2202, 0, 0); -- Prospector Brewer

DELETE FROM creature_equip_template WHERE entry=44673;
INSERT INTO creature_equip_template VALUES 
(44673, 1, 58137, 57763, 0); -- Stormcaller Mylra

DELETE FROM creature_equip_template WHERE entry=44769;
INSERT INTO creature_equip_template VALUES 
(44769, 1, 57130, 0, 0); -- Twilight Desecrator

DELETE FROM creature_equip_template WHERE entry=43837;
INSERT INTO creature_equip_template VALUES 
(43837, 1, 56232, 56232, 0); -- High Priestess Lorthuna

DELETE FROM creature_equip_template WHERE entry=44668;
INSERT INTO creature_equip_template VALUES 
(44668, 1, 39749, 28737, 0); -- Seer Galekk

DELETE FROM creature_equip_template WHERE entry=44675;
INSERT INTO creature_equip_template VALUES 
(44675, 1, 32946, 32945, 0); -- Hargoth Dimblaze

DELETE FROM creature_equip_template WHERE entry=44676;
INSERT INTO creature_equip_template VALUES 
(44676, 1, 50050, 23907, 0); -- Earthcaller Yevaa

DELETE FROM creature_equip_template WHERE entry=44677;
INSERT INTO creature_equip_template VALUES 
(44677, 1, 49713, 56175, 0); -- Windspeaker Lorvarius

DELETE FROM creature_equip_template WHERE entry=44667;
INSERT INTO creature_equip_template VALUES 
(44667, 1, 39749, 0, 0); -- Seer Kormo

DELETE FROM creature_equip_template WHERE entry=44678;
INSERT INTO creature_equip_template VALUES 
(44678, 1, 39749, 28737, 0); -- Mariahn the Soulcleanser

DELETE FROM creature_equip_template WHERE entry=44680;
INSERT INTO creature_equip_template VALUES 
(44680, 1, 56067, 56067, 0); -- Twilight Defiler

DELETE FROM creature_equip_template WHERE entry=43818;
INSERT INTO creature_equip_template VALUES 
(43818, 1, 27862, 0, 0); -- Maruut Stonebinder

DELETE FROM creature_equip_template WHERE entry=44671;
INSERT INTO creature_equip_template VALUES 
(44671, 1, 56913, 56913, 0); -- Tharm Wildfire

DELETE FROM creature_equip_template WHERE entry=44666;
INSERT INTO creature_equip_template VALUES 
(44666, 1, 56193, 30391, 0); -- Earthmender Norsala

DELETE FROM creature_equip_template WHERE entry=43835;
INSERT INTO creature_equip_template VALUES 
(43835, 1, 40501, 49720, 0); -- Earthcaller Torunscar

DELETE FROM creature_equip_template WHERE entry=44674;
INSERT INTO creature_equip_template VALUES 
(44674, 1, 42939, 56174, 0); -- Tawn Winterbluff

DELETE FROM creature_equip_template WHERE entry=44672;
INSERT INTO creature_equip_template VALUES 
(44672, 1, 42939, 56174, 0); -- Stormcaller Jalara

DELETE FROM creature_equip_template WHERE entry=44681;
INSERT INTO creature_equip_template VALUES 
(44681, 1, 55224, 0, 0); -- Twilight Heretic

DELETE FROM creature_equip_template WHERE entry=42918;
INSERT INTO creature_equip_template VALUES 
(42918, 1, 58176, 0, 57176); -- Zoltrik Drakebane

DELETE FROM creature_equip_template WHERE entry=42914;
INSERT INTO creature_equip_template VALUES 
(42914, 1, 56232, 56232, 0); -- High Priestess Lorthuna

DELETE FROM creature_equip_template WHERE entry=42923;
INSERT INTO creature_equip_template VALUES 
(42923, 1, 52519, 0, 0); -- Boldrich Stonerender

DELETE FROM creature_equip_template WHERE entry=42916;
INSERT INTO creature_equip_template VALUES 
(42916, 1, 52060, 0, 0); -- Twilight Soulreaper

DELETE FROM creature_equip_template WHERE entry=45034;
INSERT INTO creature_equip_template VALUES 
(45034, 1, 56913, 56913, 0); -- Yuldris Smolderfury

DELETE FROM creature_equip_template WHERE entry=44634;
INSERT INTO creature_equip_template VALUES 
(44634, 1, 42939, 56174, 0); -- Tawn Winterbluff

DELETE FROM creature_equip_template WHERE entry=44631;
INSERT INTO creature_equip_template VALUES 
(44631, 1, 56913, 56913, 0); -- Tharm Wildfire

DELETE FROM creature_equip_template WHERE entry=44646;
INSERT INTO creature_equip_template VALUES 
(44646, 1, 50050, 23907, 0); -- Earthcaller Yevaa

DELETE FROM creature_equip_template WHERE entry=44644;
INSERT INTO creature_equip_template VALUES 
(44644, 1, 32946, 32945, 0); -- Hargoth Dimblaze

DELETE FROM creature_equip_template WHERE entry=44642;
INSERT INTO creature_equip_template VALUES 
(44642, 1, 58137, 57763, 0); -- Stormcaller Mylra

DELETE FROM creature_equip_template WHERE entry=44633;
INSERT INTO creature_equip_template VALUES 
(44633, 1, 42939, 56174, 0); -- Stormcaller Jalara

DELETE FROM creature_equip_template WHERE entry=44647;
INSERT INTO creature_equip_template VALUES 
(44647, 1, 39749, 0, 0); -- Mariahn the Soulcleanser

DELETE FROM creature_equip_template WHERE entry=53738;
INSERT INTO creature_equip_template VALUES 
(53738, 1, 58137, 57763, 0); -- Aggra

DELETE FROM creature_equip_template WHERE entry=43809;
INSERT INTO creature_equip_template VALUES 
(43809, 1, 40501, 49720, 0); -- Earthcaller Torunscar

DELETE FROM creature_equip_template WHERE entry=44350;
INSERT INTO creature_equip_template VALUES 
(44350, 1, 56913, 56913, 0); -- Tharm Wildfire

DELETE FROM creature_equip_template WHERE entry=44353;
INSERT INTO creature_equip_template VALUES 
(44353, 1, 58137, 57763, 0); -- Stormcaller Mylra

DELETE FROM creature_equip_template WHERE entry=44352;
INSERT INTO creature_equip_template VALUES 
(44352, 1, 42939, 56174, 0); -- Tawn Winterbluff

DELETE FROM creature_equip_template WHERE entry=42788;
INSERT INTO creature_equip_template VALUES 
(42788, 1, 32946, 32945, 0); -- Hargoth Dimblaze

DELETE FROM creature_equip_template WHERE entry=42730;
INSERT INTO creature_equip_template VALUES 
(42730, 1, 40501, 49720, 0); -- Earthcaller Torunscar

DELETE FROM creature_equip_template WHERE entry=42731;
INSERT INTO creature_equip_template VALUES 
(42731, 1, 56193, 30391, 0); -- Earthmender Norsala

DELETE FROM creature_equip_template WHERE entry=42779;
INSERT INTO creature_equip_template VALUES 
(42779, 1, 1011, 1011, 0),
(42779, 2, 56913, 56913, 0); -- Exhausted Earthguard Sentinel

delete from vehicle_template_accessory where entry=48640 and accessory_entry=48639;
delete from vehicle_template_accessory where entry=42543 and accessory_entry=42711;
delete from vehicle_template_accessory where entry=48642 and accessory_entry=48639;
delete from vehicle_template_accessory where entry=48642 and accessory_entry=44135;
delete from vehicle_template_accessory where entry=43116 and accessory_entry=43182;

INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(48640, 48639, 0, 1, 'Enormous Gyreworm Bunny - Ruby Gemstone Cluster', 7, 0), -- Enormous Gyreworm Bunny - Ruby Gemstone Cluster
(42543, 42711, 0, 1, 'Crystal Gorged Basilisk - Verlok Basilisk Rider', 7, 0), -- Crystal Gorged Basilisk - Verlok Basilisk Rider
(48642, 48639, 0, 1, 'Enormous Gyreworm Bunny - Ruby Gemstone Cluster', 7, 0), -- Enormous Gyreworm Bunny - Ruby Gemstone Cluster
(44136, 44135, 0, 1, 'Zoltrik''s Pyremaw - Zoltrik Drakebane', 7, 0), -- Zoltrik's Pyremaw - Zoltrik Drakebane
(43116, 43182, 7, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 6, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 5, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 4, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 3, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 2, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 1, 1, 'Pebble - Petrified Stone Bat', 7, 0), -- Pebble - Petrified Stone Bat
(43116, 43182, 0, 1, 'Pebble - Petrified Stone Bat', 7, 0); -- Pebble - Petrified Stone Bat

DELETE FROM creature_text WHERE entry=45191;
INSERT INTO creature_text VALUES 
(45191, 1, 0, "This rock is about to fall! Jump to another!", 41, 0, 100, 0, 0, 0, "Boulder Platform", 45372);

DELETE FROM creature_text WHERE entry=44646;
INSERT INTO creature_text VALUES 
(44646, 1, 0, "Understood. I'll head there right away.", 12, 0, 100, 378, 0, 0, "Earthcaller Yevaa", 44682);

DELETE FROM creature_text WHERE entry=43116;
INSERT INTO creature_text VALUES 
(43116, 1, 0, "You hear the sound of shuffling stones behind you.", 16, 0, 100, 0, 0, 0, "Pebble", 43132);

DELETE FROM creature_text WHERE entry=43503;
INSERT INTO creature_text VALUES 
(43503, 1, 0, "Let's finish with this quickly.", 12, 0, 100, 0, 0, 21030, "Earthmender Norsala", 43580);

DELETE FROM creature_text WHERE entry=42900;
INSERT INTO creature_text VALUES 
(42900, 1, 0, "The rockling looks up at you questioningly.", 16, 0, 100, 0, 0, 0, "Quartz Rockling", 47250);

DELETE FROM creature_text WHERE entry=44135;
INSERT INTO creature_text VALUES 
(44135, 1, 0, "Ya need ta be more swift den that!", 14, 0, 100, 0, 0, 21616, "Zoltrik Drakebane", 43906);

DELETE FROM creature_text WHERE entry=43641;
INSERT INTO creature_text VALUES 
(43641, 1, 0, "The Stone Dragon Broodmother bows her head in surrender.", 41, 0, 100, 0, 0, 0, "Aeosera", 44305);

DELETE FROM creature_text WHERE entry=45034;
INSERT INTO creature_text VALUES 
(45034, 1, 0, "Got it. I'll head there right away.", 12, 0, 100, 378, 0, 0, "Yuldris Smolderfury", 44676);

DELETE FROM creature_text WHERE entry=44353 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(44353, 2, 0, "Careful out here, they don't stop coming.", 12, 0, 100, 396, 0, 0, "Stormcaller Mylra", 42686);

DELETE FROM creature_text WHERE entry=43901;
INSERT INTO creature_text VALUES 
(43901, 1, 0, "We came here to seal da rift Deathwing tore into Azeroth. We need the World Pillar to repair da hole on dis side.", 12, 0, 100, 1, 0, 21117, "Earthcaller Torunscar", 43879);

DELETE FROM creature_text WHERE entry=42788;
INSERT INTO creature_text VALUES 
(42788, 1, 0, "A chance to catch my breath! Thank you.", 12, 0, 100, 396, 0, 0, "Hargoth Dimblaze", 42682);

DELETE FROM creature_text WHERE entry=42468;
INSERT INTO creature_text VALUES 
(42468, 1, 0, "You've come to prove yourself, fleshling?  The Crumbling Depths lie northeast.  The stone you seek is within.", 12, 0, 100, 1, 0, 21767, "Felsen the Enduring", 43853);

DELETE FROM creature_text WHERE entry=42914;
INSERT INTO creature_text VALUES 
(42914, 1, 0, "Therazane's finally gathered the nerve to challenge us, has she?", 12, 0, 100, 0, 0, 20933, "High Priestess Lorthuna", 43910);

DELETE FROM creature_text WHERE entry=44137;
INSERT INTO creature_text VALUES 
(44137, 1, 0, "If you can't fight Zoltrik at range, use your Jump Drakes! ability:$B|TInterface\Icons\ability_vehicle_launchplayer.blp:64|t", 42, 0, 100, 0, 0, 0, "Crystalspire Stone Drake", 47286);

DELETE FROM creature_text WHERE entry=42923;
INSERT INTO creature_text VALUES 
(42923, 1, 0, "Deathwing will have his way with your Stonemother.", 12, 0, 100, 0, 0, 21511, "Boldrich Stonerender", 43901);

DELETE FROM creature_text WHERE entry=43339;
INSERT INTO creature_text VALUES 
(43339, 1, 0, "A Son of Kor has arrived to assist you, but watch out for his boulders!", 41, 0, 100, 0, 0, 0, "Gorgonite", 46710);

DELETE FROM creature_text WHERE entry=42916;
INSERT INTO creature_text VALUES 
(42916, 1, 0, "Deathwing's shadow settles over you.", 12, 0, 100, 0, 0, 0, "Twilight Soulreaper", 42994);

DELETE FROM creature_text WHERE entry=43836;
INSERT INTO creature_text VALUES 
(43836, 1, 0, "Elements be with us.", 12, 0, 100, 378, 0, 0, "Windspeaker Lorvarius", 44677);

DELETE FROM creature_text WHERE entry=42614;
INSERT INTO creature_text VALUES 
(42614, 1, 0, "The Stone Dragons are here, fleshling.  Take wing!", 14, 0, 100, 1, 0, 21652, "Terrath the Steady", 43900);

DELETE FROM creature_text WHERE entry=42792;
INSERT INTO creature_text VALUES 
(42792, 1, 0, "Need a hand?", 12, 0, 100, 396, 0, 0, "Earthguard Sentinel", 42690);

DELETE FROM creature_text WHERE entry=43372;
INSERT INTO creature_text VALUES 
(43372, 1, 0, "No no no! Leave Glop alone! My mushrooms! Mine!", 14, 0, 100, 0, 0, 21769, "Fungalmancer Glop", 43557);

DELETE FROM creature_text WHERE entry=42467;
INSERT INTO creature_text VALUES 
(42467, 1, 0, "Not wasted, Stonemother.  It has been very useful.", 12, 0, 100, 1, 0, 21757, "Diamant the Patient", 43842);

DELETE FROM creature_text WHERE entry=43802;
INSERT INTO creature_text VALUES 
(43802, 1, 0, "Is this the one you are wasting your time with, Diamant?", 12, 0, 100, 1, 0, 21087, "Therazane", 43848);

DELETE FROM creature_text WHERE entry=43837;
INSERT INTO creature_text VALUES 
(43837, 1, 0, "Your tale ends here, shaman. ", 12, 0, 100, 0, 0, 20938, "High Priestess Lorthuna", 43938);

DELETE FROM creature_text WHERE entry=44631;
INSERT INTO creature_text VALUES 
(44631, 1, 0, "I'm glad to hear we're fighting along side the Stonemother herself this time.", 12, 0, 100, 378, 0, 0, "Tharm Wildfire", 44679);

DELETE FROM creature_text WHERE entry=44673;
INSERT INTO creature_text VALUES 
(44673, 1, 0, "The cult is upon us! We need help in the Respite Chambers!", 14, 0, 100, 0, 0, 0, "Stormcaller Mylra", 44804);

DELETE FROM creature_text WHERE entry=42918;
INSERT INTO creature_text VALUES 
(42918, 1, 0, "Ya handle yaself on da ground.  How about in da skies?", 12, 0, 100, 0, 0, 21615, "Zoltrik Drakebane", 43905);

DELETE FROM creature_text WHERE entry=44352;
INSERT INTO creature_text VALUES 
(44352, 1, 0, "Careful out here, they don't stop coming.", 12, 0, 100, 396, 0, 0, "Tawn Winterbluff", 42686);

DELETE FROM creature_text WHERE entry=44666;
INSERT INTO creature_text VALUES 
(44666, 1, 0, "Thank you, Stonemother.  It was an honor to have...", 12, 0, 100, 0, 0, 21038, "Earthmender Norsala", 43945);

DELETE FROM creature_text WHERE entry=42823;
INSERT INTO creature_text VALUES 
(42823, 1, 0, "There is no hope for enemies of the Twilight!", 12, 0, 100, 0, 0, 0, "Twilight Priestess", 42997);

DELETE FROM creature_text WHERE entry=43792;
INSERT INTO creature_text VALUES 
(43792, 1, 0, "Ma'haat, slaughter these rabble.  I will deal with the fool priestess.", 14, 0, 100, 1, 0, 21085, "Therazane", 43942);

DELETE FROM creature_text WHERE entry=42466;
INSERT INTO creature_text VALUES 
(42466, 1, 0, "Speak with Terrath the Steady when you are ready to begin.", 42, 0, 100, 1, 0, 0, "Terrath the Steady", 44315);

DELETE FROM creature_text WHERE entry=42731;
INSERT INTO creature_text VALUES 
(42731, 1, 0, "So it is certain den. Dese elementals were bound from dormant stone only recently.", 12, 0, 100, 1, 0, 21027, "Earthmender Norsala", 42678);

DELETE FROM creature_text WHERE entry=42465;
INSERT INTO creature_text VALUES 
(42465, 1, 0, "And so the \"champion\" arrives.", 12, 0, 100, 1, 0, 21093, "Therazane", 43869);

DELETE FROM creature_text WHERE entry=42471;
INSERT INTO creature_text VALUES 
(42471, 1, 0, "Hah! Did you mistake me for Diamant, $r? Or perhaps some other whimpering, compliant stone trogg who cares?", 14, 0, 100, 1, 0, 21743, "Boden the Imposing", 42665);

DELETE FROM creature_text WHERE entry=43367;
INSERT INTO creature_text VALUES 
(43367, 1, 0, "Kill! Kill! Kill!", 12, 0, 100, 0, 0, 0, "Verlok Grubthumper", 50149);

DELETE FROM creature_text WHERE entry=43835;
INSERT INTO creature_text VALUES 
(43835, 1, 0, "Stop her!  We can still complete da binding!", 14, 0, 100, 0, 0, 21115, "Earthcaller Torunscar", 43932);

DELETE FROM creature_text WHERE entry=44634;
INSERT INTO creature_text VALUES 
(44634, 1, 0, "Some action. Glad to hear it.", 12, 0, 100, 378, 0, 0, "Tawn Winterbluff", 44678);

DELETE FROM creature_text WHERE entry=43039;
INSERT INTO creature_text VALUES 
(43039, 1, 0, "We are under attack! To arms!", 14, 0, 100, 0, 0, 0, "Twilight Duskwarden", 42983);

DELETE FROM creature_text WHERE entry=42472;
INSERT INTO creature_text VALUES 
(42472, 1, 0, "They are not the Twilight.  I see no reason to oppose their goals.", 12, 0, 100, 1, 0, 21880, "Gorsik the Tumultuous", 43864);

DELETE FROM creature_text WHERE entry=40789;
INSERT INTO creature_text VALUES 
(40789, 1, 0, "The Stone Dragon Broodmother approaches.", 16, 0, 100, 0, 0, 0, "Generic Controller Bunny (CSA)", 44312);





















