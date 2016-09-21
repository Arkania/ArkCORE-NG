
update command set help="Syntax: .modify phase #phaseId #phaseGroup
Selected object phase changed to #phaseId #phaseGroup.
Change active until in game phase changed, or GM-mode enable/disable, or re-login." 
where name="modify phase";

delete from arkcore_string where entry=186;
insert into arkcore_string (entry, content_default) values 
(186, "Invalid phase values %u.")
