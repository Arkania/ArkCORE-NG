-- 
-- wrong horse standing on cathedrale gilneas..
update creature set id=44429 where guid = 241299;

-- tobias missmantle missing riffle
UPDATE creature_template SET equipment_id=35618 WHERE entry=35618;
delete from creature_equip_template where entry=35618;
insert into creature_equip_template values (35618,0,0,1899,53243);
-- and disable move
UPDATE creature_template SET unit_flags=32772 WHERE entry=35618;

-- darius crowley in cathedrale missing riffle
UPDATE creature_template SET equipment_id=35566 WHERE entry=35566;
delete from creature_equip_template where entry=35566;
insert into creature_equip_template values (35566,0,0,1899,3042);

-- set random move on Bloodfang Stalker
update creature set spawndist=10, MovementType=1 where id=35229 and map=638 and phaseMask=8;

UPDATE creature_template SET AIName="",ScriptName="npc_bloodfang_stalker1_phase8" WHERE entry=35229;
UPDATE creature_template SET AIName="",ScriptName="npc_northgate_rebel1_phase8" WHERE entry=41015;
UPDATE creature_template SET AIName="",ScriptName="npc_northgate_rebel2_phase8" WHERE entry=36057;
UPDATE creature_template SET AIName="",ScriptName="npc_rebel_cannon_phase8" WHERE entry=35317;

-- wrong flag..  thanks to neow.. 
UPDATE creature_template SET npcflag=0 WHERE entry=35118;

-- change quest 14221 and 14222 to core script and set correct phase 1024 (&& 8 for some) for npc's
UPDATE quest_template SET RewardSpell=0 WHERE Id=14221;
UPDATE creature_template SET AIName="",ScriptName="npc_lord_darius_crowley_14222_phase8" WHERE entry=35566;
UPDATE quest_template SET RewardSpell=0,RewardSpellCast=0 WHERE Id=14222;
UPDATE creature_template SET AIName="",ScriptName="npc_frenzied_stalker_phase1024" WHERE entry=35627;
update creature set phaseMask=1024 where id=35627 and map=638;
delete from creature_queststarter where id=35627 and quest=14222;
update creature set phaseMask=1032 where id=35566 and map=638;
update creature set phaseMask=1032 where id=35317 and map=638;
delete from creature where guid=240576;
insert into creature values(240576,39660,638,1,1032,0,0,-1568.57, 1588.28, 28.1, 0.75,500,0,0,4120,0,0,0,0,0); 
update creature set phaseMask=1024 where id=41015 and map=638 and phaseMask=2;
update creature set phaseMask=1032 where guid in (241238,241239);

