
-- talk sequence after reward quest 26286

delete from creature_text where entry=234 and groupid in (12,13) and id=0;
insert into creature_text values (234, 12, 0, "Do you know anything about this, beast? Who is the admiral? Speak!", 12, 0, 100, 0, 0, 0, "talk sequence 2", 42528);
insert into creature_text values (234, 13, 0, "Gibberish from a mad wolf. Bah!", 12, 0, 100, 1, 3, 0, "talk sequence 2", 42530);

delete from creature_text where entry=42635 and groupid=11 and id=0;
insert into creature_text values (42635, 11, 0, "The dawning comes, Stoutmantle, and with it comes your end.", 12, 0, 100, 0, 0, 0, "talk sequence 2", 42529);

delete from creature_queststarter where id=29611 and quest=26322;

update creature_template_addon set auras="79531" where entry in (42654,42655);

update creature_template set AIName="",ScriptName="npc_helix_gearbreaker" where entry=42655;

delete from item_script_names where Id=58112 and ScriptName="item_potion_of_shrouding";
insert into item_script_names values (58112,"item_potion_of_shrouding");

delete from creature_text where entry=42662 and groupid in (0,1,2,3,4) and id=0;
insert into creature_text values (42662, 0, 0, "They provided the distraction I required. We continue as planned.", 12, 0, 100, 0, 0, 0, "talk Shadowy Figure", 42537);
insert into creature_text values (42662, 1, 0, "We will free the admiral during the dawning.", 12, 0, 100, 0, 0, 0, "talk Shadowy Figure", 42539);
insert into creature_text values (42662, 2, 0, "Judgment day is soon upon us, Helix.", 12, 0, 100, 0, 0, 0, "talk Shadowy Figure", 42541);
insert into creature_text values (42662, 3, 0, "Call for the people. I wish to speak to them one last time before the dawning.", 12, 0, 100, 0, 0, 0, "talk Shadowy Figure", 42542);
insert into creature_text values (42662, 4, 0, "Aye. Tonight.", 12, 0, 100, 0, 0, 0, "talk Shadowy Figure", 42544);

delete from creature_text where entry=42655 and groupid in (0,1,2,3) and id=0;
insert into creature_text values (42655, 0, 0, "The gnolls have failed, mistress. ", 12, 0, 100, 0, 0, 0, "talk Helix Gearbreaker", 42536);
insert into creature_text values (42655, 1, 0, "But mistress, the admiral is sti...", 12, 0, 100, 0, 0, 0, "talk Helix Gearbreaker", 42538);
insert into creature_text values (42655, 2, 0, "Yes, mistress.", 12, 0, 100, 0, 0, 0, "talk Helix Gearbreaker", 42540);
insert into creature_text values (42655, 3, 0, "Moonbrook, mistress?", 12, 0, 100, 0, 0, 0, "talk Helix Gearbreaker", 42543);

