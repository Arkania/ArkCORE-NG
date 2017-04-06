

UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_mekka_torque_42317' WHERE `entry` = 42317;
UPDATE `creature_template` SET `AIName` = '' WHERE `entry` = 42419;
UPDATE `creature_template` SET `modelid1` = 31878, `modelid2` = 0, `AIName` = '' WHERE `entry` = 42452;
UPDATE `creature_template` SET `ScriptName` = 'npc_engineer_grindspark_42553' WHERE `entry` = 42553;
UPDATE `creature_template` SET `ScriptName` = 'npc_toxic_pool_42563' WHERE `entry` = 42563;
UPDATE `creature_template` SET `ScriptName` = 'npc_multi_bot_42598' WHERE `entry` = 42598;
UPDATE `creature_template` SET `ScriptName` = 'npc_mekka_torque_42849' WHERE `entry` = 42849;
UPDATE `creature_template` SET `ScriptName` = 'npc_nevin_twistwrench_45966' WHERE `entry` = 45966;
UPDATE `creature_template` SET `modelid1` = 28016, `InhabitType` = 4, `HoverHeight` = 0 WHERE `entry` = 46165;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_gnomeregan_torben_46293' WHERE `entry` = 46293;
UPDATE `creature_template` SET `npcflag` = 0, `AIName` = 'SmartAI' WHERE `entry` = 46363;
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 46447;
UPDATE `creature_template` SET `ScriptName` = 'npc_carvo_blastbolt_47250' WHERE `entry` = 47250;

DELETE FROM `creature_text` WHERE `entry` = 42553;
DELETE FROM `creature_text` WHERE `entry` = 42598;
DELETE FROM `creature_text` WHERE `entry` = 42645;
DELETE FROM `creature_text` WHERE `entry` = 46185;
DELETE FROM `creature_text` WHERE `entry` = 46230;
DELETE FROM `creature_text` WHERE `entry` = 47836;

INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES
(42553, 0, 0, 'Time to put the finishing touches on my bot.', 12, 0, 100, 0, 0, 0, '', 42947),
(42553, 1, 0, 'At last, it''s finished.', 12, 0, 100, 0, 0, 0, '', 42948),
(42553, 2, 0, 'Arise my, uh... what shall I call you? How about ''multi-bot''? Arise, my multi-bot!', 12, 0, 100, 0, 0, 0, '', 42949),
(42553, 3, 0, 'Uh... a couple more tweaks should do it, I think...', 12, 0, 100, 0, 0, 0, '', 42950),

(42598, 0, 0, 'Initiating cleanup ... ...', 12, 0, 100, 0, 0, 0, '', 42476),

(42645, 0, 2, 'Thank you for breaking me out of here!', 12, 0, 100, 0, 0, 0, NULL, 42579),
(42645, 0, 5, "I don't ever want to smell unwashed trogg again!", 12, 0, 100, 0, 0, 0, NULL, 42580),
(42645, 0, 3, 'Thanks. Now, let''s blow up that cave!', 12, 0, 100, 0, 0, 0, NULL, 42581),
(42645, 0, 4, 'You have no idea how happy I am to see you!', 12, 0, 100, 0, 0, 0, NULL, 42582),
(42645, 0, 0, 'Finally, someone who''s not a trogg!', 12, 0, 100, 0, 0, 0, NULL, 42583),
(42645, 0, 1, 'I''m free! I''m really free!', 12, 0, 100, 0, 0, 0, NULL, 42584),

(46185, 0, 0, 'Commencing decontamination sequence...', 12, 0, 100, 0, 0, 0, NULL, 46323),
(46185, 1, 0, 'Decontamination complete. Standby for delivery.', 12, 0, 100, 0, 0, 0, NULL, 46324),
(46185, 2, 0, 'Warning, system overload. Malfunction imminent!', 12, 0, 100, 0, 0, 0, NULL, 46325),

(46230, 0, 0, 'Ugh! Not this again! I''m asking for a new station next expedition...', 12, 0, 100, 0, 0, 0, NULL, 46342),

(47836, 0, 0, 'You can follow me to the Loading Room, $N', 12, 0, 100, 0, 0, 0, '', 48091);

DELETE FROM `gameobject` WHERE `id` = 204042 AND `map` = 0 AND `zoneId` = 1 AND `areaId` = 135;
DELETE FROM `gameobject` WHERE `id` = 204047 AND `map` = 0 AND `zoneId` = 1 AND `areaId` = 135;
DELETE FROM `gameobject` WHERE `id` = 204021 AND `map` = 0 AND `zoneId` = 1 AND `areaId` = 135;

