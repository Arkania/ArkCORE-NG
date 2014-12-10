DELETE FROM gossip_menu WHERE entry=435 AND text_id=933;
INSERT INTO gossip_menu (entry,text_id) VALUES (435,933);

DELETE FROM gossip_menu_option WHERE menu_id=401;
DELETE FROM gossip_menu_option WHERE menu_id=421;
DELETE FROM gossip_menu_option WHERE menu_id=435;

INSERT INTO gossip_menu_option (menu_id,id,option_icon,option_text,OptionBroadcastTextID,option_id,npc_option_npcflag,action_menu_id,action_poi_id,box_coded,box_money,box_text,BoxBroadcastTextID) VALUES 
(401,0,0,"Druid",45409,1,1,405,1036,0,0,"",0),
(401,1,0,"Hunter",50546,1,1,408,1037,0,0,"",0),
(401,2,0,"Mage",45404,1,1,402,1038,0,0,"",0),
(401,3,0,"Paladin",48028,1,1,407,1039,0,0,"",0),
(401,4,0,"Priest",45405,1,1,406,1040,0,0,"",0),
(401,5,0,"Rogue",45406,1,1,403,1041,0,0,"",0),
(401,6,0,"Shaman",45410,1,1,8164,1042,0,0,"",0),
(401,7,0,"Warlock",45407,1,1,409,1043,0,0,"",0),
(401,8,0,"Warrior",45408,1,1,404,1044,0,0,"",0),

(421,0,0,"Alchemy",52058,1,1,422,1045,0,0,"",0),
(421,1,0,"Blacksmithing",51346,1,1,423,1046,0,0,"",0),
(421,2,0,"Cooking",45763,1,1,424,1048,0,0,"",0),
(421,3,0,"Enchanting",52063,1,1,444,1049,0,0,"",0),
(421,4,0,"Engineering",51347,1,1,425,1050,0,0,"",0),
(421,5,0,"First Aid",52066,1,1,426,1051,0,0,"",0),
(421,6,0,"Fishing",45767,1,1,443,1052,0,0,"",0),
(421,7,0,"Herbalism",45768,1,1,427,1053,0,0,"",0),
(421,8,0,"Inscription",48811,1,1,10010,1054,0,0,"",0),
(421,9,0,"Leatherworking",52071,1,1,428,1055,0,0,"",0),
(421,10,0,"Mining",51348,1,1,430,1056,0,0,"",0),
(421,11,0,"Skinning",52076,1,1,431,1057,0,0,"",0),
(421,12,0,"Tailoring",52077,1,1,432,1058,0,0,"",0),

(435,0,0,"|cFF0008E8NEW|r: Reforging",50622,1,1,3102,0,0,0,"",0),
(435,1,0,"|cFF0008E8NEW|r: Transmogrification",56155,1,1,265,0,0,0,"",0),
(435,2,0,"|cFF0008E8NEW|r: Void Storage",53080,1,1,9767,0,0,0,"",0),
(435,3,0,"Auction House",44627,1,1,3102,1020,0,0,"",0),
(435,4,0,"Bank of Stormwind",2749,1,1,265,1021,0,0,"",0),
(435,5,0,"Stormwind Harbor",29416,1,1,9767,1023,0,0,"",0),
(435,6,0,"Deeprun Tram",6351,1,1,3081,1025,0,0,"",0),
(435,7,0,"The Inn",7075,1,1,3126,1026,0,0,"",0),
(435,8,0,"Gryphon Master",6990,1,1,382,1027,0,0,"",0),
(435,9,0,"Guild Master",2870,1,1,383,1028,0,0,"",0),
(435,10,0,"Locksmith",33141,1,1,10260,1029,0,0,"",0),
(435,11,0,"Stable Master",45383,1,1,4925,1030,0,0,"",0),
(435,12,0,"Weapons Trainer",7247,1,1,3721,1031,0,0,"",0),
(435,13,0,"Officers' Lounge",9756,1,1,5883,1032,0,0,"",0),
(435,14,0,"Battlemaster",19209,1,1,8222,1034,0,0,"",0),
(435,15,0,"Barber",45376,1,1,10011,1035,0,0,"",0),
(435,16,0,"Lexicon of Power",32998,1,1,10205,1015,0,0,"",0),
(435,17,0,"Class Trainer",45378,1,1,401,0,0,0,"",0),
(435,18,0,"Profession Trainer",45382,1,1,421,0,0,0,"",0);
