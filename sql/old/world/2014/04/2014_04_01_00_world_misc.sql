
-- quest proving pit
-- delete wrong questgiver
delete from creature_queststarter where id=39062 and quest in (24642,24754,24762,24768,24774,24780,24786,26276);
delete from creature_queststarter where id=38142 and quest in (24642,24754,24762,24768,24774,24780,24786,26276);
UPDATE quest_template SET Method=2 WHERE Id in (24642,24754,24762,24768,24774,24780,24786,26276);

-- append creature text
update creature_text set text="Get into the pit and show us your stuff, $Gboy:girl;." where entry=39062 and groupid=0 and id=0;

-- insert scriptname
update creature_template set AIName="", ScriptName="npc_darkspear_jailor" where entry=39062;
update creature_template set AIName="", ScriptName="npc_captive_spitescale_scout" where entry=38142;

-- creature_text for entry 38142
delete from creature_text where entry=38142 and groupid=0 and id between 0 and 3;
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) values 
(38142,0,0,"I sshal ssslaughter you, Darksspear runt!",12,0,100,0,0,0,""),
(38142,0,1,"I sshal tasste your blood, landling.",12,0,100,0,0,0,""),
(38142,0,2,"The Sssea Witch will kill you all.",12,0,100,0,0,0,""),
(38142,0,3,"They sssend you to your death, youngling.",12,0,100,0,0,0,"");

update creature set MovementType=1, spawndist=10 where id=38141;
update creature_template set AIName="",ScriptName="npc_docile_island_boar" where entry=38141;
update creature_template set AIName="",ScriptName="npc_wildmane_cat" where entry=38046;
