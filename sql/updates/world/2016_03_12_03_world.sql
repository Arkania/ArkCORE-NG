
-- zone duskhaven
update creature_template set AIName="", ScriptName="npc_krennan_aranas_36331" where entry=36331;

update creature set phaseMask=1 where guid in (250021, 250081, 252045);
update creature set phaseMask=2 where guid in (252040);

update creature set position_x=-1822.732300, position_y=2296.914551, position_z=42.183014, orientation=5.631314 where guid=250021;
update creature set position_x=-1821.155273, position_y=2291.075195, position_z=42.141243, orientation=0.997465 where guid=250081;
update creature set position_x=-1822.739502, position_y=2293.689209, position_z=42.054314, orientation=0.196356 where guid=252045;

update creature_text set emote=1, BroadcastTextID=36341 where entry=36332 and groupid=1 and id=0;

update quest_template set RewardSpell=0 where id=14375;

UPDATE locales_quest SET Details_loc3="Sprecht nochmal mit König Genn Graumähne." WHERE Id=14375;



