
UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Kand Sandsucher zurück." WHERE Id=27673;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gut gemacht, Junge! Geht nun zu den Scheiben und lernt alles was Ihr könnt!", CompletedText_loc3="Kehrt zu Oberausgrabungsleiter Durdin zurück." WHERE Id=27677;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Oberausgrabungsleiter Durdin zurück." WHERE Id=27680;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Gut gemacht, Junge! Geht nun zu den Scheiben und lernt alles was Ihr könnt!", CompletedText_loc3="Kehrt zu Oberausgrabungsleiter Durdin zurück." WHERE Id=27677;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Oberausgrabungsleiter Durdin zurück." WHERE Id=27680;

update creature_template set AIName="", ScriptName="npc_jadespine_basilisk_4863" where entry=4863;
update creature_template set AIName="", ScriptName="npc_stonekeepers_4857" where entry=4857;
update creature_template set AIName="", ScriptName="npc_earthen_guardian_7076" where entry=7076;
update creature_template set AIName="", ScriptName="npc_earthen_custodian_7309" where entry=7309;
update creature_template set AIName="", ScriptName="npc_vault_warder_10120" where entry=10120;

update gameobject_template set AIName="", ScriptName="go_keystone_chamber_124371" where entry=124371;
update gameobject_template set AIName="", ScriptName="go_altar_of_the_keepers_130511" where entry=130511;
update gameobject_template set AIName="", ScriptName="go_altar_of_archaedas_133234" where entry=133234;

delete from areatrigger_scripts where entry=822;
insert into areatrigger_scripts values (822, "at_map_chamber_822");

delete from event_scripts where id=2268;

--

DELETE FROM pool_template WHERE entry=14143;
INSERT INTO pool_template VALUES (14143,1,"MP Earthen Stonecarver");

DELETE FROM pool_template WHERE entry=14144;
INSERT INTO pool_template VALUES (14144,1,"PP Earthen Stonecarver");

DELETE FROM pool_pool WHERE pool_id=14144 AND mother_pool=14143;
INSERT INTO pool_pool VALUES (14144,14143,0,"Pool Earthen Stonecarver");

DELETE FROM pool_creature WHERE guid=147386;
INSERT INTO pool_creature VALUES (147386,14144,0,"Earthen Stonecarver");

DELETE FROM pool_creature WHERE guid=147388;
INSERT INTO pool_creature VALUES (147388,14144,0,"Earthen Stonebreaker");

--

DELETE FROM pool_template WHERE entry=14143;
INSERT INTO pool_template VALUES (14143,1,"MP Earthen Stonecarver");

DELETE FROM pool_template WHERE entry=14144;
INSERT INTO pool_template VALUES (14144,1,"PP Earthen Stonecarver");

DELETE FROM pool_pool WHERE pool_id=14144 AND mother_pool=14143;
INSERT INTO pool_pool VALUES (14144,14143,0,"Pool Earthen Stonecarver");

DELETE FROM pool_creature WHERE guid=147385;
INSERT INTO pool_creature VALUES (147385,14144,0,"Earthen Stonecarver");

DELETE FROM pool_creature WHERE guid=147387;
INSERT INTO pool_creature VALUES (147387,14144,0,"Earthen Stonebreaker");


