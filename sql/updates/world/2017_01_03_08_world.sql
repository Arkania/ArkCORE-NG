

delete from creature where id=35838 and guid in (283007, 283008);

delete from creature where id=35812 and guid in (282960, 282961, 282962, 282963, 282965, 282966, 282967, 282968, 282969, 282970);

update creature set phaseId=171 where id=35810;

update creature set phaseId=0, phaseGroup=407 where id in (35875, 35882, 36432, 39655);

update gameobject set phaseId=0, phaseGroup=407 where guid=168875;

update creature set phaseId=0, phaseGroup=367 where id=36112;

DELETE FROM creature_addon WHERE guid=282966;
DELETE FROM creature_addon WHERE guid=285379;
DELETE FROM creature_addon WHERE guid=282970;
DELETE FROM creature_addon WHERE guid=284219;

UPDATE creature_template SET InhabitType=5 WHERE entry=36383;

update creature set phaseId=0, phaseGroup=430 where id=35904;

update creature set phaseId=0, phaseGroup=407 where id=36346;

delete from creature where guid in (284214, 284218, 284219, 284220, 284223, 284224, 284225, 284227);

update gameobject set phaseId=0, phaseGroup=407 where guid=168786;

delete from creature where guid in (284215, 284217, 284221, 284402);

delete from creature where guid in (282953, 282954, 282956, 282957, 282958);

delete from creature_addon where guid in (282953, 282954, 282956, 282957, 282958);

delete from waypoint_data where id in (282953, 282954, 282956, 282957, 282958);

DELETE FROM waypoint_data WHERE id=245781;
INSERT INTO waypoint_data VALUES 
(245781, 0, -8398.68, 1334.17, 102.104, 0, 0, 0, 0, 100, 0),
(245781, 1, -8408.07, 1333.38, 102.148, 0, 0, 0, 0, 100, 0),
(245781, 2, -8410.13, 1333.18, 102.201, 0, 0, 0, 0, 100, 0),
(245781, 3, -8411.12, 1333.08, 102.201, 0, 0, 0, 0, 100, 0),
(245781, 4, -8416.87, 1332.50, 102.375, 0, 0, 0, 0, 100, 0),
(245781, 5, -8424.52, 1329.44, 102.096, 0, 0, 0, 0, 100, 0),
(245781, 6, -8425.32, 1328.85, 102.096, 0, 0, 0, 0, 100, 0),
(245781, 7, -8431.02, 1324.60, 101.875, 0, 0, 0, 0, 100, 0),
(245781, 8, -8414.02, 1331.60, 102.275, 0, 0, 0, 0, 100, 0);

update creature set phaseId=0, phaseGroup=574 where guid=245781; 

update creature set MovementType=2 where guid in (285420, 285421); 

delete from creature where guid in (282935, 282936, 282937, 282939, 282940);

delete from creature_addon where guid in (282935, 282936, 282937, 282939, 282940);

update creature set phaseId=0, phaseGroup=574 where guid=249705;

delete from creature where guid=283979;

update creature set phaseId=0, phaseGroup=562 where guid=383980;

update creature set phaseId=0, phaseGroup=570 where guid=16744;

delete from creature where guid=283975;

update creature set phaseId=0, phaseGroup=562 where guid=248448;

update creature set phaseId=0, phaseGroup=570 where guid=245823;

delete from creature where guid in (284022, 284025, 284026, 284052);

update creature set id=48304 where map=648 and guid in (245775, 245776, 245777, 245778);

delete from creature where id=48304 and guid in (284037, 284028, 284043, 284048);

delete from creature where id=48304 and guid in (284035, 284038, 284041, 284049);

delete from creature where id=48304 and guid in (284034, 284036, 284039, 284050, 284053);

delete from creature where id=48304 and guid in (284029, 284031, 284032, 284040, 284045, 284051);

delete from creature where id=48304 and guid in (284044, 284023, 284042, 284024, 284027, 284030, 284032, 284046, 284033);

update creature set phaseId=0, phaseGroup=558 where id=48304;

delete from creature_addon where guid in (284022, 284023, 284025, 284026, 284028);

--

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ConditionValue2=5;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10620, 2, 47044, 5);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47045 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10620, 2, 47045, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10620, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ElseGroup=1 AND ConditionValue2=5;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10620, 1, 2, 47044, 5);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47045 AND ElseGroup=1 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10620, 1, 2, 47045, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10620 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10620, 1, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14697 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10620, 14697, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14697 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10620, 14697, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14697 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10620, 14697, 2, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14697 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10620, 14697, 2, 20);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14698 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109 AND ElseGroup=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10620, 14698, 1, 9, 14109, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14698 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10620, 14698, 1, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14698 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=3 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10620, 14698, 3, 9, 14110, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10620 AND SourceEntry=14698 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=3;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10620, 14698, 3, 20);

