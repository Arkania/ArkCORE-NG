
-- vashj'ir

delete from vehicle_template_accessory where entry in (40760, 41157, 40223, 41098, 42202, 41057, 41986, 41051, 41225, 39584);

INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(40760, 40761, 0, 1, 'Main Diving Tank - Secondary Diving Tank', 6, 0), -- Main Diving Tank - Secondary Diving Tank
(41157, 41154, 2, 1, 'Gnaws'' Corpse - Gnaws Harpoon Bunny', 6, 0), -- Gnaws' Corpse - Gnaws Harpoon Bunny
(41157, 41150, 1, 1, 'Gnaws'' Corpse - Gnaws Blood Bunny', 6, 0), -- Gnaws' Corpse - Gnaws Blood Bunny
(40223, 40353, 2, 1, 'Speckled Sea Turtle - Meatstick 01', 6, 0), -- Speckled Sea Turtle - Meatstick 01
(40223, 40351, 1, 1, 'Speckled Sea Turtle - Meatstick 00', 6, 0), -- Speckled Sea Turtle - Meatstick 00
(41098, 41154, 2, 1, 'Gnaws - Gnaws Harpoon Bunny', 6, 0), -- Gnaws - Gnaws Harpoon Bunny
(41098, 41150, 1, 1, 'Gnaws - Gnaws Blood Bunny', 6, 0), -- Gnaws - Gnaws Blood Bunny
(42202, 42094, 1, 1, 'Budd''s Vehicle Bunny - Stormwind Recruit', 6, 0), -- Budd's Vehicle Bunny - Stormwind Recruit
(41057, 46403, 3, 1, 'Gnaws - Gnaws Mouth Blood Bunny', 6, 0), -- Gnaws - Gnaws Mouth Blood Bunny
(41057, 46403, 2, 1, 'Gnaws - Gnaws Mouth Blood Bunny', 6, 0), -- Gnaws - Gnaws Mouth Blood Bunny
(41057, 46403, 1, 1, 'Gnaws - Gnaws Mouth Blood Bunny', 6, 0), -- Gnaws - Gnaws Mouth Blood Bunny
(41051, 41048, 0, 1, 'Bait Bunny - Booby-Trapped Bait', 6, 0), -- Bait Bunny - Booby-Trapped Bait
(41986, 40596, 1, 1, 'Naz''jar Battlemaiden - Spinning Trident Bunny', 6, 0), -- Naz'jar Battlemaiden - Spinning Trident Bunny
(41225, 40596, 1, 1, 'Naz''jar Battlemaiden - Spinning Trident Bunny', 6, 0), -- Naz'jar Battlemaiden - Spinning Trident Bunny
(39584, 40596, 1, 1, 'Naz''jar Battlemaiden - Spinning Trident Bunny', 6, 0); -- Naz'jar Battlemaiden - Spinning Trident Bunny

delete from npc_spellclick_spells where npc_entry in (39996, 41520, 48836);

INSERT INTO npc_spellclick_spells (`npc_entry`, `spell_id`, `cast_flags`, `user_type`) VALUES
(39996, 76193, 1, 0),
(39996, 86527, 1, 0),
(39996, 86324, 1, 0),
(41520, 77927, 1, 0),
(41520, 77684, 1, 0),
(48836, 91172, 1, 0),
(48836, 89195, 1, 0);

UPDATE locales_page_text SET `text_loc3`='<HTML>\n<BODY>\n<BR/>\n<H1 align="center">Königin Azshara</H1>\n<BR/>\n<BR/>\n<P>Möge dieses Bildnis als Zeugnis unserer unendlichen Ergebenheit für unsere ehrwürdige Königin Azshara dienen.</P>\n</BODY>\n</HTML>' WHERE `entry`=3626; -- 0
UPDATE locales_page_text SET `text_loc3`='<HTML>\n<BODY>\n<BR/>\n<H1 align="center">Lestharia Vashj</H1>\n<BR/>\n<BR/>\n<P>Dieses Monument ist ein Zeugnis der gütigen Herrschaft unserer geliebten Edlen Lestharia Vashj. Einhundert Jahre lang führte Sie die Bevölkerung Ihrer glänzenden Stadt, Vashj''ir, in ein Zeitalter endlosen Wohlstandes. Mögen sie und ihre Tochter, die glänzende Lady Vashj, weitere hundert Jahre lang den Weg unseres Volkes in seinen dunkelsten Stunden erleuchten.</P>\n</BODY>\n</HTML>' WHERE `entry`=3628; -- 0
UPDATE locales_page_text SET `text_loc3`='<HTML>\n<BODY>\n<BR/>\n<H1 align="center">Hohepriesterin Siralen</H1>\n<BR/>\n<BR/>\n<P>Möge diese Statue als ewige Erinnerung an Hohepriesterin Siralen dienen, für alles was sie getan hat, um den Tempel von Quel''Dormir zu einem strahlenden Leuchtfeuer des Glaubens wachsen zu lassen. Möge ihr neuer Dienst unter Königin Azshara selbst ein leuchtendes Beispiel für das Potenzial sein,  das eine edle Abstammung in unserer geliebten Vashj''ir wachsen ließ.</P>\n</BODY>\n</HTML>' WHERE `entry`=3629; -- 0
UPDATE locales_page_text SET `text_loc3`='<HTML>\n<BODY>\n<BR/>\n<H1 align="center">Der Hohe Waldläufer Valarian</H1>\n<BR/>\n<BR/>\n<P>In Erinnerung an den geheiligten Helden von Vashj''ir, den Hohen Waldläufer Valarian. Im Leben gab er uns Schönheit und Ruhe in den Straßen unserer herrlichen Stadt. Durch seinen Tod vertrieb er unsere Ängste und schuf dauerhaften Frieden für unser Volk. Möge sein Opfer nie vergessen werden.</P>\n</BODY>\n</HTML>' WHERE `entry`=3627; -- 0



