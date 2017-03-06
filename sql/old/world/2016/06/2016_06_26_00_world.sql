
-- Nerub'Ar Victim
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|4, `flags_extra`=`flags_extra`|64 WHERE `entry`=25284;

-- quest removed from game
UPDATE `gameobject_loot_template` SET `QuestRequired`=0 WHERE `Entry`=1409 AND `Item`=3340;

-- Feeding Arngrim 
UPDATE `creature_template` SET `unit_flags`=0 WHERE  `entry`=30423;
UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 30422;

DELETE FROM `smart_scripts` WHERE `entryorguid` =30422;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(30422, 0, 0, 1, 8,  0, 100, 0, 56727, 0, 0, 0, 12, 30423, 1, 240000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roaming Jormungar - On Spellhit - Spawn Disembodied Jormungar'),
(30422, 0, 1, 0,61,  0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Roaming Jormungar - Linked with Previous Event - Despawn');

UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 30423;

DELETE FROM `smart_scripts` WHERE `entryorguid` =30423;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(30423, 0, 0, 0, 2,  0, 100, 1, 0, 30, 0, 0, 11, 56732, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Disembodied Jormungar - On 30% HP - Summon Arngrim'),
(30423, 0, 1, 2,38,  0, 100, 0, 1, 1, 0, 0, 11, 56731, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Disembodied Jormungar - On Spellhit - Cast Kill Credit'),
(30423, 0, 2, 0,61,  0, 100, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Disembodied Jormungar - Linked with Previous Event - Despawn');

UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`= 30425;

DELETE FROM `smart_scripts` WHERE `entryorguid` =30425;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(30425, 0, 0, 0,11,  0, 100, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 0, 19, 30423, 200, 0, 0, 0, 0, 0, 'Arngrim - On Spawn - Move to closest disembodied jormungar'),
(30425, 0, 1, 2, 1,  0, 100, 0, 10000, 10000, 30000, 30000, 45, 1, 1, 0, 0, 0, 0, 19, 30423, 20, 0, 0, 0, 0, 0, 'Arngrim - OOC - Cast Ping Jormungar'),
(30425, 0, 2, 0,61,  0, 100, 0, 0, 0, 0, 0, 41, 5000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Arngrim - OOC - Linked with Previous Event - Despawn After 5 seconds');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`IN(13,17) AND `SourceEntry`=56727;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(17,0,56727,0,0,31,1,3,30422,0,0,0, '', 'Arngrims Tooth only hits Roaming Jormungar'),
(13,0,56727,0,0,31,1,3,30422,0,0,0, '', 'Arngrims Tooth only hits Roaming Jormungar');

-- Whats Haunting With Hill?
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`='' WHERE  `entry`=23555;

DELETE FROM `smart_scripts` WHERE `entryorguid` =23555;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(23555, 0, 0, 0, 2,  0, 100, 0, 0, 50, 6000, 11000, 11, 37933, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Risen Husk - On Less than 50% HP - Cast Consume Flesh'),
(23555, 0, 1, 2, 6,  0, 100, 0, 0, 0, 0, 0, 11, 42511, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Risen Husk - On Death - Cast Summon Restless Apparotation'),
(23555, 0, 2, 0,61,  0, 100, 0, 0, 0, 0, 0, 11, 42512, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Risen Husk - Linked with Previous Event - Cast Witch Hill Information Credit');

-- Risen Spirit 23554
UPDATE `creature_template` SET `AIName`= 'SmartAI',`ScriptName`='' WHERE  `entry`=23554;

DELETE FROM `smart_scripts` WHERE `entryorguid` =23554;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(23554, 0, 0, 0, 0,  0, 100, 0, 0, 0, 6000, 11000, 11, 43127, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Risen Spirit - IC - Intangible Presence'),
(23554, 0, 1, 2, 6,  0, 100, 0, 0, 0, 0, 0, 11, 42511, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Risen Spirit - On Death - Cast Summon Restless Apparotation'),
(23554, 0, 2, 0,61,  0, 100, 0, 0, 0, 0, 0, 11, 42512, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Risen Spirit - Linked with Previous Event - Cast Witch Hill Information Credit');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND  `SourceEntry`IN(23554,23555) AND `SourceId`=0;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(22,2,23554,0,0,9,0,11180,0,0,0,0,'','AI Only executes if player is on Whats haunting witch Hill'),
(22,2,23555,0,0,9,0,11180,0,0,0,0,'','AI Only executes if player is on Whats haunting witch Hill');

-- quest linking for Judgment at the eye of eternity/ Heroic Judgment at the eye of eternity
-- requires The Key to the Focusing Iris for 10m or Heroic: The Key to the Focusing Iris for 25m
UPDATE `quest_template` SET `PrevQuestId`=13372 WHERE  `Id`=13384;
UPDATE `quest_template` SET `PrevQuestId`=13375 WHERE  `Id`=13385;
UPDATE `quest_template` SET `NextQuestId`=13384 WHERE  `Id`=13372;
UPDATE `quest_template` SET `NextQuestId`=13385 WHERE  `Id`=13375;

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(32641,32642,32638,32639);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(32641,32642,32638,32639) AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(32641, 0, 0, 0, 23, 0, 100, 1, 61424, 1, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drix Blackwrench - Mojodishu - On Has Aura - Set Phase 1'),
(32641, 0, 1, 2, 23, 1, 100, 1, 61424, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drix Blackwrench - On Has No Aura (Phase 1) - Set NPC Flags'),
(32641, 0, 2, 3, 61, 1, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drix Blackwrench - Link - Say'),
(32641, 0, 3, 0, 61, 1, 100, 1, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Drix Blackwrench - Link - Despawn After 2 seconds'),

(32642, 0, 0, 0, 23, 0, 100, 1, 61424, 1, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mojodishu - On Has Aura - Set Phase 1'),
(32642, 0, 1, 2, 23, 1, 100, 1, 61424, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mojodishu - On Has No Aura (Phase 1) - Set NPC Flags'),
(32642, 0, 2, 3, 61, 1, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mojodishu - Link - Say'),
(32642, 0, 3, 0, 61, 1, 100, 1, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Mojodishu - Link - Despawn After 2 seconds'),

(32638, 0, 0, 0, 23, 0, 100, 1, 61424, 1, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hakmud of Argus <Traveling Trader> - Mojodishu - On Has Aura - Set Phase 1'),
(32638, 0, 1, 2, 23, 1, 100, 1, 61424, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hakmud of Argus <Traveling Trader> - On Has No Aura (Phase 1) - Set NPC Flags'),
(32638, 0, 2, 3, 61, 1, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hakmud of Argus <Traveling Trader> - Link - Say'),
(32638, 0, 3, 0, 61, 1, 100, 1, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Hakmud of Argus <Traveling Trader> - Link - Despawn After 2 seconds'),

(32639, 0, 0, 0, 23, 0, 100, 1, 61424, 1, 0, 0, 22, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gnimo <Adventurous Tinker> - On Has Aura - Set Phase 1'),
(32639, 0, 1, 2, 23, 1, 100, 1, 61424, 0, 0, 0, 81, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gnimo <Adventurous Tinker> - On Has No Aura (Phase 1) - Set NPC Flags'),
(32639, 0, 2, 3, 61, 1, 100, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gnimo <Adventurous Tinker> - Link - Say'),
(32639, 0, 3, 0, 61, 1, 100, 1, 0, 0, 0, 0, 41, 2000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Gnimo <Adventurous Tinker> - Link - Despawn After 2 seconds');

DELETE FROM `creature_text` WHERE `entry` in(32641,32642,32638,32639);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`,`BroadcastTextID`) VALUES
(32641, 0, 0, 'Our friendship is OVER!', 12, 0, 100, 6, 0, 0, 'Drix Blackwrench',33025),
(32641, 0, 1, 'Hey, yea, I''ve always wanted to be stranded somewhere.', 12, 0, 100, 0, 0, 0, 'Drix Blackwrench',33024),
(32641, 0, 2, 'Oh, I see how it is... You''re gonna do me like that, eh?', 12, 0, 100, 0, 0, 0, 'Drix Blackwrench',33023),
(32641, 0, 3, 'You''re just gonna leave me here? How am I supposed to get home?', 12, 0, 100, 0, 0, 0, 'Drix Blackwrench',33026),
(32642, 0, 0, 'Really, mon? Just like dat you be leavin'' Mojodishu behind?', 12, 0, 100, 1, 0, 0, 'Mojodishu',33027),
(32642, 0, 1, 'Dis bad mojo what you doin''. Don''t say Mojodishu didn''t warn ya!', 12, 0, 100, 0, 0, 0, 'Mojodishu',33028),
(32642, 0, 2, 'Be dat way den!', 12, 0, 100, 0, 0, 0, 'Mojodishu',33029),
(32638, 0, 0, 'Hakmud cannot work under these conditions! Goodbye!', 12, 0, 100, 0, 0, 0, 'Hakmud of Argus <Traveling Trader>',33017),
(32638, 0, 1, 'I thought we were friend, buddy! You leave Hakmud stranded?', 12, 0, 100, 0, 0, 0, 'Hakmud of Argus <Traveling Trader>',33018),
(32638, 0, 2, 'Thanks, buddy! Thanks for nothing!', 12, 0, 100, 0, 0, 0, 'Hakmud of Argus <Traveling Trader>',33014),
(32638, 0, 3, 'What is Hakmud supposed to do now, buddy?', 12, 0, 100, 0, 0, 0, 'Hakmud of Argus <Traveling Trader>',33016),
(32638, 0, 4, 'Why do you treat Hakmud like this, buddy?', 12, 0, 100, 0, 0, 0, 'Hakmud of Argus <Traveling Trader>',33015),
(32639, 0, 0, 'Goodbye! You were Gnimo''s best friend ever!', 12, 0, 100, 0, 0, 0, 'Gnimo <Adventurous Tinker>',33020),
(32639, 0, 1, 'Nobody loves Gnimo...', 12, 0, 100, 0, 0, 0, 'Gnimo <Adventurous Tinker>',33019),
(32639, 0, 2, 'Time for Gnimo to shut down.', 12, 0, 100, 0, 0, 0, 'Gnimo <Adventurous Tinker>',33021);

DELETE FROM creature_text WHERE entry=19228;
INSERT INTO creature_text VALUES 
(19228, 0, 0, "Hey all!  So how long until the jokes spawn?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16382),
(19228, 0, 1, "I just flew in from Ironforge and, Boy!, are my mount's wings tired!", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16649),
(19228, 0, 2, "Hey folks, go easy on me... it's my first time.", 12, 0, 100, 24, 0, 0, "Perry Gatner", 16328),
(19228, 0, 3, "Thanks for coming out to see me!  I hope you are ready for a good time, because I am.", 12, 0, 100, 21, 0, 0, "Perry Gatner", 16327),
(19228, 0, 4, "Whoa!  Is all that applause for me?  Thanks for coming out!", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16326),
(19228, 1, 0, "I never met a tauren I didn't like...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16378),
(19228, 2, 0, "To eat!!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16379),
(19228, 3, 0, "Last week I was in Goldshire. Have you been there?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16651),
(19228, 4, 0, "That town's so small, I asked a kid to draw me a map. He drew it on the back of a Defias wanted poster...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16652),
(19228, 5, 0, "to scale!!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16653),
(19228, 6, 0, "Impersonation time!!  I call this, \"The Silly Tauren.\"", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16337),
(19228, 7, 0, "The comedian clears his throat.", 16, 0, 100, 0, 0, 0, "Perry Gatner", 16338),
(19228, 8, 0, "The comedian impersonates a tauren.", 16, 0, 100, 5, 0, 6386, "Perry Gatner", 16580),
(19228, 9, 0, "Here's a good one, why do watermelons have water in them? ", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16333),
(19228, 10, 0, "Because they are planted in the spring!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16336),
(19228, 11, 0, "What's the deal with women?  I mean they are always like...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16339),
(19228, 12, 0, "The comedian impersonates a human female.", 16, 0, 100, 5, 0, 6143, "Perry Gatner", 16583),
(19228, 13, 0, "And then gnomes are even worse!  They are always saying stuff like...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16340),
(19228, 14, 0, "The comedian impersonates a gnome.", 16, 0, 100, 5, 0, 6133, "Perry Gatner", 16581),
(19228, 15, 0, "What time is it when an elekk sits on your fence?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16368),
(19228, 16, 0, "Time to get a new fence!!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16369),
(19228, 17, 0, "If I knew it was going to be like this, I'd have worn my Greater Boots of Laughter.", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16388),
(19228, 17, 1, "Apparently my reputation with you people is hostile.", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16385),
(19228, 17, 2, "Wow!  The laughs don't drop very often here, do they?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16389),
(19228, 18, 0, "Hey! Hey! Hey! It's Raliq the drunk... His momma's so fat she didn't just make the front cover of Ogre Today...", 12, 0, 100, 25, 0, 0, "Perry Gatner", 16667),
(19228, 19, 0, "She made the back cover too!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16668),
(19228, 20, 0, "The gnomes used to be a nice respectful people...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16669),
(19228, 21, 0, "The other day I saw one walking down the street shouting, \"Once you go gnome, you never go home!\"", 12, 0, 100, 1, 0, 4415, "Perry Gatner", 16670),
(19228, 22, 0, "I love blood elf women.  Especially when they say stuff like this...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16374),
(19228, 23, 0, "The comedian impersonates a blood elf.", 16, 0, 100, 5, 0, 9643, "Perry Gatner", 16582),
(19228, 24, 0, "So the blood elves think they're just one step away from ruling the world...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16682),
(19228, 25, 0, "Twelve steps is more like it!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16683),
(19228, 26, 0, "One last impersonation.  It's tough, but let's see if you can guess who it is...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16351),
(19228, 27, 0, "The comedian impersonates an orc.", 16, 0, 100, 5, 0, 7195, "Perry Gatner", 16584),
(19228, 28, 0, "Now that the show's done, can someone run me through Scarlet Monestary?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16381),
(19228, 28, 1, "Thank you! Don't forget to tip your waiters! Good night folks.", 12, 0, 100, 0, 0, 0, "Perry Gatner", 16341),
(19228, 28, 2, "Well, it's time to take these comedic muscles elsewhere. Have a good night all!", 12, 0, 100, 23, 0, 0, "Perry Gatner", 16348),
(19228, 28, 3, "Is it over already?  You've been great folks.  Walk safely and have a good night.", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16343),
(19228, 29, 0, "How many kobolds does it take to change a lantern wick?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16657),
(19228, 30, 0, "You no take candle!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16658),
(19228, 31, 0, "Goldshire's inn advertises a lakeside view...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16655),
(19228, 32, 0, "I saw a murloc swim by my window.", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16656),
(19228, 33, 0, "Have you ever noticed that all those cute, orc kids look the same?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16331),
(19228, 34, 0, "It's too bad they don't stay cute.  There must be some rite of passage in the Barrens called, \"Climb ugly tree and fall out.\"", 12, 0, 100, 0, 0, 0, "Perry Gatner", 16334),
(19228, 35, 0, "I've heard that gnomes can grant wishes...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16375),
(19228, 36, 0, "Well I wish they'd go away!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16376),
(19228, 37, 0, "Look who's here, it's Raliq the drunk... His momma's so fat dragons won't eat her...", 12, 0, 100, 25, 0, 0, "Perry Gatner", 16665),
(19228, 38, 0, "They don't know where to store the leftovers!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16666),
(19228, 39, 0, "My wife and I were happy for 23 years...", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16370),
(19228, 40, 0, "And then we met!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16371),
(19228, 41, 0, "What do you call a broken boomerang?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16372),
(19228, 42, 0, "A stick!", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16373),
(19228, 43, 0, "So this gnome tells a tauren that he's been to Molten Core.", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16332),
(19228, 44, 0, "The tauren says, \"That's a load of bull.\"", 12, 0, 100, 5, 0, 0, "Perry Gatner", 16335),
(19228, 45, 0, "How desperate do you have to be for allies that you recruit your livestock?", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16680),
(19228, 46, 0, "I own a dog, but I'm not giving him a sword.", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16681),
(19228, 47, 0, "Used to be you couldn't trust a goblin...", 12, 0, 100, 1, 0, 0, "Perry Gatner", 16671),
(19228, 48, 0, "Who am I kiddin'? If you trade with goblins you'd better have iron plating in your coinpurse.", 12, 0, 100, 6, 0, 0, "Perry Gatner", 16672);

-- Perry Gatner
SET @ENTRY := 19228;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,38,0,100,0,1,1,0,0,53,0,19228,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Data Set 1 1 - Start WP"),
(@ENTRY,@SOURCETYPE,1,2,40,0,100,0,3,19228,0,0,54,220000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Reached WP3 - Pause WP"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,80,1922800,2,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Reached WP3 - Run Script 1"),
(@ENTRY,@SOURCETYPE,3,0,40,0,100,0,6,19228,0,0,41,5000,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Reached WP6 - Despawn"),
(@ENTRY,@SOURCETYPE,4,0,40,0,100,0,2,19228,0,0,80,1922801,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Reached WP2 - Run Script 2"),
(@ENTRY,@SOURCETYPE,5,0,40,0,100,0,4,19228,0,0,80,1922802,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - On Reached WP6 - Run Script 3");


-- Perry Gatner
SET @ENTRY := 1922800;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,3000,3000,0,0,45,4,4,0,0,0,0,19,19271,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Set Data 4 4 on Albert Quarksprocket"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,14000,14000,0,0,1,3,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,7000,7000,0,0,1,4,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,7000,7000,0,0,1,5,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,7000,7000,0,0,1,6,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,6,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,7,0,0,0,100,0,5000,5000,0,0,1,8,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,8,0,0,0,100,0,7000,7000,0,0,45,2,2,0,0,0,0,19,19271,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Set Data 2 2 on Albert Quarksprocket"),
(@ENTRY,@SOURCETYPE,9,0,0,0,100,0,14000,14000,0,0,1,11,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,10,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,11,0,0,0,100,0,7000,7000,0,0,1,12,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,12,0,0,0,100,0,7000,7000,0,0,1,13,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,13,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,14,0,0,0,100,0,5000,5000,0,0,1,14,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,15,0,0,0,100,0,7000,7000,0,0,45,3,3,0,0,0,0,19,19271,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Set Data 3 3 on Albert Quarksprocket"),
(@ENTRY,@SOURCETYPE,16,0,0,0,100,0,12000,12000,0,0,1,0,0,0,0,0,0,19,18756,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line 1 on Hilton Paris"),
(@ENTRY,@SOURCETYPE,17,0,0,0,100,0,2000,2000,0,0,1,17,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,18,0,0,0,100,0,7000,7000,0,0,45,6,6,0,0,0,0,19,19271,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Set Data 6 6 on Albert Quarksprocket"),
(@ENTRY,@SOURCETYPE,19,0,0,0,100,0,14000,14000,0,0,1,20,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,20,0,0,0,100,0,7000,7000,0,0,1,21,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,21,0,0,0,100,0,7000,7000,0,0,1,22,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,22,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,23,0,0,0,100,0,5000,5000,0,0,1,23,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,24,0,0,0,100,0,7000,7000,0,0,45,5,5,0,0,0,0,19,19271,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Set Data 5 5 on Albert Quarksprocket"),
(@ENTRY,@SOURCETYPE,25,0,0,0,100,0,14000,14000,0,0,1,26,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,26,0,0,0,100,0,7000,7000,0,0,1,7,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,27,0,0,0,100,0,5000,5000,0,0,1,27,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line"),
(@ENTRY,@SOURCETYPE,38,0,0,0,100,0,7000,7000,0,0,1,28,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script - Say Line");

-- Perry Gatner
SET @ENTRY := 1922801;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,15106,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Frostwolf Emissary"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,14990,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Defilers Emissary"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,22015,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Eye of the Storm Envoy"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,30567,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Strand of the Ancients Envoy"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,15105,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Warsong Emissary"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,34949,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 2 - Set Data 1 1 on Isle of Conquest Envoy");

-- Perry Gatner
SET @ENTRY := 1922802;
SET @SOURCETYPE := 9;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,15106,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Frostwolf Emissary"),
(@ENTRY,@SOURCETYPE,1,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,14990,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Defilers Emissary"),
(@ENTRY,@SOURCETYPE,2,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,22015,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Eye of the Storm Envoy"),
(@ENTRY,@SOURCETYPE,3,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,30567,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Strand of the Ancients Envoy"),
(@ENTRY,@SOURCETYPE,4,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,15105,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Warsong Emissary"),
(@ENTRY,@SOURCETYPE,5,0,0,0,100,0,0,0,0,0,45,2,2,0,0,0,0,19,34949,0,0,0.0,0.0,0.0,0.0,"Perry Gatner - Script 3 - Set Data 2 2 on Isle of Conquest Envoy");

SET @Guid := 11329;

DELETE FROM `creature`  WHERE `guid` IN(@GUID+0,@GUID+1,@GUID+2,@GUID+3) AND `id`=18152;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(@GUID+0, 18152, 530, 1, 1, 15397, 0, 1177.666, 8130.762, 19.62192, 1.151917, 120, 0, 0, 247, 0, 0, 0, 0, 0),  
(@GUID+1, 18152, 530, 1, 1, 15394, 0, 1178.132, 8130.465, 19.65684, 1.117011, 120, 0, 0, 247, 0, 0, 0, 0, 0),  
(@GUID+2, 18152, 530, 1, 1, 15393, 0, 1178.688, 8130.183, 19.68922, 1.082104, 120, 0, 0, 247, 0, 0, 0, 0, 0), 
(@GUID+3, 18152, 530, 1, 1, 15396, 0, 1179.359, 8129.974, 19.69083, 1.012291, 120, 0, 0, 247, 0, 0, 0, 0, 0); 

DELETE FROM `event_scripts` WHERE  `id`=11424 AND `delay`=3 AND `command`=10;
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES 
(11424, 3, 10, 19656, 10000, 0, 1176.53, 8130.83, 20.13, 1.86);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(1815200,1965602) AND `source_type`=9;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(-@GUID-0,-@GUID-1,-@GUID-2,-@GUID-3) AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` =19656 AND `source_type`=0 AND `id`=1;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(19656, 0, 1, 0, 11, 0, 100, 0, 0, 0, 0, 0, 80, 1965602, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Invisible Location Trigger - On Just Summoned - Run Script'),
(1965602, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 10, @GUID+0, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #1'),
(1965602, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 10, @GUID+1, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #2'),
(1965602, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 10, @GUID+2, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #3'),
(1965602, 9, 3, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 2, 2, 0, 0, 0, 0, 10, @GUID+3, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #4'),

(1965602, 9, 4, 0, 0, 0, 100, 0, 3000, 3000, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, @GUID+0, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #1'),
(1965602, 9, 5, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, @GUID+1, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #2'),
(1965602, 9, 6, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, @GUID+2, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #3'),
(1965602, 9, 7, 0, 0, 0, 100, 0, 0, 0, 0, 0, 45, 1, 1, 0, 0, 0, 0, 10, @GUID+3, 18152, 0, 0, 0, 0, 0, 'Invisible Location Trigger Script - Respawn Baby Murloc #4'),

(-@GUID-0, 0, 0, 0, 38, 0, 100, 0, 2, 2, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Set Visible'),
(-@GUID-1, 0, 0, 0, 38, 0, 100, 0, 2, 2, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Set Visible'),
(-@GUID-2, 0, 0, 0, 38, 0, 100, 0, 2, 2, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Set Visible'),
(-@GUID-3, 0, 0, 0, 38, 0, 100, 0, 2, 2, 0, 0, 47, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Set Visible'),
(-@GUID-0, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 1, 1815200, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Start WP'),
(-@GUID-1, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 1, 1815201, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Start WP'),
(-@GUID-2, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 1, 1815202, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Start WP'),
(-@GUID-3, 0, 1, 0, 38, 0, 100, 0, 1, 1, 0, 0, 53, 1, 1815203, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Data Set - Start WP'),
(-@GUID-0, 0, 2, 3, 34, 0, 100, 0, 0, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 5.375614, 'Baby Murloc - On Reached WP1 - Set Orientation'),
(-@GUID-1, 0, 2, 3, 34, 0, 100, 0, 0, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 4.886922, 'Baby Murloc - On Reached WP1 - Set Orientation'),
(-@GUID-2, 0, 2, 3, 34, 0, 100, 0, 0, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 3.159046, 'Baby Murloc - On Reached WP1 - Set Orientation'),
(-@GUID-3, 0, 2, 3, 34, 0, 100, 0, 0, 1, 0, 0, 66, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 2.9147, 'Baby Murloc - On Reached WP1 - Set Orientation'),
(-@GUID-0, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 1815200, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Run Script'),
(-@GUID-1, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 1815200, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Run Script'),
(-@GUID-2, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 1815200, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Run Script'),
(-@GUID-3, 0, 3, 0, 61, 0, 100, 0, 0, 0, 0, 0, 80, 1815200, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Run Script'),
(-@GUID-0, 0, 4, 5, 11, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Visible'),
(-@GUID-1, 0, 4, 5, 11, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Visible'),
(-@GUID-2, 0, 4, 5, 11, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Visible'),
(-@GUID-3, 0, 4, 5, 11, 0, 100, 0, 0, 0, 0, 0, 47, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Visible'),
(-@GUID-0, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Emote State'),
(-@GUID-1, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Emote State'),
(-@GUID-2, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Emote State'),
(-@GUID-3, 0, 5, 0, 61, 0, 100, 0, 0, 0, 0, 0, 17, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - On Respawn - Set Emote State'),

(1815200, 9, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 11, 32040, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - Script - Cast Scare Daggerfen'),
(1815200, 9, 1, 0, 0, 0, 100, 0, 0, 0, 0, 0, 17, 10, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - Script - Set Emote State'),
(1815200, 9, 2, 0, 0, 0, 100, 0, 0, 0, 0, 0, 41, 18000, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Baby Murloc - Script - Despawn');

DELETE FROM `waypoints` WHERE `entry` BETWEEN 1815200 AND 1815203;
INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(1815200, 1, 1169.526, 8146.214, 19.41322, 'Baby Murloc'),
(1815201, 1, 1184.131, 8162.72, 18.72033, 'Baby Murloc'),
(1815202, 1, 1205.028, 8157.705, 18.43147, 'Baby Murloc'),
(1815203, 1, 1204.707, 8140.139, 18.77224, 'Baby Murloc');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=22 AND  `SourceGroup`=2 AND `SourceEntry`=19656;

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=32040;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13, 1, 32040, 0, 0, 31, 0, 3, 18115, 0, 0, 0, 0, '', 'Scare Daggerfen targets Daggerfen Muckdweller'),
(13, 1, 32040, 0, 1, 31, 0, 3, 18116, 0, 0, 0, 0, '', 'Scare Daggerfen targets Daggerfen Assasin'),
(22, 2, 19656, 0, 0, 23, 1, 3640, 0, 0, 0, 0, 0, '', '');


UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry`=4880;

DELETE FROM `smart_scripts` WHERE `entryorguid`=4880  AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(488000,488001)  AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(4880,0,0,2,19,0,100,0,1270,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Quest Accept (Stinkys Escape - H) - Store Targetlist'),
(4880,0,1,2,19,0,100,0,1222,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Quest Accept (Stinkys Escape - A) - Store Targetlist'),
(4880,0,2,0,61,0,100,0,0,0,0,0,80,488000,2,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Link - Run Script'),
(4880,0,3,4,40,0,100,0,8,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP8 - Pause WP (3 Seconds)'),
(4880,0,4,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP8 - Say Line 1'),
(4880,0,5,6,40,0,100,0,12,0,0,0,54,3000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP12 - Pause WP (3 Seconds)'),
(4880,0,6,0,61,0,100,0,0,0,0,0,1,2,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP12 - Say Line 2'),
(4880,0,7,0,40,0,100,0,26,0,0,0,1,3,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP26 - Say Line 3'),
(4880,0,8,9,40,0,100,0,27,0,0,0,54,6000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached 27 - Pause WP (6 Seconds)'),
(4880,0,9,0,61,0,100,0,0,0,0,0,1,4,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached 27 - Say Line 4'),
(4880,0,10,11,40,0,100,0,28,0,0,0,54,6000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP28 - Pause WP (6 Seconds)'),
(4880,0,11,0,61,0,100,0,0,0,0,0,1,5,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached 28 - Say Line 5'),
(4880,0,12,13,40,0,100,0,29,0,0,0,54,6000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP29 - Pause WP (6 Seconds)'),
(4880,0,13,14,61,0,100,0,0,0,0,0,90,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached 29 - Set Bytes 1'),
(4880,0,14,27,61,0,100,0,0,0,0,0,1,6,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached 29 - Say Line 6'),
(4880,0,15,16,40,0,100,0,30,0,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP30 - Set Bytes 1'),
(4880,0,16,0,61,0,100,0,0,0,0,0,1,7,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP30 - Say Line 7'),
(4880,0,17,18,40,0,100,0,38,0,0,0,54,6000,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP38 - Pause WP (6 Seconds)'),
(4880,0,18,19,61,0,100,0,0,0,0,0,1,8,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP38 - Say Line 8'),
(4880,0,19,20,61,0,100,0,0,0,0,0,15,1270,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP38 - Complete Quest'),
(4880,0,20,21,61,0,100,0,0,0,0,0,15,1222,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP38 - Complete Quest'),
(4880,0,21,0,40,0,100,0,0,0,0,0,59,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP38 - Set Run On'),
(4880,0,22,23,40,0,100,0,40,0,0,0,1,9,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP40 - Say Line 9'),
(4880,0,23,0,61,0,100,0,40,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP40 - Despawn'),
(4880,0,24,26,6,0,100,0,0,0,0,0,6,1270,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Death - Fail Quest'),
(4880,0,25,0,61,0,100,0,0,0,0,0,6,1222,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - On Death - Fail Quest'),
(4880,0,26,0,0,0,100,0,1000,1000,30000,30000,1,10,0,0,0,0,0,12,1,0,0,0,0,0,0,'"Stinky" Ignatz - IC  - Say Line 10'),
(4880,0,27,0,61,0,100,0,0,0,0,0,70,300,0,0,0,0,0,14,11757,20939,0,0,0,0,0,'"Stinky" Ignatz - On Reached WP29 - Despawn Bogbean Plant'),
(4880,0,28,0,24,0,100,0,0,0,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - On Evade - Set Bytes 1'),
(488000,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Set NPC Flags'),
(488000,9,1,0,0,0,100,0,0,0,0,0,2,250,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Set Faction'),
(488000,9,2,0,0,0,100,0,0,0,0,0,91,8,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Set Bytes 1'),
(488000,9,3,0,0,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Set aggresive'),
(488000,9,4,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Say Line 0'),
(488000,9,5,0,0,0,100,0,0,0,0,0,53,0,4880,0,0,0,0,1,0,0,0,0,0,0,0,'"Stinky" Ignatz - Script - Start WP');

DELETE FROM `waypoints` WHERE `entry`=4880;
DELETE FROM `script_waypoint` WHERE `entry`=4880;

INSERT INTO `waypoints` (`entry`, `pointid`, `position_x`, `position_y`, `position_z`, `point_comment`) VALUES 
(4880, 1, -2646.43, -3436.07, 35.3732, '"Stinky" Ignatz'),
(4880, 2, -2650.83, -3440.15, 35.1381, '"Stinky" Ignatz'),
(4880, 3, -2662.31, -3447.67, 35.1089, '"Stinky" Ignatz'),
(4880, 4, -2680.48, -3454.6, 34.6538, '"Stinky" Ignatz'),
(4880, 5, -2701.02, -3457.44, 34.2691, '"Stinky" Ignatz'),
(4880, 6, -2724.06, -3458.64, 33.6735, '"Stinky" Ignatz'),
(4880, 7, -2745.01, -3459.28, 32.5346, '"Stinky" Ignatz'),
(4880, 8, -2759.42, -3464.78, 32.7143, '"Stinky" Ignatz'), -- 3000
(4880, 9, -2763.63, -3471.51, 33.5388, '"Stinky" Ignatz'),
(4880, 10, -2771.79, -3480.89, 33.2553, '"Stinky" Ignatz'),
(4880, 11, -2780.66, -3488.76, 31.875, '"Stinky" Ignatz'),
(4880, 12, -2796.14, -3489.01, 30.8585, '"Stinky" Ignatz'), -- 3000
(4880, 13, -2792.12, -3495.97, 30.7324, '"Stinky" Ignatz'),
(4880, 14, -2789.06, -3502.37, 30.6704, '"Stinky" Ignatz'),
(4880, 15, -2787.72, -3515.01, 31.1176, '"Stinky" Ignatz'),
(4880, 16, -2790.84, -3523.31, 30.5733, '"Stinky" Ignatz'),
(4880, 17, -2796.59, -3520.62, 29.9187, '"Stinky" Ignatz'),
(4880, 18, -2798.56, -3518.91, 30.3887, '"Stinky" Ignatz'),
(4880, 19, -2801.47, -3516.75, 30.1915, '"Stinky" Ignatz'),
(4880, 20, -2804.36, -3513.9, 29.5508, '"Stinky" Ignatz'),
(4880, 21, -2807.98, -3518, 29.9488, '"Stinky" Ignatz'),
(4880, 22, -2815.68, -3521.74, 29.7723, '"Stinky" Ignatz'),
(4880, 23, -2823.39, -3526.23, 31.7194, '"Stinky" Ignatz'),
(4880, 24, -2836.11, -3544.7, 32.4939, '"Stinky" Ignatz'),
(4880, 25, -2830.39, -3568.86, 30.4104, '"Stinky" Ignatz'),
(4880, 26, -2824.84, -3569.52, 31.2811, '"Stinky" Ignatz'),
(4880, 27, -2818.66, -3567.8, 30.9204, '"Stinky" Ignatz'), -- 6000
(4880, 28, -2817.66, -3568.94, 30.4312, '"Stinky" Ignatz'), -- 6000
(4880, 29, -2820.39, -3592.22, 30.7163, '"Stinky" Ignatz'), -- 6000
(4880, 30, -2820.77, -3592.5, 30.8861, '"Stinky" Ignatz'),
(4880, 31, -2829.91, -3588.73, 30.6831, '"Stinky" Ignatz'),
(4880, 32, -2842.32, -3577.5, 36.8489, '"Stinky" Ignatz'),
(4880, 33, -2851.18, -3567.58, 38.5159, '"Stinky" Ignatz'),
(4880, 34, -2865.55, -3551.58, 41.439, '"Stinky" Ignatz'),
(4880, 35, -2871.23, -3548.15, 40.7614, '"Stinky" Ignatz'),
(4880, 36, -2877.84, -3544.15, 38.6702, '"Stinky" Ignatz'),
(4880, 37, -2890.39, -3542.39, 34.3144, '"Stinky" Ignatz'),
(4880, 38, -2898.73, -3543.64, 34.32, '"Stinky" Ignatz'), -- 6000
(4880, 39, -2910.06, -3568.96, 34.25, '"Stinky" Ignatz'),
(4880, 40, -2932.51, -3584.62, 37.2385, '"Stinky" Ignatz');

DELETE FROM `creature_text` WHERE `entry`=4880;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(4880, 0, 0, 'Ok, let''s get started.', 12, 0, 100, 0, 0, 0, 1610, '"Stinky" Ignatz'),
(4880, 1, 0, 'Now let''s look for the herb.', 12, 0, 100, 0, 0, 0, 1611, '"Stinky" Ignatz'),
(4880, 2, 0, 'Nope, not here...', 12, 0, 100, 0, 0, 0, 1612, '"Stinky" Ignatz'),
(4880, 3, 0, 'There must be one around here somewhere...', 12, 0, 100, 0, 0, 0, 1613, '"Stinky" Ignatz'),
(4880, 4, 0, 'Ah, there''s one!', 12, 0, 100, 0, 0, 0, 1614, '"Stinky" Ignatz'),
(4880, 5, 0, 'Come, $n!  Let''s go over there and collect it!', 12, 0, 100, 0, 0, 0, 1615, '"Stinky" Ignatz'),
(4880, 6, 0, '%s picks the herb from the ground.', 16, 0, 100, 0, 0, 0, 1616, '"Stinky" Ignatz'),
(4880, 7, 0, 'Ok, now let''s get out of here!', 12, 0, 100, 0, 0, 0, 1617, '"Stinky" Ignatz'),
(4880, 8, 0, 'I can make it from here.  Thanks, $n!  And talk to my employer about a reward!', 12, 0, 100, 0, 0, 0, 1618, '"Stinky" Ignatz'),
(4880, 9, 0, '%s disappears back into the swamp.', 16, 0, 100, 0, 0, 0, 1619, '"Stinky" Ignatz'),
(4880, 10, 0, 'Help! I''m under attack!', 12, 0, 100, 0, 0, 0, 1629, '"Stinky" Ignatz'),
(4880, 10, 1, 'Help!  The beast is on me!', 12, 0, 100, 0, 0, 0, 1630, '"Stinky" Ignatz');

DELETE FROM `gossip_menu` WHERE `entry`=10060;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES 
(10060, 13978);

DELETE FROM `gossip_menu_option` WHERE `menu_id`=10060;

INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES 
(10060, 0, 0, "Let\'s kill this... thing... and get this over with.", 32118, 1, 1, 0, 0, 0, 0, "", 0);

UPDATE creature_template_addon SET auras="58949" WHERE entry=31306;

DELETE FROM `creature_template_addon` WHERE `entry`=31301;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `auras`) VALUES
(31301, 0, 0x0, 0x1, '34427'); -- 31301 - 34427

UPDATE `creature_template` SET `unit_flags`=768 WHERE  `entry`=31301;

UPDATE `creature_template` SET `ainame`='SmartAI', `scriptname`='' WHERE `entry` IN(30698,31314,31306,31428,31301);

DELETE FROM `smart_scripts` WHERE `entryorguid` IN(30698,31314,31306,31428,31301)  AND `source_type`=0;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN(3130100)  AND `source_type`=9;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(30698,0,0,1,38,0,100,0,1,1,0,0,19,768,0,0,0,0,0,1,0,0,0,0,0,0,0,'Morbidus - On Data Set 1 1 - Set Unit Flags'),
(30698,0,1,2,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Morbidus - On Data Set 1 1 - Set Hostile'),
(30698,0,2,3,61,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,31306,0,0,0,0,0,0,'Morbidus - On Data Set 1 1 - Set Data 1 1 on Margrave Dhakar'),
(30698,0,3,4,61,0,100,0,0,0,0,0,45,1,1,0,0,0,0,19,31428,0,0,0,0,0,0,'Morbidus - On Data Set 1 1 - Set Data 1 1 on Crusader Olakin Sainrith'),
(30698,0,4,0,61,0,100,0,0,0,0,0,45,1,1,0,0,0,0,9,31314,0,200,0,0,0,0,'Morbidus - On Data Set 1 1 - Set Data 1 1 on Ebon Blade Veteran'),
(30698,0,5,6,25,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Morbidus - On Reset - Set Passive'),
(30698,0,6,0,61,0,100,0,0,0,0,0,18,768,0,0,0,0,0,1,0,0,0,0,0,0,0,'Morbidus - On Reset - Set Unit Flags'),
(30698,0,7,0,6,0,100,0,0,0,0,0,33,30698,0,0,0,0,0,24,0,0,0,0,0,0,0,'Morbidus - On Death - Kill Credit'),
(31306,0,0,1,62,0,100,0,10060,0,0,0,64,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'Margrave Dhakar - On Gossip Select - Store Targetlist'),
(31306,0,1,2,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Margrave Dhakar - On Gossip Select - Close Gossip'),
(31306,0,2,3,61,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Margrave Dhakar - On Gossip Select - Set NPC Flags'),
(31306,0,3,4,61,0,100,0,0,0,0,0,12,31301,1,600000,0,0,0,8,0,0,0,6858.596, 3580.5, 736.7512, 5.67232,'Margrave Dhakar - On Gossip Select - Summon The Lich King'),
(31306,0,4,0,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0, 0, 0, 0,'Margrave Dhakar - On Gossip Select - Say Line 0'),
(31306,0,5,6,38,0,100,0,1,1,0,0,8,2,0,0,0,0,0,1,0,0,0,0, 0, 0, 0,'Margrave Dhakar - On Data Set 1 1 - Set Hostile'),
(31306,0,6,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,30698,0,0,0,0,0,0,'Margrave Dhakar - On Data Set 1 1 - Attack Morbidus'),
(31306,0,7,8,7,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Margrave Dhakar - On Evade - Set Passive'),
(31306,0,8,0,61,0,100,0,0,0,0,0,81,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Margrave Dhakar - On Evade - Set NPC Flags'),
(31301,0,0,0,11,0,100,0,0,0,0,0,80,3130100,2,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - On Just Summoned - Run Script'),
(31314,0,0,1,38,0,100,0,1,1,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Ebon Blade Veteran - On Data Set 1 1 - Set Hostile'),
(31314,0,1,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,30698,0,0,0,0,0,0,'Ebon Blade Veteran - On Data Set 1 1 - Attack Morbidus'),
(31314,0,2,0,7,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Ebon Blade Veteran - On Evade - Set Passive'),
(31428,0,0,1,38,0,100,0,1,1,0,0,2,1770,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crusader Olakin Sainrith - On Data Set 1 1 - Set Faction'),
(31428,0,1,2,61,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crusader Olakin Sainrith - On Data Set 1 1 - Set Hostile'),
(31428,0,2,0,61,0,100,0,0,0,0,0,49,0,0,0,0,0,0,19,30698,0,0,0,0,0,0,'Crusader Olakin Sainrith - On Data Set 1 1 - Attack Morbidus'),
(31428,0,3,4,7,0,100,0,1,1,0,0,2,2070,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crusader Olakin Sainrith - On Evade - Set Faction'),
(31428,0,4,0,61,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Crusader Olakin Sainrith - On Evade - Set Passive'),
(3130100,9,0,0,0,0,100,0,100,100,0,0,11,34427,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Cast Ethereal Teleport'),
(3130100,9,1,0,0,0,100,0,5000,5000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Say Line 0'),
(3130100,9,2,0,0,0,100,0,1000,1000,0,0,11,53274,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Cast Icebound Visage'),
(3130100,9,3,0,0,0,100,0,4000,4000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Say Line 1'),
(3130100,9,4,0,0,0,100,0,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Say Line 2'),
(3130100,9,5,0,0,0,100,0,5000,5000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Say Line 3'),
(3130100,9,6,0,0,0,100,0,5000,5000,0,0,1,4,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Say Line 4'),
(3130100,9,7,0,0,0,100,0,3000,3000,0,0,1,0,0,0,0,0,0,19,31428,0,0,0,0,0,0,'The Lich King - Script - Say Line 0 (Crusader Olakin Sainrith)'),
(3130100,9,8,0,0,0,100,0,2000,2000,0,0,45,1,1,0,0,0,0,19,30698,0,0,0,0,0,0,'The Lich King - Script - Set Data 1 1 on Morbidus'),
(3130100,9,9,0,0,0,100,0,0,0,0,0,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'The Lich King - Script - Despawn');

UPDATE `smart_scripts` SET `event_type`=7 WHERE  `entryorguid`=4880 AND `source_type`=0 AND `id`=28 AND `link`=0;

DELETE FROM `conditions`  WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=10060;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorType`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, 10060, 0, 0, 0, 29, 0, 30698, 200, 0, 0, 0, 0, '', 'Margrave Dhakar only show gossip if Morbidus near'),
(15, 10060, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, '', 'Margrave Dhakar only show gossip if Morbidus is alive'),
(15, 10060, 0, 0, 0, 9, 0, 13235, 0, 0, 0, 0, 0, '', 'Margrave Dhakar only show gossip if player has The Flesh Giant Champion taken');





