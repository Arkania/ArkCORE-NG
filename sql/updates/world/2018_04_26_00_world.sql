
-- set impsy aura to quest invisible 1
UPDATE creature_addon SET auras="49414" WHERE guid=109511;

-- activate script for impsy
UPDATE creature_template SET ScriptName="npc_impsy_47339" WHERE entry=47399;

-- add text for impsy
DELETE FROM `creature_text` WHERE `entry`=47339 AND `groupid` IN (0,1,2,3,4,5,6);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES 
(47339, 0, 0, "Go away, kid, you're botherin' me!", 12, 0, 100, 0, 0, 0, "answer of enter combat", 47492),
(47339, 1, 0, "You can't do this! I have my own soul shard!", 12, 0, 100, 0, 0, 0, "answer of a spell-cast during fight", 47537),
(47339, 2, 0, "Do you HAVE to flail around like such an idiot?", 12, 0, 100, 0, 0, 0, "answer of a spell-cast during fight", 47539),
(47339, 3, 0, "Right in the face! Ow ow ow...", 14, 0, 100, 0, 0, 0, "impsy yells this as quest accept and also if he puts in the sack..", 47550),
(47339, 4, 0, "Let me out of here! It smells like ELVES!", 12, 0, 100, 0, 0, 0, "after put him into bug", 47535),
(47339, 5, 0, "Niby sold me out! HE SOLD ME OUT!", 12, 0, 100, 0, 0, 0, "random text on the way back to reward quest?", 47536),
(47339, 5, 1, "It burns in here! Wait, that's just my feet.", 12, 0, 100, 0, 0, 0, "random text on the way back to reward quest?", 47540),
(47339, 5, 2, "Let me out and I'll give you three wishes! I swear!", 12, 0, 100, 0, 0, 0, "random text on the way back to reward quest?", 47541),
(47339, 6, 0, "Catch Impsy in the sack!", 42, 0, 100, 0, 0, 0, "yellow message on screen", 47551);

-- activate script for Arcanist Delaris
UPDATE creature_template SET ScriptName="npc_arcanist_delaris_47341" WHERE entry=47341;

-- impsy 47366 say text when freed from bag
DELETE FROM `creature_text` WHERE `entry`=47366 AND `groupid` IN (0);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) VALUES 
(47366, 0, 0, "I'll talk, I'll talk! Anything! Just keep that perfumed bag away from me!", 12, 0, 100, 0, 0, 0, "on quest reward Impsy frees from the back and say this...", 47554);
 
