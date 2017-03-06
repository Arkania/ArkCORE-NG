
-- npc 48797 should walk on ground, not swimm
update creature set position_z=-34.5 where guid=24067 and id=48797;

