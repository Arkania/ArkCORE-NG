
delete from rbac_permissions where  id in (805,806,807,808,809,810);
insert into rbac_permissions values 
(805, "Command: gobject set phaseid"),
(806, "Command: gobject set phasegroup"),
(807, "Command: npc set phaseid"),
(808, "Command: npc set phasegroup"),
(809, "Command: modify phaseid"),
(810, "Command: modify phasegroup");

delete from rbac_linked_permissions where id=196 and linkedId in (809,810);
delete from rbac_linked_permissions where id=197 and linkedId in (805,806,807,808);
insert into rbac_linked_permissions values 
(197, 805),
(197, 806),
(197, 807),
(197, 808),
(196, 809),
(196, 810);



