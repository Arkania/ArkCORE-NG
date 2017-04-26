

UPDATE quest_template SET Flags=3145932, SpecialFlags=2 WHERE Id=25924; -- 2097356

UPDATE quest_template SET Flags=3145932, SpecialFlags=2 WHERE Id=14482;

update phase_definitions set zoneId=14 where zoneId=374 and entry=0;

update phase_area set areaId=14 where areaId=374 and entry=0;

delete from phase_definitions where zoneId=817 and entry=0;

delete from phase_area where areaId=817 and entry=0;

update phase_definitions set zoneId=1519 where zoneId=4411 and entry=0;

update phase_area set areaId=1519 where areaId=4411 and entry=0;

update gameobject set phaseId=200 where id=203471;

UPDATE creature SET phaseId=171 WHERE guid=112300;

UPDATE creature SET phaseId=0, phaseGroup=396 where guid in (88916, 88216, 112284, 92777, 112308, 92890, 92953, 128486, 112314);

update gameobject set phaseId=0, phaseGroup=396 where id in (204167, 204168, 204169, 204170);

delete from gameobject where guid in (400109, 400099, 400035, 400095, 400105, 400113);

DELETE FROM creature WHERE guid IN (117096, 117098, 117099, 117100, 117110, 117112, 118845, 118846, 118847);
INSERT INTO creature VALUES 
(117096, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1429.96, -5014.5, 12.2459, 3.69502, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(117099, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1429.62, -5018.57, 12.0452, 2.3834, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(117100, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1426.02, -5014.89, 12.0441, 5.5682, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(117110, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1449.38, -5012.48, 12.2222, 4.03666, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(117112, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1438.86, -5001.23, 11.6333, 5.30115, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(118845, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1446.3, -5014.31, 12.2782, 0.118048, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(118846, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1440.87, -5004.3, 11.6378, 1.93571, 300, 0, 0, 61902, 0, 0, 0, 0, 0), 
(118847, 43090, 1, 0, 0, 1, 171, 0, 32575, 0, 1437.01, -5012.76, 12.3017, 4.70424, 300, 0, 0, 61902, 0, 0, 0, 0, 0);

DELETE FROM creature WHERE id=43100 AND guid=117111;
INSERT INTO creature VALUES 
(117111, 43100, 1, 0, 0, 1, 171, 0, 32574, 0, 1437.26, -4982.95, 11.9746, 4.80243, 300, 0, 0, 0, 0, 0, 0, 0, 0);

delete from creature where guid in (2141,2142,2143,2144);

insert into creature values 
(2141, 43022, 738, 14, 374, 1, 0, 0, 0, 0, 15.031006, -7.927163, 4.969629, 2.737365, 0, 0, 0, 30951, 0, 0, 0, 0, 0),
(2142, 43023, 738, 14, 374, 1, 0, 0, 0, 0, -14.131185, 0.928000, 5.595734, 0.141628, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(2143, 43030, 738, 14, 374, 1, 0, 0, 0, 0, 30.682354, 0.193494, 10.842763, 0.043455, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(2144, 43051, 738, 14, 374, 1, 0, 0, 0, 0, -11.901013, -7.906730, 5.322639, 4.563423, 0, 0, 0, 24916, 0, 0, 0, 0, 0);

DELETE FROM creature_text WHERE entry=43090;
INSERT INTO creature_text VALUES 
(43090, 1, 0, "Strange... Just yesterday, I was dispatched to Ashenvale. ", 12, 0, 100, 396, 0, 21468, "Hellscream's Vanguard", 43037),
(43090, 2, 0, "Halfway there I got orders to meet you all here. This must be important.", 12, 0, 100, 396, 0, 21469, "Hellscream's Vanguard", 43038),
(43090, 3, 0, "Have you not heard?", 12, 0, 100, 6, 0, 21473, "Hellscream's Vanguard", 43039),
(43090, 4, 0, "An island has emerged from the depths... just off the coast of Stormwind.", 12, 0, 100, 396, 0, 21474, "Hellscream's Vanguard", 43040),
(43090, 5, 0, "We're gunna take it.", 12, 0, 100, 396, 0, 21475, "Hellscream's Vanguard", 43041),
(43090, 6, 0, "And once we do, Stormwind's days are numbered.", 12, 0, 100, 396, 0, 21476, "Hellscream's Vanguard", 43042),
(43090, 7, 0, "An island rose up from the sea... within striking distance of Stormwind? ", 12, 0, 100, 6, 0, 21470, "Hellscream's Vanguard", 43043),
(43090, 8, 0, "This is no coincidence! Azeroth herself has cast her lot with the Horde!", 12, 0, 100, 5, 0, 21471, "Hellscream's Vanguard", 43045),
(43090, 9, 0, "Here, warrior. Eat this.", 12, 0, 100, 1, 0, 21482, "Hellscream's Vanguard", 43049),
(43090, 10, 0, "Your reflexes will quicken, and your stamina will increase.", 12, 0, 100, 23, 0, 21483, "Hellscream's Vanguard", 43050),
(43090, 11, 0, "Hah! I don't need your crutches, friend. ", 12, 0, 100, 274, 0, 21491, "Hellscream's Vanguard", 43051),
(43090, 12, 0, "I've faced the best that Stormwind has to offer, and still I stand.", 12, 0, 100, 396, 0, 21492, "Hellscream's Vanguard", 43052),
(43090, 13, 0, "My axe has split as many Alliance skulls as yours, brother. Maybe more.", 12, 0, 100, 25, 0, 21484, "Hellscream's Vanguard", 43053),
(43090, 14, 0, "Hellscream will settle for nothing short of total victory. ", 12, 0, 100, 274, 0, 21485, "Hellscream's Vanguard", 43054),
(43090, 15, 0, "Should we fail, he'll chase us into the afterlife to take his retribution.", 12, 0, 100, 396, 0, 21486, "Hellscream's Vanguard", 43055),
(43090, 16, 0, "There is wisdom in your words, brother. I'll take that food of yours...", 12, 0, 100, 396, 0, 21493, "Hellscream's Vanguard", 43056),
(43090, 17, 0, "Indeed, brother. It would seem so...", 12, 0, 100, 273, 0, 21477, "Hellscream's Vanguard", 43058),
(43090, 18, 0, "Aye, as will I.", 12, 0, 100, 273, 0, 21494, "Hellscream's Vanguard", 43080),
(43090, 19, 0, "...their return is long overdue.", 12, 0, 100, 1, 0, 21488, "Hellscream's Vanguard", 43084),
(43090, 20, 0, "Hah! They should've known to send us in the first place.", 12, 0, 100, 5, 0, 21497, "Hellscream's Vanguard", 43085),
(43090, 21, 0, "Agreed, brother, but the Horde fights many fires these days and the Vanguard are few in number...", 12, 0, 100, 1, 0, 21489, "Hellscream's Vanguard", 43086),
(43090, 22, 0, "Fortunately for our enemies, we can be in only one place at a time.", 12, 0, 100, 1, 0, 21490, "Hellscream's Vanguard", 43087),
(43090, 23, 0, "Gah... this ship reeks of human.", 12, 0, 100, 14, 0, 21498, "Hellscream's Vanguard", 43093);

DELETE FROM creature_text WHERE entry=43100;
INSERT INTO creature_text VALUES 
(43100, 1, 0, "Enough jawing! There's our ride.", 12, 0, 100, 397, 0, 21283, "Legionnaire Nazgrim", 43089),
(43100, 2, 0, "That ship's been commissioned by Hellscream himself.", 12, 0, 100, 396, 0, 21284, "Legionnaire Nazgrim", 43090),
(43100, 3, 0, "You're all under strict orders - No harassing her crew!", 12, 0, 100, 274, 0, 21285, "Legionnaire Nazgrim", 43091),
(43100, 4, 0, "Hear my words, brothers!", 14, 0, 100, 5, 0, 21286, "Legionnaire Nazgrim", 43095),
(43100, 5, 0, "We sail to a virgin island, a gift from Azeroth to the Horde!", 14, 0, 100, 396, 0, 21287, "Legionnaire Nazgrim", 43096),
(43100, 6, 0, "Securing this land will win us our war!", 14, 0, 100, 397, 0, 21288, "Legionnaire Nazgrim", 43097),
(43100, 7, 0, "The enemy has fought well, for Alliance...but they grow weary.", 14, 0, 100, 396, 0, 21289, "Legionnaire Nazgrim", 43098),
(43100, 8, 0, "We shall crush what remains of them and lay claim to this land.", 14, 0, 100, 396, 0, 21290, "Legionnaire Nazgrim", 43099),
(43100, 9, 0, "From its shores, we shall conquer Stormwind, and with it any hope the enemy clings to.", 14, 0, 100, 396, 0, 21291, "Legionnaire Nazgrim", 43100),
(43100, 10, 0, "Azeroth will be reforged under a single banner!", 14, 0, 100, 5, 0, 21292, "Legionnaire Nazgrim", 43101),
(43100, 11, 0, "This banner!!", 14, 0, 100, 53, 0, 21293, "Legionnaire Nazgrim", 43102),
(43100, 12, 0, "What is the meaning of this!?", 12, 0, 100, 6, 0, 21294, "Legionnaire Nazgrim", 43114),
(43100, 13, 0, "We have a battle to win!", 12, 0, 100, 6, 0, 21295, "Legionnaire Nazgrim", 43116),
(43100, 14, 0, "Stand your ground, brothers! Make it bleed!", 14, 0, 100, 397, 0, 21296, "Legionnaire Nazgrim", 43122);

DELETE FROM creature_text WHERE entry=43023;
INSERT INTO creature_text VALUES 
(43023, 1, 0, "Ahoy!", 14, 0, 100, 22, 0, 21174, "Budd", 39642),
(43023, 2, 0, "I'm saaaailing!", 14, 0, 100, 22, 0, 21175, "Budd", 39643),
(43023, 3, 0, "Oooh... shiny!", 14, 0, 100, 397, 0, 21178, "Budd", 39652);

DELETE FROM creature_text WHERE entry=43022;
INSERT INTO creature_text VALUES 
(43022, 1, 0, "Don't pay Budd no nevermind... poor fella's got a few screws missin'.", 12, 0, 100, 0, 0, 21276, "Mack Fearsen", 39680),
(43022, 2, 0, "What the... ?", 12, 0, 100, 0, 0, 21278, "Mack Fearsen", 39687);

DELETE FROM creature_text WHERE entry=43051;
INSERT INTO creature_text VALUES 
(43051, 1, 0, "Budd! Noooo!", 14, 0, 100, 0, 0, 20915, "Adarrah", 42110),
(43051, 2, 0, "Captain! Shipwreck off the starboard bow! There appear to be survivors!", 14, 0, 100, 0, 0, 20916, "Adarrah", 39672);








