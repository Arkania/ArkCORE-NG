
update creature_loot_template set ChanceOrQuestChance=-100 where entry=345 and item=3631;

delete from creature_queststarter where id=8962 and quest=26508;

update creature_template set KillCredit1=422 where entry in (544,548,1083,545,578);

update quest_template set flags=262148, RewardSpellCast=0, RequiredSpellCast1=81769, RequiredNpcOrGo1=81769, RequiredNpcOrGoCount1=1 where Id=26512;

update creature_template set AIName="", ScriptName="npc_marshal_marris" where entry=382;
update creature_addon set path_id=0 where guid in (61128,34444);

UPDATE `gameobject_template` SET `size`=1.18 WHERE `entry`=201543; -- Warm Fire
UPDATE `gameobject_template` SET `faction`=1078 WHERE `entry`=188215; -- Collision PC Size
UPDATE `gameobject_template` SET `faction`=2401 WHERE `entry`=206602; -- Guild Chest
UPDATE `gameobject_template` SET `flags`=4 WHERE `entry` IN (206881 /*Slumber Sand*/, 203733 /*Bounty Board*/, 203976 /*Auction House*/, 203978 /*Trader's Hall*/, 204346 /*Gnoll Orders*/, 204351 /*Ettin Control Orb*/, 204437 /*Blackrock Key Pouch*/);
UPDATE `gameobject_template` SET `faction`=40 WHERE `entry`=203460; -- Immolation Trap
UPDATE `gameobject_template` SET `faction`=14 WHERE `entry`=204447; -- Seaforium Charge