--	

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ConditionValue2=3;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10622, 2, 47044, 3);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47046 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10622, 2, 47046, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10622, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ElseGroup=1 AND ConditionValue2=3;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10622, 1, 2, 47044, 3);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47046 AND ElseGroup=1 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10622, 1, 2, 47046, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10622 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10622, 1, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14700 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10622, 14700, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14700 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10622, 14700, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14700 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10622, 14700, 2, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14700 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10622, 14700, 2, 20);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14701 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109 AND ElseGroup=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10622, 14701, 1, 9, 14109, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14701 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10622, 14701, 1, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14701 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=3 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10622, 14701, 3, 9, 14110, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10622 AND SourceEntry=14701 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=3;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10622, 14701, 3, 20);

--

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ConditionValue2=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10624, 2, 47044, 2);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47047 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10624, 2, 47047, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10624, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47044 AND ElseGroup=1 AND ConditionValue2=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2) VALUES (15, 10624, 1, 2, 47044, 2);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=2 AND ConditionValue1=47047 AND ElseGroup=1 AND ConditionValue2=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1, ConditionValue2, NegativeCondition) VALUES (15, 10624, 1, 2, 47047, 1, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10624 AND SourceEntry=0 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 10624, 1, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14703 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10624, 14703, 9, 14109);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14703 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10624, 14703, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14703 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10624, 14703, 2, 9, 14110);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14703 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=2;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10624, 14703, 2, 20);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14704 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14109 AND ElseGroup=1 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10624, 14704, 1, 9, 14109, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14704 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=1 AND ElseGroup=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1) VALUES (14, 10624, 14704, 1, 20, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14704 AND SourceId=0 AND ConditionTypeOrReference=9 AND ConditionValue1=14110 AND ElseGroup=3 AND NegativeCondition=1;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference, ConditionValue1, NegativeCondition) VALUES (14, 10624, 14704, 3, 9, 14110, 1);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=14 AND SourceGroup=10624 AND SourceEntry=14704 AND SourceId=0 AND ConditionTypeOrReference=20 AND ConditionValue1=0 AND ElseGroup=3;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, SourceEntry, ElseGroup, ConditionTypeOrReference) VALUES (14, 10624, 14704, 3, 20);

delete from gameobject where id=201974;

delete from gameobject where id=201972 and guid between 168900 and 169080;

delete from creature where id=38111 and phaseId in (179, 181, 182);

update creature set phaseId=0, phasegroup=426 where id=38111 and phaseid=180;

UPDATE creature_template SET npcflag=0 WHERE entry=38111;

delete from creature where guid=283926;

delete from gameobject where id=202104;

delete from creature where guid = 283978;

UPDATE quest_template SET PointMapId=0, PointX=0, PointY=0, PointOption=0 WHERE Id=24744;

update creature set phaseId=0, phaseGroup=424 where id=36732 and phaseId=170;

update creature set phaseId=0, phaseGroup=424 where id=36681;

delete from creature where id=36682 and guid in (286238, 286239, 286240, 286241, 286242);

update creature set phaseId=0, phaseGroup=424 where id=36682;

