
-- Trixi Sharpworth
SET @ENTRY := 55339;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,20000,30000,1,0,0,0,0,0,0,17,4,20,0,0.0,0.0,0.0,0.0,"talk to player");

-- Sazz Coincatcher
SET @ENTRY := 55264;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,20000,30000,1,0,0,0,0,0,0,17,4,20,0,0.0,0.0,0.0,0.0,"talk to player");

-- Zina Sharpworth
SET @ENTRY := 55266;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,20000,30000,1,0,0,0,0,0,0,17,4,20,0,0.0,0.0,0.0,0.0,"talk to player");

delete from creature where id=55729 and guid=270813;
INSERT INTO `creature` VALUES (270813, 55729, 974, 1, 1, 0, 0, -4398.58, 6341.8, 12.841, 6.1151, 300, 0, 0, 42, 0, 0, 0, 0, 0);

DELETE FROM creature_text where entry=55729 and groupid=0;
INSERT INTO creature_text values 
(55729, 0, 0, "Hey! Hey, $R! I be havin' just the thing for ya. Ya ever see a tikbalang? Frightenin' creatures. Prone to stealin' ya away. What ya need is one of my tikbalang wards. Guaranteed to ward away all tikbalangs!", 12, 0, 100, 0, 0, 0, "", 16318),
(55729, 0, 1, "Look over here, $C! I got somethin' for ya. Just what ya need. It's soap, right... and it's on a rope! No offense, $G man:honey;, but yer a little ripe, know what I'm sayin'?", 12, 0, 100, 0, 0, 0, "", 16319),
(55729, 0, 2, "Ya look lovesick. Special someone be gettin' ya down, eh? No worries, no worries. Ya get this medallion from me, ya wear it when ya see 'em, and they be all over ya, $G man:sweetheart;!", 12, 0, 100, 0, 0, 0, "", 16320),
(55729, 0, 3, "Dangerous out there, innit? Know what ya need? Protection. I can help ya defy death itself! Ya wear this madstone 'round yer neck, see, and then ya be able to come back if ya find yerself in the spirit world! Just a quick jaunt to yer corpse and up ya come, fresh and new!", 12, 0, 100, 0, 0, 0, "", 16321),
(55729, 0, 4, "Amazing amulets! Incredible curios! The newfangled jewelcrafters be havin' nothin' on the tried and true mystical methods of ol' Griftah! Improve yerself through these magical talismans for a bargain price!", 12, 0, 100, 0, 0, 0, "", 16322),
(55729, 0, 5, "C'mere, $R. Ya don't want to be riskin' yerself in a dungeon, do ya? Filthy work, and for what? Some worthless trinket? Nah, what ya need be one of my amulets. Guaranteed to work!", 12, 0, 100, 0, 0, 0, "", 16323),
(55729, 0, 6, "Ya look tired, $C. I be havin' somethin' for ya. These amulets, they can help ya leap obstacles and swim through the rivers like ya be born to it. They energize the food ya be eatin', makin' yer wounds close before yer eyes!", 12, 0, 100, 0, 0, 0, "", 16324);

-- Griftah
SET @ENTRY := 55729;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(@ENTRY,@SOURCETYPE,0,0,1,0,100,0,0,0,30000,60000,1,0,0,0,0,0,0,17,4,20,0,0.0,0.0,0.0,0.0,"talk to player");

update gossip_menu_option set OptionBroadcastTextID=53317, option_id=1, npc_option_npcflag=1 where menu_id=13012 and id=0;
update gossip_menu_option set OptionBroadcastTextID=53060, option_id=1, npc_option_npcflag=1 where menu_id=13012 and id=1;
update gossip_menu_option set OptionBroadcastTextID=53060, option_id=1, npc_option_npcflag=1 where menu_id=13012 and id=2;
-- delete from gossip_menu_option where menu_id=13012 and id=2; 

DELETE FROM creature_text where entry=54485 and groupid=0 and id in (4, 5);
INSERT INTO creature_text values 
(54485, 0, 4, "Test your aim! Test your aim!", 12, 0, 100, 70, 0, 0, "", 53452),
(54485, 0, 5, "Come play a game so simple that even a $C can do it!", 12, 0, 100, 70, 0, 0, "", 53453);

