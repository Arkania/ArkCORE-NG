
-- vashj'ir

UPDATE creature_template SET gossip_menu_id=11352 WHERE entry=39882;

DELETE FROM gossip_menu_option WHERE menu_id=11352;
INSERT INTO gossip_menu_option VALUES 
(11352, 0, 0, "What's with the hat?", 40242, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11608;
INSERT INTO gossip_menu_option VALUES 
(11608, 0, 0, "I am ready to join you in the vision, Farseer.", 42108, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11522;
INSERT INTO gossip_menu_option VALUES 
(11522, 0, 5, "May I rest here?", 41414, 1, 1, 0, 0, 0, 0, 0, "", 0), 
(11522, 1, 1, "Do you have any supplies?", 41415, 1, 1, 0, 0, 0, 0, 0, "", 0); 

-- UPDATE creature_template SET gossip_menu_id=11514 WHERE entry=41340; -- its a multimenu.. done by script

DELETE FROM gossip_menu_option WHERE menu_id=11514;
INSERT INTO gossip_menu_option VALUES 
(11514, 0, 0, "Are there any weaknesses we can exploit? Any holes in the naga defenses?", 41378, 1, 1, 0, 0, 0, 0, 0, "", 0); 

-- UPDATE creature_template SET gossip_menu_id=11511 WHERE entry=41340; -- its a multimenu.. done by script

DELETE FROM gossip_menu_option WHERE menu_id=11511;
INSERT INTO gossip_menu_option VALUES 
(11511, 0, 0, "How did you escape, Pollard?", 41372, 1, 1, 0, 0, 0, 0, 0, "", 0); 

-- UPDATE creature_template SET gossip_menu_id=11510 WHERE entry=41340; -- its a multimenu.. done by script

DELETE FROM gossip_menu_option WHERE menu_id=11510;
INSERT INTO gossip_menu_option VALUES 
(11510, 0, 0, "Did you see Captain Taylor and his men?", 41376, 1, 1, 0, 0, 0, 0, 0, "", 0); 

-- UPDATE creature_template SET gossip_menu_id=11509 WHERE entry=41340; -- its a multimenu.. done by script

DELETE FROM gossip_menu_option WHERE menu_id=11509;
INSERT INTO gossip_menu_option VALUES 
(11509, 0, 0, "How did you get down here?", 41368, 1, 1, 0, 0, 0, 0, 0, "", 0); 

-- UPDATE creature_template SET gossip_menu_id=11508 WHERE entry=41340; -- its a multimenu.. done by script

DELETE FROM gossip_menu_option WHERE menu_id=11508;
INSERT INTO gossip_menu_option VALUES 
(11508, 0, 0, "What can you tell me about your captors?", 41370, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11489;
INSERT INTO gossip_menu_option VALUES 
(11489, 0, 0, "Who are you, friend?", 40025, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11444;
INSERT INTO gossip_menu_option VALUES 
(11444, 0, 0, "Make for that cave to the west. It's safe and dry.", 40804, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11525;
INSERT INTO gossip_menu_option VALUES 
(11525, 0, 0, "Whenever you're ready, Duarn.", 41467, 1, 1, 0, 0, 0, 0, 0, "", 0), 
(11525, 1, 0, "Let's speak with Nespirah.", 41530, 1, 1, 0, 0, 0, 0, 0, "", 0); 

DELETE FROM gossip_menu_option WHERE menu_id=11477;
INSERT INTO gossip_menu_option VALUES 
(11477, 0, 0, "I'm ready to begin the assault on the terrace.", 41193, 1, 1, 0, 0, 0, 0, 0, "", 0); 






