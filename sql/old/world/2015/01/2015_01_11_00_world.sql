
update creature_template set AIName="", ScriptName="npc_marshal_gryan_stoutmantle_234" where entry=234;
update creature_template set AIName="", ScriptName="npc_lieutenant_horatio_laine_42744" where entry=42744;
update creature_template set AIName="", ScriptName="npc_stormwind_investigator_42745" where entry=42745;
update creature_template set AIName="", ScriptName="npc_Ripsnarl_42748" where entry=42748;
update creature_template set AIName="", ScriptName="npc_hope_saldean_42749" where entry=42749;
update creature_template set AIName="", ScriptName="npc_marshal_gryan_stoutmantle_42750" where entry=42750;
update creature_template set AIName="", ScriptName="npc_captain_danuvin_42751" where entry=42751;
update creature_template set AIName="", ScriptName="npc_scout_galiaan_42752" where entry=42752;
update creature_template set AIName="", ScriptName="npc_helix_gearbreaker_42753" where entry=42753;
update creature_template set AIName="", ScriptName="npc_glubtok_42755" where entry=42755;
update creature_template set AIName="", ScriptName="npc_defias_blackguard_42769" where entry=42769;
update creature_template set AIName="", ScriptName="npc_thor_523" where entry=523;

update gameobject set phaseMask=7 where guid=183244 and id=204043;
update creature set phaseMask=15 where guid=42283 and id=523;

update creature_text set entry=42748, groupid=0, id=0 where entry=42778 and groupid=0 and id=0; 

update creature_text set entry=42749, groupid=3, id=0 where entry=42372 and groupid=0 and id=0; 
update creature_text set entry=42749, groupid=4, id=0 where entry=42372 and groupid=1 and id=0; 
update creature_text set entry=42749, groupid=5, id=0 where entry=42372 and groupid=2 and id=0; 
update creature_text set entry=42749, groupid=6, id=0 where entry=42372 and groupid=3 and id=0; 
update creature_text set entry=42749, groupid=7, id=0 where entry=42372 and groupid=4 and id=0; 
update creature_text set entry=42749, groupid=8, id=0 where entry=42372 and groupid=5 and id=0; 
update creature_text set entry=42749, groupid=9, id=0 where entry=42372 and groupid=6 and id=0; 

delete from waypoint_data where id=427531;
insert into waypoint_data values
(427531,0,-10516.60,1086.420,53.63543,0,0,0,0,100,0),
(427531,1,-10515.60,1086.420,53.63543,0,0,0,0,100,0),
(427531,2,-10507.94,1080.792,55.0241,0,0,0,0,100,0),
(427531,3,-10516.23,1070.453,54.83309,0,0,0,0,100,0),
(427531,4,-10517.38,1061.017,55.78676,0,0,0,0,100,0),
(427531,5,-10517.42,1053.604,58.06884,0,0,0,0,100,0),
(427531,6,-10515.00,1049.594,59.85727,0,0,0,0,100,0),
(427531,7,-10515.00,1049.594,59.85727,0,0,0,0,100,0);

delete from waypoint_data where id=427481;
insert into waypoint_data values
(427481,0,-10514.8,1045.6,60.80753,0,0,0,0,100,0),
(427481,1,-10514.16,1042.139,60.79846,0,0,0,0,100,0),
(427481,2,-10511.66,1043.889,60.79846,0,0,0,0,100,0),
(427481,3,-10513.16,1051.389,60.79846,0,0,0,0,100,0),
(427481,4,-10516.03,1062.179,55.78939,0,0,0,0,100,0);

delete from waypoint_data where id=427491;
insert into waypoint_data values
(427491,0,-10512.44,1044.438,60.51799,0,0,0,0,100,0),
(427491,1,-10511.82,1045.24,60.68876,0,0,0,0,100,0),
(427491,2,-10512.82,1050.24,60.18876,0,0,0,0,100,0),
(427491,3,-10512.7,1056.043,57.85953,0,0,0,0,100,0);

delete from waypoint_data where id=427551;
insert into waypoint_data values
(427551,0,-10508.5,1055.51,58.71863,0,0,0,0,100,0),
(427551,1,-10509.12,1054.364 ,59.31274,0,0,0,0,100,0),
(427551,2,-10511.12,1059.614,57.06274,0,0,0,0,100,0),
(427551,3,-10513.75,1064.217 ,55.40685,0,0,0,0,100,0);