INSERT INTO `gameobject` (`id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseId`, `phaseGroup`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES 
(204042, 0, 1, 135, 1, 0, 0, -5523.85, 711.411, 377.097, 0.0840471, 0, 0, 0.0420112, 0.999117, 300, 0, 1),
(204047, 0, 1, 135, 1, 0, 0, -5520, 693, 378, 1, 0, 0, 0, 1, 120, 255, 0),
(204021, 0, 1, 135, 1, 0, 0, -5530, 520, 388, 3, 0, 0, 0, 1, 120, 255, 1),
(204021, 0, 1, 135, 1, 0, 0, -5529, 518, 389, 3, 0, 0, 0, 1, 120, 255, 1),
(204047, 0, 1, 135, 1, 0, 0, -5520, 693, 378, 1, 0, 0, 0, 1, 120, 255, 1),
(204021, 0, 1, 135, 1, 0, 0, -5527, 697, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5528, 696, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5527, 696, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5527, 696, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5528, 695, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5529, 696, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5528, 697, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5525, 699, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5524, 699, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5524, 699, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5523, 700, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5522, 700, 375, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5524, 701, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5523, 702, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5524, 701, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5519, 703, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5520, 703, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5520, 704, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5521, 702, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5522, 702, 376, 5, 0, 0, 0, 0, 300, 0, 1),
(204021, 0, 1, 135, 1, 0, 0, -5522, 701, 376, 5, 0, 0, 0, 0, 300, 0, 1);

UPDATE `gameobject_template` SET `displayId` = 230, `size` = 0.7 WHERE `entry` = 203862;
UPDATE `gameobject_template` SET `displayId` = 9796 WHERE `entry` = 203975;
UPDATE `gameobject_template` SET `displayId` = 10094, `size` = 1.65, `ScriptName` = 'go_makeshift_cage_204019' WHERE `entry` = 204019;

DELETE FROM `gossip_menu_option` WHERE `menu_id` = 12104;
DELETE FROM `gossip_menu_option` WHERE `menu_id` = 12634;

INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `OptionBroadcastTextID`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `BoxBroadcastTextID`) VALUES
(12104, 0, 0, 'Send me to the Surface, Torben ', 46360, 1, 1, 0, 0, 0, 0, 0, NULL, 0),
(12634, 0, 0, 'I need a new GS-9x Multibot', 50617, 1, 1, 0, 0, 0, 0, 0, NULL, 0);

UPDATE `locales_creature_text` SET `text_loc3` = 'Wir versammelten eine mächtige Truppe, besiegten Thermadrahts Diener und erkämpften uns unserenWeg in die Stadt. Doch der Eindringling hatte ein letztes Ass im Ärmel....' WHERE `entry` = 42317 AND `groupid` = 0 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Schaut Euch den Holotisch an. Ich möchte Euch ein wenig von Operation: Gnomeregan zeigen.' WHERE `entry` = 42317 AND `groupid` = 1 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Es ist zu still. Wo sind Thermadrahts Verteidiger?' WHERE `entry` = 42419 AND `groupid` = 0 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'ES IST EINE FALLE! Das ist ein voll funktionstüchtiger Verstrahler!' WHERE `entry` = 42419 AND `groupid` = 1 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Zehn Minuten? Genug Zeit, um das Ding zu entschärfen.' WHERE `entry` = 42419 AND `groupid` = 2 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Hinkels, das surrende bronzene Dingsda und etwas frisches Quellwasser. Raddreh, den schmutzigen Troggstoff und eine Handvoll Kupferbolzen...' WHERE `entry` = 42419 AND `groupid` = 3 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Uh-oh! Wir müssen hier raus! Lapforge, beamt uns zurück, schnell!' WHERE `entry` = 42419 AND `groupid` = 4 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Nein! Nein, nein, NEIN!!! Ihr dürft nicht in mein Reich, Thronräuber! ICH LASSE DAS NICHT ZU!' WHERE `entry` = 42423 AND `groupid` = 0 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Aktiviert das ultimative Nuklearschutzsystem.' WHERE `entry` = 42423 AND `groupid` = 1 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = '... DESINTEGRIERT SIE ALLE!' WHERE `entry` = 42423 AND `groupid` = 2 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'ZEHN MINUTEN?! Du hast die Werkseinstellung beibehalten? Gib mir die Steuerung, du Idiot!' WHERE `entry` = 42423 AND `groupid` = 3 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = 'Verstrahler 3000 aktiviert. Achtung. Notfall. Sie haben jetzt zehn Minuten, um den minimalen Sicherheitsabstand zu erreichen.' WHERE `entry` = 42452 AND `groupid` = 0 AND `id` = 0;
UPDATE `locales_creature_text` SET `text_loc3` = '*BIEP* Achtung. Notfall. Sie haben jetzt zehn Sekunden, um den minimalen Sicherheitsabstand zu erreichen.' WHERE `entry` = 42452 AND `groupid` = 1 AND `id` = 0;

