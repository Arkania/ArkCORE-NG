
--
update creature_template_addon set auras="8042" where entry=5996;

update creature_addon set auras="8042" where guid in (select guid from creature where id=5996);
 
