
-- northern strangethorn
delete from gameobject where guid=184345 and id=204828;

update creature set position_x=-11306.23, position_y=-207.04, position_z=75.78, orientation=1.5877  where guid=56291 and id=43885;

update creature set position_x=-11345.84, position_y=-222.78, position_z=75.67, orientation=1.0222  where guid=56292 and id=43886;

update creature set phaseMask=2 where guid=54548 and id=52753;

update creature_template_addon set bytes1=0, emote=0 where entry=43921;

delete from creature_text where entry in (43919, 43921) and groupid=0 and id=0;
insert into creature_text values 
(43919, 0, 0, "Woo hoo.", 12, 0, 100, 0, 0, 0, "osborn say", 44282),
(43921, 0, 0, "Freedom!  Sweet, sweet freedom!", 12, 0, 100, 0, 0, 0, "berrin say", 44283);

update gameobject_template set AIName="", ScriptName="go_kurzen_cage_204828" where entry=204828;

update creature set spawntimesecs=120 where guid in (26643, 26642, 26546);

update gameobject set spawntimesecs=120 where guid=157202 and id=204828;
