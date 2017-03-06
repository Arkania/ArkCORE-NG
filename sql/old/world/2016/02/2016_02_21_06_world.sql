
-- fix part issue #83 

-- http://www.wowhead.com/npc=29631/awilo-longomba  guid 227218
update gameobject_loot_template set Chance=99, QuestRequired=1 where entry=192824;
update gameobject_loot_template set Chance=59, QuestRequired=1 where entry=192825;

-- http://de.wowhead.com/npc=43239/razgar
delete from fishing_loot_template where entry=5332 and item=58945;
insert into fishing_loot_template values
(5332, 58945, 0, 17, 1, 1, 1, 1, 1, "");

-- http://de.wowhead.com/quest=26572/elektrisierender-einfall
UPDATE quest_template SET Flags=131080 WHERE Id=25236;
UPDATE quest_template SET RequiredSourceItemId1=58955, RequiredSourceItemId2=58958, RequiredSourceItemId3=0, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=1, RequiredSourceItemCount3=0, RequiredSourceItemCount4=0 WHERE Id=26572;
UPDATE quest_template SET Flags=134348808 WHERE Id=25236;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Gor dem Vollstrecker bei der Blockade von Dranosh'ar in Durotar zurück.", QuestGiverTextWindow_loc3="Ertrunkene Donnerechse", QuestGiverTargetName_loc3="Ertrunkene Donnerechse" WHERE Id=25236;


