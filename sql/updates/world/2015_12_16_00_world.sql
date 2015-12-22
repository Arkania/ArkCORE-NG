

UPDATE quest_template SET Flags=12 WHERE Id=14066;

UPDATE quest_template SET Flags=524292 WHERE Id=869;

delete from creature where guid=84068 and id=3464;

delete from creature where guid=73450 and id=15810;

UPDATE quest_template SET  EndText="", RequiredNpcOrGo1=3464, RequiredNpcOrGoCount1=1, ObjectiveText1="Caravan Scene Searched" WHERE Id=14066;
UPDATE locales_quest SET EndText_loc3="", RequestItemsText_loc3="Habt Ihr den verunglückten Wagen gefunden?", ObjectiveText1_loc3="Karawanen-Tatort abgesucht" WHERE Id=14066;
UPDATE quest_template SET Flags=1048588, SpecialFlags=0 WHERE Id=14066;

UPDATE quest_template SET Flags=524292, SpecialFlags=0, RequiredNpcOrGo1=3464, RequiredNpcOrGoCount1=1, EndText="", ObjectiveText1="Source of Tracks Discovered" WHERE Id=869;
UPDATE locales_quest SET Objectives_loc3="Die Fährte führt zur Ostseite vom Dornenhügel. Folgt ihr und schaut, was sich herausfinden lässt.", 
	Details_loc3="Tierfährten umgeben die Trümmer, Fährten, die von enormen geschwungenen Klauen hinterlassen wurden. Es scheinen Raptorenspuren zu sein.$B$BEuer erster Verdacht ist, dass Raptorenreiter die Karawane überfallen haben, aber die Abdrücke sind nicht tief und es lassen sich keine Spuren finden, die nicht von Tieren stammen.$B$BDie Fährte führt nach Nordosten hin zur Ostseite vom Dornenhügel. Die Antwort auf dieses Rätsel muss in dessen Schatten liegen.", 
	EndText_loc3="", 
	OfferRewardText_loc3="Vor Euch liegt eine ganze Gruppe von Raptoren. Sie rennen um kleine Hütten herum, knurrenden einander an, und arbeiten sogar zusammen, um diese primitiven Hütten zu bauen. Sammlungen von glänzenden Dingen umgeben ihre Nester. Geheimnis gelüftet!", 
	RequestItemsText_loc3="", 
	CompletedText_loc3="Die Fährte führt zur Ostseite vom Dornenhügel. Folgt ihr und schaut, was sich herausfinden lässt.", 
	ObjectiveText1_loc3="Ursprung der Fährte entdeckt" WHERE Id=869;

delete from areatrigger_scripts where entry=5482;
insert into areatrigger_scripts values 
(5482, "at_caravan_scene_5482");

delete from areatrigger_scripts where entry=5483;
insert into areatrigger_scripts values 
(5483, "at_follow_the_tracks_5483");

-- console errors
update creature_template set VehicleId=599 where entry=36939;
delete from creature_addon where guid=120377;
delete from game_graveyard_zone where id in (109, 389, 589, 1458, 1722, 1723, 1724, 1725, 1745, 1746, 1747, 1778);

update npc_spellclick_spells set cast_flags=0 where npc_entry in (40240, 40340, 40720);

delete from npc_spellclick_spells where npc_entry in (50523, 40121, 39833, 40650, 39839, 52359);
insert into npc_spellclick_spells values
(50523, 46598, 1, 0),
(40121, 46598, 1, 0), 
(40121, 74796, 1, 0), 
(39833, 46598, 1, 0),
-- (39833, 63034, 1, 0),
(40650, 46598, 1, 0),
-- (40650, 63034, 1, 0),
(39839, 46598, 1, 0),
(52359, 46598, 1, 0),
(52359, 96847, 1, 0);









