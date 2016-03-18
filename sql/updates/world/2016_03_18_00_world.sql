

-- gilneas druid quest A Rejuvenating Touch 12283
UPDATE quest_template SET RequiredNpcOrGo1=47091, RequiredRaces=2097152, Flags=524288, QuestGiverPortrait=29467, RequiredSpell=774 WHERE Id=14283;

update npc_trainer set reqLevel=3, reqskill=573, spellcost=60 where spell=774;

update npc_trainer set reqLevel=4, reqskill=574, spellcost=60 where spell=8921;

UPDATE creature_template SET KillCredit1=0 WHERE entry=35118;

update creature_template set AIName="", ScriptName="npc_wounded_guard_47091" where entry=47091;

update creature_template set AIName="", ScriptName="npc_gwen_armstead_35840" where entry=35840;

delete from creature_text where entry=35840 and groupid in (0,1,2,3);
insert into creature_text values 
(35840, 0, 0, "The plan is to keep moving south.  We can't go back to the Merchant Square.  It's not safe.", 12, 0, 100, 0, 0, 0, "gwen armstead say part 1", 36093),
(35840, 1, 0, "We must stick together to survive.  Move around in groups.", 12, 0, 100, 0, 0, 0, "gwen armstead say part 2", 36094),
(35840, 2, 0, "The king's men will protect us.  We're almost there.", 12, 0, 100, 0, 0, 0, "gwen armstead say part 3", 36095);






