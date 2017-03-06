

delete from gossip_menu_option where menu_id=0 and id=18;

delete from creature where id in (44899, 1950, 1951);

UPDATE locales_quest SET OfferRewardText_loc3="Oh je, arme Yorick! Ich kannte sie gut, $N. Eine Assassine mit unvergleichbarem Mut…$B$BAlso, was geht dort vor sich? Was habt Yorick und Ihr herausgefunden?", QuestGiverTextWindow_loc3="Todespirscherin Rane Yorick", QuestGiverTargetName_loc3="Rane Yorick" WHERE Id=27045;

update gameobject_template set AIName="", ScriptName="go_abandoned_outhouse_205143" where entry=205143;

update creature_template set AIName="", ScriptName="npc_deathstalker_rane_yorick_44882" where entry=44882;

update creature_template_addon set auras="" where entry=44882;

DELETE FROM creature_addon WHERE guid=53623;

SET @PATHID=4488201;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID,  0, 1299.866, 1189.733, 52.11713, 2.450426, 0, 0),
(@PATHID,  1, 1290.530, 1196.473, 52.41762, 2.493623, 0, 0),
(@PATHID,  2, 1289.968, 1200.791, 52.65834, 1.700370, 0, 0),
(@PATHID,  3, 1290.122, 1205.708, 52.71643, 1.539364, 0, 0),
(@PATHID,  4, 1293.603, 1207.071, 53.53426, 0.373047, 0, 0),
(@PATHID,  5, 1299.119, 1207.071, 53.74656, 0.325923, 0, 0),
(@PATHID,  6, 1303.736, 1210.398, 53.74656, 0.930680, 0, 0),
(@PATHID,  7, 1304.215, 1212.665, 53.74656, 1.362649, 0, 0),
(@PATHID,  8, 1303.619, 1219.871, 53.74656, 1.653246, 0, 0),
(@PATHID,  9, 1300.441, 1222.615, 53.74656, 2.438645, 0, 0),
(@PATHID, 10, 1297.949, 1220.368, 53.74656, 3.942683, 0, 0),
(@PATHID, 11, 1297.620, 1212.439, 58.48082, 4.068350, 0, 0),
(@PATHID, 12, 1297.639, 1210.122, 58.47509, 4.720230, 0, 0),
(@PATHID, 13, 1301.660, 1206.269, 58.49411, 5.537040, 0, 0),
(@PATHID, 14, 1311.437, 1206.490, 58.51025, 6.259605, 0, 0),
(@PATHID, 15, 1312.644, 1208.443, 58.51212, 1.017072, 0, 0);

update creature_template set AIName="", ScriptName="npc_armoire_44893" where entry=44893;

update creature_template set AIName="", ScriptName="npc_armoire_44894" where entry=44894;

UPDATE creature_template SET unit_flags=8 WHERE entry=44893;

update creature_template_addon set bytes1=131072 where entry=44893;

SET @PATHID=4488301;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, 1299.36, 1206.64, 58.5706, 0, 0, 0),
(@PATHID, 1, 1300.36, 1206.64, 58.5706, 0, 0, 0),
(@PATHID, 2, 1302.33, 1206.44, 58.4990, 0, 0, 0),
(@PATHID, 3, 1305.32, 1206.43, 58.5126, 0, 0, 0),
(@PATHID, 4, 1313.48, 1206.09, 58.5119, 0, 0, 0),
(@PATHID, 5, 1313.48, 1206.09, 58.5119, 0, 0, 0);

SET @PATHID=4488401;
DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay, move_flag) values
(@PATHID, 0, 1296.20, 1210.54, 58.5533, 0, 0, 0),
(@PATHID, 1, 1297.20, 1210.54, 58.5533, 0, 0, 0),
(@PATHID, 2, 1302.31, 1206.61, 58.4984, 0, 0, 0),
(@PATHID, 3, 1308.40, 1206.28, 58.5109, 0, 0, 0),
(@PATHID, 4, 1308.40, 1206.28, 58.5109, 0, 0, 0);

update creature_text set comment="", BroadcastTextID=44957 where entry=44883 and groupid=0 and id=0;
update creature_text set comment="", BroadcastTextID=44960 where entry=44883 and groupid=1 and id=0;
update creature_text set comment="", BroadcastTextID=44961 where entry=44883 and groupid=2 and id=0;
update creature_text set comment="", BroadcastTextID=44965 where entry=44883 and groupid=3 and id=0;

update creature_text set comment="", BroadcastTextID=44959 where entry=44884 and groupid=0 and id=0;
update creature_text set comment="", BroadcastTextID=44962 where entry=44884 and groupid=1 and id=0;
update creature_text set comment="", BroadcastTextID=44963 where entry=44884 and groupid=2 and id=0;
update creature_text set comment="", BroadcastTextID=44884 where entry=44884 and groupid=3 and id=0;
update creature_text set comment="", BroadcastTextID=44966 where entry=44884 and groupid=4 and id=0;
update creature_text set comment="", BroadcastTextID=44967 where entry=44884 and groupid=5 and id=0;
update creature_text set comment="", BroadcastTextID=44968 where entry=44884 and groupid=6 and id=0;
update creature_text set comment="", BroadcastTextID=44969 where entry=44884 and groupid=7 and id=0;

delete from creature_text where entry=44884 and groupid in (8, 9, 10);
insert into creature_text values 
(44884, 8, 0, "What say you now, spy?", 12, 0, 100, 0, 0, 0, "", 44970),
(44884, 9, 0, "I was hoping you'd say that...", 12, 0, 100, 0, 0, 0, "", 44972),
(44884, 10, 0, "I will prepare the pack. It will take some time to gather them all, but we will join... for now.", 12, 0, 100, 1, 0, 0, "", 44973);

UPDATE creature_template SET npcflag=16777216 WHERE entry=44894;

delete from npc_spellclick_spells where npc_entry=44894;
insert into npc_spellclick_spells values
(44894, 46598, 1, 0);

update creature_template set AIName="", ScriptName="npc_lord_darius_crowley_44883" where entry=44883;

update creature_template set AIName="", ScriptName="npc_packleader_ivar_bloodfang_44884" where entry=44884;



	

