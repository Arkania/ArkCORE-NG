

update quest_template set PrevQuestId=26568 where Id=26571;
update quest_template set PrevQuestId=26607 where Id=26616;
update quest_template set NextQuestIdChain=26640 where Id=26639;
update quest_template set PrevQuestId=26616 where Id in (26636,26637,26638,26639);

update creature set spawntimesecs=120 where guid=34187 and id=43249;
update creature set spawntimesecs=120 where guid=26640 and id=43275;
update creature set spawntimesecs=120 where guid=9364 and id=43274;
update creature set spawntimesecs=120 where guid=33796 and id=43272;

update creature_template set AIName="", ScriptName="npc_john_j_keeshan_43184" where entry=43184;
update creature_template set AIName="", ScriptName="npc_hilary_8962" where entry=8962;
update creature_template set AIName="", ScriptName="npc_messner_43270" where entry=43270;
update creature_template set AIName="", ScriptName="npc_messner_43300" where entry=43300;
update creature_template set AIName="", ScriptName="npc_jorgensen_43272" where entry=43272;
update creature_template set AIName="", ScriptName="npc_krakauer_43274" where entry=43274;
update creature_template set AIName="", ScriptName="npc_danforth_43275" where entry=43275;
update creature_template set AIName="", ScriptName="npc_jorgensen_43305" where entry=43305;
update creature_template set AIName="", ScriptName="npc_krakauer_43303" where entry=43303;
update creature_template set AIName="", ScriptName="npc_danforth_43302" where entry=43302;


update quest_template set Flags=16252928, SpecialFlags=4, NextQuestId=26514 where Id=26512;
update quest_template set Flags=16252928, SpecialFlags=4, NextQuestId=26544 where Id=26514;
update quest_template set Flags=16252928, SpecialFlags=4, NextQuestId=26545 where Id=26544;

delete from creature where guid=44251 and id=43302;
update creature set position_x=-8805.83, position_y=-2206.83, position_z=144.3313, orientation=2.5307 where guid=26640 and id=43275;
update creature_template set InhabitType=7 where entry=43275;
update creature_template set InhabitType=4 where entry=43366;

update creature_loot_template set ChanceOrQuestChance=-80.4 where entry=43369 and item=59033;

update creature_addon set auras=81079 where guid=26640; -- id=43275

delete from spell_script_names where spell_id=80887 and ScriptName="spell_freeing_danforth";
insert into spell_script_names values(80887,"spell_freeing_danforth");

DELETE FROM `creature_text` WHERE `entry`=43305 AND `groupid`=0 AND `id`=0;
DELETE FROM `creature_text` WHERE `entry`=43305 AND `groupid`=1 AND `id` in (0,1,2);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(43305, 0, 0, "You know, I kept hearing the Blackrock orcs talk about the return of Hellscream to the Horde. What's that all about? Isn't Hellscream dead?", 12, 0, 0, 0, 43470),
(43305, 1, 0, "I'm just gettin' warmed up!", 12, 0, 0, 0, 43433),
(43305, 1, 1, "Welcome to hell!", 12, 0, 0, 0, 43440),
(43305, 1, 2, "Toe up...", 12, 0, 0, 0, 43441);


DELETE FROM `creature_text` WHERE `entry`=43303 AND `groupid`=4 AND `id`=0;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `emote`, `duration`, `sound`, `BroadcastTextID`) VALUES 
(43303, 4, 0, "So whatever happened to that hot little number in Stormwind? Lady Prestor was her name.", 12, 0, 0, 0, 43474);








