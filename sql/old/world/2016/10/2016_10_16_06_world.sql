
UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168800;

UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168801;

UPDATE creature_template SET InhabitType=4 WHERE entry=39169;

update creature set MovementType=2 where guid=249461;

delete from creature_addon where guid=249461;
insert into creature_addon values 
(249461, 249461, 0, 0, 1, 0, "73558 73561 76354");

DELETE FROM waypoint_data WHERE id=249461;
INSERT INTO waypoint_data VALUES 
(249461, 1, 559.0062, 3129.964, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 2, 560.0029, 3130.044, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 3, 326.5816, 3279.51, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 4, 382.7708, 3216.926, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 5, 482.934, 3142.681, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 6, 579.6129, 3132.812, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 7, 666.1511, 3179.648, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 8, 718.8976, 3261.208, 20.72534, 0, 0, 0, 0, 0, 0),
(249461, 9, 723.8906, 3347.63, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 10, 678.632, 3452.148, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 11, 580.7639, 3507.673, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 12, 449.382, 3560.323, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 13, 318.5156, 3572.397, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 14, 247.0243, 3493.674, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 15, 260.033, 3397.564, 21.91148, 0, 0, 0, 0, 0, 0),
(249461, 16, 326.5816, 3279.51, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 17, 352.5559, 3244.171, 20.72533, 0, 0, 0, 0, 0, 0),
(249461, 18, 382.7708, 3216.926, 20.72534, 0, 0, 0, 0, 0, 0);

UPDATE creature_template_addon SET auras="" WHERE entry=35810;

UPDATE creature_addon SET auras="" WHERE guid in (246036, 246037, 246038, 248205, 248206, 248207);

UPDATE creature_template SET unit_flags=294912, unit_flags2=2048 WHERE entry=35810;

UPDATE gossip_menu_option SET option_id=1, npc_option_npcflag=1, OptionBroadcastTextID=36520, action_menu_id=10823 WHERE menu_id=10677 AND id=1;

UPDATE creature_template SET gossip_menu_id=10677, dynamicflags=0, ScriptName="npc_foreman_dampwick_35769" WHERE entry=35769;

delete from conditions where SourceTypeOrReferenceId=15  and SourceGroup=10677 and SourceEntry=1;
insert into conditions values 
(15, 10677, 1, 0, 0, 28, 0, 14248, 0, 0, 0, 0, 0, "", "Refresh my Memory: quest 14248 completed"),
(15, 10677, 1, 0, 0, 8, 0, 14248, 0, 0, 1, 0, 0, "",  "Refresh my Memory: quest 14248 not rewardet");

UPDATE creature SET MovementType=2 WHERE guid=246038;
UPDATE creature_addon SET path_id=246038 WHERE guid=246038;

DELETE FROM waypoint_data WHERE id=246038;
INSERT INTO waypoint_data VALUES 
(246038, 0, 490.440, 2972.38, 8.043484, 0.906249, 0, 0, 0, 0, 0),
(246038, 1, 490.328, 2972.63, 8.043484, 0.906249, 5000, 0, 0, 0, 0),
(246038, 2, 488.877, 2978.847, 7.925544, 1.858938, 0, 0, 0, 0, 0),
(246038, 3, 486.2259, 2979.748, 7.851083, 2.813982, 0, 0, 0, 0, 0),
(246038, 4, 485.2679, 2978.036, 7.930794, 4.32823, 5000, 0, 0, 0, 0),
(246038, 5, 486.2259, 2979.748, 7.851083, 2.813982, 0, 0, 0, 0, 0),
(246038, 6, 488.877, 2978.847, 7.925544, 1.858938, 0, 0, 0, 0, 0);

UPDATE quest_template SET NextQuestId=0, ExclusiveGroup=0 WHERE Id=14021;
UPDATE quest_template SET Flags=262144, SpecialFlags=0 WHERE Id=14021;

UPDATE quest_template SET PrevQuestId=14248 WHERE Id=14031;

UPDATE creature_template_addon SET path_id=0 WHERE entry=35813;

UPDATE creature_template SET MovementType=0 WHERE entry=35813;

UPDATE creature_template SET ScriptName="npc_frightened_miner_35813" WHERE entry=35813;

delete from creature_queststarter where id=35769 and quest=14031;

DELETE FROM waypoint_data WHERE id=3581301;
INSERT INTO waypoint_data VALUES 
(3581301, 0, 493.008850, 2975.830566, 7.926551, 0.964395, 0, 0, 0, 100, 0),
(3581301, 1, 505.048004, 2986.213135, 7.264693, 0.697359, 0, 0, 0, 100, 0),
(3581301, 2, 519.035706, 2969.260498, 8.533081, 5.488284, 0, 0, 0, 100, 0),
(3581301, 3, 540.347900, 2948.988770, 4.148690, 5.637507, 0, 0, 0, 100, 0);

delete from conditions where SourceTypeOrReferenceId=19  and SourceGroup=0 and SourceEntry=14031;
insert into conditions values 
(19, 0, 14031, 0, 0, 9, 0, 14021, 0, 0, 0, 0, 0, "", "Allow accept 14031 after 14021 taken");

