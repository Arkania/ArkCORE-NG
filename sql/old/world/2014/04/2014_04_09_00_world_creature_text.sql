-- ----------------------------------
-- CATACLYSM SCRIPTS               --
-- ----------------------------------
-- Alizabal
-- DELETE FROM `script_texts` WHERE `entry` = -1900027;
DELETE FROM `creature_text` WHERE `entry`=55869;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(55869,0,0,14,25777,100,'Alizabal','I hate adventurers.'),
(55869,1,0,14,25778,100,'Alizabal','I hate... every one of you...'),
(55869,2,0,14,25784,100,'Alizabal','I didn''t hate that.'),
(55869,3,0,14,25789,100,'Alizabal','My hate will consume you!'),
(55869,4,0,14,25787,100,'Alizabal','Feel my hatred!'),
(55869,5,0,14,25791,100,'Alizabal','I hate standing still.'),
(55869,6,0,14,25790,100,'Alizabal','I hate you all!'),
(55869,7,0,14,25780,100,'Alizabal','I hate incompetent raiders.'),
(55869,8,0,14,25779,100,'Alizabal','How I HATE this place. My captors may be long-dead, but don''t think I won''t take it all out on you miserable treasure-hunters.'),
(55869,9,0,41,0,100,"Alizabal SAY_BLADES","Alizabal goes into a deadly Blade Dance!");

-- Chimaeron
-- DELETE FROM `script_texts` WHERE `entry` IN (-1900028,-1851023,-1851026,-1851027,-1851028,-1851029);
DELETE FROM `creature_text` WHERE `entry` IN (43296, 44202);
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(43296,0,0,41,0,100,"Chimaeron SAY_MASSACRE","Chimaeron prepares to massacre his foes!"),
(44202,1,0,14,20833,100,"Finkle help SAY_INTRO","Help! I'm trapped in here!"),
(44202,2,0,14,20836,100,"Finkle systems failure SAY_SYSTEM_FAILURE","Poor little fella."),
(44202,3,0,14,20838,100,"Finkle chimaeron death SAY_DEATH","Great job guys! The key should be in his guts somewhere. Just, uh, fish around in there 'till you find it."),
(44202,4,0,14,20839,100,"Finkle systems failure SAY_F_OUTRO","Thanks for freeing me! I'm off to have more amazing adventures."),
(44202,5,0,14,20837,100,"Finkle p2 SAY_P2","Oh-oh! He looks pretty mad now!");

-- Jan'alai
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1568009 AND -1568000;
DELETE FROM `creature_text` WHERE `entry`=23578;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(23578,0,0,14,12031,100,"Jan''alai SAY_AGGRO","Spirits of da wind be your doom!"),
(23578,1,0,14,12032,100,"Jan''alai SAY_FIRE_BOMBS","I burn ya now!"),
(23578,2,0,14,12033,100,"Jan''alai SAY_SUMMON_HATCHER","Where ma hatcha? Get to work on dem eggs!"),
(23578,3,0,14,12034,100,"Jan''alai SAY_ALL_EGGS","I show you strength... in numbers."),
(23578,4,0,14,12035,100,"Jan''alai SAY_BERSERK","You done run outta time!"),
(23578,5,0,14,12036,100,"Jan''alai SAY_SLAY_1","It all be over now, mon!"),
(23578,5,1,14,12037,100,"Jan''alai SAY_SLAY_2","Tazaga-choo!"),
(23578,6,0,14,12038,100,"Jan''alai SAY_DEATH","Daakara... got a surprise for you..."),
(23578,7,0,12,12039,100,"Jan''alai SAY_EVENT_COME","Come, strangers. The spirit of the dragonhawk be hungry for worthy souls."),
(23578,7,1,12,12040,100,"Jan''alai SAY_EVENT_COME","Come, friends. Your bodies gonna feed ma hatchlings, and your souls are going to fill me with power!");

