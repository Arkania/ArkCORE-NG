
update quest_template set PrevQuestId=26545 where Id in (26569,26570,26571,26586,26728);

update creature_template set AIName="", ScriptName="npc_redrige_citizen_43247" where entry=43247;

delete from areatrigger_scripts where entry=6034;
insert into areatrigger_scripts values (6034,"at_lakeshire_graveyard");

DELETE FROM `areatrigger_involvedrelation` WHERE `quest` = 26512;
INSERT INTO `areatrigger_involvedrelation` (`id`, `quest`) VALUES (6034, 26512);

update quest_template set Flags=524288, SpecialFlags=4 where Id in (26512,26514,26544);

update creature_template set questItem3=58897 where entry in (430,446,580);
update creature_template set questItem1=58897 where entry=445;