DELETE FROM `locales_creature_text` WHERE `entry` = 42553;
DELETE FROM `locales_creature_text` WHERE `entry` = 42598;
DELETE FROM `locales_creature_text` WHERE `entry` = 42645;
DELETE FROM `locales_creature_text` WHERE `entry` = 46185;
DELETE FROM `locales_creature_text` WHERE `entry` = 46230;
DELETE FROM `locales_creature_text` WHERE `entry` = 47836;

INSERT INTO `locales_creature_text` (`entry`, `groupid`, `id`, `text_loc1`, `text_loc2`, `text_loc3`, `text_loc4`, `text_loc5`, `text_loc6`, `text_loc7`, `text_loc8`) VALUES
(42553, 0, 0, NULL, NULL, 'Zeit, die letzten Kniffe an meinem Bot anzubringen.', NULL, NULL, NULL, NULL, NULL),
(42553, 1, 0, NULL, NULL, 'Endlich ist es geschafft.', NULL, NULL, NULL, NULL, NULL),
(42553, 2, 0, NULL, NULL, 'Erhebe dich, mein... äh wie soll ich dich nennen? Wie wär''s mit `Multibot`? Erhebe dich, mein Multibot!', NULL, NULL, NULL, NULL, NULL),
(42553, 3, 0, NULL, NULL, 'Oh... noch ein paar Feinabstimmungen und es ist vollbracht, schätze ich...', NULL, NULL, NULL, NULL, NULL),
(42598, 0, 0, NULL, NULL, 'Beginn der Säuberungsaktion...', NULL, NULL, NULL, NULL, NULL),
(42645, 0, 0, NULL, NULL, 'Endlich, jemand der kein Trogg ist!', NULL, NULL, NULL, NULL, NULL),
(42645, 0, 1, NULL, NULL, 'Ich bin frei! Ich bin wirklich frei!', NULL, NULL, NULL, NULL, NULL),
(42645, 0, 2, NULL, NULL, 'Ich will nie mehr den Geruch ungewaschener Troggs in der Nase haben!', NULL, NULL, NULL, NULL, NULL),
(42645, 0, 3, NULL, NULL, 'Danke. Lasst uns jetzt die Höhle in die Luft sprengen!', NULL, NULL, NULL, NULL, NULL),
(42645, 0, 4, NULL, NULL, 'Ihr habt ja keine Ahnung wie froh Ich bin euch zu sehen.', NULL, NULL, NULL, NULL, NULL),
(46185, 0, 0, NULL, NULL, 'Leite Entseuchungssequenz ein...', NULL, NULL, NULL, NULL, NULL),
(46185, 0, 1, NULL, NULL, 'Entseuchung abgeschlossen. Warte auf die Lieferung.', NULL, NULL, NULL, NULL, NULL),
(46185, 0, 2, NULL, NULL, 'Warnung. System überladen. Fehlfunktion steht bevor!', NULL, NULL, NULL, NULL, NULL),
(46230, 0, 0, NULL, NULL, 'Ugh! Nicht schon wieder! Ich bitte bei der nächsten Expedition um eine andere Station...', NULL, NULL, NULL, NULL, NULL);

DELETE FROM `locales_gossip_menu_option` WHERE `menu_id` = 12104;
DELETE FROM `locales_gossip_menu_option` WHERE `menu_id` = 12634;

