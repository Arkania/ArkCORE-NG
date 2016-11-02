
-- Rocket Sling gossip, Wild Overlook.
UPDATE`gossip_menu_option` SET `OptionBroadcastTextId`=36458,option_id=1,npc_option_npcflag=1 WHERE `menu_id`=10808;

-- 99% Wild Overlook objects.
UPDATE `gameobject` SET phaseids="179" WHERE `id`IN(196439,196444,196427,196449,196451,196433,196436,196420,196435,196438,196443,196843,196422,196426,196446,196448,196452,196431,196421,196424,196434,196432);

-- ships rowing boats.
UPDATE `gameobject` SET phaseids="171 179" WHERE `id` IN(196828,196827,196826,196825,196824,196822,196823,196820,196821,196818,196819);

-- disable gravity flag, Cyclone Vehicle.
UPDATE `creature_template` SET `InhabitType`=4 WHERE `entry`=36178;

-- spell script for monster say.
DELETE FROM `spell_scripts` WHERE `id`=68439 AND `dataint`=40144;
INSERT INTO `spell_scripts` (`id`,`effIndex`,`delay`,`command`,`datalong`,`datalong2`,`dataint`,`x`,`y`,`z`,`o`) VALUES 
(68439,0,0,0,3,0,40144,0,0,0,0);

delete from creature where guid=246155;

update creature set position_x=967.56,  position_y=3794.57, position_z=16.574, orientation=1.2984 where guid=248091;



