

update creature set phaseIds=0, phaseGroup=418 where guid in (1773, 6683, 7017, 33751);

update gameobject set phaseIds=0, phaseGroup=418 where guid in (168994);

delete from spell_phase where spell_id in (68750, 72157, 72676, 73065, 73756, 74025);
INSERT INTO `spell_phase` VALUES (68750, 0, 180, 0, 661, 681, 'lost island quest phase 5');
INSERT INTO `spell_phase` VALUES (72157, 0, 181, 0, 661, 681, 'lost island quest phase 6');
INSERT INTO `spell_phase` VALUES (72676, 0, 182, 0, 661, 681, 'lost island quest phase 7');
INSERT INTO `spell_phase` VALUES (73065, 0, 183, 0, 661, 681, 'lost island quest phase 8');
INSERT INTO `spell_phase` VALUES (73065, 1, 183, 0, 659, 682, 'lost island quest phase 8 burning');
INSERT INTO `spell_phase` VALUES (73756, 0, 184, 0, 659, 682, 'lost island quest phase 9 burning');
INSERT INTO `spell_phase` VALUES (74025, 0, 185, 0, 659, 682, 'lost island quest phase 10 burning');

UPDATE creature_text SET emote=25 WHERE entry=38432 AND groupid=2 AND id=0;


