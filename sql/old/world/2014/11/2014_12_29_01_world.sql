
update creature_template set AIName="", ScriptName="npc_ripsnarl_sentinel_hill" where entry=42635;

delete from creature_text where entry in(234) and groupid in (10,11);
delete from creature_text where entry in(42308) and groupid in (10,11,12,13,14);
delete from creature_text where entry in(42635) and groupid in (10);
insert into creature_text values
(  234,10,0,"You have our full cooperation, lieutenant. The Furlbrows were good people. Their deaths will not go unpunished.",12,0,100,0,0,0,"",42505),
(  234,11,0,"We caught this beast slaughtering sheep in the countryside. He is unrepentant and easily agitated. Keep your distance, lieutenant.",12,0,100,0,0,0,"",42508),
(42308,10,0,"That's good to hear, marshal. While $n has brought the perpetrators to justice, their ringleader is still on the loose. Perhaps with the aid of the Westfall Brigade we will finally be able to solve this case.",12,0,100,0,0,0,"",42506),
(42308,11,0,"Might I ask, what's with the worgen in the stocks?",12,0,100,0,0,0,"",42507),
(42308,12,0,"Wow, the marshal wasn't kidding.",12,0,100,0,0,0,"",42510),
(42308,13,0,"But is your bark...",12,0,100,0,0,0,"",42511),
(42308,14,0,"Worse than your bite?",12,0,100,0,0,0,"",42512),
(42635,10,0,"When I break out of these stocks I'm going to rip out your heart and devour it whole!",12,0,100,0,0,0,"",42509);

delete from waypoint_data where id in (423081,423082);
insert into waypoint_data (id,point,position_x,position_y,position_z,orientation,delay,move_flag,action,action_chance) values
(423081, 1,  -10507.96, 1047.543, 60.51798, 0, 0, 0, 0, 100),
(423081, 2,  -10509.4, 1047.37, 60.76798, 0, 0, 0, 0, 100),
(423081, 3, -10511.85, 1046.696, 60.51798, 0, 0, 0, 0, 100),
(423082, 1, -10511.85, 1046.696, 60.51798, 0, 0, 0, 0, 100),
(423082, 2, -10509.9, 1047.12, 60.76798, 0, 0, 0, 0, 100),
(423082, 3, -10508.9, 1047.37, 60.76798, 0, 0, 0, 0, 100),
(423082, 4, -10507.508, 1048.514, 60.51798, 4.356, 0, 0, 0, 100);

update creature_template set unit_flags=32768 where entry=42407;

 