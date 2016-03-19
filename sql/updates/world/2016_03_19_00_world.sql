
-- misc azuremyst_isle
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7349 and SourceEntry=3 and ConditionValue1=16;
insert into conditions values
(15, 7349, 3, 0, 0, 15, 0, 16, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Priest");

update gossip_menu_option set option_text="I wish to learn Dual Specialization.", option_id=18, npc_option_npcflag=16, OptionBroadcastTextID=33765 where action_menu_id=10371;

update gossip_menu_option set option_text="Are you sure you would like to purchase Dual Specialization?", OptionBroadcastTextID=33766 where option_id=18 and npc_option_npcflag=16 and box_money>0;

update gossip_menu_option set option_text="I wish to unlearn my Talents.", option_id=16, npc_option_npcflag=16, OptionBroadcastTextID=62295 where action_menu_id=4461;

update gossip_menu_option set OptionBroadcastTextID=4510 where option_id =5 and npc_option_npcflag=16 and option_text="I am here for training.";

delete from gossip_menu_option where menu_id=7349 and id=1;

delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7349 and SourceEntry=1 and ConditionValue1=16;

delete from gossip_menu_option where menu_id=7264 and id=1;

delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7264 and SourceEntry=1 and ConditionValue1=128;

delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7264 and SourceEntry=3 and ConditionValue1=128;
insert into conditions values
(15, 7264, 3, 0, 0, 15, 0, 128, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Mage");

update gossip_menu_option set option_text="I wish to learn Dual Specialization.", OptionBroadcastTextID=33765, option_id=18, npc_option_npcflag=16, action_menu_id=10371 where menu_id=7260 and id=1;

delete from gossip_menu_option where menu_id=7260 and id=2;

update conditions set SourceEntry=3 where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7260 and SourceEntry=2 and ConditionValue1=2; 

delete from gossip_menu_option where menu_id=7262 and id=1;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7262 and SourceEntry=1 and ConditionValue1=4;

delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=7262 and SourceEntry=3 and ConditionValue1=4;
insert into conditions values
(15, 7262, 3, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter");

UPDATE quest_template SET SpecialFlags=4 WHERE Id=9283;

delete from creature_text where entry=16483;
INSERT INTO `creature_text` VALUES (16483, 0, 0, "The Light be praised! I would have died out here if it weren\'t for you, shaman! I must get to the ship.", 12, 35, 100, 0, 0, 0, "draenei survivor say thanks", 12448);
INSERT INTO `creature_text` VALUES (16483, 0, 1, "Huh? What happened? Oh... my head feels like it\'s going to explode! I\'d best get back to the crash site.", 12, 35, 100, 0, 0, 0, "draenei survivor say thanks", 12449);
INSERT INTO `creature_text` VALUES (16483, 0, 2, "Many thanks to you, $C. I\'d best get to the crash site and see how I can help out. Until we meet again.", 12, 35, 100, 0, 0, 0, "draenei survivor say thanks", 12450);
INSERT INTO `creature_text` VALUES (16483, 0, 3, "$C, you saved me!  I owe you a debt that I can never repay.  I\'ll go see if I can help the others.", 12, 35, 100, 0, 0, 0, "draenei survivor say thanks", 12451);
INSERT INTO `creature_text` VALUES (16483, 1, 0, "Oh no! Where are we? What happened? Look, there\'s part of the ship!", 12, 35, 100, 0, 0, 0, "draenei survivor say heal", 13407);
INSERT INTO `creature_text` VALUES (16483, 1, 1, "The last thing I remember is the ship falling and us getting into the pods.  I\'ll go see how I can help.  Thank you!", 12, 35, 100, 0, 0, 0, "draenei survivor say heal", 13408);
INSERT INTO `creature_text` VALUES (16483, 1, 2, "Where am I?  Who are you?  Oh no!  What happened to the ship?", 12, 35, 100, 0, 0, 0, "draenei survivor say heal", 13409);
INSERT INTO `creature_text` VALUES (16483, 1, 3, "Ugh... what is this place?  Is that all that\'s left of the ship over there?", 12, 35, 100, 0, 0, 0, "draenei survivor say heal", 13410);
INSERT INTO `creature_text` VALUES (16483, 1, 4, "Ughhh... I hurt.  Can you help me?", 12, 35, 100, 0, 0, 0, "draenei survivor say heal", 13411);
INSERT INTO `creature_text` VALUES (16483, 2, 0, "Oh, the pain...", 12, 35, 100, 0, 0, 0, "draenei survivor say pain", 13440);
INSERT INTO `creature_text` VALUES (16483, 2, 1, "Everything hurts. Please, make it stop...", 12, 35, 100, 0, 0, 0, "draenei survivor say pain", 13441);
INSERT INTO `creature_text` VALUES (16483, 2, 2, "I don\'t know if I can make it. Please help me...", 12, 35, 100, 0, 0, 0, "draenei survivor say pain", 13442);

update creature_template set AIName="", ScriptName="npc_draenei_survivor_16483" where entry=16483;

update quest_template set PrevQuestId=9283 where Id in (9371, 26958, 26963, 26966, 26968, 26969, 26970);

delete from spell_script_names where spell_id=2061;

