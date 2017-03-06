
--  Zul'Aman

-- delete wrong loot for unused npc's
delete from creature_loot_template where entry in (46210,46209);

-- Akil'zon <Avatar  > 23574
delete from creature_loot_template where entry=23574 and item in (0,33214,33215,33216,33281,33283,33286,33293);
insert into creature_loot_template values(23574,33214,14.4,1,0,1,1);
insert into creature_loot_template values(23574,33215,9.9,1,0,1,1);
insert into creature_loot_template values(23574,33216,20.2,1,0,1,1);
insert into creature_loot_template values(23574,33281,16.2,1,0,1,1);
insert into creature_loot_template values(23574,33283,9.5,1,0,1,1);
insert into creature_loot_template values(23574,33286,15.6,1,0,1,1);
insert into creature_loot_template values(23574,33293,14.2,1,0,1,1);

-- Nalorakk <Avatar > 23576
delete from creature_loot_template where entry=23576 and item in (0,33191,33203,33206,33211,33285,33327,33640);
insert into creature_loot_template values(23576,33191,16.8,1,0,1,1);
insert into creature_loot_template values(23576,33203,8.9,1,0,1,1);
insert into creature_loot_template values(23576,33206,13.2,1,0,1,1);
insert into creature_loot_template values(23576,33211,17,1,0,1,1);
insert into creature_loot_template values(23576,33285,17.4,1,0,1,1);
insert into creature_loot_template values(23576,33327,14.9,1,0,1,1);
insert into creature_loot_template values(23576,33640,11.7,1,0,1,1);

-- Halazzi <Lynx Avatar>  23577
delete from creature_loot_template where entry=23577 and item in (0,33297,33299,33300,33303,33317,33322,33533);
insert into creature_loot_template values(23577,33297,15.4,1,0,1,1);
insert into creature_loot_template values(23577,33299,10.9,1,0,1,1);
insert into creature_loot_template values(23577,33300,18.8,1,0,1,1);
insert into creature_loot_template values(23577,33303,11.3,1,0,1,1);
insert into creature_loot_template values(23577,33317,13.6,1,0,1,1);
insert into creature_loot_template values(23577,33322,16,1,0,1,1);
insert into creature_loot_template values(23577,33533,13,1,0,1,1);

-- Jan'alai <Dragonhawk Avatar>  23578
delete from creature_loot_template where entry=23578 and item in (0,33326,33328,33329,33332,33354,33356,33357);
insert into creature_loot_template values(23578,33326,13.7,1,0,1,1);
insert into creature_loot_template values(23578,33328,14.1,1,0,1,1);
insert into creature_loot_template values(23578,33329,17.8,1,0,1,1);
insert into creature_loot_template values(23578,33332,9.9,1,0,1,1);
insert into creature_loot_template values(23578,33354,15.7,1,0,1,1);
insert into creature_loot_template values(23578,33356,12.8,1,0,1,1);
insert into creature_loot_template values(23578,33357,15.9,1,0,1,1);

-- Daakara <The Invincible> 23863
delete from creature_loot_template where entry=23863 and item in (0,33466,33467,33468,33469,33471,33473,33474,33476,33478,33479,33830,33831);
insert into creature_loot_template values(23863,33466,21.6,1,0,1,1);
insert into creature_loot_template values(23863,33467,21.1,1,0,1,1);
insert into creature_loot_template values(23863,33468,11.5,1,0,1,1);
insert into creature_loot_template values(23863,33469,17,1,0,1,1);
insert into creature_loot_template values(23863,33471,13.8,1,0,1,1);
insert into creature_loot_template values(23863,33473,16.5,1,0,1,1);
insert into creature_loot_template values(23863,33474,12.3,1,0,1,1);
insert into creature_loot_template values(23863,33476,17.3,1,0,1,1);
insert into creature_loot_template values(23863,33478,20.3,1,0,1,1);
insert into creature_loot_template values(23863,33479,16.5,1,0,1,1);
insert into creature_loot_template values(23863,33830,10.8,1,0,1,1);
insert into creature_loot_template values(23863,33831,14.5,1,0,1,1);

-- Hex Lord Malacrass 24239
delete from creature_loot_template where entry=24239 and item in (0,33298,33388,33389,33421,33432,33446,33453,33463,33464,33465,33592,33828,33829,34029);
insert into creature_loot_template values(24239,33298,15.5,1,0,1,1);
insert into creature_loot_template values(24239,33388,15.7,1,0,1,1);
insert into creature_loot_template values(24239,33389,20.9,1,0,1,1);
insert into creature_loot_template values(24239,33421,14.8,1,0,1,1);
insert into creature_loot_template values(24239,33432,14,1,0,1,1);
insert into creature_loot_template values(24239,33446,17.8,1,0,1,1);
insert into creature_loot_template values(24239,33453,11.8,1,0,1,1);
insert into creature_loot_template values(24239,33463,15.1,1,0,1,1);
insert into creature_loot_template values(24239,33464,15.3,1,0,1,1);
insert into creature_loot_template values(24239,33465,15.3,1,0,1,1);
insert into creature_loot_template values(24239,33592,11.6,1,0,1,1);
insert into creature_loot_template values(24239,33828,16.1,1,0,1,1);
insert into creature_loot_template values(24239,33829,14,1,0,1,1);
insert into creature_loot_template values(24239,34029,24.3,1,0,1,1);

















