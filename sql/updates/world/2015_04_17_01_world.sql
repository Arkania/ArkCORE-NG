
set @mpool=14501;
set @ppool=14501;

-- create mother pool = 14501
delete from pool_template where entry=@mpool;
insert into pool_template values(@mpool,17,"Master");

-- create 17 pool id's 
delete from pool_template where entry between @ppool+1 and @ppool+17;
insert into pool_template values
(@ppool+1,1,"Pool 1"),
(@ppool+2,1,"Pool 2"),
(@ppool+3,1,"Pool 3"),
(@ppool+4,1,"Pool 4"),
(@ppool+5,1,"Pool 5"),
(@ppool+6,1,"Pool 6"),
(@ppool+7,1,"Pool 7"),
(@ppool+8,1,"Pool 8"),
(@ppool+9,1,"Pool 9"),
(@ppool+10,1,"Pool 10"),
(@ppool+11,1,"Pool 11"),
(@ppool+12,1,"Pool 12"),
(@ppool+13,1,"Pool 13"),
(@ppool+14,1,"Pool 14"),
(@ppool+15,1,"Pool 15"),
(@ppool+16,1,"Pool 16"),
(@ppool+17,1,"Pool 17");

delete from pool_pool where mother_pool=@mpool and pool_id between @ppool+1 and @ppool+17;
insert into pool_pool values
(@ppool+1, @mpool, 0, "Pool 1"),
(@ppool+2, @mpool, 0, "Pool 2"),
(@ppool+3, @mpool, 0, "Pool 3"),
(@ppool+4, @mpool, 0, "Pool 4"),
(@ppool+5, @mpool, 0, "Pool 5"),
(@ppool+6, @mpool, 0, "Pool 6"),
(@ppool+7, @mpool, 0, "Pool 7"),
(@ppool+8, @mpool, 0, "Pool 8"),
(@ppool+9, @mpool, 0, "Pool 9"),
(@ppool+10, @mpool, 0, "Pool 10"),
(@ppool+11, @mpool, 0, "Pool 11"),
(@ppool+12, @mpool, 0, "Pool 12"),
(@ppool+13, @mpool, 0, "Pool 13"),
(@ppool+14, @mpool, 0, "Pool 14"),
(@ppool+15, @mpool, 0, "Pool 15"),
(@ppool+16, @mpool, 0, "Pool 16"),
(@ppool+17, @mpool, 0, "Pool 17");

-- connect creatures to pools
delete from pool_creature where pool_entry between @ppool+1 and @ppool+17;
insert into pool_creature values
(95925, @ppool+1, 0, "Pool 1"),
(93316, @ppool+1, 0, "Pool 1"),

(93785, @ppool+2, 0, "Pool 2"),
(88035, @ppool+2, 0, "Pool 2"),

(88458, @ppool+3, 0, "Pool 3"),
(88838, @ppool+3, 0, "Pool 3"),

(88001, @ppool+4, 0, "Pool 4"),
(93899, @ppool+4, 0, "Pool 4"),
(89405, @ppool+4, 0, "Pool 4"),

(88238, @ppool+5, 0, "Pool 5"),
(88368, @ppool+5, 0, "Pool 5"),

(88232, @ppool+6, 0, "Pool 6"),
(88397, @ppool+6, 0, "Pool 6"),
(87994, @ppool+6, 0, "Pool 6"),

(139015, @ppool+7, 0, "Pool 7"),
(99425, @ppool+7, 0, "Pool 7"),
(99424, @ppool+7, 0, "Pool 7"),

(99848, @ppool+8, 0, "Pool 8"),
(88095, @ppool+8, 0, "Pool 8"),

(88093, @ppool+9, 0, "Pool 9"),
(89482, @ppool+9, 0, "Pool 9"),

(93237, @ppool+10, 0, "Pool 10"),
(93630, @ppool+10, 0, "Pool 10"),

(88373, @ppool+11, 0, "Pool 11"),
(88756, @ppool+11, 0, "Pool 11"),
(93480, @ppool+11, 0, "Pool 11"),

(92719, @ppool+12, 0, "Pool 12"),
(88252, @ppool+12, 0, "Pool 12"),
(93975, @ppool+12, 0, "Pool 12"),

(93778, @ppool+13, 0, "Pool 13"),
(89567, @ppool+13, 0, "Pool 13"),

(89968, @ppool+14, 0, "Pool 14"),
(93659, @ppool+14, 0, "Pool 14"),

(89720, @ppool+15, 0, "Pool 15"),
(89331, @ppool+15, 0, "Pool 15"),

(92721, @ppool+16, 0, "Pool 16"),
(88935, @ppool+16, 0, "Pool 16"),
(88284, @ppool+16, 0, "Pool 16"),

(89913, @ppool+17, 0, "Pool 17"),
(92648, @ppool+17, 0, "Pool 17");

