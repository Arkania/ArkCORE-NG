-- Venomlash Scorpid (7022, 147422, GUID: 15455792)]

set @GUID=147422;

update creature set spawndist=0, MovementType=2 where guid=@GUID;

insert ignore into creature_addon (guid) value (@GUID);
update creature_addon set path_id=@GUID where guid=@GUID;

delete from waypoint_data where id=@GUID;
insert into waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -169.125336, 322.002625, -51.315723, 0.003922, 3000),
(@GUID, 1, -161.421249, 322.214417, -49.810696, 0.027484, 0),
(@GUID, 2, -155.385193, 318.027985, -48.970108, 5.741256, 0),
(@GUID, 3, -149.978104, 320.725311, -48.829430, 0.357350, 0),
(@GUID, 4, -148.418396, 323.990448, -47.835899, 1.154529, 0),
(@GUID, 5, -142.419067, 331.270233, -44.752796, 0.781464, 3000),
(@GUID, 6, -148.418396, 323.990448, -47.835899, 1.154529, 0),
(@GUID, 7, -149.978104, 320.725311, -48.829430, 0.357350, 0),
(@GUID, 8, -155.385193, 318.027985, -48.970108, 5.741256, 0),
(@GUID, 9, -161.421249, 322.214417, -49.810696, 0.027484, 0);
