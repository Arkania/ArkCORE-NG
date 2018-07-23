
UPDATE creature_template SET npcflag=0, dynamicflags=0, unit_flags2=34816, equipment_id=0, mechanic_immune_mask=16384, ScriptName="npc_bilgewater_buccaneer_48526" WHERE entry=48526;

-- this entry 
DELETE FROM creature_equip_template WHERE entry IN (48526);

update creature set equipment_id=0 where id=48526 and guid=249060;

update creature set MovementType=0, spawndist=0 where guid=284774;

update creature_addon set path_id=0 where guid=284774;

delete from waypoint_data where id=284774;

delete from npc_spellclick_spells where npc_entry=48526;
insert into npc_spellclick_spells values 
(48526, 70015, 1, 0),
(48526, 70075, 1, 0);

delete from conditions where SourceTypeOrReferenceId=SourceTypeOrReferenceId AND SourceGroup=48526;
insert into conditions values 
(18, 48526, 70015, 0, 0, 9, 0, 24502, 0, 0, 0, 0, 0, "", ""),  -- SPELL_CLICK_EVENT, Bilgewater Buccaneer, Summon Bilgewater Buccaneer 37179, CONDITION_QUESTTAKEN, Necessary Roughness, 
(18, 48526, 70015, 0, 0, 9, 0, 24503, 0, 0, 1, 0, 0, "", ""),  -- NegativeCondition
(18, 48526, 70075, 0, 0, 9, 0, 24502, 0, 0, 1, 0, 0, "", ""),  -- NegativeCondition
(18, 48526, 70075, 0, 0, 9, 0, 24503, 0, 0, 0, 0, 0, "", "");

update creature_template set npcflag=2 where entry=42466;

delete from game_event_gameobject where guid=6213;

UPDATE quest_template SET PrevQuestId=24567, NextQuestId=0 WHERE id=24521;

UPDATE quest_template SET PrevQuestId=24521, NextQuestIdChain=0 WHERE id=24488;

UPDATE quest_template SET NextQuestIdChain=0 WHERE id=24502;

UPDATE quest_template SET NextQuestId=0, NextQuestIdChain=0 WHERE id=24503;

UPDATE quest_template SET PrevQuestId=24503 WHERE id=24520;

UPDATE quest_template SET NextQuestId=0 WHERE id=14138;

UPDATE quest_template SET ExclusiveGroup=-14069, NextQuestIdChain=25473 WHERE id=14069;

UPDATE quest_template SET ExclusiveGroup=-14069, NextQuestIdChain=25473 WHERE id=14075;

UPDATE quest_template SET PrevQuestId=14071, NextQuestId=0, ExclusiveGroup=0 WHERE id=26712;

UPDATE quest_template SET PrevQuestId=14070 WHERE id=24567;

UPDATE quest_template SET PrevQuestId=24520, ExclusiveGroup=14113 WHERE id=14113;

UPDATE quest_template SET PrevQuestId=24520, ExclusiveGroup=14113, NextQuestIdChain=14115 WHERE id=14153;

UPDATE quest_template SET PrevQuestId=0, NextQuestIdChain=0 WHERE id=14115;

UPDATE quest_template SET NextQuestIdChain=0 WHERE id=14116;

UPDATE quest_template SET Flags=65536 WHERE id=14239;

UPDATE quest_template SET Flags=262152 WHERE id=24521;

DELETE FROM creature_queststarter WHERE id=35120 AND quest=26712;

UPDATE quest_template SET RequiredGender=1, PrevQuestId=14071, NextQuestId=0, ExclusiveGroup=0 WHERE id=26711;

UPDATE quest_template SET RequiredGender=0, PrevQuestId=14071, NextQuestId=0, ExclusiveGroup=0 WHERE id=26712;

UPDATE quest_template SET RequiredGender=1 WHERE id=14110;

UPDATE quest_template SET RequiredGender=0 WHERE id=14109;

DELETE FROM phase_area WHERE areaId=4737 and entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 0, 14138, 0, 75, 0, 1, "Kezan enable phase from start");

