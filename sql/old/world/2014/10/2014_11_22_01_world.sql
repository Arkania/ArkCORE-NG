
update creature set MovementType=2 where guid=189003 and id=16159;

update creature_addon set path_id=1890030 where guid=189003;

delete from waypoint_data where id=1890030;
insert into waypoint_data values (1890030, 0, -11088.339844, -1932.493164, 49.889282, 0, 1000, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 1, -11117.701172, -1954.608643, 49.889027, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 2, -11138.834961, -1959.594971, 49.887486, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 3, -11147.347656, -1954.754028, 49.889977, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 4, -11162.427734, -1925.241699, 49.884281, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 5, -11161.058594, -1916.108765, 49.888916, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 6, -11134.595703, -1898.381592, 49.888916, 0, 1000, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 7, -11161.058594, -1916.108765, 49.888916, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 8, -11162.427734, -1925.241699, 49.884281, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 9, -11147.347656, -1954.754028, 49.889977, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 10, -11138.834961, -1959.594971, 49.887486, 0, 0, 0, 0, 100, 0);
insert into waypoint_data values (1890030, 11, -11117.701172, -1954.608643, 49.889027, 0, 0, 0, 0, 100, 0);



