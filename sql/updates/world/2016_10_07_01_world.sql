

update arkcore_string set content_default=
"Map: %u (%s) 
Zone: %u (%s)
Area: %u (%s)
X: %.3f Y: %.3f Z: %.3f O: %.3f
grid[%u,%u]cell[%u,%u] InstanceID: %u
ZoneX: %.3f ZoneY: %.3f GroundZ: %.3f FloorZ: %.3f 
Have height data (Map: %u VMap: %u MMap: %u)"
where entry=101;
 
update arkcore_string set content_loc3= 
"Karte: %u (%s) 
Zone: %u (%s) 
Gebiet: %u (%s)
X: %.3f Y: %.3f Z: %.3f O: %.3f
grid[%u,%u]Zelle[%u,%u] InstanzID: %u
ZoneX: %.3f ZoneY: %.3f GroundZ: %.3f FloorZ: %.3f 
Have height data (Map: %u VMap: %u)"
where entry=101;

update arkcore_string set content_default=
"Liquid level: %.3f, ground: %.3f, type: %u, flags %u, status: %d."
where entry=175;

update arkcore_string set content_loc3=
"Wasserspiegel: %.3f, Boden: %.3f, Art: %d, Flags %u, Status: %d"
where entry=175;