DELETE FROM phase_area WHERE areaId=4737 and entry=1;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 1, 14138, 24520, 75, 11, 1, "Kezan from start to not rewarded 24520 ");

DELETE FROM phase_area WHERE areaId=4737 and entry=2;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 2, 24520, 14113, 64, 11, 1, "Kezan from rewarded 24520 to not rewarded 14113");

DELETE FROM phase_area WHERE areaId=4737 and entry=3;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4737, 3, 24520, 14153, 64, 11, 1, "Kezan from rewarded 24520 to not rewarded 14153");

UPDATE phase_area SET comment="Kezan Female  from reward 14113 to not reward 14115" WHERE areaid=4737 AND entry=4;

UPDATE phase_area SET comment="Kezan Male from reward 14153 to not reward 14115" WHERE areaid=4737 AND entry=5;

UPDATE phase_area SET comment="Kezan from reward 14115 to not reward 14116" WHERE areaid=4737 AND entry=6;

UPDATE phase_area SET comment="Kezan from reward 14116 to not reward 14120" WHERE areaid=4737 AND entry=7;

DELETE FROM phase_area WHERE areaid=4737 AND entry=8;
INSERT INTO phase_area 
(areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment)
VALUES
(4737, 8, 14120, 14122, 64, 9, 1, "Kezan from reward 14120 to not completed 14122");

DELETE FROM phase_area WHERE areaid=4737 AND entry=9;
INSERT INTO phase_area 
(areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment)
VALUES
(4737, 9, 14122, 14126, 66, 75, 1, "Kezan from completed14122 to end of last quest and area");

DELETE FROM phase_definitions WHERE zoneId=4737 and entry=0;
INSERT INTO phase_definitions (zoneId, entry, phaseId, phaseGroup, terrainswapmap, worldMapAreaSwap, flags, comment) values 
(4737, 0, 378, 0, 0, 0, 1, "Kezan from start to not rewarded 24520");

DELETE FROM phase_definitions WHERE zoneId=4737 and entry=1;
INSERT INTO phase_definitions (zoneId, entry, phaseId, phaseGroup, terrainswapmap, worldMapAreaSwap, flags, comment) values 
(4737, 1, 378, 0, 0, 0, 1, "Kezan from start to not rewarded 24520");

DELETE FROM phase_definitions WHERE zoneId=4737 and entry=2;
INSERT INTO phase_definitions (zoneId, entry, phaseId, phaseGroup, terrainswapmap, worldMapAreaSwap, flags, comment) values 
(4737, 2, 379, 0, 0, 0, 1, "Kezan from rewarded 24520 to not rewarded 14113");

DELETE FROM phase_definitions WHERE zoneId=4737 and entry=3;
INSERT INTO phase_definitions (zoneId, entry, phaseId, phaseGroup, terrainswapmap, worldMapAreaSwap, flags, comment) values 
(4737, 3, 379, 0, 0, 0, 1, "Kezan from rewarded 24520 to not rewarded 14153");

UPDATE phase_definitions SET comment="Kezan from reward 14120/14122" WHERE zoneid=4737 AND entry=8;

UPDATE phase_definitions SET comment="Kezan from reward 14122/14126" WHERE zoneid=4737 AND entry=9;

DELETE FROM creature_queststarter WHERE id=37106 AND quest=24567;

UPDATE quest_template SET Details="$N, Coach Crosscheck, the leader of our fearless Bilgewater Buccaneers, is looking for you.$B$BHe says that the division title against the Steamwheedle Sharks is on the line and that you\'re the only one that can bring it home for us!$B$BHead west into town. You can\'t miss Kajaro Field!$B$BA footbomb star. This is going to be great for your image!", OfferRewardText="There you are, my boy! Quick, there\'s no time to waste! We need to get one of these shredders back in working order.$B$BI\'m bringing you off the bench... you\'re going to win the game and the title for us!" WHERE id=24521;

