
UPDATE creature_template SET ScriptName="npc_prince_liam_greymane_38474" WHERE entry=38474;

delete from creature where id=38474;

update creature_text set type=14 where entry=38469 and groupid=3 and id=0;

update creature_text set type=14 where entry=38469 and groupid=1 and id=0;

update creature set spawndist=0, MovementType=0 where id=38469 and guid=18585;

DELETE FROM creature_addon WHERE guid=251894;

DELETE FROM waypoint_data WHERE id=3846901;
INSERT INTO waypoint_data VALUES 
(3846901, 0, -1659.570, 1620.006, 20.48808, 0.24366, 0, 0, 0, 0, 0),
(3846901, 1, -1631.088, 1621.131, 20.48824, 0.039456, 0, 0, 0, 0, 0),
(3846901, 2, -1631.993, 1651.859, 20.48824, 1.563129, 0, 0, 0, 0, 0);

UPDATE quest_template SET RequiredNpcOrGo1=38854 WHERE Id=24904;



