
-- enable quest
UPDATE quest_template SET Method=2 WHERE Id=29073;

UPDATE quest_template SET Method=2 WHERE Id=24803;

UPDATE quest_template SET Method=2 WHERE Id=24806;

update reference_loot_template set ChanceOrQuestChance=1 where entry=11019 and item=41809;

