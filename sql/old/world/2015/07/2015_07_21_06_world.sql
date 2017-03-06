
UPDATE `gossip_menu_option` SET `action_menu_id`=4382 WHERE `menu_id`=4346 AND `id`=1;
UPDATE `gossip_menu_option` SET `action_menu_id`=4383 WHERE `menu_id`=4346 AND `id`=2;

DELETE FROM `creature_text` WHERE `entry`=16059;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(16059,0,0, 'I''m going to kick yer ugly head in!',14,0,100,0,0,0,11953,''),
(16059,0,1, 'You want a fight? A fight you''ll get!',14,0,100,0,0,0,11952,''),
(16059,0,2, 'I crush weaklings like you every day! Bring it on!',14,0,100,0,0,0,11954,'');

DELETE FROM `spell_script_names` WHERE `spell_id`=45724;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(45724, 'spell_midsummer_braziers_hit');


