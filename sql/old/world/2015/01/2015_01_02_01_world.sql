
-- http://de.wowhead.com/npc=7024, , Agent Kearnen
update creature_template set AIName="", ScriptName="npc_agent_kearnen" where entry=7024;

delete from creature_text where entry=7024 and groupid=1 and id=0;
insert into creature_text values (7024, 1, 0, "I've got your back, $N.", 12, 0, 100, 0, 0, 0, "Agent Kearnen", 42531);

update creature_text set BroadcastTextID=42533 where entry=7024 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42534 where entry=7024 and groupid=0 and id=1;
update creature_text set BroadcastTextID=42532 where entry=7024 and groupid=0 and id=2;
update creature_text set BroadcastTextID=42535 where entry=7024 and groupid=0 and id=3;

delete from creature_questender where id=42750 and quest=26291;

