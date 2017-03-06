

update creature_template set faction=2082, unit_flags=16777224, InhabitType=5 where entry=28511;
update creature_template set spell1=51859, spell2=51904, spell3=52006, spell4=0, spell5=52694, spell6=0 where entry=28511;

delete from waypoint_data where id=2851100;
insert into waypoint_data (id,point,position_x,position_y,position_z,orientation,delay,move_flag,action,action_chance,wpguid) values 
(2851100, 0, 2341.57, -5672.8, 538.394, 0, 0, 1, 0, 100, 0),
(2851100, 1, 1957.4, -5844.1, 273.867, 0, 0, 1, 0, 100, 0),
(2851100, 2, 1758.01, -5876.79, 166.867, 0, 0, 1, 0, 100, 0);

delete from spell_script_names where spell_id=52694;
insert into spell_script_names values (52694, "spell_q12641_recall_eye_of_acherus");

