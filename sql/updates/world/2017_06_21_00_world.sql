
-- thanks to roger
-- Add missing rows from sniff
DELETE FROM `creature_text` WHERE `entry`IN(42801,42892,42965);

insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42801','1','0','Ok, ok, I give up! I\'ll tell you everything!','12','0','100','0','0','20988','Mor\'norokk the Hateful','42813');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42801','2','0','Gotcha!','12','0','100','0','0','20989','Mor\'norokk the Hateful','42796');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42801','3','0','I hope you can fly, pipsqueak!','12','0','100','0','0','20990','Mor\'norokk the Hateful','42708');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42892','1','0','Over here, you ugly whale!','12','0','100','0','0','21001','Stormcaller Mylra','42799');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42892','2','0','Meet me back up top. This two-headed freak has a few questions to answer!','12','0','100','0','0','21002','Stormcaller Mylra','42812');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','1','0','All right, sunshine. Time to spill your guts before I spill \'em for ya!','12','0','100','0','0','21003','Stormcaller Mylra','43166');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','2','0','I\'m a daughter of the Wildhammer Clan and a shaman of the Earthen Ring. My code compels me to honor my ancestors and the elements.','12','0','100','0','0','21004','Stormcaller Mylra','43168');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','3','0','Doesn\'t say a damn thing about dog-ugly ogres.','12','0','100','0','0','21005','Stormcaller Mylra','43169');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','4','0','You can start by telling us where the World Pillar fragment is. My gryphon\'s starting to look a bit tired from hauling you around.','12','0','100','0','0','21006','Stormcaller Mylra','43170');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','5','0','You were never in any danger, sweetheart. My friends down below would\'ve caught you. You\'re worth too much to us alive!','12','0','100','0','0','21007','Stormcaller Mylra','43177');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42965','6','0','Interesting. I\'d never heard of the Twilight Council until now.','12','0','100','0','0','21008','Stormcaller Mylra','43180');

-- Add missing rows for enslaved miner.44768
DELETE FROM `creature_text` WHERE `entry`=44768;

insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','1','Thank you... I wish I could help you find the forgemaster.','12','0','100','0','0','0','Enslaved Miner','44848');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','2','The forgemaster\'s a terrible murderer. Are you sure you want to go looking for him?','12','0','100','0','0','0','Enslaved Miner','44849');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','3','Ah, yes... I know about the forgemaster! I just overheard that he\'s not in the camp right now.','12','0','100','0','0','0','Enslaved Miner','44850');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','4','The forgemaster is meeting with the Twilight leadership. Trust me, I traded some gossip for a loaf of stale bread!','12','0','100','0','0','0','Enslaved Miner','44851');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','5','I don\'t know nothin\' bout no forgemaster. Now tell me where this safe place you came from is!','12','0','100','0','0','0','Enslaved Miner','44852');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('44768','1','6','I heard the forgemaster keeps notes about his meetings in a book at the tower overlooking the camp.','12','0','100','0','0','0','Enslaved Miner','44853');

-- Ogre dialogue for quest 26254
DELETE FROM `creature_text` WHERE `entry`=42964;

insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42964','1','0','Wait! You can\'t do this! You people must have a code of honor or something!','14','0','100','0','0','20992','Mor\'norokk the Hateful','43167');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42964','2','0','Stop it, you tiny, angry woman! I\'ll tell you everything! What do you want to know?','14','0','100','0','0','20993','Mor\'norokk the Hateful','43171');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42964','3','0','It was delivered to the forgemaster at Deathwing\'s Fall. I swear... that\'s all I know!','14','0','100','0','0','20994','Mor\'norokk the Hateful','43172');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42964','4','0','Happy now? Pull me up, you vicious little dwarf!','14','0','100','0','0','20995','Mor\'norokk the Hateful','43178');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42964','5','0','What? What have you done? No! Do you have any idea what the Twilight Council will do to me when they find out I\'ve talked!? I would sooner die!','14','0','100','0','0','20996','Mor\'norokk the Hateful','43179');

-- creature text for http://www.wowhead.com/npc=42731/earthmender-norsala 
DELETE FROM `creature_text` WHERE `entry`=42731;

insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42731','1','0','So it is certain den. Dese elementals were bound from dormant stone only recently.','12','0','100','1','0','21027','Earthmender Norsala','42678');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42731','2','0','Only an elemental lord could bind so many elementals so quickly. It seems we\'re at war with da Stonemother herself...','12','0','100','1','0','21028','Earthmender Norsala','42679');
insert into `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`, `BroadcastTextID`) values('42731','3','0','May da elements protect us.','12','0','100','1','0','21029','Earthmender Norsala','42680');