DELETE FROM `quest_poi` WHERE (`questid`=26651 AND `id`=3) OR (`questid`=26651 AND `id`=2) OR (`questid`=26567 AND `id`=0) OR (`questid`=26651 AND `id`=1) OR (`questid`=26693 AND `id`=1) OR (`questid`=26693 AND `id`=0) OR (`questid`=26668 AND `id`=0) OR (`questid`=26668 AND `id`=1) OR (`questid`=26509 AND `id`=1) OR (`questid`=26509 AND `id`=0) OR (`questid`=26761 AND `id`=0) OR (`questid`=26568 AND `id`=0) OR (`questid`=26694 AND `id`=0) OR (`questid`=26694 AND `id`=1) OR (`questid`=26560 AND `id`=0) OR (`questid`=26560 AND `id`=1) OR (`questid`=26728 AND `id`=0) OR (`questid`=26510 AND `id`=0) OR (`questid`=26510 AND `id`=1) OR (`questid`=26636 AND `id`=0) OR (`questid`=26636 AND `id`=1) OR (`questid`=26636 AND `id`=2) OR (`questid`=26569 AND `id`=1) OR (`questid`=26569 AND `id`=0) OR (`questid`=26569 AND `id`=3) OR (`questid`=26569 AND `id`=2) OR (`questid`=26544 AND `id`=0) OR (`questid`=26586 AND `id`=0) OR (`questid`=26544 AND `id`=1) OR (`questid`=26519 AND `id`=1) OR (`questid`=26561 AND `id`=1) OR (`questid`=26519 AND `id`=0) OR (`questid`=26561 AND `id`=0) OR (`questid`=26511 AND `id`=5) OR (`questid`=26511 AND `id`=4) OR (`questid`=26511 AND `id`=3) OR (`questid`=26511 AND `id`=2) OR (`questid`=26511 AND `id`=1) OR (`questid`=26637 AND `id`=1) OR (`questid`=26637 AND `id`=0) OR (`questid`=26570 AND `id`=3) OR (`questid`=26570 AND `id`=1) OR (`questid`=26503 AND `id`=3) OR (`questid`=26570 AND `id`=7) OR (`questid`=26503 AND `id`=2) OR (`questid`=26570 AND `id`=4) OR (`questid`=26503 AND `id`=1) OR (`questid`=26503 AND `id`=0) OR (`questid`=26587 AND `id`=1) OR (`questid`=26545 AND `id`=0) OR (`questid`=26587 AND `id`=0) OR (`questid`=26545 AND `id`=2) OR (`questid`=26713 AND `id`=1) OR (`questid`=26713 AND `id`=0) OR (`questid`=26713 AND `id`=3) OR (`questid`=26562 AND `id`=2) OR (`questid`=26520 AND `id`=0) OR (`questid`=26646 AND `id`=2) OR (`questid`=26562 AND `id`=0) OR (`questid`=26520 AND `id`=1) OR (`questid`=26562 AND `id`=1) OR (`questid`=26520 AND `id`=2) OR (`questid`=26646 AND `id`=0) OR (`questid`=26646 AND `id`=1) OR (`questid`=26512 AND `id`=0) OR (`questid`=26638 AND `id`=2) OR (`questid`=26512 AND `id`=1) OR (`questid`=26638 AND `id`=0) OR (`questid`=26638 AND `id`=1) OR (`questid`=26571 AND `id`=2) OR (`questid`=26571 AND `id`=1) OR (`questid`=26571 AND `id`=0) OR (`questid`=26714 AND `id`=2) OR (`questid`=26714 AND `id`=1) OR (`questid`=26563 AND `id`=0) OR (`questid`=26513 AND `id`=1) OR (`questid`=26513 AND `id`=0) OR (`questid`=26639 AND `id`=0) OR (`questid`=26505 AND `id`=0) OR (`questid`=26514 AND `id`=2) OR (`questid`=26514 AND `id`=0) OR (`questid`=26514 AND `id`=1) OR (`questid`=26640 AND `id`=0) OR (`questid`=26506 AND `id`=9) OR (`questid`=26573 AND `id`=1) OR (`questid`=26573 AND `id`=0) OR (`questid`=26573 AND `id`=2) OR (`questid`=26506 AND `id`=2) OR (`questid`=26506 AND `id`=0) OR (`questid`=26506 AND `id`=4) OR (`questid`=26506 AND `id`=5) OR (`questid`=26607 AND `id`=0) OR (`questid`=26708 AND `id`=0) OR (`questid`=26708 AND `id`=1) OR (`questid`=31308 AND `id`=0) OR (`questid`=31308 AND `id`=1) OR (`questid`=31308 AND `id`=2) OR (`questid`=31308 AND `id`=3) OR (`questid`=26616 AND `id`=0) OR (`questid`=26616 AND `id`=1) OR (`questid`=26692 AND `id`=4) OR (`questid`=32618 AND `id`=0) OR (`questid`=26692 AND `id`=0) OR (`questid`=26692 AND `id`=1) OR (`questid`=26726 AND `id`=0) OR (`questid`=26508 AND `id`=0) OR (`questid`=26508 AND `id`=1);
INSERT INTO `quest_poi` (`questid`, `id`, `objIndex`, `mapid`, `WorldMapAreaId`, `FloorId`, `unk3`, `unk4`) VALUES
(26651, 3, 0, 0, 36, 1, 0, 0), -- To Win a War, You Gotta Become War - 3
(26651, 2, -1, 0, 36, 1, 0, 0), -- To Win a War, You Gotta Become War - 2
(26567, 0, -1, 0, 36, 1, 0, 0), -- John J. Keeshan - 0
(26651, 1, 0, 0, 36, 1, 0, 0), -- To Win a War, You Gotta Become War - 1
(26693, 1, -1, 0, 36, 1, 0, 0), -- The Dark Tower - 1
(26693, 0, 0, 0, 36, 1, 0, 0), -- The Dark Tower - 0
(26668, 0, -1, 0, 36, 1, 0, 0), -- Detonation - 0
(26668, 1, 30, 0, 36, 1, 0, 0), -- Detonation - 1
(26509, 1, -1, 0, 36, 1, 0, 0), -- An Unwelcome Guest - 1
(26509, 0, 0, 0, 36, 1, 0, 0), -- An Unwelcome Guest - 0
(26761, 0, -1, 0, 36, 1, 0, 0), -- Threat to the Kingdom - 0
(26568, 0, -1, 0, 36, 1, 0, 0), -- This Ain't My War - 0
(26694, 0, 0, 0, 36, 1, 0, 0), -- The Grand Magus Doane - 0
(26694, 1, -1, 0, 36, 1, 0, 0), -- The Grand Magus Doane - 1
(26560, 0, 0, 0, 36, 1, 0, 0), -- Jorgensen - 0
(26560, 1, -1, 0, 36, 1, 0, 0), -- Jorgensen - 1
(26728, 0, -1, 0, 34, 1, 0, 0), -- Hero's Call: Duskwood! - 0
(26510, 0, 0, 0, 36, 1, 0, 0), -- We Must Prepare! - 0
(26510, 1, -1, 0, 36, 1, 0, 0), -- We Must Prepare! - 1
(26636, 0, 0, 0, 36, 9, 0, 0), -- Bravo Company Field Kit: Camouflage - 0
(26636, 1, 0, 0, 36, 9, 0, 0), -- Bravo Company Field Kit: Camouflage - 1
(26636, 2, -1, 0, 36, 1, 0, 0), -- Bravo Company Field Kit: Camouflage - 2
(26569, 1, 0, 0, 36, 7, 0, 0), -- Surveying Equipment - 1
(26569, 0, 0, 0, 36, 9, 0, 0), -- Surveying Equipment - 0
(26569, 3, -1, 0, 36, 1, 0, 0), -- Surveying Equipment - 3
(26569, 2, 0, 0, 36, 5, 0, 0), -- Surveying Equipment - 2
(26544, 0, 0, 0, 36, 9, 0, 0), -- They've Wised Up... - 0
(26586, 0, -1, 0, 36, 1, 0, 0), -- In Search of Bravo Company - 0
(26544, 1, -1, 0, 36, 1, 0, 0), -- They've Wised Up... - 1
(26519, 1, -1, 0, 36, 1, 0, 0), -- He Who Controls the Ettins - 1
(26561, 1, -1, 0, 36, 1, 0, 0), -- Krakauer - 1
(26519, 0, 0, 0, 36, 1, 0, 0), -- He Who Controls the Ettins - 0
(26561, 0, 0, 0, 36, 1, 0, 0), -- Krakauer - 0
(26511, 5, -1, 0, 36, 1, 0, 0), -- Lake Everstill Clean Up - 5
(26511, 4, 0, 0, 36, 7, 0, 0), -- Lake Everstill Clean Up - 4
(26511, 3, 0, 0, 36, 6, 0, 0), -- Lake Everstill Clean Up - 3
(26511, 2, 0, 0, 36, 9, 0, 0), -- Lake Everstill Clean Up - 2
(26511, 1, 0, 0, 36, 6, 0, 0), -- Lake Everstill Clean Up - 1
(26637, 1, -1, 0, 36, 1, 0, 0), -- Bravo Company Field Kit: Chloroform - 1
(26637, 0, 0, 0, 36, 8, 0, 0), -- Bravo Company Field Kit: Chloroform - 0
(26570, 3, 0, 0, 36, 7, 0, 0), -- Render's Army - 3
(26570, 1, 0, 0, 36, 7, 0, 0), -- Render's Army - 1
(26503, 3, -1, 0, 36, 1, 0, 0), -- Still Assessing the Threat - 3
(26570, 7, -1, 0, 36, 1, 0, 0), -- Render's Army - 7
(26503, 2, 0, 0, 36, 1, 0, 0), -- Still Assessing the Threat - 2
(26570, 4, 0, 0, 36, 9, 0, 0), -- Render's Army - 4
(26503, 1, 0, 0, 36, 1, 0, 0), -- Still Assessing the Threat - 1
(26503, 0, 0, 0, 36, 1, 0, 0), -- Still Assessing the Threat - 0
(26587, 1, -1, 0, 36, 1, 0, 0), -- Breaking Out is Hard to Do - 1
(26545, 0, 0, 0, 36, 1, 0, 0), -- Yowler Must Die! - 0
(26587, 0, 0, 0, 36, 1, 0, 0), -- Breaking Out is Hard to Do - 0
(26545, 2, -1, 0, 36, 1, 0, 0), -- Yowler Must Die! - 2
(26713, 1, 0, 0, 36, 1, 0, 0), -- Showdown at Stonewatch - 1
(26713, 0, 0, 0, 36, 1, 0, 0), -- Showdown at Stonewatch - 0
(26713, 3, -1, 0, 36, 1, 0, 0), -- Showdown at Stonewatch - 3
(26562, 2, -1, 0, 36, 1, 0, 0), -- And Last But Not Least... Danforth - 2
(26520, 0, 0, 0, 36, 1, 0, 0), -- Saving Foreman Oslow - 0
(26646, 2, 0, 0, 36, 1, 0, 0), -- Prisoners of War - 2
(26562, 0, 0, 0, 36, 1, 0, 0), -- And Last But Not Least... Danforth - 0
(26520, 1, 0, 0, 36, 1, 0, 0), -- Saving Foreman Oslow - 1
(26562, 1, 0, 0, 36, 1, 0, 0), -- And Last But Not Least... Danforth - 1
(26520, 2, -1, 0, 36, 1, 0, 0), -- Saving Foreman Oslow - 2
(26646, 0, 29, 0, 36, 1, 0, 0), -- Prisoners of War - 0
(26646, 1, -1, 0, 36, 1, 0, 0), -- Prisoners of War - 1
(26512, 0, 0, 0, 36, 4, 0, 0), -- Tuning the Gnomecorder - 0
(26638, 2, -1, 0, 36, 1, 0, 0), -- Hunting the Hunters - 2
(26512, 1, -1, 0, 36, 1, 0, 0), -- Tuning the Gnomecorder - 1
(26638, 0, 0, 0, 36, 5, 0, 0), -- Hunting the Hunters - 0
(26638, 1, 0, 0, 36, 7, 0, 0), -- Hunting the Hunters - 1
(26571, 2, -1, 0, 36, 1, 0, 0), -- Weapons of War - 2
(26571, 1, 0, 0, 36, 1, 0, 0), -- Weapons of War - 1
(26571, 0, 0, 0, 36, 1, 0, 0), -- Weapons of War - 0
(26714, 2, 0, 0, 36, 1, 0, 0), -- Darkblaze, Brood of the Worldbreaker - 2
(26714, 1, -1, 0, 36, 1, 0, 0), -- Darkblaze, Brood of the Worldbreaker - 1
(26563, 0, -1, 0, 36, 1, 0, 0), -- Return of the Bravo Company - 0
(26513, 1, -1, 0, 36, 1, 0, 0), -- Like a Fart in the Wind - 1
(26513, 0, 0, 0, 36, 12, 0, 0), -- Like a Fart in the Wind - 0
(26639, 0, -1, 0, 36, 1, 0, 0), -- Point of Contact: Brubaker - 0
(26505, 0, -1, 0, 36, 1, 0, 0), -- Parker's Report - 0
(26514, 2, -1, 0, 36, 1, 0, 0), -- Canyon Romp - 2
(26514, 0, 0, 0, 36, 5, 0, 0), -- Canyon Romp - 0
(26514, 1, 0, 0, 36, 11, 0, 0), -- Canyon Romp - 1
(26640, 0, -1, 0, 36, 1, 0, 0), -- Unspeakable Atrocities - 0
(26506, 9, -1, 0, 36, 1, 0, 0), -- Franks and Beans - 9
(26573, 1, 0, 0, 36, 1, 0, 0), -- His Heart Must Be In It - 1
(26573, 0, 0, 0, 36, 1, 0, 0), -- His Heart Must Be In It - 0
(26573, 2, -1, 0, 36, 1, 0, 0), -- His Heart Must Be In It - 2
(26506, 2, 0, 0, 36, 7, 0, 0), -- Franks and Beans - 2
(26506, 0, 0, 0, 36, 5, 0, 0), -- Franks and Beans - 0
(26506, 4, 0, 0, 36, 6, 0, 0), -- Franks and Beans - 4
(26506, 5, 0, 0, 36, 4, 0, 0), -- Franks and Beans - 5
(26607, 0, -1, 0, 36, 1, 0, 0), -- They Drew First Blood - 0
(26708, 0, 0, 0, 36, 11, 0, 0), -- AHHHHHHHHHHHH! AHHHHHHHHH!!! - 0
(26708, 1, -1, 0, 36, 1, 0, 0), -- AHHHHHHHHHHHH! AHHHHHHHHH!!! - 1
(31308, 0, 0, 0, 30, 12, 0, 0), -- Learning the Ropes - 0
(31308, 1, 0, 0, 30, 12, 0, 0), -- Learning the Ropes - 1
(31308, 2, 0, 0, 30, 12, 0, 0), -- Learning the Ropes - 2
(31308, 3, 0, 0, 30, 12, 0, 0), -- Learning the Ropes - 3
(26616, 0, -1, 0, 36, 1, 0, 0), -- It's Never Over - 0
(26616, 1, 30, 0, 36, 1, 0, 0), -- It's Never Over - 1
(26692, 4, -1, 0, 36, 1, 0, 0), -- Shadowhide Extinction - 4
(32618, 0, -1, 0, 30, 1, 0, 0), -- Learn To Ride - 0
(26692, 0, 0, 0, 36, 11, 0, 0), -- Shadowhide Extinction - 0
(26692, 1, -1, 0, 36, 1, 0, 0), -- Shadowhide Extinction - 1
(26726, 0, -1, 0, 36, 1, 0, 0), -- Triumphant Return - 0
(26508, 0, -1, 0, 36, 1, 0, 0), -- Nida's Necklace - 0
(26508, 1, 0, 0, 36, 6, 0, 0); -- Nida's Necklace - 1