DELETE FROM creature_addon WHERE guid=283319;
DELETE FROM creature_addon WHERE guid=283320;
DELETE FROM creature_addon WHERE guid=278083;
DELETE FROM creature_addon WHERE guid=278047;
DELETE FROM creature_addon WHERE guid=278095;
DELETE FROM creature_addon WHERE guid=278131;
DELETE FROM creature_addon WHERE guid=278101;
DELETE FROM creature_addon WHERE guid=278103;
DELETE FROM creature_addon WHERE guid=283321;
DELETE FROM creature_addon WHERE guid=283322;
DELETE FROM creature_addon WHERE guid=283323;
DELETE FROM creature_addon WHERE guid=278063;
DELETE FROM creature_addon WHERE guid=278132;
DELETE FROM creature_addon WHERE guid=283324;
DELETE FROM creature_addon WHERE guid=278026;
DELETE FROM creature_addon WHERE guid=283325;
DELETE FROM creature_addon WHERE guid=278109;
DELETE FROM creature_addon WHERE guid=283327;
DELETE FROM creature_addon WHERE guid=283328;
DELETE FROM creature_addon WHERE guid=283329;
DELETE FROM creature_addon WHERE guid=278032;
DELETE FROM creature_addon WHERE guid=278019;
DELETE FROM creature_addon WHERE guid=278064;
DELETE FROM creature_addon WHERE guid=283330;
DELETE FROM creature_addon WHERE guid=283331;
DELETE FROM creature_addon WHERE guid=283332;
DELETE FROM creature_addon WHERE guid=283333;
DELETE FROM creature_addon WHERE guid=278117;
DELETE FROM creature_addon WHERE guid=283335;
DELETE FROM creature_addon WHERE guid=283336;
DELETE FROM creature_addon WHERE guid=278079;
DELETE FROM creature_addon WHERE guid=278009;
DELETE FROM creature_addon WHERE guid=278088;
DELETE FROM creature_addon WHERE guid=283337;
DELETE FROM creature_addon WHERE guid=283339;
DELETE FROM creature_addon WHERE guid=278111;
DELETE FROM creature_addon WHERE guid=278045;
DELETE FROM creature_addon WHERE guid=278037;
DELETE FROM creature_addon WHERE guid=278061;
DELETE FROM creature_addon WHERE guid=278041;
DELETE FROM creature_addon WHERE guid=283348;
DELETE FROM creature_addon WHERE guid=283349;
DELETE FROM creature_addon WHERE guid=278057;
DELETE FROM creature_addon WHERE guid=283350;
DELETE FROM creature_addon WHERE guid=278039;
DELETE FROM creature_addon WHERE guid=278053;
DELETE FROM creature_addon WHERE guid=283351;
DELETE FROM creature_addon WHERE guid=283352;
DELETE FROM creature_addon WHERE guid=278050;
DELETE FROM creature_addon WHERE guid=278074;
DELETE FROM creature_addon WHERE guid=278025;
DELETE FROM creature_addon WHERE guid=283353;
DELETE FROM creature_addon WHERE guid=278077;
DELETE FROM creature_addon WHERE guid=278055;
DELETE FROM creature_addon WHERE guid=283354;
DELETE FROM creature_addon WHERE guid=278096;
DELETE FROM creature_addon WHERE guid=278089;
DELETE FROM creature_addon WHERE guid=278125;
DELETE FROM creature_addon WHERE guid=283355;
DELETE FROM creature_addon WHERE guid=278048;
DELETE FROM creature_addon WHERE guid=278093;
DELETE FROM creature_addon WHERE guid=283356;
DELETE FROM creature_addon WHERE guid=278129;
DELETE FROM creature_addon WHERE guid=278071;
DELETE FROM creature_addon WHERE guid=278118;
DELETE FROM creature_addon WHERE guid=283357;
DELETE FROM creature_addon WHERE guid=278060;
DELETE FROM creature_addon WHERE guid=283358;
DELETE FROM creature_addon WHERE guid=278072;
DELETE FROM creature_addon WHERE guid=278030;
DELETE FROM creature_addon WHERE guid=283359;
DELETE FROM creature_addon WHERE guid=278120;
DELETE FROM creature_addon WHERE guid=283361;
DELETE FROM creature_addon WHERE guid=278100;
DELETE FROM creature_addon WHERE guid=278082;
DELETE FROM creature_addon WHERE guid=278054;
DELETE FROM creature_addon WHERE guid=283362;
DELETE FROM creature_addon WHERE guid=278090;
DELETE FROM creature_addon WHERE guid=283363;
DELETE FROM creature_addon WHERE guid=283364;
DELETE FROM creature_addon WHERE guid=283365;
DELETE FROM creature_addon WHERE guid=283366;
DELETE FROM creature_addon WHERE guid=278021;
DELETE FROM creature_addon WHERE guid=278119;
DELETE FROM creature_addon WHERE guid=283367;
DELETE FROM creature_addon WHERE guid=278099;

UPDATE creature_template SET InhabitType=2 WHERE entry=36682;

UPDATE creature_template SET InhabitType=2 WHERE entry=36681;

