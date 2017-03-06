
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Exekutor Arren in Todesend in Tirisfal zurück." WHERE Id=26802;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Exekutor Arren in Todesend in Tirisfal zurück." WHERE Id=24973;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Meldet Euch bei Schattenpriester Sarvis in Todesend in Tirisfal." WHERE Id=24971;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Todeswache Simmer auf dem Calstonanwesen in Tirisfal zurück." WHERE Id=24978;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Apotheker Johaan auf dem Calstonanwesen in Tirisfal zurück." WHERE Id=24975;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Jungapotheker Holland bei Brill in Tirisfal zurück." WHERE Id=25038;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Apotheker Johaan auf dem Calstonanwesen in Tirisfal zurück." WHERE Id=24976;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Todeswache Simmer auf dem Calstonanwesen in Tirisfal zurück.", QuestGiverTextWindow_loc3="Krieger des Scharlachroten Kreuzzugs", QuestGiverTargetName_loc3="Krieger des Scharlachroten Kreuzzugs" WHERE Id=24980;

update creature_template set AIName="", Scriptname="npc_rotbrain_berserker" where entry=49422;
update creature_template set AIName="", Scriptname="npc_rotbrain_magus" where entry=49423;
update creature_template set AIName="", Scriptname="npc_marshal_redpath" where entry=49424;
update creature_template set AIName="", Scriptname="npc_deathguard_protector" where entry=49428;


delete from creature_equip_template where entry=49428 and id=1;
insert into creature_equip_template values (49428, 1, 1905, 0, 0);

update quest_template set Method=2, flags=0 where  Id=24976;

update creature set spawndist=5, MovementType=1 where id in (1553, 1547);

update creature_text set BroadcastTextID=2627 where entry=1535 and groupid=0 and id=0;
update creature_text set BroadcastTextID=2625 where entry=1535 and groupid=0 and id=1;
update creature_text set BroadcastTextID=2628 where entry=1535 and groupid=0 and id=2;
update creature_text set BroadcastTextID=1150 where entry=1535 and groupid=1 and id=0;

update creature_template set npcflag=16777216, dynamicflags=0 where entry=38933;
