DELETE FROM waypoint_data WHERE id=3581302;
INSERT INTO waypoint_data VALUES 
(3581302, 0, 552.432800, 2937.236572, 1.571852, 5.437247, 0, 0, 0, 100, 0),
(3581302, 1, 563.873352, 2933.236816, 0.304662, 5.959532, 0, 0, 0, 100, 0),
(3581302, 2, 574.958923, 2950.648926, -0.871740, 1.011521, 0, 0, 0, 100, 0),
(3581302, 3, 582.405334, 2959.478027, -2.108325, 0.870150, 0, 0, 0, 100, 0),
(3581302, 4, 589.242859, 2963.726807, -2.587548, 0.555990, 0, 0, 0, 100, 0),
(3581302, 5, 589.342773, 2964.532715, -2.464861, 1.741942, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581303;
INSERT INTO waypoint_data VALUES 
(3581303, 0, 598.932373, 2956.018311, -5.171926, 5.500074, 0, 0, 0, 100, 0),
(3581303, 1, 589.653931, 2937.744141, -7.592101, 4.314123, 0, 0, 0, 100, 0),
(3581303, 2, 584.266357, 2929.844482, -6.687585, 4.113848, 0, 0, 0, 100, 0),
(3581303, 3, 574.325500, 2907.105469, -7.570318, 4.506544, 0, 0, 0, 100, 0),
(3581303, 4, 575.571838, 2906.467773, -7.290232, 5.574685, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581304;
INSERT INTO waypoint_data VALUES 
(3581304, 0, 575.254578, 2915.179199, -7.424442, 2.248593, 0, 0, 0, 100, 0),
(3581304, 1, 568.493896, 2918.540527, -6.926721, 3.006502, 0, 0, 0, 100, 0),
(3581304, 2, 563.509521, 2894.124268, -9.127908, 4.498757, 0, 0, 0, 100, 0),
(3581304, 3, 570.895386, 2881.191895, -8.941821, 5.229178, 0, 0, 0, 100, 0),
(3581304, 4, 589.367859, 2869.831787, -7.200697, 5.731833, 0, 0, 0, 100, 0),
(3581304, 5, 606.872986, 2860.528076, -6.730551, 5.794664, 0, 0, 0, 100, 0),
(3581304, 6, 608.440063, 2857.149902, -7.145034, 5.072102, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581305;
INSERT INTO waypoint_data VALUES 
(3581305, 0, 621.382935, 2888.383789, -4.491171, 1.235363, 0, 0, 0, 100, 0),
(3581305, 1, 625.539978, 2912.528564, -1.920422, 1.400297, 0, 0, 0, 100, 0),
(3581305, 2, 635.507141, 2922.693604, -0.679687, 0.811248, 0, 0, 0, 100, 0),
(3581305, 3, 654.337280, 2931.954346, 0.180412, 0.489235, 0, 0, 0, 100, 0),
(3581305, 4, 666.322205, 2947.070557, -0.068140, 1.031160, 0, 0, 0, 100, 0);

DELETE FROM waypoint_data WHERE id=3581306;
INSERT INTO waypoint_data VALUES 
(3581306, 0, 660.770020, 2940.163330, 0.073123, 4.035314, 0, 1, 0, 100, 0),
(3581306, 1, 655.257446, 2936.646973, 0.649165, 3.709374, 0, 1, 0, 100, 0),
(3581306, 2, 626.537354, 2912.329102, -1.972860, 3.897870, 0, 1, 0, 100, 0),
(3581306, 3, 617.258362, 2878.102539, -4.873388, 4.447648, 0, 1, 0, 100, 0),
(3581306, 4, 607.747620, 2871.329346, -5.575698, 3.760426, 0, 1, 0, 100, 0),
(3581306, 5, 574.772766, 2887.711426, -7.991757, 2.680503, 0, 1, 0, 100, 0),
(3581306, 6, 567.091003, 2904.979736, -8.285954, 1.989353, 0, 1, 0, 100, 0),
(3581306, 7, 583.231628, 2926.404053, -6.645783, 0.925138, 0, 1, 0, 100, 0),
(3581306, 8, 599.777161, 2952.090332, -6.146738, 0.999751, 0, 1, 0, 100, 0),
(3581306, 9, 588.531677, 2961.839111, -2.787853, 2.460592, 0, 1, 0, 100, 0),
(3581306, 10, 576.072510, 2955.392822, -1.200582, 3.619055, 0, 1, 0, 100, 0),
(3581306, 11, 561.765686, 2933.269531, 0.424554, 4.078513, 0, 1, 0, 100, 0),
(3581306, 12, 551.877625, 2937.384277, 1.642743, 2.747263, 0, 1, 0, 100, 0),
(3581306, 13, 518.457947, 2971.775391, 8.817685, 2.331002, 0, 1, 0, 100, 0),
(3581306, 14, 502.113647, 2986.438232, 7.374378, 2.448811, 0, 1, 0, 100, 0),
(3581306, 15, 488.268585, 2972.944580, 8.162946, 3.992119, 0, 1, 0, 100, 0);

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Verängstigter Minenarbeiter", QuestGiverTargetName_loc3="Verängstigter Minenarbeiter" WHERE Id=14021;

UPDATE creature_template SET unit_flags=33555200 WHERE entry=35814;

UPDATE creature_template SET AIName="", ScriptName="npc_capturing_the_unknown_bunny" WHERE entry in (37872, 37895, 37896, 37897);

delete from smart_scripts where entryorguid in (37872, 37895, 37896, 37897);

UPDATE item_template SET FlagsExtra=196673 WHERE entry=49887;

DELETE FROM  spell_linked_spell WHERE spell_trigger=70649 AND spell_effect=92169;

delete from spell_scripts where id=68280;

delete from spell_linked_spell where spell_trigger in (68280, 68281);

