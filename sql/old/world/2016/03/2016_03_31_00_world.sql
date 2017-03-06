
-- fix issue #110

UPDATE creature_template SET gossip_menu_id=0, AIName="", ScriptName="npc_shin_stonepillar_39380" WHERE entry=39380;

UPDATE locales_quest SET QuestGiverTextWindow_loc3="Der Kodo", QuestGiverTargetName_loc3="Der Kodo" WHERE Id=25205;

UPDATE gossip_menu_option SET OptionBroadcastTextID=39443, option_id=1,npc_option_npcflag=1 WHERE menu_id=11209;

UPDATE creature_template SET spell1=73851 WHERE entry=39364;

UPDATE creature_template SET AIName="", ScriptName="npc_the_wolf_39364" WHERE entry=39364;

delete from creature_text where entry=39364 and groupid in (0, 1, 2, 3, 4);
insert into creature_text values 
(39364, 0, 0, "One day, The Wolf was very hungry, so he ran east to look for some food.", 42, 0, 100, 0, 0, 0, "", 39438),
(39364, 1, 0, "He happened upon a pair of battling kodos.$bClever as he was, The Wolf decided to wait for one to defeat the other.", 42, 0, 100, 0, 0, 0, "", 39439),
(39364, 2, 0, "When the weaker Kodo died, The Wolf approached and tried to eat it.", 42, 0, 100, 0, 0, 775, "", 39440),
(39364, 3, 0, "The remaining Kodo, angry at The Wolf's impetuousness,$bswiftly killed The Wolf before he had a chance to eat.", 42, 0, 100, 0, 0, 0, "", 39441),
(39364, 4, 0, "The Wolf ran and ran, looking for an easy meal.", 42, 0, 100, 0, 0, 0, "", 39444),
(39364, 4, 1, "He was hungry for kodo meat.", 42, 0, 100, 0, 0, 0, "", 39445),
(39364, 4, 2, "The Wolf was lazy, and didn't want to work for his meal.", 42, 0, 100, 0, 0, 0, "", 39446),
(39364, 4, 3, "The more he ran, the more his stomach growled.", 42, 0, 100, 0, 0, 0, "", 39447),
(39364, 4, 4, "The Wolf did not care for raptor meat.", 42, 0, 100, 0, 0, 0, "", 39448),
(39364, 4, 5, "The Wolf found scorpid meat to be too bitter.", 42, 0, 100, 0, 0, 0, "", 39449),
(39364, 4, 6, "The Wolf had grown tired of eating boar meat.", 42, 0, 100, 0, 0, 0, "", 39450),
(39364, 4, 7, "He scoured the sands of Durotar, hunting for his prey.", 42, 0, 100, 0, 0, 0, "", 39451);

delete from creature where id=39365;
insert into creature values 
(137758, 39365, 1, 1, 1, 0, 0, 1327.74, -4772.847, 24.85069, 2.583087, 120, 0, 0, 42, 0, 0, 0, 0, 0),
(137766, 39365, 1, 1, 1, 0, 0, 1321.635, -4770.257, 24.10884, 5.77704, 120, 0, 0, 42, 0, 0, 0, 0, 0);

delete from spell_script_names where spell_id=73868;
insert into spell_script_names values 
(73868, "spell_rumbling_hooves_73868");

UPDATE creature_template SET AIName="", ScriptName="npc_the_kodo_39365" WHERE entry=39365;

