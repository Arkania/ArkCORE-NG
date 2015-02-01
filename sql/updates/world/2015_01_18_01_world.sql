
-- spawned by script, drive in the boat, from beach to beach
-- http://de.wowhead.com/npc=43432/messner
-- http://de.wowhead.com/npc=43433/jorgensen
-- http://de.wowhead.com/npc=43434/krakauer
-- http://de.wowhead.com/npc=43435/danforth
-- http://de.wowhead.com/npc=43184/john-j-keeshan

DELETE FROM `creature` WHERE `guid` in (9358,9359,9360,9361,26545);
DELETE FROM `creature_addon` WHERE `guid` in (9358,9359,9360,9361,26545);
DELETE FROM `creature_template_addon` WHERE `entry` in (43184,43432,43433,43434,43435);

-- http://www.wowhead.com/npc=43222/redridge-citizen 	should be near big earl, the street fighter
-- http://www.wowhead.com/npc=43247/redridge-citizen	should be near solomon, the magister
DELETE FROM `creature_template_addon` WHERE (`entry`=43222);
DELETE FROM `creature_template_addon` WHERE (`entry`=43247);

update creature set id=43247 where id=43222 and position_z>60.0;
update creature set id=43222 where id=43247 and position_z<60.0;

-- http://de.wowhead.com/npc=43449/john-j-keeshan, waiting on the beach, bevor driving to other side..
-- http://de.wowhead.com/npc=43448/messner
-- http://de.wowhead.com/npc=43447/jorgensen
-- http://de.wowhead.com/npc=43446/krakauer
-- http://de.wowhead.com/npc=43445/danforth
delete from creature_addon where guid in (9352,9353,9354,9355,9356);
insert into creature_addon values
(9352,0,0,0,1,0,80816),
(9353,0,0,0,1,0,80816),
(9354,0,0,0,1,0,80816),
(9355,0,0,0,1,0,80816),
(9356,0,0,0,1,0,80816);

-- spawned by script
-- http://www.wowhead.com/npc=43450/keeshans-riverboat#sells
delete from creature where guid in (16744,16745) and id=43450;
delete from creature_addon where guid in (16744,16745);

-- http://www.wowhead.com/npc=43443/keeshans-riverboat#sells
update creature set position_x=-9298.24, position_y=-2360.14,position_z=56.211 where guid=9375 and id=43443;

-- first quest's in redridge are with activ quest invis 1

DELETE FROM `spell_area` WHERE (`spell`=80695 OR `spell`=80817) AND `area`=44;
INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(80695, 44, 26503, 26520, 0, 0, 0, 1, 74, 9);

INSERT INTO `spell_area` (`spell`,`area`, `quest_start`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`, `quest_start_status`, `quest_end_status` ) VALUES 
(80817, 44, 26503, 26616, 0, 0, 0, 1, 74, 9);




