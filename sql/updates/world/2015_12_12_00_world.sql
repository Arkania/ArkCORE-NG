
update creature_template set AIName="", ScriptName="npc_marshal_mcbride_197" where entry=197;
delete from creature_text where entry=197 and groupid=1;

update creature_template set AIName="", ScriptName="npc_hogger_448" where entry=448;
delete from creature_text where entry=448;
insert into creature_text values
(448, 0, 0, "More bones to gnaw on...", 12, 0, 100, 0, 0, 0, "Hogger Agro Say 1", 46596),
(448, 0, 1, "Grrrr... fresh meat!", 12, 0, 100, 0, 0, 0, "Hogger Agro Say 2", 1870),
(448, 1, 0, "Yipe! Help Hogger", 14, 0, 100, 0, 0, 0, "Hogger Script", 46936),
(448, 2, 0, "Grrr...", 12, 0, 100, 0, 0, 0, "Hogger Script", 46937),
(448, 3, 0, "Nooooo...", 12, 0, 100, 0, 0, 0, "Hogger Script", 46938),
(448, 4, 0, "Hogger is eating! Stop him!", 12, 0, 100, 0, 0, 0, "Hogger Script", 46939),
(448, 5, 0, "No hurt Hogger!", 14, 0, 100, 0, 0, 0, "Hogger Script", 47000);

update creature_template set AIName="", ScriptName="" where entry=46942;
delete from creature_text where entry=46942;
insert into creature_text values
(46942, 0, 0, "Hold your blade, adventurer!", 14, 0, 100, 0, 0, 0, "", 47004),
(46942, 1, 0, "This beast leads the Riverpaw gnoll gang and may be the key to ending gnoll aggression in Elwynn!", 12, 0, 100, 0, 0, 0, "", 47007),
(46942, 2, 0, "We're taking him into custody in the name of King Varian Wrynn.", 12, 0, 100, 0, 0, 0, "", 47008),
(46942, 3, 0, "Take us to the Stockades, Andromath.", 12, 0, 100, 0, 0, 0, "", 47009);

update creature_template set AIName="", ScriptName="" where entry=46943;
delete from creature_text where entry=46943;
insert into creature_text values
(46943, 0, 0, "WoW!", 14, 0, 100, 0, 0, 0, "", 47006),
(46943, 1, 0, "General Jonathan Marcus!", 14, 0, 100, 0, 0, 0, "", 47005);

update creature_template set AIName="", ScriptName="" where entry=42413;
delete from creature_text where entry=42413 and groupid=1;
insert into creature_text values
(42413, 1, 0, "General Jonathan Marcus!", 14, 0, 100, 0, 0, 0, "", 47005);


				