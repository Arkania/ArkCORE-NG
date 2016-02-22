
-- issue #79

update creature_template set AIName="", ScriptName="npc_gershala_nightwhisper_32911" where entry=32911;
update creature_template set AIName="", ScriptName="npc_cerellean_whiteclaw_33093" where entry=33093;
update creature_template set AIName="", ScriptName="npc_volcor_33094" where entry=33094;
update creature_template set AIName="", ScriptName="npc_shaldyn_33095" where entry=33095;
update creature_template set AIName="", ScriptName="npc_lordanel_sentinel_32969" where entry=32969;

delete from creature_text where entry=32969 and groupid between 0 and 7 and id=0;
insert into creature_text values 
(32969,0,0,"Cerellean! You made it!",12,0,100,0,0,0,"",33248),
(32969,1,0,"I'll get him back to Lor'danel.  Thank you for your help, stranger.",12,0,100,0,0,0,"",33249),
(32969,2,0,"Gershala... Dentaria will be so happy to see you alive.",12,0,100,0,0,0,"",33258),
(32969,3,0,"I'll take him back to the priestess. Thank you for your kindness.",12,0,100,0,0,0,"",33259),
(32969,4,0,"Shaldyn!",12,0,100,0,0,0,"",33261),
(32969,5,0,"I will see to it that Shaldyn is returned safely. Thank you, hero.",12,0,100,0,0,0,"",33260),
(32969,6,0,"Volcor... I'm so glad to see that you made it. But where is Grimclaw?",12,0,100,0,0,0,"",33262),
(32969,7,0,"We'll worry about him later. I need to get you to safety.",12,0,100,0,0,0,"",33263);

update npc_text set BroadcastTextID0=33150 where ID=14299;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Priesterin Dentaria in Lor'danel zurück." WHERE Id=13518;

update creature_template set InhabitType=4 where entry in (43747, 43751);


