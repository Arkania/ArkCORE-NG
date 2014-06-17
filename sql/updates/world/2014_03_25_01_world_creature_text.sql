-- Custodian of Time's Whispers for quest 10277
-- DELETE FROM `script_texts` WHERE `entry` IN (-1000217,-1000218,-1000219,-1000220,-1000221,-1000222,-1000223,-1000224,-1000225,-1000226,-1000227,-1000228,-1000229,-1000230);
DELETE FROM `creature_text` WHERE `entry`=20129; 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(20129,0,0, 'Greetings, $N. I will guide you through the cavern. Please try and keep up.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_1'),
(20129,1,0, 'We do not know if the Caverns of Time have always been accessible to mortals. Truly, it is impossible to tell as the Timeless One is in perpetual motion, changing our timeways as he sees fit. What you see now may very well not exist tomorrow. You may wake up and have no memory of this place.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_2'),
(20129,2,0, 'It is strange, I know... Most mortals cannot actually comprehend what they see here, as often, what they see is not anchored within their own perception of reality.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_3'),
(20129,3,0, 'Follow me, please.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_4'),
(20129,4,0, 'There are only two truths to be found here: First, that time is chaotic, always in flux, and completely malleable and second, perception does not dictate reality.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_5'),
(20129,5,0, 'As custodians of time, we watch over and care for Nozdormu''s realm. The master is away at the moment, which means that attempts are being made to dramatically alter time. The master never meddles in the affairs of mortals but instead corrects the alterations made to time by others. He is reactionary in this regard.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_6'),
(20129,6,0, 'For normal maintenance of time, the Keepers of Time are sufficient caretakers. We are able to deal with most ordinary disturbances. I speak of little things, such as rogue mages changing something in the past to elevate their status or wealth in the present.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_7'),
(20129,7,0, 'These tunnels that you see are called timeways. They are infinite in number. The ones that currently exist in your reality are what the master has deemed as ''trouble spots.'' These trouble spots may differ completely in theme but they always share a cause. That is, their existence is a result of the same temporal disturbance. Remember that should you venture inside one...',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_8'),
(20129,8,0, 'This timeway is in great disarray! We have agents inside right now attempting to restore order. What information I have indicates that Thrall''s freedom is in jeopardy. A malevolent organization known as the Infinite Dragonflight is trying to prevent his escape. I fear without outside assistance, all will be lost.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_9'),
(20129,9,0, 'We have very little information on this timeway. Sa''at has been dispatched and is currently inside. The data we have gathered from his correspondence is that the Infinite Dragonflight are once again attempting to alter time. Could it be that the opening of the Dark Portal is being targeted for sabotage? Let us hope not...',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_10'),
(20129,10,0, 'This timeway collapsed and reformed. The result was Stratholme of yore. What could possibly be happening inside?',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_11'),
(20129,11,0, 'The timeways are currently ranked in order from least catastrophic to most catastrophic. Note that they are all classified as catastrophic, meaning that any single one of these timeways collapsing would mean that your world would end. We only classify them in such a way so that the heroes and adventurers that are sent here know which timeway best suits their abilities.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_12'),
(20129,12,0, 'All we know of this timeway is that it leads to Mount Hyjal. The Infinite Dragonflight have gone to great lengths to prevent our involvement. We know next to nothing, mortal. Soridormi is currently attempting to break through the timeway''s defenses but has thus far been unsuccessful. You might be our only hope of breaking through and resolving the conflict.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_13'),
(20129,13,0, 'Our time is at an end $N. I would wish you luck, if such a thing existed.',15,0,100,0,0,0, 'WHISPER_CUSTODIAN_14');

-- Mimiron
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1603259 AND -1603240;
DELETE FROM `creature_text` WHERE `entry`=33350;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(33350,0,0, 'Oh, my! I wasn''t expecting company! The workshop is such a mess! How embarrassing!',14,0,100,0,0,15611, 'Mimiron SAY_AGGRO'),
(33350,1,0, 'Now why would you go and do something like that? Didn''t you see the sign that said ''DO NOT PUSH THIS BUTTON!''? How will we finish testing with the self-destruct mechanism active?',14,0,100,0,0,15629, 'Mimiron SAY_HARDMODE_ON'),
(33350,2,0, 'We haven''t much time, friends! You''re going to help me test out my latest and greatest creation. Now, before you change your minds, remember, that you kind of owe it to me after the mess you made with the XT-002.',14,0,100,0,0,15612, 'Mimiron SAY_MKII_ACTIVATE'),
(33350,3,0, 'MEDIC!',14,0,100,0,0,15613, 'Mimiron SAY_MKII_SLAY_1'),
(33350,3,1, 'I can fix that... or, maybe not! Sheesh, what a mess...',14,0,100,0,0,15614, 'Mimiron SAY_MKII_SLAY_2'),
(33350,4,0, 'WONDERFUL! Positively marvelous results! Hull integrity at 98.9 percent! Barely a dent! Moving right along.',14,0,100,0,0,15615, 'Mimiron SAY_MKII_DEATH'),
(33350,5,0, 'Behold the VX-001 Anti-personnel Assault Cannon! You might want to take cover.',14,0,100,0,0,15616, 'Mimiron SAY_VX001_ACTIVATE'),
(33350,6,0, 'Fascinating. I think they call that a "clean kill".',14,0,100,0,0,15617, 'Mimiron SAY_VX001_SLAY_1'),
(33350,6,1, 'Note to self: Cannon highly effective against flesh.',14,0,100,0,0,15618, 'Mimiron SAY_VX001_SLAY_2'),
(33350,7,0, 'Thank you, friends! Your efforts have yielded some fantastic data! Now, where did I put- oh, there it is!',14,0,100,0,0,15619, 'Mimiron SAY_VX001_DEATH'),
(33350,8,0, 'Isn''t it beautiful? I call it the magnificent aerial command unit!',14,0,100,0,0,15620, 'Mimiron SAY_AERIAL_ACTIVATE'),
(33350,9,0, 'Outplayed!',14,0,100,0,0,15621, 'Mimiron SAY_AERIAL_SLAY_1'),
(33350,9,1, 'You can do better than that!',14,0,100,0,0,15622, 'Mimiron SAY_AERIAL_SLAY_2'),
(33350,10,0, 'Preliminary testing phase complete. Now comes the true test!!',14,0,100,0,0,15623, 'Mimiron SAY_AERIAL_DEATH'),
(33350,11,0, 'Gaze upon its magnificence! Bask in its glorious, um, glory! I present you... V-07-TR-0N!',14,0,100,0,0,15624, 'Mimiron SAY_V07TRON_ACTIVATE'),
(33350,12,0, 'Prognosis: Negative!',14,0,100,0,0,15625, 'Mimiron SAY_V07TRON_SLAY_1'),
(33350,12,1, 'You''re not going to get up from that one, friend.',14,0,100,0,0,15626, 'Mimiron SAY_V07TRON_SLAY_2'),
(33350,13,0, 'It would appear that I''ve made a slight miscalculation. I allowed my mind to be corrupted by the fiend in the prison, overriding my primary directive. All systems seem to be functional now. Clear.',14,0,100,0,0,15627, 'Mimiron SAY_V07TRON_DEATH'),
(33350,14,0, 'Oh, my! It would seem that we are out of time, my friends!',14,0,100,0,0,15628, 'Mimiron SAY_BERSERK'),
(33350,15,0, 'Combat matrix enhanced. Behold wonderous rapidity!',14,0,100,0,0,15630, 'Mimiron SAY_YS_HELP');

-- AzjolNerub/Ahnkahet/Elder Nadox
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1619020 AND -1619014;
DELETE FROM `creature_text` WHERE `entry`=29309;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(29309,0,0, 'The secrets of the deep shall remain hidden.',14,0,100,0,0,14033, 'SAY_AGGRO'),
(29309,1,0, 'Sleep now, in the cold dark.',14,0,100,0,0,14036, 'SAY_SLAY_1'),
(29309,1,1, 'For the Lich King!',14,0,100,0,0,14037, 'SAY_SLAY_2'),
(29309,1,2, 'Perhaps we will be allies soon.',14,0,100,0,0,14038, 'SAY_SLAY_3'),
(29309,2,0, 'Master, is my service complete?',14,0,100,0,0,14039, 'SAY_DEATH'),
(29309,3,0, 'The young must not grow hungry...',14,0,100,0,0,14034, 'SAY_EGG_SAC_1'),
(29309,3,1, 'Shhhad ak kereeesshh chak-k-k!',14,0,100,0,0,14035, 'SAY_EGG_SAC_2'),
(29309,4,0, 'An Ahn''kahar Guardian hatches!',16,0,100,0,0,14035, 'EMOTE_HATCHES');

-- AzjolNerub/Ahnkahet/Herald Volazj
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1619036 AND -1619030;
DELETE FROM `creature_text` WHERE `entry`=29311;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(29311,0,0, 'Shgla''yos plahf mh''naus.', 14,0,100,0,0,14043, 'SAY_AGGRO_1'),
(29311,0,1, 'They who dine on lost souls know only hunger.', 15, 0, 100, 0, 0, 14043, 'SAY_AGGRO_2'),
(29311,1,0, 'Ywaq puul skshgn: on''ma yeh''glu zuq.', 14,0,100,0,0,14045, 'SAY_SLAY_1'),
(29311,1,1, 'Ywaq ma phgwa''cul hnakf.',14,0,100,0,0,14046, 'SAY_SLAY_2'),
(29311,1,2, 'Ywaq maq oou; ywaq maq ssaggh. Ywaq ma shg''fhn.',14,0,100,0,0,14047, 'SAY_SLAY_3'),
(29311,2,0, 'Iilth vwah, uhn''agth fhssh za.', 14, 0, 100, 0, 0, 14048, 'SAY_DEATH_1'),
(29311,2,1, 'Where one falls, many shall take its place.', 15, 0, 100, 0, 0, 14048, 'SAY_DEATH_2'),
(29311,3,0, 'Gul''kafh an''shel. Yoq''al shn ky ywaq nuul.', 14, 0, 100, 0, 0, 14044, 'SAY_PHASE');

-- AzjolNerub/Ahnkahet/Jedoga Shadowseeker
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1619013 AND -1619000;
DELETE FROM `creature_text` WHERE `entry`=29310;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(29310, 0, 0, 'These are sacred halls! Your intrusion will be met with death!', 14, 0, 100, 0, 0, 14343, 'SAY_AGGRO'),
(29310, 1, 0, 'Who among you is devoted?', 14, 0, 100, 0, 0, 14343, 'SAY_SACRIFICE_1_1'),
(29310, 1, 1, 'You there! Step forward!', 14, 0, 100, 0, 0, 14343, 'SAY_SACRIFICE_1_2'),
(29310, 2, 0, 'Yogg-Saron, grant me your power!', 14, 0, 100, 0, 0, 14343, 'SAY_SACRIFICE_2_1'),
(29310, 2, 1, 'Master, a gift for you!', 14, 0, 100, 0, 0, 14343, 'SAY_SACRIFICE_2_2'),
(29310, 3, 0, 'Glory to Yogg-Saron!', 14, 0, 100, 0, 0, 0, 'SAY_SLAY_1'),
(29310, 3, 1, 'You are unworthy!', 14, 0, 100, 0, 0, 0, 'SAY_SLAY_2'),
(29310, 3, 2, 'Get up! You haven''t suffered enough.', 14, 0, 100, 0, 0, 14350, 'SAY_SLAY_3'),
(29310, 4, 0, 'Do not expect your sacrilege... to go unpunished.', 14, 0, 100, 0, 0, 0, 'SAY_DEATH'),
(29310, 5, 0, 'The elements themselves will rise up against the civilized world! Only the faithful will be spared!', 14, 0, 100, 0, 0, 14352, 'SAY_PREACHING_1'),
(29310, 5, 1, 'Immortality can be yours, but only if you pledge yourself fully to Yogg-Saron!', 14, 0, 100, 0, 0, 14353, 'SAY_PREACHING_2'),
(29310, 5, 2, 'Here, on the very borders of his domain, you will experience power you could have never imagined!', 14, 0, 100, 0, 0, 0, 'SAY_PREACHING_3'),
(29310, 5, 3, 'You have traveled long and risked much to be here! Your devotion shall be rewarded.', 14, 0, 100, 0, 0, 0, 'SAY_PREACHING_4'),
(29310, 5, 4, 'The faithful shall be exalted! But there is more work to be done. We will press on until all of Azeroth lies beneath his shadow!', 14, 0, 100, 0, 0, 0, 'SAY_PREACHING_5');