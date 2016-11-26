
delete from creature where guid=240518;

UPDATE quest_template SET Flags=131080 WHERE Id=14348;

update creature set PhaseIds="182" where id=36198 and guid in (13293, 13294, 13295, 13296, 13297);

update creature set phaseIds="", phaseGroup=431, SpawnTimeSecs=120 where id=36540;

delete from creature where id=51589;

UPDATE creature SET phaseIds="183" WHERE guid=253469;

update creature set phaseIds="186" where guid=252309 and id=36065;

delete from spell_phase where spell_id in (68481, 68482, 68483, 69484, 69485, 69486, 70695, 70696, 74093, 74096);
insert into spell_phase values 
(68481, 0, 181, 0,   0,   0, "Quest Zone-Specific 06"),
(68482, 0, 182, 0,   0,   0, "Quest Zone-Specific 07"),
(68483, 0, 183, 0, 655, 678, "Duskhaven, shattered land, Quest Zone-Specific 08"),
(68483, 1, 183, 0, 655, 683, "Duskhaven, shattered land, Quest Zone-Specific 08"),
(69484, 0, 186, 0, 656, 679, "Quest Zone-Specific 11"),
(69485, 0, 187, 0, 656, 679, "Quest Zone-Specific 12"),
(69486, 0, 188, 0, 656, 679, "Quest Zone-Specific 13"),
(70695, 0, 189, 0, 656, 679, "Quest Zone-Specific 14"),
(70696, 0, 190, 0, 656, 679, "Quest Zone-Specific 15"),
(74093, 0, 191, 0, 656, 679, "Quest Zone-Specific 16"),
(74096, 0, 194, 0, 656, 679, "Quest Zone-Specific 19");

update creature set map=654, phaseIds="186" where id=37078;

insert into game_event_seasonal_questrelation (questId, eventEntry) values('24615','335');







