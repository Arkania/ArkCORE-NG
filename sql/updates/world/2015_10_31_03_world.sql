-- Shrike Bat (4861, 147427, 0, GUID: 15455795)]

set @GUID=147427;

update creature set spawndist=0, MovementType=2 where guid=@GUID;

insert ignore into creature_addon (guid) value (@GUID);
update creature_addon set path_id=@GUID where guid=@GUID;

delete from waypoint_data where id=@GUID;
insert into waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -195.991684, 264.598297, -49.445580, 1.056354, 3000),
(@GUID, 1, -189.374374, 275.123718, -48.512939, 1.205580, 0),
(@GUID, 2, -186.675919, 284.310242, -47.983326, 1.264485, 0),
(@GUID, 3, -184.914047, 291.103485, -48.333965, 1.335171, 0),
(@GUID, 4, -185.537109, 295.037445, -49.834949, 1.617914, 0),
(@GUID, 5, -178.769714, 311.871460, -53.158562, 1.213434, 3000),
(@GUID, 6, -185.537109, 295.037445, -49.834949, 1.617914, 0),
(@GUID, 7, -184.914047, 291.103485, -48.333965, 1.335171, 0),
(@GUID, 8, -186.675919, 284.310242, -47.983326, 1.264485, 0),
(@GUID, 9, -189.374374, 275.123718, -48.512939, 1.205580, 0);

