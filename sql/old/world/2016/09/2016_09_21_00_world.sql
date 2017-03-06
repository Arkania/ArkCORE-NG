
update arkcore_string set content_default=
" Map: %u (%s) Zone: %u (%s) Area: %u (%s) 
 X: %f Y: %f Z: %f Orientation: %f
 grid[%u,%u]cell[%u,%u] InstanceID: %u
 ZoneX: %f ZoneY: %f
 GroundZ: %f FloorZ: %f Have height data (Map: %u VMap: %u MMap: %u)" where entry=101;

update arkcore_string set content_loc3=
" Karte: %u (%s) Zone: %u (%s) Gebiet: %u (%s) 
 X: %f Y: %f Z: %f Orientierung: %f
 grid[%u,%u]Zelle[%u,%u] InstanzID: %u 
 ZoneX: %f ZoneY: %f
 GroundZ: %f FloorZ: %f Have height data (Map: %u VMap: %u)" where entry=101;
 
update arkcore_string set content_default="|cff0066FFSuccess (entry: %u) - added %s %u to the players phaseIds.|r" where entry=178;
 
update arkcore_string set content_default="|cffFF0000Condition for phaseId %s (entry: %u, zoneId: %u) failed.|r" where entry=179;
 
update arkcore_string set content_default="|cffFF0000Condition for phaseId %s (entry: %u, zoneId: %u) has last phaseId flag. Skipped other definitions.|r" where entry=180;
 
update arkcore_string set content_default="|cff6699FFThe player phaseIds %s through definitions, %s through phasing auras, and phase %s through custom phaseIds.|r" where entry=181;
 
update arkcore_string set content_default="|cff0099FFThe player phaseIds: %s .|r" where entry=182;
 
update arkcore_string set content_default="|cff0099FFReport for player: %s, zoneId: %u, level: %u, team: %u, phaseupdateflag: %u|r" where entry=183;

update arkcore_string set content_default="|cff663399There are no phase definitions defined for zoneId %u.|r" where entry=184;
 
update arkcore_string set content_default="|cff663399Name: %s (%s), Zone: %s, PhaseIds: %s, GUID: %u, Flags: %s, Roles: %s" where entry=1150;
 