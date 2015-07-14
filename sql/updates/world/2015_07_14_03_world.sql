
update creature_text set BroadcastTextID=13976 where entry=39665 and groupid=4 and id=0;
update creature_text set BroadcastTextID=50618 where entry=39665 and groupid=5 and id=0;

delete from spell_script_names where spell_id=75539;
insert into spell_script_names values (75539, "spell_chains_of_woe");

delete from creature_text where entry=39698 and groupid=5 and id=0;
update creature_text set BroadcastTextID=49589 where entry=39665 and groupid=0 and id=0;
update creature_text set BroadcastTextID=49591 where entry=39665 and groupid=1 and id=0;
update creature_text set BroadcastTextID=49590 where entry=39665 and groupid=2 and id=0;
update creature_text set BroadcastTextID=49592 where entry=39665 and groupid=3 and id=0;
update creature_text set BroadcastTextID=50620 where entry=39665 and groupid=4 and id=0;

delete from creature_text where entry=39679 and groupid=5 and id=0;
delete from creature_text where entry=39679 and groupid=6 and id=0;

update creature_text set BroadcastTextID=49585 where entry=39679 and groupid=0 and id=0;
update creature_text set BroadcastTextID=49587 where entry=39679 and groupid=1 and id=0;
update creature_text set BroadcastTextID=49586 where entry=39679 and groupid=2 and id=0;
update creature_text set BroadcastTextID=49588 where entry=39679 and groupid=3 and id=0;
update creature_text set BroadcastTextID=50619 where entry=39679 and groupid=4 and id=0;

update creature_template set AIName="", ScriptName="npc_twilight_zealot" where entry=39990;
update creature_template set AIName="", ScriptName="npc_corla_netheressence_trigger" where entry=49526;

update creature_template set VehicleId=1598 where entry=52363;

update instance_template set script="instance_dragon_soul" where map=967;

delete from creature_text where entry=55294;
insert into creature_text (entry, groupid, id, text, type, BroadcastTextID) values 
(55294, 0, 0, "I am the beginning of the end...the shadow which blots out the sun...the bell which tolls your doom...", 14, 55320),
(55294, 1, 0, "For this moment ALONE was I made. Look upon your death, mortals, and despair!", 14, 55323),
(55294, 2, 0, "The cycle of time brings an end to all things.", 14, 55328),
(55294, 3, 0, "Now is the hour of twilight!", 14, 55329),
(55294, 4, 0, "But...but...I am...Ul...trax...ionnnnnn...", 14, 55330),
(55294, 5, 0, "Fall before Ultraxion!", 14, 55331),
(55294, 6, 0, "The final shred of light fades, and with it, your pitiful mortal existence!", 14, 55334),
(55294, 7, 0, "I WILL DRAG YOU WITH ME INTO FLAME AND DARKNESS!", 14, 55337);







