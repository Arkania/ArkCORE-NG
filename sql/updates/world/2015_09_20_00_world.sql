
-- wrong phase
update creature set phaseMask=8 where guid in (271066, 250769);

-- spawned by script
delete from creature where id=35660;
delete from creature where guid in (251431, 251422, 251427, 251421, 251417);

-- set to better positions
update creature set position_x=-1440.710083, position_y=1429.456787, position_z=35.555893, orientation=0.412187  where guid=251420;
update creature set position_x=-1462.234741, position_y=1421.691040, position_z=35.555893, orientation=5.729330  where guid=251418;
update creature set position_x=-1480.293213, position_y=1386.956421, position_z=36.006737, orientation=5.305207  where guid=251424;
update creature set position_x=-1504.528687, position_y=1396.468262, position_z=35.556332, orientation=0.396469  where guid=251414;
update creature set position_x=-1551.584595, position_y=1390.074585, position_z=35.559502, orientation=0.298291  where guid=251372;
update creature set position_x=-1550.329102, position_y=1393.617065, position_z=35.556419, orientation=5.207031  where guid=251415;
update creature set position_x=-1521.939453, position_y=1421.273193, position_z=35.556419, orientation=1.554926  where guid=251371;
update creature set position_x=-1438.276855, position_y=1372.247437, position_z=35.556419, orientation=3.074671  where guid=251429;
update creature set position_x=-1448.458008, position_y=1362.877930, position_z=35.556419, orientation=5.391597  where guid=251356;
update creature set position_x=-1568.719971, position_y=1340.632202, position_z=35.836159, orientation=4.103546  where guid=251351;

-- enrage by spell
update creature_template_addon set auras="" where entry=34884;
