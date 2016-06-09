
-- fix quest 13151 in stratholme

DELETE FROM creature_text WHERE entry=27745 AND groupid=0 AND id=0;
INSERT INTO creature_text VALUES 
(27745, 0, 0, "The Lightbringer...", 12, 0, 100, 1, 0, 0, "", 28625);

DELETE FROM creature_text WHERE entry=28169;
INSERT INTO creature_text VALUES 
(28169, 0, 0, "Everyone I know seems to be coming down with something really bad.", 12, 0, 100, 1, 0, 0, "", 28821),
(28169, 0, 1, "I haven't felt this bad since I tried to eat some Dragon's Breath Chili.", 12, 0, 100, 1, 0, 0, "", 28822),
(28169, 0, 2, "My bed is looking pretty good right now.", 12, 0, 100, 1, 0, 0, "", 28823),
(28169, 0, 3, "My boss is going to kill me if I have to stay home sick another day this month.", 12, 0, 100, 1, 0, 0, "", 28824),
(28169, 0, 4, "Have you heard any news from the town leaders about the sickness going around?", 12, 0, 100, 1, 0, 0, "", 28825),
(28169, 0, 5, "Have you talked to anyone who hasn't started getting sick?", 12, 0, 100, 1, 0, 0, "", 28826),
(28169, 0, 6, "It must be something in the water, I tell you.", 12, 0, 100, 1, 0, 0, "", 28827),
(28169, 0, 7, "Oh, my. Excuse me a moment.", 12, 0, 100, 1, 0, 0, "", 28828),
(28169, 1, 0, "What? This can't be!", 12, 0, 100, 0, 0, 0, "culling SAY_PHASE204a", 27549),
(28169, 2, 0, "Did you see that?", 12, 0, 100, 1, 0, 0, "culling SAY_PHASE204b", 28829);


DELETE FROM creature_text WHERE entry=28167;
INSERT INTO creature_text VALUES 
(28167, 0, 0, "Everyone I know seems to be coming down with something really bad.", 12, 0, 100, 1, 0, 0, "", 28821),
(28167, 0, 1, "I haven't felt this bad since I tried to eat some Dragon's Breath Chili.", 12, 0, 100, 1, 0, 0, "", 28822),
(28167, 0, 2, "My bed is looking pretty good right now.", 12, 0, 100, 1, 0, 0, "", 28823),
(28167, 0, 3, "My boss is going to kill me if I have to stay home sick another day this month.", 12, 0, 100, 1, 0, 0, "", 28824),
(28167, 0, 4, "Have you heard any news from the town leaders about the sickness going around?", 12, 0, 100, 1, 0, 0, "", 28825),
(28167, 0, 5, "Have you talked to anyone who hasn't started getting sick?", 12, 0, 100, 1, 0, 0, "", 28826),
(28167, 0, 6, "It must be something in the water, I tell you.", 12, 0, 100, 1, 0, 0, "", 28827),
(28167, 0, 7, "Oh, my. Excuse me a moment.", 12, 0, 100, 1, 0, 0, "", 28828),
(28167, 1, 0, "Prince Arthas, may the light be praised! Many people in the town have begun to fall seriously ill, can you help us?", 12, 0, 100, 0, 0, 0, "culling SAY_PHASE202", 27547);

delete from creature where guid in (233848, 233881);

UPDATE creature_template SET ScriptName="npc_civilian_transformation_trigger_28815" WHERE entry=28815;

delete from creature where id=27732 and guid in (233649, 233655);
delete from creature where id=27742 and guid in (233664, 233669, 233674, 233677);
delete from creature where id=27743 and guid in (233662, 233666, 233668, 233672);
delete from creature where id=27744 and guid in (233661, 233663, 233667, 233673);
delete from creature where id=28199 and guid in (233650, 233652, 233654, 233657, 233679, 233680);
delete from creature where id=28200 and guid in (233648, 233651, 233653, 233656);

delete from creature where id=28340 and guid in (233658, 233660);
delete from creature where id=28341 and guid in (233659);

update creature set spawntimesecs=7200, spawnMask=3, phaseMask=1 where map=595;

UPDATE creature_template SET HoverHeight=1.0000 WHERE entry=30997;

update gossip_menu_option set OptionBroadcastTextID=28508 where menu_id=9712 and id=0;











