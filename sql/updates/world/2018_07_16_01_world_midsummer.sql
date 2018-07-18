
-- enable all midsummer quest
UPDATE quest_template SET Method=2, Flags=65536, SpecialFlags=0 WHERE Title Like "Honor the Flame" and RewardItemId1=23247;

UPDATE quest_template SET Method=2, Flags=65536, SpecialFlags=0 WHERE Title Like "Desecrate this Fire!" and RewardItemId1=23247;

-- Incense for the Festival Scorchlings
UPDATE quest_template SET PrevQuestId=0, Method=2, Level=1 WHERE id=11966;

UPDATE quest_template SET PrevQuestId=0, Method=2, Level=1 WHERE id=11964;

delete from spell_script_names where spell_id in (45406, 45716, 46630, 45671, 46747, 45644, 45819);
insert into spell_script_names values
(45406, "spell_midsummer_ribbon_pole"),
(45716, "spell_midsummer_torch_quest"),
(46630, "spell_midsummer_torch_quest"),
(45671, "spell_midsummer_fling_torch"),
(46747, "spell_midsummer_fling_torch"),
(45644, "spell_midsummer_juggling_torch"),
(45819, "spell_midsummer_juggling_torch");

-- wrong bonfire in capital city
delete from gameobject where guid=6228; -- exodar
delete from gameobject where guid=6229; -- silvermoon
delete from gameobject where guid=6225; -- orgrimmar
delete from gameobject where guid=6227; -- mulgore
delete from gameobject where guid=6223; -- undercity
delete from gameobject where guid=6206; -- stormwind

delete from game_event_gameobject where guid in (6206,6223,6225,6227,6228,6229);

-- npc 48935 double empty equipment
DELETE FROM creature_equip_template WHERE entry=48935 AND id=2;

-- npc 47641 walk into the bonfire
UPDATE creature SET spawndist=4.0 WHERE guid=26327;

update locales_quest set Title_loc3="Ehrt die Flamme" where id in (28761,28923,28926,28928,28929,28932,28933,28946,28949);

-- the 1125 Crag Boar walking inside tree
UPDATE creature SET spawndist=5.0 WHERE guid=62834;

-- enable the quest
UPDATE quest_template SET Flags=143362, SpecialFlags=3, LimitTime=45, PrevQuestId=11882, RequiredSourceItemId1=25515, RequiredSourceItemCount1=8 WHERE id=11731;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, LimitTime=45, PrevQuestId=11915, RequiredSourceItemId1=34862, RequiredSourceItemCount1=8 WHERE id=11922;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, LimitTime=90, RequiredSourceItemId1=25515, RequiredSourceItemCount1=20 WHERE id=11921;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, LimitTime=90, RequiredSourceItemId1=25515, RequiredSourceItemCount1=20 WHERE id=11926;

UPDATE quest_template SET Flags=143362, SpecialFlags=3, RequiredSourceItemId1=25515, RequiredSourceItemCount1=4 WHERE id=11657;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, RequiredSourceItemId1=25515, RequiredSourceItemCount1=4 WHERE id=11923;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, RequiredSourceItemId1=25515, RequiredSourceItemCount1=10 WHERE id=11924;
UPDATE quest_template SET Flags=143362, SpecialFlags=3, RequiredSourceItemId1=25515, RequiredSourceItemCount1=10 WHERE id=11925;

-- remove the smartscript, is autocomplete the quest.. 
delete from smart_scripts where entryorguid in (25975, 26113);

-- the focus 1365 has range of sight = 100 
update gameobject_template set data1=100 where entry=300068;

UPDATE quest_template SET Level=1, Method=2 WHERE Level=-1 and Title LIKE "% the Elder";

UPDATE gossip_menu_option SET option_text="The Festival Talespinner asked me to speak with you.", OptionBroadcastTextID=25442 WHERE menu_id=9278 AND id=0;

UPDATE locales_gossip_menu_option SET option_text_loc3="Der Geschichtenerzähler hat mich gebeten, mit Euch zu sprechen." WHERE menu_id=9278 AND id=0;

UPDATE quest_template SET Level=1, PrevQuestId=11966 WHERE id=9339;

UPDATE quest_template SET Level=1, PrevQuestId=11964 WHERE id=9365;

delete from creature_queststarter where id=16818 and quest=9368;
insert into creature_queststarter values
(16818, 9368);

delete from creature_queststarter where id=16817 and quest=9367;
insert into creature_queststarter values
(16817, 9367);

UPDATE quest_template SET Level=1 WHERE id=11915;

UPDATE quest_template SET Level=1 WHERE id=11882;

update creature set position_x=9905.37, position_y=2226.02, position_z=1329.39, orientation=6.168 where id=6491 and guid=132655;

-- 2 missing spell focus
delete from gameobject_template where entry in (181371, 181377);
INSERT INTO gameobject_template 
(entry, type, displayId, name, IconName, castBarCaption, unk1, faction, flags, size, questItem1, questItem2, questItem3, questItem4, questItem5, questItem6, data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16, data17, data18, data19, data20, data21, data22, data23, data24, data25, data26, data27, data28, data29, data30, data31, unkInt32, AIName, ScriptName, VerifiedBuild) 
VALUES 
(181371, 8, 0, "Midsummer Bonfire Spell Focus", "", "", "",          0, 0, 1, 0, 0, 0, 0, 0, 0, 1365, 100, 181375, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", "", 1),
(181377, 8, 0, "Midsummer Bonfire Campfire Spell Focus", "", "", "", 0, 0, 1, 0, 0, 0, 0, 0, 0,    4, 100, 181376, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", "", 1);

delete from conditions where SourceTypeOrReferenceId=13 AND ConditionTypeOrReference=31 AND ConditionValue2=16592;
-- INSERT INTO `conditions` VALUES (13, 1, 28861, 0, 0, 31, 0, 3, 16592, 0, 0, 0, 0, '', NULL); -- ID - 28861 Holiday - Midsummer, Remove Bonfire
-- INSERT INTO `conditions` VALUES (13, 2, 28806, 0, 1, 31, 0, 3, 16592, 0, 0, 0, 0, '', NULL); -- ID - 28806 Toss Fuel on Bonfire

update quest_template set RequiredRaces=946 where id in (11581,11732,11734,11735,
         11736,11737,11738,11739,11740,11741,11742,11743,11744,11745,11746,11747,
		 11748,11749,11750,11751,11752,11753,11754,11755,11756,11757,11758,11759,
		 11760,11761,11762,11763,13440,13442,13443,13444,13445,13446,13447,13449);  -- nur H zulassen

update quest_template set RequiredRaces=2098253 where id in (11580,11764,11765,11766,
       11767,11768,11769,11770,11771,11772,11773,11774,11775,11776,11777,11778,11779,
	   11780,11781,11782,11783,11784,11785,11786,11787,11799,11800,11801,11802,11803,
	   13441,13450,13451,13453,13454,13455,13457,13458);  -- nur A zulassen

delete from spell_script_names where spell_id=29437;
insert into spell_script_names values 
(29437, "spell_toss_fuel_on_bonfire_29437");

update gameobject_template set faction=1735, AIName="", ScriptName="go_midsummer_bonfire" where name="Alliance Bonfire";

update gameobject_template set faction=1732, AIName="", ScriptName="go_midsummer_bonfire" where name="Horde Bonfire";

DELETE FROM game_event_gameobject WHERE guid IN (22029, 22040, 41836, 45339);

