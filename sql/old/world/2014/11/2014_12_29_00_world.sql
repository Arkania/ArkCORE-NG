
update creature set spawndist=0, MovementType=0 where guid in (43357,43445,43034,43547,43340,43252);
update creature set spawndist=0, MovementType=0 where guid in (42869,42882,42418,42587,42824);

update creature_template set faction_A=35, faction_H=35, unit_flags=131844 where entry=42617;


