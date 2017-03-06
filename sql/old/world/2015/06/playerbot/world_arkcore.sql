
SET @Id=8010;

delete from arkcore_string where entry between @Id and @Id+16;
insert into arkcore_string (`entry`, `content_default`) values
(@Id+0,"To see list of available npcbot commands type .npcbot or .npcb"),
(@Id+1,"You can also use .maintank (or .mt or .main) command on any party member (even npcbot) so your bots will stick to your plan."),
(@Id+2,"If you want your npcbots to heal someone out of your party set any raid target icon on them."),
(@Id+3,"If you want your npcbots to heal someone out of your party set proper raid target icon on them, one of these:"),
(@Id+4,"star"),
(@Id+5,"circle"),
(@Id+6,"diamond"),
(@Id+7,"triangle"),
(@Id+8,"moon"),
(@Id+9,"square"),
(@Id+10,"cross"),
(@Id+11,"skull"),
(@Id+12,"I am tank here!"),
(@Id+13,"I will tank now."),
(@Id+14,"I gonna tank"),
(@Id+15,"I think I will be best tank here..."),
(@Id+16,"I AM the tank!");

