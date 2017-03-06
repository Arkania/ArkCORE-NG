
set @ENTRY=3061;
set @GOSSIP=4647;

delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu values
(@GOSSIP, 4997), -- Do you prefer guns or bows?
(@GOSSIP, 4998); -- I do not have the knowledge you seek.

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=@GOSSIP;
insert into conditions values
(14, @GOSSIP, 4997, 0, 0, 15, 0,    4, 0, 0, 0, 0, 0, "", ""), -- Class mask 4=hunter 
(14, @GOSSIP, 4998, 0, 0, 15, 0, 1531, 0, 0, 0, 0, 0, "", ""); -- ALL class 4.x = 1535 - hunter = 1531

delete from gossip_menu_option where menu_id=@GOSSIP;
insert into gossip_menu_option values
(@GOSSIP, 0, 3, "I seek training in the ways of the Hunter.", 7643, 5, 16, 0, 0, 0, 0, 0, "", 0),
(@GOSSIP, 1, 0, "I wish to unlearn my talents.", 62295, 1, 1, 4461, 0, 0, 0, 0, "", 0),
(@GOSSIP, 2, 0, "Learn about Dual Talent Specialization.", 33765, 1, 1, 10371, 0, 0, 0, 0, "", 0);

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=@GOSSIP;
insert into conditions values
(15, @GOSSIP, 0, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter"),
(15, @GOSSIP, 1, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter"),
(15, @GOSSIP, 2, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter");



set @ENTRY=3065;
set @GOSSIP=4012;

delete from gossip_menu where entry=@GOSSIP;
insert into gossip_menu values
(@GOSSIP, 4868), -- Tauren have a passion for hunting; it is something that runs deep with our kind.
(@GOSSIP, 4998); -- I do not have the knowledge you seek.

delete from conditions where SourceTypeOrReferenceId=14 and SourceGroup=@GOSSIP;
insert into conditions values
(14, @GOSSIP, 4868, 0, 0, 15, 0,    4, 0, 0, 0, 0, 0, "", ""), -- Class mask 4=hunter 
(14, @GOSSIP, 4998, 0, 0, 15, 0, 1531, 0, 0, 0, 0, 0, "", ""); -- ALL class 4.x = 1535 - hunter = 1531

delete from gossip_menu_option where menu_id=@GOSSIP;
insert into gossip_menu_option values
(@GOSSIP, 0, 3, "I seek training in the ways of the Hunter.", 7643, 5, 16, 0, 0, 0, 0, 0, "", 0),
(@GOSSIP, 1, 0, "I wish to unlearn my talents.", 62295, 1, 1, 4461, 0, 0, 0, 0, "", 0),
(@GOSSIP, 2, 0, "Learn about Dual Talent Specialization.", 33765, 1, 1, 10371, 0, 0, 0, 0, "", 0);

delete from conditions where SourceTypeOrReferenceId=15 and SourceGroup=@GOSSIP;
insert into conditions values
(15, @GOSSIP, 0, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter"),
(15, @GOSSIP, 1, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter"),
(15, @GOSSIP, 2, 0, 0, 15, 0, 4, 0, 0, 0, 0, 0, "", "Show gossip option if player is a Hunter");

