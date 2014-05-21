
-- set krennan to the tree
update creature set id=35753 where guid=250254;

-- change phase of cannon
update creature set phaseMask=8 where guid in (251103,251104);

update creature set position_x=-1802.961, position_y=1389.619, position_z=20.285, orientation=5.33 where guid=251103;

update creature_template set AIName="", ScriptName="npc_commandeered_cannon_phase8" where entry=35914;

UPDATE quest_template SET RewardSpellCast=0 WHERE Id=14293;
