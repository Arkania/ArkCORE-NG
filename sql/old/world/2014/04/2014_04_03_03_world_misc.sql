
-- creature_text for entry 16483
delete from creature_text where entry=16483 and groupid between 0 and 1 and id between 0 and 3;
delete from creature_text where entry=16483 and groupid=0 and id between 4 and 8;
insert into creature_text (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) values 
(16483,0,0,"The last thing I remember is the ship falling and us getting into the pods. I'll go see how I can help. Thank you!",12,0,100,0,0,0,""),
(16483,0,1,"$C, you saved me! I owe you a debt that I can never repay. I'll go see if I can help the others.",12,0,100,0,0,0,""),
(16483,0,2,"Ugh... what is this place? Is that all that's left of the ship over there?",12,0,100,0,0,0,""),
(16483,0,3,"$C, Where am I? Who are you? Oh no! What happened to the ship?",12,0,100,0,0,0,""),
(16483,0,4,"Huh? What happened? Oh... my head feels like it's going to explode! I'd best get back to the crash site.",12,0,100,0,0,0,""),
(16483,0,5,"Huh? What happened? Oh... my head feels like it's going to explode! I'd best get to the crash site.",12,0,100,0,0,0,""),
(16483,0,6,"Many thanks to you, $C. I'd best get to the crash site and see how I can help out. Until we meet again.",12,0,100,0,0,0,""),
(16483,0,7,"Oh no! Where are we? What happened? Look, there's part of the ship!",12,0,100,0,0,0,""),
(16483,0,8,"The Light be praised! I would have died out here if it weren't for you, shaman! I must get to the ship.",12,0,100,0,0,0,""),
(16483,1,0,"Oh, the pain...",12,0,100,0,0,0,""),
(16483,1,1,"Everything hurts. Please, make it stop...",12,0,100,0,0,0,""),
(16483,1,2,"Ughhh... I hurt. Can you help me?",12,0,100,0,0,0,""),
(16483,1,3,"I don't know if I can make it. Please help me...",12,0,100,0,0,0,"");

update creature_template set AIName="", ScriptName="npc_stillpine_captive" where entry=17375;




