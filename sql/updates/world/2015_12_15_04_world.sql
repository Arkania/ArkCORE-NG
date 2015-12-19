
-- import waypoints for npc 40650.. hatchery
set @GUID=120196;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4737.2, -2400.28, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4760.12, -2401.68, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4777.31, -2386.47, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4778.72, -2363.55, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4763.5, -2346.35, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4740.58, -2344.95, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4723.39, -2360.17, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4721.99, -2383.08, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4737.2, -2400.28, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4760.12, -2401.68, 804.997, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4777.31, -2386.47, 804.997, 0, 0, 0, 0, 100, 0);

set @GUID=120198;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4575.66, -2446.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4560.15, -2429.2, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4561.15, -2406.26, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4578.08, -2390.75, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4601.02, -2391.75, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4616.53, -2408.68, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4615.53, -2431.62, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4598.6, -2447.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4575.66, -2446.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4560.15, -2429.2, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4561.15, -2406.26, 775.756, 0, 0, 0, 0, 100, 0);

set @GUID=120202;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4668.79, -2367.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4685.72, -2351.99, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4686.72, -2329.05, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4671.21, -2312.12, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4648.27, -2311.12, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4631.34, -2326.63, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4630.34, -2349.57, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4645.85, -2366.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4668.79, -2367.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4685.72, -2351.99, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4686.72, -2329.05, 738.218, 0, 0, 0, 0, 100, 0);

set @GUID=120236;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4571.08, -2404.58, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4583.75, -2385.43, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4606.25, -2380.85, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4625.4, -2393.53, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4629.98, -2416.03, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4617.31, -2435.18, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4594.81, -2439.75, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4575.66, -2427.08, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4571.08, -2404.58, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4583.75, -2385.43, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4606.25, -2380.85, 799.078, 0, 0, 0, 0, 100, 0);

set @GUID=120238;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4704.58, -2330.32, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4710.33, -2352.55, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4698.67, -2372.33, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4676.45, -2378.08, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4656.66, -2366.43, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4650.91, -2344.2, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4662.57, -2324.42, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4684.8, -2318.67, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4704.58, -2330.32, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4710.33, -2352.55, 760.147, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4698.67, -2372.33, 760.147, 0, 0, 0, 0, 100, 0);

set @GUID=120240;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4773.56, -2542.51, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4778.14, -2520.01, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4765.46, -2500.86, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4742.96, -2496.28, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4723.82, -2508.96, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4719.24, -2531.46, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4731.91, -2550.6, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4754.41, -2555.18, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4773.56, -2542.51, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4778.14, -2520.01, 748.199, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4765.46, -2500.86, 748.199, 0, 0, 0, 0, 100, 0);

set @GUID=120242;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4678.6, -2496.73, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4657.39, -2505.52, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4648.6, -2526.73, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4657.39, -2547.94, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4678.6, -2556.73, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4699.81, -2547.94, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4708.6, -2526.73, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4699.81, -2505.52, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4678.6, -2496.73, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4657.39, -2505.52, 811.686, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4648.6, -2526.73, 811.686, 0, 0, 0, 0, 100, 0);

set @GUID=120244;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4648.92, -2461.91, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4671.84, -2463.31, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4689.04, -2448.1, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4690.44, -2425.18, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4675.22, -2407.98, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4652.3, -2406.58, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4635.11, -2421.79, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4633.71, -2444.71, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4648.92, -2461.91, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4671.84, -2463.31, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4689.04, -2448.1, 803.602, 0, 0, 0, 0, 100, 0);

set @GUID=120248;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4631.23, -2345.45, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4643.9, -2326.3, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4666.4, -2321.73, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4685.55, -2334.4, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4690.13, -2356.9, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4677.46, -2376.04, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4654.96, -2380.62, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4635.81, -2367.95, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4631.23, -2345.45, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4643.9, -2326.3, 787.256, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4666.4, -2321.73, 787.256, 0, 0, 0, 0, 100, 0);

set @GUID=120250;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4752.23, -2505.22, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4739.23, -2524.14, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4743.41, -2546.72, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4762.33, -2559.73, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4784.91, -2555.54, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4797.91, -2536.62, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4793.73, -2514.04, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4774.81, -2501.04, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4752.23, -2505.22, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4739.23, -2524.14, 800.094, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4743.41, -2546.72, 800.094, 0, 0, 0, 0, 100, 0);

set @GUID=120256;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4727.09, -2403.32, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4707.73, -2415.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4702.75, -2438.07, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4715.09, -2457.44, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4737.51, -2462.41, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4756.87, -2450.07, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4761.84, -2427.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4749.51, -2408.29, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4727.09, -2403.32, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4707.73, -2415.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4702.75, -2438.07, 754.748, 0, 0, 0, 0, 100, 0);

set @GUID=120260;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4660.63, -2410.8, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4664.81, -2388.22, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4651.81, -2369.3, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4629.23, -2365.12, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4610.31, -2378.12, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4606.13, -2400.7, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4619.13, -2419.62, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4641.71, -2423.8, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4660.63, -2410.8, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4664.81, -2388.22, 766.796, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4651.81, -2369.3, 766.796, 0, 0, 0, 0, 100, 0);

