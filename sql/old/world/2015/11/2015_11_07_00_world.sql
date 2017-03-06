

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

update gossip_menu_option set OptionBroadcastTextID=9352 where menu_id=5709 and id=0;

delete from creature_text where entry=14354;
insert into creature_text values 
(14354, 1, 0, "If you want the key, you'll have to catch me!", 12, 0, 100, 0, 0, 0, "", 9349),
(14354, 2, 0, "Chase me if you dare! I run without a care!", 12, 0, 100, 0, 0, 0, "", 9353),
(14354, 3, 0, "Why would you ever want to harm me!? Come. Friends we can be!", 12, 0, 100, 0, 0, 0, "", 9357),
(14354, 4, 0, "Die?! You make Pusillin cry!", 12, 0, 100, 0, 0, 0, "", 9360),
(14354, 5, 0, "Say hello to my little friends!", 12, 0, 100, 0, 0, 0, "", 9363);

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

UPDATE creature SET curhealth=7356 WHERE guid=154088 AND id=14354;
UPDATE creature SET curhealth=1321 WHERE guid=154092 AND id=14369;
UPDATE creature SET curhealth=1321 WHERE guid=154093 AND id=14369;
UPDATE creature SET curhealth=2227 WHERE guid=154094 AND id=14364;
UPDATE creature SET curhealth=2297 WHERE guid=154095 AND id=14364;
UPDATE creature SET curhealth=5284 WHERE guid=154101 AND id=11473;
UPDATE creature SET curhealth=5072 WHERE guid=154107 AND id=11473;
UPDATE creature SET curhealth=6340 WHERE guid=154108 AND id=11469;
UPDATE creature SET curhealth=4904 WHERE guid=154109 AND id=11471;
UPDATE creature SET curhealth=5284 WHERE guid=154110 AND id=11473;
UPDATE creature SET curhealth=6340 WHERE guid=154111 AND id=11469;
UPDATE creature SET curhealth=5072 WHERE guid=154112 AND id=14398;
UPDATE creature SET curhealth=6340 WHERE guid=154113 AND id=11472;
UPDATE creature SET curhealth=5072 WHERE guid=154114 AND id=11470;
UPDATE creature SET curhealth=6340 WHERE guid=154115 AND id=11475;
UPDATE creature SET curhealth=5072 WHERE guid=154116 AND id=11471;
UPDATE creature SET curhealth=1651 WHERE guid=154118 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154119 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154120 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154121 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154122 AND id=11477;
UPDATE creature SET curhealth=1585 WHERE guid=154123 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154124 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154125 AND id=11477;
UPDATE creature SET curhealth=1651 WHERE guid=154127 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154128 AND id=11476;
UPDATE creature SET curhealth=1651 WHERE guid=154129 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154130 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154131 AND id=11476;
UPDATE creature SET curhealth=1585 WHERE guid=154132 AND id=11476;
UPDATE creature SET curhealth=5344 WHERE guid=154134 AND id=11462;
UPDATE creature SET curhealth=5344 WHERE guid=154135 AND id=11462;
UPDATE creature SET curhealth=4720 WHERE guid=154137 AND id=11464;
UPDATE creature SET curhealth=4720 WHERE guid=154138 AND id=11464;
UPDATE creature SET curhealth=6340 WHERE guid=154140 AND id=11465;
UPDATE creature SET curhealth=6340 WHERE guid=154141 AND id=11465;
UPDATE creature SET curhealth=11672 WHERE guid=154143 AND id=13021;
UPDATE creature SET curhealth=5284 WHERE guid=154145 AND id=11480;
UPDATE creature SET curhealth=6604 WHERE guid=154148 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154150 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154151 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154152 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154153 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154154 AND id=14303;
UPDATE creature SET curhealth=6604 WHERE guid=154155 AND id=14303;
UPDATE creature SET curhealth=6340 WHERE guid=154156 AND id=11458;
UPDATE creature SET curhealth=6604 WHERE guid=154157 AND id=11458;
UPDATE creature SET curhealth=6340 WHERE guid=154158 AND id=11458;
UPDATE creature SET curhealth=12680 WHERE guid=154160 AND id=11459;
UPDATE creature SET curhealth=5072 WHERE guid=154164 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154165 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154174 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154175 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154176 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154177 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154183 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154184 AND id=11483;
UPDATE creature SET curhealth=5072 WHERE guid=154185 AND id=11483;
UPDATE creature SET curhealth=5284 WHERE guid=154186 AND id=11483;
UPDATE creature SET curhealth=1135 WHERE guid=154188 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154189 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154190 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154191 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154192 AND id=11466;
UPDATE creature SET curhealth=1135 WHERE guid=154193 AND id=11466;
UPDATE creature SET curhealth=1336 WHERE guid=154199 AND id=11442;
UPDATE creature SET curhealth=14784 WHERE guid=154202 AND id=11450;
UPDATE creature SET curhealth=15352 WHERE guid=154203 AND id=11450;
UPDATE creature SET curhealth=1336 WHERE guid=154206 AND id=11442;
UPDATE creature SET curhealth=185 WHERE guid=154208 AND id=11446;
UPDATE creature SET curhealth=15352 WHERE guid=154210 AND id=14351;
UPDATE creature SET curhealth=14784 WHERE guid=154211 AND id=11450;
UPDATE creature SET curhealth=10352 WHERE guid=154212 AND id=11444;
UPDATE creature SET curhealth=13815 WHERE guid=154213 AND id=11445;
UPDATE creature SET curhealth=14784 WHERE guid=154214 AND id=11441;
UPDATE creature SET curhealth=185 WHERE guid=154215 AND id=11446;
UPDATE creature SET curhealth=14784 WHERE guid=154218 AND id=11450;
UPDATE creature SET curhealth=15352 WHERE guid=154220 AND id=14351;
UPDATE creature SET curhealth=14256 WHERE guid=154221 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154222 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154223 AND id=11441;
UPDATE creature SET curhealth=14256 WHERE guid=154224 AND id=11441;
UPDATE creature SET curhealth=13815 WHERE guid=154225 AND id=11445;
UPDATE creature SET curhealth=15352 WHERE guid=154227 AND id=14351;
UPDATE creature SET curhealth=15352 WHERE guid=154228 AND id=14351;
UPDATE creature SET curhealth=185 WHERE guid=154229 AND id=11446;
UPDATE creature SET curhealth=9976 WHERE guid=154230 AND id=11444;
UPDATE creature SET curhealth=185 WHERE guid=154232 AND id=11446;
UPDATE creature SET curhealth=185 WHERE guid=154233 AND id=11446;
UPDATE creature SET curhealth=1336 WHERE guid=154235 AND id=11442;
UPDATE creature SET curhealth=1336 WHERE guid=154236 AND id=11442;
UPDATE creature SET curhealth=1336 WHERE guid=154237 AND id=11442;
UPDATE creature SET curhealth=14256 WHERE guid=154238 AND id=11441;
UPDATE creature SET curhealth=14784 WHERE guid=154239 AND id=11441;
UPDATE creature SET curhealth=535 WHERE guid=154241 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154242 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154243 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154244 AND id=13160;
UPDATE creature SET curhealth=535 WHERE guid=154245 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154246 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154247 AND id=13160;
UPDATE creature SET curhealth=554 WHERE guid=154248 AND id=13160;
UPDATE creature SET curhealth=1782 WHERE guid=154249 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154250 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154251 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154252 AND id=13036;
UPDATE creature SET curhealth=1848 WHERE guid=154253 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154254 AND id=13036;
UPDATE creature SET curhealth=1782 WHERE guid=154255 AND id=13036;
UPDATE creature SET curhealth=12680 WHERE guid=154257 AND id=13285;
UPDATE creature SET curhealth=12192 WHERE guid=154258 AND id=13285;
UPDATE creature SET curhealth=9440 WHERE guid=154261 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154262 AND id=13197;
UPDATE creature SET curhealth=1002 WHERE guid=154263 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154264 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154265 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154266 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154267 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154268 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154269 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154270 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154271 AND id=13022;
UPDATE creature SET curhealth=9440 WHERE guid=154273 AND id=13197;
UPDATE creature SET curhealth=12680 WHERE guid=154274 AND id=13285;
UPDATE creature SET curhealth=12680 WHERE guid=154275 AND id=13285;
UPDATE creature SET curhealth=9440 WHERE guid=154276 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154277 AND id=13197;
UPDATE creature SET curhealth=1002 WHERE guid=154278 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154279 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154280 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154281 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154282 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154283 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154284 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154285 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154286 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154287 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154288 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154289 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154290 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154291 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154292 AND id=13022;
UPDATE creature SET curhealth=1002 WHERE guid=154293 AND id=13022;
UPDATE creature SET curhealth=12680 WHERE guid=154294 AND id=13285;
UPDATE creature SET curhealth=12680 WHERE guid=154295 AND id=13285;
UPDATE creature SET curhealth=5072 WHERE guid=154297 AND id=11461;
UPDATE creature SET curhealth=4904 WHERE guid=154298 AND id=11461;
UPDATE creature SET curhealth=4904 WHERE guid=154299 AND id=11461;
UPDATE creature SET curhealth=5072 WHERE guid=154300 AND id=11461;
UPDATE creature SET curhealth=5072 WHERE guid=154301 AND id=11461;
UPDATE creature SET curhealth=12192 WHERE guid=154302 AND id=13285;
UPDATE creature SET curhealth=9440 WHERE guid=154304 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154305 AND id=11456;
UPDATE creature SET curhealth=5836 WHERE guid=154308 AND id=11456;
UPDATE creature SET curhealth=9440 WHERE guid=154309 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154310 AND id=13197;
UPDATE creature SET curhealth=6096 WHERE guid=154312 AND id=11452;
UPDATE creature SET curhealth=4720 WHERE guid=154314 AND id=11453;
UPDATE creature SET curhealth=9440 WHERE guid=154315 AND id=13197;
UPDATE creature SET curhealth=6096 WHERE guid=154318 AND id=11452;
UPDATE creature SET curhealth=4904 WHERE guid=154319 AND id=11453;
UPDATE creature SET curhealth=11160 WHERE guid=154320 AND id=13196;
UPDATE creature SET curhealth=9440 WHERE guid=154321 AND id=13197;
UPDATE creature SET curhealth=4904 WHERE guid=154322 AND id=11453;
UPDATE creature SET curhealth=5836 WHERE guid=154323 AND id=11452;
UPDATE creature SET curhealth=5836 WHERE guid=154324 AND id=11452;
UPDATE creature SET curhealth=6096 WHERE guid=154325 AND id=11452;
UPDATE creature SET curhealth=4904 WHERE guid=154326 AND id=11453;
UPDATE creature SET curhealth=4904 WHERE guid=154327 AND id=11453;
UPDATE creature SET curhealth=5836 WHERE guid=154328 AND id=11456;
UPDATE creature SET curhealth=5836 WHERE guid=154329 AND id=11454;
UPDATE creature SET curhealth=4016 WHERE guid=154330 AND id=11455;
UPDATE creature SET curhealth=10688 WHERE guid=154332 AND id=13196;
UPDATE creature SET curhealth=5836 WHERE guid=154333 AND id=11451;
UPDATE creature SET curhealth=4016 WHERE guid=154334 AND id=11455;
UPDATE creature SET curhealth=5836 WHERE guid=154335 AND id=11454;
UPDATE creature SET curhealth=5836 WHERE guid=154336 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154337 AND id=11456;
UPDATE creature SET curhealth=4720 WHERE guid=154338 AND id=11457;
UPDATE creature SET curhealth=1459 WHERE guid=154339 AND id=13276;
UPDATE creature SET curhealth=5836 WHERE guid=154340 AND id=11451;
UPDATE creature SET curhealth=11160 WHERE guid=154341 AND id=13196;
UPDATE creature SET curhealth=9440 WHERE guid=154342 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154343 AND id=11451;
UPDATE creature SET curhealth=4016 WHERE guid=154344 AND id=11455;
UPDATE creature SET curhealth=5836 WHERE guid=154345 AND id=11454;
UPDATE creature SET curhealth=5580 WHERE guid=154346 AND id=11451;
UPDATE creature SET curhealth=4160 WHERE guid=154347 AND id=11455;
UPDATE creature SET curhealth=11160 WHERE guid=154348 AND id=13196;
UPDATE creature SET curhealth=4016 WHERE guid=154349 AND id=11455;
UPDATE creature SET curhealth=5836 WHERE guid=154350 AND id=11456;
UPDATE creature SET curhealth=9440 WHERE guid=154351 AND id=13197;
UPDATE creature SET curhealth=5836 WHERE guid=154352 AND id=11456;
UPDATE creature SET curhealth=11160 WHERE guid=154353 AND id=13196;
UPDATE creature SET curhealth=4904 WHERE guid=154354 AND id=11457;
UPDATE creature SET curhealth=5836 WHERE guid=154355 AND id=11456;
UPDATE creature SET curhealth=4016 WHERE guid=154356 AND id=11455;
UPDATE creature SET curhealth=5580 WHERE guid=154357 AND id=11451;
UPDATE creature SET curhealth=5580 WHERE guid=154358 AND id=11454;
UPDATE creature SET curhealth=5580 WHERE guid=154359 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154360 AND id=11456;
UPDATE creature SET curhealth=5580 WHERE guid=154361 AND id=11451;
UPDATE creature SET curhealth=5836 WHERE guid=154362 AND id=11451;
UPDATE creature SET curhealth=5580 WHERE guid=154363 AND id=11454;
UPDATE creature SET curhealth=9440 WHERE guid=154364 AND id=13197;
UPDATE creature SET curhealth=9440 WHERE guid=154365 AND id=13197;
UPDATE creature SET curhealth=6340 WHERE guid=154371 AND id=11475;
UPDATE creature SET curhealth=5284 WHERE guid=154372 AND id=11473;
UPDATE creature SET curhealth=1135 WHERE guid=154374 AND id=11466;
UPDATE creature SET curhealth=4720 WHERE guid=154385 AND id=11457;
UPDATE creature SET curhealth=1459 WHERE guid=154386 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154387 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154388 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154389 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154390 AND id=13276;
UPDATE creature SET curhealth=1459 WHERE guid=154391 AND id=13276;
UPDATE creature SET curhealth=42 WHERE guid=154400 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154401 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154402 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154403 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154408 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154409 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154410 AND id=14366;
UPDATE creature SET curhealth=42 WHERE guid=154411 AND id=14366;
UPDATE creature SET curhealth=1098 WHERE guid=154418 AND id=14400;
UPDATE creature SET curhealth=1057 WHERE guid=154419 AND id=14400;
UPDATE creature SET curhealth=42 WHERE guid=154420 AND id=14366;
UPDATE creature SET curhealth=10984 WHERE guid=154435 AND id=11484;
UPDATE creature SET curhealth=10984 WHERE guid=154437 AND id=14399;
UPDATE creature SET curhealth=10984 WHERE guid=154439 AND id=14399;
UPDATE creature SET curhealth=10984 WHERE guid=154440 AND id=11484;
UPDATE creature SET curhealth=305 WHERE guid=154441 AND id=14370;
UPDATE creature SET curhealth=10568 WHERE guid=154444 AND id=11484;
UPDATE creature SET curhealth=10984 WHERE guid=154445 AND id=14399;
UPDATE creature SET curhealth=365 WHERE guid=154446 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154447 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154448 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154449 AND id=11460;
UPDATE creature SET curhealth=152 WHERE guid=154450 AND id=14370;
UPDATE creature SET curhealth=10984 WHERE guid=154451 AND id=11484;
UPDATE creature SET curhealth=10984 WHERE guid=154452 AND id=11484;
UPDATE creature SET curhealth=152 WHERE guid=154453 AND id=14370;
UPDATE creature SET curhealth=365 WHERE guid=154454 AND id=11460;
UPDATE creature SET curhealth=365 WHERE guid=154455 AND id=11460;
UPDATE creature SET curhealth=152 WHERE guid=154456 AND id=14370;
UPDATE creature SET curhealth=365 WHERE guid=154457 AND id=11460;
UPDATE creature SET curhealth=970 WHERE guid=154474 AND id=44992;




