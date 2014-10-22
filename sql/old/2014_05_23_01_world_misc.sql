
update creature_template set AIName="", ScriptName="npc_crowley_horse_phase8" where entry=44427;
update creature_template set AIName="", ScriptName="npc_crowley_horse_1round_phase8" where entry=44428;
update creature_template set AIName="", ScriptName="npc_crowley_horse_2round_phase8" where entry=35231;
update creature_template set AIName="", ScriptName="npc_lord_darius_crowley_summon_phase8" where entry=35230;
update creature_template set AIName="", ScriptName="npc_bloodfang_stalker_phase8" where entry=35230;

UPDATE quest_template SET NextQuestIdChain=0, Flags=0, SpecialFlags=0, RequiredNpcOrGo1=35582, RequiredNpcOrGoCount1=1 WHERE Id=14212;


