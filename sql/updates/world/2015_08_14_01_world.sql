
UPDATE quest_template SET RequiredNpcOrGoCount1=5, RequiredSourceItemId1=39253, RequiredSourceItemId4=0, RequiredSourceItemCount1=1, RequiredSourceItemCount4=0 WHERE Id=12698;

update creature_template set AIName="", ScriptName="npc_gothik_the_harvester_28658" where entry=28658;

DELETE FROM spell_bonus_data WHERE entry=85692;
INSERT INTO `spell_bonus_data` VALUES (85692, 1.36, 0, 0, 0, 'Warlock - Doomguard Doom Bolt');

update creature_addon set emote=0, auras=52147 where guid in (237731, 237732, 237733, 237734, 237735, 237740, 237741, 237742, 237743, 237744);
update creature_addon set auras=52147 where guid in (237745, 237746, 237747, 237748, 237749, 237750, 237751, 237752);

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Naja.. nicht alle sehen gleich aus, aber es ist die gleiche Uniform! Tötet sie alle!", QuestGiverTargetName_loc3="Scharlachroter Flottenverteidiger" WHERE Id=12701;

update creature_template set AIName="", ScriptName="npc_scarlet_ghoul_28845" where entry=28845;
update creature_template set AIName="", ScriptName="npc_scarlet_miner_cart_28817" where entry=28817;
update creature_template set AIName="", ScriptName="npc_scarlet_miner_28841" where entry=28841;

update creature_text set BroadcastTextID=29048 where entry=28907 and groupid=0 and id=0;
update creature_text set BroadcastTextID=29049 where entry=28907 and groupid=1 and id=0;
update creature_text set BroadcastTextID=29051 where entry=28907 and groupid=3 and id=0;
update creature_text set BroadcastTextID=29052 where entry=28907 and groupid=4 and id=0;
update creature_text set BroadcastTextID=29058 where entry=28907 and groupid=8 and id=0;
update creature_text set BroadcastTextID=29059 where entry=28907 and groupid=9 and id=0;
update creature_text set BroadcastTextID=29056 where entry=28907 and groupid=10 and id=0;
update creature_text set BroadcastTextID=29061 where entry=28907 and groupid=12 and id=0;
update creature_text set BroadcastTextID=29057 where entry=28907 and groupid=13 and id=0;
update creature_text set BroadcastTextID=29060 where entry=28907 and groupid=14 and id=0;

update creature_template set faction=16, unit_class=2, Exp=3 where entry in (41948, 51119, 51120, 51121);
update creature_template set Exp=3 where entry in (41576, 49973, 49979, 49985);
update creature_template set Exp=3 where entry in (52409, 53797, 53798, 53799);

UPDATE creature_template SET pickpocketloot=20051 WHERE entry=20051;

update skinning_loot_template set ChanceOrQuestChance=50 where entry=12899 and item=4304;

update creature set position_x=2319.13, position_y=-5736.79, position_z=153.92, orientation=0.669 where guid=238562;
delete from smart_scripts where entryorguid in (28907, 2890700);
update creature_template set AIName="", ScriptName="npc_prince_valanar_28907" where entry=28907;







