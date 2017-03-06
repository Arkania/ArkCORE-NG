
delete from creature_addon where guid in (6984,13620,13621);
insert into creature_addon values (6984,0,0,0,1,0,"79498");
insert into creature_addon values (13620,0,0,0,1,0,"79498");	
insert into creature_addon values (13621,0,0,0,1,0,"79498");


delete from creature_text where entry in (42383,42384,42386) and groupid in (10,11);
delete from creature_text where entry in (42390,42391,42400) and groupid in (10);

insert into creature_text values 
(42384,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42384,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42384,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42384,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42384,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332),
(42384,11,0,"Thank you, kind and gentle stranger.",12,0,100,0,0,0,"",42486),
(42384,11,1,"Westfall stew? I'll never forget this moment!",12,0,100,0,0,0,"",42487),
(42384,11,2,"I'd know that smell anywhere! Salma's famous stew!",12,0,100,0,0,0,"",42488),
(42384,11,3,"Maybe... maybe life is worth living.",12,0,100,0,0,0,"",42489),
(42384,11,4,"Bless you, friend.",12,0,100,0,0,0,"",42490),
(42384,11,5,"Perhaps one day I will repay you for this kind act.",12,0,100,0,0,0,"",42491),
(42386,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42386,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42386,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42386,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42386,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332),
(42386,11,0,"Thank you, kind and gentle stranger.",12,0,100,0,0,0,"",42486),
(42386,11,1,"Westfall stew? I'll never forget this moment!",12,0,100,0,0,0,"",42487),
(42386,11,2,"I'd know that smell anywhere! Salma's famous stew!",12,0,100,0,0,0,"",42488),
(42386,11,3,"Maybe... maybe life is worth living.",12,0,100,0,0,0,"",42489),
(42386,11,4,"Bless you, friend.",12,0,100,0,0,0,"",42490),
(42386,11,5,"Perhaps one day I will repay you for this kind act.",12,0,100,0,0,0,"",42491),
(42383,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42383,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42383,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42383,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42383,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332),
(42383,11,0,"Thank you, kind and gentle stranger.",12,0,100,0,0,0,"",42486),
(42383,11,1,"Westfall stew? I'll never forget this moment!",12,0,100,0,0,0,"",42487),
(42383,11,2,"I'd know that smell anywhere! Salma's famous stew!",12,0,100,0,0,0,"",42488),
(42383,11,3,"Maybe... maybe life is worth living.",12,0,100,0,0,0,"",42489),
(42383,11,4,"Bless you, friend.",12,0,100,0,0,0,"",42490),
(42383,11,5,"Perhaps one day I will repay you for this kind act.",12,0,100,0,0,0,"",42491),
(42390,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42390,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42390,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42390,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42390,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332),
(42391,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42391,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42391,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42391,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42391,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332),
(42400,10,0,"Down with the king!",12,0,100,0,0,0,"",42330),
(42400,10,1,"Heartless monsters!",12,0,100,0,0,0,"",42334),
(42400,10,2,"What do you expect us to do?",12,0,100,0,0,0,"",42336),
(42400,10,3,"Dirty, rotten pig-lickers. You'll get your come-uppance some day.",12,0,100,0,0,0,"",42347),
(42400,10,4,"What right do you have keeping us out?",12,0,100,0,0,0,"",42332);


update creature_addon set auras=NULL where guid in (43318,43569,43102,43107,42964,43122);

update creature_template_addon set auras=NULL where entry=42793;

update creature_template set modelid1=23690 where entry=234;

update creature_template_addon set auras="92290" where entry in (449,589,594);

update creature_template_addon set auras="79497" where entry in (54371,54372,54373);

delete from creature_addon where guid in (6667,6981,6669,6753,6755,6656,42752,43228,43007,43248,43180,43061,42585,42342);
insert into creature_addon (guid,bytes2,auras) values 
(6667,1,"92290"),
(6981,1,"92290"),
(6669,1,"92290"),
(6753,1,"92290"),
(6755,1,"92290"),
(6656,1,"92290"),
(42752,1,"92290"),
(43228,1,"92290"),
(43007,1,"92290"),
(43248,1,"92290"),
(43180,1,"92290"),
(43061,1,"92290"),
(42342,1,"92290"),
(42585,1,"92290");














