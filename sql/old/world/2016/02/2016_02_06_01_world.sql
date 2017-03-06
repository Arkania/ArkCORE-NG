

UPDATE quest_template SET Method=2 WHERE Id=24917;

UPDATE locales_quest SET OfferRewardText_loc3="Jawohl. Ich kenne diese Klinge... und ich werde mich bis ans Ende meiner Tage an sie erinnern - an jenen Zeitpunkt, der für immer verloren sein wird.$B$BIhr habt mir einen großen Dienst erwiesen, Held. Ich möchte Euch etwas von den Frosterben zum Geschenk machen. Verfahrt damit wie Euch beliebt, doch vergesst nicht jene, die bei dieser kolossalen Heldentat an Eurer Seite standen.", RequestItemsText_loc3="Was hast du da, $R?" WHERE Id=24917;

UPDATE quest_template SET Method=2, RequiredMinRepFaction=1156, RequiredMinRepValue=6000, Flags=8200 WHERE Id in (24819, 24820, 24821, 24822, 24836, 24837, 24838, 24839, 24840, 24841, 24842, 24843, 24844, 24845, 24846, 24847, 25246, 25247, 25248, 25249);

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Ein tiefes Gefühl der Angst überkommt Euch, als die Flamme die Einzelteile verschlingt." WHERE Id=24545;

UPDATE locales_quest SET OfferRewardText_loc3="Dann ist es also endlich vollbracht.$B$BMögen die Völker Azeroths unserer Taten hier ewig gedenken. Mögen die Opfer so vieler für immer in ihren Herzen brennen. Mögen sie im Angesicht großer Bedrohungen nie die Bereitschaft verlieren, ihr Leben für andere zu riskieren.", QuestGiverTextWindow_loc3="Der Lichkönig", QuestGiverTargetName_loc3="Der Lichkönig" WHERE Id=24748;

UPDATE quest_template SET Method=2 WHERE Id=24549;

UPDATE locales_quest SET OfferRewardText_loc3="Ich gratuliere, $C.$B$BEntgegen aller unüberwindbaren Hindernisse habt Ihr den Sturm überstanden.$B$BIch vertraue darauf, dass Ihr Eure Belohnung als angemessen empfinden werdet..." WHERE Id=24549;

UPDATE locales_quest SET EndText_loc3="", OfferRewardText_loc3="Das sollte genügen, $C.$B$BKommt zu mir, wenn Schattenschneide mit ihren Kräften ausgestattet wurde, und ich werde versuchen, sie zu vervollständigen.", RequestItemsText_loc3="Habt Ihr die Splitter des Frostthrons besorgt, $C?" WHERE Id=24548;

UPDATE quest_template SET RequestItemsText="Have you obtained the shards of the frozen throne, $C?" WHERE Id=24548;

UPDATE locales_quest SET OfferRewardText_loc3="Die Axt hat die Mächte aufgesogen, $R, und die Schmiede ist bald bereit für die Erschaffung von Schattengram..." WHERE Id=24757;

UPDATE quest_template SET RequiredNpcOrGo1=37955, RequiredNpcOrGoCount1=1 WHERE Id=24756;

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht, $C.$B$BSchattengram ist fast in Reichweite." WHERE Id=24756;

UPDATE quest_template SET RequiredNpcOrGo1=36678, RequiredNpcOrGoCount1=1 WHERE Id=24749;

UPDATE locales_quest SET OfferRewardText_loc3="Gut gemacht, $C!$B$BWir kommen dem Abschluss unserer Arbeit immer näher." WHERE Id=24749;

UPDATE locales_quest SET Objectives_loc3="Hochlord Darion Mograine möchte, dass Ihr mit Schattenschneide 50 Diener des Lichkönigs in der Eiskronenzitadelle tötet. Die Seelen sind nur in den Schwierigkeitsgraden für 10 oder 25 Mann erhältlich." WHERE Id=24547;

UPDATE quest_template SET Method=2, Type=62 WHERE Id=24743;



