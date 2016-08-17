

delete from creature where id=34959;

UPDATE creature SET phaseMask=63 WHERE id=40074 and map=648;
UPDATE creature SET phaseMask=63 WHERE id=40075 and map=648;
UPDATE creature SET phaseMask=63 WHERE id=40076 and map=648;
UPDATE creature SET phaseMask=63 WHERE id=40077 and map=648;
UPDATE creature SET phaseMask=127 WHERE id=7395 and map=648;
UPDATE creature SET phaseMask=1 WHERE id=34830 and map=648;
UPDATE creature SET phaseMask=127 WHERE id=49131;

UPDATE creature_template SET spell1=45111 WHERE entry=34830;

DELETE FROM creature WHERE id=37804;
INSERT INTO creature VALUES 
(249036, 37804, 648, 1, 63, 31758, 0, -8373.49, 1261.65, 193.101, 4.096792, 300, 0, 0, 42, 0, 2, 0, 0, 0), 
(249048, 37804, 648, 1, 64, 31758, 0, -8104.13, 1488.53, 22.24953, 4.29351, 300, 0, 0, 42, 0, 0, 0, 0, 0);

delete from creature_addon where guid=249036;
insert into creature_addon values 
(249036, 249036, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=249036;
INSERT INTO waypoint_data VALUES 
(249036, 0, -8390.728, 1273.877, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 1, -8389.971, 1273.224, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 2, -8373.49, 1261.65, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 3, -8153.8, 1248.94, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 4, -8044.31, 1363.61, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 5, -7995.4, 1577.3, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 6, -8142.9, 1779.23, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 7, -8329.3, 1799.12, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 8, -8442.08, 1662.2, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 9, -8453.66, 1574.3, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 10, -8459.68, 1418.59, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 11, -8373.49, 1261.65, 193.101, 0, 0, 0, 0, 0, 0),
(249036, 12, -8153.8, 1248.94, 193.101, 0, 0, 0, 0, 0, 0);

UPDATE creature_template SET ScriptName="npc_kaja_cola_balloon_37804" WHERE entry=37804;

DELETE FROM creature_text WHERE entry=37804 AND groupid=0 AND id=6;
INSERT INTO creature_text VALUES 
(37804, 0, 6, "All new Kaja'Cola! Now with 100 percent more ideas!", 14, 0, 100, 0, 0, 0, "Kaja'Cola Balloon", 37402);

UPDATE creature_template SET AIName="", ScriptName="npc_sassy_hardwrench_34668" WHERE entry=34668;

delete from smart_scripts where entryorguid=34668;

UPDATE creature_template SET ScriptName="npc_foreman_dampwick_34872" WHERE entry=34872;

UPDATE creature_template SET AIName="", ScriptName="npc_sister_goldskimmer_34692" WHERE entry=34692;

delete from smart_scripts where entryorguid=34692;

UPDATE creature_template SET ScriptName="npc_candy_cane_35053" WHERE entry=35053;

UPDATE creature_template SET ScriptName="npc_hobart_grapplehammer_48494" WHERE entry=48494;

UPDATE creature_template SET ScriptName="npc_subject_nine_49150" WHERE entry=49150;

update creature_template_addon set auras=NULL where entry=49150;

delete from creature_queststarter where id=34668 and quest=25473;

DELETE FROM creature_text WHERE entry=34689 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(34689, 0, 0, "All you gotta do is learn how to cast Frost Nova. Then, head over to the training dummies that Bamm is shooting at and let 'er rip.", 12, 0, 100, 0, 0, 0, "Fizz Lighter Say", 49029);

UPDATE creature_text SET sound=12007 WHERE entry=34830 AND groupid=0;

UPDATE quest_template SET PrevQuestId=0 WHERE Id=25473;

DELETE FROM creature_text WHERE entry=34696;
INSERT INTO creature_text VALUES 
(34696, 0, 0, "All you gotta do is learn how to cast Corruption, and then go use it on these training dummies that Bamm is shooting at. Corrupt 'em!", 12, 0, 100, 0, 0, 0, "Evol Fingers Say", 49033),
(34696, 1, 0, "I knew I should have brought my folding chair.", 12, 0, 100, 0, 0, 0, "Evol Fingers Say", 36396),
(34696, 2, 0, "I swear this line's not moving!", 12, 0, 100, 0, 0, 0, "Evol Fingers Say", 36389),
(34696, 3, 0, "That rocket looks unsafe even by our standards!", 12, 0, 100, 0, 0, 0, "Evol Fingers Say", 36393),
(34696, 4, 0, "Why are we rocketing over to an island that has a volcano? Didn't we barely survive this scenario on Kezan?", 12, 0, 100, 0, 0, 0, "Evol Fingers Say", 36394);

UPDATE creature_text SET emote=0 WHERE entry=34689 AND groupid=1 AND id=0;

DELETE FROM creature_text WHERE entry=34689 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(34689, 1, 0, "All you gotta do is let me teach you how to perform a Primal Strike and then use it on these training dummies that Bamm is shooting at.", 12, 0, 100, 0, 0, 0, "Fizz Lighter", 49032);

DELETE FROM creature WHERE id=35053;
INSERT INTO creature VALUES 
(245772, 35053, 648, 1, 15, 0, 0, -8425.49, 1367.73, 104.68, 5.09122, 500, 0, 0, 102, 0, 0, 0, 0, 0),
(13300, 35053, 648, 1, 112, 0, 0, -8377.75, 1333.65, 102.53, 1.3439, 300, 0, 0, 102, 0, 0, 0, 0, 0), 
(13663, 35053, 648, 1, 64, 0, 0, -7854.03, 1844.73, 7.55749, 5.67232, 300, 0, 0, 102, 0, 0, 0, 0, 0); 

UPDATE creature_template SET gossip_menu_id=10611 WHERE entry=35053;

UPDATE creature_template SET gossip_menu_id=10612 WHERE entry=35054;






