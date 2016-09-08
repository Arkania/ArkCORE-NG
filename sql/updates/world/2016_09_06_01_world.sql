
-- remove some phaseMask that was created with .gm command
 
update creature set phaseMask=4194304 where id=883 and phaseMask=4294967295;

update creature set phaseMask=131072 where id=37716 and phaseMask=4294967295;

update creature set phaseMask=1 where phaseMask=4294967295;

-- first big part, convert all phase 1 entrys
update creature set phaseMask=0, phaseIds='169', phaseGroups='' where phaseMask<=1 and phaseIds='' and phaseGroups='';

update gameobject set phaseMask=0, phaseIds='169', phaseGroups='' where phaseMask<=1 and phaseIds='' and phaseGroups='';

