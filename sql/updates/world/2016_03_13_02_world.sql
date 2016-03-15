
update creature set id=36698, phaseMask=28672 where id=56000 and guid =250012;

update npc_text set BroadcastTextID0=36636 where ID=15035;

update gossip_menu_option set OptionBroadcastTextID=2823, option_id=3, npc_option_npcflag=128 where menu_id=10842 and id=0;

SET @GUID=251980;
UPDATE creature SET spawndist=0, MovementType = 2 WHERE guid=@GUID;

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@GUID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@GUID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@GUID, 0, -1873.832, 2256.51, 42.32388, 2.350769, 0),
(@GUID, 1, -1865.808, 2247.833, 42.32388, 5.578752, 0),
(@GUID, 2, -1862.833, 2248.039, 42.32388, 0.069182, 5000),
(@GUID, 3, -1882.611, 2224.727, 42.32388, 3.901927, 0),
(@GUID, 4, -1898.322, 2236.381, 42.32388, 2.303642, 0),
(@GUID, 5, -1903.037, 2245.846, 42.32388, 1.44363, 5000),
(@GUID, 6, -1888.325, 2259.584, 42.32388, 0.693575, 5000),
(@GUID, 7, -1878.302, 2260.22, 42.32388, 6.230632, 0);

update npc_text set BroadcastTextID0=36605 where ID=15028;

delete from gossip_menu_option where menu_id=10371;
insert into gossip_menu_option values 
(10371, 0, 0, "Purchase a Dual Talent Specialization.", 33765, 18, 16, 0, 0, 0, 0, 100000, "Are you sure you wish to purchase a Dual Talent Specialization?", 0);

