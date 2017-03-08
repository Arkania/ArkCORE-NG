
-- npc had too high value.
UPDATE `creature_template` SET `Health_mod`=2 WHERE `entry`=12160;
-- Fix for quests 26948/26949 class quests.
UPDATE `quest_template` SET `QuestGiverPortrait`=34003,`QuestGiverTextWindow`="Wounded Sentinel",`QuestGiverTargetName`="Wounded Sentinel",`RequiredNpcOrGo1`=44617 WHERE `id`=26948;
UPDATE `quest_template` SET `QuestGiverPortrait`=34003,`QuestGiverTextWindow`="Wounded Sentinel",`QuestGiverTargetName`="Wounded Sentinel",`RequiredNpcOrGo1`=44617 WHERE `id`=26949;
-- trainer updates from DBC
UPDATE `npc_trainer` SET reqlevel=8 WHERE  spell=122;
UPDATE `npc_trainer` SET reqskill=8 WHERE  spell=2136;
UPDATE `npc_trainer` SET reqlevel=5 WHERE  spell=2136;
UPDATE `npc_trainer` SET reqlevel=3,reqskill=26 WHERE spell=100;
UPDATE `npc_trainer` SET reqlevel=26,reqskill=26 WHERE spell=7384;
UPDATE `npc_trainer` SET reqlevel=7,reqskill=6 WHERE spell=116;
UPDATE `npc_trainer` SET reqlevel=14,reqskill=237 WHERE spell=118;
UPDATE `npc_trainer` SET reqlevel=18,reqskill=6 WHERE spell=120;
UPDATE `npc_trainer` SET reqlevel=8,reqskill=6 WHERE spell=122;
UPDATE `npc_trainer` SET reqlevel=16,reqskill=237 WHERE spell=1953;
UPDATE `npc_trainer` SET reqlevel=9,reqskill=237 WHERE spell=2139;
UPDATE `npc_trainer` SET reqlevel=26,reqskill=8 WHERE spell=2948;
UPDATE `npc_trainer` SET reqlevel=68,reqskill=237 WHERE spell=6117;
UPDATE `npc_trainer` SET reqlevel=7,reqskill=574 WHERE spell=339;
UPDATE `npc_trainer` SET reqlevel=5,reqskill=574 WHERE spell=467;
UPDATE `npc_trainer` SET reqlevel=8,reqskill=134 WHERE spell=768;
UPDATE `npc_trainer` SET reqlevel=5,reqskill=613 WHERE spell=17;
UPDATE `npc_trainer` SET reqlevel=4,reqskill=78 WHERE spell=589;
