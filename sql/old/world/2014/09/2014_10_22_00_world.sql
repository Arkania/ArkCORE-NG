
-- http://www.wowhead.com/npc=40283	Searing Light
-- npc are spawned from script
delete from creature where id=40283;

-- http://www.wowhead.com/npc=40183	Cave In Stalker
-- npc are spawned from script
delete from creature where id=40183;

update gameobject_template set faction=35,flags=16,data0=1845,data6=8,data10=76606,AIName="",ScriptName="go_beacon_of_light" where entry=207218;
update gameobject_template set faction=35,flags=16,data0=1845,data6=8,data10=76608,AIName="",ScriptName="go_beacon_of_light" where entry=207219;

update gameobject_template set faction=35,flags=16,data0=0,data6=8,data10=76606,AIName="",ScriptName="go_beacon_of_light" where entry=203133;
update gameobject_template set faction=35,flags=16,data0=0,data6=8,data10=76608,AIName="",ScriptName="go_beacon_of_light" where entry=203136;

delete from spell_script_names where spell_id in (76606,76608);
insert into spell_script_names (spell_id,ScriptName) values
(76606,"spell_disable_beacon_beams"),
(76608,"spell_disable_beacon_beams");

update creature_text set BroadcastTextId=44783 where entry=39425 and groupid=2 and id=0;
update creature_text set BroadcastTextId=44786 where entry=39425 and groupid=2 and id=1;
update creature_text set BroadcastTextId=40968 where entry=39425 and groupid=4 and id=0;
update creature_text set BroadcastTextId=50665 where entry=39425 and groupid=5 and id=0;
update creature_text set text="%s becomes protected by his defense beacons! Disable them by pulling the levers below!" where entry=39425 and groupid=4 and id=0;
update creature_text set text="%s is no longer protected by the beacons!", type=41,comment="VO_HO_Anhuur_Special",sound=0 where entry=39425 and groupid=5 and id=0;

delete from creature where id=56054 and guid in (241776,241777);

