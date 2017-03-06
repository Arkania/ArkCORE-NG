

UPDATE gameobject SET phaseIds="170 171 172 179" WHERE guid=168787;

UPDATE quest_template SET Method=2 WHERE Id=14239;

UPDATE quest_template SET PrevQuestId=14239, NextQuestId=14014, ExclusiveGroup=0, RequiredGender=0 WHERE Id=14474;

UPDATE quest_template SET PrevQuestId=14239, NextQuestId=14014, ExclusiveGroup=0, RequiredGender=1 WHERE Id=14001;

delete from smart_scripts where entryorguid=36608;

delete from smart_scripts where entryorguid=3660800;

UPDATE creature_template SET AIName="", ScriptName="npc_doc_zapnozzle_36608" WHERE entry=36608;

UPDATE creature_template SET ScriptName="npc_geargrinder_gizmo_36600" WHERE entry=36600;

UPDATE creature_template_addon SET emote=0, auras="68327 91298" WHERE entry=36600;

