

update quest_template set RequiredNpcOrGo1=47057 where Id=24784;
update quest_template set RequiredNpcOrGo1=42501 where Id=26200;

update creature_template set KillCredit1=0, AIName="", ScriptName="npc_wounded_darkspear_watcher" where entry=47057;

update creature_text set BroadcastTextId=2049 where entry=5702 and groupid=0 and id=0;
update creature_text set BroadcastTextId=2050 where entry=5702 and groupid=1 and id=0;
update creature_text set BroadcastTextId=2051 where entry=5702 and groupid=2 and id=0;
update creature_text set BroadcastTextId=2052 where entry=5702 and groupid=3 and id=0;
update creature_text set BroadcastTextId=2053 where entry=5702 and groupid=4 and id=0;
update creature_text set BroadcastTextId=2054 where entry=5702 and groupid=5 and id=0;
update creature_text set BroadcastTextId=2055 where entry=5702 and groupid=6 and id=0;
update creature_text set BroadcastTextId=2056 where entry=5702 and groupid=7 and id=0;

