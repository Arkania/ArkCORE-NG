
-- quest 29573
UPDATE locales_quest SET Title_loc3="Sicherheit geht vor", Objectives_loc3="Tötet 10 astrale Grufträuber, 5 astrale Zauberer, 5 Nexuswandler und 5 astrale Zauberbinder. Kehrt danach zu Konstrukteur Morphalius zurück.", Details_loc3="Es ist hier jetzt fast so sicher, dass meine Leute kommen und sich holen können, was rechtmäßig ihnen gehört. Die einzig große, noch verbleibende Gefahr stellt Shaffars Leibgarde dar. Von der wimmelt es hier.$B$BKümmert Euch um diese Streitkräfte, während ich wieder zu Kräften komme.", OfferRewardText_loc3="Wunderbar! Haramad wird sich über die guten Neuigkeiten freuen! Dieser Ort wird ihm wie ein reifer Apfel in die Hand fallen.", CompletedText_loc3="Kehrt zu Konstrukteur Morphalius in Managruft zurück." WHERE Id=29573;

-- npc 18341
update creature_loot_template set Chance=100, QuestRequired=1 where entry=18341 and item=18344;

-- quest 29574
UPDATE locales_quest SET OfferRewardText_loc3="Diese Proben sind äußerst interessant. Sie werden mir sehr helfen.", RequestItemsText_loc3="Wenn Ihr nicht habt, wonach ich suche, verschwendet Ihr nur meine Zeit." WHERE Id=29574;

-- quest 29582
UPDATE locales_quest SET OfferRewardText_loc3="Der Hohlschädel hat stattdessen Euch geschickt?$B$B<Konstrukteur Morphalius mustert Euch.>$B$BDann werdet Ihr wohl genügen müssen." WHERE Id=29582;

-- npc chromie 26527
UPDATE npc_text SET BroadcastTextID0=27091 WHERE ID=12949;

UPDATE gossip_menu_option SET option_id=1, npc_option_npcflag=1, OptionBroadcastTextID=39667 WHERE menu_id=9586 AND id=2;

-- gameobject Suspicious Grain Crate 190094, Crate Highlight 190117
update gameobject set phaseMask=65535, position_x=1579.42, position_y=621.446, position_z=99.7329, orientation=2.9845 where id=190117 and guid =53392;
update gameobject set phaseMask=65535, position_x=1570.92, position_y=669.933, position_z=102.309, orientation=-1.64061 where id=190117 and guid =53394;
update gameobject set phaseMask=65535, position_x=1629.68, position_y=731.367, position_z=112.847, orientation=-0.837757 where id=190117 and guid =53410;
update gameobject set phaseMask=65535, position_x=1628.98, position_y=812.142, position_z=120.689, orientation=0.436332 where id=190117 and guid =53417;
update gameobject set phaseMask=65535, position_x=1674.39, position_y=872.307, position_z=120.394, orientation=-1.11701 where id=190117 and guid =53425;

delete from gossip_menu_option where menu_id=7769 and id=1;

update creature_template set AIName="", ScriptName="npc_erozion_18723" where entry=18723;
update creature_template set AIName="", ScriptName="npc_thrall_old_hillsbrad_17876" where entry=17876;
update creature_template set AIName="", ScriptName="npc_taretha_18887" where entry=18887;

UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Verdächtige Kornkiste", QuestGiverTargetName_loc3="Verdächtige Kornkiste" WHERE Id=13149;

UPDATE quest_template SET QuestGiverPortrait=38638, RequiredSourceItemId1=37888, RequiredSourceItemId2=0, RequiredSourceItemCount1=1, RequiredSourceItemCount2=0 WHERE Id=13149;

delete from creature where guid in (233744, 233745);
delete from creature_addon where guid in (233744, 233745); -- entry 27827

delete from creature where id=30996;

delete from creature where guid between 11757 and 11761;
insert into creature values 
(11757, 27827, 595, 3, 65535, 0, 0, 1579.42, 621.446, 99.4329, 2.9845, 300, 0, 0, 1, 0, 0, 0, 33554432, 0),
(11758, 27827, 595, 3, 65535, 0, 0, 1570.92, 669.933, 102.009, -1.64061, 300, 0, 0, 1, 0, 0, 0, 33554432, 0),
(11759, 27827, 595, 3, 65535, 0, 0, 1629.68, 731.367, 112.547, -0.837757, 300, 0, 0, 1, 0, 0, 0, 33554432, 0),
(11760, 27827, 595, 3, 65535, 0, 0, 1628.98, 812.142, 120.389, 0.436332, 300, 0, 0, 1, 0, 0, 0, 33554432, 0),
(11761, 27827, 595, 3, 65535, 0, 0, 1674.39, 872.307, 120.094, -1.11701, 300, 0, 0, 1, 0, 0, 0, 33554432, 0);

delete from gameobject where guid between 10017 and 10021;
insert into gameobject values 
(10017, 190094, 595, 3, 65535, 1579.42, 621.446, 99.7329, 2.9845, 0, 0, 0.969222, 0.24619, 300, 0, 1),
(10018, 190094, 595, 3, 65535, 1570.92, 669.933, 102.309, -1.64061, 0, 0, 0.756421, -0.654085, 300, 0, 1),
(10019, 190094, 595, 3, 65535, 1629.68, 731.367, 112.847, -0.837757, 0, 0, 0.996838, -0.0794628, 300, 0, 1),
(10020, 190094, 595, 3, 65535, 1628.98, 812.142, 120.689, 0.436332, 0, 0, 0.508174, -0.861254, 300, 0, 1),
(10021, 190094, 595, 3, 65535, 1674.39, 872.307, 120.394, -1.11701, 0, 0, 0.966241, -0.25764, 300, 0, 1);

-- chromie 27915 is spawned from script..
delete from creature where id=27915 and guid=233894;

-- quest 13151
UPDATE locales_quest SET EndText_loc3="", QuestGiverTextWindow_loc3="Prinz von Lordaeron", QuestGiverTargetName_loc3="Arthas" WHERE Id=13151;

UPDATE quest_template SET QuestGiverPortrait=24949, QuestGiverTextWindow="Prince of Lordaeron", QuestGiverTargetName="Arthas" WHERE Id=13151;

-- CoT Stratholme - Mal'Ganis KC Bunny



