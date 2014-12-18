

insert ignore into creature_text (entry,groupid,id) value (40,0,2);
update creature_text set text="No kill me! No kill me!",type=12,probability=50,comment="combat Say" where entry=40 and groupid=0 and id=2;

update creature_text set BroadcastTextID=1863 where entry=40 and groupid=0 and id=0;
update creature_text set BroadcastTextID=1864 where entry=40 and groupid=0 and id=1;
update creature_text set BroadcastTextID=1868 where entry=40 and groupid=0 and id=2;
