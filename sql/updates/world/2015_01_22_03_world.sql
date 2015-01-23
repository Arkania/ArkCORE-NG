
-- http://wowdata.buffed.de/npc/Kazon-584
update creature set modelid=0 where guid in (647,648) and id=584;  -- modelid invisible???

-- http://wowdata.buffed.de/npc/Chatter-616
update creature_template set modelid1=821, modelid2=37620 where entry=616; 
update creature set modelid=821 where id=616;

-- http://wowdata.buffed.de/npc/Rohh-der-Schweigsame-947  -- modelid invisible???
update creature_template set modelid1=10792, modelid2=37623 where entry=947; 
delete from creature where guid between 621 and 632 and id=947;
update creature set modelid=10792 where guid=45624 and id=947;

-- http://wowdata.buffed.de/npc/Sucher-Aqualon-14269
update creature_template set modelid1=525,modelid2=37624, InhabitType=4,HoverHeight=2.0  where entry=14269;
delete from creature where guid=34503;
insert INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES 
(34503, 14269, 0, 1, 1, 37624, 0, -9449.9, -3301.54, 3.65667, 4.29351, 120, 0, 0, 1, 0, 0, 0, 0, 0);

-- http://wowdata.buffed.de/npc/Kalmarrik-14270
delete from creature where guid between 578 and 607 and id=14270;   -- modelid invisible???

-- http://wowdata.buffed.de/npc/Rippenbrecher-14271  -- modelid invisible???
update creature_template set modelid1=500, modelid2=37621 where entry=14271;  
delete from creature where guid between 633 and 646 and id=14271;
update creature set modelid=0 where guid=44306 and id=14271;

-- http://wowdata.buffed.de/npc/Fletschzahn-14272
update creature_template set modelid1=497, modelid2=6378 where entry=14272;
delete from creature where guid between 608 and 618 and id=14272;
update creature set modelid=0 where guid=44277 and id=14272;

-- http://wowdata.buffed.de/npc/Felsenherz-14273  -- modelid invisible???

-- http://www.wowhead.com/item=58898/dirt-stained-scroll
DELETE FROM `creature_loot_template` WHERE (`entry`=580) AND (`item`=58898);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(580, 58898, 10, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=430) AND (`item`=58898);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(430, 58898, 10, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=445) AND (`item`=58898);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(445, 58898, 10, 1, 0, 1, 1);

DELETE FROM `creature_loot_template` WHERE (`entry`=446) AND (`item`=58898);
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
(446, 58898, 10, 1, 0, 1, 1);

-- http://www.wowhead.com/npc=652/bridge-worker-matthew
update creature_addon set path_id=0 where guid=34086;

















