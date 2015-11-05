
UPDATE creature_template SET questItem1=62053, questItem2=0 WHERE entry=7023;

-- wrong references
update creature_loot_template set MincountOrRef=1 where item in (866, 1625, 3787, 3832, 4022, 4044, 7975);

-- old loot from quest
delete from creature_loot_template where item=8053;

-- close the door
update gameobject set state=1 where guid in (188058, 188032);

-- set echomok's door to autoclose 5 sec.
update gameobject_template set data2=5000 where entry=124370;

-- 

DELETE FROM pool_template WHERE entry=14141;
INSERT INTO pool_template VALUES (14141,3,"MP Stonevault Mauler");

DELETE FROM pool_template WHERE entry=14142;
INSERT INTO pool_template VALUES (14142,3,"PP Stonevault Mauler");

DELETE FROM pool_pool WHERE pool_id=14142 and mother_pool=14141;
INSERT INTO pool_pool VALUES (14142, 14141, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147254;
INSERT INTO pool_creature VALUES (147254,14142,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147257;
INSERT INTO pool_creature VALUES (147257,14142,0,"Stonevault Flameweaver");

DELETE FROM pool_creature WHERE guid=147256;
INSERT INTO pool_creature VALUES (147256,14142,0,"Stonevault Flameweaver");

DELETE FROM pool_creature WHERE guid=147271;
INSERT INTO pool_creature VALUES (147271,14142,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147272;
INSERT INTO pool_creature VALUES (147272,14142,0,"Stonevault Flameweaver");

-- 

update gameobject_template set AIName="", ScriptName="go_ironaya_seal_door_124372" where entry=124372;

UPDATE locales_quest SET OfferRewardText_loc3="Macht Euch keine Sorgen weger der legendären Kammer, meine Jungs sind vor Ort!  Ihr habt wichtigeres zu tun!" WHERE Id=27672;

UPDATE `creature_template` SET `unit_flags`=0 where `entry`=28221;

delete from gameobject_loot_template where entry=123329;
insert into gameobject_loot_template values
(123329, 7740, 100, 1, 1, 1, 1),
(123329, 69841, 14, 1, 1, 1, 1),
(123329, 69839, 14, 1, 1, 1, 1),
(123329, 69840, 14, 1, 1, 1, 1);