-- Ragnaros
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1900024 AND -1900000;
DELETE FROM `creature_text` WHERE `entry`=52409;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(52409,0,0,14,24517,100,"Ragnaros SAY_AGGRO","Mortal Insects! You dare tresspass into MY domain? Your arrogance will be purged in living flame."),
(52409,1,0,14,24519,100,"Ragnaros SAY_DEATH","Too soon! ... You have come too soon..."),
(52409,2,0,14,24521,100,"Ragnaros SAY_KILL_1","Die!"),
(52409,2,1,14,24522,100,"Ragnaros SAY_KILL_2","Your judgement has come!"),
(52409,2,2,14,24531,100,"Ragnaros SAY_KILL_3","Die, insect!"),
(52409,3,0,14,24524,100,"Ragnaros SAY_ENRAGE_TEXT","Fall to your knees, mortals! This ends now."),
(52409,4,1,14,24515,100,"Ragnaros SAY_INTERMISSION2","Denizens of flame! Come to me!"),
(52409,5,0,14,24516,100,"Ragnaros SAY_INTERMISSION1","Arrise, servants of fire! Consume their flesh!"),
(52409,6,0,14,24525,100,"Ragnaros SAY_PHASE_2","Sulfuras will be your end!"),
(52409,7,1,14,24533,100,"Ragnaros SAY_PHASE_3","Begone from my realm, insects!"),
(52409,8,0,14,24532,100,"Ragnaros SAY_PURGE","By fire be purged!"),
(52409,9,0,14,24518,100,"Ragnaros SAY_DEATH_H","No, noooo- This was to be my hour of triumph..."),
(52409,10,0,14,24520,100,"Ragnaros SAY_SULFURAS_SMASH","You will be crushed!"),
(52409,11,0,14,24526,100,"Ragnaros SAY_PHASE_HEROIC_TEXT","When I finish this, your pathetic mortal world will burn with my vengeance!"),
(52409,12,0,14,24529,100,"Ragnaros SAY_ENGULFING_FLAMES_TEXT","This is MY realm!"),
(52409,13,0,41,0,100,"Ragnaros SAY_ENRAGE","With nobody in range, Ragnaros enrages and begins casting Magma Blast!"),
(52409,14,0,41,0,100,"Ragnaros SAY_SMASH","Ragnaros begins casting Sulfuras smash!"),
(52409,15,0,41,0,100,"Ragnaros SAY_SPLITTING","Ragnaros does a splitting blow and submerges into the lava!"),
(52409,16,0,41,0,100,"Ragnaros SAY_SONS","Sons of Flame emerge and start heading towards Sulfuras!"),
(52409,17,0,41,0,100,"Ragnaros SAY_NEW_PHASE","Ragnaros emerges from the lava!"),
(52409,18,0,41,0,100,"Ragnaros SAY_ENGULFING","Ragnaros begins casting Engulfing Flames!"),
(52409,19,0,41,0,100,"Ragnaros SAY_WORLD","Ragnaros begins casting World in Flames!"),
(52409,20,0,41,0,100,"Ragnaros SAY_METEOR","A Living Meteor crashes onto the platform!"),
(52409,21,0,41,0,100,"Ragnaros SAY_HEROIC_PHASE","Ragnaros rises from the lava and is now able to move!"),
(52409,22,0,41,0,100,"Ragnaros SAY_AID","Keepers of Azeroth come to your aid!");

-- Shannox
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1999984 AND -1999971;
DELETE FROM `creature_text` WHERE `entry`=53691;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(53691,0,0,14,24517,100,"Shannox SAY_AGGRO","A-hah! The interlopers! Kill them. EAT THEM!"),
(53691,1,0,41,0,100,"Shannox EMOTE_SOFT_ENRAGE","Shannox becomes enraged at seeing once of his companions fall!"),
(53691,2,0,14,0,100,"Shannox SAY_ON_DOGS_FALL","Oh, you murderers! Why? Why would you kill such a noble animal?"),
(53691,3,0,14,0,100,"Shannox SAY_ON_DEAD","Ohh... the pain. Lord of Fire, it hurts...."),
(53691,4,0,14,0,100,"Shannox SAY_DOG_FOOD","Dog food!"),
(53691,5,0,14,0,100,"Shannox SAY_FETCH_SUPPER","Fetch your supper!"),
(53691,6,0,14,0,100,"Shannox SAY_GO_FOR_THROAT","Go for the throat!"),
(53691,7,0,14,0,100,"Shannox SAY_BURN_ONE","Now you burn!"),
(53691,7,1,14,0,100,"Shannox SAY_BURN_TWO","The Firelord will be most pleased."),
(53691,8,0,14,0,100,"Shannox SAY_ON_KILL_ONE","What in the world? Let''s get out of here!"),
(53691,8,1,14,0,100,"Shannox SAY_ON_KILL_TWO","Twist in flames, interlopers!"),
(53691,9,0,14,0,100,"Shannox SAY_RIPLIMB","Riplimb! No... no! Oh, you terrible little beasts! How could you?!"),
(53691,10,0,14,0,100,"Shannox SAY_INTRO_SPECH_PART_ONE","Yes, I smell them too, Riplimb. Outsiders encroach on the Firelords private grounds."),
(53691,11,0,14,0,100,"Shannox SAY_INTRO_SPECH_PART_TWO","Find their trail. Find them for me, that I may dispense punishment!");

