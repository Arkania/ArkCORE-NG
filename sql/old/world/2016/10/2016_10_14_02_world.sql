
UPDATE gameobject_loot_template SET QuestRequired=1 WHERE entry=195201 AND item=46828;

UPDATE quest_template SET ExclusiveGroup=14001 WHERE Id=14001;

UPDATE quest_template SET ExclusiveGroup=14001 WHERE Id=14474;

UPDATE quest_template SET PrevQuestId=-14014, NextQuestId=0, ExclusiveGroup=0, Flags=0 WHERE Id=14019;

UPDATE quest_template SET PrevQuestId=-14014, NextQuestId=0, ExclusiveGroup=0 WHERE Id=14473;

DELETE FROM `creature_queststarter` WHERE `id`=35650;
INSERT INTO `creature_queststarter` (`id`,`quest`) VALUES
(35650,14014),
(35650,14234),
(35650,14248);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Teraptorjunges", QuestGiverTargetName_loc3="Teraptorjunges" WHERE Id=14473;

UPDATE quest_template SET QuestGiverPortrait=30187, QuestGiverTextWindow="Bomb-Throwing Monkey", QuestGiverTargetName="Bomb-Throwing Monkey" WHERE Id=14019;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Bombenwerfender Affe", QuestGiverTargetName_loc3="Bombenwerfender Affe" WHERE Id=14019;

UPDATE creature_template SET ScriptName="npc_bomb_throwing_monkey_34699" WHERE entry=34699;

delete from spell_linked_spell where spell_trigger=66142;
insert into spell_linked_spell values 
(66142, 8858, 1, "Bomb-Throwing Monkey");

UPDATE quest_template SET RequiredSourceItemId1=49028, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=14019;