delete from creature_text where entry =42744;
insert into creature_text values
(42744,0,0,"Just tell me one thing, Vanessa.",12,0,100,16,0,0,"Rise of the Brotherhood 11th sentence",42674),
(42744,1,0,"Why'd you have the Furlbrows killed?",12,0,100,16,0,0,"Rise of the Brotherhood 12th sentence",42675);

update creature_text set BroadcastTextID=42655 where entry=42750 and groupid=4 and id=0;
update creature_text set BroadcastTextID=42656 where entry=42749 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42657 where entry=42750 and groupid=5 and id=0;
update creature_text set BroadcastTextID=42658 where entry=42749 and groupid=1 and id=0;
update creature_text set BroadcastTextID=42659 where entry=42749 and groupid=2 and id=0;
update creature_text set BroadcastTextID=42660 where entry=42749 and groupid=3 and id=0;
update creature_text set BroadcastTextID=42661 where entry=42749 and groupid=4 and id=0;
update creature_text set BroadcastTextID=42662 where entry=42749 and groupid=5 and id=0;
update creature_text set BroadcastTextID=42663 where entry=42748 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42672 where entry=42749 and groupid=9 and id=0;
update creature_text set BroadcastTextID=42673 where entry=42749 and groupid=6 and id=0;

update creature_text set BroadcastTextID=42676 where entry=42749 and groupid=7 and id=0;
update creature_text set BroadcastTextID=42677 where entry=42749 and groupid=8 and id=0;

update creature_text set BroadcastTextID=42681 where entry=42750 and groupid=6 and id=0;

update creature_text set BroadcastTextID=42505 where entry=42750 and groupid=0 and id=0;
update creature_text set BroadcastTextID=42508 where entry=42750 and groupid=1 and id=0;
update creature_text set BroadcastTextID=42528 where entry=42750 and groupid=2 and id=0;
update creature_text set BroadcastTextID=42530 where entry=42750 and groupid=3 and id=0;

delete from gossip_menu_option where menu_id=4106 and id=1;
insert into gossip_menu_option values
(4106,1,2,"I need a ride, fast!  I have an important message to deliver!",7667,4,8192,0,0,0,0,0,"",0);

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=4106 and SourceEntry=1 and ConditionTypeOrReference=28 and ConditionValue1=26322; 
insert into conditions (SourceTypeOrReferenceId,SourceGroup,SourceEntry,ConditionTypeOrReference,ConditionValue1) values 
(15,4106,1,28,26322);

delete from waypoint_data where id=4276901;
insert into waypoint_data values 
(4276901,0,-10509.5900,1050.4760,60.2991,0,0,0,0,100,0),
(4276901,1,-10503.3300,1057.5080,60.0979,0,0,0,0,100,0),
(4276901,2,-10501.5700,1059.5410,59.3968,0,0,0,0,100,0);

delete from waypoint_data where id=4276902;
insert into waypoint_data values 
(4276902,0,-10503.3400,1044.3310,60.5180,0,0,0,0,100,0),
(4276902,1,-10507.2500,1045.2230,60.7680,0,0,0,0,100,0),
(4276902,2,-10509.7500,1045.4730,60.7680,0,0,0,0,100,0),
(4276902,3,-10517.1700,1046.6150,60.5180,0,0,0,0,100,0);

delete from waypoint_data where id=4276903;
insert into waypoint_data values 
(4276903,0,-10511.6500,1039.5410,60.5180,0,0,0,0,100,0),
(4276903,1,-10513.0300,1039.1800,60.7676,0,0,0,0,100,0),
(4276903,2,-10516.2800,1037.9300,60.7676,0,0,0,0,100,0),
(4276903,3,-10521.7800,1036.4300,60.5176,0,0,0,0,100,0),
(4276903,4,-10522.9100,1035.8190,60.5172,0,0,0,0,100,0);

delete from waypoint_data where id=4276904;
insert into waypoint_data values 
(4276904,0,-10511.0800,1048.7850,60.5180,0,0,0,0,100,0),
(4276904,1,-10517.7600,1053.5360,58.0349,0,0,0,0,100,0);

