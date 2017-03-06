
-- fix issue #113  remove random movement
update creature set  spawndist=0, MovementType=0 where guid=5776 and id=1740;

