
update creature set spawndist=0, MovementType=0 where guid in (42270,42037,41860,41604,41557,41459,41440,41314,41301,41180,37346);
update creature set spawndist=0, MovementType=0 where guid in (37155,37084,37049,37022,36380,36339,36288,36228,35869,35690,35579);
update creature set spawndist=0, MovementType=0 where guid in (35285,35268,35212,35131,35061,35033,34748,34654,34541,34477,34469,34466);

update creature set spawndist=0, MovementType=0 where guid in (46132,46112,45844,45829,45801,45792,45713,45623,45534,45412,45408);
update creature set spawndist=0, MovementType=0 where guid in (45369,45324,45005,44560,44554,44530,44526,44513,44421,44326,44310);

UPDATE creature_template SET AIName="", ScriptName="npc_hired_looter_35234" WHERE entry=35234;

delete from smart_scripts where entryorguid=35234;

update creature set spawndist=0, MovementType=0 where id in (35234, 35063);

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_citizen_35063" WHERE entry=35063;

delete from smart_scripts where entryorguid=35063;

delete from spell_script_names where spell_id=70330;
insert into spell_script_names values 
(70330, "spell_knock_back_70330");

delete from creature where guid in (248968, 245737, 283983, 248430, 283990, 248429);

UPDATE npc_text SET text0_0="You cannot afford Szabo's services. We do not work for free, little waif.$B$BAway with you to the bank. Bring Szabo all of your macaroons.", BroadcastTextID0=35362, em0_0=274 WHERE ID=14701;

DELETE FROM conditions where SourceGroup in (10620,10622,10624);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10622, 14700, 9, 14109);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10622, 14701, 9, 14109, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10622, 14700, 9, 14110);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10622, 14701, 9, 14110, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10622, 9, 14109, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10622, 9, 14110, 1);

DELETE FROM gossip_menu WHERE entry=10620 and text_id=14698;
INSERT INTO gossip_menu VALUES (10620, 14698);

UPDATE npc_text SET text0_0="That bling is phat like your momma!", BroadcastTextID0=35355 WHERE ID=14698;

DELETE FROM gossip_menu WHERE entry=10620 and text_id=14699;
delete from npc_text where id=14699;

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10620, 14697, 9, 14109);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10620, 14698, 9, 14109, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10620, 14697, 9, 14110);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10620, 14698, 9, 14110, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10620, 9, 14109, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionTarget=0 AND ConditionValue1=14110 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10620, 9, 14110, 1);

UPDATE npc_text SET text0_0="", text0_1="Yeah? Yous don't look like you got the moolah to buy anything from me.$B$B<Missa pops her bubblegum.>$B$BMaybe yous forgot to go to the bank?", BroadcastTextID0=35382 WHERE ID=14704;

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10624, 14703, 9, 14109);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10624, 14704, 9, 14109, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10624, 14703, 9, 14110);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(14, 10624, 14704, 9, 14110, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10624, 9, 14109, 1);

INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES 
(15, 10624, 9, 14110, 1);

UPDATE creature SET phaseGroup=557 WHERE guid=245772;

UPDATE creature SET phaseGroup=557 WHERE guid=245773;

delete from creature_queststarter where id=35200 and quest=14115;

UPDATE creature_template SET npcflag=0, AIName="", ScriptName="npc_pirate_party_crasher_35200" WHERE entry=35200;

delete from smart_scripts where entryorguid=35200;

UPDATE creature_template SET ScriptName="npc_kezan_partygoer_35202" WHERE entry=35202;

DELETE FROM waypoint_data WHERE id=285419 AND point=0;
INSERT INTO waypoint_data VALUES 
(285419, 0, -8446.03, 1315.03, 108.055, 0, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=285419 AND point=1;
INSERT INTO waypoint_data VALUES 
(285419, 1, -8444.02, 1306.15, 108.055, 0, 0, 0, 0, 100, 0);

UPDATE creature_template_addon SET auras="89842" WHERE entry=48805;

UPDATE gameobject SET position_x=-8421.82, position_y=1323.34, position_z=101.99, orientation=2.34162 WHERE guid=168379;

UPDATE creature_template_addon SET emote=0 WHERE entry=37709;

UPDATE creature_template SET flags_extra=0 WHERE entry=35234;

update creature_addon set emote=0 where guid in (245472,245474,245478,245480,245482,245483,245485,245489,245493,245495,245497,245500,245502,245504,245505,245509);
update creature_addon set emote=0 where guid in (245511,245518,245522,245523,245524,245525,245526,245528,245536,245544,245549,245550,245551,245555);
update creature_addon set emote=0 where guid in (245557,245558,245559,285477,285478,285479,285480,285481,285482,285483,285484,285485,285486,285487,285488,285489,285490);

update creature set phaseId=383 where id=35234 and phaseId=172;
 
UPDATE creature_template SET ScriptName="npc_hot_rod_34840" WHERE entry=34840;

UPDATE creature_template_addon SET auras="" WHERE entry=34840; -- 66392

DELETE FROM creature_template_addon WHERE entry=37676;
INSERT INTO creature_template_addon VALUES 
(37676, 0, 0, 0, 1, 0, "70329");

-- sound is random from core script
UPDATE creature_text SET emote=0, sound=0 WHERE entry in (35063,35075) AND groupid=0;

UPDATE creature_template SET ScriptName="npc_kezan_citizen_35063_35075" WHERE entry in (35063, 35075);
 
delete from creature_equip_template where entry=35234;
insert into creature_equip_template values 
(35234, 0, 1906, 12745, 0); 

UPDATE quest_template SET SpecialFlags=0 WHERE Id=28607;

UPDATE gossip_menu_option SET OptionBroadcastTextID=7658, option_id=5, npc_option_npcflag=16 WHERE menu_id=10684 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=2522, option_id=5, npc_option_npcflag=16 WHERE menu_id=10683 AND id=0;

UPDATE creature_template SET unit_flags2=0, dynamicflags=0 WHERE entry=34673;

UPDATE creature_template SET unit_flags2=0, dynamicflags=0 WHERE entry=34692;

UPDATE creature_template SET unit_flags2=0, dynamicflags=0 WHERE entry=34696;

-- warrior
UPDATE gossip_menu_option SET OptionBroadcastTextID=3147 WHERE menu_id=10821 AND id=0;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10821 AND SourceEntry=15000;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10821, 15000, 15, 1534);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10821 AND SourceEntry=15001;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10821, 15001, 15, 1);

