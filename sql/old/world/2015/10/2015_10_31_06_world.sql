-- Shrike Bat (GUID: 15456141)]

set @GUID=147418;

update creature set spawndist=0, MovementType=2 where guid=@GUID;

insert ignore into creature_addon (guid) value (@GUID);
update creature_addon set path_id=@GUID where guid=@GUID;

delete from waypoint_data where id=@GUID;
insert into waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -85.981575, 350.232697, -49.769001, 3.114105, 3000),
(@GUID, 1, -98.386490, 351.689117, -48.819595, 2.756748, 0),
(@GUID, 2, -113.445534, 353.306091, -45.396049, 2.949171, 0),
(@GUID, 3, -128.014313, 335.376434, -43.861382, 3.993750, 3000),
(@GUID, 4, -113.445534, 353.306091, -45.396049, 2.949171, 0),
(@GUID, 5, -98.386490, 351.689117, -48.819595, 2.756748, 0);
