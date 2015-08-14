

delete from creature where id=28768;
delete from creature_addon  where guid in (236928, 236929, 236930, 236931, 236932, 236933, 236934, 236935, 236936, 236937, 236938);
delete from creature_addon  where guid in (236954, 236955, 236956, 236957, 236958, 236959, 236960, 236961, 236962, 236963, 236964);

UPDATE creature_template SET npcflag=16777216, rangeattacktime=2000, mechanic_immune_mask=8388624, dynamicflags=0 WHERE entry=28782;
update creature_template set AIName="", ScriptName="npc_acherus_deathcharger_28782" where entry=28782;

update creature_template set faction=2084 where entry=28406;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Unwürdiger Initiand", QuestGiverTargetName_loc3="Unwürdiger Initiand" WHERE Id=12848;



