

-- fix issue #116 part 3
-- 3) http://www.wowhead.com/npc=39087/slain-scarlet-friar - Must don't move, attack and have death state


update creature set spawndist=0, MovementType=0 where id in (39086, 39087);

delete from creature_addon where guid in (select guid from creature where id=39087);

update creature_template_addon set auras="29266 73304" where entry=39087;

delete from creature_addon where guid in (select guid from creature where id=39086);

update creature_template_addon set auras="29266 73304" where entry=39086;

delete from creature where guid in (5596, 5597, 5806, 5807, 5808, 5809);

