
-- stranglethorn area..

UPDATE creature_template SET spell2=15038, questItem2=58901 WHERE entry=1490;

update creature_loot_template set Chance=75 where Entry=1490 and Item=4016;
update creature_loot_template set Chance=75 where Entry=1490 and Item=58901;

UPDATE quest_template SET Flags=134217736, SpecialFlags=0 WHERE Id=26551;
UPDATE quest_template SET Flags=134217736, SpecialFlags=0 WHERE Id=26810;

UPDATE quest_template SET Flags=786432 WHERE Id=26552;
UPDATE quest_template SET Flags=786432 WHERE Id=26811;

UPDATE quest_template SET Method=2, Flags=8192, SpecialFlags=1 WHERE Id=8193;

UPDATE locales_quest SET OfferRewardText_loc3="Beeilt Euch und reicht die Fische ein, wenn Ihr den Titel des Meisteranglers erwerben wollt! Ich stehe hier schon seit STUNDEN ohne etwas zu essen! Gebt mir die Viecher schon her!" WHERE Id=8193;

UPDATE quest_template SET Level=1 WHERE Id=8193;

UPDATE quest_template SET Method=2, Flags=8 WHERE Id=26597;

UPDATE quest_template SET Flags=8 WHERE Id=26697;

UPDATE creature_template SET questItem2=58812 WHERE entry=772;

UPDATE creature_template SET questItem2=58813 WHERE entry=1713;

update npc_trainer set spellcost=60, reqskill=573, reqLevel=3 where spell=774;

update npc_trainer set spellcost=60, reqskill=574, reqLevel=4 where spell=8921;

UPDATE quest_template SET Method=2, RequiredFactionId1=21, RequiredFactionValue1=-1, Flags=8456, SpecialFlags=1 WHERE Id=9259;

UPDATE quest_template SET RequiredRaces=946 WHERE Id=28750;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=28749;

delete from gameobject where guid=184345 and id=204828;


