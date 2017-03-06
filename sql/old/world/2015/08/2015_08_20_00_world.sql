
UPDATE quest_template SET SourceSpellId=52275 WHERE Id=12687;

delete from creature_text where entry=28788;
insert into creature_text values
(28788, 0, 0, "Impressive, death knight. Return to me in the world of the living for your reward.", 12, 0, 100, 0, 0, 0, "",28835);

update creature_template set AIName="", ScriptName="npc_salanar_the_horseman_28653" where entry=28653;
update creature_template set AIName="", ScriptName="npc_salanar_the_horseman_28788" where entry=28788;
update creature_template set AIName="", ScriptName="npc_dark_rider_of_acherus_28768" where entry=28768;

delete from npc_spellclick_spells where npc_entry=28782;
insert into npc_spellclick_spells values 
(28782, 52280, 1, 0);

delete from quest_poi where questid=12687 and id=0 and objIndex=-1;

update creature_text set BroadcastTextID=29266 where entry=28406 and groupid=0 and id=7;
update creature_text set BroadcastTextID=29263 where entry=28406 and groupid=0 and id=3;
update creature_text set BroadcastTextID=29267 where entry=28406 and groupid=0 and id=8;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Scharlachroter Ghul", QuestGiverTargetName_loc3="Scharlachroter Ghul" WHERE Id=12698;

delete from creature where guid=237877;

update creature_text set BroadcastTextID=28899 where entry=28841 and groupid=1 and id=0;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Bürgermeister Quimby", QuestGiverTargetName_loc3="Bürgermeister Quimby" WHERE Id=12719;
UPDATE quest_template SET RequiredItemId1=39362, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=12719;



