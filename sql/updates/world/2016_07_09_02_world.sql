
update creature set spawntimesecs=90 where id in (38218, 38465, 38466, 38426, 38469, 38470);

update creature_equip_template set itemEntry1=3364, itemEntry3=2552 where entry=38221 and id=1;

delete from creature_equip_template where entry=38210 and id=1;
insert into creature_equip_template values 
(38210, 1, 2827, 0, 36629);	

DELETE FROM creature_text WHERE entry=38507;
INSERT INTO creature_text VALUES 
(38507, 0, 0, "Let us go at once.  We will track Sylvanas down.  For Gilneas!", 12, 0, 100, 15, 0, 0, "", 38399),
(38507, 1, 0, "Let's do our best not to be seen!", 12, 0, 100, 0, 0, 0, "tobias", 38401),
(38507, 2, 0, "Did you hear that? Sylvanas is headed to the cathedral. Let's hurry!", 12, 0, 100, 0, 0, 0, "tobias", 38402),
(38507, 3, 0, "Quick, hide in the water!", 12, 0, 100, 0, 0, 0, "tobias", 38403);

DELETE FROM creature_text WHERE entry=38533;
INSERT INTO creature_text VALUES 
(38533, 0, 0, "It appears you're losing control of Gilneas, Sylvanas.  Garrosh fears he's going to have to carry out this invasion himself.", 12, 0, 100, 1, 0, 22620, "", 38426),
(38533, 1, 0, "You sound very confident, your Majesty. I sincerely hope you do not plan to use the plague. Garrosh has expllicitely forbidden it.", 12, 0, 100, 0, 0, 22621, "warhowl", 38427),
(38533, 2, 0, "I will deliver my report to our leader, then. By your leave, my lady.", 12, 0, 100, 0, 0, 22622, "warhowl", 38428);

DELETE FROM creature_text WHERE entry=46026;
INSERT INTO creature_text VALUES 
(46026, 0, 0, "You can assure Garrosh that this is a minor setback. Our victory in Gilneas will be absolute.", 12, 0, 100, 0, 0, 20492, "sylvanas", 38422),
(46026, 1, 0, "You'd do well to watch your tone, General! Neither you nor Garrosh have anything to worry about. We've seized all production of the plague, as he ordered. We'd never deploy it without his permission.", 12, 0, 100, 0, 0, 20493, "sylvanas", 38423),
(46026, 2, 0, "Go with honor... General.", 12, 0, 100, 0, 0, 20494, "sylvanas", 38424),
(46026, 3, 0, "What kind of question is that? Of course we're deploying the plague, as planned! Let the gilneans enjoy their small victory. Not even their bones will remain by tomorrow!", 12, 0, 100, 0, 0, 20495, "sylvanas", 38425);

DELETE FROM creature_text WHERE entry=38537;
INSERT INTO creature_text VALUES 
(38537, 0, 0, "My Lady!  Should I order my men to stop the deployment of the Plague?  Or are we to continue as planned?", 12, 0, 100, 66, 0, 20917, "", 38440),
(38537, 1, 0, "As you wish!", 12, 0, 100, 0, 0, 20918, "crenshaw", 38441);

