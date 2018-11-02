-- TEST Dragon egg chest.
update `gameobject_template` set `data1`=175770 where `entry`=175770;
delete from `gameobject_loot_template` where `Entry`=175770;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('175770','62513','0','100','1','1','0','1','1','PLACEHOLDER');

-- Splintered Dragon Bone.Added in patch 5.4.2.17645.
update `gameobject_template` set `data1`=193047 where `entry`=193047;
delete from `gameobject_loot_template` where `Entry`=193047;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('193047','36730','0','100','1','1','0','1','1','placeholder');

-- Small Termite Mound.Quest
update `gameobject_template` set `data1`=178804 where `entry`=178804;
delete from `gameobject_loot_template` where `Entry`=178804;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('178804','15043','0','100','1','1','0','15','30',NULL);

-- Unfortunate Snobold.Added in patch 5.4.2.17645
update `gameobject_template` set `data1`=191604 where `entry`=191604;
delete from `gameobject_loot_template` where `Entry`=191604;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('191604','46886','0','100','1','1','0','1','1','PLACEHOLDER');

-- Tin Vein.
update `gameobject_template` set `data1`=103709 where `entry`=103709;
delete from `gameobject_loot_template` where `Entry`=103709;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('103709','1206','0','4','0','1','0','1','1',NULL),
('103709','1210','0','3','0','1','0','1','1',NULL),
('103709','1529','0','1','0','1','0','1','1',NULL),
('103709','1705','0','3','0','1','0','1','1',NULL),
('103709','2771','0','100','0','1','0','1','9',NULL),
('103709','2836','0','80','0','1','0','1','13',NULL);

-- Suspicious Outhouse.Quest
update `gameobject_template` set `data1`=184309 where `entry`=184309;
delete from `gameobject_loot_template` where `Entry`=184309;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('184309','29361','0','100','1','1','0','1','1',NULL);

-- Sunfury Torch.-Added in patch 5.4.2.17645.
update `gameobject_template` set `data1`=184251 where `entry`=184251;
delete from `gameobject_loot_template` where `Entry`=184251;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('184251','5134','0','100','1','1','0','1','1','PLACEHOLDER');

-- Shipment of Iron.DEPRECIATED Quest.
update `gameobject_template` set `data1`=1736 where `entry`=1736;
delete from `gameobject_loot_template` where `Entry`=1736;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('1736','3564','0','100','1','1','0','1','1',NULL);

-- Seaweed Frond.Added in patch 5.4.2.17645.
update `gameobject_template` set `data1`=201562 where `entry`=201562;
delete from `gameobject_loot_template` where `Entry`=201562;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('201562','5569','0','100','0','1','0','1','1','PLACEHOLDER');

-- Rusty Armor.Added in patch 5.4.2.17645.
update `gameobject_template` set `data1`=193046 where `entry`=193046;
delete from `gameobject_loot_template` where `Entry`=193046;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('193046','5134','0','100','0','1','0','1','1','PLACEHOLDER');

-- Rich Saronite Vein.
update `gameobject_template` set `data1`=193954 where `entry`=193954;
delete from `gameobject_loot_template` where `Entry`=193954;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('193954','36912','0','100','0','1','0','5','7',NULL),
('193954','36917','0','8','0','1','0','1','1',NULL),
('193954','36918','0','0.8','0','1','0','1','1',NULL),
('193954','36920','0','8','0','1','0','1','1',NULL),
('193954','36921','0','0.8','0','1','0','1','1',NULL),
('193954','36923','0','8','0','1','0','1','1',NULL),
('193954','36924','0','0.8','0','1','0','1','1',NULL),
('193954','36926','0','8','0','1','0','1','1',NULL),
('193954','36927','0','0.8','0','1','0','1','1',NULL),
('193954','36929','0','8','0','1','0','1','1',NULL),
('193954','36930','0','0.9','0','1','0','1','1',NULL),
('193954','36932','0','9','0','1','0','1','1',NULL),
('193954','36933','0','0.7','0','1','0','1','1',NULL),
('193954','37701','0','49','0','1','0','2','8',NULL),
('193954','37703','0','50','0','1','0','2','8',NULL);

-- Pile o' Gold. Added in patch 5.4.2.17645. 185525
update `gameobject_template` set `data1`=185525 where `entry`=185525;
delete from `gameobject_loot_template` where `Entry`=185525;
insert into `gameobject_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) values
('185525','5134','0','100','1','1','0','1','1',NULL);

-- Petrified Dragon Bone. Added in patch 5.4.2.17645, Disable loot.
update `gameobject_template` set `data1`=0 where `entry` in(188647,141872);













