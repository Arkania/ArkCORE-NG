
UPDATE creature_template SET minlevel=23, maxlevel=24, faction=1514, baseattacktime=2000, rangeattacktime=2000, unit_flags=32768 WHERE entry=33569;

UPDATE creature_template SET gossip_menu_id=10338, rangeattacktime=2000 WHERE entry=33440;

UPDATE creature_template SET rangeattacktime=2000 WHERE entry=12858;

delete from creature where id=33912;

UPDATE creature_template SET minlevel=24, maxlevel=24, faction=1642, baseattacktime=2000, rangeattacktime=2000, unit_flags=32768 WHERE entry=33945;

UPDATE creature_template SET minlevel=20, maxlevel=11, faction=1642, baseattacktime=2000, rangeattacktime=2000, unit_class=2, unit_flags=32768 WHERE entry=33914;

update creature_template_addon set auras="" where entry=12903;



