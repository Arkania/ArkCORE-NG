
delete from creature_text where entry=38535 and groupid in (0, 1, 2);
insert into creature_text values
(38535, 0, 0, "Gosh, Mr. Noggenfogger, I know you wouldn't want to damage your reputation as a neutral trade entity by forming closer ties to the Horde!", 12, 0, 100, 0, 0, 0, "", 40537),
(38535, 1, 0, "Oh, oh, I know this one! It's better than doing business with failed goblins that had to beg others for help!", 12, 0, 100, 0, 0, 0, "", 40539),
(38535, 2, 0, "There you go, Mister Noggenfogger! You won't have to worry about those giants anymore!", 12, 0, 100, 0, 0, 0, "", 40567);

delete from creature where guid=101509;
insert into creature values
(101509, 40505, 1, 1, 1, 0, 0, -7087.14, -3910.16, 11.7486, 4.53086, 300, 0, 0, 42, 0, 0, 0, 0, 0);

UPDATE creature_template SET InhabitType=4 WHERE entry=40505;