-- Temple Guardian Anhuur
-- DELETE FROM `script_texts` WHERE `entry` = -1900025;
DELETE FROM `creature_text` WHERE `entry`=39425;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(39425, 0, 0, 'Turn back, intruders! These halls must not be disturbed!', 14, 0, 100, 0, 0, 18580, 'VO_HO_Anhuur_Engage'),
(39425, 1, 0, 'Beacons of light, bestow upon me your aegis!', 14, 0, 100, 0, 0, 18581, 'VO_HO_Anhuur_Event'),
(39425, 2, 0, 'A product of your own insolence!', 14, 0, 100, 0, 0, 18583, 'VO_HO_Anhuur_Slay02'),
(39425, 2, 1, 'I regret nothing !', 14, 0, 100, 0, 0, 18582, 'VO_HO_Anhuur_Slay01'),
(39425, 3, 0, 'What... have you... done? ', 14, 0, 100, 0, 0, 18579, 'VO_HO_Anhuur_Death'),
(39425, 4, 0, 'Temple Guardian Anhuur becomes protected by his defense beacons! Disable them by pulling the levers below!', 41, 0, 100, 0, 0, 0, 'VO_HO_Anhuur_Special');

-- Isiset <Construct of Magic>
UPDATE `creature_text` SET `probability`=100 WHERE `entry`=39587;
-- DELETE FROM `script_texts` WHERE `entry` = -1900026;
DELETE FROM `creature_text` WHERE `entry`=39587 AND `groupid`=4;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(39587, 4, 0, 'Isiset splits into Mirror Images!', 41, 0, 100, 0, 0, 0, 'Isiset SAY_SPLIT');

-- General Husam
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1877022 AND -1877000;
DELETE FROM `creature_text` WHERE `entry`=44577;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(44577, 0, 0, 'Invaders! You shall go no further! ', 14, 0, 0, 0, 0, 21886, 'VO_TV_Husam_Engage01'),
(44577, 1, 0, 'Tread Lightly! ', 14, 0, 0, 0, 0, 21887, 'VO_TV_Husam_Event01'),
(44577, 2, 0, 'Murkash!', 14, 0, 0, 0, 0, 21888, 'VO_TV_Husam_Event02'),
(44577, 3, 0, 'Siamat must not be freed! Turn back before it is too late!', 14, 0, 0, 0, 0, 21885, 'VO_TV_Husam_Death01'),
(44577, 4, 0, 'Insolent rats!', 14, 0, 0, 0, 0, 21889, 'VO_TV_Husam_Kill02');

-- High Prophet Barim
-- DELETE FROM `script_texts` WHERE `entry` IN (-1877004,-1877005,-1877006,-1877023,-1877024);
DELETE FROM `creature_text` WHERE `entry`=43612;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(43612, 0, 0, 'Begone infidels, you are not welcome here!', 14, 0, 0, 0, 0, 19735, 'VO_TV_Barim_Engage01'),
(43612, 1, 0, 'May peace find you now.', 14, 0, 0, 0, 0, 19738, 'VO_TV_Barim_Kill01'),
(43612, 2, 0, 'Kneel before me and repent!', 14, 0, 0, 0, 0, 19737, 'VO_TV_Barim_Event02'),
(43612, 2, 1, 'The Heavens take you!', 14, 0, 0, 0, 0, 19736, 'VO_TV_Barim_Event01'),
(43612, 3, 0, 'Death is only the beginning!', 14, 0, 0, 0, 0, 19733, 'VO_TV_Barim_Death');

-- Augh
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1877020 AND -1877007;
DELETE FROM `creature_text` WHERE `entry`=49045;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(49045, 0, 0, 'Bwaaaah! You no take da treasure!!!', 14, 0, 100, 0, 0, 0, 'Augh'),
(49045, 1, 0, 'Bwagauugh!!! Augh feed you to da crocs!!!', 12, 0, 100, 0, 0, 0, 'Augh'),
(49045, 2, 0, 'Gwaaaaaaaaaaaahhh!!!', 12, 0, 100, 0, 0, 0, 'Augh'),
(49045, 3, 0, 'Augh steal your treasure. Uhn uhn uhnnn!', 14, 0, 100, 0, 0, 0, 'Augh'),
(49045, 4, 0, 'GAAAH! How you kill croc?!', 14, 0, 100, 0, 0, 0, 'Augh'),
(49045, 5, 0, 'Augh smart! Augh already steal treasure while you no looking!', 14, 0, 100, 0, 0, 0, 'Augh');

