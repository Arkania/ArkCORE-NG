
update creature set phaseIds=trim(CONCAT(trim(phaseIds), " ", trim(phaseGroups)));

update gameobject set phaseIds=trim(CONCAT(trim(phaseIds), " ", trim(phaseGroups)));

update phase_definitions set phaseId=phaseGroup where phaseId=0 and phaseGroup>0;

update phase_definitions set phaseId=169 where phaseId=0;

update creature set phaseIds="169 " where phaseIds="";

update gameobject set phaseIds="169 " where phaseIds="";

