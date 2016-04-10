
--  http://www.wowhead.com/quest=27099/no-escape

UPDATE locales_quest SET OfferRewardText_loc3="Anscheinend muss man Crowley ernster nehmen, als ich gedacht habe. Dennoch, er ist ein Mensch - Fleisch und Blut - voller Geheimnisse. Geheimnisse, die ich alle kenne...$B$BIhr habt mir gute Dienste erwiesen, $N. Ich könnte jemand mit Euren Fähigkeiten am Grabmal gebrauchen. Ich habe einen Plan, um mit Crowley und seinen Aufrührern endgültig fertigzuwerden. Werdet Ihr mir auch weiterhin zur Seite stehen?", CompletedText_loc3="Benachrichtigt Fürstin Sylvanas Windläufer in der Kommandozentrale der Verlassenen im Silberwald." WHERE Id=27099;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Worgenrenegat", QuestGiverTargetName_loc3="Worgenrenegat" WHERE Id=26989;

UPDATE locales_quest SET OfferRewardText_loc3="Ausgezeichnet! Mit diesen Eingeweiden und dem wilden Verhängniskraut können wir den Erregerstamm unserer neuen Krankheit testen. Jetzt müssen wir nur noch ein geeignetes Ziel auswählen." WHERE Id=26995;

UPDATE locales_quest SET RequestItemsText_loc3="Habt Ihr die Murlocs der Finsterflossen bei den Morgeninseln ausgerottet?" WHERE Id=26998;

UPDATE locales_quest SET OfferRewardText_loc3="Belmont wird ein bisschen nervös und schon schickt er irgendeinen Grünschnabel, um nach mir zu suchen? Hört zu, ich habe das Ivarhaus aus diesem Plumpsklo heraus drei Tage lang observiert. Eure Anwesenheit gefährdet die gesamte verdammte Mission!$B$BIch habe keine Zeit für Erklärungen. Wir müssen jetzt handeln. Sonst war alles umsonst." WHERE Id=27039;

update creature set phaseMask=8 where id in(53577);

update creature set phaseMask=9, spawntimesecs=120 where id in (44793, 44792, 44791, 44913);

delete from creature_loot_template where entry=44793 and item in (3110, 20765, 21776);
insert into creature_loot_template values
(44793,  3110, 0, 38.0, 1, 1, 0, 1, 1, ""),
(44793, 20765, 0, 0.01, 1, 1, 0, 1, 1, ""),
(44793, 21776, 0, 0.01, 1, 1, 0, 1, 1, "");

update creature_template set AIName="", ScriptName="npc_forsaken_trooper_44791" where entry=44791;
update creature_template set AIName="", ScriptName="npc_forsaken_trooper_44791" where entry=44792;
update creature_template set AIName="", ScriptName="npc_worgen_renegade_44793" where entry=44793;

delete from creature where id=44733;

delete from creature where id in (44732, 44733, 44734, 44737);

UPDATE creature_template SET spell1=83477, npcflag=16777216 WHERE entry=44731;

UPDATE creature_template SET npcflag=0, unit_flags=33536 WHERE entry=44732;

UPDATE creature_template SET npcflag=0, unit_flags=33536 WHERE entry=44733;

UPDATE creature_template SET npcflag=0, unit_flags=33536 WHERE entry=44734;

delete from vehicle_template_accessory where entry=44731;
insert into vehicle_template_accessory values
(44731, 44734, 0, 0, "Horde Engineer as driver", 8, 0),
(44731, 44737, 1, 0, "Ettin as horse", 8, 0),
(44731, 44733, 3, 0, "Trooper as passenger", 8, 0),
(44731, 44732, 4, 0, "Trooper as passenger", 8, 0),
(44731, 44733, 5, 0, "Trooper as passenger", 8, 0),
(44731, 44733, 6, 0, "Trooper as passenger", 8, 0),
(44731, 44732, 7, 0, "Trooper as passenger", 8, 0);
 
delete from npc_spellclick_spells where npc_entry in (44731, 44732, 44733, 44734, 44737);
insert into npc_spellclick_spells values
(44731, 46598, 0, 0), -- car
(44737, 46598, 0, 0), -- horse
(44734, 46598, 0, 0), -- driver
(44732, 46598, 0, 0), -- 2 passengers 
(44733, 46598, 0, 0); -- 3 passengers 

UPDATE creature_template SET questItem1=60742, questItem2=60743 WHERE entry=1765;

UPDATE creature_template SET questItem2=60742, questItem3=60743 WHERE entry=1778;

delete from gameobject_loot_template where entry=1765 and item in (60742, 2672);
insert into gameobject_loot_template values
(1765, 60742, 0, 8, 1, 1, 0, 1, 1, ""),
(1765, 2672, 0, 13, 1, 1, 0, 1, 1, "");

