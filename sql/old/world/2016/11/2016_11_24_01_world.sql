
delete from creature where guid=192132 and id=25740;

UPDATE creature_template SET Health_mod=1 WHERE entry=36399;

UPDATE creature_template SET Health_mod=1 WHERE entry=36397;

UPDATE creature_template_addon SET auras="71333" WHERE entry=38531;

update creature set phaseIds=169, phaseGroup=0 where id in (29212, 39629, 45177);

update creature set phaseIds=172, phaseGroup=0 where id in (44468);

update creature set phaseIds=176, phaseGroup=0 where id in (31098) and phaseIds="176 177";

update creature set phaseIds=179, phaseGroup=0 where id in (46053);

update creature set phaseIds=181, phaseGroup=0 where id in (40732);

update creature set phaseIds=194, phaseGroup=0 where id in (40819);

update creature set phaseIds=0, phaseGroup=443 where id=4075 AND map=654;

update creature set phaseIds=0, phaseGroup=443 where id=35374 AND map=654 and guid=10434;

update creature set phaseIds=0, phaseGroup=412 where id=39660 and map=654;

UPDATE quest_template SET RequiredNpcOrGo1=44175 WHERE Id=25145;

delete from spell_script_names where spell_id in (689, 89420);
insert into spell_script_names values
(689, "spell_warl_drain_life"),
(89420, "spell_warl_drain_life");

delete from spell_script_names where spell_id=1120;
insert into spell_script_names values
(1120, "spell_warl_drain_soul");






