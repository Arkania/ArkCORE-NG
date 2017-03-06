
-- mostly spawned from script
delete from creature where id=43775 and (guid<>9238 and guid<>9076);

-- all spawned from script
delete from creature where id=43788;

-- mostly spawned from script
delete from creature where id=431 and (guid<>44529 and guid<>44534 and guid<>44536);

SET @WP=443110;
SET @CGUID=44311;

UPDATE creature SET MovementType=2 WHERE guid=@CGUID;
delete from creature_addon where guid=@CGUID;
insert into creature_addon values (@CGUID,@WP,0,0,1,0,"");

DELETE FROM waypoint_data WHERE id=@WP;
INSERT INTO waypoint_data (id,point,position_x, position_y, position_z, orientation,delay, move_flag, action, action_chance) VALUES 
(@WP,0,-9043.169922,-3215.707764,109.085991,0.0,5000,0,0,100),
(@WP,1,-9023.294922,-3215.032227,108.153450,0.0,0,0,0,100),
(@WP,2,-9042.413086,-3212.061523,108.870804,0.0,3000,0,0,100),
(@WP,3,-9023.294922,-3215.032227,108.153450,0.0,0,0,0,100),
(@WP,4,-9041.407227,-3215.179199,109.028816,0.0,1000,0,0,100),
(@WP,5,-9023.294922,-3215.032227,108.153450,0.0,0,0,0,100),
(@WP,6,-9044.505859,-3218.041748,109.425125,0.0,6000,0,0,100),
(@WP,7,-9023.294922,-3215.032227,108.153450,0.0,0,0,0,100),
(@WP,8,-9038.426758,-3216.724609,109.254807,0.0,4000,0,0,100),
(@WP,9,-9023.294922,-3215.032227,108.153450,0.0,0,0,0,100);

delete from creature where guid in (60854,60855,60856,44485,44052,44560,45623,44302,45616,44471,44084,44093,44088,43496,44063,44526);

update creature_loot_template set ChanceOrQuestChance=-100 where entry=703 and item=3632;

update creature set MovementType=1, spawndist=30 where guid in (33839,33871,34258);
update creature set MovementType=1, spawndist=5 where guid in (34222,33760);

update creature_loot_template set ChanceOrQuestChance=-100 where entry=334 and item=3633;

update creature set spawntimesecs=600 where guid=44101 and id=334;

update creature_template set InhabitType=4 where entry=43533;

update creature set position_z=79.885, spawndist=25 where guid in (34432,34421) and id=43533;
update creature set position_z=79.885, spawndist=25 where guid in (34043) and id=43533;

update creature set MovementType=1, spawndist=8 where id=441;
update creature_template set AIName="" where entry=441;
delete from smart_scripts where entryorguid=441;

update creature_template_addon set auras="80673" where entry=4462;

delete from creature_questender where id=344 and quest=180;
insert into creature_questender values (344,180);

delete from creature_questender where id=344 and quest=169;
insert into creature_questender values (344,169);

delete from gameobject where guid in (22,23) and id=204388;
insert into gameobject (guid,id,position_x,position_y,position_z,orientation,spawntimesecs,animprogress,state) values
(22,204388,-8788.281250,-2143.973145,156.761856,2.732661,300,100,1),
(23,204388,-8814.999023,-2170.657227,150.620209,2.190738,300,100,1);

update quest_template set NextQuestIdChain=26514 where Id=26512;
update quest_template set NextQuestIdChain=26544 where Id=26514;
update quest_template set NextQuestIdChain=26545 where Id=26544;
update quest_template set NextQuestIdChain=0 where Id=26545;

update quest_template set SpecialFlags=0 where id=26508;

update gameobject_template set data8=26508 where entry=154357;

delete from creature_text where entry=344 and groupid between 0 and 3 and id=0;
insert into creature_text (entry,groupid,id,text,type,BroadcastTextID) Value 
(344,0,0,"Wir sind erledigt! Ich könnte eigentlich gleich eine Evakuierung ausrufen und Seenhain räumen, bevor die Orcs einmarschieren.",12,43262),
(344,1,0,"Und das, wo wir endlich diese verfluchte Brücke fertiggestellt haben! Welche Hoffnung gibt es schon, $n?",12,43263),
(344,2,0,"Welche Hoffnung, Oberst? Was könnte uns schon vor diesem drohenden Sturmangriff bewahren?",12,43265),
(344,3,0,"Keeshan lebt? Ich dachte, er sei gestorben.",12,43270);

delete from creature_text where entry=43221 and groupid between 0 and 5 and id=0;
insert into creature_text (entry,groupid,id,text,type,BroadcastTextID) Value 
(43221,0,0,"Es besteht Hoffnung, Solomon.",12,43264),
(43221,1,0,"Er diente 248 Einsätze in Folge während des Ersten, Zweiten und Dritten Krieges.",12,43266),
(43221,2,0,"Wurde gefangen vor fünf Jahren von einem Bataillon stinkender, schweinischer Schwarzfelsorcs knapp fünf Klicks außerhalb der südlichen EMZ.",12,43267),
(43221,3,0,"Gefoltert und als lebendes Urinal für junge Orckrieger missbraucht. FÜNF JAHRE LANG.",12,43268),
(43221,4,0,"JOHN J. KEESHAN.",12,43269),
(43221,5,0,"Er ist am Leben und hat die vergangenen fünf Monate als Verbannter in Seenhain verbracht. Oder habt Ihr es nicht gewusst? Genug geredet. Wir müssen Leute retten!",12,43271);

delete from creature_text where entry=43270 and groupid=0 and id=0;
insert into creature_text (entry,groupid,id,text,type,BroadcastTextID) Value 
(43270,0,0,"Ihr glaubt, diese Gitter könnten mich aufhalten? HA!",12,43296);

update creature_template set AIName="", ScriptName="npc_colonel_troteman_43221" where entry=43221;

update quest_template set SourceSpellId=80818 where Id=26567;


