
update creature_template set npcflag=0 where entry=37989;
update creature_template set npcflag=0 where entry=38002;
update creature set spawntimesecs=120 where guid=90057;

delete from areatrigger_scripts where entry=5675 and ScriptName="at_raptor_pens";
insert into areatrigger_scripts values (5675, "at_raptor_pens");


