
update creature_template set AIName="", ScriptName="npc_bravo_company_siege_tank" where entry=43734;

-- quest 26708 AHHHHHHHHHHHHHH has a buggy spell 81808
-- we need a core programmer, who is able to help us..
-- i set the quest to autocomplete

update quest_template set Flags=65544, Method=0 where Id=26708;


