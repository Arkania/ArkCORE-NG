
delete from creature_addon where guid in (6878, 7091, 7094);

update creature_template_addon set bytes1=65536, bytes2=1, emote=0, auras="79488 29266" where entry in (237, 238, 582);

update creature_template set npcflag=0 where entry in (237, 238, 582);

