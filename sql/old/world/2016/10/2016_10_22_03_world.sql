
UPDATE creature_template SET ScriptName="npc_sassy_hardwrench_35650" WHERE entry=35650;

DELETE FROM creature_text WHERE entry=38738;
INSERT INTO creature_text VALUES 
(38738, 0, 0, "Get in there and show those zombies what the Bilgewater Buccaneers are made of, kid!", 12, 0, 100, 25, 0, 0, "Coach Crosscheck", 50072),
(38738, 1, 0, "Alright, people, hold that line!", 12, 0, 100, 5, 0, 0, "Coach Crosscheck", 38606),
(38738, 2, 0, "The play is a Kilo Tango Charlie Blitz on three. One... two... three! Um... guys?!", 12, 0, 100, 396, 0, 0, "Coach Crosscheck", 38607),
(38738, 3, 0, "Bilgewater Buccaneers for life!", 12, 0, 100, 15, 0, 0, "Coach Crosscheck", 38613);

UPDATE creature_template SET ScriptName="npc_coach_crosscheck_38738" WHERE entry=38738;

UPDATE creature_template SET ScriptName="npc_maxx_avalanche_35786" WHERE entry=35786;

DELETE FROM creature_text WHERE entry=35758;
INSERT INTO creature_text VALUES 
(35758, 0, 0, "The monkeys are going to get a kick out of those bananas!", 12, 0, 100, 11, 0, 0, "Bamm Megabomb", 49830),
(35758, 1, 0, "That was the most beautiful thing that I've ever seen!", 12, 0, 100, 0, 0, 0, "Bamm Megabomb", 49831);

UPDATE creature_template SET ScriptName="npc_bamm_megabomb_35758" WHERE entry=35758;

DELETE FROM creature_text WHERE entry=36403;
INSERT INTO creature_text VALUES 
(36403, 0, 0, "Nobody panic! I'll see to it we get off of this deplorable island. You'll see... I've got it all planned out!", 14, 0, 100, 274, 0, 19588, "Trade Prince Gallywix", 36379),
(36403, 0, 1, "Never fear, Trade Prince Gallywix is here. We'll be on our way to our new home in Azshara before you know it! Despite the bumbling interference of $N.", 14, 0, 100, 0, 0, 19589, "Trade Prince Gallywix", 36380),
(36403, 0, 2, "I can't help but think that if it weren't for the meddling of $N back on Kezan, we'd all be safe and sound in Azshara by now.", 14, 0, 100, 5, 0, 19590, "Trade Prince Gallywix", 36381),
(36403, 0, 3, "I've got my eye on you, $N. Let's just say that only one of us will be leaving this island, and that goblin's name begins with Trade Prince!", 14, 0, 100, 0, 0, 19591, "Trade Prince Gallywix", 36382),
(36403, 0, 4, "You thought to take my place on Kezan, $N? You reach too far! I made you what you were... were being the operative word. You're nothing now. Nothing!", 14, 0, 100, 0, 0, 19592, "Trade Prince Gallywix", 36383),
(36403, 0, 5, "I want you all to listen good... anyone who's not with me can start looking for a new job!", 14, 0, 100, 0, 0, 19593, "Trade Prince Gallywix", 36384),
(36403, 0, 6, "No worries, everyone. This is just a short pit stop on our way to our new home.", 14, 0, 100, 0, 0, 19594, "Trade Prince Gallywix", 36385);

UPDATE creature_template SET ScriptName="npc_trade_prince_gallywix_36403" WHERE entry=36403;

