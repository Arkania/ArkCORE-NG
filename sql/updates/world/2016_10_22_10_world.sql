
UPDATE creature_template_addon SET bytes1=0 WHERE entry=36383;

UPDATE creature SET phaseIds="172" WHERE guid=246287;

UPDATE creature SET phaseIds="172" WHERE guid=248350;

UPDATE creature_template SET dynamicflags=0, ScriptName="npc_aggra_36115" WHERE entry=36115;

UPDATE creature_template SET ScriptName="npc_orc_battlesworn_36104" WHERE entry=36104;

UPDATE creature_template SET dynamicflags=0, ScriptName="npc_kilag_gorefang_36117" WHERE entry=36117;

UPDATE creature_template SET dynamicflags=0, ScriptName="npc_si_operative_36103" WHERE entry=36103;

update creature set phaseIds="172" where id=36103;

update creature set phaseIds="179" where id=36348;

update creature set phaseIds="170 171" where id=36346;

UPDATE creature SET phaseIds="172" WHERE guid=246168;

UPDATE creature SET phaseIds="172" WHERE guid=246094;

UPDATE creature SET phaseIds="172" WHERE guid=246785;

UPDATE creature_template SET unit_flags=32768 WHERE entry=36383;

UPDATE quest_template SET Flags=786432 WHERE Id=14242;

UPDATE quest_template SET RewardSpell=0 WHERE Id=14242;

UPDATE gameobject_template SET Size=1.3 WHERE entry=195704;

UPDATE gameobject_template SET Size=1.3 WHERE entry=195707;

UPDATE gameobject SET phaseIds="172" WHERE guid=168928;

UPDATE gameobject SET phaseIds="179" WHERE guid=168929;

delete from creature where guid=248391;

UPDATE creature SET phaseIds="170 171 172" WHERE guid=246095;

UPDATE creature SET position_x=993.028, position_y=3852.31 WHERE guid=246095;

UPDATE creature_template SET InhabitType=4 WHERE entry=36177;

UPDATE creature SET phaseIds="170 172 172" WHERE id=36149;

UPDATE creature SET phaseIds="179" WHERE id=36621;

UPDATE creature SET phaseIds="179" WHERE id=36176;

UPDATE creature_addon SET emote=431 WHERE guid=248052;

UPDATE creature SET position_x=996.07, position_y=3762.49 WHERE guid=247773;

update gameobject set phaseIds="179" where id in (196818, 196819, 196820, 196821, 196822, 196823, 196824, 196825, 196826, 196827, 196828);

-- Rope ladders and Arcane Cage.
UPDATE `gameobject` SET `phaseids`="171 172 179" WHERE `id` IN(196397, 196396);
UPDATE `gameobject_template` SET `data5`=1,data2=18775,`data1`=14242,`flags`=4,`IconName`="Interact" WHERE `entry`=195704;

DELETE FROM creature_text WHERE entry=36161;
INSERT INTO creature_text VALUES 
(36161, 0, 0, "Use the Cyclone of the Elements to kill the pirates on the ships and boats!", 41, 0, 100, 0, 0, 0, "say Thrall", 0),
(36161, 1, 0, "Spirits of the sea, rise and lay waste to my enemies!", 12, 0, 100, 0, 0, 0, "Thrall", 36198),
(36161, 2, 0, "Power of the ocean, heed my call!", 12, 0, 100, 0, 0, 0, "Thrall", 36199),
(36161, 3, 0, "Children of the watery depths, lay waste to those who foul your realm!", 12, 0, 100, 0, 0, 0, "Thrall", 36200),
(36161, 4, 0, "Speed of the storm, heed my call!", 12, 0, 100, 0, 0, 0, "Thrall", 36201),
(36161, 5, 0, "Winds of boundless fury, unleash your tempest upon the Alliance!", 12, 0, 100, 0, 0, 0, "Thrall", 36202),
(36161, 6, 0, "Sons of Stormwall, descend and destroy those who would prevent me from protecting this world!", 12, 0, 100, 0, 0, 0, "Thrall", 36203);

UPDATE creature_template SET ScriptName="npc_scout_brax_36112" WHERE entry=36112;

UPDATE creature_template SET ScriptName="npc_gyrochoppa_pilot_36129" WHERE entry=36129;

UPDATE creature_template SET ScriptName="npc_gyrochoppa_36143" WHERE entry=36143;

UPDATE creature_template SET ScriptName="npc_thrall_36622" WHERE entry=36622;

UPDATE creature_template SET minlevel=88, maxlevel=88, faction=29, unit_flags=32768 WHERE entry=36161;

UPDATE creature_template SET ScriptName="npc_thrall_36161" WHERE entry=36161;

delete from creature where guid=246096;