DELETE FROM creature_addon WHERE guid=283926;
DELETE FROM creature_addon WHERE guid=283978;
DELETE FROM creature_addon WHERE guid=286239;
DELETE FROM creature_addon WHERE guid=286238;
DELETE FROM creature_addon WHERE guid=284918;
DELETE FROM creature_addon WHERE guid=284919;
DELETE FROM creature_addon WHERE guid=248518;
DELETE FROM creature_addon WHERE guid=284920;
DELETE FROM creature_addon WHERE guid=284921;
DELETE FROM creature_addon WHERE guid=284922;
DELETE FROM creature_addon WHERE guid=284923;
DELETE FROM creature_addon WHERE guid=284924;
DELETE FROM creature_addon WHERE guid=284925;
DELETE FROM creature_addon WHERE guid=284926;
DELETE FROM creature_addon WHERE guid=284927;
DELETE FROM creature_addon WHERE guid=284928;
DELETE FROM creature_addon WHERE guid=284929;
DELETE FROM creature_addon WHERE guid=284930;
DELETE FROM creature_addon WHERE guid=284931;
DELETE FROM creature_addon WHERE guid=284932;
DELETE FROM creature_addon WHERE guid=284933;
DELETE FROM creature_addon WHERE guid=284934;
DELETE FROM creature_addon WHERE guid=284935;
DELETE FROM creature_addon WHERE guid=284936;
DELETE FROM creature_addon WHERE guid=284937;
DELETE FROM creature_addon WHERE guid=284938;
DELETE FROM creature_addon WHERE guid=284939;
DELETE FROM creature_addon WHERE guid=284940;
DELETE FROM creature_addon WHERE guid=284941;
DELETE FROM creature_addon WHERE guid=284942;
DELETE FROM creature_addon WHERE guid=284943;
DELETE FROM creature_addon WHERE guid=284944;
DELETE FROM creature_addon WHERE guid=284945;
DELETE FROM creature_addon WHERE guid=284946;
DELETE FROM creature_addon WHERE guid=284947;
DELETE FROM creature_addon WHERE guid=284948;
DELETE FROM creature_addon WHERE guid=284949;
DELETE FROM creature_addon WHERE guid=284950;
DELETE FROM creature_addon WHERE guid=284951;
DELETE FROM creature_addon WHERE guid=248791;
DELETE FROM creature_addon WHERE guid=284952;
DELETE FROM creature_addon WHERE guid=248777;
DELETE FROM creature_addon WHERE guid=284953;
DELETE FROM creature_addon WHERE guid=284954;
DELETE FROM creature_addon WHERE guid=284955;
DELETE FROM creature_addon WHERE guid=284956;
DELETE FROM creature_addon WHERE guid=284957;
DELETE FROM creature_addon WHERE guid=284958;
DELETE FROM creature_addon WHERE guid=284959;
DELETE FROM creature_addon WHERE guid=284960;
DELETE FROM creature_addon WHERE guid=284961;
DELETE FROM creature_addon WHERE guid=248793;
DELETE FROM creature_addon WHERE guid=284962;
DELETE FROM creature_addon WHERE guid=248789;
DELETE FROM creature_addon WHERE guid=248795;
DELETE FROM creature_addon WHERE guid=284963;
DELETE FROM creature_addon WHERE guid=284964;
DELETE FROM creature_addon WHERE guid=284965;
DELETE FROM creature_addon WHERE guid=284966;
DELETE FROM creature_addon WHERE guid=284967;
DELETE FROM creature_addon WHERE guid=248389;
DELETE FROM creature_addon WHERE guid=248780;
DELETE FROM creature_addon WHERE guid=284968;
DELETE FROM creature_addon WHERE guid=284969;
DELETE FROM creature_addon WHERE guid=284970;
DELETE FROM creature_addon WHERE guid=284971;
DELETE FROM creature_addon WHERE guid=284972;
DELETE FROM creature_addon WHERE guid=284973;
DELETE FROM creature_addon WHERE guid=284974;
DELETE FROM creature_addon WHERE guid=284975;
DELETE FROM creature_addon WHERE guid=284976;
DELETE FROM creature_addon WHERE guid=284977;
DELETE FROM creature_addon WHERE guid=284978;
DELETE FROM creature_addon WHERE guid=284979;
DELETE FROM creature_addon WHERE guid=284980;
DELETE FROM creature_addon WHERE guid=284981;
DELETE FROM creature_addon WHERE guid=284982;
DELETE FROM creature_addon WHERE guid=284983;
DELETE FROM creature_addon WHERE guid=284984;
DELETE FROM creature_addon WHERE guid=284985;
DELETE FROM creature_addon WHERE guid=248390;
DELETE FROM creature_addon WHERE guid=284986;
DELETE FROM creature_addon WHERE guid=284987;
DELETE FROM creature_addon WHERE guid=284988;
DELETE FROM creature_addon WHERE guid=284989;
DELETE FROM creature_addon WHERE guid=284990;
DELETE FROM creature_addon WHERE guid=284991;
DELETE FROM creature_addon WHERE guid=284992;
DELETE FROM creature_addon WHERE guid=284993;
DELETE FROM creature_addon WHERE guid=248792;
DELETE FROM creature_addon WHERE guid=284994;
DELETE FROM creature_addon WHERE guid=284995;
DELETE FROM creature_addon WHERE guid=284996;
DELETE FROM creature_addon WHERE guid=284997;
DELETE FROM creature_addon WHERE guid=284998;
DELETE FROM creature_addon WHERE guid=284999;
DELETE FROM creature_addon WHERE guid=285000;
DELETE FROM creature_addon WHERE guid=285001;
DELETE FROM creature_addon WHERE guid=285002;
DELETE FROM creature_addon WHERE guid=285003;
DELETE FROM creature_addon WHERE guid=285004;
DELETE FROM creature_addon WHERE guid=285005;
DELETE FROM creature_addon WHERE guid=285006;
DELETE FROM creature_addon WHERE guid=285007;
DELETE FROM creature_addon WHERE guid=285008;
DELETE FROM creature_addon WHERE guid=285009;
DELETE FROM creature_addon WHERE guid=285010;
DELETE FROM creature_addon WHERE guid=285011;
DELETE FROM creature_addon WHERE guid=285012;
DELETE FROM creature_addon WHERE guid=285013;
DELETE FROM creature_addon WHERE guid=285014;
DELETE FROM creature_addon WHERE guid=285015;
DELETE FROM creature_addon WHERE guid=285016;
DELETE FROM creature_addon WHERE guid=285017;
DELETE FROM creature_addon WHERE guid=248378;
DELETE FROM creature_addon WHERE guid=248377;
DELETE FROM creature_addon WHERE guid=285018;
DELETE FROM creature_addon WHERE guid=285019;
DELETE FROM creature_addon WHERE guid=285020;
DELETE FROM creature_addon WHERE guid=285021;
DELETE FROM creature_addon WHERE guid=285022;
DELETE FROM creature_addon WHERE guid=285023;
DELETE FROM creature_addon WHERE guid=285024;
DELETE FROM creature_addon WHERE guid=285025;
DELETE FROM creature_addon WHERE guid=285026;
DELETE FROM creature_addon WHERE guid=285027;
DELETE FROM creature_addon WHERE guid=285028;
DELETE FROM creature_addon WHERE guid=285029;
DELETE FROM creature_addon WHERE guid=285030;
DELETE FROM creature_addon WHERE guid=285031;
DELETE FROM creature_addon WHERE guid=285032;
DELETE FROM creature_addon WHERE guid=285033;
DELETE FROM creature_addon WHERE guid=285034;
DELETE FROM creature_addon WHERE guid=285035;
DELETE FROM creature_addon WHERE guid=285036;
DELETE FROM creature_addon WHERE guid=285037;
DELETE FROM creature_addon WHERE guid=246406;
DELETE FROM creature_addon WHERE guid=285038;
DELETE FROM creature_addon WHERE guid=285039;
DELETE FROM creature_addon WHERE guid=285040;
DELETE FROM creature_addon WHERE guid=285041;
DELETE FROM creature_addon WHERE guid=285042;
DELETE FROM creature_addon WHERE guid=285043;
DELETE FROM creature_addon WHERE guid=285044;
DELETE FROM creature_addon WHERE guid=285045;
DELETE FROM creature_addon WHERE guid=285046;
DELETE FROM creature_addon WHERE guid=285047;
DELETE FROM creature_addon WHERE guid=285048;
DELETE FROM creature_addon WHERE guid=285049;
DELETE FROM creature_addon WHERE guid=285050;
DELETE FROM creature_addon WHERE guid=285051;
DELETE FROM creature_addon WHERE guid=285052;
DELETE FROM creature_addon WHERE guid=285053;
DELETE FROM creature_addon WHERE guid=285054;
DELETE FROM creature_addon WHERE guid=285055;
DELETE FROM creature_addon WHERE guid=285056;
DELETE FROM creature_addon WHERE guid=285057;
DELETE FROM creature_addon WHERE guid=285058;
DELETE FROM creature_addon WHERE guid=285059;
DELETE FROM creature_addon WHERE guid=285060;
DELETE FROM creature_addon WHERE guid=285061;
DELETE FROM creature_addon WHERE guid=285062;
DELETE FROM creature_addon WHERE guid=285063;
DELETE FROM creature_addon WHERE guid=285064;
DELETE FROM creature_addon WHERE guid=285065;
DELETE FROM creature_addon WHERE guid=285066;
DELETE FROM creature_addon WHERE guid=285067;
DELETE FROM creature_addon WHERE guid=285068;
DELETE FROM creature_addon WHERE guid=285069;
DELETE FROM creature_addon WHERE guid=285070;
DELETE FROM creature_addon WHERE guid=285071;
DELETE FROM creature_addon WHERE guid=285072;
DELETE FROM creature_addon WHERE guid=285073;
DELETE FROM creature_addon WHERE guid=285074;
DELETE FROM creature_addon WHERE guid=285075;
DELETE FROM creature_addon WHERE guid=285076;
DELETE FROM creature_addon WHERE guid=285077;
DELETE FROM creature_addon WHERE guid=285078;
DELETE FROM creature_addon WHERE guid=285079;
DELETE FROM creature_addon WHERE guid=285080;
DELETE FROM creature_addon WHERE guid=285081;
DELETE FROM creature_addon WHERE guid=285082;
DELETE FROM creature_addon WHERE guid=285083;
DELETE FROM creature_addon WHERE guid=285084;
DELETE FROM creature_addon WHERE guid=285085;
DELETE FROM creature_addon WHERE guid=285086;
DELETE FROM creature_addon WHERE guid=285087;
DELETE FROM creature_addon WHERE guid=285088;
DELETE FROM creature_addon WHERE guid=285089;
DELETE FROM creature_addon WHERE guid=285090;
DELETE FROM creature_addon WHERE guid=285091;
DELETE FROM creature_addon WHERE guid=285092;
DELETE FROM creature_addon WHERE guid=285093;
DELETE FROM creature_addon WHERE guid=285094;
DELETE FROM creature_addon WHERE guid=285095;
DELETE FROM creature_addon WHERE guid=285096;
DELETE FROM creature_addon WHERE guid=285097;
DELETE FROM creature_addon WHERE guid=285098;
DELETE FROM creature_addon WHERE guid=285099;
DELETE FROM creature_addon WHERE guid=285100;
DELETE FROM creature_addon WHERE guid=285101;
DELETE FROM creature_addon WHERE guid=285102;
DELETE FROM creature_addon WHERE guid=285103;
DELETE FROM creature_addon WHERE guid=285104;
DELETE FROM creature_addon WHERE guid=285105;
DELETE FROM creature_addon WHERE guid=285106;
DELETE FROM creature_addon WHERE guid=285107;
DELETE FROM creature_addon WHERE guid=285108;
DELETE FROM creature_addon WHERE guid=285109;
DELETE FROM creature_addon WHERE guid=285110;
DELETE FROM creature_addon WHERE guid=285111;
DELETE FROM creature_addon WHERE guid=285112;
DELETE FROM creature_addon WHERE guid=285113;
DELETE FROM creature_addon WHERE guid=285114;
DELETE FROM creature_addon WHERE guid=285115;
DELETE FROM creature_addon WHERE guid=285116;
DELETE FROM creature_addon WHERE guid=285117;
DELETE FROM creature_addon WHERE guid=285118;
DELETE FROM creature_addon WHERE guid=285119;
DELETE FROM creature_addon WHERE guid=285120;
DELETE FROM creature_addon WHERE guid=285121;
DELETE FROM creature_addon WHERE guid=285122;
DELETE FROM creature_addon WHERE guid=285123;
DELETE FROM creature_addon WHERE guid=285124;
DELETE FROM creature_addon WHERE guid=285125;
DELETE FROM creature_addon WHERE guid=285126;
DELETE FROM creature_addon WHERE guid=285127;
DELETE FROM creature_addon WHERE guid=285128;
DELETE FROM creature_addon WHERE guid=285129;
DELETE FROM creature_addon WHERE guid=285130;
DELETE FROM creature_addon WHERE guid=285131;
DELETE FROM creature_addon WHERE guid=285132;
DELETE FROM creature_addon WHERE guid=285133;
DELETE FROM creature_addon WHERE guid=285134;
DELETE FROM creature_addon WHERE guid=285135;
DELETE FROM creature_addon WHERE guid=285136;
DELETE FROM creature_addon WHERE guid=285137;
DELETE FROM creature_addon WHERE guid=285138;
DELETE FROM creature_addon WHERE guid=285139;
DELETE FROM creature_addon WHERE guid=285140;
DELETE FROM creature_addon WHERE guid=285141;
DELETE FROM creature_addon WHERE guid=285142;
DELETE FROM creature_addon WHERE guid=285143;
DELETE FROM creature_addon WHERE guid=285144;
DELETE FROM creature_addon WHERE guid=285145;
DELETE FROM creature_addon WHERE guid=285146;
DELETE FROM creature_addon WHERE guid=285147;
DELETE FROM creature_addon WHERE guid=285148;
DELETE FROM creature_addon WHERE guid=285149;
DELETE FROM creature_addon WHERE guid=285150;
DELETE FROM creature_addon WHERE guid=285151;
DELETE FROM creature_addon WHERE guid=285152;
DELETE FROM creature_addon WHERE guid=285153;
DELETE FROM creature_addon WHERE guid=285154;
DELETE FROM creature_addon WHERE guid=285155;
DELETE FROM creature_addon WHERE guid=285156;
DELETE FROM creature_addon WHERE guid=285157;
DELETE FROM creature_addon WHERE guid=285158;
DELETE FROM creature_addon WHERE guid=285159;
DELETE FROM creature_addon WHERE guid=285160;
DELETE FROM creature_addon WHERE guid=285161;
DELETE FROM creature_addon WHERE guid=285162;
DELETE FROM creature_addon WHERE guid=285163;
DELETE FROM creature_addon WHERE guid=285164;
DELETE FROM creature_addon WHERE guid=285165;
DELETE FROM creature_addon WHERE guid=285166;
DELETE FROM creature_addon WHERE guid=285167;
DELETE FROM creature_addon WHERE guid=285168;
DELETE FROM creature_addon WHERE guid=285169;
DELETE FROM creature_addon WHERE guid=285170;
DELETE FROM creature_addon WHERE guid=285171;
DELETE FROM creature_addon WHERE guid=285172;
DELETE FROM creature_addon WHERE guid=285173;
DELETE FROM creature_addon WHERE guid=285174;
DELETE FROM creature_addon WHERE guid=285175;
DELETE FROM creature_addon WHERE guid=285176;
DELETE FROM creature_addon WHERE guid=285177;
DELETE FROM creature_addon WHERE guid=285178;
DELETE FROM creature_addon WHERE guid=285179;
DELETE FROM creature_addon WHERE guid=285180;
DELETE FROM creature_addon WHERE guid=285181;
DELETE FROM creature_addon WHERE guid=285182;
DELETE FROM creature_addon WHERE guid=285183;
DELETE FROM creature_addon WHERE guid=285184;
DELETE FROM creature_addon WHERE guid=285185;
DELETE FROM creature_addon WHERE guid=285186;
DELETE FROM creature_addon WHERE guid=285187;
DELETE FROM creature_addon WHERE guid=285188;
DELETE FROM creature_addon WHERE guid=285189;
DELETE FROM creature_addon WHERE guid=285190;
DELETE FROM creature_addon WHERE guid=285191;
DELETE FROM creature_addon WHERE guid=285192;
DELETE FROM creature_addon WHERE guid=285193;
DELETE FROM creature_addon WHERE guid=285194;
DELETE FROM creature_addon WHERE guid=285195;
DELETE FROM creature_addon WHERE guid=285196;
DELETE FROM creature_addon WHERE guid=285197;
DELETE FROM creature_addon WHERE guid=285198;
DELETE FROM creature_addon WHERE guid=285199;
DELETE FROM creature_addon WHERE guid=285200;
DELETE FROM creature_addon WHERE guid=285201;
DELETE FROM creature_addon WHERE guid=285202;
DELETE FROM creature_addon WHERE guid=285203;
DELETE FROM creature_addon WHERE guid=285204;
DELETE FROM creature_addon WHERE guid=285205;
DELETE FROM creature_addon WHERE guid=285206;
DELETE FROM creature_addon WHERE guid=285207;
DELETE FROM creature_addon WHERE guid=285208;
DELETE FROM creature_addon WHERE guid=285209;
DELETE FROM creature_addon WHERE guid=285210;
DELETE FROM creature_addon WHERE guid=285211;
DELETE FROM creature_addon WHERE guid=285212;
DELETE FROM creature_addon WHERE guid=285213;
DELETE FROM creature_addon WHERE guid=285214;
DELETE FROM creature_addon WHERE guid=285215;
DELETE FROM creature_addon WHERE guid=285216;
DELETE FROM creature_addon WHERE guid=285217;
DELETE FROM creature_addon WHERE guid=285218;
DELETE FROM creature_addon WHERE guid=285219;
DELETE FROM creature_addon WHERE guid=285220;
DELETE FROM creature_addon WHERE guid=285221;
DELETE FROM creature_addon WHERE guid=285222;
DELETE FROM creature_addon WHERE guid=285223;
DELETE FROM creature_addon WHERE guid=285224;
DELETE FROM creature_addon WHERE guid=285225;
DELETE FROM creature_addon WHERE guid=285226;
DELETE FROM creature_addon WHERE guid=248794;
DELETE FROM creature_addon WHERE guid=285227;
DELETE FROM creature_addon WHERE guid=285228;
DELETE FROM creature_addon WHERE guid=285229;
DELETE FROM creature_addon WHERE guid=285230;
DELETE FROM creature_addon WHERE guid=285231;
DELETE FROM creature_addon WHERE guid=248351;
DELETE FROM creature_addon WHERE guid=285232;
DELETE FROM creature_addon WHERE guid=285233;
DELETE FROM creature_addon WHERE guid=285234;
DELETE FROM creature_addon WHERE guid=285235;
DELETE FROM creature_addon WHERE guid=285236;
DELETE FROM creature_addon WHERE guid=285237;
DELETE FROM creature_addon WHERE guid=285238;
DELETE FROM creature_addon WHERE guid=285239;
DELETE FROM creature_addon WHERE guid=285240;
DELETE FROM creature_addon WHERE guid=285241;
DELETE FROM creature_addon WHERE guid=285242;
DELETE FROM creature_addon WHERE guid=285243;
DELETE FROM creature_addon WHERE guid=285244;
DELETE FROM creature_addon WHERE guid=285245;
DELETE FROM creature_addon WHERE guid=285246;
DELETE FROM creature_addon WHERE guid=285247;
DELETE FROM creature_addon WHERE guid=285248;
DELETE FROM creature_addon WHERE guid=285249;
DELETE FROM creature_addon WHERE guid=285250;
DELETE FROM creature_addon WHERE guid=285251;
DELETE FROM creature_addon WHERE guid=285252;
DELETE FROM creature_addon WHERE guid=285253;
DELETE FROM creature_addon WHERE guid=285254;
DELETE FROM creature_addon WHERE guid=248371;
DELETE FROM creature_addon WHERE guid=285255;
DELETE FROM creature_addon WHERE guid=285256;
DELETE FROM creature_addon WHERE guid=285257;
DELETE FROM creature_addon WHERE guid=285258;
DELETE FROM creature_addon WHERE guid=285259;
DELETE FROM creature_addon WHERE guid=285260;
DELETE FROM creature_addon WHERE guid=285261;
DELETE FROM creature_addon WHERE guid=285262;
DELETE FROM creature_addon WHERE guid=285263;
DELETE FROM creature_addon WHERE guid=246405;
DELETE FROM creature_addon WHERE guid=285264;
DELETE FROM creature_addon WHERE guid=248382;
DELETE FROM creature_addon WHERE guid=285265;
DELETE FROM creature_addon WHERE guid=285266;
DELETE FROM creature_addon WHERE guid=285267;
DELETE FROM creature_addon WHERE guid=285268;
DELETE FROM creature_addon WHERE guid=285269;
DELETE FROM creature_addon WHERE guid=285270;
DELETE FROM creature_addon WHERE guid=285271;
DELETE FROM creature_addon WHERE guid=285272;
DELETE FROM creature_addon WHERE guid=285273;
DELETE FROM creature_addon WHERE guid=285274;
DELETE FROM creature_addon WHERE guid=285275;
DELETE FROM creature_addon WHERE guid=285276;
DELETE FROM creature_addon WHERE guid=285277;
DELETE FROM creature_addon WHERE guid=285278;
DELETE FROM creature_addon WHERE guid=285279;
DELETE FROM creature_addon WHERE guid=285280;
DELETE FROM creature_addon WHERE guid=285281;
DELETE FROM creature_addon WHERE guid=248381;
DELETE FROM creature_addon WHERE guid=285282;
DELETE FROM creature_addon WHERE guid=285283;
DELETE FROM creature_addon WHERE guid=285284;
DELETE FROM creature_addon WHERE guid=285285;
DELETE FROM creature_addon WHERE guid=285286;
DELETE FROM creature_addon WHERE guid=285287;
DELETE FROM creature_addon WHERE guid=285288;
DELETE FROM creature_addon WHERE guid=285289;
DELETE FROM creature_addon WHERE guid=285290;
DELETE FROM creature_addon WHERE guid=285291;
DELETE FROM creature_addon WHERE guid=285292;
DELETE FROM creature_addon WHERE guid=246402;
DELETE FROM creature_addon WHERE guid=285293;
DELETE FROM creature_addon WHERE guid=285294;
DELETE FROM creature_addon WHERE guid=285295;
DELETE FROM creature_addon WHERE guid=285296;
DELETE FROM creature_addon WHERE guid=285297;
DELETE FROM creature_addon WHERE guid=285298;
DELETE FROM creature_addon WHERE guid=285299;
DELETE FROM creature_addon WHERE guid=285300;
DELETE FROM creature_addon WHERE guid=246412;
DELETE FROM creature_addon WHERE guid=285301;
DELETE FROM creature_addon WHERE guid=285302;
DELETE FROM creature_addon WHERE guid=285303;
DELETE FROM creature_addon WHERE guid=285304;
DELETE FROM creature_addon WHERE guid=285305;
DELETE FROM creature_addon WHERE guid=285306;
DELETE FROM creature_addon WHERE guid=285307;
DELETE FROM creature_addon WHERE guid=285308;
DELETE FROM creature_addon WHERE guid=285309;
DELETE FROM creature_addon WHERE guid=285310;
DELETE FROM creature_addon WHERE guid=285311;
DELETE FROM creature_addon WHERE guid=285312;
DELETE FROM creature_addon WHERE guid=285313;
DELETE FROM creature_addon WHERE guid=285314;
DELETE FROM creature_addon WHERE guid=285315;
DELETE FROM creature_addon WHERE guid=285317;
DELETE FROM creature_addon WHERE guid=285318;
DELETE FROM creature_addon WHERE guid=285319;
DELETE FROM creature_addon WHERE guid=285320;
DELETE FROM creature_addon WHERE guid=285321;
DELETE FROM creature_addon WHERE guid=285322;
DELETE FROM creature_addon WHERE guid=285323;
DELETE FROM creature_addon WHERE guid=285324;
DELETE FROM creature_addon WHERE guid=285325;
DELETE FROM creature_addon WHERE guid=285326;
DELETE FROM creature_addon WHERE guid=285327;
DELETE FROM creature_addon WHERE guid=246413;
DELETE FROM creature_addon WHERE guid=285328;
DELETE FROM creature_addon WHERE guid=285329;
DELETE FROM creature_addon WHERE guid=285330;
DELETE FROM creature_addon WHERE guid=286240;
DELETE FROM creature_addon WHERE guid=286241;
DELETE FROM creature_addon WHERE guid=286242;



-- 558 = 378 379 380 381 382 383 384 all
-- 562 = 378 379
-- 563 = 382 383 384
-- 570 = 381 382 383 384
-- 571 = 383 384
-- 573 = 379 381 382
-- 574 = 378,379 and 381 to 384. (phase 380 is angry for pirates=emote 431)


