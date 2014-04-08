-- ----------------------------------
-- CATACLYSM DUNGEONS SCRIPTS --
-- ----------------------------------
-- Alizabal
-- DELETE FROM `script_texts` WHERE `entry` = -1900027;
DELETE FROM `creature_text` WHERE `entry`=55869 AND `groupid`=9;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(55869,9,0,16,0,100,"Alizabal SAY_BLADES","Alizabal goes into a deadly Blade Dance!");

-- Chimaeron
-- DELETE FROM `script_texts` WHERE `entry` IN (-1900028,-1851023,-1851026,-1851027,-1851028,-1851029);
DELETE FROM `creature_text` WHERE `entry` IN (43296, 44202);
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`type`,`sound`,`probability`,`comment`,`text`) VALUES
(43296,0,0,16,0,100,"Chimaeron SAY_MASSACRE","Chimaeron prepares to massacre his foes!"),
(44202,1,0,14,20833,100,"Finkle help SAY_INTRO","Help! I'm trapped in here!"),
(44202,2,0,14,20836,100,"Finkle systems failure SAY_SYSTEM_FAILURE","Poor little fella."),
(44202,3,0,14,20838,100,"Finkle chimaeron death SAY_DEATH","Great job guys! The key should be in his guts somewhere. Just, uh, fish around in there 'till you find it."),
(44202,4,0,14,20839,100,"Finkle systems failure SAY_F_OUTRO","Thanks for freeing me! I'm off to have more amazing adventures."),
(44202,5,0,14,20837,100,"Finkle p2 SAY_P2","Oh-oh! He looks pretty mad now!");