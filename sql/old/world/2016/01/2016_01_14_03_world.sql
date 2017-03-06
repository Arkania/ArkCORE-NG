
delete from smart_scripts where entryorguid=38288;

delete from gameobject_queststarter where id=206111 and quest=28825;
insert into gameobject_queststarter values
(206111, 28825);

delete from creature_queststarter where id=45226 and quest=28825;

-- QuestGiverPortrait has someone the correct id??
UPDATE quest_template SET RequiredRaces=2098253, QuestGiverPortrait=34336 WHERE Id=28825;

UPDATE quest_template SET Flags=524288, SpecialFlags=4 WHERE Id=14482;

UPDATE creature_template SET InhabitType=3 WHERE entry in (40770, 41808, 40753);

update creature set spawndist=25, MovementType=1 where id=40370;
update creature set spawndist=20, MovementType=1 where id=36629;
update creature set spawndist=15, MovementType=1 where id=43180;
update creature set spawndist=15, MovementType=1 where id=40276;
update creature set spawndist=20, MovementType=1 where id=39918;
update creature set spawndist=20, MovementType=1 where id=41808;
update creature set spawndist=25, MovementType=1 where id=41809;
update creature set spawndist=20, MovementType=1 where id=40753;

delete from creature where guid=9740 and id=40746;
delete from creature where guid=12678 and id=51475;
delete from creature where guid in (12759, 12760) and id=41750;