update waypoint_data set position_x=-4293.35, position_y=6295.18 where id=270424 and point=3;
update waypoint_data set delay=3000 where id=270424;

UPDATE quest_template SET Method=2, Level=1, RequiredMaxRepFaction=909, RequiredMaxRepValue=500, Flags=8200, SpecialFlags=1, Details="The first lesson in drawing a crowd is: lure them with gadgets and trinkets!  Can you help me?$B$BI need small furry paws to use for prizes.  You can find those on the cats of the Barrens or Darkshore....$B$BBring me some paws and I'll trade you a Darkmoon Faire ticket for them.", OfferRewardText="Great, you got them! We can use these to make toys and baubles, and those will attract more people to the Faire!$B$BHere's your ticket, $N. You earned it!" WHERE Id=7899;

UPDATE locales_quest SET Details_loc3="Die erste Lektion um eine Menschenmenge anzuziehen wäre: lockt sie mit kleinen technischen Spielereien oder Schmuck! Könnt Ihr mir helfen?$B$BIch benötige kleine pelzige Tatzen als Preis. Ihr könnt sie bei Katzen des nördlichen Brachlands oder der Dunkelküste finden.... $B$BBring mir einige Pfoten und ich werde Euch ein Los für den Dunkelmond Jahrmarkt besorgen.", EndText_loc3="" WHERE Id=7899;

UPDATE quest_template SET Method=2, Level=10, RequiredMaxRepFaction=909, RequiredMaxRepValue=1100, Flags=8200, SpecialFlags=1, RequestItemsText="Children love toys!  And no matter what race, I've found that all children love furry, plushy toys made from torn bear pelts!$B$BYou can get those pelts from the bears of Ashenvale or Hillsbrad.  Bring me a heap of them and earn yourself a heap of Darkmoon Faire tickets!" WHERE Id=7900;

UPDATE quest_template SET Method=2, Level=20, RequiredMaxRepFaction=909, RequiredMaxRepValue=1700, Flags=8200, SpecialFlags=1, OfferRewardText="Well done, $N! These tails will make great prizes for our visitors, and that means happy visitors... who talk to their friends and bring more visitors!$B$BHere are your tickets! Have a good time at the Darkmoon Faire... and don't forget to tell your friends about us!", RequestItemsText="It's amazing what people value!  Take, for instance, a wooden stick with a soft bushy tail attached to it.  Now, you and I might think something like that isn't all that valuable... but if you give that piece of junk a neat name like \"Savage Fuzz Tail\" and put it in a pretty box, then people will think it's valuable.  Trash becomes treasure!$B$BGet me soft bushy tails from the wolves of Desolace and the Badlands, and I'll give you Darkmoon Faire tickets." WHERE Id=7901;

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht, $N! Diese buschigen Schwänze werden unseren Besuchern gefallen - und das bedeutet sogleich glückliche Besucher... Besucher, die ihren Freunden vom Jahrmarkt erzählen und somit für noch mehr Publikum sorgen!$B$BHier sind Eure Lose! Viel Spaß auf dem Dunkelmond-Jahrmarkt... und vergesst nicht Euren Freunden von uns zu erzählen!" WHERE Id=7901;

UPDATE quest_template SET Method=2, Level=30, RequiredMaxRepFaction=909, RequiredMaxRepValue=2500, Flags=8200, SpecialFlags=1, OfferRewardText="Ah, the plumes!  They are amazing, don't you think!  It would be easy to spark one's imaginations with such beauties!$B$BYou do such charitable work, <name>.  The smiles on our visitors' faces when they see the show is a grand payment indeed, but please take these tickets as well.", RequestItemsText="A person's imagination is an incredible thing.  It can make the smallest hill seem like the largest mountain.  It can make the most innocuous shadow appear cast by a horrible nightmare!$B$BWe at the Darkmoon Faire let our visitor's imaginations blossom!  But to help stretch their imaginations... sometimes we have to get tricky.$B$BI need vibrant plumes for one of my attractions.  You can get them from the birds of the more dangerous areas of Azeroth.  Bring me the plumes and many tickets will be yours!" WHERE Id=7902;

UPDATE quest_template SET Level=1 WHERE Id=29507;

