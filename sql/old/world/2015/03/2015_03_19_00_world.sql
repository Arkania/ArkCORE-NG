
UPDATE `creature_template` SET `npcflag`=641 WHERE `entry`=32024;
UPDATE `creature_template` SET `npcflag`=3201 WHERE `entry`=32028;
UPDATE `creature_template` SET `npcflag`=3201 WHERE `entry`=32765;
UPDATE `creature_template` SET `npcflag`=641 WHERE `entry`=32078;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=22551;
UPDATE `creature_template` SET `npcflag`=4194306 WHERE `entry`=22577;
UPDATE `creature_template` SET `npcflag`=129 WHERE `entry`=22557;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=21533;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=21560;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=21562;
UPDATE `creature_template` SET `unit_class`=1 WHERE `entry`=36357;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=28516;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=29021;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=28514;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=29024;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=29022;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=28515;
UPDATE `creature_template` SET `type`=7 WHERE `entry`=29023;
UPDATE `creature_template` SET `faction`=1801 WHERE `entry`=38095;
UPDATE `creature_template` SET `family`=45 WHERE `entry`=40009;
UPDATE `creature_template` SET `family`=45 WHERE `entry`=40014;
UPDATE `creature_template` SET `family`=45 WHERE `entry`=40016;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=49648;
UPDATE `creature_template` SET `type`=1 WHERE `entry`=49503;
UPDATE `creature_template` SET `type`=2 WHERE `entry`=43874;
UPDATE `creature_template` SET `unit_class`=8 WHERE `entry`=43876;
UPDATE `creature_template` SET `unit_class`=8 WHERE `entry`=45913;
UPDATE `creature_template` SET `faction`=14 WHERE `entry`=49990;
UPDATE `creature_template` SET `npcflag`=2 WHERE `entry`=48944;
UPDATE `creature_template` SET `family`=4 WHERE `entry`=52559;
UPDATE `creature_template` SET `type`=0 WHERE `entry`=52559;
UPDATE `creature_template` SET `family`=4 WHERE `entry`=52560;
UPDATE `creature_template` SET `type`=0 WHERE `entry`=52560;
UPDATE `creature_template` SET `family`=4 WHERE `entry`=52561;
UPDATE `creature_template` SET `type`=0 WHERE `entry`=52561;

delete from creature_equip_template where entry in (62415,65648,69975,69974,73190,61841,61838,61837,61836,61834,65153,69334);

update creature set spawndist=0 where guid in (774,34086,34444,61128);

delete from creature_addon where guid in (34523,9249,80705,26527);

update quest_template set RequiredSourceItemCount4=0 where Id=2459;
update quest_template set RequiredSourceItemCount2=0 where Id=13897;
update quest_template set RequiredSourceItemCount2=0 where Id=13946;
update quest_template set RequiredSkillId=0 where Id=3120;
update quest_template set RequiredItemId2=0, RequiredSourceItemCount1=0 where Id=10813;
update quest_template set RequiredItemId1=31463, RequiredItemCount1=1 where Id=10813;
update quest_template set RequiredSourceItemCount2=0 where Id=13892;
update quest_template set RequiredSourceItemCount2=0 where Id=13948;
update quest_template set RequiredSourceItemCount3=0 where Id=13565;
update quest_template set RequiredSourceItemCount2=0 where Id=13642;
update quest_template set SourceItemCount=1 where Id=10368;
update quest_template set RequiredSourceItemCount2=0 where Id=13580;
update quest_template set Flags=65544 where Id=28638;
update quest_template set RequiredNpcOrGoCount1=1, RequiredNpcOrGoCount2=1 where Id=24626;
update quest_template set RequiredSourceItemId3=0, RequiredSourceItemCount3=0 where Id=24626;
update quest_template set RequiredSourceItemId1=50053, RequiredSourceItemCount1=1 where Id=24626;
update quest_template set RequiredSourceItemCount4=0 where Id=24813;
update quest_template set PrevQuestId=0 where Id in (30011,30002,30001,30015);
update quest_template set NextQuestId=0 where Id in (30002,30001);
update quest_template set RequiredItemId1=0 where Id=26237;
update quest_template set Flags=8 where Id in (27612,28838);
delete from quest_template where Id=40000;
delete from creature_questender where id=56007 and quest=40000;
delete from creature_questender where id=56024 and quest=27092;
	
	
	
