delete from command where name="gobject set phase";
delete from command where name="npc set phase";
delete from command where name="modify phase";

delete from command where name="gobject set phaseid";
insert into command values 
("gobject set phaseid", 805, "Syntax: .gobject set phaseid #id (source)
Selected unit or pet phaseid set/unset to #id. 
In creature case state saved to DB and persistent.");

delete from command where name="gobject set phasegroup";
insert into command values 
("gobject set phasegroup", 806, "Syntax: .gobject set phasegroup #groupid (source)
Gameobject with DB guid #guid phaseid set/unset to all id's included this #phasexgroup. 
Gameobject state saved to DB and persistent.");


delete from command where name="npc set phaseid";
insert into command values 
("npc set phaseid", 807, "Syntax: .npc set phaseid #id (source)
Selected unit or pet phaseid set to #id. 
In creature case state saved to DB and persistent.");

delete from command where name="npc set phasegroup";
insert into command values 
("npc set phasegroup", 808, "Syntax: .npc set phasegroup #groupid (source)
Selected unit or pet phaseid set to all id's included in this #phasexgroup. 
In creature case state saved to DB and persistent. ");


delete from command where name="modify phaseid";
insert into command values 
("modify phaseid", 809, "Syntax: .modify phaseid #id (source)
Selected object's phaseid set to #id.
In creature case state saved to DB and persistent.");

delete from command where name="modify phasegroup";
insert into command values 
("modify phasegroup", 810, "Syntax: .modify phasegroup #groupid (source)
Selected object's phaseid set to (all id's included in) this #phasexgroup.
In creature case state saved to DB and persistent.");
