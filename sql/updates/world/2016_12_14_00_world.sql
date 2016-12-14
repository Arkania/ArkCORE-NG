

UPDATE creature_template SET modelid1=38689, minlevel=88, maxlevel=88, faction=2204, unit_flags=32776 WHERE entry=36622;

DELETE FROM creature_template_addon WHERE entry=36622;
INSERT INTO creature_template_addon VALUES 
(36622, 0, 0, 0, 1, 0, "");

DELETE FROM waypoint_data WHERE id=3662200;
INSERT INTO waypoint_data VALUES 
(3662200, 0, 990.2989, 3847.225, 3.229019, 4.314629, 0, 1, 0, 0, 0),
(3662200, 1, 982.969, 3840.568, 3.229796, 4.004399, 0, 1, 0, 0, 0),
(3662200, 2, 971.9352, 3816.387, 3.23076, 5.374913, 0, 1, 0, 0, 0),
(3662200, 3, 975.2913, 3810.38, 3.23076, 5.221761, 0, 1, 0, 0, 0),
(3662200, 4, 980.188, 3810.202, 3.230962, 6.2467, 0, 1, 0, 0, 0),
(3662200, 5, 980.8309, 3812.375, 3.231904, 1.228005, 0, 1, 0, 0, 0),
(3662200, 6, 983.0446, 3818.283, 8.608394, 1.69139, 0, 1, 0, 0, 0),
(3662200, 7, 982.9799, 3820.387, 8.698087, 1.542164, 0, 1, 0, 0, 0),
(3662200, 8, 982.9996, 3821.723, 10.39601, 1.530383, 0, 1, 0, 0, 0),
(3662200, 9, 981.4396, 3822.528, 11.16622, 2.665284, 0, 1, 0, 0, 0),
(3662200, 10, 980.5885, 3822.906, 11.16468, 2.724189, 0, 1, 0, 0, 0),
(3662200, 11, 980.7786, 3823.334, 11.19272, 1.153392, 0, 1, 0, 0, 0),
(3662200, 12, 980.7786, 3823.334, 11.19272, 1.153392, 0, 1, 0, 0, 0);

DELETE FROM creature WHERE id=36161 AND guid=246096;
INSERT INTO creature VALUES 
(246096, 36161, 648, 0, 0, 1, "179", 0, 0, 0, 980.804, 3823.14, 11.1827, 1.169371, 86400, 0, 0, 0, 0, 0, 0, 0, 0);

update creature set phaseId=0, phaseGroup=558 where guid=279168 and id=37761;
delete from creature where guid in (279169, 279170, 279171, 279172, 279173, 279174);


delete from arkcore_string where entry=5030;
insert into arkcore_string (entry, content_default, content_loc3) values 
(5030, "Uses invalid phaseID.", "Benutzt ungültige phaseID.");

update gameobject set orientation=0.229 where guid=22975;

update gameobject set orientation=0.229 where guid=81779;

update gameobject set phaseId=181, phaseGroup=0 where guid=168994;


