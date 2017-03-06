
-- fix issue #114

set @GUID=10083;
set @ID=164759;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 10.928241, 3.364799, 6.097200, 4.856187, 300, 255, 1);

set @GUID=10084;
set @ID=164760;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 11.606291, 0.102354, 6.098372, 1.749937, 300, 255, 1);

set @GUID=10085;
set @ID=164761;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 14.675901, -0.120680, 6.097804, 3.909786, 300, 255, 1);

set @GUID=10086;
set @ID=164762;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 12.208157, -2.591444, 6.099893, 0.772117, 300, 255, 1);

set @GUID=10087;
set @ID=164763;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 16.500662, -1.214721, 6.098497, 0.776045, 300, 255, 1);

set @GUID=10088;
set @ID=164764;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 19.018456, 1.048604, 6.096811, 3.8980085, 300, 255, 1);

set @GUID=10089;
set @ID=164765;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 6.333239, -8.790290, 6.098568, 3.053703, 300, 255, 1);

set @GUID=10090;
set @ID=164766;
delete from gameobject where guid=@GUID and id=@ID;
insert into gameobject (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, animprogress, state) values 
(@GUID, @ID, 593, 35.060139, 5.306768, 6.094744, 3.108675, 300, 255, 1);


delete from gameobject where guid in (175554, 175555, 175556, 175557, 175558, 175559, 175560, 175561, 175562);

delete from gameobject where guid in (177790, 177791, 177792, 177793, 177794, 177795, 177796, 177797, 177798);









