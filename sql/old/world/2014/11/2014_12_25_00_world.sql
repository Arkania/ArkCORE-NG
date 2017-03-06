

delete from creature where guid in (269422,269423,269424,269425) and id=42385;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`,`modelid`,`position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(269422, 42385, 0, 1, 1, 11873, -10113.52, 1045.869, 37.48228, 0.2617994, 120, 0, 0), -- Orphan (Area: Westfall) 8632
(269423, 42385, 0, 1, 1,   338, -10111.3, 1044.02, 37.47646, 1.291544, 120, 0, 0), -- Orphan (Area: Westfall)	27466
(269424, 42385, 0, 1, 1,   221, -10112.44, 1044.927, 37.48221, 0.9424778, 120, 0, 0), -- Orphan (Area: Westfall) 8634
(269425, 42385, 0, 1, 1,   344, -10119, 1046.574, 42.25, 5.730374, 120, 5, 1); -- Orphan (Area: Westfall) 8639  (random movement)

delete from creature_addon where guid in (269422,269423,269424,269425);
insert into creature_addon (guid, path_id, mount, bytes1, bytes2, emote, auras) values
(269422, 0, 0, 0, 1, 0, ""), -- Orphan
(269423, 0, 0, 0, 1, 0, ""), -- Orphan
(269424, 0, 0, 0, 1, 0, ""), -- Orphan
(269425, 0, 0, 0, 1, 0, ""); -- Orphan

delete from creature_text where entry=42385 and groupid in (0,1,2) and id=0;
insert into creature_text (entry, groupid, id, text, type, language, probability, emote, duration, sound, comment, BroadcastTextID) values
(42385, 0, 0, "I'm so happy. Thank you, mama and thank you, $n.", 12, 7, 100, 1, 0, 0, "Waise to Player", 42470),
(42385, 1, 0, "YAY FOR $n!", 12, 7, 100, 1, 0, 0,  "Waise to Player", 42472),
(42385, 2, 0, "%s cries.", 16, 7, 100, 1, 0, 0,  "Waise to Player", 42473);

delete from creature_text where entry=235 and groupid in (0,1) and id in (0,1);
insert into creature_text values
(235, 0, 0, "Thank you, $n. Your kindness will not be forgotten.", 12, 7, 100, 2, 0, 0, "Salma Saldean to Player",42468),
(235, 1, 0, "Dinner's ready! Come and get it!", 14, 7, 100, 22, 0, 0, "Salma Saldean to Player",42469),
(235, 1, 1, "Dinner's ready! Come and get it!", 14, 7, 100, 0, 0, 0, "Salma Saldean to Player", 42469);

delete from waypoint_data where id in (2694220, 2694221,2694230, 2694231, 2694240, 2694241, 70930, 70931);
insert into waypoint_data (id, point, position_x, position_y ,position_z, orientation, delay, move_flag, action, action_chance) values
(2694220, 0, -10112.53, 1044.365, 37.71697, 0, 0, 0, 0, 100),
(2694220, 1, -10110.51, 1039.865, 37.71697, 0, 0, 0, 0, 100),
(2694220, 2, -10108.75, 1037.395, 37.71697, 1.47, 0, 0, 0, 100),

(2694221, 0, -10109.56, 1040.115, 37.96697, 0, 0, 0, 0, 100),
(2694221, 1, -10111.31, 1042.365, 37.71697, 0, 0, 0, 0, 100),
(2694221, 2, -10113.52, 1045.869, 37.48228, 0, 0, 0, 0, 100),

(2694230, 0, -10112.53, 1044.365, 37.71697, 0, 0, 0, 0, 100),
(2694230, 1, -10108.51, 1040.865, 37.71697, 0, 0, 0, 0, 100),
(2694230, 2, -10106.75, 1039.395, 37.71697, 1.47, 0, 0, 0, 100),

(2694231, 0, -10109.56, 1040.115, 37.96697, 0, 0, 0, 0, 100),
(2694231, 1, -10111.31, 1042.365, 37.71697, 0, 0, 0, 0, 100),
(2694231, 2, -10111.3, 1044.02, 37.47646, 0, 0, 0, 0, 100),

(2694240, 0, -10112.76, 1043.972, 37.71951, 0, 0, 0, 0, 100),
(2694240, 1, -10112.01, 1042.222, 37.71951, 0, 0, 0, 0, 100),
(2694240, 2, -10110.26, 1040.222, 37.71951, 0, 0, 0, 0, 100),
(2694240, 3, -10109.51, 1039.472, 37.96951, 0, 0, 0, 0, 100),

(2694241, 0, -10109.26, 1039.472, 38.21951, 0, 0, 0, 0, 100),
(2694241, 1, -10110.01, 1040.722, 37.71951, 0, 0, 0, 0, 100),
(2694241, 2, -10110.76, 1042.222, 37.71951, 0, 0, 0, 0, 100),
(2694241, 3, -10112.01, 1044.722, 37.71951, 0, 0, 0, 0, 100),

(70930, 0, -10112.12, 1041.93, 37.5376, 2.33, 0, 0, 0, 100),
(70930, 1, -10110.13, 1040.74, 37.5376, 5.61, 0, 0, 0, 100),
(70930, 2, -10109.23, 1040.01, 37.7376, 5.61, 0, 0, 0, 100),

(70931, 0, -10109.23, 1040.01, 37.8376, 5.61, 0, 0, 0, 100),
(70931, 1, -10110.15, 1040.74, 37.5376, 5.61, 0, 0, 0, 100),
(70931, 2, -10112.12, 1041.93, 37.5376, 2.33, 0, 0, 0, 100);

UPDATE quest_template SET RequiredItemId1=0,RequiredItemCount1=0,RequiredSourceItemId1=57988,RequiredSourceItemCount1=1 WHERE Id=26266;

-- 8632		Emote ID: OneShotCry (18)	Chat type: MonsterEmote (16)	  	Text: %s weint.
-- 27466	Emote ID: OneShotTalk (1)	Chat type: MonsterSay (12) 	 	Text: Ich bin so glücklich. Danke, Mama, und habt Dank, $n.		Sender Name: Waise
-- 8634		Chat type: MonsterSay (12) 







