

update spell_phase set terrainswapmap=638, worldmapareaswap=683, comment="Quest Zone-Specific 06, Duskhaven invasion" where spell_id=68481 and id=0;

update spell_phase set terrainswapmap=638, worldmapareaswap=683, comment="Quest Zone-Specific 07, Duskhaven invasion" where spell_id=68482 and id=0;

update spell_phase set  comment="Quest Zone-Specific 08, Duskhaven shattered land" where spell_id=68483 and id=0;

update spell_phase set  comment="Quest Zone-Specific 08, Duskhaven shattered land" where spell_id=68483 and id=4;

-- 42962	42964	42965
delete from npc_spellclick_spells where npc_entry=42962 and spell_id=46598;
insert into npc_spellclick_spells values 
(42962, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=42964 and spell_id=46598;
insert into npc_spellclick_spells values 
(42964, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=42965 and spell_id=46598;
insert into npc_spellclick_spells values 
(42965, 46598, 0, 0);

-- 42887	42892
delete from npc_spellclick_spells where npc_entry=42887 and spell_id=46598;
insert into npc_spellclick_spells values 
(42887, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=42892 and spell_id=46598;
insert into npc_spellclick_spells values 
(42892, 46598, 0, 0);

-- 45024	45027
delete from npc_spellclick_spells where npc_entry=45024 and spell_id=46598;
insert into npc_spellclick_spells values 
(45024, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=45027 and spell_id=46598;
insert into npc_spellclick_spells values 
(45027, 46598, 0, 0);

-- 45004	45028
delete from npc_spellclick_spells where npc_entry=45004 and spell_id=46598;
insert into npc_spellclick_spells values 
(45004, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=45028 and spell_id=46598;
insert into npc_spellclick_spells values 
(45028, 46598, 0, 0);

-- 43952	45064
delete from npc_spellclick_spells where npc_entry=43952 and spell_id=46598;
insert into npc_spellclick_spells values 
(43952, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=45064 and spell_id=46598;
insert into npc_spellclick_spells values 
(45064, 46598, 0, 0);

-- 44353	47172
delete from npc_spellclick_spells where npc_entry=44353 and spell_id=46598;
insert into npc_spellclick_spells values 
(44353, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=47172 and spell_id=46598;
insert into npc_spellclick_spells values 
(47172, 46598, 0, 0);

-- 44352	47173
delete from npc_spellclick_spells where npc_entry=44352 and spell_id=46598;
insert into npc_spellclick_spells values 
(44352, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=47173 and spell_id=46598;
insert into npc_spellclick_spells values 
(47173, 46598, 0, 0);

-- 42788	47170
delete from npc_spellclick_spells where npc_entry=42788 and spell_id=46598;
insert into npc_spellclick_spells values 
(42788, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=47170 and spell_id=46598;
insert into npc_spellclick_spells values 
(47170, 46598, 0, 0);

-- 48640	48639
delete from npc_spellclick_spells where npc_entry=48640 and spell_id=46598;
insert into npc_spellclick_spells values 
(48640, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=48639 and spell_id=46598;
insert into npc_spellclick_spells values 
(48639, 46598, 0, 0);

-- 42543	42711
delete from npc_spellclick_spells where npc_entry=42543 and spell_id=46598;
insert into npc_spellclick_spells values 
(42543, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=42711 and spell_id=46598;
insert into npc_spellclick_spells values 
(42711, 46598, 0, 0);

-- 48642	48639
delete from npc_spellclick_spells where npc_entry=48642 and spell_id=46598;
insert into npc_spellclick_spells values 
(48642, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=48639 and spell_id=46598;
insert into npc_spellclick_spells values 
(48639, 46598, 0, 0);

-- 44136	44135
delete from npc_spellclick_spells where npc_entry=44136 and spell_id=46598;
insert into npc_spellclick_spells values 
(44136, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=44135 and spell_id=46598;
insert into npc_spellclick_spells values 
(44135, 46598, 0, 0);

-- 43116	43182
delete from npc_spellclick_spells where npc_entry=43116 and spell_id=46598;
insert into npc_spellclick_spells values 
(43116, 46598, 0, 0);

delete from npc_spellclick_spells where npc_entry=43182 and spell_id=46598;
insert into npc_spellclick_spells values 
(43182, 46598, 0, 0);

UPDATE creature SET spawntimesecs=120, spawndist=0, MovementType=2 WHERE guid=251499;

DELETE FROM creature_addon WHERE guid=251499;
INSERT INTO creature_addon VALUES 
(251499, 251499, 0, 0, 0, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=251499;
INSERT INTO waypoint_data VALUES 
(251499, 0, -1996.782, 831.0535, 66.02951, 3.767722, 0, 0, 0, 100, 0),
(251499, 1, -1996.782, 831.0535, 66.02951, 3.767722, 0, 0, 0, 100, 0),
(251499, 2, -1999.721, 825.2953, 66.02951, 4.392107, 0, 0, 0, 100, 0),
(251499, 3, -1989.004, 832.4166, 66.02951, 0.3905, 0, 0, 0, 100, 0),
(251499, 4, -2001.01, 836.1732, 66.02951, 2.797745, 0, 0, 0, 100, 0),
(251499, 5, -2003.009, 830.7334, 66.02951, 4.348906, 0, 0, 0, 100, 0),
(251499, 6, -1990.839, 833.0342, 66.02951, 0.052773, 0, 0, 0, 100, 0);

UPDATE creature SET spawntimesecs=120, spawndist=0, MovementType=2 WHERE guid=251516;

DELETE FROM creature_addon WHERE guid=251516;
INSERT INTO creature_addon VALUES 
(251516, 251516, 0, 0, 0, 0, 0, 0, 0, "");

DELETE FROM waypoint_data WHERE id=251516;
INSERT INTO waypoint_data VALUES 
(251516, 0, -2055.547, 955.1889, 70.01167, 6.021801, 0, 0, 0, 100, 0),
(251516, 1, -2047.332, 956.0767, 70.1542, 0.154875, 0, 0, 0, 100, 0),
(251516, 2, -2053.816, 965.3387, 70.1781, 2.267597, 0, 0, 0, 100, 0),
(251516, 3, -2063.144, 958.2491, 69.85641, 3.850175, 0, 0, 0, 100, 0),
(251516, 4, -2065.665, 946.0754, 70.04063, 4.517762, 0, 0, 0, 100, 0),
(251516, 5, -2053.94, 946.0564, 70.00212, 6.280979, 0, 0, 0, 100, 0),
(251516, 6, -2061.985, 957.3421, 69.89639, 2.192982, 0, 0, 0, 100, 0),
(251516, 7, -2048.602, 962.2726, 70.14308, 0.300171, 0, 0, 0, 100, 0);




