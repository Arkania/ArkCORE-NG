

update creature_template set AIName="", ScriptName="boss_alzzin_the_wildshaper" where entry=11492;
update creature_template set AIName="", ScriptName="boss_captain_kromcrush" where entry=14325;
update creature_template set AIName="", ScriptName="boss_chorush_the_observer" where entry=14324;
update creature_template set AIName="", ScriptName="boss_guard_fengus" where entry=14321;
update creature_template set AIName="", ScriptName="boss_guard_moldar" where entry=14326;
update creature_template set AIName="", ScriptName="boss_guard_slipkik" where entry=14323;
update creature_template set AIName="", ScriptName="boss_hydrospawn" where entry=13280;
update creature_template set AIName="", ScriptName="boss_illyanna_ravenoak" where entry=11488;
update creature_template set AIName="", ScriptName="boss_immolthar" where entry=11496;
update creature_template set AIName="", ScriptName="boss_king_gordok" where entry=11501;
update creature_template set AIName="", ScriptName="boss_lethtendris" where entry=14327;
update creature_template set AIName="", ScriptName="boss_magister_kalendris" where entry=11487;
update creature_template set AIName="", ScriptName="boss_prince_tortheldrin" where entry=11486;
update creature_template set AIName="", ScriptName="boss_stomper_kreeg" where entry=14322;
update creature_template set AIName="", ScriptName="boss_tendris_warpwood" where entry=11489;
update creature_template set AIName="", ScriptName="boss_zevrim_thornhoof" where entry=11490;
update creature_template set AIName="", ScriptName="npc_pusillin_14354" where entry=14354;
update creature_template set AIName="", ScriptName="npc_old_ironbark_11491" where entry=11491;
update creature_template set AIName="", ScriptName="npc_ironbark_the_redeemed_14241" where entry=14241;
update gameobject_template set AIName="", ScriptName="go_conservatory_door_176907" where entry=176907;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Estulan zurück." WHERE Id=27112;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zum Behüter der Shen'dralar zurück.", QuestGiverTextWindow_loc3="Tendris Wucherborke", QuestGiverTargetName_loc3="Tendris Wucherborke" WHERE Id=27109;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zur Uralten Shen'dralar zurück." WHERE Id=27110;

UPDATE creature_template SET faction=14, type_flags=72 WHERE entry=11486;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu 'Botschafter' Dagg'thol zurück." WHERE Id=27107;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu 'Botschafter' Dagg'thol zurück." WHERE Id=27108;

update npc_text set BroadcastTextID0=45125 where ID=16713;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Furgus Wucherborke zurück." WHERE Id=27103;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Furgus Wucherborke zurück." WHERE Id=27104;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Furgus Wucherborke zurück." WHERE Id=27105;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Martie Jainrose in Seenhain im Rotkammgebirge zurück." WHERE Id=26509;

delete from gameobject where guid=184293 and id=177198;

UPDATE quest_template SET RequiredItemId1=18540, RequiredItemId2=0, RequiredItemCount1=1, RequiredItemCount2=0 WHERE Id=27103;

delete from creature_text where entry=16097;
insert into creature_text values 
(16097, 0, 0, "In life, I focused my energies on healing others. Let us see in death how much pain I can cause!", 12, 0, 100, 0, 0, 0, "", 11970),
(16097, 1, 0, "My torture is ended and now I can join the Goddess. Thank you so very much!", 12, 0, 100, 0, 0, 0, "", 11860);


delete from gameobject_loot_template where entry=179548 and item=18365;
insert into gameobject_loot_template values
(179548, 18365, 0, 1, 1, 1, 1);

delete from gameobject_loot_template where entry=179528 and item in (18255, 18297);
insert into gameobject_loot_template values
(179528, 18255, 50, 1, 0, 5, 10),
(179528, 18297, 100, 1, 0, 1, 1);

delete from gameobject where id=179528 and guid in (189215, 189169, 189199, 189231, 189179, 189177, 189219, 189227, 189207);
delete from gameobject where id=179528 and guid in (189181, 189211, 189173, 189223, 189185, 189189, 189180, 189193, 189197);

update creature_loot_template set ChanceOrQuestChance=100 where entry=14354 and item=18249;
	