delete from vehicle_template_accessory where entry=45120;
insert into vehicle_template_accessory values
(45120, 44913, 0, 0, "Orc Sea Dog as driver", 8, 0);
 
delete from npc_spellclick_spells where npc_entry in (45120, 44913) and spell_id=46598;
insert into npc_spellclick_spells values
(45120, 46598, 0, 0), -- car Orc Demolisher
(44913, 46598, 0, 0); -- driver

update creature set spawndist=0, MovementType=0 where id=45120;

delete from gossip_menu_option where menu_id=6944 and id=2;

update creature_template set gossip_menu_id=11892, AIName="", ScriptName="npc_bat_handler_maggotbreath_44825" where entry=44825;

delete from gossip_menu_option where menu_id=11892;
insert into gossip_menu_option values 
(11892, 0, 2, "Show me where I can fly.", 12271, 4, 8192, 0, 0, 0, 0, 0, "", 0),
(11892, 1, 0, "I need to take a bat to the Dawning Isles.", 44905, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=11892 AND SourceEntry=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1, Comment) VALUES 
(15, 11892, 1, 9, 26998, "Show gossip option if player has quest");

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=6944 AND SourceEntry=1;

UPDATE creature_template SET spell1=83573 WHERE entry=44821;

update creature_template set gossip_menu_id=11892, AIName="", ScriptName="npc_forsaken_bat_44821" where entry=44821;

DELETE FROM creature_text where entry=26539 and groupid=0;
INSERT INTO creature_text values 
(26539, 0, 0, "The zeppelin to Vengeance Landing has just arrived! All aboard for Howling Fjord!", 12, 0, 100, 0, 0, 0, "", 29540);

DELETE FROM creature_text where entry=9566 and groupid=0;
INSERT INTO creature_text values 
(9566, 0, 0, "The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!", 12, 0, 100, 0, 0, 0, "", 22077);

DELETE FROM creature_text where entry=3150 and groupid=0;
INSERT INTO creature_text values 
(3150, 0, 0, "The zeppelin to Grom'gol has just arrived! All aboard for Stranglethorn!", 12, 0, 100, 0, 0, 0, "", 22097);

DELETE FROM creature_text where entry=1536 and groupid=0 and id=4;
INSERT INTO creature_text values 
(1536, 0, 4, "%s attempts to run away in fear!", 12, 0, 100, 0, 0, 0, "", 1150);

DELETE FROM creature_text where entry=1537 and groupid=0 and id=4;
INSERT INTO creature_text values 
(1537, 0, 4, "%s attempts to run away in fear!", 12, 0, 100, 0, 0, 0, "", 1150);

DELETE FROM creature_text where entry=44825 and groupid=0;
INSERT INTO creature_text values 
(44825, 0, 0, "You better bring that bat back in one piece, $N!", 12, 0, 100, 1, 0, 0, "", 44906);

DELETE FROM creature_text where entry=44791 and groupid between 0 and 2;
INSERT INTO creature_text values 
(44791, 0, 0, "That beast came from nowhere!", 12, 0, 100, 5, 0, 0, "", 44836),
(44791, 1, 0, "Worgen filth! I spit on your corpse!", 12, 0, 100, 14, 0, 0, "", 44837),
(44791, 2, 0, "They won't take our land without a fight!", 12, 0, 100, 15, 0, 0, "", 44838);

DELETE FROM creature_text where entry=44792 and groupid between 0 and 2;
INSERT INTO creature_text values 
(44792, 0, 0, "That beast came from nowhere!", 12, 0, 100, 5, 0, 0, "", 44836),
(44792, 1, 0, "Worgen filth! I spit on your corpse!", 12, 0, 100, 14, 0, 0, "", 44837),
(44792, 2, 0, "They won't take our land without a fight!", 12, 0, 100, 15, 0, 0, "", 44838);

DELETE FROM creature_text where entry=44734 and groupid=0;
INSERT INTO creature_text values 
(44734, 0, 0, "ALL ABOARD! Next stop: The Sepulcher.", 12, 0, 100, 0, 0, 0, "", 44796);

DELETE FROM creature_text where entry=44821 and groupid between 0 and 1;
INSERT INTO creature_text values 
(44821, 0, 0, "Eliminate all murlocs by using the Blight Concoction!$B$B|r|TInterface\Icons\INV_ALCHEMY_POTION_05.BLP:24|t", 42, 0, 100, 0, 0, 0, "", 44902),
(44821, 1, 0, "Returning to Forsaken High Command!$B$B|r|TInterface\Icons\ACHIEVEMENT_ZONE_SILVERPINE_01.BLP:24|t", 42, 0, 100, 0, 0, 0, "", 44903);