UPDATE locales_quest SET Title_loc3="Meldet Euch für ein Testspiel", Details_loc3="$N, Trainer Blutgrätsch, der Kopf unserer furchtlosen Bilgewasserbukaniere, sucht Euch.$B$BEr sagt, dass der Ligatitel gegen die Dampfdruckhaie in Gefahr ist und dass nur Ihr den Pokal nach Hause holen könnt!$B$BGeht nach Westen in die Stadt. Ihr könnt das Kajarofeld nicht verfehlen!$B$BEin Fußbombenstar. Das wird sich hervorragend auf Euer Image auswirken!", Objectives_loc3="Sprecht mit Trainer Blutgrätsch auf dem Kajarofeld auf Kezan.", OfferRewardText_loc3="Da seid Ihr ja, mein $GJunge:Mädchen;! Schnell, wir haben keine Zeit zu verlieren! Wir müssen diese Schredder wieder funktionstüchtig machen.$B$BIch hole Euch von der Ersatzbank... Ihr werdet das Spiel und den Titel für uns gewinnen!" WHERE id=24521;

DELETE FROM creature_queststarter WHERE id=34668 AND quest=24521;
INSERT INTO creature_queststarter VALUES 
(34668, 24521);

DELETE FROM creature_questender WHERE id=37106 AND quest=24521;
INSERT INTO creature_questender VALUES 
(37106, 24521);

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=24521, NextQuestIdChain=24488 WHERE id=24567;

UPDATE quest_template SET PrevQuestId=14070, NextQuestId=24488, ExclusiveGroup=24521, NextQuestIdChain=24488 WHERE id=24521;

UPDATE creature_template SET dynamicflags=0 WHERE entry=49150;

UPDATE creature_template_addon SET auras="91603" WHERE entry=49150;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14007;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14008;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14009;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14010;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14011;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14012;

UPDATE quest_template SET NextQuestId=24488, ExclusiveGroup=14007, NextQuestIdChain=24488 WHERE id=14013;

UPDATE quest_template SET RequiredNpcOrGo1=44175, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=2, RequiredNpcOrGoCount2=0 WHERE id=14008;

UPDATE quest_template SET RequiredNpcOrGo1=44175, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=3, RequiredNpcOrGoCount2=0 WHERE id=14010;

UPDATE quest_template SET RequiredNpcOrGo1=44175, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=3, RequiredNpcOrGoCount2=0 WHERE id=14012;

UPDATE quest_template SET RequiredNpcOrGo1=44175, RequiredNpcOrGo2=0, RequiredNpcOrGoCount1=1, RequiredNpcOrGoCount2=0 WHERE id=14013;

UPDATE creature SET phaseId=384 WHERE guid=272089;

DELETE FROM creature WHERE guid=272091;

UPDATE creature_template SET dynamicflags=0 WHERE entry=34668;

DELETE FROM creature WHERE guid=282930;

DELETE FROM creature WHERE guid=282931;

DELETE FROM creature WHERE guid=279168;

UPDATE quest_template SET NextQuestId=14122, NextQuestIdChain=14122 WHERE id=14121;

UPDATE quest_template SET NextQuestId=14122, NextQuestIdChain=14122 WHERE id=14123;

UPDATE quest_template SET PrevQuestId=14120, NextQuestId=14122, ExclusiveGroup=-14121, NextQuestIdChain=14122 WHERE id=14124;

UPDATE quest_template SET PrevQuestId=0, NextQuestId=0, ExclusiveGroup=0, NextQuestIdChain=0 WHERE id=14122;

UPDATE quest_template SET PrevQuestId=14122 WHERE id=14125;

DELETE FROM creature_queststarter WHERE id=34668 AND quest=14120;

DELETE FROM creature WHERE guid=272108;

delete from gameobject where id=188215 and guid in (57894, 57896, 168405);

UPDATE gameobject SET phaseId=385, phaseGroup=0 WHERE guid=57928;

UPDATE gameobject SET phaseId=0, phaseGroup=571 WHERE guid=168605;

UPDATE gameobject_template SET ScriptName="go_flammable_bed_201734" WHERE entry=201734;

UPDATE gameobject_template SET ScriptName="go_gasbot_control_panel_202850" WHERE entry=202850;

delete from gameobject where id=202850 and guid=57928;




