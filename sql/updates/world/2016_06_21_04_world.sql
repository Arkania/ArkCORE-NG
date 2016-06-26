

delete from conditions where SourceGroup=7938;

delete from conditions where SourceGroup=7939;

UPDATE creature_template SET gossip_menu_id=0, AIName="", ScriptName="npc_vlagga_freyfeather_18930" WHERE entry=18930;

UPDATE creature_template SET gossip_menu_id=0, AIName="", ScriptName="npc_amish_wildhammer_18931" WHERE entry=18931;

delete from smart_scripts where entryorguid=18930;

delete from smart_scripts where entryorguid=18931;

update creature_text set BroadcastTextID=16456 where entry=19308 and groupid=0 and id=0;

update creature_text set BroadcastTextID=16454 where entry=19308 and groupid=0 and id=2;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Höllengeist", QuestGiverTargetName_loc3="Höllengeist" WHERE Id=10909;

UPDATE quest_template SET Method=2, PrevQuestId=10903, RequiredItemId1=31772, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=10909;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10916;

UPDATE quest_template SET PrevQuestId=10903, RequiredSourceItemId1=31799, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=10916;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Oberst Jules", QuestGiverTargetName_loc3="Oberst Jules" WHERE Id=10935;

UPDATE quest_template SET PrevQuestId=10909, RequiredItemId1=31828, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=10935;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10058;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=10106;

UPDATE quest_template SET RequiredMinRepFaction=946, RequiredMaxRepFaction=947, RequiredMaxRepValue=41999, RequiredRaces=2098253 WHERE Id=10106;

UPDATE quest_template SET RequiredMinRepFaction=947, RequiredMaxRepFaction=947, RequiredMaxRepValue=41999, RequiredRaces=946 WHERE Id=10110;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=13408;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=13409;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=13410;

UPDATE locales_quest SET EndText_loc3="" WHERE Id in (10106, 10110, 13408, 13409, 13410, 13411);


