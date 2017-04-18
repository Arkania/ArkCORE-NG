
delete from creature_template_addon where entry in (43508, 50523);

insert into creature_template_addon values
(43508, 0, 0, 0, 1, 0, 770, 0, 0, ""),
(42748, 0, 0, 0, 1, 0, 676, 0, 0, ""),
(50523, 0, 0, 0, 1, 0, 1193, 0, 0, "");

UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=648;
UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=649;
UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=650;
UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=651;
UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=652;
UPDATE creature_template_addon SET aiAnimKit=726 WHERE entry=653;
UPDATE creature_template_addon SET aiAnimKit=646 WHERE entry=42147;
UPDATE creature_template_addon SET aiAnimKit=721 WHERE entry=43150;
UPDATE creature_template_addon SET aiAnimKit=748 WHERE entry=43275;
UPDATE creature_template_addon SET aiAnimKit=770 WHERE entry=43508;
UPDATE creature_template_addon SET aiAnimKit=722 WHERE entry=43611;
UPDATE creature_template_addon SET aiAnimKit=1193 WHERE entry=50523;
UPDATE creature_template_addon SET aiAnimKit=646 WHERE entry=52321;
UPDATE creature_template_addon SET aiAnimKit=645 WHERE entry=52358;
UPDATE creature_template_addon SET aiAnimKit=676 WHERE entry=42635;
UPDATE creature_template_addon SET aiAnimKit=676 WHERE entry=42748;
UPDATE creature_template_addon SET aiAnimKit=695 WHERE entry=42839;
UPDATE creature_template_addon SET aiAnimKit=645 WHERE entry=43276;
UPDATE creature_template_addon SET aiAnimKit=573 WHERE entry=45847;
UPDATE creature_template_addon SET aiAnimKit=983 WHERE entry=46363;
UPDATE creature_template_addon SET aiAnimKit=989 WHERE entry=46449;

delete from smart_scripts where entryorguid=43094;




