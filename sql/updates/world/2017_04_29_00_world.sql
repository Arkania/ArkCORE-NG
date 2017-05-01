
UPDATE creature SET position_z=30.06 WHERE guid=77877;

delete from creature where guid=251490;

UPDATE creature_template SET npcflag=2, ScriptName="npc_slain_watchman_36205" WHERE entry=36205;

UPDATE creature SET position_x=-1907.81, position_y=2312.481, position_z=39.6815, orientation=2.799 WHERE guid=252047;

delete from creature_equip_template where entry=51409;
insert into creature_equip_template values 
(51409, 1, 0, 0, 15460);

delete from creature_equip_template where entry=37946;
insert into creature_equip_template values 
(37946, 1, 0, 0, 2552);

UPDATE quest_template SET Flags=2162696 WHERE Id=14467;

delete from spell_phase where spell_id in (68481,68482,68483,69077,69078,69484,69485,69486,70695,70696,74096,84481);

INSERT INTO `spell_phase` VALUES 
(68481, 0, 181, 0, 655, 678, 'Quest Zone-Specific 06'),
(68482, 0, 182, 0, 655, 678, 'Quest Zone-Specific 07'),
(68483, 0, 183, 0, 655, 678, 'Duskhaven, shattered land, Quest Zone-Specific 08'),
(68483, 1, 183, 0, 655, 683, 'Duskhaven, shattered land, Quest Zone-Specific 08'),
(69077, 0, 184, 0, 655, 678, 'Quest Zone-Specific 09'),
(69078, 0, 185, 0, 656, 679, 'Quest Zone-Specific 10'),
(69484, 0, 186, 0, 656, 679, 'Quest Zone-Specific 11'),
(69485, 0, 187, 0, 656, 679, 'Quest Zone-Specific 12'),
(69486, 0, 188, 0, 656, 679, 'Quest Zone-Specific 13'),
(70695, 0, 189, 0, 656, 679, 'Quest Zone-Specific 14'),
(70696, 0, 190, 0, 656, 679, 'Quest Zone-Specific 15'),
(74096, 0, 194, 0, 656, 679, 'Quest Zone-Specific 19');

UPDATE gameobject SET phaseId=0, phaseGroup=450 WHERE guid in (166781, 166771, 166787);

UPDATE gameobject_template SET ScriptName="go_gate_196399" WHERE entry=196399;

UPDATE gameobject_template SET ScriptName="go_gate_196401" WHERE entry=196401;

UPDATE gameobject_template SET ScriptName="go_kings_gate_196412" WHERE entry=196412;

UPDATE quest_template SET Flags=2359300, SpecialFlags=2 WHERE Id=14465;

UPDATE creature SET phaseId=0, phaseGroup=433 WHERE id=36453;

DELETE FROM npc_spellclick_spells WHERE npc_entry=44928;
INSERT INTO npc_spellclick_spells VALUES 
(44928, 46598, 0, 0);

DELETE FROM npc_spellclick_spells WHERE npc_entry=43336;
INSERT INTO npc_spellclick_spells VALUES 
(43336, 46598, 0, 0);

UPDATE creature_template SET npcflag=1 WHERE entry=44928;

UPDATE creature SET phaseId=194, spawndist=0, MovementType=0 WHERE id=38762;

UPDATE creature_template SET ScriptName="npc_ogre_ambusher_38762" WHERE entry=38762;



