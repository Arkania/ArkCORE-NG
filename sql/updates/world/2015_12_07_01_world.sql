
-- quest 26073 26074

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Krom'gar hat seinen Champion geschickt! Ihr müsst Euch keine Sorgen machen, Champion. Wir tanken den Ballon rasch wieder auf. Wollt Ihr uns in der Zwischenzeit ein wenig helfen?", CompletedText_loc3="Meldet Euch bei Jibbly Rakit in den Schlickwerken im Steinkrallengebirge.", QuestGiverTextWindow_loc3="Heißluftballon von Krom'gar", QuestGiverTargetName_loc3="Heißluftballon von Krom'gar" WHERE Id=26074;
UPDATE locales_quest SET OfferRewardText_loc3="Lok'tar ogar! Ihr seid die Verkörperung all dessen, was einen Soldaten der Horde ausmacht, $N. Hätten wir doch nur mehr wie Euch, dann wäre der Krieg bereits vorbei und Kalimdor würde der Horde gehören - UNANGEFOCHTEN!!$B$BErhebt Euch als ein Champion von Krom'gar!" WHERE Id=26073;

delete from creature_queststarter where id=41023 and quest=26073;

-- spawned from script
delete from creature where guid=118567 and id=42020;
delete from creature where guid=118568 and id=42019;
delete from creature where id=42015;
delete from creature where id=42016;
delete from creature where id=41894;

-- repair the hot air ballon
update creature_template set InhabitType=4 where entry=42029;
update creature_template_addon set bytes1=50331648 where entry in (41987, 41988, 42029);
UPDATE creature_template SET unit_flags=33536 WHERE entry=42029;

update creature_template set VehicleId=854 where entry=42020;

update creature set position_z=113.477 where guid=100963;
update creature set position_z=105.897 where guid=103054;
update creature set position_x=899.539,	position_y=-36.2722, position_z=96.9005 where guid=102817;

