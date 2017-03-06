
UPDATE `creature` SET `orientation`=0 WHERE `guid`=181680;

DELETE FROM creature_text WHERE entry=20102 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(20102, 6, 0, "We should go trick or treating later.", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 23286),
(20102, 6, 1, "There MUST be a way to make more money off of this holiday.", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 23299),
(20102, 6, 2, "The innkeepers are mad to be giving away treats for free.", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 23300),
(20102, 6, 3, "For the Alliance! Wait... the Horde! Wait... which was I again?", 12, 0, 100, 4, 0, 149, "Goblin Commoner to Goblin Commoner", 23364),
(20102, 8, 0, "Where are all those wonderful winter hats coming from?", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 16503),
(20102, 8, 1, "Ah, the Winter Wondervolt. What will we think of next?", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 16501),
(20102, 8, 2, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 0, 100, 0, 0, 0, "Goblin Commoner to Goblin Commoner", 16463),
(20102, 8, 3, "Ah, the Winter Wondervolt. What will we think of next?", 12, 0, 100, 274, 0, 0, "Goblin Commoner to Goblin Commoner", 16501);

DELETE FROM creature_text WHERE entry=18927 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(18927, 6, 0, "Brains... braaaiiins!", 12, 7, 100, 15, 0, 0, "Human Commoner to Human Commoner", 23358),
(18927, 6, 1, "We should go trick or treating later.", 12, 7, 100, 396, 0, 0, "Human Commoner to Human Commoner", 24348),
(18927, 6, 2, "Are there any more inns we can visit for treats?", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 23293),
(18927, 6, 3, "We should go trick or treating later.", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 24348),
(18927, 6, 4, "For the Horde!", 12, 7, 100, 274, 0, 0, "Human Commoner to Human Commoner", 23357),
(18927, 6, 5, "What do you think of the mask?", 12, 7, 100, 1, 0, 0, "Human Commoner to Human Commoner", 24339),
(18927, 6, 6, "You know... why DO we celebrate this holiday?", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 23287),
(18927, 8, 0, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 7, 100, 6, 0, 0, "Human Commoner to Human Commoner", 24341),
(18927, 8, 1, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 24341),
(18927, 8, 2, "I should take the tram to Ironforge and visit Greatfather Winter.", 12, 7, 100, 6, 0, 0, "Human Commoner to Human Commoner", 16032),
(18927, 8, 3, "Greatfather Winter will leave presents for everyone under the tree in Ironforge. I can't wait to get mine!", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 16422),
(18927, 8, 4, "Greatfather Winter will leave presents for everyone under the tree in Ironforge. I can't wait to get mine!", 12, 7, 100, 396, 0, 0, "Human Commoner to Human Commoner", 16422),
(18927, 8, 5, "I should take the tram to Ironforge and visit Greatfather Winter.", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 16032),
(18927, 8, 6, "Where are all those wonderful winter hats coming from?", 12, 7, 100, 0, 0, 0, "Human Commoner to Human Commoner", 24342),
(18927, 8, 7, "I should take the tram to Ironforge and visit Greatfather Winter.", 12, 7, 100, 396, 0, 0, "Human Commoner to Human Commoner", 16032);

DELETE FROM creature_text WHERE entry=19177 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(19177, 6, 0, "Next year, I'm dressing up as either a corsair or an assassin.", 12, 1, 100, 1, 0, 0, "Troll Commoner to Troll Commoner", 24336),
(19177, 6, 1, "Happy Hallow's End!", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 24329),
(19177, 6, 2, "What do you think of the mask?", 12, 1, 100, 1, 0, 0, "Troll Commoner to Troll Commoner", 24337),
(19177, 6, 3, "Boo-hoo! I'm a poor little gnome, and I don't have a capital ci... oh, wait.", 12, 1, 100, 1, 0, 0, "Troll Commoner to Troll Commoner", 23354),
(19177, 6, 4, "Someone should make a candy with a chewy gnome center.", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 23297),
(19177, 6, 5, "We should go trick or treating later.", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 24331),
(19177, 6, 6, "I think I've eaten too much candy...", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 24330),
(19177, 8, 0, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 24323),
(19177, 8, 1, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 16464),
(19177, 8, 2, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 1, 100, 0, 0, 0, "Troll Commoner to Troll Commoner", 24324);

