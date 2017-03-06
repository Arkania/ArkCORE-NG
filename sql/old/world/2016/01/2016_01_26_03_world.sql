

UPDATE quest_template SET PrevQuestId=14138 WHERE Id=14075;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Vorarbeiter Feuchtlunte im Hauptgeschäftssitz der HGK auf Kezan zurück." WHERE Id=14075;

UPDATE quest_template SET PrevQuestId=14138 WHERE Id=14069;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Vorarbeiter Feuchtlunte im Hauptgeschäftssitz der HGK auf Kezan zurück." WHERE Id=14069;

UPDATE quest_template SET Method=2, PrevQuestId=14071, Flags=8200 WHERE Id=28607;

UPDATE quest_template SET PrevQuestId=14138, SpecialFlags=4 WHERE Id=25473;
UPDATE quest_template SET SpecialFlags=4 WHERE Id=14069;
UPDATE quest_template SET SpecialFlags=4 WHERE Id=14075;

delete from creature_queststarter where id=34872 and quest=14138;

delete from creature where guid=249045 and id=48519;

delete from gameobject where guid=168380 and id=207761;

update gameobject set phaseMask=640 where id in (207311, 207312, 207313, 207314, 207315, 207316);

DELETE FROM `smart_scripts` WHERE `entryorguid`=34696 AND `id`=0 AND `source_type`=0 LIMIT 1;
DELETE FROM `smart_scripts` WHERE `entryorguid`=34689 AND `id`=0 AND `source_type`=0 LIMIT 1;

update creature_template set AIName="", ScriptName="npc_fizz_lighter_34689" where entry=34689;
update creature_template set AIName="", ScriptName="npc_evol_fingers_34696" where entry=34696;