delete from creature where id=14354;
insert into creature (guid, id, map, position_x, position_y, position_z, orientation, spawntimesecs, spawndist, curhealth, curmana, MovementType) values
(154088, 14354, 429, 83.390000, -198.430000, -3.950000, 2.800000, 7200, 3, 5896, 7698, 1);	

delete from creature_text where entry=14354;
insert into creature_text values 
(14354, 0, 0, "Do you want to play a game, stinky?", 12, 0, 100, 0, 0, 0, "", 9350),
(14354, 0, 1, "I hold the key to lands of free! Catch me and you'll see!", 12, 0, 100, 0, 0, 0, "", 9351),
(14354, 0, 2, "Still alive? You do surprise. Watch me as I flee!", 12, 0, 100, 0, 0, 0, "", 9354),
(14354, 0, 3, "Turn that frown upside down!", 12, 0, 100, 0, 0, 0, "", 9358),
(14354, 0, 4, "This is the end of the line, no friend of mine!", 12, 0, 100, 0, 0, 0, "", 9361),
(14354, 1, 0, "A Game? Are you crazy?", 12, 0, 100, 0, 0, 0, "", 9352),
(14354, 1, 1, "Why you little...", 12, 0, 100, 0, 0, 0, "", 9355),
(14354, 1, 2, "Mark my words, I will catch you, imp. And when I do!", 12, 0, 100, 0, 0, 0, "", 9356),
(14354, 1, 3, "DIE!", 12, 0, 100, 0, 0, 0, "", 9359),
(14354, 1, 4, "Prepare to meet your maker.", 12, 0, 100, 0, 0, 0, "", 9362),
(14354, 2, 0, "If you want the key, you'll have to catch me!", 12, 0, 100, 0, 0, 0, "", 9349),
(14354, 2, 1, "Chase me if you dare! I run without a care!", 12, 0, 100, 0, 0, 0, "", 9353),
(14354, 2, 2, "Why would you ever want to harm me!? Come. Friends we can be!", 12, 0, 100, 0, 0, 0, "", 9357),
(14354, 2, 3, "Die?! You make Pusillin cry!", 12, 0, 100, 0, 0, 0, "", 9360),
(14354, 2, 4, "Say hello to my little friends!", 12, 0, 100, 0, 0, 0, "", 9363);

DELETE FROM pool_template WHERE entry=14145;
INSERT INTO pool_template VALUES (14145,1,"MP Pusillin");

DELETE FROM pool_template WHERE entry=14146;
INSERT INTO pool_template VALUES (14146,1,"PP Pusillin");

DELETE FROM pool_pool WHERE pool_id=14146 AND mother_pool=14145;
INSERT INTO pool_pool VALUES (14146,14145,0,"Pool Pusillin");

DELETE FROM pool_creature WHERE guid=154088;
INSERT INTO pool_creature VALUES (154088,14146,0,"Pusillin");

DELETE FROM pool_creature WHERE guid=117125;
INSERT INTO pool_creature VALUES (117125,14146,0,"Pusillin");

DELETE FROM pool_creature WHERE guid=117126;
INSERT INTO pool_creature VALUES (117126,14146,0,"Pusillin");

DELETE FROM pool_creature WHERE guid=117127;
INSERT INTO pool_creature VALUES (117127,14146,0,"Pusillin");

DELETE FROM pool_creature WHERE guid=117128;
INSERT INTO pool_creature VALUES (117128,14146,0,"Pusillin");

--
UPDATE creature_template SET Health_mod=18 WHERE entry=11488;
UPDATE creature_template SET Health_mod=20 WHERE entry=14322;
UPDATE creature_template SET Health_mod=20 WHERE entry=14321;
UPDATE creature_template SET Health_mod=20 WHERE entry=14323;
UPDATE creature_template SET Health_mod=25 WHERE entry=11496;
UPDATE creature_template SET Health_mod=18 WHERE entry=16097;
UPDATE creature_template SET Health_mod=4 WHERE entry=11473;
UPDATE creature_template SET Health_mod=4 WHERE entry=11470;
UPDATE creature_template SET Health_mod=4 WHERE entry=11471;
UPDATE creature_template SET Health_mod=4 WHERE entry=11469;
UPDATE creature_template SET Health_mod=4 WHERE entry=11475;
UPDATE creature_template SET Health_mod=4 WHERE entry=14398;
UPDATE creature_template SET Health_mod=4 WHERE entry=11472;
UPDATE creature_template SET Health_mod=4 WHERE entry=11462;
UPDATE creature_template SET Health_mod=4 WHERE entry=11464;
UPDATE creature_template SET Health_mod=4 WHERE entry=11465;
UPDATE creature_template SET Health_mod=8 WHERE entry=13021;
UPDATE creature_template SET Health_mod=4 WHERE entry=11480;

