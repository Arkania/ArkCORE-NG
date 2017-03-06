
update creature_template set AIName="", ScriptName="npc_renders_valley_camera" where entry=43618;

SET @WP=43618;
DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9636.17,-3476.182,122.9651,0.0,0,0,0,100),
(@WP,1,-9649.17,-3455.182,122.9651,0.0,0,0,0,100),
(@WP,2,-9648.17,-3423.182,118.9651,0.0,0,0,0,100),
(@WP,3,-9600.77,-3290.79,118.67,0.0,0,0,0,100),
(@WP,4,-9647.77,-3250.79,118.67,0.0,0,0,0,100),
(@WP,5,-9663.41,-3221.29,118.969,0.0,0,0,0,100),
(@WP,6,-9662.41,-3114.79,133.302,0.0,0,0,0,100),
(@WP,7,-9723.61,-3076.8,144.747,0.0,0,0,0,100),
(@WP,8,-9771.52,-3108,144.747,0.0,0,0,0,100),
(@WP,9,-9790.64,-3182.29,148.414,0.0,0,0,0,100),
(@WP,10,-9722.16,-3256.83,145.692,0.0,0,0,0,100),
(@WP,11,-9653.33,-3264.69,146.969,0.0,0,0,0,100),
(@WP,12,-9663.528,-3220.006,113.1663,0.0,0,0,0,100),
(@WP,13,-9662.882,-3198.597,116.8296,0.0,0,0,0,100),
(@WP,14,-9662.406,-3193.194,117.8118,0.0,0,0,0,100),
(@WP,15,-9658.686,-3137.969,128.4617,0.0,0,0,0,100),
(@WP,16,-9670.788,-3101.805,136.3173,0.0,0,0,0,100),
(@WP,17,-9672.171,-3100.325,136.6848,0.0,0,0,0,100),
(@WP,18,-9675.633,-3097.028,137.5267,0.0,0,0,0,100),
(@WP,19,-9783.902,-3130.975,146.0245,0.0,0,0,0,100),
(@WP,20,-9792.888,-3167.863,148.0745,0.0,0,0,0,100),
(@WP,21,-9722.574,-3256.58,145.6966,0.0,0,0,0,100),
(@WP,22,-9683.456,-3265.419,146.1606,0.0,0,0,0,100),
(@WP,23,-9678.353,-3265.378,146.2926,0.0,0,0,0,100),
(@WP,24,-9619.15,-3323.56,121.743,0.0,0,0,0,100),
(@WP,25,-9643.15,-3456.56,121.743,0.0,0,0,0,100),
(@WP,26,-9638.15,-3472.56,121.743,0.0,0,0,0,100);

update creature_template set InhabitType=4 where entry=43618;

SET @CGUID=269885;
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+0 AND @CGUID+49;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `MovementType`) VALUES
(@CGUID+0, 43639, 0, 1, 1, -9711.4, -3177.91, 58.69363, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+1, 43639, 0, 1, 1, -9706.88, -3203.73, 58.73793, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+2, 43639, 0, 1, 1, -9748.49, -3222.49, 64.37774, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+3, 43639, 0, 1, 1, -9750.97, -3222.22, 62.56533, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+4, 43639, 0, 1, 1, -9678.96, -3185.24, 61.89243, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+5, 43639, 0, 1, 1, -9761.71, -3213, 59.07093, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+6, 43639, 0, 1, 1, -9743.54, -3218.09, 63.44853, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+7, 43639, 0, 1, 1, -9645.43, -3254.5, 48.69893, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+8, 43639, 0, 1, 1, -9748.05, -3190.01, 75.41183, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+9, 43639, 0, 1, 1, -9734.24, -3190.78, 91.05894, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+10, 43639, 0, 1, 1, -9707.13, -3176.16, 58.78423, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+11, 43639, 0, 1, 1, -9726.37, -3181.92, 60.10133, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+12, 43639, 0, 1, 1, -9658.72, -3201.41, 48.78183, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+13, 43639, 0, 1, 1, -9686.5, -3205.22, 70.73643, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+14, 43639, 0, 1, 1, -9729.21, -3186.02, 82.09763, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+15, 43639, 0, 1, 1, -9744.52, -3184.06, 92.15424, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+16, 43639, 0, 1, 1, -9710.2, -3232.89, 87.91634, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+17, 43639, 0, 1, 1, -9673.47, -3195.14, 57.68893, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+18, 43639, 0, 1, 1, -9629.98, -3178.69, 55.79793, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+19, 43639, 0, 1, 1, -9795.77, -3237.37, 60.22393, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+20, 43639, 0, 1, 1, -9698.55, -3221.25, 62.66623, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+21, 43639, 0, 1, 1, -9730.17, -3180.57, 75.64433, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+22, 43639, 0, 1, 1, -9710.72, -3132.82, 58.73643, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+23, 43639, 0, 1, 1, -9713.17, -3127.67, 59.99253, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+24, 43639, 0, 1, 1, -9718.31, -3119.87, 77.61124, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+25, 43639, 0, 1, 1, -9750.54, -3142.47, 83.57774, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+26, 43639, 0, 1, 1, -9739.61, -3174.16, 75.63544, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+27, 43639, 0, 1, 1, -9709.29, -3118.84, 69.19124, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+28, 43639, 0, 1, 1, -9761.64, -3163.18, 58.69863, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+29, 43639, 0, 1, 1, -9810.29, -3206.12, 60.77693, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+30, 43639, 0, 1, 1, -9780.46, -3189.95, 58.69213, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+31, 43639, 0, 1, 1, -9701.97, -3158.67, 58.69213, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+32, 43639, 0, 1, 1, -9794.13, -3203.44, 80.49043, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+33, 43639, 0, 1, 1, -9811.86, -3204.99, 65.32474, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+34, 43639, 0, 1, 1, -9734.41, -3171.97, 60.74753, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+35, 43639, 0, 1, 1, -9796.03, -3180.38, 63.49613, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+36, 43639, 0, 1, 1, -9711.25, -3126.45, 71.08014, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+37, 43639, 0, 1, 1, -9719.54, -3164.21, 59.38283, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+38, 43639, 0, 1, 1, -9690.43, -3161.28, 60.77583, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+39, 43639, 0, 1, 1, -9728.69, -3127.69, 58.75583, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+40, 43639, 0, 1, 1, -9724.27, -3153.3, 73.31223, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+41, 43639, 0, 1, 1, -9721.18, -3155.63, 64.73704, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+42, 43639, 0, 1, 1, -9734.65, -3178.74, 92.20203, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+43, 43639, 0, 1, 1, -9725.72, -3126.97, 59.88663, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+44, 43639, 0, 1, 1, -9795.45, -3178.91, 61.70153, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+45, 43639, 0, 1, 1, -9780.15, -3158.31, 69.95783, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+46, 43639, 0, 1, 1, -9734.03, -3182.35, 59.64493, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+47, 43639, 0, 1, 1, -9772.02, -3192.66, 61.71133, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+48, 43639, 0, 1, 1, -9731.29, -3119.59, 69.98293, 0, 120, 0, 0), -- Explosion Trigger (Area: Redridge Mountains)
(@CGUID+49, 43639, 0, 1, 1, -9648.93, -3136.66, 49.23403, 0, 120, 0, 0); -- Explosion Trigger (Area: Redridge Mountains)

update creature set modelid=11686 where id=43639;







