
-- fix some console errors
delete from smart_scripts where entryorguid in (190549, 195327, 203133, 203136, 101811, 101831, 101832, 101833, 101834, 18900, 18901);

delete from smart_scripts where entryorguid in (47649, 34503, 34544, 27717, 1756, 643, 197, 448, 2297900, 27699, 34846);

delete from smart_scripts where entryorguid in (456, 1038, 4971, 5254, 5475, 5848, 5863, 5863, 5863, 6047);

UPDATE `creature_template` SET `gossip_menu_id`=6944 WHERE `entry`=37888; -- Frax Bucketdrop 
UPDATE `creature_template` SET `gossip_menu_id`=12032 WHERE `entry`=44232; -- Janice Myers 
UPDATE `creature_template` SET `gossip_menu_id`=6944 WHERE `entry`=44230; -- Richard Trueflight
UPDATE `creature_template` SET `gossip_menu_id`=12022 WHERE `entry`=45417; -- Fiona
UPDATE `creature_template` SET `gossip_menu_id`=12035 WHERE `entry`=45400; -- Fiona's Caravan 
UPDATE `creature_template` SET `gossip_menu_id`=6944 WHERE `entry`=44233; -- William Kielar Jr. 
UPDATE `creature_template` SET `gossip_menu_id`=12086 WHERE `entry`=45828; -- Argent Apothecary Judkins 
UPDATE `creature_template` SET `gossip_menu_id`=3626, `npcflag`=147, `dynamicflags`=0 WHERE `entry`=11557; -- Meilosh 
UPDATE `creature_template` SET `gossip_menu_id`=3625, `npcflag`=643, `dynamicflags`=0 WHERE `entry`=11555; -- Gorn One Eye 
UPDATE `creature_template` SET `gossip_menu_id`=6801, `dynamicflags`=0 WHERE `entry`=11558; -- Kernda 
 
update gossip_menu_option set id=0 where menu_id=3626 and id=2;
delete from gossip_menu_option where menu_id=3625 and id=1;
delete from gossip_menu_option where menu_id=3624 and id=1;