UPDATE quest_template SET Method=2, Level=1, RequiredMaxRepFaction=909, RequiredMaxRepValue=500, Flags=8200, SpecialFlags=1, OfferRewardText="Great! These will work great! They're not too heavy, but not too light either. They're perfect for building muscle mass!$B$BThanks much, $N. Here's your Darkmoon Faire ticket!", RequestItemsText="It takes a lot of work to be the strongest woman alive!  My weight set is getting too light and if I'm to stay fit then I'll need more weights!$B$BDo you think you could bring me some weight stones?  If you do, then I'll give you a Darkmoon Faire ticket." WHERE Id=7889;

UPDATE locales_quest SET OfferRewardText_loc3="Großartig. Das wird wunderbar funktionieren. Nicht zu schwer aber auch nicht zu leicht. Perfekt um Muskeln aufzubauen!$B$BIch danke Euch, $N, Hier sind Eure Dunkelmond Jahrmarkts Lose." WHERE Id=7889;

UPDATE quest_template SET Method=2, Level=1, RequiredMaxRepFaction=909, RequiredMaxRepValue=1100, Flags=8200, SpecialFlags=1, OfferRewardText="You brought the stones!  And they're heavy!  I can already feel my muscles getting bigger.  Thanks $N!$B$BHere, take these tickets, and be sure not to eat too many sweets while you're at the faire.  A big strong $C like you needs to keep himself in fighting shape!", RequestItemsText="To help with my workout, I like to fit a staff between heavy grinding stones, then lift the staff over my head.  It isn't easy, but being the strongest woman in the world, like I am, can't be earned sitting down!$B$BCan you help me?  I need more grinding stones - bring me some and I'll trade Darkmoon Faire tickets for them." WHERE Id=7890;

UPDATE quest_template SET Method=2, Level=20, RequiredMaxRepFaction=909, RequiredMaxRepValue=1700, Flags=8200, SpecialFlags=1, OfferRewardText="Yes!  These are exactly what I need!  Such a lovely color, and they still leave my arms bare so you can see how strong they are!  Perfect!$B$BHere you are, $N.  Here are your tickets - enjoy!", RequestItemsText="I'm working on a new costume, for when I have my own booth as the strongest woman alive!  Right now I'm looking for some bracers I can wear.  They can't cover much because people want to see my muscles, but I still want to flash a little color, you know?$B$BHow about green iron bracers, $N?  Can you make me green iron bracers?  If you can, then I have a whole bunch of Darkmoon Faire tickets for you." WHERE Id=7891;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ja! Das sind genau die Richtigen! Sie haben so eine wunderschöne Farbe und lassen meine Arme ausreichend frei, damit man sehen kann wie stark ich bin! Perfekt!$B$BHier, $N. Hier sind Eure Lose - amüsiert Euch schön!" WHERE Id=7891;

UPDATE quest_template SET Method=2, Level=30, RequiredMaxRepFaction=909, RequiredMaxRepValue=2500, Flags=8200, SpecialFlags=1, OfferRewardText="Ah, perfect!  This mace has a big, heavy head on it.  I bet I could smash just about anything with it.  I just hope I don't break it along with whatever I swing it against!$B$BHere are your tickets, $N.  Enjoy your stay at the faire!", RequestItemsText="For my act as the strongest woman alive, I plan to accept items from the audience and smash them with a big, black mace!$B$BCan you make me a big black mace, $N?" WHERE Id=7892;

UPDATE quest_template SET Method=2, Level=6, Flags=8200, SpecialFlags=1, OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets.", RequestItemsText="Step right up, step right up!  If you have tickets from the Darkmoon Faire you'd like redeemed, then just say so!  You can redeem tickets in various denominations for wondrous and fantastic prizes.  Don't be shy, give it a try!" WHERE Id=7930;

UPDATE locales_quest SET RequestItemsText_loc3="Kommt näher, kommt näher! Wenn ihr Lose vom Dunkelmond-Jahrmarkt habt, die ihr einlösen möchtet, dann sagt nur Bescheid! Ihr könnt Lose gegen zahlreiche, wundersame und fantastische Preise einlösen. Scheut euch nicht, probiert es aus!" WHERE Id=7930;

