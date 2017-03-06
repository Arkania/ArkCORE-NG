
-- fix issue #138 #139 #140 #141 #142
-- player and some npc's are in wrong phase.. all are corrected in previous fixxes..

-- quest 24578
delete from creature where id=37822 and guid=16465;

-- quest 24616
UPDATE locales_quest SET CompletedText_loc3="Kehrt zu Belysra Sternenhauch in der Bradshawmühle zurück." WHERE Id=24616;

delete from creature where id=37953 and guid=252471;

delete from areatrigger_scripts where entry=6687;
insert into areatrigger_scripts values 
(6687, "at_the_blackwald_6687");

update creature_text set BroadcastTextID=37672 where entry=37953 and groupid=0;
update creature_text set BroadcastTextID=37673 where entry=37953 and groupid=1;

DELETE FROM creature_text where entry=37953 and groupid=2;
INSERT INTO creature_text values 
(37953, 2, 0, "Use Belrysa's Talisman to escape before the Dark Scout shoots you!$B$B|TInterface\Icons\inv_jewelry_talisman_10.blp:64|t", 42, 0, 100, 1, 0, 0, "", 37674);

update creature_template set faction=118, AIName="", ScriptName="npc_dark_scout_37953" where entry=37953;

delete from item_script_names where id=49944;
insert into item_script_names values 
(49944, "item_belysras_talisman_49944");

delete from creature where id=37195 and guid=252439;

   