delete from gossip_menu_option where menu_id=10834;
insert into gossip_menu_option values 
(10834, 0, 3, "I seek training as a druid.", 8295, 5, 16, 0, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=10835;
insert into gossip_menu_option values 
(10835, 0, 3, "I seek training in the ways of the Hunter.", 7643, 5, 16, 0, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=10836;
insert into gossip_menu_option values 
(10836, 0, 3, "I require warrior training.", 3147, 5, 16, 0, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=10837;
insert into gossip_menu_option values 
(10837, 0, 3, "I am interested in mage training.", 2522, 5, 16, 0, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=10838;
insert into gossip_menu_option values 
(10838, 0, 3, "I require priest training.", 7169, 5, 16, 0, 0, 0, 0, 0, "", 0);

update creature_template set gossip_menu_id=10702 where entry=36652;

update creature_template set gossip_menu_id=10699 where entry=36630;

delete from gossip_menu_option where menu_id=15000;
delete from gossip_menu_option where menu_id=15001;

update gossip_menu_option set OptionBroadcastTextID=44403, option_id=3, npc_option_npcflag=128 where menu_id=11794 and id=0;
update gossip_menu_option set OptionBroadcastTextID=44404, option_id=3, npc_option_npcflag=128 where menu_id=11794 and id=1;

update npc_text set BroadcastTextID0=23856 where ID=12189;
update npc_text set BroadcastTextID0=32674 where ID=14108;

update npc_text set BroadcastTextID0=32548 where ID=14083;
update npc_text set BroadcastTextID0=32550 where ID=14084;
update npc_text set BroadcastTextID0=32551 where ID=14085;
update npc_text set BroadcastTextID0=32552 where ID=14086;

update npc_text set BroadcastTextID0=47108 where ID=17126;
update npc_text set BroadcastTextID0=47129 where ID=17127;
update npc_text set BroadcastTextID0=47130 where ID=17128;
update npc_text set BroadcastTextID0=47131 where ID=17129;
update npc_text set BroadcastTextID0=47132 where ID=17130;
update npc_text set BroadcastTextID0=47133 where ID=17131;
update npc_text set BroadcastTextID0=47134 where ID=17132;
update npc_text set BroadcastTextID0=47136 where ID=17133;
update npc_text set BroadcastTextID0=47137 where ID=17134;
update npc_text set BroadcastTextID0=47138 where ID=17135;
update npc_text set BroadcastTextID0=47139 where ID=17136;
update npc_text set BroadcastTextID0=47140 where ID=17137;
update npc_text set BroadcastTextID0=47141 where ID=17138;

update npc_text set BroadcastTextID1=47181 where ID=17143;
update npc_text set BroadcastTextID2=47182 where ID=17143;
update npc_text set BroadcastTextID3=47183 where ID=17143;
update npc_text set BroadcastTextID4=47184 where ID=17143;
update npc_text set BroadcastTextID4=47185 where ID=17143;
update npc_text set BroadcastTextID4=47186 where ID=17143;
update npc_text set BroadcastTextID4=47187 where ID=17143;

delete from gossip_menu_option where menu_id=12180;
insert into gossip_menu_option values 
(12180, 0, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 2, 3, "Train me in Skinning.", 47117, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 3, 3, "Train me in Alchemy.", 47109, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 4, 3, "Train me in Blacksmithing.", 47110, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 5, 3, "Train me in Enchanting.", 47111, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 6, 3, "Train me in Engineering.", 47119, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 7, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 8, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 9, 3, "Train me in Leatherworking.", 47115, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 10, 3, "Train me in Tailoring.", 47118, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12180, 11, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12180, 12, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12185;
insert into gossip_menu_option values 
(12185, 0, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 2, 3, "Train me in Skinning.", 47117, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 3, 3, "Train me in Alchemy.", 47109, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 4, 3, "Train me in Blacksmithing.", 47110, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 5, 3, "Train me in Enchanting.", 47111, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 6, 3, "Train me in Engineering.", 47119, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 7, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 8, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 9, 3, "Train me in Leatherworking.", 47115, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 10, 3, "Train me in Tailoring.", 47118, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12185, 11, 0, "Tell me about Herbalism.", 47142, 1, 1, 12188, 0, 0, 0, 0, "", 0),
(12185, 12, 0, "Tell me about Mining.", 47143, 1, 1, 12189, 0, 0, 0, 0, "", 0),
(12185, 13, 0, "Tell me about Skinning.", 47144, 1, 1, 12190, 0, 0, 0, 0, "", 0),
(12185, 14, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12186;
insert into gossip_menu_option values 
(12186, 0, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 2, 3, "Train me in Skinning.", 47117, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 3, 3, "Train me in Alchemy.", 47109, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 4, 3, "Train me in Blacksmithing.", 47110, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 5, 3, "Train me in Enchanting.", 47111, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 6, 3, "Train me in Engineering.", 47119, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 7, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 8, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 9, 3, "Train me in Leatherworking.", 47115, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 10, 3, "Train me in Tailoring.", 47118, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12186, 11, 0, "Tell me about Alchemy.", 47145, 1, 1, 12191, 0, 0, 0, 0, "", 0),
(12186, 12, 0, "Tell me about Blacksmithing.", 47146, 1, 1, 12192, 0, 0, 0, 0, "", 0),
(12186, 13, 0, "Tell me about Enchanting.", 47147, 1, 1, 12193, 0, 0, 0, 0, "", 0),
(12186, 14, 0, "Tell me about Engineering.", 47148, 1, 1, 12195, 0, 0, 0, 0, "", 0),
(12186, 15, 0, "Tell me about Inscription.", 47149, 1, 1, 12196, 0, 0, 0, 0, "", 0),
(12186, 16, 0, "Tell me about Jewelcrafting.", 47150, 1, 1, 12197, 0, 0, 0, 0, "", 0),
(12186, 17, 0, "Tell me about Leatherworking.", 47151, 1, 1, 12198, 0, 0, 0, 0, "", 0),
(12186, 18, 0, "Tell me about Tailoring.", 47152, 1, 1, 12199, 0, 0, 0, 0, "", 0),
(12186, 19, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12188;
insert into gossip_menu_option values 
(12188, 0, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12188, 1, 3, "Train me in Alchemy.", 47109, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12188, 2, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12188, 3, 0, "Tell me about Alchemy.", 47145, 1, 1, 12191, 0, 0, 0, 0, "", 0),
(12188, 4, 0, "Tell me about Inscription.", 47149, 1, 1, 12196, 0, 0, 0, 0, "", 0),
(12188, 5, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12188, 6, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12189;
insert into gossip_menu_option values 
(12189, 0, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12189, 1, 3, "Train me in Blacksmithing.", 47110, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12189, 2, 3, "Train me in Engineering.", 47119, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12189, 3, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12189, 4, 0, "Tell me about Blacksmithing.", 47146, 1, 1, 12192, 0, 0, 0, 0, "", 0),
(12189, 5, 0, "Tell me about Engineering.", 47148, 1, 1, 12195, 0, 0, 0, 0, "", 0),
(12189, 6, 0, "Tell me about Jewelcrafting.", 47150, 1, 1, 12197, 0, 0, 0, 0, "", 0),
(12189, 7, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12189, 8, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12190;
insert into gossip_menu_option values 
(12190, 0, 3, "Train me in Skinning.", 47117, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12190, 1, 3, "Train me in Leatherworking.", 47115, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12190, 2, 0, "Tell me about Leatherworking.", 47151, 1, 1, 12198, 0, 0, 0, 0, "", 0),
(12190, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12190, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12191;
insert into gossip_menu_option values 
(12191, 0, 3, "Train me in Alchemy.", 47109, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12191, 1, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12191, 2, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12191, 3, 0, "Tell me about Herbalism.", 47142, 1, 1, 12188, 0, 0, 0, 0, "", 0),
(12191, 4, 0, "Tell me about Inscription.", 47149, 1, 1, 12196, 0, 0, 0, 0, "", 0),
(12191, 5, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12191, 6, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12192;
insert into gossip_menu_option values 
(12192, 0, 3, "Train me in Blacksmithing.", 47110, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12192, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12192, 2, 0, "Tell me about Mining.", 47143, 1, 1, 12189, 0, 0, 0, 0, "", 0),
(12192, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12192, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12193;
insert into gossip_menu_option values 
(12193, 0, 3, "Train me in Enchanting.", 47111, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12193, 1, 3, "Train me in Tailoring.", 47118, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12193, 2, 0, "Tell me about Tailoring.", 47152, 1, 1, 12199, 0, 0, 0, 0, "", 0),
(12193, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12193, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12195;
insert into gossip_menu_option values 
(12195, 0, 3, "Train me in Engineering.", 47119, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12195, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12195, 2, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12195, 3, 0, "Tell me about Mining.", 47143, 1, 1, 12189, 0, 0, 0, 0, "", 0),
(12195, 4, 0, "Tell me about Jewelcrafting.", 47150, 1, 1, 12197, 0, 0, 0, 0, "", 0),
(12195, 5, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12195, 6, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12196;
insert into gossip_menu_option values 
(12196, 0, 3, "Train me in Inscription.", 47113, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12196, 1, 3, "Train me in Herbalism.", 47112, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12196, 2, 0, "Tell me about Herbalism.", 47142, 1, 1, 12188, 0, 0, 0, 0, "", 0),
(12196, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12196, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12197;
insert into gossip_menu_option values 
(12197, 0, 3, "Train me in Jewelcrafting.", 47114, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12197, 1, 3, "Train me in Mining.", 47116, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12197, 2, 0, "Tell me about Mining.", 47143, 1, 1, 12189, 0, 0, 0, 0, "", 0),
(12197, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12197, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12198;
insert into gossip_menu_option values 
(12198, 0, 3, "Train me in Leatherworking.", 47115, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12198, 1, 3, "Train me in Skinning.", 47117, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12198, 2, 0, "Tell me about Skinning.", 47144, 1, 1, 12190, 0, 0, 0, 0, "", 0),
(12198, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12198, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

delete from gossip_menu_option where menu_id=12199;
insert into gossip_menu_option values 
(12199, 0, 3, "Train me in Tailoring.", 47118, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12199, 1, 3, "Train me in Enchanting.", 47111, 5, 16, 0, 0, 0, 0, 0, "", 0),
(12199, 2, 0, "Tell me about Enchanting.", 47147, 1, 1, 12193, 0, 0, 0, 0, "", 0),
(12199, 3, 0, "Tell me about gathering professions.", 47106, 1, 1, 12185, 0, 0, 0, 0, "", 0),
(12199, 4, 0, "Tell me about production professions.", 47107, 1, 1, 12186, 0, 0, 0, 0, "", 0);

update npc_text set BroadcastTextID0=47105 where ID=17125;

update gossip_menu_option set OptionBroadcastTextID=4510 where  menu_id=5853 and id=1;

update npc_text set text0_0="You need something, $C?", BroadcastTextID0=36606 where ID=15029;

update npc_text set BroadcastTextID0=36054 where ID=14831;

SET @GUID=252127;
SET @ENTRY=36602;
SET @PATHID=252127;

delete from creature where guid=@GUID;
INSERT INTO `creature` VALUES (@GUID, @ENTRY, 654, 1, 20480, 0, 0, -1806.5, 2291.601, 48.25063, 2.382172, 500, 0, 0, 42, 0, 2, 0, 0, 0);

INSERT IGNORE INTO creature_addon (guid) VALUE (@GUID);
UPDATE creature_addon SET path_id=@PATHID WHERE guid=@GUID;

DELETE FROM waypoint_data WHERE id=@PATHID;
INSERT INTO waypoint_data (id, point, position_x, position_y, position_z, orientation, delay) values
(@PATHID, 0, -1806.5, 2291.601, 48.25063, 2.382172, 5000),
(@PATHID, 1, -1804.486, 2289.956, 48.52819, 5.468789, 0),
(@PATHID, 2, -1815.737, 2278.424, 48.24928, 3.960826, 0),
(@PATHID, 3, -1823.972, 2276.357, 48.37102, 3.387485, 0),
(@PATHID, 4, -1824.599, 2279.243, 48.25063, 1.824542, 5000),
(@PATHID, 5, -1823.638, 2276.097, 48.25063, 5.009331, 0),
(@PATHID, 6, -1834.028, 2273.763, 48.53919, 3.367849, 0),
(@PATHID, 7, -1845.047, 2284.663, 49.01207, 2.390028, 0),
(@PATHID, 8, -1847.01, 2289.29, 49.23626, 2.091577, 0),
(@PATHID, 9, -1846.11, 2289.76, 49.27164, 0.48151, 5000),
(@PATHID, 10, -1847.557, 2288.813, 49.17143, 3.721278, 0),
(@PATHID, 11, -1841.554, 2283.02, 48.50987, 5.759384, 0),
(@PATHID, 12, -1840.617, 2284.294, 48.48009, 0.937039, 5000),
(@PATHID, 13, -1842.146, 2282.709, 48.4794, 4.18466, 0),
(@PATHID, 14, -1833.193, 2274.151, 48.50591, 5.492351, 0),
(@PATHID, 15, -1815.233, 2278.622, 48.37112, 0.24589, 0),
(@PATHID, 16, -1804.46, 2289.535, 48.50758, 0.764253, 0),
(@PATHID, 17, -1806.5, 2291.601, 48.25145, 2.45286, 0);

SET @GOSSIP=10699;
SET @TEXT_YES=14842;
SET @TEXT_NO=14843;
SET @FLAG_YES=8;
SET @FLAG_NO=1527;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer rogue"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no rogue");

SET @GOSSIP=10702;
SET @TEXT_YES=14849;
SET @TEXT_NO=14848;
SET @FLAG_YES=256;
SET @FLAG_NO=1279;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer warlock"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no warlock");

SET @GOSSIP=10838;
SET @TEXT_YES=14844;
SET @TEXT_NO=14845;
SET @FLAG_YES=16;
SET @FLAG_NO=1519;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer priest"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no priest");

SET @ID=0;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for priest class");

SET @GOSSIP=10837;
SET @TEXT_YES=14840;
SET @TEXT_NO=14841;
SET @FLAG_YES=128;
SET @FLAG_NO=1407;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer mage"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no mage");

SET @ID=0;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for mage class");

SET @GOSSIP=10836;
SET @TEXT_YES=14831;
SET @TEXT_NO=14832;
SET @FLAG_YES=1;
SET @FLAG_NO=1534;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer warrior"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no warrior");

SET @ID=0;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for warrior class");

SET @GOSSIP=10835;
SET @TEXT_YES=15028;
SET @TEXT_NO=15029;
SET @FLAG_YES=4;
SET @FLAG_NO=1531;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer hunter"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no hunter");

SET @ID=0;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for hunter class");

SET @GOSSIP=10834;
SET @TEXT_YES=14836;
SET @TEXT_NO=14835;
SET @FLAG_YES=1024;
SET @FLAG_NO=511;
delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu value 
(@GOSSIP, @TEXT_YES),
(@GOSSIP, @TEXT_NO);

delete from conditions where SourceTypeOrReferenceId=14 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry in (@TEXT_YES, @TEXT_NO);
insert into conditions values 
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer druid"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no druid");

SET @ID=0;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for druid class");





