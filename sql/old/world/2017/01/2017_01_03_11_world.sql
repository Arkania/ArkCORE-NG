
UPDATE creature_addon SET emote=0 WHERE guid=286189;

UPDATE creature_template SET ScriptName="npc_brett_coins_mcquid_37762" WHERE entry=37762;

UPDATE creature_template SET ScriptName="npc_sally_salvager_sandscrew_37761" WHERE entry=37761;

DELETE FROM creature_addon WHERE guid=248943;

INSERT INTO creature_addon VALUES (248943, 0, 0, 0, 1, 431, ""); 

UPDATE creature SET phaseGroup=562 WHERE guid=283980;

delete from creature where id=35294 and guid in (285643,285638);

UPDATE quest_template SET Flags=2621440 WHERE Id=14124;

delete from creature where id=34830 and guid in (283869,283876, 283872);

UPDATE quest_template SET RequiredNpcOrGo1=44175, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=3, RequiredNpcOrGoCount2=0 WHERE Id=14009;

UPDATE creature_template SET ScriptName="npc_injured_employee_48305" WHERE entry=48305;

DELETE FROM creature_addon WHERE guid=283872;
DELETE FROM creature_addon WHERE guid=283876;
DELETE FROM creature_addon WHERE guid=283869;
DELETE FROM creature_addon WHERE guid=285638;
DELETE FROM creature_addon WHERE guid=285643;

delete from creature_queststarter where id=34874 and quest=28349;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Baron Küstenschipper", QuestGiverTargetName_loc3="Baron Küstenschipper" WHERE Id=14046;

UPDATE quest_template SET QuestGiverTextWindow="Baron Longshore", QuestGiverTargetName="Baron Longshore" WHERE Id=14046;

update quest_template set NextQuestIdChain=24502 where Id=24488;
update quest_template set NextQuestIdChain=24503 where Id=24502;
update quest_template set NextQuestIdChain=24520 where Id=24503;
update quest_template set NextQuestIdChain=14115 where Id=14113;
update quest_template set NextQuestIdChain=14116 where Id=14115;
update quest_template set NextQuestIdChain=14120 where Id=14116;
update quest_template set NextQuestIdChain=14014 where Id=14474;
update quest_template set NextQuestIdChain=14248 where Id=14014;
update quest_template set NextQuestIdChain=14234 where Id=14031;
update quest_template set NextQuestIdChain=14234 where Id=14233;
update quest_template set NextQuestIdChain=14235 where Id=14234;
update quest_template set NextQuestIdChain=14236 where Id=14235;
update quest_template set NextQuestIdChain=14303 where Id=14236;
update quest_template set NextQuestIdChain=14237 where Id=14303;
update quest_template set NextQuestIdChain=14238 where Id=14237;
update quest_template set NextQuestIdChain=14240 where Id=14238;
update quest_template set NextQuestIdChain=14241 where Id=14240;
update quest_template set NextQuestIdChain=14242 where Id=14241;
update quest_template set NextQuestIdChain=14326 where Id=14242;
update quest_template set NextQuestIdChain=14243 where Id=14326;
update quest_template set NextQuestIdChain=14445 where Id=14243;
update quest_template set NextQuestIdChain=14244 where Id=14445;
update quest_template set NextQuestIdChain=14245 where Id=14244;
update quest_template set NextQuestIdChain=24671 where Id=27139;
update quest_template set NextQuestIdChain=24817 where Id=24816;
update quest_template set NextQuestIdChain=24856 where Id=24817;
update quest_template set NextQuestIdChain=24858 where Id=24856;
update quest_template set NextQuestIdChain=24864 where Id=24858;
update quest_template set NextQuestIdChain=24868 where Id=24864;
update quest_template set NextQuestIdChain=24897 where Id=24868;
update quest_template set NextQuestIdChain=24901 where Id=24897;
update quest_template set NextQuestIdChain=24924 where Id=24901;
update quest_template set NextQuestIdChain=24937 where Id=24925;
update quest_template set NextQuestIdChain=24937 where Id=24929;
update quest_template set NextQuestIdChain=24940 where Id=24937;
update quest_template set NextQuestIdChain=24942 where Id=24940;
update quest_template set NextQuestIdChain=24952 where Id=24942;
update quest_template set NextQuestIdChain=24954 where Id=24952;
update quest_template set NextQuestIdChain=24958 where Id=24954;
update quest_template set NextQuestIdChain=25023 where Id=24958;
update quest_template set NextQuestIdChain=25024 where Id=25023;
update quest_template set NextQuestIdChain=25066 where Id=25058;
update quest_template set NextQuestIdChain=25098 where Id=25066;
update quest_template set NextQuestIdChain=25099 where Id=25098;
update quest_template set NextQuestIdChain=25100 where Id=25099;
update quest_template set NextQuestIdChain=25109 where Id=25100;
update quest_template set NextQuestIdChain=25110 where Id=25109;
update quest_template set NextQuestIdChain=25125 where Id=25122;
update quest_template set NextQuestIdChain=25184 where Id=25125;
update quest_template set NextQuestIdChain=25200 where Id=25184;
update quest_template set NextQuestIdChain=25204 where Id=25200;
update quest_template set NextQuestIdChain=25207 where Id=25204;
update quest_template set NextQuestIdChain=25213 where Id=25207;
update quest_template set NextQuestIdChain=25251 where Id=25243;
update quest_template set NextQuestIdChain=25265 where Id=25251;
update quest_template set NextQuestIdChain=25266 where Id=25265;
update quest_template set NextQuestIdChain=25267 where Id=25266;


