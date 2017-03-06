
update phase_area set quest_end_status=11 where areaid=616 and entry=0;
update phase_area set quest_end_status=11 where areaid=616 and entry=1;
update phase_area set quest_end_status=11 where areaid=616 and entry=2;
update phase_area set quest_end_status=11 where areaid=616 and entry=3;

update phase_area set quest_end_status=11 where areaid=4714 and entry=0;
update phase_area set quest_end_status=11 where areaid=4714 and entry=1;
update phase_area set quest_end_status=11 where areaid=4714 and entry=2;
update phase_area set quest_end_status=11 where areaid=4714 and entry=3;

update phase_area set quest_start=14078, quest_end=14078, quest_start_status=75, quest_end_status=11 where areaid=4755 and entry=0;
delete from phase_area where areaId=4755 and entry=1;
insert into phase_area values
(4755, 1, 14078, 14159, 64, 11, 0, "Gilneas phase 2");

update phase_area set quest_end_status=11 where areaid=5420 and entry=0;

delete from phase_definitions where zoneId=4755 and entry=1;
insert into phase_definitions values
(4755, 1, 2, 0, 638, 0, 1, "Gilneas player startposition");

update npc_text set BroadcastTextID0=36059 where ID=14836;

update gossip_menu_option set OptionBroadcastTextID=36060 where menu_id=10696 and id=1;

UPDATE quest_template SET PrevQuestId=14283 WHERE Id=14291;

update creature set phaseMask=2 where phaseMask=4 and id=44548;

update creature set phaseMask=2 where phaseMask=4 and id=47091;

update creature set phaseMask=2 where id in (35232);

update creature_template set ScriptName="" where entry=34863;

update creature_template set ScriptName="npc_frightened_citizen_35836" where entry=35836;

update creature set position_x=-1733.226929, position_y=1341.242554, position_z=19.663870 where guid=250167 and id=35118;
update creature set position_x=-1721.588013, position_y=1348.509277, position_z=19.672361 where guid=250268 and id=35118;

update creature set phaseMask=2 where guid in (250851);
update creature set phaseMask=4 where guid in (250226, 250227, 250228, 250229);
update creature set phaseMask=6 where guid in (278397);

delete from creature where guid=278397 and id=50415;

update creature_template set Health_mod=1, ScriptName="" where entry=35370;

delete from spell_phase where spell_id=72870;
insert into spell_phase values 
(72870, 4, 638, 683);

update creature set phaseMask=4 where id in (35463);

update creature set phaseMask=4, position_x=-1804.494141, position_y=1407.072021, position_z=19.840219, orientation=4.923051 where guid=250821 and id=35550;

delete from creature where guid=250040 and id=35905;

UPDATE creature_template SET unit_flags=4, unit_flags2=34816 WHERE entry=35914;

update creature_template set AIName="", ScriptName="npc_lord_godfrey_35906" where entry=35906;
update creature set phaseMask=12 where guid=250284 and id=35906;

delete from creature where guid=240813 and id=35906;

delete from creature where id in (35385, 35916, 38377);

update creature set phaseMask=4 where id=35509;

update gameobject set phaseMask=12 where id in (195453, 195454, 195465, 195466);

update creature_text set sound=19712, BroadcastTextID=36092 where entry=35550 and groupid=0 and id=0;
update creature_text set BroadcastTextID=36091 where entry=35550 and groupid=0 and id=1;
update creature_text set sound=19709, BroadcastTextID=36090 where entry=35550 and groupid=0 and id=2;
update creature_text set sound=19712, BroadcastTextID=36092 where entry=35550 and groupid=1 and id=0;

delete from creature where guid in (250231, 250251);

update creature_template set AIName="", ScriptName="npc_gilnean_city_guard_35504" where entry=35504;

update creature set phaseMask=4 where guid=250254 and id=35753;

update creature set phaseMask=4 where id=35505;

delete from creature where map=638 and id in (34851, 34863, 34916, 35118, 35229, 35753);

DELETE FROM creature_addon WHERE guid=240582;
DELETE FROM creature_addon WHERE guid=240581;
DELETE FROM creature_addon WHERE guid=240580;
DELETE FROM creature_addon WHERE guid=240579;
DELETE FROM creature_addon WHERE guid=240578;
DELETE FROM creature_addon WHERE guid=240577;
DELETE FROM creature_addon WHERE guid=240537;
DELETE FROM creature_addon WHERE guid=240536;
DELETE FROM creature_addon WHERE guid=240535;
DELETE FROM creature_addon WHERE guid=240534;
DELETE FROM creature_addon WHERE guid=240533;
DELETE FROM creature_addon WHERE guid=240532;
DELETE FROM creature_addon WHERE guid=240531;
DELETE FROM creature_addon WHERE guid=240482;


-- https://www.youtube.com/watch?v=kYCyQBdM2Vw



