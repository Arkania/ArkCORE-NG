
delete from item_loot_template where entry=44113 and item =0;

update item_loot_template set ChanceOrQuestChance=35 where entry=11024 and item=49209;
update item_loot_template set ChanceOrQuestChance=-45 where entry=11024 and item=11040;

delete from item_loot_template where entry =33875 and item=10004;

update gameobject_template set data0=57,data1=106319 where entry=106319;

update quest_template set method=2 where Id=26297;

update creature_template set AIName="", ScriptName="npc_van_cleef_dummy" where entry=42679;
update creature_template set AIName="", ScriptName="" where entry=42680;

update creature_text set BroadcastTextID=42570 where entry=42680 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42571 where entry=42680 and groupid=1 and id=0;
update creature_text set BroadcastTextID=42572 where entry=42680 and groupid=2 and id=0;
update creature_text set BroadcastTextID=42573 where entry=42680 and groupid=3 and id=0;
update creature_text set BroadcastTextID=42574 where entry=42680 and groupid=4 and id=0;
update creature_text set BroadcastTextID=42575 where entry=42680 and groupid=5 and id=0;
update creature_text set BroadcastTextID=42576 where entry=42680 and groupid=6 and id=0;
update creature_text set BroadcastTextID=42577 where entry=42680 and groupid=7 and id=0;

