
-- misc northern stranglethorn

-- comment by wowhead: quest-phased version of Nesingwary's Expedition in Northern Stranglethorn
-- They aren't attackable by players and seem to be there purely for cosmetic effect.
update creature_template set faction=14, minlevel=83, maxlevel=83, unit_flags=512 where entry=52173;

update creature set phaseMask=2 where id in (52173, 52184, 52291, 52293, 52294, 52295, 52296, 52297, 52298, 52821);

update creature set spawndist=0, MovementType=0 where id in (52295, 52296);

UPDATE quest_template SET Method=2 WHERE Id=26732;

UPDATE quest_template SET Method=2, Flags=0 WHERE Id in (7791, 7792, 7802, 7807, 7813, 7820, 7826, 7833, 10352, 10359);

UPDATE quest_template SET Method=2, Flags=0 WHERE Id in (7793, 7798, 7803, 7808, 7814, 7821, 7827, 7834, 10354, 10360);

UPDATE quest_template SET Method=2, Flags=524288 WHERE Id=14279;
