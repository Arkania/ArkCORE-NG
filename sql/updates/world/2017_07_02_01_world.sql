

update gameobject set phaseId=171 where guid=400038;

UPDATE creature_template SET ScriptName="" WHERE entry=43091;

-- npc_ship_to_vashjir_phase_caster_bunny_40559

delete from creature where id=34668 and guid in (272080, 272081, 272082, 272083);

update creature set PhaseId=0, phaseGroup=559 where id=35053 and guid=272109;

delete from creature where id=35053 and guid in (272110, 272111, 272112, 272113);

