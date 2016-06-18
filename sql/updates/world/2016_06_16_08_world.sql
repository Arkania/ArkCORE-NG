

UPDATE creature_template_addon SET auras="29266" WHERE entry=26514;

UPDATE quest_template SET OfferRewardText="Good, $C. You've done well. I'll keep these safe from prying eyes; the last thing we need is a strong Shadow Council rising up again.$B$BCheck back with me in the future; there's always something that needs doing around here, apparently, and I might need another able body.", RequestItemsText="Did you secure the books? They need to be kept out of the wrong hands." WHERE Id=14356;

UPDATE `page_text` SET `Text`="a large scale operation so close to the tauren homeland, but do not feel that they pose a large impediment to our overall business plan in the area.$B$BWe are pleased to hear that mining has begun in the mineral rich plains of Mulgore. Because of this the board has approved your equipment request. In addition to mining, we feel that Mulgore also has much to offer in the way of lumber, thus you will also be provided with several of our newest model shredders and raw materials to construct a mill.", `next_page`=0 WHERE `entry`=353;
DELETE FROM `page_text` WHERE entry = 354;

UPDATE `page_text` SET `next_page`=571, `Text`="The Bleeding Sparrow: Manifest$B$B(20) barrels rum. Destination: Theramore$B(50) sacks flour. Destination: Theramore$B(2) crates assorted gnome tools. Destination: Ratchet$B(30) bolts cotton cloth. Destination: Theramore$B(4) crates spices. Destination: Theramore$B(3) passengers. Destination: Theramore" WHERE `entry`=527;
UPDATE `page_text` SET `next_page`=0, `Text`="Captain,$B$BI wish you fortune in your journeys. Regrettably, fortune did not favor our first abduction attempt.$B$BWhen our team made contact with the target in the Stormwind/Ironforge tunnels, they found only a decoy.  It appears he showed more wisdom than we accredited him.$B$BBut our second plan is already in motion.  Defias agents are prepared to intercept the target as he approaches Theramore.  Soon Stormwind will feel our bite all too keenly..$B$B-M" WHERE `entry`=571;

UPDATE quest_template SET PrevQuestId=9280, NextQuestIdChain=9283 WHERE Id=9409;
UPDATE quest_template SET ExclusiveGroup=9280, NextQuestIdChain=9409 WHERE Id=9280;
UPDATE quest_template SET ExclusiveGroup=9280, NextQuestIdChain=9409 WHERE Id=9369;