-- Siamat
-- DELETE FROM `script_texts` WHERE `entry` IN (-1877011,-1877012,-1877013,-1877025,-1877026,-1877027);
DELETE FROM `creature_text` WHERE `entry`=44819;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(44819, 0, 0, 'I. AM. UNLEASHED!', 14, 0, 100, 0, 0, 20231, 'VO_TV_Siamat_Intro01'),
(44819, 1, 0, 'Winds of the south, rise and come to your masters aid!', 14, 0, 100, 0, 0, 20227, 'VO_TV_Siamat_Engage01'),
(44819, 2, 0, 'Cower before the tempest storm!', 14, 0, 100, 0, 0, 20228, 'VO_TV_Siamat_Event01'),
(44819, 2, 1, 'Suffer the storm!', 14, 0, 100, 0, 0, 20229, 'VO_TV_Siamat_Event02'),
(44819, 2, 2, 'Your city will be buried! Your lives forfeit to the elements! ', 14, 0, 100, 0, 0, 20230, 'VO_TV_Siamat_Event03'),
(44819, 3, 0, 'Nothing more than dust in the wind.', 14, 0, 100, 0, 0, 20232, 'VO_TV_Siamat_Kill01'),
(44819, 4, 0, 'The sky... Beckons...', 14, 0, 100, 0, 0, 20226, 'VO_TV_Siamat_Death01');

-- Frightened Citizen
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1977018 AND -1977004;
DELETE FROM `creature_text` WHERE `entry` IN (34981,35836);
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(34981,0,0,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","Protect me, please!"),
(34981,0,1,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","It''s coming right for me!"),
(34981,0,2,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","What in the world? Let''s get out of here!"),
(34981,0,3,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","Help!"),
(34981,0,4,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","Help me, please!"),
(34981,0,5,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","Worgen! Worgen everywhere!"),
(34981,0,6,12,0,100,"Quest Evacuate the Merchant Square NPC_J_CITIZEN_RANDOM_SAY","Flee! They''re everywhere!"),
(35836,0,0,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","Protect me, please!"),
(35836,0,1,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","It''s coming right for me!"),
(35836,0,2,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","What in the world? Let''s get out of here!"),
(35836,0,3,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","Help!"),
(35836,0,4,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","Help me, please!"),
(35836,0,5,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","Worgen! Worgen everywhere!"),
(35836,0,6,12,0,100,"Quest Evacuate the Merchant Square NPC_CW_CITIZEN_RANDOM_SAY","Flee! They''re everywhere!");

-- Lord Godfrey
-- DELETE FROM `script_texts` WHERE `entry` = -1977024;
DELETE FROM `creature_text` WHERE `entry`=35115;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(35115,0,0,12,0,100,"Lord Godfrey NPC_LORD_GODFREY_QOD_SAY","We ought to leave Crowley in prison with those beasts!");

-- King Genn Greymane
-- DELETE FROM `script_texts` WHERE `entry` = -1977025;
DELETE FROM `creature_text` WHERE `entry`=35112;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(35112,0,0,12,0,100,"King Genn Greymane NPC_KING_GENN_GREYMANE_QOD","Enough! I've made up my mind. We need Crowley on our side.");

-- Josiah Avery
-- DELETE FROM `script_texts` WHERE `entry` BETWEEN -1977063 AND -1977069;
DELETE FROM `creature_text` WHERE `entry`=35369;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(35369,0,0,12,0,100,"Quest The Rebel Lord''s Arsenal RANDOM_JOSIAH_YELL","My face! What''s wrong with my face!"),
(35369,0,1,12,0,100,"Quest The Rebel Lord''s Arsenal RANDOM_JOSIAH_YELL","My hands... don''t look at my hands!"),
(35369,0,2,12,0,100,"Quest The Rebel Lord''s Arsenal RANDOM_JOSIAH_YELL","What''s wrong with me??!"),
(35369,0,3,12,0,100,"Quest The Rebel Lord''s Arsenal RANDOM_JOSIAH_YELL","Make it stop!"),
(35369,0,4,12,0,100,"Quest The Rebel Lord''s Arsenal RANDOM_JOSIAH_YELL","I can''t fight it!"),
(35369,1,0,12,0,100,"Quest The Rebel Lord''s Arsenal SAY_WORGEN_BITE","The pain is unbearable!");