
-- instance uldaman
-- dbc : instance with one difficulty and max 5 players. 

update creature_template set AIName="", ScriptName="boss_revelosh" where entry=6910;
update creature_template set AIName="", ScriptName="boss_baelog" where entry=6906;
update creature_template set AIName="", ScriptName="boss_eric_the_swift" where entry=6907;
update creature_template set AIName="", ScriptName="boss_olaf" where entry=6908;
update creature_template set AIName="", ScriptName="boss_ironaya" where entry=7228;
update creature_template set AIName="", ScriptName="boss_obsidian_sentinel" where entry=7023;
update creature_template set AIName="", ScriptName="boss_ancient_stone_keeper" where entry=7206;
update creature_template set AIName="", ScriptName="boss_galgann_firehammer" where entry=7291;
update creature_template set AIName="", ScriptName="boss_grimlok" where entry=4854;
update creature_template set AIName="", ScriptName="boss_archaedas" where entry=2748;

-- delete creatures in the mall.. are spawned from script..
delete from creature where guid between 147502 and 147507;
delete from creature where id in (46231, 46232);

delete from gameobject where id in (205969, 205970);

delete from gameobject where guid=20919 and id=124372;

update creature_template_addon set bytes1=0 where entry=46236;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gut gemacht! Grabstelle Drei und die Geheimnisse hinter dieser Tür werden bald uns und nur uns gehören.", CompletedText_loc3="Kehrt zu Lidia Sonnenglanz zurück.", QuestGiverTextWindow_loc3="Galgann Feuerhammer", QuestGiverTargetName_loc3="Galgann Feuerhammer" WHERE Id=27681;
UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27676;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Olga Runenschwur zurück.", QuestGiverTextWindow_loc3="Galgann Feuerhammer", QuestGiverTargetName_loc3="Galgann Feuerhammer" WHERE Id=27676;

UPDATE quest_template SET RequiredRaces=2098253 WHERE Id=27672;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Oberausgrabungsleiter Durdin zurück." WHERE Id=27672;
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zum Obersten Prüfer Tae'thelan Blutwächter zurück." WHERE Id=27679;

update creature set spawntimesecs=86400 where map=70;

-- now create all groups

