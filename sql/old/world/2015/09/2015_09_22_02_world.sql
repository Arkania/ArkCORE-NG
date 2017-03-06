
DELETE FROM playercreateinfo_spell WHERE Spell = 79684;
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (1, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (2, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (4, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (8, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (16, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (32, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (64, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (128, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (256, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (512, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (1024, 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");
INSERT INTO playercreateinfo_spell (racemask, classmask, Spell, Note) VALUES (2097152 , 128, 79684, "Mages - Offensive State (DND) - Enables Arcane Missiles");

-- Arcane Missiles
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (79683,-79683,5143);
INSERT INTO `spell_linked_spell` VALUES 
(79683, 79808, 0, 'Arcane Missiles aurastate link'),
(-79683, -79808, 0, 'Arcane Missiles aurastate link'),
-- On retail, you lose the 79683 aura by just clicking on arcane missiles
(5143,-79683,0,'Arcane missiles! aura removal due to arcane missiles cast');

INSERT INTO `spell_learn_spell` (`entry`, `SpellID`, `Active`) VALUES
(5143, 79684, 0);


