
update creature_template set AIName="", ScriptName="npc_gilneas_city_guard_phase1" where entry=34864;
update creature_template set AIName="", ScriptName="npc_panicked_citizen_phase1" where entry=44086;
update creature_template set AIName="", ScriptName="npc_prince_liam_greymane_phase1" where entry=34850;
update creature_template set AIName="", ScriptName="npc_lieutenant_walden_phase1" where entry=34863;

update creature_template set AIName="", ScriptName="npc_prince_liam_greymane_phase2" where entry=34913;
update creature_template set AIName="", ScriptName="npc_gilneas_city_guard_phase2" where entry=34916;
update creature_template set AIName="", ScriptName="npc_rampaging_worgen_phase2" where entry=35660;
update creature_template set AIName="", ScriptName="npc_frightened_citizen_j_phase2" where entry=34981;
update creature_template set AIName="", ScriptName="npc_frightened_citizen_cw_phase2" where entry=35836;
update creature_template set AIName="", ScriptName="npc_rampaging_worgen_cw_phase2" where entry=34884;

update gameobject_template set AIName="", ScriptName="go_merchant_square_door_phase2" where entry=195327;

update creature set phaseMask=1 where guid=240560;
update creature set phaseMask=3 where guid=15454881;