delete from waypoint_data where id=4276905;
insert into waypoint_data values 
(4276905,0,-10505.6200,1041.0970,60.5180,0,0,0,0,100,0),
(4276905,1,-10509.4000,1044.7230,60.7680,0,0,0,0,100,0),
(4276905,2,-10512.6900,1047.3490,60.5180,0,0,0,0,100,0);

delete from waypoint_data where id=4276906;
insert into waypoint_data values 
(4276906,0,-10508.1000,1040.0490,60.5180,0,0,0,0,100,0),
(4276906,1,-10508.0000,1046.1060,60.7680,0,0,0,0,100,0),
(4276906,2,-10507.9000,1050.1640,60.5180,0,0,0,0,100,0);

delete from waypoint_data where id=4276907;
insert into waypoint_data values 
(4276907,0,-10511.7200,1041.6850,60.5180,0,0,0,0,100,0),
(4276907,1,-10509.9600,1046.6490,60.7680,0,0,0,0,100,0),
(4276907,2,-10509.4600,1048.1490,60.7680,0,0,0,0,100,0),
(4276907,3,-10508.7100,1050.1130,60.5180,0,0,0,0,100,0);

delete from waypoint_data where id=4276908;
insert into waypoint_data values 
(4276908,0,-10511.1000,1048.5700,60.5180,0,0,0,0,100,0),
(4276908,1,-10518.9500,1056.5660,56.7703,0,0,0,0,100,0);

delete from waypoint_data where id=4276909;
insert into waypoint_data values 
(4276909,0,-10508.3900,1050.4250,60.4875,0,0,0,0,100,0),
(4276909,1,-10503.3700,1058.3400,59.8144,0,0,0,0,100,0),
(4276909,2,-10501.3500,1061.7550,58.6413,0,0,0,0,100,0);

delete from waypoint_data where id=4276910;
insert into waypoint_data values 
(4276910,0,-10505.2700,1049.4110,60.5180,0,0,0,0,100,0),
(4276910,1,-10507.7200,1050.9230,60.6706,0,0,0,0,100,0),
(4276910,2,-10515.6700,1054.9350,57.8232,0,0,0,0,100,0);

delete from waypoint_data where id=4276911;
insert into waypoint_data values 
(4276911,0,-10512.3000,1040.6920,60.5180,0,0,0,0,100,0),
(4276911,1,-10513.5300,1040.0630,60.7647,0,0,0,0,100,0),
(4276911,2,-10516.5300,1038.8130,60.7647,0,0,0,0,100,0),
(4276911,3,-10521.5300,1036.5630,60.5147,0,0,0,0,100,0),
(4276911,4,-10522.7700,1035.9340,60.5115,0,0,0,0,100,0);

delete from waypoint_data where id=4276912;
insert into waypoint_data values 
(4276912,0,-10505.8600,1049.6490,60.5180,0,0,0,0,100,0),
(4276912,1,-10507.7400,1050.8130,60.6332,0,0,0,0,100,0),
(4276912,2,-10515.1200,1053.9780,58.2485,0,0,0,0,100,0);

delete from waypoint_data where id=4276913;
insert into waypoint_data values 
(4276913,0,-10510.5500,1049.9170,60.3656,0,0,0,0,100,0),
(4276913,1,-10521.7700,1051.9900,59.5536,0,0,0,0,100,0),
(4276913,2,-10524.4900,1052.5630,58.7415,0,0,0,0,100,0);

delete from waypoint_data where id=4276914;
insert into waypoint_data values 
(4276914,0,-10502.7000,1042.7840,60.5180,0,0,0,0,100,0),
(4276914,1,-10500.7500,1042.5520,60.7378,0,0,0,0,100,0),
(4276914,2,-10493.0000,1041.5520,60.7378,0,0,0,0,100,0),
(4276914,3,-10490.7900,1040.8200,60.4576,0,0,0,0,100,0);

delete from waypoint_data where id=4276915;
insert into waypoint_data values 
(4276915,0,-10510.7100,1049.7240,60.4121,0,0,0,0,100,0),
(4276915,1,-10521.7600,1052.1500,59.5922,0,0,0,0,100,0),
(4276915,2,-10524.3000,1052.5770,58.7723,0,0,0,0,100,0);

update creature set phaseMask=4 where id=42793;

