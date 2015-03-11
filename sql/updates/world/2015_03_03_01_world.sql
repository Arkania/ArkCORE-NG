
update creature_text set BroadcastTextID=42224 where entry=42309 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42225 where entry=42309 and groupid=1 and id=0;
update creature_text set BroadcastTextID=42226 where entry=42309 and groupid=2 and id=0;

update creature_text set BroadcastTextID=42386 where entry in (42391,42383,42386) and groupid=0 and id=0;
update creature_text set BroadcastTextID=42375 where entry in (42391,42383,42386) and groupid=0 and id=1;
update creature_text set BroadcastTextID=42389 where entry in (42391,42383,42386) and groupid=0 and id=2;
update creature_text set BroadcastTextID=42358 where entry in (42391,42383,42386) and groupid=0 and id=3;
update creature_text set BroadcastTextID=42361 where entry in (42391,42383,42386) and groupid=0 and id=4;
update creature_text set BroadcastTextID=42374 where entry in (42391,42383,42386) and groupid=0 and id=5;
update creature_text set BroadcastTextID=42385 where entry in (42391,42383,42386) and groupid=0 and id=6;
update creature_text set BroadcastTextID=42384 where entry in (42391,42383,42386) and groupid=0 and id=7;

update creature_text set BroadcastTextID=42383 where entry in (42391,42383,42386) and groupid=1 and id=0;
update creature_text set BroadcastTextID=42382 where entry in (42391,42383,42386) and groupid=2 and id=0;
update creature_text set BroadcastTextID=42381 where entry in (42391,42383,42386) and groupid=3 and id=0;
update creature_text set BroadcastTextID=42380 where entry in (42391,42383,42386) and groupid=4 and id=0;
update creature_text set BroadcastTextID=42457 where entry in (42386) and groupid=5 and id=0;

update quest_template set SourceSpellId=0 where Id=26215;
update creature_template_addon set auras="79343 79372 29266" where entry=42560;