DELETE FROM creature_text WHERE entry=19169 AND groupid in (4,6,8);
INSERT INTO creature_text VALUES 
(19169, 4, 0, "The Horde fires will never be extinguished!", 12, 1, 100, 4, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24534),
(19169, 6, 0, "Gaze upon my crazy tentacle-face and despair, Azerothian!", 12, 1, 100, 23, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 23356),
(19169, 6, 1, "Next year, I'm dressing up as either a corsair or an assassin.", 12, 1, 100, 1, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24336),
(19169, 6, 2, "I think I've eaten too much candy...", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24330),
(19169, 6, 3, "What do you think of the mask?", 12, 1, 100, 1, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24337),
(19169, 6, 4, "We should go trick or treating later.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24331),
(19169, 6, 5, "Happy Hallow's End!", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24329),
(19169, 6, 6, "This time of year is quite important to our Forsaken allies.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 23288),
(19169, 6, 7, "For the Alliance!", 12, 1, 100, 4, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 23351),
(19169, 6, 8, "We should attend the next burning of the Wickerman.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 23292),
(19169, 6, 9, "What do you think of the mask?", 12, 1, 100, 273, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24337),
(19169, 8, 0, "Winter Veil has always been a human thing. To see the goblins and orcs take it up is rather strange.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 16173),
(19169, 8, 1, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 16464),
(19169, 8, 2, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 6, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 16464),
(19169, 8, 3, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 0, 0, 0, "Blood Elf Commoner to Blood Elf Commoner", 24323);

DELETE FROM creature_text WHERE entry=19175 AND groupid in (5,6,8);
INSERT INTO creature_text VALUES 
(19175, 5, 0, "Where's me gold? Where's me beer? Where's me feet?", 12, 1, 100, 5, 0, 0, "Orc Commoner to Orc Commoner", 23352),
(19175, 6, 0, "We should go trick or treating later.", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 24331),
(19175, 6, 1, "Happy Hallow's End!", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 24329),
(19175, 6, 2, "What do you think of the mask?", 12, 1, 100, 1, 0, 0, "Orc Commoner to Orc Commoner", 24337),
(19175, 6, 3, "We should attend the next burning of the Wickerman.", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 23292),
(19175, 6, 4, "We should go trick or treating later.", 12, 1, 100, 273, 0, 0, "Orc Commoner to Orc Commoner", 24331),
(19175, 6, 5, "Where's me gold? Where's me beer? Where's me feet?", 12, 1, 100, 6, 0, 0, "Orc Commoner to Orc Commoner", 23352),
(19175, 6, 6, "For the Alliance!", 12, 1, 100, 4, 0, 0, "Orc Commoner to Orc Commoner", 23351),
(19175, 6, 7, "Where's me gold? Where's me beer? Where's me feet?", 12, 1, 100, 6, 0, 0, "Orc Commoner to Orc Commoner", 23352),
(19175, 6, 8, "The Forsaken are right to celebrate their freedom.", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 23295),
(19175, 6, 9, "I think I've eaten too much candy...", 12, 1, 100, 396, 0, 0, "Orc Commoner to Orc Commoner", 24330),
(19175, 6, 10, "I think I've eaten too much candy...", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 24330),
(19175, 8, 0, "Though we do not truly understand the traditions of Winter Veil, we have taken to them.", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 16164),
(19175, 8, 1, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 0, 0, 0, "Orc Commoner to Orc Commoner", 24323),
(19175, 8, 2, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 6, 0, 0, "Orc Commoner to Orc Commoner", 24323);

DELETE FROM creature_text WHERE entry=19171 AND groupid in (5,6,8);
INSERT INTO creature_text VALUES 
(19171, 5, 0, "To Brewfest!", 12, 7, 100, 5, 0, 0, "Draenei Commoner to Draenei Commoner", 23630),
(19171, 6, 0, "What do you think of the mask?", 12, 7, 100, 1, 0, 0, "Draenei Commoner to Draenei Commoner", 24339),
(19171, 6, 1, "You know... why DO we celebrate this holiday?", 12, 7, 100, 0, 0, 0, "Draenei Commoner to Draenei Commoner", 23287),
(19171, 6, 2, "For the Horde!", 12, 7, 100, 4, 0, 0, "Draenei Commoner to Draenei Commoner", 23357),
(19171, 8, 0, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 7, 100, 0, 0, 0, "Draenei Commoner to Draenei Commoner", 24341),
(19171, 8, 1, "Where are all those wonderful winter hats coming from?", 12, 7, 100, 0, 0, 0, "Draenei Commoner to Draenei Commoner", 24342),
(19171, 8, 2, "Greatfather Winter will leave presents for everyone under the tree in Ironforge. I can't wait to get mine!", 12, 7, 100, 0, 0, 0, "Draenei Commoner to Draenei Commoner", 16422),
(19171, 8, 3, "It is my understanding that the people of the Alliance celebrate this Winter Veil in Ironforge.", 12, 7, 100, 0, 0, 0, "Draenei Commoner to Draenei Commoner", 16161);

DELETE FROM creature_text WHERE entry=19172;
INSERT INTO creature_text VALUES 
(19172, 0, 0, "Have you seen the fireworks? This is the best time of year to buy them.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24351),
(19172, 0, 1, "During the Lunar Festival, we should take time to seek out our elders and consider their wisdom.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24350),
(19172, 0, 2, "Lunar Festival is the best time of year for fireworks!", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 16206),
(19172, 0, 3, "The druids of Nighthaven are holding a great celebration in Moonglade for the Lunar Festival.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24352),
(19172, 6, 0, "We should go trick or treating later.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24348),
(19172, 6, 1, "Happy Hallow's End!", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24346),
(19172, 6, 2, "We should go trick or treating later.", 12, 7, 100, 1, 0, 0, "Gnome Commoner to Gnome Commoner", 24348),
(19172, 6, 3, "Me got the mad voodoo, mon!", 12, 7, 100, 1, 0, 0, "Gnome Commoner to Gnome Commoner", 23361),
(19172, 8, 0, "Greatfather Winter will leave presents for everyone under the tree in Ironforge. I can't wait to get mine!", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 16422),
(19172, 8, 1, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24340),
(19172, 8, 2, "How embarrassing! Someone mistook me for one of Greatfather Winter's helpers.", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 16204),
(19172, 8, 3, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 7, 100, 273, 0, 0, "Gnome Commoner to Gnome Commoner", 24340),
(19172, 8, 4, "Where are all those wonderful winter hats coming from?", 12, 7, 100, 0, 0, 0, "Gnome Commoner to Gnome Commoner", 24342);

DELETE FROM creature_text WHERE entry=19176 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(19176, 6, 0, "What do you think of the mask?", 12, 1, 100, 1, 0, 0, "Tauren Commoner to Tauren Commoner", 24337),
(19176, 6, 1, "Ishnu-dal-dieb.", 12, 1, 100, 3, 0, 0, "Tauren Commoner to Tauren Commoner", 23355),
(19176, 6, 2, "For the Alliance!", 12, 1, 100, 4, 0, 0, "Tauren Commoner to Tauren Commoner", 23351),
(19176, 8, 0, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 0, 0, 0, "Tauren Commoner to Tauren Commoner", 24323),
(19176, 8, 1, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 0, 0, 0, "Tauren Commoner to Tauren Commoner", 16464),
(19176, 8, 2, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 1, 100, 0, 0, 0, "Tauren Commoner to Tauren Commoner", 24324),
(19176, 8, 3, "Greatfather Winter is only a wyvern's ride away to Orgrimmar.", 12, 1, 100, 0, 0, 0, "Tauren Commoner to Tauren Commoner", 16170);

DELETE FROM creature_text WHERE entry=19178 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(19178, 6, 0, "We should go trick or treating later.", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24331),
(19178, 6, 1, "We should attend the next burning of the Wickerman.", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 23292),
(19178, 6, 2, "For the Alliance!", 12, 1, 100, 4, 0, 0, "Forsaken Commoner to Forsaken Commoner", 23351),
(19178, 6, 3, "Happy Hallow's End!", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24329),
(19178, 6, 4, "I think I've eaten too much candy...", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24330),
(19178, 6, 5, "I think I've eaten too much candy...", 12, 1, 100, 274, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24330),
(19178, 8, 0, "Winter Veil just isn't the same now, but going through the motions still makes me feel something.", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 16167),
(19178, 8, 1, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 6, 0, 0, "Forsaken Commoner to Forsaken Commoner", 16464),
(19178, 8, 2, "Where are all those wonderful winter hats coming from?", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24325),
(19178, 8, 3, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 0, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24323),
(19178, 8, 4, "Winter Veil just isn't the same now, but going through the motions still makes me feel something.", 12, 1, 100, 396, 0, 0, "Forsaken Commoner to Forsaken Commoner", 16167),
(19178, 8, 5, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 1, 100, 273, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24323),
(19178, 8, 6, "Where are all those wonderful winter hats coming from?", 12, 1, 100, 273, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24325),
(19178, 8, 7, "Winter Veil just isn't the same now, but going through the motions still makes me feel something.", 12, 1, 100, 6, 0, 0, "Forsaken Commoner to Forsaken Commoner", 16167),
(19178, 8, 8, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 1, 100, 273, 0, 0, "Forsaken Commoner to Forsaken Commoner", 24324),
(19178, 8, 9, "Greatfather Winter will leave presents for everyone under the tree in Orgrimmar. I wonder what he'll bring me this year.", 12, 1, 100, 396, 0, 0, "Forsaken Commoner to Forsaken Commoner", 16464);

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`IN(20102,18927,19177,19169,19175,19171,19172,19176,19178);

DELETE FROM `smart_scripts` WHERE `entryorguid`IN(20102,18927,19177,19169,19175,19171,19172,19176,19178)  AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(20102,0,0,0,1,0,100,0,3000,15000,45000,90000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Goblin Commoner - OOC - Say'),
(18927,0,0,0,1,0,100,0,3000,15000,45000,90000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Human Commoner - OOC - Say'),
(19177,0,0,0,1,0,100,0,3000,15000,45000,90000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Troll Commoner - OOC - Say'),
(19169,0,0,0,1,0,100,0,3000,15000,45000,90000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blood Elf Commoner - OOC - Say'),
(19175,0,0,0,1,0,100,0,3000,15000,45000,90000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Orc Commoner - OOC - Say'),
(19169,0,4,0,1,0,100,0,3000,15000,45000,90000,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blood Elf Commoner - OOC - Say'),
(19175,0,5,0,1,0,100,0,3000,15000,45000,90000,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Orc Commoner - OOC - Say'),
(19171,0,5,0,1,0,100,0,3000,15000,45000,90000,1,5,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blood Elf Commoner - OOC - Say'),
(20102,0,6,0,1,0,100,0,3000,15000,45000,90000,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Goblin Commoner - OOC - Say'),
(19172,0,6,0,1,0,100,0,3000,15000,45000,90000,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Gnome Commoner - OOC - Say'),
(18927,0,6,0,1,0,100,0,3000,15000,45000,90000,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Human Commoner - OOC - Say'),
(19175,0,6,0,1,0,100,0,3000,15000,45000,90000,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Orc Commoner - OOC - Say'),
(19178,0,6,0,1,0,100,0,3000,15000,45000,90000,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'Forsaken Commoner - OOC - Say'),
(19178,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Forsaken Commoner - OOC - Say'),
(20102,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Goblin Commoner - OOC - Say'),
(19169,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blood Elf Commoner - OOC - Say');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` in(20102,18927,19177,19169,19175,19171,19172,19176,19178);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 1, 20102, 0, 0, 12, 1, 7, 0, 0, 0, 0, 0, '', 'Commoner - Luna Festival must be active'),
(22, 1, 18927, 0, 0, 12, 1, 7, 0, 0, 0, 0, 0, '', 'Commoner - Luna Festival must be active'),
(22, 1, 19175, 0, 0, 12, 1, 7, 0, 0, 0, 0, 0, '', 'Commoner - Luna Festival must be active'),
(22, 1, 19169, 0, 0, 12, 1, 7, 0, 0, 0, 0, 0, '', 'Commoner - Luna Festival must be active'),
(22, 1, 19177, 0, 0, 12, 1, 7, 0, 0, 0, 0, 0, '', 'Commoner - Luna Festival must be active'),
(22, 5, 19169, 0, 0, 12, 1, 1, 0, 0, 0, 0, 0, '', 'Commoner - Midsummer must be active'),
(22, 6, 19175, 0, 0, 12, 1, 24, 0, 0, 0, 0, 0, '', 'Commoner - BrewFest must be active'),
(22, 6, 19171, 0, 0, 12, 1, 24, 0, 0, 0, 0, 0, '', 'Commoner - BrewFest must be active'),
(22, 7, 20102, 0, 0, 12, 1, 12, 0, 0, 0, 0, 0, '', 'Commoner - Hallows End must be active'),
(22, 7, 19172, 0, 0, 12, 1, 12, 0, 0, 0, 0, 0, '', 'Commoner - Hallows End must be active'),
(22, 7, 18927, 0, 0, 12, 1, 12, 0, 0, 0, 0, 0, '', 'Commoner - Hallows End must be active'),
(22, 7, 19175, 0, 0, 12, 1, 12, 0, 0, 0, 0, 0, '', 'Commoner - Hallows End must be active'),
(22, 7, 19178, 0, 0, 12, 1, 12, 0, 0, 0, 0, 0, '', 'Commoner - Hallows End must be active'),
(22, 9, 20102, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19169, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19178, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active');

UPDATE `creature` SET `phaseMask`=3 WHERE  `id`=(31328);
delete from creature where id in (31310,31313);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=25 AND `SourceEntry`=719;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(25, 0, 719, 0, 0, 8, 0, 25372, 0, 0, 1, 0, 0, '', 'Hyjal terrain swap if Aessina''s Miracle quest is not rewarded');

DELETE FROM creature_text WHERE entry=19173 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(19173, 6, 0, "Next year, I'm dressing up as either a corsair or an assassin.", 12, 7, 100, 1, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24338),
(19173, 6, 1, "Happy Hallow's End!", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24346),
(19173, 6, 2, "We should go trick or treating later.", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 0),
(19173, 6, 3, "For the Horde!", 12, 7, 100, 4, 0, 0, "Night Elf Commoner to Night Elf Commoner", 23357),
(19173, 6, 4, "Curse this twisting of the night. The candy's good, though.", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 23294),
(19173, 6, 5, "You know... why DO we celebrate this holiday?", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 23287),
(19173, 6, 6, "What do you think of the mask?", 12, 7, 100, 1, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24339),
(19173, 6, 7, "Next year, I'm dressing up as either a corsair or an assassin.", 12, 7, 100, 1, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24338),
(19173, 8, 0, "It feels like everyone wants to kiss me under the mistletoe.", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 16158),
(19173, 8, 1, "It feels like everyone wants to kiss me under the mistletoe.", 12, 7, 100, 396, 0, 0, "Night Elf Commoner to Night Elf Commoner", 16158),
(19173, 8, 2, "Where are all those wonderful winter hats coming from?", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24342),
(19173, 8, 3, "Greatfather Winter will leave presents for everyone under the tree in Ironforge. I can't wait to get mine!", 12, 7, 100, 6, 0, 0, "Night Elf Commoner to Night Elf Commoner", 16422),
(19173, 8, 4, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 7, 100, 0, 0, 0, "Night Elf Commoner to Night Elf Commoner", 24340);

DELETE FROM creature_text WHERE entry=19148 AND groupid in (6,8);
INSERT INTO creature_text VALUES 
(19148, 6, 0, "I think I've eaten too much candy...", 12, 7, 100, 0, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24347),
(19148, 6, 1, "Happy Hallow's End!", 12, 7, 100, 0, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24346),
(19148, 8, 0, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 7, 100, 0, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24341),
(19148, 8, 1, "Where are all those wonderful winter hats coming from?", 12, 7, 100, 274, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24342),
(19148, 8, 2, "I hope I have a chance to visit with Greatfather Winter before Winter Veil is over.", 12, 7, 100, 0, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24340),
(19148, 8, 3, "The goblins of Smokywood Pastures always have such wonderful treats for sale this time of year.", 12, 7, 100, 0, 0, 0, "Dwarf Commoner to Dwarf Commoner", 24341);

UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`IN(19148, 15746, 19173);
DELETE FROM `smart_scripts` WHERE `entryorguid`=15746  AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN(18927,19171,19175,19177,19173,19172,19176,19148)  AND `source_type`=0 AND  `id`=8;
DELETE FROM `smart_scripts` WHERE `entryorguid`IN(18927,19171,19175,19177,19173,19172,19176,19148,19148,19173)  AND `source_type`=0 AND  `id`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(18927,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Human Commoner - OOC - Say'),
(19171,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Dreani Commoner - OOC - Say'),
(19175,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Orc Commoner - OOC - Say'),
(19177,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Troll Commoner - OOC - Say'),
(19173,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Night Elf Commoner - OOC - Say'),
(19172,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Gnome Commoner - OOC - Say'),
(19176,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Tauren Commoner - OOC - Say'),
(19148,0,8,0,1,0,100,0,3000,15000,45000,90000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Dwarf Commoner - OOC - Say'),
(15746,0,0,0,1,0,100,0,3000,15000,600000,600000,1,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'Great-father Winter''s Helper - OOC - Say'),

(18927,0,9,0,64,0,100,0,0,0,0,0,98,7862, 9626,0,0,0,0,7,0,0,0,0,0,0,0,'Human Commoner - On Gossip Hello - Send Gossip Menu'),
(19148,0,9,0,64,0,100,0,0,0,0,0,98,7907, 9686,0,0,0,0,7,0,0,0,0,0,0,0,'Dwarf Commoner - On Gossip Hello - Send Gossip Menu'),
(19169,0,9,0,64,0,100,0,0,0,0,0,98,7911, 9698,0,0,0,0,7,0,0,0,0,0,0,0,'Blood Elf Commoner - On Gossip Hello - Send Gossip Menu'),
(19171,0,9,0,64,0,100,0,0,0,0,0,98,7910, 9694,0,0,0,0,7,0,0,0,0,0,0,0,'Draeni Commoner - On Gossip Hello - Send Gossip Menu'),
(19172,0,9,0,64,0,100,0,0,0,0,0,98,7929, 9717,0,0,0,0,7,0,0,0,0,0,0,0,'Gnome Commoner - On Gossip Hello - Send Gossip Menu'),
(19173,0,9,0,64,0,100,0,0,0,0,0,98,7909, 9690,0,0,0,0,7,0,0,0,0,0,0,0,'Night Elf Commoner - On Gossip Hello - Send Gossip Menu'),
(19175,0,9,0,64,0,100,0,0,0,0,0,98,7912, 9702,0,0,0,0,7,0,0,0,0,0,0,0,'Orc Commoner - On Gossip Hello - Send Gossip Menu'),
(19176,0,9,0,64,0,100,0,0,0,0,0,98,7913, 9706,0,0,0,0,7,0,0,0,0,0,0,0,'Tauren Commoner - On Gossip Hello - Send Gossip Menu'),
(19177,0,9,0,64,0,100,0,0,0,0,0,98,7933, 9718,0,0,0,0,7,0,0,0,0,0,0,0,'Troll Commoner - On Gossip Hello - Send Gossip Menu'),
(19178,0,9,0,64,0,100,0,0,0,0,0,98,7914, 9710,0,0,0,0,7,0,0,0,0,0,0,0,'Forsaken Commoner - On Gossip Hello - Send Gossip Menu');

DELETE FROM creature_text WHERE entry=15746;
INSERT INTO creature_text VALUES 
(15746, 8, 0, "Presents for everyone! Father Winter's put gifts under the tree for all.", 14, 0, 100, 0, 0, 0, "Great-father Winter's Helper", 11430);

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` in(18927,19171,19175,19177,19173,19172,19176,19148) AND `SourceGroup`=9;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` in(18927,19171,19175,19177,19173,19172,19176,19148,19148,19173) AND `SourceGroup`=10;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry` =15746;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 9, 18927, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19171, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19175, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19177, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19173, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19172, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19176, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 9, 19148, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 1, 15746, 0, 0, 12, 1, 52, 0, 0, 0, 0, 0, '', 'Great-father Winter''s Helper - Winter Veil: Gifts must be active'),
(22, 10, 18927, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19148, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19169, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19171, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19172, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19173, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19175, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19176, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19177, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active'),
(22, 10, 19178, 0, 0, 12, 1, 2, 0, 0, 0, 0, 0, '', 'Commoner - Winterveil must be active');

UPDATE `gameobject_template` SET `flags` = 16 WHERE `entry` IN (184278,184279,183932);

UPDATE `creature_template` SET `faction`=1434 WHERE  `entry`=9516;

DELETE FROM `gameobject` WHERE `id` IN (185168, 185169) AND `guid` IN (40114, 26314);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(40114, 185168, 543, 3, 1, -1429.81, 1772.916, 82.0765, 5.044002, 0, 0, 0, 1, 7200, 255, 1), -- 185168 (Area: 3562)
(26314, 185169, 543, 3, 1, -1429.81, 1772.916, 82.0765, 5.044002, 0, 0, 0, 1, 7200, 255, 1); -- 185169 (Area: 3562)

UPDATE `creature_template` SET `flags_extra`=130 WHERE  `entry`=37826;
UPDATE `creature_template` SET `unit_flags`=768, `unit_flags2`=2099200, `dynamicflags`=1613035584 WHERE  `entry`=37857;
UPDATE `creature_template` SET `unit_flags`=33554688, `unit_flags2`=2099200, `dynamicflags`=1613037824 WHERE  `entry`=37894;
UPDATE `creature_template` SET `unit_flags`=33554688, `unit_flags2`=2099200, `dynamicflags`=1613036800 WHERE  `entry`=37878;

SET @TRIGG := 5650;
SET @BUNNY := 37832;-- Lich King Stun Bunny
SET @CGUID := 53284; 
SET @QUEST := 24546;-- The Sacred and the Corrupt
SET @LIGHTSVENGENCE := 49869;
SET @BUNNY2	:= 37878;-- AoD Impact Bunny
SET @LICHKING := 37857;-- The Lich King

DELETE FROM `areatrigger_scripts` WHERE `entry` = @TRIGG;
INSERT INTO `areatrigger_scripts`(`entry`, `ScriptName`) VALUES
(@TRIGG,'SmartTrigger');

DELETE FROM `smart_scripts` WHERE `entryorguid` =@TRIGG AND `source_type`=2;
INSERT INTO `smart_scripts`(`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@TRIGG,2,0,1,46,0,100,0,@TRIGG,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,"On Trigger - Store Target List"),
(@TRIGG,2,1,2,61,0,100,0,@TRIGG,0,0,0,100,1,0,0,0,0,0,10,@CGUID,@BUNNY,0,0,0,0,0,"On Trigger - Send Target List to Lich King Stun Bunny"),
(@TRIGG,2,2,0,61,0,100,0,0,0,0,0,45,1,1,0,0,0,0,10,@CGUID,@BUNNY,0,0,0,0,0,"On Trigger - Set Data on Lich King Stun Bunny");

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND`SourceEntry`=@TRIGG;
INSERT INTO `conditions`(`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(22,1,@TRIGG,2,0,9,0,@QUEST,0,0,0,0,'','Trigger only activates if player is on and has not completed The Sacred and the Corrupt'),
(22,1,@TRIGG,2,0,2,0,@LIGHTSVENGENCE,1,0,1,0,'','Trigger does not activate if player already has lights vengence');
	
DELETE FROM `creature_text` WHERE `entry` IN(37976,37893,@LICHKING);
INSERT INTO `creature_text`(`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(37976, 0, 0, 'Fear not, master. I shall rend the flesh of your enemy!', 12, 0, 100, 0, 0, 17077, 37657, 'Vegard the Unforgiven'),
(37976, 1, 0, 'Master... I have... failed.', 12, 0, 100, 0, 0, 17076, 37656, 'Vegard the Unforgiven'),
(37976, 2, 0, 'It is done, master.', 12, 0, 100, 0, 0, 17075, 37655, 'Vegard the Unforgiven'),
(37893, 0, 0, 'I hear and obey, master...', 12, 0, 100, 0, 0, 17073, 0, 'Vegard the Unforgiven'),
(37893, 1, 0, 'The enemy shall suffer greatly, master!', 12, 0, 100, 0, 0, 17074, 37651, 'Vegard the Unforgiven'),
(@LICHKING, 0, 0, 'So predictable...', 12, 0, 100, 396, 0, 17252, 37506, 'The Lich King'),
(@LICHKING, 1, 0, 'Did you truly expect to fulfill Mograine''s task unopposed?', 12, 0, 100, 6, 0, 17253, 37507, 'The Lich King'),
(@LICHKING, 2, 0, 'You both shall suffer as his father does...', 12, 0, 100, 396, 0, 17254, 37508, 'The Lich King'),
(@LICHKING, 3, 0, '...in eternal unrest!', 12, 0, 100, 0, 0, 17255, 37509, 'The Lich King'),
(@LICHKING, 4, 0, 'Die well, fool.', 12, 0, 100, 397, 0, 17256, 37510, 'The Lich King');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=70653;
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES 
(70653, 70966, 1, 'Lich King Zap Player - Knockback 50 No Log');

UPDATE creature_template SET minlevel=80, maxlevel=80, faction=14 WHERE entry=37881;

UPDATE creature_template SET minlevel=80, maxlevel=80, faction=1885 WHERE entry=37893;

UPDATE creature_template SET minlevel=81, maxlevel=81, faction=1885 WHERE entry=37976;

UPDATE creature_template SET minlevel=60, maxlevel=60 WHERE entry=37952;

UPDATE `creature_template` SET `flags_extra`=0 WHERE  `entry`=37826;

DELETE FROM `creature_text` WHERE `entry`in(37120);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextID`, `comment`) VALUES
(37120, 0, 0, 'So, it has begun....', 12, 0, 100, 396, 0, 16834, 37248, 'Highlord Darion Mograine to Player'),
(37120, 1, 0, 'Behold! The binding of sacred and corrupt; the forging of Shadow''s Edge, a weapon of untold potential!', 12, 0, 100, 0, 0, 16835, 37249, 'Highlord Darion Mograine to Player'),
(37120, 2, 0, 'Bend it to your will, and you shall wield unspeakable power!', 12, 0, 100, 396, 0, 16836, 37250, 'Highlord Darion Mograine to Player'),
(37120, 3, 0, 'Fail, and your soul shall forever be its slave.', 12, 0, 100, 396, 0, 16837, 37251, 'Highlord Darion Mograine to Player');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`IN(70529,71310,70471);
INSERT INTO `conditions`(`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 3, 71310, 0, 0, 31, 0, 3, 38191, 0, 0, 0, 0, '', 'Pull Shadows Edge targets Shadows Edge'),
(13, 3, 70471, 0, 0, 31, 0, 3, 37702, 0, 0, 0, 0, '', ' Mograine Forge Beam targets Runeforge Bunny');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND `SourceEntry`IN(5650);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(22, 1, 5650, 2, 0, 9, 0, 24545, 0, 0, 0, 0, 0, '', 'Trigger only activates if player is on and has not completed The Sacred and the Corrupt'),
(22, 1, 5650, 2, 0, 2, 0, 49869, 1, 0, 1, 0, 0, '', 'Trigger does not activate if player already has lights vengence');

UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=22843;
UPDATE `creature_template` SET `InhabitType`=4 WHERE  `entry`=22842;

SET @GUID := 156608;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-253.4223,`position_y`=5430.909,`position_z`=28.92926 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-253.4223,5430.909,28.92926,0,0,1,0,100,0),
(@PATH,2,-252.2368,5429.647,28.75794,0,0,1,0,100,0),
(@PATH,3,-246.0865,5428.435,29.54239,0,0,1,0,100,0),
(@PATH,4,-239.4053,5431.095,29.54241,0,0,1,0,100,0),
(@PATH,5,-235.5483,5436.207,30.90352,0,0,1,0,100,0),
(@PATH,6,-235.0203,5442.249,30.87573,0,0,1,0,100,0),
(@PATH,7,-238.777,5445.627,32.07018,0,0,1,0,100,0),
(@PATH,8,-246.5504,5445.43,30.82018,0,0,1,0,100,0),
(@PATH,9,-254.3803,5440.281,29.67928,0,0,1,0,100,0),
(@PATH,10,-255.2896,5432.612,28.92926,0,0,1,0,100,0);
 
SET @GUID := 156511;
SET @PATH := @GUID * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-231.4784,`position_y`=5442.248,`position_z`=29.75438 WHERE `guid`=@GUID;
DELETE FROM `creature_addon` WHERE `guid`=@GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@GUID,@PATH,0,0,1,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_flag`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-231.4784,5442.248,29.75438,0,0,1,0,100,0),
(@PATH,2,-231.9071,5441.805,29.40595,0,0,1,0,100,0),
(@PATH,3,-233.5468,5436.123,30.58605,0,0,1,0,100,0),
(@PATH,4,-235.9648,5433.313,31.33606,0,0,1,0,100,0),
(@PATH,5,-245.6634,5430.377,32.44696,0,0,1,0,100,0),
(@PATH,6,-254.214,5432.43,32.50253,0,0,1,0,100,0),
(@PATH,7,-257.6299,5440.645,31.36549,0,0,1,0,100,0),
(@PATH,8,-250.052,5446.799,30.14325,0,0,1,0,100,0),
(@PATH,9,-244.9603,5449.014,29.67106,0,0,1,0,100,0),
(@PATH,10,-237.6145,5448.882,29.75438,0,0,1,0,100,0);

UPDATE `creature_template` SET `gossip_menu_id`=9832 WHERE  `entry` IN (5188,5049);

SET @CGUID := 240807;
DELETE FROM `creature` WHERE `id`IN(37827,37878);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 37878, 571, 1, 1, 4785.788, -587.8594, 161.2263, 5.009095, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+1, 37878, 571, 1, 1, 4779.228, -587.1545, 162.1223, 4.537856, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+2, 37878, 571, 1, 1, 4802.324, -553.8646, 163.156, 4.869469, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+3, 37878, 571, 1, 1, 4778.958, -567.7934, 162.0411, 3.647738, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+4, 37878, 571, 1, 1, 4782.333, -572.7118, 161.8683, 5.585053, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+5, 37878, 571, 1, 1, 4789.622, -579.4358, 161.0213, 4.520403, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+6, 37878, 571, 1, 1, 4798.444, -562.9028, 161.4739, 1.466077, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+7, 37878, 571, 1, 1, 4760.652, -561.3246, 165.0569, 3.944444, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+8, 37878, 571, 1, 1, 4787.11, -566.2014, 161.6813, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+9, 37878, 571, 1, 1, 4767.754, -560.6215, 163.8418, 1.064651, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+10, 37878, 571, 1, 1, 4772.837, -575.5347, 162.7558, 1.64061, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+11, 37878, 571, 1, 1, 4797.168, -577.1268, 160.2595, 2.478368, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+12, 37878, 571, 1, 1, 4763.54, -576.6424, 163.8399, 5.253441, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+13, 37878, 571, 1, 1, 4763.713, -569.2257, 163.7682, 3.839724, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+14, 37878, 571, 1, 1, 4800.604, -547.7327, 164.9199, 0.715585, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+15, 37878, 571, 1, 1, 4782.397, -593.6545, 161.6707, 1.605703, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+16, 37878, 571, 1, 1, 4771.824, -566.1719, 162.4859, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+17, 37878, 571, 1, 1, 4791.537, -557.3125, 162.7901, 4.066617, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+18, 37878, 571, 1, 1, 4756.674, -580.4653, 165.0974, 1.48353, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+19, 37878, 571, 1, 1, 4782.095, -580.7483, 161.8616, 1.27409, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+20, 37878, 571, 1, 1, 4772.525, -585.9844, 163.0426, 2.687807, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+21, 37878, 571, 1, 1, 4759.741, -587.8351, 164.6121, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+22, 37878, 571, 1, 1, 4776.268, -596.5695, 162.6325, 2.059489, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+23, 37878, 571, 1, 1, 4793.397, -570.8108, 160.8941, 3.682645, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+24, 37878, 571, 1, 1, 4767.424, -594.3489, 163.828, 1.58825, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+25, 37878, 571, 1, 1, 4797.148, -583.2952, 159.8615, 3.595378, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+26, 37878, 571, 1, 1, 4817.919, -551.9774, 162.0828, 3.036873, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+27, 37878, 571, 1, 1, 4792.533, -591.684, 160.2542, 4.206244, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+28, 37878, 571, 1, 1, 4790.34, -607.0833, 160.2565, 3.525565, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+29, 37878, 571, 1, 1, 4782.63, -605.3073, 161.6125, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+30, 37878, 571, 1, 1, 4817.919, -551.9774, 162.0828, 3.036873, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+31, 37878, 571, 1, 1, 4792.533, -591.684, 160.2542, 4.206244, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+32, 37878, 571, 1, 1, 4790.34, -607.0833, 160.2565, 3.525565, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+33, 37878, 571, 1, 1, 4782.63, -605.3073, 161.6125, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+34, 37878, 571, 1, 1, 4798.115, -607.4479, 159.7254, 0.715585, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+35, 37878, 571, 1, 1, 4791.471, -618.4844, 159.7092, 2.059489, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+36, 37878, 571, 1, 1, 4792.949, -603.3854, 160.3281, 2.740167, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+37, 37878, 571, 1, 1, 4798.659, -602.0208, 159.8221, 2.565634, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+38, 37878, 571, 1, 1, 4810.37, -549.7691, 163.2147, 3.385939, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+39, 37878, 571, 1, 1, 4796.788, -613.9011, 159.7589, 0.8901179, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+40, 37878, 571, 1, 1, 4802.318, -570.2361, 160.2752, 1.064651, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+41, 37878, 571, 1, 1, 4784.508, -609.382, 161.722, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+42, 37878, 571, 1, 1, 4789.024, -611.7726, 160.3697, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+43, 37878, 571, 1, 1, 4816.295, -556.5955, 161.8312, 3.822271, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+44, 37878, 571, 1, 1, 4806.933, -604.0538, 159.585, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+45, 37878, 571, 1, 1, 4809.641, -555.4688, 162.6923, 0.715585, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+46, 37878, 571, 1, 1, 4826.658, -555.1059, 161.3158, 4.625123, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+47, 37878, 571, 1, 1, 4790.142, -624.1771, 159.6133, 0.9773844, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+48, 37878, 571, 1, 1, 4810.255, -627.4636, 159.1524, 1.500983, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+49, 37878, 571, 1, 1, 4810.049, -609.3768, 159.4645, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+50, 37878, 571, 1, 1, 4806.465, -618.2396, 159.5483, 5.445427, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+51, 37878, 571, 1, 1, 4815.847, -606.0087, 160.2059, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+52, 37878, 571, 1, 1, 4793.201, -627.0521, 159.9451, 3.473205, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+53, 37878, 571, 1, 1, 4814.297, -619.2708, 158.7552, 0.715585, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+54, 37878, 571, 1, 1, 4837.163, -576.5104, 160.5024, 5.078908, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+55, 37878, 571, 1, 1, 4800.022, -618.3073, 159.7944, 3.508112, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+56, 37878, 571, 1, 1, 4796.73, -622.5868, 159.9098, 2.356194, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+57, 37878, 571, 1, 1, 4806.011, -623.4809, 159.5464, 2.740167, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+58, 37878, 571, 1, 1, 4803.761, -610.7188, 159.545, 4.24115, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+59, 37878, 571, 1, 1, 4791.314, -635.191, 160.8559, 4.817109, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+60, 37878, 571, 1, 1, 4795.549, -631.2952, 160.2526, 1.361357, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+61, 37878, 571, 1, 1, 4809.817, -614.8125, 159.2753, 2.199115, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+62, 37878, 571, 1, 1, 4828.341, -562.2778, 160.3308, 0.9599311, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+63, 37878, 571, 1, 1, 4793.918, -639.1545, 161.241, 4.468043, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+64, 37878, 571, 1, 1, 4788.442, -639.3229, 162.3155, 1.37881, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+65, 37878, 571, 1, 1, 4801.533, -631.1614, 160.0972, 3.525565, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+66, 37878, 571, 1, 1, 4804.434, -635.9236, 159.8547, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+67, 37878, 571, 1, 1, 4806.627, -631.4097, 159.5468, 4.939282, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+68, 37878, 571, 1, 1, 4835.668, -563.5555, 161.4551, 0.4886922, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+69, 37878, 571, 1, 1, 4788.494, -629.8542, 161.1564, 5.340707, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+70, 37878, 571, 1, 1, 4798.058, -635.0156, 160.5321, 3.141593, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+71, 37878, 571, 1, 1, 4814.169, -631.3663, 158.7541, 5.235988, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+72, 37878, 571, 1, 1, 4809.902, -635.441, 159.2038, 1.151917, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+73, 37878, 571, 1, 1, 4845.159, -576.0278, 159.9401, 5.532694, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+74, 37878, 571, 1, 1, 4845.673, -593.6736, 159.1436, 3.874631, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+75, 37878, 571, 1, 1, 4809.697, -642.8246, 159.2958, 2.007129, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+76, 37878, 571, 1, 1, 4804.116, -640.8143, 160.1202, 2.373648, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+77, 37878, 571, 1, 1, 4825.955, -637.9774, 157.6442, 5.340707, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+78, 37878, 571, 1, 1, 4854.851, -593.2795, 157.3008, 4.625123, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+79, 37878, 571, 1, 1, 4822.641, -641.3472, 157.8503, 3.944444, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+80, 37878, 571, 1, 1, 4843.747, -587.0625, 159.7272, 0.9250245, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+81, 37878, 571, 1, 1, 4822.299, -616.1996, 157.9486, 2.286381, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+82, 37878, 571, 1, 1, 4851.638, -585.6007, 158.117, 2.059489, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+83, 37878, 571, 1, 1, 4842.857, -580.882, 159.7307, 2.96706, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+84, 37878, 571, 1, 1, 4826.226, -624.4792, 157.9513, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+85, 37878, 571, 1, 1, 4845.403, -613.0851, 157.4199, 1.815142, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+86, 37878, 571, 1, 1, 4840.92, -570.6979, 161.174, 3.769911, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+87, 37878, 571, 1, 1, 4837.809, -627.6736, 157.6199, 1.954769, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+88, 37878, 571, 1, 1, 4813.187, -639.132, 158.8725, 0, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+89, 37878, 571, 1, 1, 4833.483, -635.0799, 157.4865, 4.834562, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+90, 37878, 571, 1, 1, 4842.37, -621.6962, 157.5227, 2.879793, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+91, 37878, 571, 1, 1, 4829.419, -629.3629, 157.6456, 3.612832, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+92, 37878, 571, 1, 1, 4815.688, -625.3021, 158.6156, 4.066617, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+93, 37878, 571, 1, 1, 4848.793, -601.8837, 157.445, 4.258604, 120, 0, 0), -- 37878 (Area: 4192)
(@CGUID+94, 37827, 571, 1, 1, 4812.731, -582.6302, 162.4707, 4.118977, 120, 0, 0); -- 37827 (Area: 4192) 