DELETE FROM creature_text where entry=44882 and groupid between 0 and 2;
INSERT INTO creature_text values 
(44882, 0, 0, "We haven't got much time. Crowley will be arriving shortly. Let's go!", 12, 0, 100, 5, 0, 0, "", 44951),
(44882, 1, 0, "THERE! Hide in the armoire! I'll hide in the shadows next to you.", 12, 0, 100, 25, 0, 0, "", 44955),
(44882, 2, 0, "I live... and die... for the Banshee Queen.", 12, 0, 100, 0, 0, 0, "", 44971);

DELETE FROM creature_text where entry=45498 and groupid between 0 and 4;
INSERT INTO creature_text values 
(45498, 0, 0, "Hey, \"Salty\" when are you going to get a new name? Thish town ain't big 'nough for two of ussh...", 12, 0, 100, 22, 0, 0, "", 45621),
(45498, 1, 0, "Yoo hoo!  \"Shmaltzy!\"  Hey, why come your shupplies... Whe... Oh... Um... You got lots of boxes to keep track of...", 12, 0, 100, 22, 0, 0, "", 45624),
(45498, 2, 0, "Pssst!  Pssst!  Hey!  \"Pepper!\"  Are you done hording all the shupplies!  You shee what I just did? Horde..  For the horde!", 12, 0, 100, 22, 0, 0, "", 45625),
(45498, 3, 0, "I didn't like that pet anyways.  Beshides... People stop by all the time and give me their pets.  If I lost one, it doesn't matter, I've got dozens more to lose!", 12, 0, 100, 22, 0, 0, "", 45637),
(45498, 4, 0, "I sent my pet out to get me shome more to drink.  You'll be shorry when he shows up with a wagon full of Mudder's Milk and you don't get any.", 12, 0, 100, 22, 0, 0, "", 45638);

DELETE FROM creature_text where entry=44916 and groupid between 0 and 1;
INSERT INTO creature_text values 
(44916, 0, 0, "Who's not drunk, Torok?", 12, 0, 100, 0, 0, 0, "", 45018),
(44916, 1, 0, "Yes.", 12, 0, 100, 0, 0, 0, "", 45020);

DELETE FROM creature_text where entry=44917 and groupid between 0 and 1;
INSERT INTO creature_text values 
(44917, 0, 0, "Including me?", 12, 0, 100, 6, 0, 0, "", 45019),
(44917, 1, 0, "<hic!> Well... Let's see... By my count, nobody. The whole crew's drunk out of their gourds, admiral... 'cept the sea pups... <hic!>", 12, 0, 100, 0, 0, 0, "", 45021);

DELETE FROM creature_text where entry=45497 and groupid between 0 and 2;
INSERT INTO creature_text values 
(45497, 0, 0, "It's \"Salty!\"  I got here firsht!  I got off the boat and onto land firsht!  I called the name \"Salty.\"  Hey... Where's your pet at?", 12, 0, 100, 22, 0, 0, "", 45627),
(45497, 1, 0, "Maybe you should worry about your pet and not me!  I'm taking care of my bushinesh jusht fine!", 12, 0, 100, 22, 0, 0, "", 45628),
(45497, 2, 0, "Hey, shtop bothering me.  You're a dishgrace to us all.  You can't even hold onto your own petsh!", 12, 0, 100, 22, 0, 0, "", 45631);

DELETE FROM creature_text where entry=44914 and groupid between 0 and 7;
INSERT INTO creature_text values 
(44914, 0, 0, "Where to going, captain?", 12, 0, 100, 66, 0, 0, "", 44990),
(44914, 1, 0, "Dis not so bad. Maybe little heavy, but me ok.", 12, 0, 100, 0, 0, 0, "", 44991),
(44914, 2, 0, "Maybe captain carry one box too?", 12, 0, 100, 0, 0, 0, "", 44994),
(44914, 3, 0, "Captain, pup need help!", 12, 0, 100, 0, 0, 0, "", 44996),
(44914, 4, 0, "Please, captain, I can put box down?", 12, 0, 100, 0, 0, 0, "", 44999),
(44914, 5, 0, "Please... Kill... Me...", 12, 0, 100, 0, 0, 0, "", 45001),
(44914, 6, 0, "OOF!", 12, 0, 100, 0, 0, 0, "", 45024),
(44914, 7, 0, "Where to put? Dey falling! HELP!", 12, 0, 100, 0, 0, 0, "", 45025);

