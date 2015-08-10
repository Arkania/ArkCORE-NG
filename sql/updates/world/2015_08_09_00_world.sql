
update creature_template set AIName="", ScriptName="npc_dark_rider_of_acherus_28768" where entry=28768;
update creature_template set AIName="", ScriptName="boss_ragnaros_firelands" where entry=52409;
update creature_template set AIName="", ScriptName="npc_engulfing_flames" where entry=53485;



update creature_template set difficulty_entry_1=53797, difficulty_entry_2=53798, difficulty_entry_3=53799 where entry=52409;

update gameobject_template set flags=32  where entry=280000;

update gameobject_template set flags=32, data0=1 where entry=209098;

update creature_template set InhabitType=4 where entry=53245;

UPDATE quest_template SET Flags=8 WHERE Id=27726;

UPDATE locales_quest SET OfferRewardText_loc3="Vielleicht könnt Ihr ja helfen, $C." WHERE Id=28578;
UPDATE quest_template SET Method=2 WHERE Id=28578;


-- http://de.wowhead.com/npc=15187/cenarius-abgesandte-jademond

UPDATE `creature_template` SET `faction`=16 WHERE `entry`=51119;
UPDATE `creature_template` SET `unit_class`=2 WHERE `entry`=51119;
UPDATE `creature_template` SET `faction`=16 WHERE `entry`=49973;
UPDATE `creature_template` SET `faction`=16 WHERE `entry`=49979;
UPDATE `creature_template` SET `faction`=16 WHERE `entry`=49985;
UPDATE `creature_template` SET `faction`=2234 WHERE `entry`=53797;
UPDATE `creature_template` SET `faction`=2234 WHERE `entry`=53798;
UPDATE `creature_template` SET `faction`=2234 WHERE `entry`=53799;