UPDATE `quest_poi` SET `FloorId`=1, `unk4`=0 WHERE `questid`=353 AND `id`=0; -- Stormpike's Delivery - 0



DELETE FROM `quest_poi_points` WHERE (`questId`=26651 AND `id`=3) OR (`questId`=26651 AND `id`=2) OR (`questId`=26567 AND `id`=0) OR (`questId`=26651 AND `id`=1) OR (`questId`=26693 AND `id`=1) OR (`questId`=26693 AND `id`=0) OR (`questId`=26668 AND `id`=0) OR (`questId`=353 AND `id`=0) OR (`questId`=26668 AND `id`=1) OR (`questId`=26509 AND `id`=1) OR (`questId`=26509 AND `id`=0) OR (`questId`=26761 AND `id`=0) OR (`questId`=26568 AND `id`=0) OR (`questId`=26694 AND `id`=0) OR (`questId`=26694 AND `id`=1) OR (`questId`=26560 AND `id`=0) OR (`questId`=26560 AND `id`=1) OR (`questId`=26728 AND `id`=0) OR (`questId`=26510 AND `id`=0) OR (`questId`=26510 AND `id`=1) OR (`questId`=26636 AND `id`=0) OR (`questId`=26636 AND `id`=1) OR (`questId`=26636 AND `id`=2) OR (`questId`=26569 AND `id`=1) OR (`questId`=26569 AND `id`=0) OR (`questId`=26569 AND `id`=3) OR (`questId`=26569 AND `id`=2) OR (`questId`=26544 AND `id`=0) OR (`questId`=26586 AND `id`=0) OR (`questId`=26544 AND `id`=1) OR (`questId`=26519 AND `id`=1) OR (`questId`=26561 AND `id`=1) OR (`questId`=26519 AND `id`=0) OR (`questId`=26561 AND `id`=0) OR (`questId`=26511 AND `id`=5) OR (`questId`=26511 AND `id`=4) OR (`questId`=26511 AND `id`=3) OR (`questId`=26511 AND `id`=2) OR (`questId`=26511 AND `id`=1) OR (`questId`=26637 AND `id`=1) OR (`questId`=26637 AND `id`=0) OR (`questId`=26570 AND `id`=3) OR (`questId`=26570 AND `id`=1) OR (`questId`=26503 AND `id`=3) OR (`questId`=26570 AND `id`=7) OR (`questId`=26503 AND `id`=2) OR (`questId`=26570 AND `id`=4) OR (`questId`=26503 AND `id`=1) OR (`questId`=26503 AND `id`=0) OR (`questId`=26587 AND `id`=1) OR (`questId`=26545 AND `id`=0) OR (`questId`=26587 AND `id`=0) OR (`questId`=26545 AND `id`=2) OR (`questId`=26713 AND `id`=1) OR (`questId`=26713 AND `id`=0) OR (`questId`=26713 AND `id`=3) OR (`questId`=26562 AND `id`=2) OR (`questId`=26520 AND `id`=0) OR (`questId`=26646 AND `id`=2) OR (`questId`=26562 AND `id`=0) OR (`questId`=26520 AND `id`=1) OR (`questId`=26562 AND `id`=1) OR (`questId`=26520 AND `id`=2) OR (`questId`=26646 AND `id`=0) OR (`questId`=26646 AND `id`=1) OR (`questId`=26512 AND `id`=0) OR (`questId`=26638 AND `id`=2) OR (`questId`=26512 AND `id`=1) OR (`questId`=26638 AND `id`=0) OR (`questId`=26638 AND `id`=1) OR (`questId`=26571 AND `id`=2) OR (`questId`=26571 AND `id`=1) OR (`questId`=26571 AND `id`=0) OR (`questId`=26714 AND `id`=2) OR (`questId`=26714 AND `id`=1) OR (`questId`=26563 AND `id`=0) OR (`questId`=26513 AND `id`=1) OR (`questId`=26513 AND `id`=0) OR (`questId`=26639 AND `id`=0) OR (`questId`=26505 AND `id`=0) OR (`questId`=26514 AND `id`=2) OR (`questId`=26514 AND `id`=0) OR (`questId`=26514 AND `id`=1) OR (`questId`=26640 AND `id`=0) OR (`questId`=26506 AND `id`=9) OR (`questId`=26573 AND `id`=1) OR (`questId`=26573 AND `id`=0) OR (`questId`=26573 AND `id`=2) OR (`questId`=26506 AND `id`=2) OR (`questId`=26506 AND `id`=0) OR (`questId`=26506 AND `id`=4) OR (`questId`=26506 AND `id`=5) OR (`questId`=26607 AND `id`=0) OR (`questId`=26708 AND `id`=0) OR (`questId`=26708 AND `id`=1) OR (`questId`=31308 AND `id`=0) OR (`questId`=31308 AND `id`=1) OR (`questId`=31308 AND `id`=2) OR (`questId`=31308 AND `id`=3) OR (`questId`=26616 AND `id`=0) OR (`questId`=26616 AND `id`=1) OR (`questId`=26692 AND `id`=4) OR (`questId`=32618 AND `id`=0) OR (`questId`=26692 AND `id`=0) OR (`questId`=26692 AND `id`=1) OR (`questId`=26726 AND `id`=0) OR (`questId`=26508 AND `id`=0) OR (`questId`=26508 AND `id`=1);
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES
(26651, 3, 0, -9739, -3185), -- To Win a War, You Gotta Become War
(26651, 2, 0, -9608, -3484), -- To Win a War, You Gotta Become War
(26567, 0, 0, -9202, -2154), -- John J. Keeshan
(26651, 1, 0, -9722, -3117), -- To Win a War, You Gotta Become War
(26693, 1, 0, -9636, -3475), -- The Dark Tower
(26693, 0, 0, -9011, -3214), -- The Dark Tower
(26668, 0, 0, -9636, -3475), -- Detonation
(353, 0, 0, -4826, -2677), -- Stormpike's Delivery
(26668, 1, 0, -9636, -3467), -- Detonation
(26509, 1, 0, -9246, -2045), -- An Unwelcome Guest
(26509, 0, 0, -9289, -1919), -- An Unwelcome Guest
(26761, 0, 0, -9219, -2222), -- Threat to the Kingdom
(26568, 0, 0, -9212, -2215), -- This Ain't My War
(26694, 0, 0, -9292, -3310), -- The Grand Magus Doane
(26694, 1, 0, -9636, -3475), -- The Grand Magus Doane
(26560, 0, 0, -8700, -2598), -- Jorgensen
(26560, 1, 0, -8718, -2341), -- Jorgensen
(26728, 0, 0, -10560, -1152), -- Hero's Call: Duskwood!
(26510, 0, 0, -9236, -2451), -- We Must Prepare!
(26510, 1, 0, -9219, -2222), -- We Must Prepare!
(26636, 0, 0, -9714, -2792), -- Bravo Company Field Kit: Camouflage
(26636, 0, 1, -9676, -2790), -- Bravo Company Field Kit: Camouflage
(26636, 0, 2, -9636, -2778), -- Bravo Company Field Kit: Camouflage
(26636, 0, 3, -9629, -2773), -- Bravo Company Field Kit: Camouflage
(26636, 0, 4, -9603, -2711), -- Bravo Company Field Kit: Camouflage
(26636, 0, 5, -9625, -2557), -- Bravo Company Field Kit: Camouflage
(26636, 0, 6, -9640, -2496), -- Bravo Company Field Kit: Camouflage
(26636, 0, 7, -9709, -2483), -- Bravo Company Field Kit: Camouflage
(26636, 0, 8, -9723, -2524), -- Bravo Company Field Kit: Camouflage
(26636, 1, 0, -9706, -2915), -- Bravo Company Field Kit: Camouflage
(26636, 1, 1, -9623, -2858), -- Bravo Company Field Kit: Camouflage
(26636, 1, 2, -9609, -2775), -- Bravo Company Field Kit: Camouflage
(26636, 1, 3, -9615, -2701), -- Bravo Company Field Kit: Camouflage
(26636, 1, 4, -9666, -2576), -- Bravo Company Field Kit: Camouflage
(26636, 1, 5, -9693, -2517), -- Bravo Company Field Kit: Camouflage
(26636, 1, 6, -9713, -2498), -- Bravo Company Field Kit: Camouflage
(26636, 1, 7, -9717, -2612), -- Bravo Company Field Kit: Camouflage
(26636, 1, 8, -9719, -2686), -- Bravo Company Field Kit: Camouflage
(26636, 2, 0, -9463, -2825), -- Bravo Company Field Kit: Camouflage
(26569, 1, 0, -8883, -2578), -- Surveying Equipment
(26569, 1, 1, -8821, -2536), -- Surveying Equipment
(26569, 1, 2, -8794, -2514), -- Surveying Equipment
(26569, 1, 3, -8779, -2499), -- Surveying Equipment
(26569, 1, 4, -8751, -2471), -- Surveying Equipment
(26569, 1, 5, -8818, -2482), -- Surveying Equipment
(26569, 1, 6, -8857, -2537), -- Surveying Equipment
(26569, 0, 0, -8790, -2422), -- Surveying Equipment
(26569, 0, 1, -8675, -2367), -- Surveying Equipment
(26569, 0, 2, -8672, -2317), -- Surveying Equipment
(26569, 0, 3, -8675, -2268), -- Surveying Equipment
(26569, 0, 4, -8677, -2246), -- Surveying Equipment
(26569, 0, 5, -8694, -2163), -- Surveying Equipment
(26569, 0, 6, -8756, -2142), -- Surveying Equipment
(26569, 0, 7, -8789, -2135), -- Surveying Equipment
(26569, 0, 8, -8829, -2188), -- Surveying Equipment
(26569, 3, 0, -9277, -2241), -- Surveying Equipment
(26569, 2, 0, -8753, -2616), -- Surveying Equipment
(26569, 2, 1, -8670, -2581), -- Surveying Equipment
(26569, 2, 2, -8723, -2552), -- Surveying Equipment
(26569, 2, 3, -8755, -2559), -- Surveying Equipment
(26569, 2, 4, -8822, -2593), -- Surveying Equipment
(26544, 0, 0, -8842, -2071), -- They've Wised Up...
(26544, 0, 1, -8801, -2053), -- They've Wised Up...
(26544, 0, 2, -8795, -2048), -- They've Wised Up...
(26544, 0, 3, -8767, -2009), -- They've Wised Up...
(26544, 0, 4, -8821, -1921), -- They've Wised Up...
(26544, 0, 5, -8848, -1917), -- They've Wised Up...
(26544, 0, 6, -8881, -1916), -- They've Wised Up...
(26544, 0, 7, -8950, -1992), -- They've Wised Up...
(26544, 0, 8, -8918, -2040), -- They've Wised Up...
(26586, 0, 0, -9233, -2700), -- In Search of Bravo Company
(26544, 1, 0, -9219, -2222), -- They've Wised Up...
(26519, 1, 0, -8833, -1937), -- He Who Controls the Ettins
(26561, 1, 0, -8694, -2145), -- Krakauer
(26519, 0, 0, -8833, -1940), -- He Who Controls the Ettins
(26561, 0, 0, -8694, -2148), -- Krakauer
(26511, 5, 0, -9216, -2216), -- Lake Everstill Clean Up
(26511, 4, 0, -9312, -2575), -- Lake Everstill Clean Up
(26511, 4, 1, -9227, -2475), -- Lake Everstill Clean Up
(26511, 4, 2, -9216, -2454), -- Lake Everstill Clean Up
(26511, 4, 3, -9252, -2413), -- Lake Everstill Clean Up
(26511, 4, 4, -9283, -2416), -- Lake Everstill Clean Up
(26511, 4, 5, -9313, -2421), -- Lake Everstill Clean Up
(26511, 4, 6, -9353, -2518), -- Lake Everstill Clean Up
(26511, 3, 0, -9467, -2894), -- Lake Everstill Clean Up
(26511, 3, 1, -9436, -2841), -- Lake Everstill Clean Up
(26511, 3, 2, -9446, -2785), -- Lake Everstill Clean Up
(26511, 3, 3, -9470, -2780), -- Lake Everstill Clean Up
(26511, 3, 4, -9489, -2793), -- Lake Everstill Clean Up
(26511, 3, 5, -9484, -2873), -- Lake Everstill Clean Up
(26511, 2, 0, -9566, -2676), -- Lake Everstill Clean Up
(26511, 2, 1, -9528, -2638), -- Lake Everstill Clean Up
(26511, 2, 2, -9533, -2583), -- Lake Everstill Clean Up
(26511, 2, 3, -9570, -2588), -- Lake Everstill Clean Up
(26511, 2, 4, -9598, -2598), -- Lake Everstill Clean Up
(26511, 2, 5, -9614, -2609), -- Lake Everstill Clean Up
(26511, 2, 6, -9620, -2638), -- Lake Everstill Clean Up
(26511, 2, 7, -9617, -2655), -- Lake Everstill Clean Up
(26511, 2, 8, -9604, -2665), -- Lake Everstill Clean Up
(26511, 1, 0, -9365, -2856), -- Lake Everstill Clean Up
(26511, 1, 1, -9316, -2835), -- Lake Everstill Clean Up
(26511, 1, 2, -9304, -2801), -- Lake Everstill Clean Up
(26511, 1, 3, -9339, -2745), -- Lake Everstill Clean Up
(26511, 1, 4, -9372, -2745), -- Lake Everstill Clean Up
(26511, 1, 5, -9371, -2787), -- Lake Everstill Clean Up
(26637, 1, 0, -9466, -2826), -- Bravo Company Field Kit: Chloroform
(26637, 0, 0, -9502, -2728), -- Bravo Company Field Kit: Chloroform
(26637, 0, 1, -9450, -2728), -- Bravo Company Field Kit: Chloroform
(26637, 0, 2, -9364, -2627), -- Bravo Company Field Kit: Chloroform
(26637, 0, 3, -9327, -2522), -- Bravo Company Field Kit: Chloroform
(26637, 0, 4, -9374, -2487), -- Bravo Company Field Kit: Chloroform
(26637, 0, 5, -9418, -2459), -- Bravo Company Field Kit: Chloroform
(26637, 0, 6, -9534, -2475), -- Bravo Company Field Kit: Chloroform
(26637, 0, 7, -9514, -2685), -- Bravo Company Field Kit: Chloroform
(26570, 3, 0, -8813, -2617), -- Render's Army
(26570, 3, 1, -8753, -2616), -- Render's Army
(26570, 3, 2, -8670, -2581), -- Render's Army
(26570, 3, 3, -8732, -2472), -- Render's Army
(26570, 3, 4, -8751, -2471), -- Render's Army
(26570, 3, 5, -8838, -2471), -- Render's Army
(26570, 3, 6, -8883, -2578), -- Render's Army
(26570, 1, 0, -8790, -2422), -- Render's Army
(26570, 1, 1, -8675, -2367), -- Render's Army
(26570, 1, 2, -8668, -2266), -- Render's Army
(26570, 1, 3, -8694, -2163), -- Render's Army
(26570, 1, 4, -8756, -2142), -- Render's Army
(26570, 1, 5, -8789, -2135), -- Render's Army
(26570, 1, 6, -8829, -2188), -- Render's Army
(26503, 3, 0, -9621, -1873), -- Still Assessing the Threat
(26570, 7, 0, -9275, -2262), -- Render's Army
(26503, 2, 0, -9589, -2264), -- Still Assessing the Threat
(26570, 4, 0, -9246, -2843), -- Render's Army
(26570, 4, 1, -9205, -2855), -- Render's Army
(26570, 4, 2, -9164, -2847), -- Render's Army
(26570, 4, 3, -9054, -2646), -- Render's Army
(26570, 4, 4, -9040, -2619), -- Render's Army
(26570, 4, 5, -9072, -2610), -- Render's Army
(26570, 4, 6, -9110, -2602), -- Render's Army
(26570, 4, 7, -9230, -2636), -- Render's Army
(26570, 4, 8, -9276, -2768), -- Render's Army
(26503, 1, 0, -9797, -2199), -- Still Assessing the Threat
(26503, 0, 0, -9461, -1895), -- Still Assessing the Threat
(26587, 1, 0, -9233, -2700), -- Breaking Out is Hard to Do
(26545, 0, 0, -8891, -2169), -- Yowler Must Die!
(26587, 0, 0, -9165, -2744), -- Breaking Out is Hard to Do
(26545, 2, 0, -9219, -2222), -- Yowler Must Die!
(26713, 1, 0, -9479, -2963), -- Showdown at Stonewatch
(26713, 0, 0, -9326, -3028), -- Showdown at Stonewatch
(26713, 3, 0, -9142, -3037), -- Showdown at Stonewatch
(26562, 2, 0, -8806, -2207), -- And Last But Not Least... Danforth
(26520, 0, 0, -9113, -2064), -- Saving Foreman Oslow
(26646, 2, 0, -9528, -3271), -- Prisoners of War
(26562, 0, 0, -8826, -2188), -- And Last But Not Least... Danforth
(26520, 1, 0, -9112, -2353), -- Saving Foreman Oslow
(26562, 1, 0, -8826, -2188), -- And Last But Not Least... Danforth
(26520, 2, 0, -9231, -2207), -- Saving Foreman Oslow
(26646, 0, 0, -9822, -3265), -- Prisoners of War
(26646, 1, 0, -9463, -2829), -- Prisoners of War
(26512, 0, 0, -9187, -2332), -- Tuning the Gnomecorder
(26512, 0, 1, -9160, -2305), -- Tuning the Gnomecorder
(26512, 0, 2, -9187, -2278), -- Tuning the Gnomecorder
(26512, 0, 3, -9214, -2305), -- Tuning the Gnomecorder
(26638, 2, 0, -9466, -2829), -- Hunting the Hunters
(26512, 1, 0, -9219, -2222), -- Tuning the Gnomecorder
(26638, 0, 0, -9705, -2970), -- Hunting the Hunters
(26638, 0, 1, -9660, -2887), -- Hunting the Hunters
(26638, 0, 2, -9674, -2856), -- Hunting the Hunters
(26638, 0, 3, -9714, -2852), -- Hunting the Hunters
(26638, 0, 4, -9713, -2891), -- Hunting the Hunters
(26638, 1, 0, -9707, -2797), -- Hunting the Hunters
(26638, 1, 1, -9620, -2787), -- Hunting the Hunters
(26638, 1, 2, -9603, -2715), -- Hunting the Hunters
(26638, 1, 3, -9657, -2637), -- Hunting the Hunters
(26638, 1, 4, -9680, -2608), -- Hunting the Hunters
(26638, 1, 5, -9714, -2619), -- Hunting the Hunters
(26638, 1, 6, -9725, -2677), -- Hunting the Hunters
(26571, 2, 0, -9212, -2215), -- Weapons of War
(26571, 1, 0, -9209, -2792), -- Weapons of War
(26571, 0, 0, -9210, -2792), -- Weapons of War
(26714, 2, 0, -9474, -2977), -- Darkblaze, Brood of the Worldbreaker
(26714, 1, 0, -9142, -3037), -- Darkblaze, Brood of the Worldbreaker
(26563, 0, 0, -9212, -2215), -- Return of the Bravo Company
(26513, 1, 0, -9284, -2298), -- Like a Fart in the Wind
(26513, 0, 0, -9038, -2451), -- Like a Fart in the Wind
(26513, 0, 1, -8991, -2407), -- Like a Fart in the Wind
(26513, 0, 2, -8921, -2335), -- Like a Fart in the Wind
(26513, 0, 3, -8878, -2269), -- Like a Fart in the Wind
(26513, 0, 4, -8878, -2159), -- Like a Fart in the Wind
(26513, 0, 5, -8955, -2082), -- Like a Fart in the Wind
(26513, 0, 6, -8963, -2075), -- Like a Fart in the Wind
(26513, 0, 7, -9103, -2012), -- Like a Fart in the Wind
(26513, 0, 8, -9134, -2013), -- Like a Fart in the Wind
(26513, 0, 9, -9153, -2049), -- Like a Fart in the Wind
(26513, 0, 10, -9172, -2274), -- Like a Fart in the Wind
(26513, 0, 11, -9146, -2341), -- Like a Fart in the Wind
(26639, 0, 0, -9676, -2842), -- Point of Contact: Brubaker
(26505, 0, 0, -9219, -2222), -- Parker's Report
(26514, 2, 0, -9219, -2222), -- Canyon Romp
(26514, 0, 0, -9034, -2496), -- Canyon Romp
(26514, 0, 1, -9006, -2393), -- Canyon Romp
(26514, 0, 2, -9071, -2377), -- Canyon Romp
(26514, 0, 3, -9099, -2384), -- Canyon Romp
(26514, 0, 4, -9082, -2433), -- Canyon Romp
(26514, 1, 0, -8980, -2338), -- Canyon Romp
(26514, 1, 1, -8948, -2333), -- Canyon Romp
(26514, 1, 2, -8902, -2299), -- Canyon Romp
(26514, 1, 3, -8879, -2276), -- Canyon Romp
(26514, 1, 4, -8767, -2009), -- Canyon Romp
(26514, 1, 5, -8821, -1921), -- Canyon Romp
(26514, 1, 6, -8848, -1917), -- Canyon Romp
(26514, 1, 7, -8881, -1916), -- Canyon Romp
(26514, 1, 8, -9144, -1997), -- Canyon Romp
(26514, 1, 9, -9153, -2020), -- Canyon Romp
(26514, 1, 10, -9152, -2208), -- Canyon Romp
(26640, 0, 0, -9463, -2829), -- Unspeakable Atrocities
(26506, 9, 0, -9633, -1880), -- Franks and Beans
(26573, 1, 0, -8695, -2162), -- His Heart Must Be In It
(26573, 0, 0, -8695, -2162), -- His Heart Must Be In It
(26573, 2, 0, -9212, -2215), -- His Heart Must Be In It
(26506, 2, 0, -9641, -2405), -- Franks and Beans
(26506, 2, 1, -9493, -2346), -- Franks and Beans
(26506, 2, 2, -9459, -2308), -- Franks and Beans
(26506, 2, 3, -9706, -2132), -- Franks and Beans
(26506, 2, 4, -9731, -2156), -- Franks and Beans
(26506, 2, 5, -9725, -2188), -- Franks and Beans
(26506, 2, 6, -9713, -2231), -- Franks and Beans
(26506, 0, 0, -9665, -1867), -- Franks and Beans
(26506, 0, 1, -9655, -1818), -- Franks and Beans
(26506, 0, 2, -9652, -1756), -- Franks and Beans
(26506, 0, 3, -9806, -1767), -- Franks and Beans
(26506, 0, 4, -9802, -1868), -- Franks and Beans
(26506, 4, 0, -9495, -2061), -- Franks and Beans
(26506, 4, 1, -9584, -1820), -- Franks and Beans
(26506, 4, 2, -9600, -1780), -- Franks and Beans
(26506, 4, 3, -9728, -1729), -- Franks and Beans
(26506, 4, 4, -9655, -1996), -- Franks and Beans
(26506, 4, 5, -9633, -2015), -- Franks and Beans
(26506, 5, 0, -9680, -1833), -- Franks and Beans
(26506, 5, 1, -9712, -1809), -- Franks and Beans
(26506, 5, 2, -9800, -1756), -- Franks and Beans
(26506, 5, 3, -9793, -1857), -- Franks and Beans
(26607, 0, 0, -9202, -2154), -- They Drew First Blood
(26708, 0, 0, -9380, -3454), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 1, -9215, -3374), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 2, -9128, -3321), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 3, -9095, -3237), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 4, -9095, -3220), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 5, -9169, -3079), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 6, -9204, -3075), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 7, -9371, -3264), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 8, -9406, -3379), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 9, -9411, -3396), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 0, 10, -9405, -3421), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(26708, 1, 0, -9145, -2980), -- AHHHHHHHHHHHH! AHHHHHHHHH!!!
(31308, 0, 0, -9230, -65), -- Learning the Ropes
(31308, 0, 1, -9203, -65), -- Learning the Ropes
(31308, 0, 2, -9146, -65), -- Learning the Ropes
(31308, 0, 3, -9124, -28), -- Learning the Ropes
(31308, 0, 4, -9161, 102), -- Learning the Ropes
(31308, 0, 5, -9219, 123), -- Learning the Ropes
(31308, 0, 6, -9277, 97), -- Learning the Ropes
(31308, 0, 7, -9288, 92), -- Learning the Ropes
(31308, 0, 8, -9377, 50), -- Learning the Ropes
(31308, 0, 9, -9362, 8), -- Learning the Ropes
(31308, 0, 10, -9335, -18), -- Learning the Ropes
(31308, 0, 11, -9288, -44), -- Learning the Ropes
(31308, 1, 0, -9530, -502), -- Learning the Ropes
(31308, 1, 1, -9414, -502), -- Learning the Ropes
(31308, 1, 2, -9367, -460), -- Learning the Ropes
(31308, 1, 3, -9335, -344), -- Learning the Ropes
(31308, 1, 4, -9335, -260), -- Learning the Ropes
(31308, 1, 5, -9356, -160), -- Learning the Ropes
(31308, 1, 6, -9388, -97), -- Learning the Ropes
(31308, 1, 7, -9451, -28), -- Learning the Ropes
(31308, 1, 8, -9514, -44), -- Learning the Ropes
(31308, 1, 9, -9541, -134), -- Learning the Ropes
(31308, 1, 10, -9578, -260), -- Learning the Ropes
(31308, 1, 11, -9588, -376), -- Learning the Ropes
(31308, 2, 0, -9678, -334), -- Learning the Ropes
(31308, 2, 1, -9636, -265), -- Learning the Ropes
(31308, 2, 2, -9614, -213), -- Learning the Ropes
(31308, 2, 3, -9525, 23), -- Learning the Ropes
(31308, 2, 4, -9514, 76), -- Learning the Ropes
(31308, 2, 5, -9525, 166), -- Learning the Ropes
(31308, 2, 6, -9562, 208), -- Learning the Ropes
(31308, 2, 7, -9614, 223), -- Learning the Ropes
(31308, 2, 8, -9757, 255), -- Learning the Ropes
(31308, 2, 9, -9767, -192), -- Learning the Ropes
(31308, 2, 10, -9767, -292), -- Learning the Ropes
(31308, 2, 11, -9751, -355), -- Learning the Ropes
(31308, 3, 0, -9319, 187), -- Learning the Ropes
(31308, 3, 1, -9277, 202), -- Learning the Ropes
(31308, 3, 2, -9235, 245), -- Learning the Ropes
(31308, 3, 3, -9251, 329), -- Learning the Ropes
(31308, 3, 4, -9325, 403), -- Learning the Ropes
(31308, 3, 5, -9372, 445), -- Learning the Ropes
(31308, 3, 6, -9578, 534), -- Learning the Ropes
(31308, 3, 7, -9630, 492), -- Learning the Ropes
(31308, 3, 8, -9651, 403), -- Learning the Ropes
(31308, 3, 9, -9646, 334), -- Learning the Ropes
(31308, 3, 10, -9430, 223), -- Learning the Ropes
(31308, 3, 11, -9388, 202), -- Learning the Ropes
(26616, 0, 0, -9467, -2830), -- It's Never Over
(26616, 1, 0, -9283, -2357), -- It's Never Over
(26692, 4, 0, -9142, -3037), -- Shadowhide Extinction
(32618, 0, 0, -9441, -1391), -- Learn To Ride
(26692, 0, 0, -9356, -3439), -- Shadowhide Extinction
(26692, 0, 1, -9101, -3334), -- Shadowhide Extinction
(26692, 0, 2, -9083, -3314), -- Shadowhide Extinction
(26692, 0, 3, -9068, -3271), -- Shadowhide Extinction
(26692, 0, 4, -9085, -3184), -- Shadowhide Extinction
(26692, 0, 5, -9095, -3175), -- Shadowhide Extinction
(26692, 0, 6, -9159, -3140), -- Shadowhide Extinction
(26692, 0, 7, -9360, -3120), -- Shadowhide Extinction
(26692, 0, 8, -9428, -3123), -- Shadowhide Extinction
(26692, 0, 9, -9433, -3368), -- Shadowhide Extinction
(26692, 0, 10, -9424, -3433), -- Shadowhide Extinction
(26692, 1, 0, -9634, -3473), -- Shadowhide Extinction
(26726, 0, 0, -9219, -2222), -- Triumphant Return
(26508, 0, 0, -9352, -2206), -- Nida's Necklace
(26508, 1, 0, -9364, -2397), -- Nida's Necklace
(26508, 1, 1, -9316, -2147), -- Nida's Necklace
(26508, 1, 2, -9324, -1987), -- Nida's Necklace
(26508, 1, 3, -9368, -2094), -- Nida's Necklace
(26508, 1, 4, -9387, -2175), -- Nida's Necklace
(26508, 1, 5, -9376, -2304); -- Nida's Necklace


