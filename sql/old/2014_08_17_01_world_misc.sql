
-- http://de.wowhead.com/quest=8500 all this quest have no creature_queststarter
-- http://www.wowwiki.com/Huntress_Swiftriver  This is no longer available as game event is permanently over as of patch 3.2.0.  
-- http://www.wowwiki.com/Quest:One_Commendation_Signet  This is no longer available as game event is permanently over as of patch 3.2.0.  
delete from creature_questender where quest in (8500,8503,8504,8505,8506,8509,8510,8511,8512,8513,8514,8515,8516,8517,8518);
delete from creature_questender where quest in (8520,8521,8522,8523,8524,8525,8526,8527,8528,8529,8530,8531,8532,8533);
delete from creature_questender where quest in (8394,8395,8492,8493,8494,8495,8811,8812,8814,8819,8820,8822,10695,10696);
delete from creature_questender where quest in (8813,8821,8838,8839,8834,8835);