UPDATE quest_template SET Method=2, Level=15, Flags=8200, SpecialFlags=1, EndText="Here you go, here you go! A prize fit for a <king/queen>! Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know! For as long as the Darkmoon Faire is here, I'll", OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets." WHERE Id=7931;

UPDATE locales_quest SET EndText_loc3="Kommt näher, kommt näher! Wenn ihr Lose vom Dunkelmond-Jahrmarkt habt, die ihr einlösen möchtet, dann sagt nur Bescheid! Ihr könnt Lose gegen zahlreiche, wundersame und fantastische Preise einlösen. Scheut euch nicht, probiert es aus!" WHERE Id=7931;

UPDATE quest_template SET Method=2, Level=25, Flags=8200, SpecialFlags=1, OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets.", RequestItemsText="Step right up, step right up!  If you have tickets from the Darkmoon Faire you'd like redeemed, then just say so!  You can redeem tickets in various denominations for wondrous and fantastic prizes.  Don't be shy, give it a try!" WHERE Id=7935;

UPDATE locales_quest SET OfferRewardText_loc3="Bitteschön, bitteschön! Ein passender Preis für einen König! Meinen Glückwunsch!$B$BSolltet Ihr noch mehr Lose haben, die Ihr einlösen möchtet, dann lasst es mich bitte wissen! Solange der Dunkelmond-Jahrmarkt hier ist, werde ich Eure Lose entgegennehmen." WHERE Id=7935;

UPDATE quest_template SET Method=2, Level=30, Flags=8200, SpecialFlags=1, OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets.", RequestItemsText="Step right up, step right up!  If you have tickets from the Darkmoon Faire you'd like redeemed, then just say so!  You can redeem tickets in various denominations for wondrous and fantastic prizes.  Don't be shy, give it a try!" WHERE Id=7932;

UPDATE locales_quest SET RequestItemsText_loc3="Kommt näher, kommt näher! Wenn ihr Lose vom Dunkelmond-Jahrmarkt habt, die ihr einlösen möchtet, dann sagt nur Bescheid! Ihr könnt Lose gegen zahlreiche, wundersame und fantastische Preise einlösen. Scheut euch nicht, probiert es aus!" WHERE Id=7932;

UPDATE quest_template SET Method=2, Level=6, Flags=8200, SpecialFlags=1, OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets.", RequestItemsText="Step right up, step right up!  If you have tickets from the Darkmoon Faire you'd like redeemed, then just say so!  You can redeem tickets in various denominations for wondrous and fantastic prizes.  Don't be shy, give it a try!" WHERE Id=7934;

UPDATE locales_quest SET RequestItemsText_loc3="Kommt näher, kommt näher! Wenn ihr Lose vom Dunkelmond-Jahrmarkt habt, die ihr einlösen möchtet, dann sagt nur Bescheid! Ihr könnt Lose gegen zahlreiche, wundersame und fantastische Preise einlösen. Scheut euch nicht, probiert es aus!" WHERE Id=7934;

UPDATE quest_template SET Method=2, Level=45, Flags=8200, SpecialFlags=1, OfferRewardText="Here you go, here you go!  A prize fit for a king!  Congratulations to you, my friend!$B$BIf you have more tickets you'd like to turn in, then please let me know!  For as long as the Darkmoon Faire is here, I'll redeem your tickets.", RequestItemsText="Step right up, step right up!  If you have tickets from the Darkmoon Faire you'd like redeemed, then just say so!  You can redeem tickets in various denominations for wondrous and fantastic prizes.  Don't be shy, give it a try!" WHERE Id=7936;

UPDATE locales_quest SET RequestItemsText_loc3="Kommt näher, kommt näher! Wenn ihr Lose vom Dunkelmond-Jahrmarkt habt, die ihr einlösen möchtet, dann sagt nur Bescheid! Ihr könnt Lose gegen zahlreiche, wundersame und fantastische Preise einlösen. Scheut euch nicht, probiert es aus!" WHERE Id=7936;

update npc_text set BroadcastTextID0=10165 where id=7398;

