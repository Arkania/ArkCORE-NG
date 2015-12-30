
delete from quest_poi_points where id=0 and questId in (10693, 10694, 26226, 28477, 24536, 26233, 26234);
delete from quest_poi_points where id=1 and questId in (11246, 11249, 11257, 11260, 25348, 26556);
delete from quest_poi_points where id=2 and questId in (25348);
-- delete from quest_poi_points where id=3 and questId in ();
delete from quest_poi_points where id=4 and questId in (11245, 11259, 26227);
delete from quest_poi_points where id=16 and questId in (25092);
delete from quest_poi_points where id=23 and questId in (12958);

delete from quest_poi where questId in (10693, 10694, 410694, 12619, 12842, 12848);

delete from creature where id in (15525, 15739, 15459, 15460, 15469, 15477, 15508, 15512, 15515, 15522, 15528, 15529, 15532, 15533, 15535, 15700, 24205, 15458, 3349, 15738, 15736);
delete from creature_questender where id in (15525, 15739, 15459, 15460, 15469, 15477, 15508, 15512, 15515, 15522, 15528, 15529, 15532, 15533, 15535, 15700, 24205, 15458, 3349, 15738, 15736);
delete from creature_queststarter where id in (15525, 15739, 15459, 15460, 15469, 15477, 15508, 15512, 15515, 15522, 15528, 15529, 15532, 15533, 15535, 15700, 24205, 15458, 3349, 15738, 15736);

delete from creature where id in (5885, 6018, 14727, 5883, 5882, 3373, 6014);
delete from creature where guid in (128083);
-- console errors
delete from disenchant_loot_template where entry in (59120, 59121, 65020, 67129);

delete from reference_loot_template where entry in (11050, 11051, 43296, 43722);

delete from game_event_creature where eventEntry=26 and guid=1364;
delete from game_event_creature where eventEntry=26 and guid=127047;

delete from fishing_loot_template where entry=4395 and item=11799;

update gameobject_loot_template set ChanceOrQuestChance=6 where entry=123329 and item in (69839, 69840, 69841);