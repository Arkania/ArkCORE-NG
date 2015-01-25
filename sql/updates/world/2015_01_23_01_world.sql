
update creature_template set AIName="", ScriptName="" where entry=43094;
update creature_template set AIName="", ScriptName="npc_canyon_ettin_43197" where entry=43197;

delete from creature_text where entry in 
(334, 341, 435, 486, 648, 649, 650, 651, 652, 653, 3504, 3518, 5607, 5608, 8962, 8963, 43080, 43081, 43197, 43496, 43728, 43744, 43775, 43812, 43826, 43827, 43829);

insert into creature_text values
(334,0,0,"Your corpses will feed the Blackrock war machine.",12,0,100,0,0,0,"",43916), 

(341,0,0,"I... just... wanted... to... build... the... damned... bridge...",12,0,100,0,0,0,"",43176), 
(341,1,0,"Thank you,$G lad:lass;. Thank you, greatly.",12,0,100,0,0,0,"",2281), 


(435,0,0,"%s becomes enraged!",16,0,100,0,0,0,"",24144), 
(435,1,0,"[Orcish] Lok maka zaga Makogg kag kil Moth'kazoroth",12,0,100,0,0,0,"",0), 
(435,2,0,"[Orcish] Tago mog regas gi mog Tov'nokaz Kagg",12,0,100,0,0,0,"",0), 
(435,3,0,"[Orcish] Ogg kaz ko zugas kil mog Tov'nokaz Kagg",12,0,100,0,0,0,"",0), 

(486,0,0,"%s becomes enraged!",16,0,100,0,0,0,"",24144), 
(486,1,0,"[Broken Common] Death here for you.",12,0,100,0,0,0,"",43915),

(648,0,0,"HO!",12,0,100,0,0,0,"",43183),
(648,1,0,"ANYWHERE BUT THE BRIDGE!",12,0,100,0,0,0,"",43232),

(649,0,0,"HO!",12,0,100,0,0,0,"",43183),

(650,0,0,"HO!",12,0,100,0,0,0,"",43183),

(651,0,0,"HO!",12,0,100,0,0,0,"",43183),
(651,1,0,"NOOOOOO!!!",12,0,100,0,0,0,"",43231),

(652,0,0,"HO!",12,0,100,0,0,0,"",43183), 
(652,1,0,"I'M PUSHIN' AS HARD AS I CAN! THING WEIGHS A TON!",12,0,100,0,0,0,"",43186),

(653,0,0,"PUT YOUR BACKS INTO IT, BOYS!",12,0,100,0,0,0,"",43181), 
(653,1,0,"HEAVE!",12,0,100,0,0,0,"",43182), 
(653,2,0,"HO!",12,0,100,0,0,0,"",43183), 
(653,3,0,"DAMN ROCK WON'T BUDGE!",12,0,100,0,0,0,"",43184),
(653,4,0,"PUSH HARDER!",12,0,100,0,0,0,"",43185), 

(3504,0,0,"My feet hurt.",12,0,100,0,0,0,"",1099), 

(3518,0,0,"Fresh bread for sale!",12,0,100,0,0,0,"",1101), 
(3518,1,0,"Warm, wholesome bread!",12,0,100,0,0,0,"",1102),
(3518,2,0,"Rolls, buns and bread. Baked fresh!",12,0,100,0,0,0,"",1103), 
(3518,3,0,"Freshly baked bread for sale!",12,0,100,0,0,0,"",1104), 

(5607,0,0,"Fishing sounds good.",12,0,100,0,0,0,"",1924), 

(5608,0,0,"I dunno. What do you want to do?",12,0,100,0,0,0,"",1923), 

(8962,0,0,"I know how to speak kitty, and Effsee said thank you.",12,0,100,0,0,0,"",4628),

(8963,0,0,"Meow!",12,0,100,0,0,0,"",4627),

(43080,0,0,"Be on your guard, $c.",12,0,100,0,0,0,"",42963), 

(43081,0,0,"Outgoing, $c.",12,0,100,0,0,0,"",42986),

(43197,0,0,"ROCK NOT SO HEAVY! PUNY HUMIES!",12,0,100,0,0,0,"",43218),
(43197,1,0,"Where trow? TROW ON BRIDGE??",12,0,100,0,0,0,"",43220),
(43197,2,0,"OK! Me trow in water!",12,0,100,0,0,0,"",43222),
(43197,3,0,"BYE, BYE, DADDY!",14,0,100,0,0,0,"",43226),

