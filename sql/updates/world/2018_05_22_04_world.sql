
UPDATE creature_text SET text="No more nice ogre! You hurt Mogor!!", BroadcastTextID=15483 WHERE entry=18069 AND groupid=5 AND id=0;

UPDATE locales_creature_text SET text_loc3="Kein netter Oger mehr! Ihr Mogor weh tun!!" WHERE entry=18069 AND groupid=5 AND id=0;


UPDATE creature_text SET type=41, BroadcastTextID=0 WHERE entry=29 AND groupid=1 AND id=0;

UPDATE locales_creature_text SET text_loc3="Lasst die Schlacht um den Strand der Uralten beginnen!" WHERE entry=29 AND groupid=1 AND id=0;


UPDATE creature_text SET language=7, BroadcastTextID=1279 WHERE entry=3843 AND groupid=0 AND id=0;

UPDATE creature_text SET language=7, BroadcastTextID=1282 WHERE entry=3843 AND groupid=1 AND id=0;

UPDATE creature_text SET language=7, BroadcastTextID=1283 WHERE entry=3843 AND groupid=2 AND id=0;

UPDATE creature_text SET language=7, BroadcastTextID=1284 WHERE entry=3843 AND groupid=3 AND id=0;

UPDATE creature_text SET language=7, BroadcastTextID=1285 WHERE entry=3843 AND groupid=4 AND id=0;

UPDATE locales_creature_text SET text_loc3="Die Jahre waren unbarmherzig zu dir und zu mir, mein Herz, aber sei versichert, ich bin es wirklich, und nach so langer Zeit sind wir endlich wieder vereint." WHERE entry=3843 AND groupid=0 AND id=0;

UPDATE locales_creature_text SET text_loc3="Lass es nicht dein Herz betrüben, Geliebter. Du hast mich aus der Sklaverei befreit und dafür liebe ich dich umso mehr." WHERE entry=3843 AND groupid=1 AND id=0;

UPDATE locales_creature_text SET text_loc3="Leider kann sogar dies nicht lange dauern... Die Bindungen, die mich in dieser Welt halten, werden schwächer und ziehen mich fort..." WHERE entry=3843 AND groupid=2 AND id=0;

UPDATE locales_creature_text SET text_loc3="Lebe wohl, Cerellean, bis wir wieder vereint sind..." WHERE entry=3843 AND groupid=3 AND id=0;

UPDATE locales_creature_text SET text_loc3="%s flüstert mit leiser Stimme, die im Nebel verklingt: \"Wisse, dass ich dich immer lieben werde...\"" WHERE entry=3843 AND groupid=4 AND id=0;

UPDATE quest_template SET PrevQuestId=931 WHERE id=2399;

UPDATE quest_template SET PrevQuestId=927 WHERE id=941;

UPDATE quest_template SET PrevQuestId=937, NextQuestId=0 WHERE id=940;

UPDATE quest_template SET NextQuestId=0 WHERE id=488;

UPDATE quest_template SET PrevQuestId=489 WHERE id=932;

UPDATE quest_template SET PrevQuestId=489 WHERE id=13946;