set @GUID=120299;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4599.88, -2438.22, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4613.54, -2419.76, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4636.25, -2416.37, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4654.7, -2430.03, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4658.1, -2452.74, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4644.44, -2471.19, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4621.73, -2474.59, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4603.27, -2460.93, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4599.88, -2438.22, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4613.54, -2419.76, 725.062, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4636.25, -2416.37, 725.062, 0, 0, 0, 0, 100, 0);

set @GUID=120301;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4693.68, -2439.73, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4698.26, -2417.23, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4685.58, -2398.08, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4663.08, -2393.5, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4643.94, -2406.18, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4639.36, -2428.68, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4652.03, -2447.82, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4674.53, -2452.4, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4693.68, -2439.73, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4698.26, -2417.23, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4685.58, -2398.08, 712.124, 0, 0, 0, 0, 100, 0);

set @GUID=120303;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4693.52, -2515.54, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4670.94, -2511.36, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4657.94, -2492.43, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4662.12, -2469.86, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4681.04, -2456.85, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4703.62, -2461.03, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4716.63, -2479.96, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4712.44, -2502.53, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4693.52, -2515.54, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4670.94, -2511.36, 707.63, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4657.94, -2492.43, 707.63, 0, 0, 0, 0, 100, 0);

set @GUID=120305;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4769.65, -2401.57, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4776.17, -2423.58, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4765.21, -2443.76, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4743.2, -2450.28, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4723.02, -2439.33, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4716.5, -2417.31, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4727.46, -2397.14, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4749.47, -2390.61, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4769.65, -2401.57, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4776.17, -2423.58, 714.963, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4765.21, -2443.76, 714.963, 0, 0, 0, 0, 100, 0);

set @GUID=120417;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4575.24, -2447.04, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4575.66, -2446.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4560.15, -2429.2, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4561.15, -2406.26, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4578.08, -2390.75, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4601.02, -2391.75, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4616.53, -2408.68, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4615.53, -2431.62, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4598.6, -2447.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4575.66, -2446.13, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4560.15, -2429.2, 775.756, 0, 0, 0, 0, 100, 0),
(@GUID, 12, 4561.15, -2406.26, 775.756, 0, 0, 0, 0, 100, 0);

set @GUID=120419;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4648.48, -2462.81, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4648.92, -2461.91, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4671.84, -2463.31, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4689.04, -2448.1, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4690.44, -2425.18, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4675.22, -2407.98, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4652.3, -2406.58, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4635.11, -2421.79, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4633.71, -2444.71, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4648.92, -2461.91, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4671.84, -2463.31, 803.602, 0, 0, 0, 0, 100, 0),
(@GUID, 12, 4689.04, -2448.1, 803.602, 0, 0, 0, 0, 100, 0);

set @GUID=120421;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4726.92, -2402.33, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4727.09, -2403.32, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4707.73, -2415.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4702.75, -2438.07, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4715.09, -2457.44, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4737.51, -2462.41, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4756.87, -2450.07, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4761.84, -2427.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4749.51, -2408.29, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4727.09, -2403.32, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4707.73, -2415.66, 754.748, 0, 0, 0, 0, 100, 0),
(@GUID, 12, 4702.75, -2438.07, 754.748, 0, 0, 0, 0, 100, 0);

set @GUID=120430;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4693.68, -2439.73, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4698.26, -2417.23, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4685.58, -2398.08, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4663.08, -2393.5, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4643.94, -2406.18, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4639.36, -2428.68, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4652.03, -2447.82, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4674.53, -2452.4, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4693.68, -2439.73, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4698.26, -2417.23, 712.124, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4685.58, -2398.08, 712.124, 0, 0, 0, 0, 100, 0);

set @GUID=120432;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4570.1, -2404.39, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4571.08, -2404.58, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4583.75, -2385.43, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4606.25, -2380.85, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4625.4, -2393.53, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4629.98, -2416.03, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4617.31, -2435.18, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4594.81, -2439.75, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4575.66, -2427.08, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4571.08, -2404.58, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4583.75, -2385.43, 799.078, 0, 0, 0, 0, 100, 0),
(@GUID, 12, 4606.25, -2380.85, 799.078, 0, 0, 0, 0, 100, 0);

set @GUID=120434;
update creature set spawndist=0, MovementType=2 where guid=@GUID;
delete from creature_addon where guid=@guid;
insert into creature_addon values (@GUID, @GUID, 0, 50331648, 1, 0, "");
update creature_addon set path_id=@GUID where guid=@GUID;
delete from waypoint_data where id=@GUID;
insert into waypoint_data values
(@GUID, 1, 4668.79, -2367.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 2, 4685.72, -2351.99, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 3, 4686.72, -2329.05, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 4, 4671.21, -2312.12, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 5, 4648.27, -2311.12, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 6, 4631.34, -2326.63, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 7, 4630.34, -2349.57, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 8, 4645.85, -2366.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 9, 4668.79, -2367.5, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 10, 4685.72, -2351.99, 738.218, 0, 0, 0, 0, 100, 0),
(@GUID, 11, 4686.72, -2329.05, 738.218, 0, 0, 0, 0, 100, 0);


