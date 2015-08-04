
update creature set MovementType=1 where guid in (34539, 145622, 145630, 145639, 145663, 145668, 145671, 145675, 145685, 145694, 145718, 145725, 145729, 145732, 145751, 145752, 145768, 145777, 145787, 145790, 145797, 145818, 145821, 145837, 145926, 145946, 145967, 145976, 145980, 145992, 146004, 189003);

UPDATE `creature_template` SET `faction`=14 WHERE `entry`=48821;

update npc_text set BroadcastTextID0=15708 where Id=9478;

update creature_template set AIName="" where entry=42698;
update creature_template set AIName="" where entry=643;
update creature_template set AIName="" where entry=48832;
update creature_template set AIName="" where entry=479010;
update creature_template set AIName="" where entry=29021;
update creature_template set AIName="" where entry=29024;
update creature_template set AIName="" where entry=29022;
update creature_template set AIName="" where entry=29023;
update creature_template set AIName="" where entry=46209;
update creature_template set AIName="" where entry=48936;

update creature set MovementType=0 where guid=268650;

delete from command where name="reload creature_onkill_reward";
delete from command where name="credits";

update waypoint_scripts set dataint=7194 where id=39;
update waypoint_scripts set dataint=7193 where id=40;
update waypoint_scripts set dataint=7191 where id=41;
update waypoint_scripts set dataint=10128 where id=42;
update waypoint_scripts set dataint=6406 where id=43;
update waypoint_scripts set dataint=6405 where id=44;
update waypoint_scripts set dataint=10158 where id=45;
update waypoint_scripts set dataint=10155 where id=46;
update waypoint_scripts set dataint=10146 where id=47;
update waypoint_scripts set dataint=12835 where id=67;
update waypoint_scripts set dataint=12832 where id=70;
update waypoint_scripts set dataint=12833 where id=71;
update waypoint_scripts set dataint=14565 where id=72;
update waypoint_scripts set dataint=14567 where id=73;
update waypoint_scripts set dataint=14217 where id=74;
update waypoint_scripts set dataint=15373 where id=112;
update waypoint_scripts set dataint=41824 where id=142;
update waypoint_scripts set dataint=1 where id=143;
update waypoint_scripts set dataint=16059 where id=160;
update waypoint_scripts set dataint=16977 where id=170;
update waypoint_scripts set dataint=16974 where id=171;

delete from smart_scripts where entryorguid in (40273, 40290, 40291, 41073, 39381, 39414, 39415, 39854, 39855, 39870, 39890);
delete from smart_scripts where entryorguid in (39892, 39900, 39909, 39954, 39956, 39962, 40166, 40167, 40268, 40270, 40272);
delete from smart_scripts where entryorguid in (43778, 47162, 47296, 47297, 47626, 47739, 49541, 32933, 32934);

update creature_template set AIName="SmartAI" where entry in (42698, 46209, 48832, 48936, 29021, 29022, 29023, 29024);




