
SET @Id=8010;

delete from arkcore_string where entry between @Id and @Id+11;
insert into arkcore_string (`entry`, `content_default`, `content_loc3`) values
(@Id+0,"To see list of available npcbot commands type .npcbot or .npcb","Um die verfügbare Hilfe aufzurufen, benutze .npcbot oder .npcb"),
(@Id+1,"You can also use .maintank (or .mt or .main) command on any party member (even npcbot) so your bots will stick to your plan.","Ausserdem könnt Ihr den Befehl .maintank(.mt oder .main) auf jedes Gruppenmitglied anwenden, so daß Eure Gruppe Euren Bedürfnissen entspricht."),
(@Id+2,"If you want your npcbots to heal someone out of your party set any raid target icon on them.","Wenn Euer Bot-Helfer Euch oder jemanden aus Eurer Gruppe heilen soll, gebt ihm ein entsprechendes Schlachtzug Icon im Gruppen-Kontrollfenster."),
(@Id+3,"If you want your npcbots to heal someone out of your party set proper raid target icon on them, one of these:","Wenn Euer Bot-Helfer Euch oder jemanden aus Eurer Gruppe heilen soll, gebt ihm eines der folgenden Schlachtzug Icon's im Gruppen-Kontrollfenster."),
(@Id+4,"star","Stern"),
(@Id+5,"circle","Kreis"),
(@Id+6,"diamond","Diamant"),
(@Id+7,"triangle","Dreieck"),
(@Id+8,"moon","Mond"),
(@Id+9,"square","Rechteck"),
(@Id+10,"cross","Kreuz"),
(@Id+11,"skull","Totenkopf");


