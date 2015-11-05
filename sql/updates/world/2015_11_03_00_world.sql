
update creature_template set MovementType=0 where entry in (7011, 7012);
update creature set spawndist=0, MovementType=0 where id in (7011, 7012);


