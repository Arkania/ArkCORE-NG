
update gossip_menu_option set OptionBroadcastTextID=37885 where id=0 and  menu_id in(39062, 10972, 10974);
update gossip_menu_option set option_id=1, npc_option_npcflag=0 where menu_id=10974 and id=0;

DELETE FROM `creature_text` WHERE `entry` IN(22431, 22432); 
-- Barada 
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `BroadcastTextId`, `comment`) VALUES 
(22431, 0, 0, 'It is time. The rite of exorcism will now commence...', 12, 0, 100, 0, 0, 0, 20400, 'Barada'), 
(22431, 1, 0, 'Prepare yourself. Do not allow the ritual to be interrupted or we may lose our patient...', 12, 0, 100, 0, 0, 0, 20401, 'Barada'), 
(22431, 2, 0, 'Back foul beings of darkness! You have no power here!', 12, 0, 100, 0, 0, 0, 20404, 'Barada'), 
(22431, 3, 0, 'I... must not... falter', 12, 0, 100, 0, 0, 0, 20407, 'Barada'), 
(22431, 4, 0, 'The Light is my guide... it is my sustenance!', 12, 0, 100, 0, 0, 0, 20408, 'Barada'), 
(22431, 5, 0, 'The power of light compells you! Back to your pit!', 12, 0, 100, 0, 0, 0, 20405, 'Barada'), 
(22431, 6, 0, 'Be cleansed with Light, human! Let not the demonic corruption overwhelm you.', 12, 0, 100, 0, 0, 0, 20403, 'Barada'), 
(22431, 7, 0, 'Back! I cast you back... corruptor of faith! Author of pain! Do not return, or suffer the same fate as you did here today!', 12, 0, 100, 0, 0, 0, 20419, 'Barada'), 
 
-- Colonel Jules 
(22432, 0, 0, 'Keep away. The fool is mine.', 12, 0, 100, 0, 0, 0, 20402, 'Colonel Jules'), 
(22432, 1, 0, 'Ah! Cease the incantations, Anchorite! Cease, or I will show you such pain that your pathetic people have never imagined!', 12, 0, 100, 0, 0, 0, 20414, 'Colonel Jules'), 
(22432, 2, 0, 'This is fruitless, draenei! You and your little helper cannot wrest control of this pathetic human. He is mine!', 12, 0, 100, 0, 0, 0, 20416, 'Colonel Jules'), 
(22432, 3, 0, 'I see your ancestors, Anchorite! They writhe and scream in the darkness... they are with us!', 12, 0, 100, 0, 0, 0, 20415, 'Colonel Jules'), 
(22432, 4, 0, 'I will tear your soul into morsels and slow roast them over demon fire.', 12, 0, 100, 0, 0, 0, 20417, 'Colonel Jules'); 

update quest_template set EndText="", CompletedText="Return to Nortet at the Darkspear Training Grounds in the Echo Isles." where Id=24640;
update quest_template set EndText="", CompletedText="Return to Ortezza at the Darkspear Training Grounds in the Echo Isles." where Id=24778;
update quest_template set EndText="", CompletedText="Return to Legati at the Darkspear Training Grounds in the Echo Isles." where Id=24772;
update quest_template set EndText="", CompletedText="Return to Tunari at the Darkspear Training Grounds in the Echo Isles." where Id=24784;
update quest_template set EndText="", CompletedText="Return to Nekali at the Darkspear Training Grounds in the Echo Isles." where Id=24760;
update quest_template set EndText="", CompletedText="Return to Soratha at the Darkspear Training Grounds in the Echo Isles." where Id=24752;
update quest_template set EndText="", CompletedText="Return to Voldreka at the Darkspear Training Grounds in the Echo Isles." where Id=26274;
update quest_template set EndText="", CompletedText="Return to Zen'Tabra at the Darkspear Training Grounds in the Echo Isles." where Id=24766;

update creature_text set BroadcastTextID=37886 where entry=39062 and groupid=0 and id=0;

update creature_text set BroadcastTextID=39089 where entry=38142 and groupid=0 and id=0;
update creature_text set BroadcastTextID=39092 where entry=38142 and groupid=0 and id=1;
update creature_text set BroadcastTextID=39090 where entry=38142 and groupid=0 and id=2;
update creature_text set BroadcastTextID=39091 where entry=38142 and groupid=0 and id=3;
update creature_text set BroadcastTextID=39090 where entry=38142 and groupid=1 and id=0;


