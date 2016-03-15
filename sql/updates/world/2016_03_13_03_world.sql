

delete from creature where guid=240523 and id=35873;

DELETE FROM phase_area WHERE areaId=4714 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 0, 14078, 14091, 75, 1, 0, "Gilneas phase 1");

DELETE FROM phase_area WHERE areaId=4714 AND entry=1;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4714, 1, 14091, 14159, 66, 11, 0, "Gilneas phase 2");

DELETE FROM phase_area WHERE areaId=4755 AND entry=0;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 0, 14078, 14091, 75, 1, 0, "Gilneas phase 1");

DELETE FROM phase_area WHERE areaId=4755 AND entry=1;
INSERT INTO phase_area (areaId, entry, quest_start, quest_end, quest_start_status, quest_end_status, flags, comment) VALUES 
(4755, 1, 14091, 14159, 66, 11, 0, "Gilneas phase 2");

update npc_text set BroadcastTextID0=36065 where ID=14838;

update npc_text set BroadcastTextID0=36076 where ID=14848;

SET @GOSSIP=10696;
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

SET @ID=1;
delete from conditions where SourceTypeOrReferenceId=15 and ConditionTypeOrReference=15 and SourceGroup=@GOSSIP and SourceEntry=@ID;
insert into conditions values 
(15, @GOSSIP, @ID, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "enable gossip only for druid class");

SET @GOSSIP=10697;
SET @TEXT_YES=14838;
SET @TEXT_NO=14839;
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

SET @GOSSIP=10700;
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

update gossip_menu_option set npc_option_npcflag=16 where menu_id=@GOSSIP and id=@ID;

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

SET @GOSSIP=10698;
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

SET @GOSSIP=10694;
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
(14, @GOSSIP, @TEXT_YES, 0, 0, 15, 0, @FLAG_YES, 0, 0, 0, 0, 0, "", "text trainer warrier"),
(14, @GOSSIP, @TEXT_NO, 0, 0, 15, 0,  @FLAG_NO , 0, 0, 0, 0, 0, "", "text trainer no warrier");

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

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Lorna Crowley im Militärviertel in Gilneas zurück." WHERE Id=14204;

delete from creature where guid=250227 and id=35370;

UPDATE creature_template SET npcflag=npcflag | 2 WHERE entry=47972;

delete from spell_script_names where spell_id=67805; --	spell_attack_lurker_67805



