-- Quest 28102 - Fight the power / Add Shadowstalkers to kill count
UPDATE creature_template SET KillCredit1=7106 WHERE entry=7110;

-- Quest 28460 - Threat of the Winterspring / Update creature kill credit
UPDATE creature_template SET KillCredit1=48586 WHERE entry IN (7440,7441,7442,10738);
