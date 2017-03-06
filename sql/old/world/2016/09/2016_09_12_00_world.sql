
delete from spell_script_names where spell_id=89842;

delete from vehicle_template_accessory where entry in (48805, 48806, 48719, 48721);
insert into vehicle_template_accessory values 
(48805, 48340, 0, 0, "KTC Waiter", 6, 30000),
(48805, 48341, 1, 0, "KTC Waiter", 6, 30000),
(48805, 48341, 2, 0, "KTC Waiter", 6, 30000),
(48805, 48342, 3, 0, "KTC Waiter", 6, 30000),
(48805, 48343, 4, 0, "KTC Waiter", 6, 30000),

(48806, 48340, 0, 0, "KTC Waitress", 6, 30000),
(48806, 48341, 1, 0, "KTC Waitress", 6, 30000),
(48806, 48341, 2, 0, "KTC Waitress", 6, 30000),
(48806, 48342, 3, 0, "KTC Waitress", 6, 30000),
(48806, 48343, 4, 0, "KTC Waitress", 6, 30000),

(48719, 48340, 0, 0, "KTC Waiter", 6, 30000),
(48719, 48341, 1, 0, "KTC Waiter", 6, 30000),
(48719, 48341, 2, 0, "KTC Waiter", 6, 30000),
(48719, 48342, 3, 0, "KTC Waiter", 6, 30000),
(48719, 48343, 4, 0, "KTC Waiter", 6, 30000),

(48721, 48340, 0, 0, "KTC Waitress", 6, 30000),
(48721, 48341, 1, 0, "KTC Waitress", 6, 30000),
(48721, 48341, 2, 0, "KTC Waitress", 6, 30000),
(48721, 48342, 3, 0, "KTC Waitress", 6, 30000),
(48721, 48343, 4, 0, "KTC Waitress", 6, 30000);

delete from npc_spellclick_spells where npc_entry in (48805, 48806, 48719, 48721, 48340, 48341, 48342, 48343);
insert into npc_spellclick_spells values 
(48805, 46598, 1, 0), -- ID - 90909 Drink Tray
(48806, 46598, 1, 0), -- ID - 89842 Drink Tray
(48719, 46598, 1, 0), 
(48721, 46598, 1, 0),

(48340, 89908, 1, 0), -- ID - 89908 Goblin Cocktail
(48341, 89908, 1, 0), 
(48342, 89908, 1, 0),
(48343, 89908, 1, 0);

update creature set phaseGroups="381 382 383 384" where id in (49338, 49339);

DELETE FROM creature WHERE guid in (18587, 18588, 18589);
INSERT INTO creature VALUES 
(18587, 34890, 648, 0, 0, 1, '', '378', 29482, 0, -8507.65, 1342.85, 101.78, 6.26573, 300, 0, 0, 71, 0, 0, 0, 0, 0),
(18588, 34892, 648, 0, 0, 1, '', '378', 29495, 0, -8068.13, 1482.03, 9.01469, 3.59538, 300, 0, 0, 71, 0, 0, 0, 0, 0),
(18589, 34954, 648, 0, 0, 1, '', '378', 32385, 0, -8179.48, 1321.38, 27.6826, 5.25344, 300, 0, 0, 71, 0, 0, 0, 0, 0);

UPDATE locales_quest SET ObjectiveText1_loc3="Schlüssel für den Hot Rod benutzt" WHERE Id=14071;

update creature_template set AIName="", ScriptName="npc_rod_hot_34840" where entry=34840;

DELETE FROM creature_template_addon WHERE entry=35239;
INSERT INTO creature_template_addon VALUES 
(35239, 0, 0, 0, 1, 233, "");

-- wrong queststarter.
DELETE FROM `creature_queststarter` WHERE `id`=37203 and `quest`=28414;

-- Spellclick conditions for bilgewater buccaneer.
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=18 AND `SourceGroup`=48526;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorType`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES 
(18,48526,70015,0,0,9,0,24502,0,0,0,0,0,'',NULL),
(18,48526,70075,0,0,9,0,24503,0,0,0,0,0,'',NULL),
(18,48526,70015,0,0,9,0,24503,0,0,1,0,0,'',NULL),
(18,48526,70075,0,0,9,0,24502,0,0,1,0,0,'',NULL);

-- Bilgewater Buccaneer spellclicks.
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` IN(48526,37179,37213);
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES 
(37213, 46598, 1, 0),
(37179, 70016, 3, 0),
(48526, 70015, 1, 0),
(48526, 70075, 1, 0);

UPDATE `creature_template` SET `npcflag`=16777216 WHERE entry IN(48526,37179,37213);

UPDATE quest_template SET RequiredNpcOrGo1=48323, RequiredNpcOrGoCount1=1 WHERE Id=14071;

UPDATE creature SET modelid=11686 WHERE guid=248977;
UPDATE creature_template SET InhabitType=5 WHERE entry=35193;

UPDATE creature_template SET VehicleId=448 WHERE entry=34840;


