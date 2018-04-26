
-- set gossip to Arcanist Delaris
UPDATE creature_template SET gossip_menu_id=12244 where entry=47341;

-- replace wrong questgiver picture and text..
UPDATE quest_template SET QuestGiverPortrait=16891, QuestGiverTargetName="Impsy", QuestGiverTextWindow="Capture Impsy" WHERE id=28000;

-- on quest accept we need the aura: see invisible spell 49416.. a spellcast from here give error message on screen
UPDATE quest_template SET RewardSpellCast=49416, SourceSpellId=0 WHERE id=28000;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Fangt Impsy" WHERE id=28000;

-- npc 10920, 10923, 10924, 22931, 11554 and more double spawn..
DELETE FROM creature WHERE guid in (130232, 130233, 130234, 130237, 130229);

-- wrong gameobject questgiver
DELETE FROM gameobject_questender WHERE id=164885;

-- missing random move 
UPDATE creature SET spawndist=10, MovementType=1 WHERE id=7097;

-- missing random move 
UPDATE creature SET spawndist=10, MovementType=1 WHERE id=8959;

-- double spawn
DELETE FROM creature WHERE guid IN 
(130084, 130083, 130074, 130070, 130050, 130047, 130043, 130018, 130085, 130245, 130208, 130188,
130187, 130180, 130156, 130148, 130147, 130145, 130144, 130137, 130101, 130100, 130095, 130246,
130015, 124398, 124396, 124365, 124363, 124266, 124264, 124263, 124262, 124122, 124034, 124401,
124423, 130009, 130008, 130007, 129939, 129935, 129931, 129875, 124265, 124453, 124452, 123939);

-- double spawn
DELETE FROM creature WHERE guid IN 
(130128, 130138, 130168, 130169, 130199, 130127, 130081, 130033, 129982, 129891,
 129888, 124461, 124367, 130200);
 
 -- double spawn
DELETE FROM creature WHERE guid IN 
(130023, 130021, 130017, 130002, 129936, 129998, 130024, 130025, 130167, 130157, 130155, 130146,
130103, 130102, 130094, 130071, 130056, 130052, 130027, 130026, 130201, 129933, 129932, 124428,
124386, 124370, 124026, 124021, 124015, 124014, 124013, 124009, 124429, 124459, 129930, 129900,
129897, 129893, 129892, 129887, 124030, 124464, 124463, 124005);

 -- double spawn
DELETE FROM creature WHERE guid IN 
(129953, 129972, 130048, 130049, 130051, 130053, 130054, 130055, 130058,
130059, 129952, 129951, 129950, 124376, 124387, 124454, 124455, 124457,
124460, 129940, 129947, 129948, 129949, 130062);

 -- double spawn
DELETE FROM creature WHERE guid IN 
(109823, 109838, 109863, 109873, 109915, 109933, 109966, 109974, 
109981, 110019, 110063, 110091, 110107, 110118, 110145, 110150, 
110170, 110259, 110262, 126070, 126099, 126191, 126231);
 
 -- double spawn
DELETE FROM creature WHERE guid IN 
(129851, 129849, 129847, 129846, 129845, 129838, 129852, 129853, 129854, 129855, 
129963, 129969, 129970, 129971, 129976, 130209, 130077, 124477, 123963, 123965, 
123979, 123984, 123986, 123990, 123991, 123992, 124466, 124468, 124469, 124471, 
124472, 124475, 124476, 123956);

 -- double spawn
DELETE FROM creature WHERE guid IN 
(124473, 124474, 129843, 129844, 129848, 129850, 129856, 129857, 130072, 
130073, 130189, 130223, 124470, 124465, 123946, 123951, 123955, 123969, 
123973, 123975, 123976, 123980, 124006, 124011, 124018, 124028, 124037, 
124040, 124045, 124080, 123940, 123940, 123940);

 -- double spawn
DELETE FROM creature WHERE guid=85259;

 -- double spawn
DELETE FROM creature WHERE guid IN 
(123947, 123952, 124001, 124007, 124047);

 -- double spawn
DELETE FROM creature WHERE guid IN 
(123944, 124054, 124019, 124017, 124003, 124002, 124000, 123999, 123977, 123964, 123978);

 -- double spawn
DELETE FROM creature WHERE guid IN 
(124094, 124076, 124053, 124041, 124038, 124031, 124025, 124024, 
123949, 123950, 123953, 123959, 123971, 123982, 124020, 124023, 123962);

-- enable quest and add some missing text in enUS and deDE
UPDATE quest_template SET method=2, Flags=16640 WHERE id=28396;

UPDATE quest_template SET RequestItemsText="While you have proven yourself to me, you may need to continue to work toward proving yourself to the suspicious brethren of my tribe.  To that end, I may be able to continue assisting you.$B$BSome of the Deadwood furbolgs wear a distinctive headdress that may be used as a means of proof in thinning their numbers.  Bring me a feather from any headdresses you acquire; for every set of five you bring me, you will earn recognition amongst the Timbermaw." WHERE id=28396;

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht, $N! Ich werde dafür Sorgen, dass alle Furbolgs der Holzschlundfeste von Euren Taten erfahren.$B$BVergesst nicht, mir alle Federn zu bringen, die Ihr findet." WHERE id=28396;
 
UPDATE locales_quest SET CompletedText_loc3="Kehrt zu Grazle im Teufelswald zurück." WHERE id=28396;
 
UPDATE quest_template SET PrevQuestId=28100, NextQuestId=0 WHERE id=27989;
UPDATE quest_template SET PrevQuestId=27989, NextQuestId=0 WHERE id=27994;
UPDATE quest_template SET PrevQuestId=27994, NextQuestId=0 WHERE id=27995;
UPDATE quest_template SET PrevQuestId=27995, NextQuestId=0 WHERE id=28150;
 
UPDATE quest_template SET PrevQuestId=28044, NextQuestId=0 WHERE id=28102; 
 
UPDATE quest_template SET PrevQuestId=28113, NextQuestId=0 WHERE id=28152; 
UPDATE quest_template SET PrevQuestId=28152, NextQuestId=0 WHERE id=28116;  
UPDATE quest_template SET PrevQuestId=28044, NextQuestId=0 WHERE id=28113; 
 
UPDATE quest_template SET PrevQuestId=28121, NextQuestId=0 WHERE id=28119; 

UPDATE quest_template SET PrevQuestId=28116, NextQuestId=0 WHERE id=28121; 

UPDATE quest_template SET PrevQuestId=28119, NextQuestId=0 WHERE id=28128; 
 
UPDATE quest_template SET PrevQuestId=28113, NextQuestId=0 WHERE id=28288; 
 
UPDATE quest_template SET PrevQuestId=27995, NextQuestId=0 WHERE id=28396;  
 
 
 
 
 
 
 