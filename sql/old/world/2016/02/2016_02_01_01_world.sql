

UPDATE quest_template SET Method=2, Flags=65544, SpecialFlags=4 WHERE Id=8713;

delete from item_script_names where Id=52514;
insert into item_script_names values
(52514, "item_thonks_spyglass_52514");

update creature_template set AIName="", ScriptName="npc_durotar_watershed_telescope_39320" where entry=39320;
update creature_template set AIName="", ScriptName="npc_durotar_watershed_telescope_39345" where entry=39345;
update creature_template set AIName="", ScriptName="npc_durotar_watershed_telescope_39346" where entry=39346;
update creature_template set AIName="", ScriptName="npc_durotar_watershed_telescope_39347" where entry=39347;

delete from waypoint_data where id=3932001;
insert into waypoint_data values
(3932001, 0,  392.285, -4583.329, 76.66824, 2.406953, 0, 1, 0, 100, 0),
(3932001, 1,  392.285, -4583.329, 76.66824, 2.406953, 0, 1, 0, 100, 0),
(3932001, 2, 60.78472, -4232.328, 38.40229, 2.406953, 10000, 1, 0, 100, 0),
(3932001, 3, 60.78472, -4232.328, 38.40229, 2.406953, 0, 1, 0, 100, 0);

delete from waypoint_data where id=3934501;
insert into waypoint_data values
(3934501, 0,  392.285, -4583.329, 76.66824, 1.210, 0, 1, 0, 100, 0),
(3934501, 1,  392.285, -4583.329, 76.66824, 1.210, 0, 1, 0, 100, 0),
(3934501, 2, 555.5816, -4146.896, 28.34670, 1.210, 10000, 1, 0, 100, 0),
(3934501, 3, 555.5816, -4146.896, 28.34670, 1.210, 0, 1, 0, 100, 0);

delete from waypoint_data where id=3934601;
insert into waypoint_data values
(3934601, 0,  392.285, -4583.329, 76.66824, 0.759, 0, 1, 0, 100, 0),
(3934601, 1,  392.285, -4583.329, 76.66824, 0.759, 0, 1, 0, 100, 0),
(3934601, 2,  721.934, -4260.484, 23.06897, 0.759, 10000, 1, 0, 100, 0),
(3934601, 3,  721.934, -4260.484, 23.06897, 0.759, 0, 1, 0, 100, 0);

delete from waypoint_data where id=3934701;
insert into waypoint_data values
(3934701, 0,  392.285, -4583.329, 76.66824, 1.326, 0, 1, 0, 100, 0),
(3934701, 1,  392.285, -4583.329, 76.66824, 1.326, 0, 1, 0, 100, 0),
(3934701, 2, 349.1458, -3869.010, 25.06922, 1.326, 10000, 1, 0, 100, 0),
(3934701, 3, 349.1458, -3869.010, 25.06922, 1.326, 0, 1, 0, 100, 0);

UPDATE creature_template SET InhabitType=4 WHERE entry in (39320, 39345, 39346, 39347, 39357, 39358, 39359, 39360);

update creature_template_addon set bytes1=33554432 where entry in (39320, 39345, 39346, 39347);


