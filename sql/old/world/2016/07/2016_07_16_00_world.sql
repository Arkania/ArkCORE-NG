
/*  issue #161
-- Query: SELECT * FROM gameobject_loot_template WHERE entry=208814
LIMIT 0, 1000
--http://www.wowhead.com/quest=29313/the-secret-to-perfect-kimchi
--add missing loot template and enable loot in gobj.
--Dodger
-- Date: 2016-07-06 17:13
*/
delete from gameobject_loot_template where entry=208814 and item=69898;
INSERT INTO gameobject_loot_template (Entry,Item,Reference,Chance,QuestRequired,LootMode,GroupId,MinCount,MaxCount,Comment) VALUES 
(208814,69898,0,100,1,1,0,1,1,NULL);

UPDATE gameobject_template SET data1=208814,questItem1=69898 WHERE entry=208814;