-- no paladin
-- hunter
DELETE FROM gossip_menu WHERE entry=10675 AND text_id=14797;
INSERT INTO gossip_menu VALUES (10675, 14797);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10675 AND SourceEntry=14796;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10675, 14796, 15, 1531);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10675 AND SourceEntry=14797;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10675, 14797, 15, 4);

delete from gossip_menu_option where menu_id=10675 and id=0;
insert into gossip_menu_option values 
(10675, 0, 3, "I seek training in the ways of the Hunter.", 7643, 5, 16, 0, 0, 0, 0, 0, "", 0);

-- rogue
DELETE FROM gossip_menu WHERE entry=10686 AND text_id=14812;
INSERT INTO gossip_menu VALUES (10686, 14812);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10686 AND SourceEntry=14811;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10686, 14811, 15, 1527);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10686 AND SourceEntry=14812;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10686, 14812, 15, 8);

delete from gossip_menu_option where menu_id=10686 and id=0;
insert into gossip_menu_option values 
(10686, 0, 3, "Can you train me how to use rogue skills?", 7491, 5, 16, 0, 0, 0, 0, 0, "", 0);

-- priest
DELETE FROM gossip_menu WHERE entry=10685 AND text_id=14600;
INSERT INTO gossip_menu VALUES (10685, 14600);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10685 AND SourceEntry=14600;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10685, 14600, 15, 16);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10685 AND SourceEntry=14601;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10685, 14601, 15, 1519);

delete from gossip_menu_option where menu_id=10685 and id=0;
insert into gossip_menu_option values 
(10685, 0, 3, "I require priest training.", 7169, 5, 16, 0, 0, 0, 0, 0, "", 0);

-- shaman
DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10684 AND SourceEntry=14807;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10684, 14807, 15, 1471);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10684 AND SourceEntry=14808;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10684, 14808, 15, 64);

-- mage
DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10683 AND SourceEntry=14805;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10683, 14805, 15, 1407);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10683 AND SourceEntry=14806;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10683, 14806, 15, 128);

-- warlock
DELETE FROM gossip_menu WHERE entry=10681 AND text_id=14596;
INSERT INTO gossip_menu VALUES (10681, 14596);

UPDATE gossip_menu_option SET OptionBroadcastTextID=2544 WHERE menu_id=10681 AND id=0;

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10681 AND SourceEntry=14595;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10681, 14595, 15, 1279);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10681 AND SourceEntry=14596;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES 
(14, 10681, 14596, 15, 256);

-- ghost healer kezan.. remove double, visible all phases..
delete from creature where guid = 245789;
update creature set phaseId=0, phaseGroup=558 where guid=285377;

-- ghost healer lost island
delete from creature where guid in (248360, 285379);

DELETE FROM creature WHERE guid IN (9249, 9250, 9251, 9252, 9253, 9254, 9255, 9256, 9257, 9258, 9259, 9263);
INSERT INTO creature VALUES 
(9249, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, -8115.33, 1520.22, 10.3416, 3.19395, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9250, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 1475.17, 2059.1, 222.899, 0.593412, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9251, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 615.972, 1962.5, 12.7702, 6.02139, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9252, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 858.247, 2331.56, 11.8153, 3.9619, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9253, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 1396.05, 1337.23, 130.325, 3.35103, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9254, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 1735.44, 2690.9, 85.8003, 0.23094, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9255, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 716.535, 1830.71, 104.456, 3.89208, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9256, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 867.524, 2780.05, 114.394, 0.174533, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9257, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 521.91, 2707.84, 105.979, 3.28122, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9258, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 1000.78, 3310.56, 3.48974, 0.10472, 300, 0, 0, 4120, 0, 0, 0, 0, 0), 
(9259, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 630.9, 3121.1, 3.9, 5.78469, 300, 0, 0, 4120, 0, 0, 0, 0, 0),
(9263, 39660, 648, 0, 0, 1, 0, 558, 5233, 0, 2035.77, 2324.85, 78.911, 1.38469, 300, 0, 0, 4120, 0, 0, 0, 0, 0);

UPDATE creature_template SET InhabitType=4 WHERE entry=36719;

UPDATE creature_template SET mindmg=5, maxdmg=7, attackpower=32, minrangedmg=3, maxrangedmg=4 WHERE entry=35812;

delete from creature where guid=15455930;
update creature set phaseId=171 where guid=246042;

delete from creature where guid=15455934;
update creature set phaseId=172 where guid=246093;

delete from creature where guid=15456351;
update creature set phaseId=181 where guid=6683;

delete from creature where guid in (15455923, 15456483, 15456484);

UPDATE creature_template SET unit_flags2=0 WHERE entry=35758;

delete from gossip_menu_option where menu_id=10549 and id=0;
insert into gossip_menu_option values 
(10549, 0, 3, "I seek training in the ways of the Hunter.", 7643, 5, 16, 0, 0, 0, 0, 0, "", 0);


