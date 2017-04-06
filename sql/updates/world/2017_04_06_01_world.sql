
UPDATE creature_template SET AIName="", ScriptName="npc_nevin_twistwrench_45966" WHERE entry=45966;
UPDATE creature_template SET AIName="", ScriptName="npc_carvo_blastbolt_47250" WHERE entry=47250;
UPDATE creature_template SET AIName="", ScriptName="npc_sanitron_500_46185" WHERE entry=46185;
UPDATE creature_template SET AIName="", ScriptName="npc_gnomeregan_torben_46293" WHERE entry=46293;
UPDATE creature_template SET AIName="", ScriptName="npc_mekka_torque_42317" WHERE entry=42317;
UPDATE creature_template SET AIName="", ScriptName="npc_toxic_pool_42563" WHERE entry=42563;
UPDATE creature_template SET AIName="", ScriptName="npc_engineer_grindspark_42553" WHERE entry=42553;
UPDATE creature_template SET AIName="", ScriptName="npc_multi_bot_42598" WHERE entry=42598;
UPDATE gameobject_template SET AIName="", ScriptName="go_makeshift_cage_204019" WHERE entry=204019;

delete from smart_scripts where entryorguid in (42317, 46293);
