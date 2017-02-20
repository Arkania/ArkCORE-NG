

DELETE FROM pool_template WHERE entry=349;
DELETE FROM pool_template WHERE entry=348;
DELETE FROM pool_pool WHERE pool_id=349 AND mother_pool=348;
DELETE FROM pool_creature WHERE guid in (245984, 286620, 286624);

INSERT INTO pool_template VALUES 
(349, 1, "Auto added description");

INSERT INTO pool_template VALUES 
(348, 1, "Auto added description");

INSERT INTO pool_pool VALUES 
(349, 348, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(245984, 349, 33, "Auto added description"),
(286620, 349, 33, "Auto added description"),
(286624, 349, 34, "Auto added description");

DELETE FROM pool_template WHERE entry=351;
DELETE FROM pool_template WHERE entry=350;
DELETE FROM pool_pool WHERE pool_id=351 AND mother_pool=350;
DELETE FROM pool_creature WHERE guid in (245995, 286617);

INSERT INTO pool_template VALUES 
(351, 1, "Auto added description");

INSERT INTO pool_template VALUES 
(350, 1, "Auto added description");

INSERT INTO pool_pool VALUES 
(351, 350, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(245995, 351, 50, "Auto added description"),
(286617, 351, 50, "Auto added description");

DELETE FROM pool_template WHERE entry=353;
DELETE FROM pool_template WHERE entry=352;
DELETE FROM pool_pool WHERE pool_id=353 AND mother_pool=352;
DELETE FROM pool_creature WHERE guid in (246006, 286618, 286621);

INSERT INTO pool_template VALUES 
(353, 1, "Auto added description");

INSERT INTO pool_template VALUES 
(352, 1, "Auto added description");

INSERT INTO pool_pool VALUES 
(353, 352, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(246006, 353, 33, "Auto added description"),
(286618, 353, 33, "Auto added description"),
(286621, 353, 34, "Auto added description");

DELETE FROM pool_template WHERE entry=355;
DELETE FROM pool_template WHERE entry=354;
DELETE FROM pool_pool WHERE pool_id=355 AND mother_pool=354;
DELETE FROM pool_creature WHERE guid in (245991, 286616);

INSERT INTO pool_template VALUES 
(355, 1, "Auto added description");

INSERT INTO pool_template VALUES 
(354, 1, "Auto added description");

INSERT INTO pool_pool VALUES 
(355, 354, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(245991, 355, 50, "Auto added description"),
(286616, 355, 50, "Auto added description");

DELETE FROM pool_template WHERE entry=357;
DELETE FROM pool_template WHERE entry=356;
DELETE FROM pool_pool WHERE pool_id=357 AND mother_pool=356;
DELETE FROM pool_creature WHERE guid in (245988, 245989, 246003, 286615, 286619);

INSERT INTO pool_template VALUES 
(357, 2, "Auto added description");

INSERT INTO pool_template VALUES 
(356, 2, "Auto added description");

INSERT INTO pool_pool VALUES 
(357, 356, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(245988, 357, 20, "Auto added description"),
(245989, 357, 20, "Auto added description"),
(246003, 357, 20, "Auto added description"),
(286615, 357, 20, "Auto added description"),
(286619, 357, 20, "Auto added description");

DELETE FROM pool_template WHERE entry=360;
DELETE FROM pool_template WHERE entry=359;
DELETE FROM pool_pool WHERE pool_id=360 AND mother_pool=359;
DELETE FROM pool_creature WHERE guid in (246004, 286622, 286623);

INSERT INTO pool_template VALUES 
(360, 1, "Auto added description");

INSERT INTO pool_template VALUES 
(359, 1, "Auto added description");

INSERT INTO pool_pool VALUES 
(360, 359, 100, "Auto added description");

INSERT INTO pool_creature VALUES 
(246004, 360, 33, "Auto added description"),
(286622, 360, 33, "Auto added description"),
(286623, 360, 34, "Auto added description");







