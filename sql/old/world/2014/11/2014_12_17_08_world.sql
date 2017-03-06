
update creature_template set unit_flags=8388608,faction_A=31,faction_H=31 where entry=721;

delete from creature where guid=45005 and id=327;
update creature_template set type_flags=2147483648 where entry=327;

