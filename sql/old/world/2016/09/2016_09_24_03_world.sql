
UPDATE creature_template SET ScriptName="npc_chip_endale_35054" WHERE entry=35054;

DELETE FROM creature_text WHERE entry=35054 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(35054, 0, 0, "Make sure you pull plenty of moolah out of the bank. I don't want you buying any of that cheap clothing you usually like to wear. This party's important!", 12, 0, 100, 0, 0, 0, "Chip Endale", 49022);

DELETE FROM creature_text WHERE entry=35054 AND groupid=1 AND id=0;
INSERT INTO creature_text VALUES 
(35054, 1, 0, "You're dressed to impress! Use your new powers below to make your party guests happy!", 12, 0, 100, 0, 0, 0, "Chip Endale", 35444);

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_partygoer_35175" WHERE entry=35175;

UPDATE creature_template SET AIName="", ScriptName="npc_kezan_partygoer_35186" WHERE entry=35186;

DELETE FROM creature WHERE id=24110 AND guid=254315;
INSERT INTO creature VALUES 
(254315, 24110, 648, 0, 0, 1, "379", 0, 0, -8482.854, 1341.462, 112.348, 0, 500, 0, 0, 6141, 0, 0, 0, 0, 0);

UPDATE creature_template SET AIName="", ScriptName="npc_elm_general_purpose_bunny_large_24110" WHERE entry=24110;

delete from smart_scripts where entryorguid in (24110, 35175, 35186);

UPDATE creature_template SET InhabitType=2 WHERE entry=35185;

UPDATE creature_template_addon SET bytes1=50331648 WHERE entry=35185;

UPDATE creature_template SET ScriptName="" WHERE entry=35185;

UPDATE gameobject_template SET ScriptName="go_kajamite_deposit_195488" WHERE entry=195488;

update gameobject set phaseIds="378 379 380 382" where id=195489;

