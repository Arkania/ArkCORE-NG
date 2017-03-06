
-- fixing issue #79
UPDATE quest_template SET SpecialFlags=0 WHERE Id=10617;

UPDATE creature_template SET faction=14, speed_walk=1, InhabitType=4 WHERE entry=21373;

UPDATE creature_template SET InhabitType=4 WHERE entry=21840;

UPDATE creature_template SET faction=1738, InhabitType=4 WHERE entry=21470;

UPDATE creature_template SET InhabitType=5 WHERE entry=21839;

UPDATE creature_template SET InhabitType=5 WHERE entry=20749;

delete from creature where id=21731;

update creature set modelid=20024 where id=21819;

update creature set modelid=11686 where id=21422;

update creature set modelid=19595 where id=20845;

UPDATE creature_template SET InhabitType=5 WHERE entry=21123;

UPDATE creature_template SET InhabitType=5 WHERE entry=22268;


