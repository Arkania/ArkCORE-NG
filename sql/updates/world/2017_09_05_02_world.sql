
UPDATE quest_template SET QuestGiverPortrait=0 WHERE Id=28826;

delete from creature where guid in (26874,51722,51749,51750,51751,51752,51753,51754,51755,51756,51757,51758, 49430);

delete from creature_addon where guid in (26874,51722,51749,51750,51751,51752,51753,51754,51755,51756,51757,51758, 49430);

update creature set phaseId=169, phaseGroup=0 where guid in (1112, 1176, 48894, 49026, 49800);

update gameobject set phaseId=0, phaseGroup=368 where id in (208437, 208438);

update creature_addon set bytes1=33554434, bytes2=1 where guid in (500032, 500033, 500036); 

update creature_addon set bytes1=33554433, bytes2=1 where guid in (500034, 500035, 500037); 

delete from creature where id=52654 and guid=53432;

update creature_template set faction=35 where entry=52654;

update creature_template set InhabitType=4 where entry=52806;

update transports set phaseId=171 where guid=40;  -- 203466

update transports set phaseId=171 where guid=42;  -- 197195

update creature set phaseId=171 where map=738; -- horde ship to vashj'ir

update creature set phaseId=171 where map=674; -- alliance ship to vashj'ir

update creature set modelid=21342, phaseId=171, phaseGroup=0 where id=32520 and guid=49800;

update creature set modelid=21342, phaseId=171, phaseGroup=0 where id=32520 and guid=43007;

UPDATE creature_template SET ScriptName="npc_captain_taylor_42103" WHERE entry=42103;

UPDATE creature_template SET ScriptName="npc_stormwind_soldier_42021" WHERE entry=42021;
