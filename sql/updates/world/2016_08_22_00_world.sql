
delete from creature where id in (34957, 34958, 34959);

delete from creature where id in (34954, 34890, 34892);

UPDATE creature_template SET AIName="", ScriptName="npc_ace_34957" WHERE entry=34957;

UPDATE creature_template SET AIName="", ScriptName="npc_gobber_34958" WHERE entry=34958;

UPDATE creature_template SET AIName="", ScriptName="npc_izzy_34959" WHERE entry=34959;

delete from areatrigger_scripts where entry in (5497, 5498, 5499);
insert into areatrigger_scripts values 
(5497, "at_kezan_ace_5497"),
(5498, "at_kezan_gobber_5498"),
(5499, "at_kezan_izzy_5499");

UPDATE creature_template SET ScriptName="npc_megs_dreadshredder_34874" WHERE entry=34874;

UPDATE creature_template SET ScriptName="npc_bamm_megabomb_34673" WHERE entry=34673;

delete from phase_definitions where zoneId= 4737 and entry=0;
insert into phase_definitions values 
(4737, 0, 204, 0, 378, 0, 0, 1, "Kezan from start");

delete from phase_definitions where zoneId= 4737 and entry=1;
insert into phase_definitions values 
(4737, 1, 15, 0, 379, 0, 0, 1, "Kezan from reward quest 14109");

delete from phase_definitions where zoneId= 4737 and entry=2;
insert into phase_definitions values 
(4737, 2, 19, 0, 380, 0, 0, 1, "Kezan from reward quest 14113");

delete from phase_definitions where zoneId= 4737 and entry=3;
insert into phase_definitions values 
(4737, 3, 35, 0, 381, 0, 0, 1, "Kezan from reward quest 14115");

delete from phase_definitions where zoneId= 4737 and entry=4;
insert into phase_definitions values 
(4737, 4, 1023, 0, 382, 0, 0, 1, "Kezan from complete quest 14116");

delete from phase_definitions where zoneId= 4737 and entry=5;
insert into phase_definitions values 
(4737, 5, 9, 0, 383, 0, 0, 1, "Kezan from reward quest 14120");

delete from phase_definitions where zoneId= 4737 and entry=6;
insert into phase_definitions values 
(4737, 6, 447, 0, 384, 0, 0, 1, "Kezan from reward quest 14122");

delete from phase_definitions where zoneId= 4720 and entry=0;
insert into phase_definitions values 
(4720, 0, 2, 170, 0, 0, 0, 1, "Lost island from start ");

delete from phase_area where areaId=4737 and entry=0;
insert into phase_area values 
(4737, 0, 14138, 14109, 75, 11, 1, "Kezan from start to reward quest 14109");

delete from phase_area where areaId=4737 and entry=1;
insert into phase_area values 
(4737, 1, 14109, 14113, 64, 11, 1, "Kezan from reward 14109 to reward 14113");

delete from phase_area where areaId=4737 and entry=2;
insert into phase_area values 
(4737, 2, 14113, 14115, 64, 11, 1, "Kezan from reward 14113 to reward 14115");

delete from phase_area where areaId=4737 and entry=3;
insert into phase_area values 
(4737, 3, 14115, 14116, 64, 11, 1, "Kezan from reward 14115 to reward 14116");

delete from phase_area where areaId=4737 and entry=4;
insert into phase_area values 
(4737, 4, 14116, 14120, 64, 11, 1, "Kezan from reward 14116 to reward 14120");

delete from phase_area where areaId=4737 and entry=5;
insert into phase_area values 
(4737, 5, 14120, 14122, 64, 11, 1, "Kezan from reward 14120 to reward 14122");

delete from phase_area where areaId=4737 and entry=6;
insert into phase_area values 
(4737, 6, 14122, 14126, 64, 11, 1, "Kezan from reward 14122 to reward 14126");

delete from conditions where SourceTypeOrReferenceId=25;

