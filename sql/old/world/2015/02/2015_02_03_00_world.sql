

DELETE FROM `creature_addon` WHERE `guid` in (9352,9353,9354,9355,9356,9357);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(9352, 0, 0, 65536, 0, 0, "81201"),
(9353, 0, 0, 65536, 0, 0, "81201"),
(9354, 0, 0, 65536, 0, 0, "81201"),
(9355, 0, 0, 65536, 0, 0, "81201"),
(9356, 0, 0, 65536, 0, 0, "81201"),
(9357, 0, 0, 0, 0, 0, "80694 80815 81201");

update creature set spawntimesecs=120 WHERE `guid` in (9352,9353,9354,9355,9356);

update creature_template set AIName="", ScriptName="", VehicleId=963 where entry=43443;
update creature_template set AIName="", ScriptName="vehicle_keeshans_riverboat_43450" where entry=43450;
update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43449" where entry=43449;
update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43457" where entry=43457;
update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43458" where entry=43458;

-- waypoint for keeshan riverboat.. startet by script..
SET @WP=43450;
DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9300.98,-2363.67,55.66713,0.0,0,0,0,100),
(@WP,1,-9319.45,-2381.07,55.3839,0.0,0,0,0,100),
(@WP,2,-9349.95,-2416.14,55.3839,0.0,0,0,0,100),
(@WP,3,-9373.91,-2457.97,55.3839,0.0,0,0,0,100),
(@WP,4,-9403.5,-2515.62,55.3839,0.0,0,0,0,100),
(@WP,5,-9409.03,-2558.76,55.3839,0.0,0,0,0,100),
(@WP,6,-9416.4,-2617.67,55.3839,0.0,0,0,0,100),
(@WP,7,-9416.39,-2668.8,55.3839,0.0,0,0,0,100),
(@WP,8,-9411.74,-2732.56,55.3839,0.0,0,0,0,100),
(@WP,9,-9395.99,-2796.17,55.3839,0.0,0,0,0,100),
(@WP,10,-9404,-2831.58,55.3839,0.0,0,0,0,100),
(@WP,11,-9423.828,-2839.637,56.4091,0.0,0,0,0,100);

update quest_template set RequiredNpcOrGo1=0, RequiredNpcOrGoCount1=0, Flags=8, SpecialFlags=2, ObjectiveText1="Reach Camp Everstill in Redridge." where Id=26616;

DELETE FROM `creature_addon` WHERE `guid` in (9351, 26548, 26578, 26641, 26645);
INSERT INTO `creature_addon` (`guid`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES 
(9351, 0, 0, 65536, 0, 0, "81240 81266 81496"),
(26548, 0, 0, 65544, 0, 0, "81240 81266 81496"),
(26578, 0, 0, 65536, 0, 0, "81240 81266 81496"),
(26641, 0, 0, 65536, 0, 0, "81240 81266 81496"),
(26645, 0, 0, 65536, 0, 0, "81240 81266 81496");

update creature set position_x=-9462.13, position_y=-2828.65, position_z=65.276, orientation=2.54589, MovementType=0, spawndist=0 where id=43458; 
update creature set position_x=-9467.15, position_y=-2827.66, position_z=65.279, orientation=0.14650, MovementType=0, spawndist=0 where id=43459; 
update creature set position_x=-9465.10, position_y=-2830.68, position_z=65.279, orientation=1.48560, MovementType=0, spawndist=0 where id=43460; 
update creature set position_x=-9463.04, position_y=-2824.79, position_z=65.278, orientation=4.31696, MovementType=0, spawndist=0 where id=43461; 
update creature set position_x=-9465.74, position_y=-2824.94, position_z=65.278, orientation=5.16519, MovementType=0, spawndist=0 where id=43462; 







