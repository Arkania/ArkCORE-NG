
update creature_text set BroadcastTextID=20281 where entry=727 and groupid=0 and id=0;
update creature_text set BroadcastTextID=32807 where entry=727 and groupid=1 and id=0;
update creature_text set BroadcastTextID=0 where entry=727 and groupid=2 and id=0;

update creature_text set BroadcastTextID=43242 where entry=40951 and groupid=0 and id=0;

update creature_text set BroadcastTextID=43253 where entry=40950 and groupid=0 and id=0;
update creature_text set BroadcastTextID=43236 where entry=40950 and groupid=1 and id=0;
update creature_text set BroadcastTextID=43522 where entry=40950 and groupid=2 and id=0;
update creature_text set BroadcastTextID=43243 where entry=40950 and groupid=3 and id=0;
update creature_text set BroadcastTextID=43235 where entry=40950 and groupid=4 and id=0;

update creature_text set BroadcastTextID=43245 where entry=41335 and groupid=0 and id=0;
update creature_text set BroadcastTextID=43248 where entry=41335 and groupid=1 and id=0;

UPDATE locales_quest SET EndText_loc3="" WHERE Id=384;
UPDATE locales_quest SET EndText_loc3="" WHERE Id=315;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Hauptmann Tharran in Kharanos zurück." WHERE Id=25667;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Rüstmeisterin Glynna in Kharanos zurück." WHERE Id=25668;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Hauptmann Tharran in Kharanos zurück." WHERE Id=25724;
UPDATE locales_quest SET Title_loc3="Zum Zusehen verdammt", Objectives_loc3="Leitet Hauptmann Tharrans Befehle an Gebirgsjäger Dunstan, Gebirgsjäger Lewin und Gebirgsjäger Valgrum im Graufelsbau weiter.", Details_loc3="Der Kataklysmus hat die Troggs in Scharen an die Oberfläche getrieben, sodass die Frostmähnentrolle um ihr Leben fliehen mussten. Leider haben sie sich entschieden, sich direkt vor unserer Nase niederzulassen und uns Ärger zu bereiten.$B$BIch habe Gebirgsjäger Dunstan und seinen Trupp zum Graufelsbau südwestlich der Stadt geschickt, um dort ein Auge auf die Wendigos zu haben, jetzt aber brauchen wir sie hier in Kharanos. Macht sie ausfindig und sagt ihnen, sie sollen diese ferngesteuerten Beobachtungsbots aufstellen und dann nach Kharanos zurückkehren.", EndText_loc3="", OfferRewardText_loc3="Danke für Eure Hilfe, $N. Unsere Truppen sind zurzeit weit verstreut und drei Gebirgsjäger könnten den Unterschied zwischen einer erfolgreichen Verteidigung von Kharanos und überrannt zu werden ausmachen.", RequestItemsText_loc3="", CompletedText_loc3="Kehre zu Haupmann Tharran in Kharanos zurück." WHERE Id=313;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Hauptmann Tharran in Kharanos zurück.", QuestGiverTextWindow_loc3="Totems der Konstriktion", QuestGiverTargetName_loc3="Totems der Konstriktion" WHERE Id=25792;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Sprecht mit Delber Kurbeldreh in Stahlrosts Depot." WHERE Id=25838;

UPDATE quest_template SET PrevQuestId=310 WHERE Id=311;
UPDATE quest_template SET PrevQuestId=310 WHERE Id=308;
UPDATE quest_template SET PrevQuestId=310 WHERE Id=403;
UPDATE quest_template SET PrevQuestId=25667 WHERE Id=25724;
UPDATE quest_template SET PrevQuestId=25724 WHERE Id=313;
UPDATE quest_template SET PrevQuestId=25724 WHERE Id=25792;
UPDATE quest_template SET PrevQuestId=25792 WHERE Id=25838;

update locales_creature_text set text_loc3="Willkommen in Kharanos." where entry=727 and groupid=0 and id=2;

update creature_template set KillCredit1=40940 where entry=1135;

UPDATE creature_template SET questItem1=60496 WHERE entry=1125;

delete from creature where Id=1135;
DELETE FROM `creature_addon` WHERE `guid` NOT IN (SELECT `guid` FROM `creature`);

update gameobject_template set size=1.0 where entry=203130;

insert ignore into creature_addon (guid) value (11531);
update creature_addon set path_id=1153100 where guid=11531;
update creature set MovementType=2 where guid=11531;
delete from waypoint_data where id=1153100;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, move_flag) VALUES 
(1153100, 0, -5478.708984, -225.659042, 354.347717, 0),
(1153100, 1, -5488.913574, -216.091599, 354.253387, 0),
(1153100, 2, -5492.081543, -238.994553, 354.276672, 0),
(1153100, 3, -5498.768066, -232.468033, 353.709808, 0),
(1153100, 4, -5480.554688, -217.158310, 354.254272, 0),
(1153100, 5, -5493.027832, -226.545288, 354.306976, 0);

UPDATE creature_template SET gossip_menu_id=11455 WHERE entry=40991;
UPDATE creature_template SET gossip_menu_id=11456 WHERE entry=40994;
UPDATE creature_template SET gossip_menu_id=11457 WHERE entry=41056;

update gossip_menu_option set OptionBroadcastTextID=40986, option_id=1, npc_option_npcflag=1 where menu_id=11455 and id=0;
update gossip_menu_option set OptionBroadcastTextID=40986, option_id=1, npc_option_npcflag=1 where menu_id=11456 and id=0;
update gossip_menu_option set OptionBroadcastTextID=40986, option_id=1, npc_option_npcflag=1 where menu_id=11457 and id=0;

delete from gossip_menu where entry=11456;
insert into gossip_menu value (11456,15973);
update npc_text set BroadcastTextID0=40985 where ID=15972;
update npc_text set BroadcastTextID0=40989 where ID=15973;
update npc_text set BroadcastTextID0=40994 where ID=15974;

delete from creature_text where entry in (40991, 40994, 41056) and groupid=0 and id=0;
insert into creature_text (entry, groupid, id, text, BroadcastTextID) values
(40991, 0, 0, "Tell Captain Tharran that I'll be back in Kharanos as soon as I've verified that the bot is working correctly.", 41005),
(40994, 0, 0, "I can't wait to get out there and help in the fight against those trolls.", 41006),
(41056, 0, 0, "We've been fighting nonstop since the cataclysm. It'll be nice to get a rest, if a brief one.", 41008);

update creature_template set AIName="", ScriptName="npc_mountaineer_dunstan" where entry = 40991;
update creature_template set AIName="", ScriptName="npc_mountaineer_lewin" where entry = 40994;
update creature_template set AIName="", ScriptName="npc_mountaineer_valgrum" where entry = 41056;

update item_template set RequiredReputationFaction=72, RequiredReputationRank=6 where entry=67531;








