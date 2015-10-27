
-- kadrak has aura ID - 65052 Quest Invisibility 2
update creature_addon set auras="65052" where guid=115584;

DELETE FROM spell_area WHERE spell=65051 and area=1703 and quest_start=29111;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65051, 1703, 29111, 13721, 74, 64, 0, 0, 0);

DELETE FROM spell_area WHERE spell=65051 and area=1703 and quest_start=28876;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65051, 1703, 28876, 13721, 74, 64, 0, 0, 0);

DELETE FROM spell_area WHERE spell=65051 and area=1703 and quest_start=28493;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65051, 1703, 28493, 13721, 74, 64, 0, 0, 0);

DELETE FROM spell_area WHERE spell=65053 and area=1703 and quest_start=29111;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65053, 1703, 29111, 13721, 74, 64, 0, 0, 0);

DELETE FROM spell_area WHERE spell=65053 and area=1703 and quest_start=28876;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65053, 1703, 28876, 13721, 74, 64, 0, 0, 0);

DELETE FROM spell_area WHERE spell=65053 and area=1703 and quest_start=28493;
INSERT INTO spell_area (spell, area, quest_start, quest_end, quest_start_status, quest_end_status, racemask, gender, autocast) VALUES 
(65053, 1703, 28493, 13721, 74, 64, 0, 0, 0);

update creature_template set gossip_menu_id=11137 where entry=38442;

UPDATE quest_template SET PrevQuestId=25035 WHERE Id=24812;
UPDATE quest_template SET PrevQuestId=25035 WHERE Id=24813;
UPDATE quest_template SET NextQuestId=25073 WHERE Id=24814;


delete from quest_poi_points where questId=23622;
insert into quest_poi_points values
(24622, 0, 0, -1560, -5305);

delete from quest_poi where questId=24622 and objIndex=-1;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Verlorenes Brutkrallenjungtier", QuestGiverTargetName_loc3="Verlorenes Brutkrallenjungtier" WHERE Id=24623;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Naj'tess wollte die engsten Verbündeten der Dunkelspeertrolle gegen sie aufbringen, aber dabei unterschätzt er mehr als nur die Trolle." WHERE Id=24625;

update creature_addon set path_id=90057 where guid=90057;
update creature set MovementType=2 where guid=90057;

UPDATE creature_template SET gossip_menu_id=11131 WHERE entry=38989;

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=11131 and SourceEntry=0 and ConditionTypeOrReference=9 and ConditionValue1=25035;

insert into conditions values
(15, 11131, 0, 0, 0, 9, 0, 25035, 0, 0, 0, 0, 0, "", "");

UPDATE creature_template SET gossip_menu_id=11020 WHERE entry=38225;

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=11020 and SourceEntry=0 and ConditionTypeOrReference=9 and ConditionValue1=24814;

insert into conditions values
(15, 11020, 0, 0, 0, 9, 0, 24814, 0, 0, 0, 0, 0, "", "");

update npc_text set BroadcastTextID0=38316 where ID=15318;

update gossip_menu_option set OptionBroadcastTextID=38317 where menu_id=11020 and id=0;

update creature_template set AIName="", ScriptName="npc_voljin_38225" where entry=38225;
update creature_template set AIName="", ScriptName="npc_voljin_38966" where entry=38966;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Vol'jin in der Dunkelspeerfeste auf den Echoinseln." WHERE Id=24814;

UPDATE locales_quest SET OfferRewardText_loc3="Die Macht, die freigesetzt wurde, als die Seehexe starb, war immens. Ich kann diese Macht benutzen, um eine Vision von weit entfernten Orten heraufzubeschwören.$B$BSeht her, Neuling. Ich möchte, dass Ihr hier seid, wenn ich mit Thrall in Kontakt trete. Vielleicht gewinnt auch Ihr dadurch Einsicht." WHERE Id=24814;




