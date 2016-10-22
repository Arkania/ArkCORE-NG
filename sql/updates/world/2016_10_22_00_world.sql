
UPDATE creature_template SET ScriptName="npc_orc_scout_35894" WHERE entry=35894;

UPDATE creature_template SET ScriptName="npc_kilag_gorefang_35893" WHERE entry=35893;

update creature_template_addon set auras="" where entry in (35896, 35897); -- 15595 sniff show unknown spell "Root Self" = 23973.. 

delete from vehicle_template_accessory where entry=35995;
insert into vehicle_template_accessory values 
(35995, 36042, 0, 0, "Strangle Vine", 6, 30000);

UPDATE creature_template SET ScriptName="npc_poison_spitter_35896" WHERE entry=35896;

UPDATE creature_template SET ScriptName="npc_freezya_35897" WHERE entry=35897;

UPDATE creature_template SET ScriptName="npc_strangle_vine_35995" WHERE entry=35995;

