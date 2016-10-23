
UPDATE quest_template SET Flags=3407872, RequiredSourceItemId1=49108, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=14236;

DELETE FROM creature_text WHERE entry=35918;
INSERT INTO creature_text VALUES 
(35918, 0, 0, "We should move now.  See you at the Wild Overlook.", 12, 0, 100, 3, 0, 0, "Orc Scout", 36116),
(35918, 1, 0, "We will move ahead, Kilag.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36109),
(35918, 2, 0, "$N has cleared a path. We will go ahead.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36110),
(35918, 3, 0, "Do not wait long, Kilag. We will scout ahead.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36111);

UPDATE creature_template SET ScriptName="npc_orc_scout_35918" WHERE entry=35918;

DELETE FROM creature_text WHERE entry=38738 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38738, 1, 0, "The play is a Kilo Tango Charlie Blitz on three. One... two... three! Um... guys?!", 12, 0, 100, 396, 0, 0, "Coach Crosscheck", 38607);

DELETE FROM creature_text WHERE entry=36403;
INSERT INTO creature_text VALUES 
(36403, 0, 0, "I can't help but think that if it weren't for the meddling of $N back on Kezan, we'd all be safe and sound in Azshara by now.", 12, 0, 100, 0, 0, 0, "Trade Prince Gallywix", 36381),
(36403, 1, 0, "You thought to take my place on Kezan, $N? You reach too far! I made you what you were... were being the operative word. You're nothing now. Nothing!", 14, 0, 100, 11, 0, 0, "", 36383);

DELETE FROM creature_text WHERE entry=38738 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38738, 1, 0, "This isn't footbomb, kids. This is the real deal!", 12, 0, 100, 22, 0, 0, "Coach Crosscheck", 38609);

DELETE FROM creature_text WHERE entry=38738 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(38738, 2, 0, "Bilgewater Buccaneers for life!", 12, 0, 100, 15, 0, 0, "Coach Crosscheck", 38613);

DELETE FROM creature_text WHERE entry=35758 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(35758, 2, 0, "That was the most beautiful thing that I've ever seen!", 12, 0, 100, 0, 0, 0, "Bamm Megabomb", 49831);

DELETE FROM creature_text WHERE entry=36403 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(36403, 1, 0, "Nobody panic! I'll see to it we get off of this deplorable island. You'll see... I've got it all planned out!", 14, 0, 100, 0, 0, 0, "Trade Prince Gallywix", 36379);

DELETE FROM creature_text WHERE entry=38738 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38738, 1, 0, "Goldskimmer, are you ready to run with it?", 12, 0, 100, 6, 0, 0, "Coach Crosscheck", 38610);

DELETE FROM creature_text WHERE entry=36403 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(36403, 1, 0, "I can't help but think that if it weren't for the meddling of $N back on Kezan, we'd all be safe and sound in Azshara by now.", 12, 0, 100, 0, 0, 0, "Trade Prince Gallywix", 36381);

DELETE FROM creature_text WHERE entry=38738 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38738, 1, 0, "Alright, people, hold that line!", 12, 0, 100, 5, 0, 0, "Coach Crosscheck", 38606);

