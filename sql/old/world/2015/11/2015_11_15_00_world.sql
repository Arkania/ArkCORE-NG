
-- quest 866
UPDATE quest_template SET RequiredSkillPoints=40 WHERE Id=866;

-- npc 11046 -- gossip
delete from gossip_menu_option where menu_id=4118;
insert into gossip_menu_option values (4118, 0, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0);

-- npc 8359 -- gossip
delete from gossip_menu_option where menu_id=4325 and id=1;

-- npc 3483 -- gossip
delete from gossip_menu_option where menu_id=4324 and id=2;

-- some flower flying
update gameobject set position_z=22.72 where guid=31361;
update gameobject set position_z=34.86 where guid=9399;
update gameobject set position_z=21.30 where guid=16061;
update gameobject set position_z=21.80 where guid=11800;
update gameobject set position_z=20.16 where guid=31363;
update gameobject set position_z=65.94 where guid=11574;
update gameobject set position_z=23.65 where guid=31382;
update gameobject set position_z=26.36 where guid=1206;

update creature set spawndist=10, MovementType=1 where id=6368;

