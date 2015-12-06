

-- thanks to roger..
 /*!40101 SET NAMES utf8 */;
 UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=33266;
 delete from smart_scripts where entryorguid=33266;
 insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('33266','0','0','1','8','0','100','0','62644','0','1000','1000','33','33266','0','0','0','0','0','7','0','0','0','0','0','0','0','kill credit');
 insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('33266','0','1','2','61','0','100','0','0','0','0','0','17','378','0','0','0','0','0','1','0','0','0','0','0','0','0','on smart link - cast emote talk');
 insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('33266','0','2','3','61','0','100','0','0','0','0','0','46','15','0','0','0','0','0','1','0','0','0','0','0','0','0','On smart link - move away');
 insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('33266','0','3','4','61','0','100','0','0','0','0','0','1','0','2000','0','0','0','0','1','0','0','0','0','0','0','0','On smart link - say random from group.');
 insert into `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) values('33266','0','4','0','61','0','100','0','0','0','0','0','41','2000','0','0','0','0','0','1','0','0','0','0','0','0','0','On smart link - mob despawn'); 
  
 delete from gameobject where guid=19263 and id=146084;
  
 delete from gameobject where guid=19763 and id=141070;
 delete from gameobject where guid=16479 and id=141072;
 delete from gameobject where guid=25478 and id=141073;
 delete from gameobject where guid=25485 and id=141074;

 update gameobject set state=1 where guid=189748 and id=141070; 
 update gameobject set state=1 where guid=189749 and id=141071; 
 update gameobject set state=1 where guid=189751 and id=141072; 
 update gameobject set state=1 where guid=189742 and id=141073; 
 update gameobject set state=1 where guid=189743 and id=141074; 