DELETE FROM creature_text WHERE entry=35838;
INSERT INTO creature_text VALUES 
(35838, 0, 0, "Sooie nah mi juju, gobin!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36347),
(35838, 1, 0, "Taronto bosch!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36348),
(35838, 2, 0, "Mkay, m'ne ta oor!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36349);

DELETE FROM creature_text WHERE entry=35813;
INSERT INTO creature_text VALUES 
(35813, 0, 0, "Okay, here we go. You're gonna cover me, right?", 12, 0, 100, 396, 0, 0, "", 35995),
(35813, 1, 0, "Whoa! What's with all of the cave paintings? Ack, do I hear monkeys?", 12, 0, 100, 0, 0, 0, "miner", 36102),
(35813, 2, 0, "This chunk's been picked clean.", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36011),
(35813, 2, 1, "I can't get anything else out of this one.", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36012),
(35813, 2, 2, "We've hit the jackpot in this place!", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36013),
(35813, 2, 3, "Did I ever tell you that I was a mid-level accountant with the company back on Kezan? I worked for you for years. Do you even know my name?", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36014),
(35813, 2, 4, "The monkeys already extracted most of the kaja'mite out of this deposit.", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36015),
(35813, 2, 5, "What I wouldn't give for some explosives right about now.", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36016),
(35813, 2, 6, "Hey, why am I doing all of the work here?", 12, 0, 100, 0, 0, 0, "Frightened Miner", 36017),
(35813, 3, 0, "That's good enough for now. I'll make my way out on my own. Thanks for the escort.", 12, 0, 100, 0, 0, 0, "miner", 36018);

DELETE FROM creature_text WHERE entry=35769 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35769, 1, 0, "On behalf of the Bilgewater Cartel, I lay claim to this mine!", 12, 0, 100, 0, 0, 0, "Foreman Dampwick", 49834);

DELETE FROM creature_text WHERE entry=35650 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(35650, 2, 0, "We need some new friends if we're going to survive all of this. Hopefully, the orcs won't just kill you on sight.", 12, 0, 100, 0, 0, 0, "Sassy Hardwrench", 49835);

DELETE FROM creature_text WHERE entry=36042;
INSERT INTO creature_text VALUES 
(36042, 0, 0, "My ribs are broken.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36599),
(36042, 1, 0, "Throm-Ka, goblin!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36600),
(36042, 2, 0, "Aka'Magosh, goblin!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36601),
(36042, 3, 0, "Lok'tar!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36602),
(36042, 4, 0, "I give you thanks for my life.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36603);

DELETE FROM creature_text WHERE entry=35893 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35893, 1, 0, "Go back to Aggra and tell her that we're moving northwest.", 12, 0, 100, 0, 0, 0, "Kilag Gorefang", 49855);

DELETE FROM creature_text WHERE entry=35875 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35875, 1, 0, "Head back through the vale and meetup with Kilag at the Wild Overlook.", 12, 0, 100, 0, 0, 0, "Aggra", 49860);

DELETE FROM creature_text WHERE entry=35917 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35917, 1, 0, "Ride Bastia! Find Brax!", 12, 0, 100, 0, 0, 0, "Kilag Gorefang", 49863);

DELETE FROM creature_text WHERE entry=36161;
INSERT INTO creature_text VALUES 
(36161, 0, 0, "Use the Cyclone of the Elements to kill the pirates on the ships and boats!", 41, 0, 100, 0, 0, 0, "say Thrall", 0),
(36161, 1, 0, "Children of the watery depths, lay waste to those who foul your realm!", 14, 0, 100, 0, 0, 0, "Thrall", 36200),
(36161, 2, 0, "Winds of boundless fury, unleash your tempest upon the Alliance!", 12, 0, 100, 0, 0, 0, "Thrall", 36202),
(36161, 3, 0, "Sons of Stormwall, descend and destroy those who would prevent me from protecting this world!", 14, 0, 100, 0, 0, 0, "Thrall", 36203);

-- Type: RaidBossEmote (41)
-- GUID: Full: 0x380000004A627A4 Type: Player Low: 77997988 Name: Badfrank
-- Text: Auf zur Wilden Aussicht.
-- BroadcastTextId: 40144

DELETE FROM creature_text WHERE entry=36519 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(36519, 1, 0, "Is that a volcano over on that other island?", 12, 0, 100, 0, 0, 0, "Evol Fingers", 36392);

DELETE FROM creature_text WHERE entry=36513;
INSERT INTO creature_text VALUES 
(36513, 0, 0, "You think you're such a bigshot, saving everyone and making friends with these orc savages?!", 14, 0, 100, 25, 0, 19584, "", 36460),
(36513, 1, 0, "I'm gonna crush you. I'm the Trade Prince, me! I've got a plan that's gonna get me off this island and make me the King of Azshara!", 14, 0, 100, 0, 0, 19585, "gallywix", 36461),
(36513, 2, 0, "Mark my words! I'm gonna get you, $N! I'll get you all! Out of my way!", 14, 0, 100, 15, 0, 19586, "Trade Prince Gallywix", 36462);

DELETE FROM creature_text WHERE entry=38122 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38122, 1, 0, "Now get us some real eggs.", 12, 0, 100, 0, 0, 0, "Bamm Megabomb", 49899);

DELETE FROM creature_text WHERE entry=38120;
INSERT INTO creature_text VALUES 
(38120, 0, 0, "Greely, load The Biggest Egg Ever into the Poultryizer. Mechnuggets for everyone!", 14, 0, 100, 0, 0, 0, "Hobart Grapplehammer", 38106),
(38120, 1, 0, "Shut it down, shut it down! The eggs are bad!!!", 14, 0, 100, 0, 0, 0, "Hobart Grapplehammer", 38170),
(38120, 2, 0, "$N, over here if you please.", 12, 0, 100, 3, 0, 0, "Hobart Grapplehammer", 41262),
(38120, 3, 0, "It's really quite simple, $N. Just attach these fireworks to the wild cluckers and I'll use this controller to fly them into the cage.", 12, 0, 100, 5, 0, 0, "", 49894),
(38120, 4, 0, "Don't underestimate the Mechachicken, $N. After all, it is a Hobart Grapplehammer invention!", 12, 0, 100, 0, 0, 0, "Hobart Grapplehammer", 49900),
(38120, 5, 0, "The marketing research Megs has conducted suggests that a naga invasion is imminent!", 12, 0, 100, 5, 0, 0, "Hobart Grapplehammer", 49934);

DELETE FROM creature_text WHERE entry=38124;
INSERT INTO creature_text VALUES 
(38124, 0, 0, "Genius idea, sir. Your brain power never ceases to amaze me!", 14, 0, 100, 1, 0, 0, "", 38119),
(38124, 1, 0, "This thing is huge! Reverse the polarity on the Poultryizer. We'll have to shove it in through the outtake.", 14, 0, 100, 5, 0, 0, "Assistant Greely", 38141),
(38124, 2, 0, "There it goes.  It should only be a moment now....", 14, 0, 100, 1, 0, 0, "Assistant Greely", 38142),
(38124, 3, 0, "$N, get to the Mechashark X-Steam Controller.  Rid us of the Hammer menace!", 12, 0, 100, 1, 0, 0, "Say Text on Quest Accept", 49911);











