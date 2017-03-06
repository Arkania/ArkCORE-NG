
update creature_template_addon set auras="80816" where entry=43194;

update creature set spawntimesecs=120 where id in (341, 648, 649, 650, 651, 652, 653, 43094, 43196, 43197);

update creature_addon set bytes1=4 where guid=61128;

SET @WP=431971;
DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9270.795,-2299.455,69.8349,0.0,0,0,0,100),
(@WP,1,-9271.545,-2309.705,70.0849,0.0,0,0,0,100),
(@WP,2,-9279.795,-2319.205,67.0849,0.0,0,0,0,100),
(@WP,3,-9304.045,-2330.455,61.5849,0.0,0,0,0,100),
(@WP,4,-9324.86,-2338.94,61.2445,0.0,0,0,0,100),
(@WP,5,-9323.752,-2341.33,61.2445,5.086,0,0,0,100);

SET @WP=431972;
DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9308.439,-2330.975,61.716,0.0,0,0,0,100),
(@WP,1,-9292.939,-2325.475,62.716,0.0,0,0,0,100),
(@WP,2,-9276.939,-2316.725,68.966,0.0,0,0,0,100),
(@WP,3,-9260.689,-2312.725,75.216,0.0,0,0,0,100),
(@WP,4,-9237.689,-2313.225,78.716,0.0,0,0,0,100),
(@WP,5,-9214.52,-2334.01,83.6875,0.0,0,0,0,100);


update creature_addon set auras="80698" where guid in (34444,33943,33790,34335,34086,34217,33827,33989);

update creature_template_addon set auras="80615" where entry=43194;



