

-- wrong placed npc on ships..
delete from creature where guid in (159487, 159488, 159489, 159490, 118855, 118856);

update creature set map=586, position_x=23.3145, position_y=4.8571, position_z=11.91 where guid=159491;

