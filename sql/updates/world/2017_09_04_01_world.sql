
-- set respawn for nazgrim and vanGuard to short respawn value, so each loop of ship to vashir can take player..
update creature set spawntimesecs=45 where id in (43090, 43100);

update creature set spawntimesecs=45 where id in (42021, 42022, 42095, 42103);