DELETE FROM creature_text where entry=44942 and groupid between 0 and 3;
INSERT INTO creature_text values 
(44942, 0, 0, "Welcome to the party, $G pal:lady;!", 12, 0, 100, 5, 0, 0, "", 45077),
(44942, 1, 0, "Thank you, friend. Let's kill us some overgrown... spiders. Sounded better in my head.", 12, 0, 100, 5, 0, 0, "", 45078),
(44942, 2, 0, "We gotta find the matriarch of this operation and end her!", 12, 0, 100, 5, 0, 0, "", 45079),
(44942, 3, 0, "I need a drink!", 12, 0, 100, 5, 0, 0, "", 45080);

DELETE FROM creature_text where entry=44913 and groupid between 0 and 1;
INSERT INTO creature_text values 
(44913, 0, 0, "It'sh makin' me hungry... why's it shooo big? You shome kind of idiot or shomething? Makin' a chicken sho big... Who doesh that?", 12, 0, 100, 1, 0, 0, "", 45062),
(44913, 1, 0, "Forshaken do... that'sh who...It'sh sho big... Look at it'sh big shtupid neck. I jusht want to choke it to death!", 12, 0, 100, 1, 0, 0, "", 45063);

DELETE FROM creature_text where entry=44912 and groupid=0;
INSERT INTO creature_text values 
(44912, 0, 0, "Touch my chicken and I will kill you in your sleep. Am I understood?", 12, 0, 100, 1, 0, 0, "", 45069);

DELETE FROM creature_text where entry=44951 and groupid between 0 and 11;
INSERT INTO creature_text values 
(44951, 0, 0, "This way, $N. We will take them by surprise.", 12, 0, 100, 457, 0, 0, "", 45193),
(44951, 0, 1, "The warmth of this place sickens me.", 12, 0, 100, 0, 0, 0, "", 45095),
(44951, 0, 2, "Do you feel it, $N? The darkness surrounds us.", 12, 0, 100, 0, 0, 0, "", 45097),
(44951, 0, 3, "Life is meaningless. It is in the afterlife that we are truly tested.", 12, 0, 100, 0, 0, 0, "", 45098),
(44951, 0, 4, "I sense doom in your future, $N.", 12, 0, 100, 0, 0, 0, "", 45094),
(44951, 0, 5, "I long for the frozen wastes of Northrend.", 12, 0, 100, 0, 0, 0, "", 45096),
(44951, 0, 6, "Different master, same insatiable thirst for power.", 12, 0, 100, 0, 0, 0, "", 45093),
(44951, 0, 7, "Waste no time, $N. We mustn't keep the Banshee Queen waiting.", 12, 0, 100, 0, 0, 0, "", 45092),
(44951, 0, 8, "Through me the Banshee Queen sees all...", 12, 0, 100, 0, 0, 0, "", 45099),
(44951, 1, 0, "Rise, $N! Become Forsaken!", 14, 0, 100, 0, 0, 0, "", 45091),
(44951, 1, 1, "Bow before your new master!", 14, 0, 100, 0, 0, 0, "", 45114),
(44951, 1, 2, "Rise and destroy our enemies!", 14, 0, 100, 0, 0, 0, "", 45115);

DELETE FROM creature_text where entry=44959 and groupid between 0 and 4;
INSERT INTO creature_text values 
(44959, 0, 0, "I am Forsaken.", 12, 0, 100, 66, 0, 0, "", 45106),
(44959, 0, 1, "For the glory of the Dark Lady!", 12, 0, 100, 15, 0, 0, "", 45107),
(44959, 0, 2, "Wha... What has happened?", 12, 0, 100, 6, 0, 0, "", 45108),
(44959, 0, 3, "I am eternal... I am death.", 12, 0, 100, 273, 0, 0, "", 45109),
(44959, 0, 4, "I LIVE!", 12, 0, 100, 15, 0, 0, "", 45111);

DELETE FROM creature_text where entry=44964 and groupid between 0 and 1;
INSERT INTO creature_text values 
(44964, 0, 0, "At your command.", 12, 0, 100, 66, 0, 0, "", 45110),
(44964, 1, 0, "I understand.", 12, 0, 100, 0, 0, 0, "", 53318);

DELETE FROM creature_text where entry=44960 and groupid between 0 and 4;
INSERT INTO creature_text values 
(44960, 0, 0, "I am Forsaken.", 12, 0, 100, 66, 0, 0, "", 45106),
(44960, 1, 0, "For the glory of the Dark Lady!", 12, 0, 100, 15, 0, 0, "", 45107),
(44960, 2, 0, "Wha... What has happened?", 12, 0, 100, 6, 0, 0, "", 45108),
(44960, 3, 0, "I am eternal... I am death.", 12, 0, 100, 273, 0, 0, "", 45109),
(44960, 4, 0, "I LIVE!", 12, 0, 100, 15, 0, 0, "", 45111);



