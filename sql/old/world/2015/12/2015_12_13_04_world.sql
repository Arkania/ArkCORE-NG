
-- hyjal
UPDATE quest_template SET PrevQuestId=25600 WHERE Id=25612;
UPDATE quest_template SET PrevQuestId=25600 WHERE Id=25611;
UPDATE quest_template SET PrevQuestId=25577 WHERE Id=25599;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Jordan Olafson im Amboss des Feuers zurück.", QuestGiverTextWindow_loc3="Schwelende Kerne zerstört", QuestGiverTargetName_loc3="Schwelende Kerne zerstört" WHERE Id=25577;

UPDATE quest_template SET Flags=131208 WHERE Id=25577;

update npc_text set BroadcastTextID0=40900 where ID=15955;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Yargra Schwarznarbe im Amboss des Feuers zurück.", QuestGiverTextWindow_loc3="Arbeiter der Dunkeleisenzwerge", QuestGiverTargetName_loc3="Arbeiter der Dunkeleisenzwerge" WHERE Id=25576;

UPDATE locales_quest SET EndText_loc3="", CompletedText_loc3="Kehrt zu Jordan Olafson im Amboss des Feuers zurück." WHERE Id=25600;

delete from creature where id=40838;
insert into creature value
(116801, 40838, 1, 1, 1, 32103, 1, 4995.06, -2204.85, 1126.9, 5.18854, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116802, 40838, 1, 1, 1, 32103, 1, 4978.83, -2104.28, 1144.84, 3.89208, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116803, 40838, 1, 1, 1, 32098, 1, 4997.3, -2099.36, 1144.94, 6.17846, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116804, 40838, 1, 1, 1, 32098, 1, 5041.13, -2159.26, 1136.48, 4.64909, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116805, 40838, 1, 1, 1, 32103, 1, 5067.05, -2142.26, 1136.61, 2.88757, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116806, 40838, 1, 1, 1, 32101, 1, 5042.7, -2153.63, 1136.71, 0.155005, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116807, 40838, 1, 1, 1, 32101, 1, 4993.47, -2171.21, 1133.31, 5.95157, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116808, 40838, 1, 1, 1, 32098, 1, 4930.65, -2180.8, 1124.81, 5.63741, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116809, 40838, 1, 1, 1, 32101, 1, 5080.77, -2143.51, 1136.61, 3.65564, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116810, 40838, 1, 1, 1, 32098, 1, 4942, -2169.63, 1124.69, 2.65581, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116811, 40838, 1, 1, 1, 32103, 1, 5094.2, -2192.04, 1136.69, 3.33358, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116812, 40838, 1, 1, 1, 32101, 1, 4952.65, -2202.2, 1117.16, -0.304549, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116813, 40838, 1, 1, 1, 32103, 1, 5012.25, -2043.12, 1148.98, 2.17831, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116814, 40838, 1, 1, 1, 32101, 1, 5086.95, -2196.08, 1136.61, 1.48353, 300, 0, 0, 30951, 0, 0, 0, 0, 0),
(116815, 40838, 1, 1, 1, 32098, 1, 5028.83, -2152.6, 1136.51, 5.60251, 300, 0, 0, 30951, 0, 0, 0, 0, 0);

UPDATE creature_template SET mindmg=464, maxdmg=604, attackpower=708, minrangedmg=353, maxrangedmg=512, rangedattackpower=112, Health_mod=1 WHERE entry=40838;

UPDATE creature_template SET mindmg=464, maxdmg=604, attackpower=708, dmg_multiplier=1, minrangedmg=353, maxrangedmg=512, rangedattackpower=112, Health_mod=1 WHERE entry=40841;

UPDATE creature_template SET mindmg=510, maxdmg=722, attackpower=804, minrangedmg=421, maxrangedmg=613, rangedattackpower=129, Health_mod=1 WHERE entry=40844;

UPDATE creature_template SET mindmg=206, maxdmg=268, attackpower=281, dmg_multiplier=7.5, minrangedmg=206, maxrangedmg=268, rangedattackpower=281 WHERE entry=40845;


