

DELETE FROM `creature_text` WHERE `entry`=68 AND `groupid` BETWEEN 2 AND 5;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(68, 2, 0, "%s throws a rotten apple at $n.", 16, 0, 100, 0, 0, 0, 31671, "Stormwind City Guard"),
(68, 3, 0, "%s throws rotten banana on $n.", 16, 0, 100, 0, 0, 0, 31672, "Stormwind City Guard"),
(68, 4, 0, "%s spits on $n.", 16, 0, 100, 0, 0, 0, 31673, "Stormwind City Guard"),
(68, 5, 0, "Monster!", 12, 0, 100, 0, 0, 0, 31662, "Stormwind City Guard"),
(68, 5, 1, "Murderer!", 12, 0, 100, 0, 0, 0, 31679, "Stormwind City Guard"),
(68, 5, 2, "GET A ROPE!", 12, 0, 100, 0, 0, 0, 31669, "Stormwind City Guard"),
(68, 5, 3, "How dare you set foot in our city!", 12, 0, 100, 0, 0, 0, 31684, "Stormwind City Guard"),
(68, 5, 4, "You disgust me.", 12, 0, 100, 0, 0, 0, 31680, "Stormwind City Guard"),
(68, 5, 5, "Looks like we\'re going to have ourselves an execution.", 12, 0, 100, 0, 0, 0, 31682, "Stormwind City Guard"),
(68, 5, 6, "Traitorous dog.", 12, 0, 100, 0, 0, 0, 31665, "Stormwind City Guard"),
(68, 5, 7, "My family was wiped out by the Scourge! MONSTER!", 12, 0, 100, 0, 0, 0, 31667, "Stormwind City Guard");

DELETE FROM `creature_text` WHERE `entry`=1756 AND `groupid` BETWEEN 2 AND 5;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(1756, 2, 0, "%s throws a rotten apple at $n.", 16, 0, 100, 0, 0, 0, 31671, "Stormwind Royal Guard"),
(1756, 3, 0, "%s throws rotten banana on $n.", 16, 0, 100, 0, 0, 0, 31672, "Stormwind Royal Guard"),
(1756, 4, 0, "%s spits on $n.", 16, 0, 100, 0, 0, 0, 31673, "Stormwind Royal Guard"),
(1756, 5, 0, "Monster!", 12, 0, 100, 0, 0, 0, 31662, "Stormwind Royal Guard"),
(1756, 5, 1, "Murderer!", 12, 0, 100, 0, 0, 0, 31679, "Stormwind Royal Guard"),
(1756, 5, 2, "GET A ROPE!", 12, 0, 100, 0, 0, 0, 31669, "Stormwind Royal Guard"),
(1756, 5, 3, "How dare you set foot in our city!", 12, 0, 100, 0, 0, 0, 31684, "Stormwind Royal Guard"),
(1756, 5, 4, "You disgust me.", 12, 0, 100, 0, 0, 0, 31680, "Stormwind Royal Guard"),
(1756, 5, 5, "Looks like we\'re going to have ourselves an execution.", 12, 0, 100, 0, 0, 0, 31682, "Stormwind Royal Guard"),
(1756, 5, 6, "Traitorous dog.", 12, 0, 100, 0, 0, 0, 31665, "Stormwind Royal Guard"),
(1756, 5, 7, "My family was wiped out by the Scourge! MONSTER!", 12, 0, 100, 0, 0, 0, 31667, "Stormwind Royal Guard");

DELETE FROM `creature_text` WHERE `entry`=1976 AND `groupid` BETWEEN 2 AND 6;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(1976, 2, 0, "%s throws a rotten apple at $n.", 16, 0, 100, 0, 0, 0, 31671, "Stormwind City Patroller"),
(1976, 3, 0, "%s throws rotten banana on $n.", 16, 0, 100, 0, 0, 0, 31672, "Stormwind City Patroller"),
(1976, 4, 0, "%s spits on $n.", 16, 0, 100, 0, 0, 0, 31673, "Stormwind City Patroller"),
(1976, 5, 0, "Monster!", 12, 0, 100, 0, 0, 0, 31662, "Stormwind City Patroller"),
(1976, 5, 1, "Murderer!", 12, 0, 100, 0, 0, 0, 31679, "Stormwind City Patroller"),
(1976, 5, 2, "GET A ROPE!", 12, 0, 100, 0, 0, 0, 31669, "Stormwind City Patroller"),
(1976, 5, 3, "How dare you set foot in our city!", 12, 0, 100, 0, 0, 0, 31684, "Stormwind City Patroller"),
(1976, 5, 4, "You disgust me.", 12, 0, 100, 0, 0, 0, 31680, "Stormwind City Patroller"),
(1976, 5, 5, "Looks like we\'re going to have ourselves an execution.", 12, 0, 100, 0, 0, 0, 31682, "Stormwind City Patroller"),
(1976, 5, 6, "Traitorous dog.", 12, 0, 100, 0, 0, 0, 31665, "Stormwind City Patroller"),
(1976, 5, 7, "My family was wiped out by the Scourge! MONSTER!", 12, 0, 100, 0, 0, 0, 31667, "Stormwind City Patroller"),
(1976, 6, 0, "Taste blade, mongrel!", 12, 0, 100, 0, 0, 0, 10950, "SAY_GUARD_SIL_AGGRO1"),
(1976, 6, 1, "Please tell me that you didn't just do what I think you just did. Please tell me that I'm not going to have to hurt you...", 12, 0, 100, 0, 0, 0, 10951, "SAY_GUARD_SIL_AGGRO2"),
(1976, 6, 2, "As if we don't have enough problems, you go and create more!", 12, 0, 100, 0, 0, 0, 10953, "SAY_GUARD_SIL_AGGRO3");

DELETE FROM `creature_text` WHERE `entry`=14304 AND `groupid` BETWEEN 2 AND 5;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(14304, 2, 0, "%s throws a rotten apple at $n.", 16, 0, 100, 0, 0, 0, 31671, "Kor\'kron Elite"),
(14304, 3, 0, "%s throws rotten banana on $n.", 16, 0, 100, 0, 0, 0, 31672, "Kor\'kron Elite"),
(14304, 4, 0, "%s spits on $n.", 16, 0, 100, 0, 0, 0, 31673, "Kor\'kron Elite"),
(14304, 5, 0, "Monster!", 12, 0, 100, 0, 0, 0, 31662, "Kor\'kron Elite"),
(14304, 5, 1, "Murderer!", 12, 0, 100, 0, 0, 0, 31679, "Kor\'kron Elite"),
(14304, 5, 2, "GET A ROPE!", 12, 0, 100, 0, 0, 0, 31669, "Kor\'kron Elite"),
(14304, 5, 3, "How dare you set foot in our city!", 12, 0, 100, 0, 0, 0, 31684, "Kor\'kron Elite"),
(14304, 5, 4, "You disgust me.", 12, 0, 100, 0, 0, 0, 31680, "Kor\'kron Elite"),
(14304, 5, 5, "Looks like we\'re going to have ourselves an execution.", 12, 0, 100, 0, 0, 0, 31682, "Kor\'kron Elite"),
(14304, 5, 6, "Traitorous dog.", 12, 0, 100, 0, 0, 0, 31665, "Kor\'kron Elite"),
(14304, 5, 7, "My family was wiped out by the Scourge! MONSTER!", 12, 0, 100, 0, 0, 0, 31667, "Kor\'kron Elite");

update creature_template set AIName="", ScriptName="guard_generic" where entry in (68, 1756, 1976, 14304);









