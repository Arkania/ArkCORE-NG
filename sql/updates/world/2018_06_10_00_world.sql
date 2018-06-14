
-- fix some trainer npc in orgrimmar 
UPDATE creature_template SET npcflag=81 WHERE entry=52170;

DELETE FROM npc_trainer WHERE entry=45548 AND spell=-200401;

DELETE FROM npc_trainer WHERE entry=45545 AND spell=-200403;

DELETE FROM npc_trainer WHERE entry=52170 AND spell=-200408;

DELETE FROM npc_trainer WHERE entry=45559 AND spell=-200410;

DELETE FROM npc_trainer WHERE entry=52170 AND spell=2575;

DELETE FROM npc_trainer WHERE entry=52170 AND spell=2581;
INSERT INTO npc_trainer 
(entry, spell, spellcost, reqskill, reqskillvalue, reqlevel)
VALUES
(52170, 2581, 10, 0, 0, 5);

UPDATE npc_trainer SET reqlevel=5 WHERE entry=45540 AND spell=3279;

DELETE FROM npc_trainer WHERE entry=45550 AND spell=2550;

DELETE FROM npc_trainer WHERE entry=45550 AND spell=2551;
INSERT INTO npc_trainer 
(entry, spell, spellcost, reqskill, reqskillvalue, reqlevel)
VALUES
(45550, 2551, 84, 0, 0, 5);

-- First Aid
DELETE FROM npc_trainer WHERE spell in (3273, 3274, 7924, 10846, 27028, 45542, 74559);

-- fishing
DELETE FROM npc_trainer WHERE spell in (7620, 7731, 7732, 18248, 33095, 51294, 88868);

-- cooking
DELETE FROM npc_trainer WHERE spell in (2550, 3102, 3413, 18260, 33359, 51296, 88053);

-- archaeology
DELETE FROM npc_trainer WHERE spell in (78670, 88961, 89718, 89719, 89720, 89721, 89722);

-- Alchemist
DELETE FROM npc_trainer WHERE spell in (2259, 3101, 3464, 11611, 28596, 51304, 80731);

-- Blacksmithing
DELETE FROM npc_trainer WHERE spell in (2018, 3100, 3538, 9785, 29844, 51300, 76666);

-- Enchanting
DELETE FROM npc_trainer WHERE spell in (7411, 7412, 7413, 13920, 28029, 51313, 74258);

-- Engineer
DELETE FROM npc_trainer WHERE spell in (4036, 4037, 4038, 12656, 30350, 51306, 82774);

-- Herbalist
DELETE FROM npc_trainer WHERE spell in (2366, 2368, 3570, 11993, 28695, 50300, 74519);

-- Scribe
DELETE FROM npc_trainer WHERE spell in (45357, 45358, 45359, 45360, 45361, 45363, 86008);

-- Jewelcrafter
DELETE FROM npc_trainer WHERE spell in (25229, 25230, 28894, 28895, 28897, 51311, 73318);

-- Leatherworker
DELETE FROM npc_trainer WHERE spell in (2108, 3104, 3811, 10662, 32549, 51302, 81199);

-- Miner
DELETE FROM npc_trainer WHERE spell in (2575, 2576, 3564, 10248, 29354, 50310, 74517);

-- Skinner
DELETE FROM npc_trainer WHERE spell in (8613, 8617, 8618, 10768, 32678, 50305, 74522);

-- Tailor
DELETE FROM npc_trainer WHERE spell in (3908, 3909, 3910, 12180, 26790, 51309, 75156);

update gossip_menu_option set npc_option_npcflag=16 where npc_option_npcflag=0 and option_icon=3 and option_text like "%train%";

update gossip_menu_option set npc_option_npcflag=128 where npc_option_npcflag=0 and option_icon=1 and option_text like "%browse%";

update gossip_menu_option set OptionBroadcastTextID=3370 where OptionBroadcastTextID=0 and option_text like "I want to browse your goods%";

update gossip_menu_option set option_id=3 where option_id=0 and option_text like "I want to browse your goods%";

update gossip_menu_option set OptionBroadcastTextID=8897 where OptionBroadcastTextID=0 and option_text like "Let me browse your goods%";

update gossip_menu_option set option_id=3 where option_id=0 and option_text like "Let me browse your goods%";

update gossip_menu_option set OptionBroadcastTextID=7658 where OptionBroadcastTextID=0 and option_text like "Teach me the ways of the spirits%";

update gossip_menu_option set option_id=5 where option_id=0 and option_text like "Teach me the ways of the spirits%";

update gossip_menu_option set OptionBroadcastTextID=8442 where OptionBroadcastTextID=0 and option_text like "Please teach me%";

update gossip_menu_option set option_id=5 where option_id=0 and option_text like "Please teach me%";


