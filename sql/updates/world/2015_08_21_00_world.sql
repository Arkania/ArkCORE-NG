
UPDATE locales_quest SET EndText_loc3="" WHERE Id=12716;

UPDATE creature_template SET InhabitType=4 WHERE entry=28906;

update creature_text set BroadcastTextID=28770 where entry=28942 and groupid=0 and id=0;
update creature_text set BroadcastTextID=29078 where entry=28942 and groupid=0 and id=1;
update creature_text set BroadcastTextID=28765 where entry=28942 and groupid=0 and id=2;
update creature_text set BroadcastTextID=28769 where entry=28942 and groupid=0 and id=3;
update creature_text set BroadcastTextID=29085 where entry=28942 and groupid=0 and id=4;
update creature_text set BroadcastTextID=29086 where entry=28942 and groupid=0 and id=5;
update creature_text set BroadcastTextID=29088 where entry=28942 and groupid=0 and id=6;
update creature_text set BroadcastTextID=29074 where entry=28942 and groupid=0 and id=7;
update creature_text set BroadcastTextID=28788 where entry=28942 and groupid=1 and id=0;
update creature_text set BroadcastTextID=28789 where entry=28942 and groupid=1 and id=1;
update creature_text set BroadcastTextID=28791 where entry=28942 and groupid=1 and id=2;
update creature_text set BroadcastTextID=28792 where entry=28942 and groupid=1 and id=3;
update creature_text set BroadcastTextID=28793 where entry=28942 and groupid=1 and id=4;
update creature_text set BroadcastTextID=28790 where entry=28942 and groupid=1 and id=5;

UPDATE quest_template SET Method=2, Flags=8328, SpecialFlags=1 WHERE Id=12718;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=12718;

update creature_template set AIName="", ScriptName="npc_crusade_persuaded_28610" where entry in (28610, 28939, 28940);





