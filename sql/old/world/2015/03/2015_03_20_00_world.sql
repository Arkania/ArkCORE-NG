
delete from spell_proc_event where entry in(34485, 46913, 34486, 34487, 50685, 84588, 46914, 46915, 53221, 53222, 53224, 81913, 81914, 29598, 84607, 84608, 80128, 80129, 53256, 53259, 53260, 5952, 9799, 11095, 11119, 11120, 11185, 11213, 11255, 12289, 12298, 12311, 12319, 12487, 12574, 12575, 12598, 12668, 12724, 12725, 12797, 12799, 12834, 12846, 12849, 12867, 12872, 12873, 12958, 12971, 12972, 13754, 13867, 14156, 14160, 14161, 14186, 14190, 14892, 15362, 16086, 16176, 16180, 16196, 16235, 16256, 16281, 16282, 16487, 16489, 16492, 16544, 17793, 17796, 17801, 18094, 18095, 19184, 19387, 19572, 19573, 20049, 20056, 20057, 20177, 20179, 20911, 25988, 29074, 29075, 29179, 29180, 29593, 29594, 29834, 29838, 30160, 30293, 30295, 31124, 31126, 31569, 31570, 31571, 31572, 32385, 32387, 32392, 33881, 33882, 34497, 34498, 34499, 34935, 34938, 34939, 34950, 34954, 35100, 35102, 35541, 35550, 35551, 46867, 46945, 46949, 47195, 47196, 47197, 47201, 47202, 47203, 47245, 47246, 47247, 47258, 47259, 47260, 47516, 47517, 47569, 47570, 47580, 47581, 48483, 48484, 48496, 48499, 48500, 48539, 48544, 49004, 49018, 49149, 49188, 49219, 49529, 49530, 49627, 49628, 50115, 51459, 51462, 51523, 51524, 51556, 51557, 51558, 51562, 51563, 51564, 51625, 51626, 51664, 51665, 51667, 51679, 51692, 51696, 52795, 52797, 53178, 53179, 53228, 53232, 53234, 53237, 53238, 53375, 53376, 53486, 53488, 53569, 53576, 53671, 53673, 53695, 53696, 53709, 53710, 54151, 55666, 55667, 56342, 56343, 56611, 56636, 56637, 56638, 56822, 57470, 57472, 57878, 57880, 59057, 62764, 62765, 63156, 63158, 63373, 63374, 63730, 63733, 65661, 66191, 66192, 77794, 77795, 77796, 82984, 82988, 84583, 84587, 85113, 85114, 88820);

delete from spell_group_stack_rules where group_id=1120;

update npc_text set BroadcastTextID0=27076 where ID=12946;

update creature_template set AIName="", ScriptName="" where entry=42697;

UPDATE `creature_template` SET `npcflag`=641 WHERE `entry`=37344;
UPDATE `creature_template` SET `npcflag`=3201 WHERE `entry`=37348;
UPDATE `creature_template` SET `npcflag`=3201 WHERE `entry`=37485;
UPDATE `creature_template` SET `npcflag`=641 WHERE `entry`=37399;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=31991;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=32105;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=37310;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=37426;
UPDATE `creature_template` SET `exp`=1 WHERE `entry`=22679;
UPDATE `creature_template` SET `exp`=1 WHERE `entry`=22639;
UPDATE `creature_template` SET `exp`=1 WHERE `entry`=22612;
UPDATE `creature_template` SET `exp`=1 WHERE `entry`=20544;
UPDATE `creature_template` SET `exp`=1 WHERE `entry`=21943;
UPDATE `creature_template` SET `exp`=3 WHERE `entry`=49155;
UPDATE `creature_template` SET `exp`=0 WHERE `entry` in (23576,52764);
UPDATE `creature_template` SET `exp`=2 WHERE `entry` in (36885,86885);
UPDATE `creature_template` SET `exp`=3 WHERE `entry` in (40765,49064);
UPDATE `creature_template` SET `exp`=3 WHERE `entry` in (40788,49082);

