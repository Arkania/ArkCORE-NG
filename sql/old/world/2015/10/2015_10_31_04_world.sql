-- Jadespine Basilisk (4863, 147424, GUID: 15455793)]

set @GUID=147424;

update creature set spawndist=0, MovementType=2 where guid=@GUID;

insert ignore into creature_addon (guid) value (@GUID);
update creature_addon set path_id=@GUID where guid=@GUID;

delete from waypoint_data where id=@GUID;
insert into waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -182.282089, 302.861084, -51.295162, 1.339100, 3000),
(@GUID, 1, -179.991013, 314.902863, -53.041176, 1.343027, 0),
(@GUID, 2, -176.442764, 323.921570, -51.890625, 0.722563, 0),
(@GUID, 3, -169.613297, 324.681549, -51.102123, 0.062828, 0),
(@GUID, 4, -162.790512, 323.100098, -49.872612, 6.055417, 3000),
(@GUID, 5, -169.613297, 324.681549, -51.102123, 0.062828, 0),
(@GUID, 6, -176.442764, 323.921570, -51.890625, 0.722563, 0),
(@GUID, 7, -179.991013, 314.902863, -53.041176, 1.343027, 0);
