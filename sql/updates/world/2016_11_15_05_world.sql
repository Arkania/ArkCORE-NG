
update creature set equipment_id=0 where id=36346;

delete from vehicle_template_accessory where entry=28451 and accessory_entry=28468;
delete from vehicle_template_accessory where entry=28468 and accessory_entry=28451;

UPDATE quest_template SET RequiredNpcOrGo1=44175 WHERE Id=24968;

UPDATE creature_template SET KillCredit1=44175 WHERE entry=44794;

UPDATE locales_quest SET OfferRewardText_loc3="Glückwunsch... Einen Schritt näher, ein Meister der dunklen Künste zu sein. Geht und übt was Ihr gelernt habt, und kehrt zu mir zurück, wenn Ihr stärker geworden seid. Ich werde Euch dann mehr beibringen.", CompletedText_loc3="Kehrt zurück zu Maximillion in Todesend ", ObjectiveText1_loc3="Praktiziert Feuerbrand", QuestGiverTextWindow_loc3="Trainingsattrappe", QuestGiverTargetName_loc3="Trainingsattrappe" WHERE Id=24968;

UPDATE creature_template SET KillCredit1=1890 WHERE entry=1501;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=26550;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=26809;

UPDATE gossip_menu_option SET OptionBroadcastTextID=43278, option_id=1, npc_option_npcflag=1 WHERE menu_id=11711 AND id=1;

delete from playercreateinfo_spell where spell=21184;

delete from playercreateinfo_spell_custom where spell=21184;

UPDATE gameobject_template SET ScriptName="go_totem_of_hireek_204361" WHERE entry=204361;

UPDATE creature_template SET ScriptName="npc_wings_of_hireek_43241" WHERE entry=43241;

UPDATE creature_addon SET path_id=0 WHERE guid=23606;

update creature set MovementType=0 where guid=23606;

DELETE FROM waypoint_data WHERE id=4324101;
INSERT INTO waypoint_data VALUES 
(4324101, 0, -13355.46, -27.00635, 29.44026, 2.296905, 0, 1, 0, 100, 0),
(4324101, 1, -13414.58, 51.79816, 50.77106, 2.241927, 0, 1, 0, 100, 0),
(4324101, 2, -13437.19, 60.55619, 51.91462, 2.772071, 0, 1, 0, 100, 0),
(4324101, 3, -13461.38, 48.5985, 50.07495, 3.600666, 0, 1, 0, 100, 0),
(4324101, 4, -13512.21, -30.01856, 52.60163, 4.185785, 0, 1, 0, 100, 0),
(4324101, 5, -13554.48, -159.7719, 65.9166, 4.401769, 0, 1, 0, 100, 0),
(4324101, 6, -13579.08, -226.4927, 55.10126, 4.342866, 0, 1, 0, 100, 0),
(4324101, 7, -13632.46, -267.0449, 38.59391, 3.820577, 0, 1, 0, 100, 0),
(4324101, 8, -13656.7, -280.7307, 31.21223, 3.667424, 0, 1, 0, 100, 0),
(4324101, 9, -13668.84, -307.8107, 31.17233, 4.393916, 0, 1, 0, 100, 0),
(4324101, 10, -13657.92, -335.2852, 27.2471, 5.273562, 0, 1, 0, 100, 0),
(4324101, 11, -13646.92, -329.5979, 20.36576, 1.036335, 0, 1, 0, 100, 0),
(4324101, 12, -13645.7, -325.3626, 17.69689, 1.452596, 0, 1, 0, 100, 0),
(4324101, 13, -13649.35, -320.3016, 14.33958, 2.10055, 0, 1, 0, 100, 0),
(4324101, 14, -13649.7, -319.7023, 14.33208, 2.10055, 0, 1, 0, 100, 0);

DELETE FROM creature_text WHERE entry=43245;
INSERT INTO creature_text VALUES 
(43245, 1, 0, "Jin'do the Hexxer!  It's been a while since I've seen that mask.", 12, 0, 100, 0, 0, 0, "Zanzil the Outcast", 43362),
(43245, 2, 0, "What brings you out to my part of Stranglethorn?  I'm not accustomed to taking visitors from the esteemed Zul'Gurub.", 12, 0, 100, 0, 0, 0, "Zanzil the Outcast", 43363),
(43245, 3, 0, "What a shame... but not a concern for an old exile like Zanzil.", 12, 0, 100, 0, 0, 0, "Zanzil the Outcast", 43366),
(43245, 4, 0, "Friend?  You were among those who spit and threw stones, Jin'do.  But let's let bygones be bygones, eh?", 12, 0, 100, 0, 0, 0, "Zanzil the Outcast", 43369),
(43245, 5, 0, "So your bat and your snake need Zanzil's help?  Very well.  I'll see you inside Zul'Gurub... old friend.", 12, 0, 100, 0, 0, 0, "Zanzil the Outcast", 43370);

DELETE FROM creature_text WHERE entry=43246;
INSERT INTO creature_text VALUES 
(43246, 1, 0, "You know well enough about why I'm here, Zanzil.", 12, 0, 100, 0, 0, 0, "Shade of the Hexxer", 43364),
(43246, 2, 0, "The Gurubashi have fallen on hard times.  I live, and Mandokir has returned... but the rest of us are gone.", 12, 0, 100, 0, 0, 0, "Shade of the Hexxer", 43365),
(43246, 3, 0, "Well, Zanzil, I'd like to make it your concern.  I've recovered the bodies of High Priestess Jeklik and High Priest Venoxis.", 12, 0, 100, 0, 0, 0, "Shade of the Hexxer", 43367),
(43246, 4, 0, "I remember what you can do with those elixirs of yours.  Can your elixirs help out an old friend?", 12, 0, 100, 0, 0, 0, "Shade of the Hexxer", 43368);

delete from gossip_menu where entry=15145;

UPDATE creature_template SET InhabitType=4 WHERE entry=43241;

delete from creature where guid=66627;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id in (26810, 26811, 26812, 26813, 26814);

UPDATE quest_template SET RequiredRaces=946 WHERE Id in (26551, 26552, 26553, 26554, 26555);