update creature_template set speed_walk=1,speed_run=1.14286 where entry=43499;

update creature_template set AIName="", ScriptName="" where entry in (46209,46210,46211);
update creature_template set AIName="", ScriptName="" where entry in (46227,46228,46229);

UPDATE `creature_template` SET `exp`=3 WHERE `entry`=49990;

UPDATE `creature_template` SET `difficulty_entry_1`=0 WHERE `entry`=49624;

update creature_template set AIName="", ScriptName="" where entry=51350;

UPDATE `creature_template` SET `exp`=3 WHERE `entry` in (57409,57771,57772);

UPDATE `creature_template` SET `difficulty_entry_2`=0, `difficulty_entry_3`=0 WHERE `entry`=57158;
UPDATE `creature_template` SET `difficulty_entry_2`=0, `difficulty_entry_3`=0 WHERE `entry`=57159;

update creature_template set speed_walk=1,speed_run=1.14286 where entry=993;

UPDATE `creature_template` SET `difficulty_entry_1`=0 WHERE `entry`=65184; 


delete from creature_equip_template where entry=44880;

delete from fishing_loot_template where entry=58503 and item=58503;

delete from creature_equip_template where entry=2355;

update creature_equip_template set id=1 where entry=43607 and id=0;
update creature_equip_template set id=1 where entry=43608 and id=0;
update creature_equip_template set id=1 where entry=43609 and id=0;
update creature_equip_template set id=1 where entry=43610 and id=0;
update creature_equip_template set id=1 where entry=43611 and id=0;

update `creature_template_addon` set `auras`="32783" where entry=50164;

update `creature_template_addon` set `auras`="65432" where `entry`=34917;
update `creature_template_addon` set `auras`="" where `entry`=34353;
update `creature_template_addon` set `auras`="" where `entry`=41747;
update `creature_template_addon` set `mount`=37496 where `entry`=46523;
update `creature_template_addon` set `mount`=37492 where `entry`=46520;
update `creature_template_addon` set `auras`="75236 52679" where `entry`=40353;
update `creature_template_addon` set `mount`=37212 where `entry`=46522;
update `creature_template_addon` set `mount`=2325 where `entry`=44833;

delete from `creature_template_addon` where `entry`=38318;
delete from `creature_template_addon` where `entry`=33292;

update `creature_template_addon` set `auras`="76624" where `entry`=40351;
update `creature_template_addon` set `auras`="76020" where `entry`=40761;
update `creature_template_addon` set `auras`="" where `entry`=41907;

update creature_template set flags_extra=0 where entry in (15757,15818,23899,21768,40630);

update creature set spawnmask=1 where guid=145590 and id=46383;
update creature set spawnmask=0 where guid=255045 and id=48844;

UPDATE `creature_template` SET `exp`=3 WHERE `entry`=57292;
UPDATE `creature_template` SET `exp`=3 WHERE `entry`=57293;

UPDATE `creature_template` SET `difficulty_entry_1`=48828 WHERE `entry`=40600;
UPDATE `creature_template` SET `exp`=2, faction=16 WHERE `entry`=48828;

UPDATE `creature_template` SET `difficulty_entry_1`=48845 WHERE `entry`=48844;
UPDATE `creature_template` SET `exp`=3, faction=16 WHERE `entry`=48845;

delete from pool_gameobject where pool_entry in (10796,10987,11176,11269,11745,11836,11929,12026,12216,12308);
delete from pool_template where entry in (10796,10987,11176,11269,11745,11836,11929,12026,12216,12308);

update game_event_creature_quest set eventEntry=26 where eventEntry=255 and id=20102 and quest=14036;
update game_event_creature_quest set eventEntry=26 where eventEntry=255 and id=19175 and quest=14036;
update game_event_creature_quest set eventEntry=26 where eventEntry=255 and id=19169 and quest=14036;
update game_event_creature_quest set eventEntry=26 where eventEntry=255 and id=20102 and quest=14022;
update game_event_creature_quest set eventEntry=26 where eventEntry=255 and id=18927 and quest=14022;














