-- fix issue #193

DELETE FROM creature WHERE guid=196741;
INSERT INTO creature VALUES 
(196741, 28451, 571, 0, 0, 1, "169", 0, 0, 0, 6487.6, 5076.98, -63.2429, 5.84007, 300, 0, 0, 35310, 0, 0, 0, 0, 0);

delete from smart_scripts where entryorguid=28451;
delete from smart_scripts where entryorguid=28468;

delete from npc_spellclick_spells where npc_entry in (28451, 28468);