UPDATE quest_template SET Method=2, Level=1, RequiredMaxRepFaction=909, RequiredMaxRepValue=500, Flags=8200, SpecialFlags=1, OfferRewardText="Aha!  The modulators!  Superb!$B$BI can't tell you exactly what we're building, but these will be invaluable for its construction.  I am in your debt, <name>, but please, take this Darkmoon Faire ticket as a token of my appreciation.", RequestItemsText="Yebb is developing a new attraction for the Zoo Bizarre, one that will drive people crazy with wonder, and delight!  But it will take a lot of work, and a lot of materials...$B$BThat includes copper modulators.  We need lots of modulators for the mechanical parts of the attraction.  Bring me copper modulators and I'll trade for them with a Darkmoon Faire ticket." WHERE Id=7894;

UPDATE quest_template SET Method=2, Level=10, RequiredMaxRepFaction=909, RequiredMaxRepValue=1100, Flags=8200, SpecialFlags=1, OfferRewardText="You brought the gizmos!  Wonderful!  Even now I can hear their buzzing, whirring chorus in my mind!  Oh, when this booth is ready it will be the wonder of the world, mark me!$B$BHere are your tickets, $N.  And please enjoy your stay at the Faire!", RequestItemsText="My new booth will be a sight to see, yes sir!  A sight to see, and... for a lucky few, to touch!$B$BI can already hear the whirring bronze gizmos singing their song of mechanical rapture as patrons step to my booth and test their skill!$B$BAh... now I need the gizmos themselves to bring my dream closer to fruition.  Please, <name>, bring me whirring bronze gizmos... and Darkmoon Faire tickets will be yours!" WHERE Id=7895;

UPDATE quest_template SET Method=2, Level=20, RequiredMaxRepFaction=909, RequiredMaxRepValue=1700, Flags=8200, SpecialFlags=1, OfferRewardText="You brought the fireworks.  Wonderful work, <name>!  I can't wait to light these and tell the world that my booth is ready to go!  I must still wait, quite a long time I'm afraid, but... I'll be ready when I'm ready, yes?$B$BHere are the tickets, $N.  Enjoy yourself!", RequestItemsText="When I finally get this booth up and running, I'll want to advertise!  And what better way is there to advertise than with fireworks?$B$BWell, some might think that the smell of a cauldron, churning with the boiling heads of your foes is better for drawing crowds, but... we're in mixed company.  So fireworks it will have to be!$B$BBring me green fireworks, $N, and I have a big fistful of Darkmoon Faire tickets for you." WHERE Id=7896;

UPDATE quest_template SET Method=2, Level=30, RequiredMaxRepFaction=909, RequiredMaxRepValue=2500, Flags=8200, SpecialFlags=1, OfferRewardText="Thank you!  Now I can get to fixing things.$B$BIt's going to take a lot of repair kits and a lot of late nights to get everything in working order.  Sometimes I think it'd be better to get back to my roots and restart my career as a headhunter, but... the Faire has been good to me.$B$BTake these tickets, $N, and have fun!", RequestItemsText="The biggest reason I can't open up my booth is that... everything's broken!  I need mechanical repair kits to fix all this stuff!$B$BCan you bring me those kits, $N?  I'll trade you... kits for Darkmoon Faire tickets.  What do you say?" WHERE Id=7897;

SET @GUID=270326;

UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@GUID, 0, -4003.537, 6254.285, 10.06505, 5.612407, 5000, 0),
(@GUID, 1, -4069.523, 6325.563, 10.00841, 2.317663, 0, 0),
(@GUID, 2, -4113.795, 6350.085, 9.700578, 2.63575, 0, 0),
(@GUID, 3, -4170.447, 6356.026, 9.700578, 3.059865, 0, 0),
(@GUID, 4, -4297.712, 6343.854, 9.637695, 3.142332, 5000, 0),
(@GUID, 5, -4297.712, 6343.854, 9.637695, 3.142332, 0, 0),
(@GUID, 6, -4170.447, 6356.026, 9.700578, 3.059865, 0, 0),
(@GUID, 7, -4113.795, 6350.085, 9.700578, 2.63575, 0, 0),
(@GUID, 8, -4069.523, 6325.563, 10.00841, 2.317663, 0, 0),
(@GUID, 9, -4003.537, 6254.285, 10.06505, 5.612407, 5000, 0);

delete from creature_formations where leaderGUID=270326;
insert into creature_formations values 
(270326, 270326, 0, 0, 0, 0, 0),
(270326, 270327, 3.0, 360, 0, 1, 3);


