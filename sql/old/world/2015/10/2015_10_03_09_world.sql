
delete from smart_scripts where entryorguid=33201;
update creature_template set AIName="" where entry=33201;

delete from creature where id in (52212, 52337, 52338, 52385);

DELETE FROM `creature_template_addon` WHERE (`entry`=8016);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (8016, 0, 0, 0, 1, 0, 29266);

UPDATE creature_template SET unit_flags=768, unit_flags2=2048 WHERE entry=8016;

delete from creature where guid in (84024, 129665);

update creature_template_addon set auras="" where entry in(8582);
update creature_addon set auras="" where guid in (115584);

UPDATE creature_template SET gossip_menu_id=10328, minlevel=20, maxlevel=20, faction=85, baseattacktime=2000, rangeattacktime=2000, unit_flags=768 WHERE entry=33294;

update npc_text set BroadcastTextID0=33433 where ID=14336;

UPDATE creature_template SET minlevel=20, maxlevel=20, faction=85 WHERE entry=33294;

UPDATE creature_template SET minlevel=20, maxlevel=20, faction=85 WHERE entry=33304;

delete from creature_text where entry=33304;
insert into creature_text (entry, groupid, id, text, BroadcastTextID) values
(33304, 0, 0, "Thank you, friend. I could not rest knowing that my mission had not been completed.", 33440),
(33304, 1, 0, "...and that my mens' sacrifice had not been avenged.", 33441),
(33304, 2, 0, "We must hurry, now. I sense that my time is short.", 33442),
(33304, 3, 0, "Follow me closely, and prepare for battle!", 33443),
(33304, 4, 0, "Captain Elendilad conceals himself on the island ahead, cowardly issuing orders to his underlings.", 33444),
(33304, 5, 0, "He must fall!", 33445),
(33304, 6, 0, "Show yourself, elf-coward! Face your death with honor!", 33449),
(33304, 7, 0, "Mission complete. Thank you, friend.", 33470);

UPDATE creature_template SET minlevel=20, maxlevel=21, faction=124 WHERE entry=33302;

delete from creature_text where entry=33302;
insert into creature_text (entry, groupid, id, text, BroadcastTextID) values
(33302, 0, 0, "How many times must I have you killed, orc?!", 33455),
(33302, 1, 0, "Curse you, $R vermin! This forest belongs to the Kaldorei...", 33462);



