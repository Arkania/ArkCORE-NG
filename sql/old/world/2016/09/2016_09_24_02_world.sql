

UPDATE quest_template SET RequiredSourceItemId1=47044, RequiredSourceItemId4=0, RequiredSourceItemCount1=10, RequiredSourceItemCount4=0 WHERE Id=14110;

UPDATE quest_template SET RequiredSourceItemId1=47044, RequiredSourceItemId4=0, RequiredSourceItemCount1=10, RequiredSourceItemCount4=0 WHERE Id=14109;

UPDATE creature_template SET gossip_menu_id=10618, ScriptName="npc_fbok_bank_teller_35120" WHERE entry=35120;

UPDATE quest_template SET RewardSpell=0 WHERE Id=14110;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35363 WHERE menu_id=10622 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35383 WHERE menu_id=10624 AND id=0;

UPDATE gossip_menu_option SET OptionBroadcastTextID=35354 WHERE menu_id=10620 AND id=0;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14113;

UPDATE quest_template SET ExclusiveGroup=0 WHERE Id=14153;

delete from phase_definitions where zoneId=4737;
insert into phase_definitions values 
(4737, 0, 378, 0, 0, 1, "Kezan from start to -Reward 14109"),
(4737, 1, 378, 0, 0, 1, "Kezan from start to -Reward 14110"),
(4737, 2, 379, 0, 0, 1, "Kezan from reward 14109/14109"),
(4737, 3, 379, 0, 0, 1, "Kezan from reward 14110/14110"),
(4737, 4, 380, 0, 0, 1, "Kezan from reward 14113/14113"),
(4737, 5, 380, 0, 0, 1, "Kezan from reward 14153/14153"),
(4737, 6, 381, 0, 0, 1, "Kezan from reward 14115/14115"),
(4737, 7, 382, 0, 0, 1, "Kezan from reward 14116/14116"),
(4737, 8, 383, 0, 0, 1, "Kezan from reward 14120/14120"),
(4737, 9, 384, 0, 0, 1, "Kezan from reward 14122/14122");

delete from phase_area where areaId=4737;
insert into phase_area values 
(4737, 0, 14138, 14109, 75, 11, 1, "Kezan from start to -reward 14109"),
(4737, 1, 14138, 14110, 75, 11, 1, "Kezan from start to -reward 14110"),
(4737, 2, 14109, 14113, 64, 11, 1, "Kezan from reward Female 14109 to -reward 14113"),
(4737, 3, 14110, 14153, 64, 11, 1, "Kezan from reward Male   14110 to -reward 14153"),
(4737, 4, 14113, 14115, 64, 11, 1, "Kezan from reward Female 14113 to -reward 14115"),
(4737, 5, 14153, 14115, 64, 11, 1, "Kezan from reward Male   14153 to -reward 14115"),
(4737, 6, 14115, 14116, 64, 11, 1, "Kezan from reward 14115 to -reward 14116"),
(4737, 7, 14116, 14120, 64, 11, 1, "Kezan from reward 14116 to -reward 14120"),
(4737, 8, 14120, 14122, 64, 11, 1, "Kezan from reward 14120 to -reward 14122"),
(4737, 9, 14122, 14126, 64, 11, 1, "Kezan from reward 14122 to -reward 14126");









