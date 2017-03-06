

-- fix issue #135
delete from quest_poi where questId=14398 and id=0;

delete from quest_poi where questId=14399 and id=1;

delete from creature where id=36461 and guid=251519;

delete from creature_text where entry=36461 and groupid=0;

update creature_template set AIName="", ScriptName="npc_chance_36459" where entry=36459;

UPDATE creature_template SET npcflag=16777216 WHERE entry=36459;

delete from npc_spellclick_spells where npc_entry=36459 and spell_id=43689; 
delete from npc_spellclick_spells where npc_entry=36459 and spell_id=68743; 
insert into npc_spellclick_spells values
(36459, 68743, 1, 0);

update creature_loot_template set QuestRequired=1 where entry=36461 and item=49281;

delete from quest_poi where questId=14401 and id=1;

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14400;

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14401;

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14404;

UPDATE quest_template SET PrevQuestId=14397, NextQuestId=0, ExclusiveGroup=0 WHERE Id=14406;

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14416;

delete from quest_poi where questId=14404 and id=3;


