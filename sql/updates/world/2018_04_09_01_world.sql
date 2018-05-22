
UPDATE creature_template SET InhabitType=4, speed_run=1.42857, AIName='',ScriptName='npc_feralas_hippogryph_5300' WHERE entry IN (5300, 5304);

UPDATE creature_template SET AIName='',ScriptName='npc_wandering_forest_walker_7584' WHERE entry=7584;

UPDATE creature_template SET equipment_id=40069, AIName='',ScriptName='npc_horde_poacher_40069' WHERE entry=40069;

UPDATE creature_template SET minlevel=36, maxlevel=37, faction=83, mindmg=51, maxdmg=68, attackpower=124, minrangedmg=35, maxrangedmg=52, rangedattackpower=12 WHERE entry=40069; -- 1801 or 83

UPDATE quest_template SET QuestGiverPortrait=3210, QuestGiverTargetName="Frayfeather Hippogryph", QuestGiverTextWindow="Frayfeather Hippogryph" WHERE id=25409;

UPDATE quest_template SET QuestGiverPortrait=9592, QuestGiverTargetName="Wandering Forest Walker", QuestGiverTextWindow="Wandering Forest Walker" WHERE id=25410;

DELETE FROM smart_scripts where entryorguid IN (5300, 5304, 7584, 40069);

UPDATE creature SET spawndist=0, MovementType=0 WHERE id IN (5300, 5304);

UPDATE creature SET spawndist=10, MovementType=1 WHERE id IN (7584, 5260, 5268);

DELETE FROM creature_equip_template WHERE entry=40069;
INSERT INTO creature_equip_template VALUES 
(40069, 1, 33318, 0, 2551);

UPDATE locales_creature_text SET text_loc3="%s gerät in Raserei!" WHERE entry=40069 AND groupid=0 AND id=0;

UPDATE locales_quest set QuestGiverTargetName_loc3="Fransenfederhippo", QuestGiverTextWindow_loc3="Versammelt Fransenfederhippogryphen oder Fransenfederflügler" WHERE id=25409;

UPDATE locales_quest set QuestGiverTargetName_loc3="Waldgänger", QuestGiverTextWindow_loc3="Versammelt wandernde Waldgänger" WHERE id=25410;

UPDATE locales_quest set OfferRewardText_loc3="Irrwische haben immer in Harmonie mit Nachtelfen gelebt, und bei einigen Dingen sind wir sogar von ihnen abhängig. Diese kleinen Jungs, die Sie zurückgeschickt haben, werden uns zum Beispiel bei neuen Konstruktionen und Reparaturen helfen.$B$BBereit für mehr?" WHERE id=25407;

UPDATE locales_quest set ObjectiveText1_loc3="Irrwische versammelt?" WHERE id=25407;

UPDATE locales_quest set CompletedText_loc3="Kehrt zu Tierführerin Tessina am Turm von Estulan in Feralas zurück." WHERE id=25407;

UPDATE locales_quest set OfferRewardText_loc3="Ein richtig ausgebildetes Geschwader von Hippogryphen kann fast jedem Gegner wiederstehen. Die Mondfederfeste wird mit diesen edlen Bestien auf unserer Seite viel sicherer sein." WHERE id=25409;

UPDATE locales_quest set ObjectiveText1_loc3="Hippogryphen versammelt" WHERE id=25409;

UPDATE locales_quest set OfferRewardText_loc3="Ihr mögt es nicht bemerkt haben, aber einige Treants sind zu uralten Beschützern geworden. Wir könnten ein paar mehr von denen hier verwenden..." WHERE id=25410;

UPDATE locales_quest set ObjectiveText1_loc3="Treants  versammelt?" WHERE id=25410;