UPDATE creature_template SET Health_mod=1 WHERE entry=14241;
UPDATE creature_template SET Health_mod=4 WHERE entry=14303;
UPDATE creature_template SET Health_mod=4 WHERE entry=11458;
UPDATE creature_template SET Health_mod=8 WHERE entry=11459;
UPDATE creature_template SET Health_mod=4 WHERE entry=11483;
UPDATE creature_template SET Health_mod=1 WHERE entry=11466;
UPDATE creature_template SET minlevel=45, maxlevel=45, Health_mod=0.1 WHERE entry=11446;

UPDATE creature_template SET Health_mod=8 WHERE entry=11448;
UPDATE creature_template SET Health_mod=9 WHERE entry=11445;
UPDATE creature_template SET Health_mod=8 WHERE entry=11450;
UPDATE creature_template SET minlevel=46, maxlevel=46, Health_mod=8 WHERE entry=14351;
UPDATE creature_template SET Health_mod=8 WHERE entry=11441;

UPDATE creature_template SET Health_mod=8 WHERE entry=11444;
UPDATE creature_template SET minlevel=46, maxlevel=46, Health_mod=2 WHERE entry=14385;

UPDATE creature_template SET Health_mod=1.5 WHERE entry=14385;
UPDATE creature_template SET Health_mod=20 WHERE entry=14326;
UPDATE creature_template SET Health_mod=1 WHERE entry=13036;
UPDATE creature_template SET Health_mod=8 WHERE entry=13285;
UPDATE creature_template SET Health_mod=8 WHERE entry=13197;
UPDATE creature_template SET Health_mod=8 WHERE entry=13196;
UPDATE creature_template SET Health_mod=4 WHERE entry=11461;
UPDATE creature_template SET Health_mod=4 WHERE entry=11456;
UPDATE creature_template SET Health_mod=4 WHERE entry=11454;
UPDATE creature_template SET Health_mod=4 WHERE entry=11455;
UPDATE creature_template SET Health_mod=4 WHERE entry=11452;
UPDATE creature_template SET Health_mod=4 WHERE entry=11453;
UPDATE creature_template SET Health_mod=1 WHERE entry=13276;
UPDATE creature_template SET Health_mod=4 WHERE entry=11457;
UPDATE creature_template SET Health_mod=4 WHERE entry=11451;
UPDATE creature_template SET minlevel=43, maxlevel=43, Health_mod=12 WHERE entry=11467;

UPDATE creature_template SET Health_mod=1 WHERE entry=11476;
UPDATE creature_template SET Health_mod=1 WHERE entry=11477;

UPDATE creature_template SET Health_mod=25 WHERE entry=11489;
UPDATE creature_template SET Health_mod=30 WHERE entry=11486;
UPDATE creature_template SET Health_mod=15 WHERE entry=11501;
UPDATE creature_template SET minlevel=61, maxlevel=62, Health_mod=6 WHERE entry=14324;
UPDATE creature_template SET minlevel=62, maxlevel=63, Health_mod=15 WHERE entry=14325;

UPDATE creature_template SET Health_mod=1 WHERE entry=11491;
UPDATE creature_template SET Health_mod=30 WHERE entry=11492;
UPDATE creature_template SET Health_mod=25 WHERE entry=11490;
UPDATE creature_template SET Health_mod=5 WHERE entry=14349;
UPDATE creature_template SET Health_mod=20 WHERE entry=14327;
UPDATE creature_template SET Health_mod=25 WHERE entry=11487;
UPDATE creature_template SET Health_mod=8 WHERE entry=11484;
UPDATE creature_template SET Health_mod=8 WHERE entry=14399;
UPDATE creature_template SET Health_mod=7 WHERE entry=14308;
UPDATE creature_template SET Health_mod=0.1 WHERE entry=14386;
UPDATE creature_template SET Health_mod=0.1 WHERE entry=14370;
UPDATE creature_template SET minlevel=47, maxlevel=47, Health_mod=8 WHERE entry=14353;
	