INSERT INTO `locales_gossip_menu_option` (`menu_id`, `id`, `option_text_loc1`, `option_text_loc2`, `option_text_loc3`, `option_text_loc4`, `option_text_loc5`, `option_text_loc6`, `option_text_loc7`, `option_text_loc8`, `box_text_loc1`, `box_text_loc2`, `box_text_loc3`, `box_text_loc4`, `box_text_loc5`, `box_text_loc6`, `box_text_loc7`, `box_text_loc8`) VALUES
(12104, 0, NULL, NULL, 'Bringt mich zur Oberfläche, Torben', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL),
(12634, 0, NULL, NULL, 'Ich brauch eine neuen GS-9x Multibot', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

UPDATE `quest_template` SET `PrevQuestId` = 27674, `RewardItemId1` = 59042, `RewardItemCount1` = 1 WHERE `Id` = 26197;
UPDATE `quest_template` SET `PrevQuestId` = 27674, `RewardItemId1` = 59040, `RewardItemCount1` = 1 WHERE `Id` = 26199;
UPDATE `quest_template` SET `PrevQuestId` = 27674, `RewardItemId1` = 59041, `RewardItemCount1` = 1 WHERE `Id` = 26202;
UPDATE `quest_template` SET `Method` = 2, `ZoneOrSort` = 801, `PrevQuestId` = 27674, `Flags` = 1572864, `RewardItemId1` = 59039, `RewardItemCount1` = 1 WHERE `Id` = 26203;
UPDATE `quest_template` SET `QuestGiverPortrait` = 0 WHERE `Id` = 26205;
UPDATE `quest_template` SET `PrevQuestId` = 27674, `RewardChoiceItemId1` = 59043, `RewardChoiceItemId2` = 59041, `RewardChoiceItemCount1` = 1, `RewardChoiceItemCount2` = 1 WHERE `Id` = 26206;
UPDATE `quest_template` SET `Method` = 2, `Flags` = 0 WHERE `Id` = 26208;
UPDATE `quest_template` SET `Level` = 3, `MinLevel` = 2, `ExclusiveGroup` = -26284 WHERE `Id` = 26284;
UPDATE `quest_template` SET `ExclusiveGroup` = -26284 WHERE `Id` = 26285;
UPDATE `quest_template` SET `RequiredNpcOrGo1` = -204042, `RequiredNpcOrGoCount1` = 1, `ObjectiveText2` = 'Kill Boss Bruggor' WHERE `Id` = 26318;
UPDATE `quest_template` SET `Method` = 2, `Level` = 2, `MinLevel` = 1 WHERE `Id` = 27635;
UPDATE `quest_template` SET `PrevQuestId` = 27635 WHERE `Id` = 27674;
UPDATE `quest_template` SET `PrevQuestId` = 27670 WHERE `Id` = 28167;

DELETE FROM `smart_scripts` WHERE `entryorguid` = 46363;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 46447;
DELETE FROM `smart_scripts` WHERE `entryorguid` = 46293;

INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(46363, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 80653, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Irradiation Aura'),
(46447, 0, 0, 0, 11, 0, 100, 0, 0, 0, 0, 0, 11, 80653, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Irradiation Aura');

DELETE FROM `waypoint_data` WHERE `id` = 15459904;

INSERT INTO `waypoint_data` (`id`, `point`, `position_x`, `position_y`, `position_z`, `orientation`, `delay`, `move_type`, `action`, `action_chance`, `wpguid`) VALUES
(15459904, 1, -4981.25, 780.992, 288.485, 0, 2000, 1, 0, 100, 0),
(15459904, 2, -4989.39, 779.806, 288.485, 0, 0, 1, 0, 100, 0),
(15459904, 3, -5002.69, 769.878, 288.485, 0, 0, 1, 0, 100, 0),
(15459904, 4, -5004.79, 770.036, 287.237, 0, 0, 1, 0, 100, 0),
(15459904, 5, -5031.01, 772.175, 283.101, 0, 0, 1, 0, 100, 0),
(15459904, 6, -5105.9, 775.347, 283.315, 0, 0, 1, 0, 100, 0),
(15459904, 7, -5111.33, 773.41, 287.398, 0, 0, 1, 0, 100, 0),
(15459904, 8, -5133.34, 763.884, 287.373, 0, 0, 1, 0, 100, 0),
(15459904, 9, -5157.74, 765.17, 287.395, 0, 0, 1, 0, 100, 0),
(15459904, 10, -5161.05, 765.459, 285.474, 0, 0, 1, 0, 100, 0),
(15459904, 11, -5174, 767.117, 285.474, 0, 3000, 1, 154599041, 100, 0),
(15459904, 12, -5174, 767.117, 285.474, 0, 0, 1, 154599042, 100, 0);

DELETE FROM `waypoint_scripts` WHERE `guid` = 154599041;
DELETE FROM `waypoint_scripts` WHERE `guid` = 154599042;

INSERT INTO `waypoint_scripts` (`guid`, `id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
(154599041, 154599041, 0, 1, 66, 0, 0, 0, 0, 0, 0),
(154599042, 154599042, 0, 18, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM `creature` WHERE `id` = 42645;