DELETE FROM creature_text WHERE entry=38738;
INSERT INTO creature_text VALUES 
(38738, 0, 0, "Get in there and show those zombies what the Bilgewater Buccaneers are made of, kid!", 12, 0, 100, 25, 0, 0, "Coach Crosscheck", 50072),
(38738, 1, 0, "Alright, people, hold that line!", 12, 0, 100, 5, 0, 0, "Coach Crosscheck", 38606),
(38738, 1, 1, "The play is a Kilo Tango Charlie Blitz on three. One... two... three! Um... guys?!", 12, 0, 100, 396, 0, 0, "Coach Crosscheck", 38607),
(38738, 1, 2, "We're up against pterrodax, sharks, teraptors, and bomb-throwing monkeys. It's going to take a miracle to win!", 12, 0, 100, 5, 0, 0, "Coach Crosscheck", 38608),
(38738, 1, 3, "This isn't footbomb, kids. This is the real deal!", 12, 0, 100, 22, 0, 0, "Coach Crosscheck", 38609),
(38738, 1, 4, "Goldskimmer, are you ready to run with it?", 12, 0, 100, 6, 0, 0, "Coach Crosscheck", 38610),
(38738, 1, 5, "Are we gonna let them make a bunch of monkeys out of us? NO!", 12, 0, 100, 6, 0, 0, "Coach Crosscheck", 38611),
(38738, 1, 6, "What I wouldn't give for one of my Buccaneer shredder suits right about now!", 12, 0, 100, 15, 0, 0, "Coach Crosscheck", 38612),
(38738, 1, 7, "Bilgewater Buccaneers for life!", 12, 0, 100, 15, 0, 0, "Coach Crosscheck", 38613);

DELETE FROM creature_text WHERE entry=35758 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35758, 1, 0, "That was the most beautiful thing that I've ever seen!", 12, 0, 100, 11, 0, 0, "Bamm Megabomb", 49831);

UPDATE creature_template SET ScriptName="npc_pygmy_witchdoctor_35838" WHERE entry=35838;

DELETE FROM creature_text WHERE entry=35838;
INSERT INTO creature_text VALUES 
(35838, 0, 0, "Sooie nah mi juju, gobin!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36347),
(35838, 0, 1, "Taronto bosch!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36348),
(35838, 0, 2, "Mkay, m'ne ta oor!", 14, 0, 100, 0, 0, 0, "Pygmy Witchdoctor", 36349);

DELETE FROM creature_text WHERE entry=35769 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35769, 1, 0, "On behalf of the Bilgewater Cartel, I lay claim to this mine!", 12, 0, 100, 4, 0, 0, "Foreman Dampwick", 49834);

DELETE FROM creature_text WHERE entry=35650 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(35650, 2, 0, "We need some new friends if we're going to survive all of this. Hopefully, the orcs won't just kill you on sight.", 12, 0, 100, 1, 0, 0, "Sassy Hardwrench", 49835);

DELETE FROM creature_text WHERE entry=36042;
INSERT INTO creature_text VALUES 
(36042, 0, 0, "My ribs are broken.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36599),
(36042, 0, 1, "Throm-Ka, goblin!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36600),
(36042, 0, 2, "Aka'Magosh, goblin!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36601),
(36042, 0, 3, "Lok'tar!", 12, 0, 100, 0, 0, 0, "Orc Scout", 36602),
(36042, 0, 4, "I give you thanks for my life.", 12, 0, 100, 0, 0, 0, "Orc Scout", 36603);

UPDATE creature_template SET ScriptName="npc_aggra_35875" WHERE entry=35875;

DELETE FROM phase_area WHERE areaId=4720 AND entry in (1, 2, 3);
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4720, 1, 14303, 14240, 64, 11, 0, "phase 171 from reward quest 14303 to reward 14240"),
(4720, 2, 14240, 14326, 64, 1, 0, "phase 172 from reward quest 14240 to accept 14326"),
(4720, 3, 14326, 14245, 74, 11, 0, "phase 179 from accept quest to... ");

DELETE FROM phase_definitions WHERE zoneId=4720 AND entry=4;
INSERT INTO phase_definitions VALUES 
(4720, 4, 180, 661, 681, 1, "Comment for phase 180 : Zone town in a box Id: 4871");






