
-- darkmoon faire 
update creature set spawndist=0, MovementType=0 where id=55093 and guid=53383;
update creature set spawndist=0, MovementType=0 where id=55089 and guid=56650;

update creature_template set AIName="", ScriptName="npc_fire_juggler_generic" where entry in (55089, 55093);

update creature_template_addon set auras="" where entry in (55089, 55093);

UPDATE creature_template SET minlevel=35, maxlevel=35, faction=1555, scale=1.0 WHERE entry=56069;

update creature set phaseMask=2 where id=33286 and guid=270418;

delete from gameobject where guid in (182470, 182471);
INSERT INTO `gameobject` VALUES 
(182470, 210175, 974, 1, 1, -4447.76, 6327.07, 13.2646, 0, 0, 0, 0, 1, 300, 255, 1),
(182471, 210176, 974, 1, 1, -4447.96, 6331.43, 13.2646, 0, 0, 0, 0, 1, 300, 255, 1);

UPDATE creature_template SET scale=1, name="Steven Stagnaro", subname="Fishing Trainer", IconName="" WHERE entry=56068;

update creature set spawndist=0, MovementType=0 where guid=270789;

update creature_template set faction=1555 where entry=35642;

update creature_template set faction=35 where entry=56041;