(43496,0,0,"The Bravo Company, all present and accounted for...",12,0,100,0,0,0,"",44172),
(43496,1,0,"Did you truly believe that the orcs had the presence of mind required to plan an invasion of this magnitude?",12,0,100,0,0,0,"",44173), 
(43496,2,0,"No matter. You will die now, a paltry offering to Deathwing as our march upon Stormwind begins.",12,0,100,0,0,0,"",44174),
(43496,3,0,"Feed the master's rage! COME AND DIE!",14,0,100,0,0,0,"",44175),
(43496,4,0,"I grow tired of these games!",12,0,100,0,0,0,"",44176),
(43496,5,0,"Suffer in flames!",12,0,100,0,0,0,"",44177),
(43496,6,0,"You will die with me, Keeshan! This world has enough heroes!",12,0,100,0,0,0,"",44209),

(43728,0,0,"At your service.",12,0,100,0,0,0,"",43811), 

(43744,0,0,"AAHHHHHHHHH!!!!",12,0,100,0,0,0,"",43822),
(43744,1,0,"AAHHHHHHHHHHHHHHHHHH!!!!",12,0,100,0,0,0,"",43823),
(43744,2,0,"AAAAAAAAAAAHHHHHHHHHHHHH!!!!",12,0,100,0,0,0,"",43824),
(43744,3,0,"BLOOD AND THUNDER, RIGHT!?",12,0,100,0,0,0,"",43825),
(43744,4,0,"I CAN'T FIND YOUR LEGS, JOEY! I CAN'T FIND YOUR DAMNED LEGS!",12,0,100,0,0,0,"",43826),
(43744,5,0,"AAAHHHH!",12,0,100,0,0,0,"",43827),
(43744,6,0,"RUN TO YOUR DARK GODS, YOU FILTHY ANIMALS!",12,0,100,0,0,0,"",43828),
(43744,7,0,"THERE ARE NO FRIENDLY CIVILIANS!",12,0,100,0,0,0,"",43829),

(43775,0,0,"[Orcish] Nakaz kil Zugas zug Moth'kazoroth",12,0,100,0,0,0,"",0),

(43812,0,0,"AAAAAAHHHHHHHHHHHHHHH!",12,0,100,0,0,0,"",43922),
(43812,1,0,"WAR IS IN MY BLOOD!",12,0,100,0,0,0,"",44127),
(43812,2,0,"You brought this on yourself!",12,0,100,0,0,0,"",44128),
(43812,3,0,"Shoulda just left us alone.",12,0,100,0,0,0,"",44129),
(43812,4,0,"FEEL THE THUNDER!",12,0,100,0,0,0,"",44130),
(43812,5,0,"You're nothing!",12,0,100,0,0,0,"",44131),
(43812,6,0,"Your pain excites me!",12,0,100,0,0,0,"",44132),
(43812,7,0,"After we clean this place up, maybe we can start rebuilding it. Maybe they'll give it to Bravo Company. We'll call it: BRAVO KEEP!",12,0,100,0,0,0,"",44139),
(43812,8,0,"You gutless bastard! You've killed 'em all! Now I kill you!",12,0,100,0,0,0,"",44210),

(43826,0,0,"We all owe our lives to Keeshan. He's saved our hides a hundred times.",12,0,100,0,0,0,"",43480),

(43827,0,0,"I feel weak. I mean weaker than normal. Like as if the Light is less powerful this week. Probably just something I ate. Orc food gives me the craps.",12,0,100,0,0,0,"",43465),
(43827,1,0,"You ever seen Keeshan kill an orc? It's a sight to behold, $g man:lady;.",12,0,100,0,0,0,"",43466),
(43827,2,0,"Can't believe we're putting the old team back together. All thanks to you, $n.",12,0,100,0,0,0,"",43468),
(43827,3,0,"So I heard Thrall left the Horde. That true?",12,0,100,0,0,0,"",43469),

(43829,0,0,"GET SOME!",12,0,100,0,0,0,"",43436),
(43829,1,0,"Anyone hear from my girl? Darcy?",12,0,100,0,0,0,"",44143);




