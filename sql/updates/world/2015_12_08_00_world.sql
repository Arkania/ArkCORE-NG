
-- deepholm
update creature_template_addon set auras="31765 80852 83323 " where entry=42573;
update creature_template_addon set auras="80852 " where entry=42889;
update creature_template_addon set auras="84957 " where entry=43065;
update creature_template_addon set auras="83323 " where entry=43397;
update creature_template_addon set auras="83323 " where entry=43405;
update creature_template_addon set auras="84957 " where entry=44361;
update creature_template_addon set auras="84957 " where entry=44362;
update creature_template_addon set auras="78148 78150 84667" where entry=45035;
update creature_template_addon set auras="78148 78150 84667" where entry=45036;
update creature_template_addon set auras="79949 84667 " where entry=45037;
update creature_template_addon set auras="79949 84667 " where entry=45038;
update creature_template_addon set auras="78148 78150 84667" where entry=45039;

update creature_addon set auras="83323 " where guid=243061;
update creature_addon set auras="31765 80852 83323 " where guid=243062;

delete from creature where id in (44672, 44679);