DELETE FROM pool_template WHERE entry=1077;
INSERT INTO pool_template VALUES (1077,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1132;
INSERT INTO pool_template VALUES (1132,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1132 and mother_pool=1077;
INSERT INTO pool_pool VALUES (1132, 1077, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147397;
INSERT INTO pool_creature VALUES (147397,1132,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147170;
INSERT INTO pool_creature VALUES (147170,1132,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147285;
INSERT INTO pool_creature VALUES (147285,1132,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147302;
INSERT INTO pool_creature VALUES (147302,1132,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147173;
INSERT INTO pool_creature VALUES (147173,1132,0,"Stonevault Oracle");

--

DELETE FROM pool_template WHERE entry=1133;
INSERT INTO pool_template VALUES (1133,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1227;
INSERT INTO pool_template VALUES (1227,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1227 and mother_pool=1133;
INSERT INTO pool_pool VALUES (1227, 1133, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147361;
INSERT INTO pool_creature VALUES (147361,1227,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147362;
INSERT INTO pool_creature VALUES (147362,1227,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147395;
INSERT INTO pool_creature VALUES (147395,1227,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147289;
INSERT INTO pool_creature VALUES (147289,1227,0,"Stonevault Pillager");

--

DELETE FROM pool_template WHERE entry=1228;
INSERT INTO pool_template VALUES (1228,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1230;
INSERT INTO pool_template VALUES (1230,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1230 and mother_pool=1228;
INSERT INTO pool_pool VALUES (1230, 1228, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147167;
INSERT INTO pool_creature VALUES (147167,1230,0,"Stonevault Ambusher");

DELETE FROM pool_creature WHERE guid=147178;
INSERT INTO pool_creature VALUES (147178,1230,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147286;
INSERT INTO pool_creature VALUES (147286,1230,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147363;
INSERT INTO pool_creature VALUES (147363,1230,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=1229;
INSERT INTO pool_template VALUES (1229,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1231;
INSERT INTO pool_template VALUES (1231,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1231 and mother_pool=1229;
INSERT INTO pool_pool VALUES (1231, 1229, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147401;
INSERT INTO pool_creature VALUES (147401,1231,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147300;
INSERT INTO pool_creature VALUES (147300,1231,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147399;
INSERT INTO pool_creature VALUES (147399,1231,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147394;
INSERT INTO pool_creature VALUES (147394,1231,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147398;
INSERT INTO pool_creature VALUES (147398,1231,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=1232;
INSERT INTO pool_template VALUES (1232,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1233;
INSERT INTO pool_template VALUES (1233,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1233 and mother_pool=1232;
INSERT INTO pool_pool VALUES (1233, 1232, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147298;
INSERT INTO pool_creature VALUES (147298,1233,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147171;
INSERT INTO pool_creature VALUES (147171,1233,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147174;
INSERT INTO pool_creature VALUES (147174,1233,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=1234;
INSERT INTO pool_template VALUES (1234,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1235;
INSERT INTO pool_template VALUES (1235,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1235 and mother_pool=1234;
INSERT INTO pool_pool VALUES (1235, 1234, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147393;
INSERT INTO pool_creature VALUES (147393,1235,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147364;
INSERT INTO pool_creature VALUES (147364,1235,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147371;
INSERT INTO pool_creature VALUES (147371,1235,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=1236;
INSERT INTO pool_template VALUES (1236,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=1237;
INSERT INTO pool_template VALUES (1237,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=1237 and mother_pool=1236;
INSERT INTO pool_pool VALUES (1237, 1236, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147301;
INSERT INTO pool_creature VALUES (147301,1237,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147175;
INSERT INTO pool_creature VALUES (147175,1237,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147288;
INSERT INTO pool_creature VALUES (147288,1237,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147284;
INSERT INTO pool_creature VALUES (147284,1237,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147287;
INSERT INTO pool_creature VALUES (147287,1237,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147392;
INSERT INTO pool_creature VALUES (147392,1237,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=1241;
INSERT INTO pool_template VALUES (1241,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=2686;
INSERT INTO pool_template VALUES (2686,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=2686 and mother_pool=1241;
INSERT INTO pool_pool VALUES (2686, 1241, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147435;
INSERT INTO pool_creature VALUES (147435,2686,0,"Stonevault Cave Lurker");

DELETE FROM pool_creature WHERE guid=147428;
INSERT INTO pool_creature VALUES (147428,2686,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147432;
INSERT INTO pool_creature VALUES (147432,2686,0,"Stonevault Cave Lurker");

--

DELETE FROM pool_template WHERE entry=8068;
INSERT INTO pool_template VALUES (8068,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=8777;
INSERT INTO pool_template VALUES (8777,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=8777 and mother_pool=8068;
INSERT INTO pool_pool VALUES (8777, 8068, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147366;
INSERT INTO pool_creature VALUES (147366,8777,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147396;
INSERT INTO pool_creature VALUES (147396,8777,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147297;
INSERT INTO pool_creature VALUES (147297,8777,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147177;
INSERT INTO pool_creature VALUES (147177,8777,0,"Stonevault Rockchewer");

--

DELETE FROM pool_template WHERE entry=9867;
INSERT INTO pool_template VALUES (9867,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=10796;
INSERT INTO pool_template VALUES (10796,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=10796 and mother_pool=9867;
INSERT INTO pool_pool VALUES (10796, 9867, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147299;
INSERT INTO pool_creature VALUES (147299,10796,0,"Stonevault Pillager");

DELETE FROM pool_creature WHERE guid=147365;
INSERT INTO pool_creature VALUES (147365,10796,0,"Stonevault Rockchewer");

DELETE FROM pool_creature WHERE guid=147172;
INSERT INTO pool_creature VALUES (147172,10796,0,"Stonevault Oracle");

DELETE FROM pool_creature WHERE guid=147168;
INSERT INTO pool_creature VALUES (147168,10796,0,"Stonevault Ambusher");

--

DELETE FROM pool_template WHERE entry=12026;
INSERT INTO pool_template VALUES (12026,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=12216;
INSERT INTO pool_template VALUES (12216,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=12216 and mother_pool=12026;
INSERT INTO pool_pool VALUES (12216, 12026, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147417;
INSERT INTO pool_creature VALUES (147417,12216,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147416;
INSERT INTO pool_creature VALUES (147416,12216,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147253;
INSERT INTO pool_creature VALUES (147253,12216,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147415;
INSERT INTO pool_creature VALUES (147415,12216,0,"Stonevault Geomancer");

--

DELETE FROM pool_template WHERE entry=12308;
INSERT INTO pool_template VALUES (12308,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=13671;
INSERT INTO pool_template VALUES (13671,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=13671 and mother_pool=12308;
INSERT INTO pool_pool VALUES (13671, 12308, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147414;
INSERT INTO pool_creature VALUES (147414,13671,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147410;
INSERT INTO pool_creature VALUES (147410,13671,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147409;
INSERT INTO pool_creature VALUES (147409,13671,0,"Stonevault Geomancer");

--

DELETE FROM pool_template WHERE entry=13672;
INSERT INTO pool_template VALUES (13672,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=13673;
INSERT INTO pool_template VALUES (13673,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=13673 and mother_pool=13672;
INSERT INTO pool_pool VALUES (13673, 13672, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147407;
INSERT INTO pool_creature VALUES (147407,13673,0,"Stonevault Geomancer");

DELETE FROM pool_creature WHERE guid=147408;
INSERT INTO pool_creature VALUES (147408,13673,0,"Stonevault Brawler");

DELETE FROM pool_creature WHERE guid=147162;
INSERT INTO pool_creature VALUES (147162,13673,0,"Stonevault Geomancer");

DELETE FROM pool_creature WHERE guid=147163;
INSERT INTO pool_creature VALUES (147163,13673,0,"Stonevault Brawler");

--

DELETE FROM pool_template WHERE entry=14135;
INSERT INTO pool_template VALUES (14135,3,"MP Stonevault");

DELETE FROM pool_template WHERE entry=14136;
INSERT INTO pool_template VALUES (14136,3,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=14136 and mother_pool=14135;
INSERT INTO pool_pool VALUES (14136, 14135, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147271;
INSERT INTO pool_creature VALUES (147271,14136,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147272;
INSERT INTO pool_creature VALUES (147272,14136,0,"Stonevault Flameweaver");

DELETE FROM pool_creature WHERE guid=147413;
INSERT INTO pool_creature VALUES (147413,14136,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147268;
INSERT INTO pool_creature VALUES (147268,14136,0,"Stonevault Flameweaver");

DELETE FROM pool_creature WHERE guid=147267;
INSERT INTO pool_creature VALUES (147267,14136,0,"Stonevault Mauler");

--

DELETE FROM pool_template WHERE entry=14137;
INSERT INTO pool_template VALUES (14137,2,"MP Stonevault");

DELETE FROM pool_template WHERE entry=14138;
INSERT INTO pool_template VALUES (14138,2,"PP Stonevault");

DELETE FROM pool_pool WHERE pool_id=14138 and mother_pool=14137;
INSERT INTO pool_pool VALUES (14138, 14137, 0, "Stonevault");

DELETE FROM pool_creature WHERE guid=147265;
INSERT INTO pool_creature VALUES (147265,14138,0,"Stonevault Flameweaver");

DELETE FROM pool_creature WHERE guid=147264;
INSERT INTO pool_creature VALUES (147264,14138,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147263;
INSERT INTO pool_creature VALUES (147263,14138,0,"Stonevault Mauler");

DELETE FROM pool_creature WHERE guid=147266;
INSERT INTO pool_creature VALUES (147266,14138,0,"Stonevault Flameweaver");

--





