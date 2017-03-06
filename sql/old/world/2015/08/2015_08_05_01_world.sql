
delete from game_graveyard_zone where id=109 and ghost_zone=33;

UPDATE creature_template SET lootid=0 WHERE entry=57160;

delete from gameobject_loot_template where entry=205828;
insert into gameobject_loot_template values
(205828, 61373, -100, 1, 0, 1, 1);

UPDATE creature_template SET lootid=0 WHERE entry=5524;

delete from creature_questender where id = 11520;

update item_template set spellid_1=78866, spellcharges_1=-1 where entry=54464;

delete from player_factionchange_items where alliance_id=90897;

update waypoint_scripts set dataint=6405 where id=313;
update waypoint_scripts set dataint=10158 where id=314;
update waypoint_scripts set dataint=22544 where id=315;
update waypoint_scripts set dataint=10146 where id=317;
update waypoint_scripts set dataint=12835 where id=318;
update waypoint_scripts set dataint=12832 where id=319;
update waypoint_scripts set dataint=12833 where id=320;
update waypoint_scripts set dataint=14565 where id=322;
update waypoint_scripts set dataint=14567 where id=324;
update waypoint_scripts set dataint=15144 where id=325;
update waypoint_scripts set dataint=15373 where id=326;
update waypoint_scripts set dataint=30492 where id=329;
update waypoint_scripts set dataint=977 where id=330;  -- wrong.. 
update waypoint_scripts set dataint=16059 where id=331;
update waypoint_scripts set dataint=16977 where id=332;
update waypoint_scripts set dataint=16974 where id=333;
update waypoint_scripts set dataint=209 where id=385;
update waypoint_scripts set dataint=224 where id=386;
update waypoint_scripts set dataint=225 where id=387;
update waypoint_scripts set dataint=213 where id=388;
update waypoint_scripts set dataint=225 where id=389;
update waypoint_scripts set dataint=225 where id=390;
update waypoint_scripts set dataint=224 where id=391;
update waypoint_scripts set dataint=214 where id=392;
update waypoint_scripts set dataint=217 where id=393;
update waypoint_scripts set dataint=210 where id=394;
update waypoint_scripts set dataint=205 where id=395;
update waypoint_scripts set dataint=216 where id=397;
update waypoint_scripts set dataint=212 where id=399;
update waypoint_scripts set dataint=208 where id=401;
update waypoint_scripts set dataint=214 where id=403;
update waypoint_scripts set dataint=215 where id=405;
update waypoint_scripts set dataint=206 where id=407;
update waypoint_scripts set dataint=212 where id=409;
update waypoint_scripts set dataint=214 where id=411;
update waypoint_scripts set dataint=1153 where id=413;
update waypoint_scripts set dataint=1130 where id=414;
update waypoint_scripts set dataint=201 where id=416;
update waypoint_scripts set dataint=218 where id=417;
update waypoint_scripts set dataint=222 where id=418;
update waypoint_scripts set dataint=221 where id=419;
update waypoint_scripts set dataint=204 where id=420;
update waypoint_scripts set dataint=222 where id=421;
update waypoint_scripts set dataint=219 where id=422;
update waypoint_scripts set dataint=218 where id=423;
update waypoint_scripts set dataint=221 where id=424;
update waypoint_scripts set dataint=219 where id=425;
update waypoint_scripts set dataint=222 where id=426;
update waypoint_scripts set dataint=587 where id=427;
update waypoint_scripts set dataint=589 where id=428;
update waypoint_scripts set dataint=590 where id=429;
update waypoint_scripts set dataint=588 where id=430;
update waypoint_scripts set dataint=1091 where id=431;
update waypoint_scripts set dataint=1197 where id=432;
update waypoint_scripts set dataint=1195 where id=433;
update waypoint_scripts set dataint=1194 where id=434;
update waypoint_scripts set dataint=1199 where id=435;
update waypoint_scripts set dataint=1195 where id=436;
update waypoint_scripts set dataint=1197 where id=437;
update waypoint_scripts set dataint=1192 where id=438;
update waypoint_scripts set dataint=1194 where id=439;
update waypoint_scripts set dataint=1193 where id=440;
update waypoint_scripts set dataint=1199 where id=441;
update waypoint_scripts set dataint=1197 where id=442;
update waypoint_scripts set dataint=1195 where id=443;
update waypoint_scripts set dataint=1192 where id=444;
update waypoint_scripts set dataint=1194 where id=445;
update waypoint_scripts set dataint=1195 where id=446;
update waypoint_scripts set dataint=24425 where id=447;
update waypoint_scripts set dataint=24425 where id=449;
update waypoint_scripts set dataint=22216 where id=451;
update waypoint_scripts set dataint=22211 where id=452;
update waypoint_scripts set dataint=22206 where id=453;
update waypoint_scripts set dataint=25086 where id=455;
update waypoint_scripts set dataint=25073 where id=456;
update waypoint_scripts set dataint=25074 where id=457;
update waypoint_scripts set dataint=25075 where id=458;
update waypoint_scripts set dataint=25076 where id=459;
update waypoint_scripts set dataint=23842 where id=463;
update waypoint_scripts set dataint=328 where id=1000;
update waypoint_scripts set dataint=327 where id=1001;
update waypoint_scripts set dataint=5956 where id=1002;
update waypoint_scripts set dataint=5957 where id=1003;
update waypoint_scripts set dataint=5960 where id=1004;
update waypoint_scripts set dataint=5959 where id=1005;
update waypoint_scripts set dataint=24439 where id=1120;
update waypoint_scripts set dataint=24443 where id=1121;










