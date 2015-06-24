
-- we need a scripted gossip
update creature_template set gossip_menu_id=0 where entry=38989;
update creature_text set BroadcastTextID=39243 where entry=38989;

UPDATE `creature_template` SET `npcflag`=3, `gossip_menu_id`=4047 WHERE `entry`=658; 

update creature_template set VehicleId=664, AIName="", ScriptName="npc_bloodtalon_thrasher_38991" where entry=38991;

update creature_text set BroadcastTextID=185 where entry=1402 and groupid=0 and id=2;
update creature_text set BroadcastTextID=183 where entry=1402 and groupid=0 and id=1;