UPDATE creature_template SET minlevel=45, maxlevel=45, Health_mod=1 WHERE entry=45040;
UPDATE creature_template SET minlevel=45, maxlevel=45, Health_mod=1 WHERE entry=45052;
UPDATE creature_template SET minlevel=45, maxlevel=45, Health_mod=1 WHERE entry=56064;

UPDATE creature SET curhealth=7356 WHERE guid=117128 AND id=14354;
UPDATE creature SET curhealth=7356 WHERE guid=117128 AND id=14354;
UPDATE creature SET curhealth=7356 WHERE guid=117128 AND id=14354;
UPDATE creature SET curhealth=7356 WHERE guid=117128 AND id=14354;
UPDATE creature SET curhealth=4120 WHERE guid=154080 AND id=16045;
UPDATE creature SET curhealth=12260 WHERE guid=154083 AND id=13280;
UPDATE creature SET curhealth=25668 WHERE guid=154084 AND id=11488;
UPDATE creature SET curhealth=38380 WHERE guid=154085 AND id=14322;
UPDATE creature SET curhealth=38380 WHERE guid=154086 AND id=14321;
UPDATE creature SET curhealth=39800 WHERE guid=154087 AND id=14323;
UPDATE creature SET curhealth=7356 WHERE guid=117128 AND id=14354;
UPDATE creature SET curhealth=44550 WHERE guid=154089 AND id=11496;
UPDATE creature SET curhealth=2297 WHERE guid=154090 AND id=14364;
UPDATE creature SET curhealth=1321 WHERE guid=154091 AND id=14369;
UPDATE creature SET curhealth=1321 WHERE guid=154091 AND id=14369;
UPDATE creature SET curhealth=1321 WHERE guid=154091 AND id=14369;
UPDATE creature SET curhealth=2227 WHERE guid=154090 AND id=14364;
UPDATE creature SET curhealth=2227 WHERE guid=154090 AND id=14364;
UPDATE creature SET curhealth=43956 WHERE guid=154096 AND id=16097;
UPDATE creature SET curhealth=5284 WHERE guid=154099 AND id=11473;
UPDATE creature SET curhealth=5284 WHERE guid=154100 AND id=11470;
UPDATE creature SET curhealth=5072 WHERE guid=154099 AND id=11473;
UPDATE creature SET curhealth=4904 WHERE guid=154102 AND id=11471;
UPDATE creature SET curhealth=6340 WHERE guid=154103 AND id=11469;
UPDATE creature SET curhealth=6340 WHERE guid=154104 AND id=11475;
UPDATE creature SET curhealth=5284 WHERE guid=154105 AND id=14398;
UPDATE creature SET curhealth=6340 WHERE guid=154106 AND id=11472;
UPDATE creature SET curhealth=5072 WHERE guid=154099 AND id=11473;
UPDATE creature SET curhealth=6604 WHERE guid=154103 AND id=11469;
UPDATE creature SET curhealth=4904 WHERE guid=154102 AND id=11471;
UPDATE creature SET curhealth=5072 WHERE guid=154099 AND id=11473;
UPDATE creature SET curhealth=6604 WHERE guid=154103 AND id=11469;
UPDATE creature SET curhealth=5284 WHERE guid=154105 AND id=14398;
UPDATE creature SET curhealth=6096 WHERE guid=154106 AND id=11472;
UPDATE creature SET curhealth=5284 WHERE guid=154100 AND id=11470;
UPDATE creature SET curhealth=6604 WHERE guid=154104 AND id=11475;
UPDATE creature SET curhealth=4904 WHERE guid=154102 AND id=11471;
UPDATE creature SET curhealth=1651 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154117 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1651 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1651 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=1651 WHERE guid=154126 AND id=11476;
UPDATE creature SET curhealth=5580 WHERE guid=154133 AND id=11462;
UPDATE creature SET curhealth=5580 WHERE guid=154133 AND id=11462;
UPDATE creature SET curhealth=5580 WHERE guid=154133 AND id=11462;
UPDATE creature SET curhealth=4720 WHERE guid=154136 AND id=11464;
UPDATE creature SET curhealth=4540 WHERE guid=154136 AND id=11464;
UPDATE creature SET curhealth=4540 WHERE guid=154136 AND id=11464;
UPDATE creature SET curhealth=6096 WHERE guid=154139 AND id=11465;
UPDATE creature SET curhealth=6340 WHERE guid=154139 AND id=11465;
UPDATE creature SET curhealth=6340 WHERE guid=154139 AND id=11465;
UPDATE creature SET curhealth=11672 WHERE guid=154142 AND id=13021;
UPDATE creature SET curhealth=11672 WHERE guid=154142 AND id=13021;
UPDATE creature SET curhealth=5492 WHERE guid=154144 AND id=11480;
UPDATE creature SET curhealth=5284 WHERE guid=154144 AND id=11480;
UPDATE creature SET curhealth=2871 WHERE guid=154146 AND id=14241;
UPDATE creature SET curhealth=6340 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6340 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=6604 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6340 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6340 WHERE guid=154147 AND id=14303;
UPDATE creature SET curhealth=6340 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154149 AND id=11458;
UPDATE creature SET curhealth=12680 WHERE guid=154159 AND id=11459;
UPDATE creature SET curhealth=13208 WHERE guid=154159 AND id=11459;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154163 AND id=11483;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=6104 WHERE guid=154195 AND id=16032;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=13815 WHERE guid=154200 AND id=11445;
UPDATE creature SET curhealth=14784 WHERE guid=154201 AND id=11450;
UPDATE creature SET curhealth=14784 WHERE guid=154201 AND id=11450;
UPDATE creature SET curhealth=15352 WHERE guid=154201 AND id=11450;
UPDATE creature SET curhealth=15352 WHERE guid=154204 AND id=14351;
UPDATE creature SET curhealth=14784 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=10352 WHERE guid=154209 AND id=11444;
UPDATE creature SET curhealth=15352 WHERE guid=154204 AND id=14351;
UPDATE creature SET curhealth=15352 WHERE guid=154201 AND id=11450;
UPDATE creature SET curhealth=9976 WHERE guid=154209 AND id=11444;
UPDATE creature SET curhealth=13815 WHERE guid=154200 AND id=11445;
UPDATE creature SET curhealth=14784 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=15352 WHERE guid=154201 AND id=11450;
UPDATE creature SET curhealth=2878 WHERE guid=154219 AND id=14385;
UPDATE creature SET curhealth=15352 WHERE guid=154204 AND id=14351;
UPDATE creature SET curhealth=14784 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=14784 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=13815 WHERE guid=154200 AND id=11445;
UPDATE creature SET curhealth=38380 WHERE guid=154226 AND id=14326;
UPDATE creature SET curhealth=15352 WHERE guid=154204 AND id=14351;
UPDATE creature SET curhealth=15352 WHERE guid=154204 AND id=14351;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=10352 WHERE guid=154209 AND id=11444;
UPDATE creature SET curhealth=1782 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=185 WHERE guid=154196 AND id=11446;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=1336 WHERE guid=154198 AND id=11442;
UPDATE creature SET curhealth=14784 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154205 AND id=11441;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154240 AND id=13160;
UPDATE creature SET curhealth=1848 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154231 AND id=13036;
UPDATE creature SET curhealth=12680 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=12192 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=12680 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=10688 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=12192 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=12192 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154259 AND id=13022;
UPDATE creature SET curhealth=12680 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=12680 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=5072 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=4904 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=4904 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=5072 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=5072 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=4904 WHERE guid=154296 AND id=11461;
UPDATE creature SET curhealth=12192 WHERE guid=154256 AND id=13285;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=5580 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=5836 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=4720 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=4904 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=4904 WHERE guid=154317 AND id=11457;
UPDATE creature SET curhealth=6096 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=4720 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=11160 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=4904 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=5836 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=5836 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=5836 WHERE guid=154311 AND id=11452;
UPDATE creature SET curhealth=4904 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=4720 WHERE guid=154313 AND id=11453;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=5836 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5580 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=11160 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=5836 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5580 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=5836 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=4904 WHERE guid=154317 AND id=11457;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=5580 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=10688 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=5580 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5580 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=5580 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=4160 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=11160 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=10688 WHERE guid=154272 AND id=13196;
UPDATE creature SET curhealth=4720 WHERE guid=154317 AND id=11457;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=4016 WHERE guid=154307 AND id=11455;
UPDATE creature SET curhealth=5580 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=5836 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154303 AND id=11456;
UPDATE creature SET curhealth=5836 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154331 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154306 AND id=11454;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154260 AND id=13197;
UPDATE creature SET curhealth=20592 WHERE guid=154366 AND id=11467;
UPDATE creature SET curhealth=42900 WHERE guid=154368 AND id=11489;
UPDATE creature SET curhealth=6604 WHERE guid=154104 AND id=11475;
UPDATE creature SET curhealth=5072 WHERE guid=154099 AND id=11473;
UPDATE creature SET curhealth=1135 WHERE guid=154187 AND id=11466;
UPDATE creature SET curhealth=53460 WHERE guid=154375 AND id=11486;
UPDATE creature SET curhealth=48555 WHERE guid=154380 AND id=11501;
UPDATE creature SET curhealth=15540 WHERE guid=154381 AND id=14324;
UPDATE creature SET curhealth=49965 WHERE guid=154382 AND id=14325;
UPDATE creature SET curhealth=1585 WHERE guid=154383 AND id=11491;
UPDATE creature SET curhealth=38040 WHERE guid=154384 AND id=11492;
UPDATE creature SET curhealth=4904 WHERE guid=154317 AND id=11457;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154316 AND id=13276;
UPDATE creature SET curhealth=38100 WHERE guid=154392 AND id=11490;
UPDATE creature SET curhealth=5900 WHERE guid=154393 AND id=14349;
UPDATE creature SET curhealth=24520 WHERE guid=154394 AND id=14327;
UPDATE creature SET curhealth=35650 WHERE guid=154397 AND id=11487;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=10984 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=10568 WHERE guid=154404 AND id=14399;
UPDATE creature SET curhealth=12012 WHERE guid=154405 AND id=14308;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154412 AND id=13916;
UPDATE creature SET curhealth=1098 WHERE guid=154417 AND id=14400;
UPDATE creature SET curhealth=1098 WHERE guid=154417 AND id=14400;
UPDATE creature SET curhealth=1098 WHERE guid=154417 AND id=14400;
UPDATE creature SET curhealth=42 WHERE guid=154398 AND id=14366;
UPDATE creature SET curhealth=10568 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=305 WHERE guid=154436 AND id=14370;
UPDATE creature SET curhealth=10984 WHERE guid=154404 AND id=14399;
UPDATE creature SET curhealth=15920 WHERE guid=154438 AND id=14353;
UPDATE creature SET curhealth=10568 WHERE guid=154404 AND id=14399;
UPDATE creature SET curhealth=10568 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=305 WHERE guid=154436 AND id=14370;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=10984 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=10568 WHERE guid=154404 AND id=14399;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=305 WHERE guid=154436 AND id=14370;
UPDATE creature SET curhealth=10568 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=10984 WHERE guid=154399 AND id=11484;
UPDATE creature SET curhealth=152 WHERE guid=154436 AND id=14370;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=152 WHERE guid=154436 AND id=14370;
UPDATE creature SET curhealth=365 WHERE guid=154442 AND id=11460;
UPDATE creature SET curhealth=9156 WHERE guid=154466 AND id=14389;
UPDATE creature SET curhealth=3052 WHERE guid=154467 AND id=14122;
UPDATE creature SET curhealth=5836 WHERE guid=154468 AND id=44969;
UPDATE creature SET curhealth=1848 WHERE guid=154470 AND id=45040;
UPDATE creature SET curhealth=1848 WHERE guid=154471 AND id=45052;
UPDATE creature SET curhealth=1848 WHERE guid=154472 AND id=56064;
UPDATE creature SET curhealth=970 WHERE guid=154473 AND id=44992;
UPDATE creature SET curhealth=970 WHERE guid=154473 AND id=44992;
UPDATE creature SET curhealth=1093 WHERE guid=154475 AND id=44991;
UPDATE creature SET curhealth=3302 WHERE guid=154476 AND id=44999;