DELETE FROM `creature_equip_template` WHERE `entry` IN (69334, 65153, 61834, 61836, 61837, 61838, 61841, 73190, 69974, 69975,65648, 62415);
INSERT INTO `creature_equip_template` (`entry`, `id`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES
(69334, 1, 89897, 0, 0), -- Adherent Hanjun
(65153, 1, 46987, 143, 0), -- General Hammond Clay
(61834, 1, 82278, 0, 0), -- Alyn Black
(61836, 1, 2549, 0, 0), -- Moni Widdlesprock
(61837, 1, 12751, 0, 0), -- Leria Nightwind
(61838, 1, 61327, 67460, 0), -- Gavin Marlsbury
(61841, 1, 80580, 0, 0), -- Brunn Goldenmug
(73190, 1, 100229, 0, 0), -- Necrolord Sipe
(69974, 1, 5305, 0, 0), -- Knight-Lieutenant T'Maire Sydes
(69975, 1, 5305, 1984, 0), -- Captain Dirgehammer
(65648, 1, 3367, 0, 0), -- Old MacDonald
(62415, 1, 1910, 0, 0); -- Silvershard Emissary


DELETE FROM `npc_text` WHERE `ID` IN (20964, 7015, 21137, 17607);
INSERT INTO `npc_text` (`ID`, `BroadcastTextId0`) VALUES
(20964, 66835), -- 20964
(7015, 9685), -- 7015
(21137, 67341), -- 21137
(17607, 49765); -- 17607






