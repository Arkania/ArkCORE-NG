

-- horse has wrong position
delete from creature where guid=240476;
-- rebel's have wrong positions
update creature set position_x=-1747.89, position_y=1672.17, position_z=21.735 where guid=241250;
update creature set position_x=-1760.51, position_y=1668.068, position_z=21.735 where guid=241249;

-- missing prince greymane, move from unuset map..
update creature set map=638,phaseMask=8 where guid=251108;



