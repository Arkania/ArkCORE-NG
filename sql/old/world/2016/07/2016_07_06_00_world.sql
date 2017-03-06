

delete from creature_equip_template where entry=50570 and id=1;
insert into creature_equip_template values 
(50570, 1, 1117, 0, 0);

update creature set equipment_id=1 where guid=253411 and id=50570;

UPDATE quest_template SET RequiredSourceItemId1=49944, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=24616;

update creature_template set AIName="", ScriptName="" where entry=37195;

update creature_template set AIName="", ScriptName="npc_tobias_mistmantle_38051" where entry=38051;

DELETE FROM creature_text WHERE entry=37195 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(37195, 0, 0, "Lorna!", 14, 0, 100, 1, 0, 19511, "crowley", 38641);

UPDATE creature_template SET minlevel=5, maxlevel=5 WHERE entry=38051;

DELETE FROM creature_text WHERE entry=38051 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(38051, 1, 0, "It will be done!", 12, 0, 100, 1, 0, 0, "say tobias", 37812);

DELETE FROM creature_text WHERE entry=37195 AND groupid=2 AND id=0;
INSERT INTO creature_text VALUES 
(37195, 2, 0, "Does this toad speak for you, Genn?  Do you come to our dwelling as a friend?  Or do you come as a tyrant?", 14, 0, 100, 1, 0, 19510, "crowley", 38640);

DELETE FROM creature_text WHERE entry=37195 AND groupid=3 AND id=0;
INSERT INTO creature_text VALUES 
(37195, 3, 0, "Aye, Genn.  It is not law that binds us.  It is something far stronger.  My men are ready to give their lives under your command.", 12, 0, 100, 1, 0, 19512, "crowley", 38642);

