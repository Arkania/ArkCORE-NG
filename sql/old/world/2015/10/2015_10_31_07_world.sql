-- Jadespine Basilisk (GUID: 15456097)]

set @GUID=147375;

update creature set spawndist=0, MovementType=2 where guid=@GUID;

insert ignore into creature_addon (guid) value (@GUID);
update creature_addon set path_id=@GUID where guid=@GUID;

delete from waypoint_data where id=@GUID;
insert into waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -140.169220, 289.470154, -46.493088, 1.606135, 3000),
(@GUID, 1, -140.017044, 299.851318, -46.142406, 1.531523, 0),
(@GUID, 2, -140.991730, 312.871735, -44.463497, 1.672894, 0),
(@GUID, 3, -140.996460, 325.183990, -44.508984, 1.127042, 0),
(@GUID, 4, -127.469795, 335.338867, -43.891937, 0.624388, 3000),
(@GUID, 5, -140.996460, 325.183990, -44.508984, 1.127042, 0),
(@GUID, 6, -140.991730, 312.871735, -44.463497, 1.672894, 0),
(@GUID, 7, -140.017044, 299.851318, -46.142406, 1.531523, 0);


