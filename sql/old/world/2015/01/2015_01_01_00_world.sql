

update creature_loot_template set ChanceOrQuestChance=0.5 where entry=154;
update creature_loot_template set ChanceOrQuestChance=19 where entry=454;
update creature_loot_template set ChanceOrQuestChance=0.2 where entry=42357;

update creature_template set QuestItem1=57786 where entry in (1109,199,154);
update creature_template set QuestItem1=57788 where entry in (157,454,42357);

delete from creature_questender where id=42750 and quest=26286;
UPDATE `item_template` SET `StartQuest`=26286 WHERE `entry` = 58111;
update creature_template set QuestItem1=58111,QuestItem2=725 where entry in (124,501,452,54371,54372,54373);
update creature_template set npcflag=640 where entry in (3625,22654);

delete from creature_queststarter where id=234 and quest in(26291,26320);

update quest_template set RequiredNpcOrGo1=42652 where Id=26287;
update creature_template set KillCredit1=42652 where entry in (124,452,501,54371,54372,54373);

