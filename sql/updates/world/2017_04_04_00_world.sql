

UPDATE quest_template SET PrevQuestId=27239 WHERE Id=27240;

DELETE FROM gossip_menu_option WHERE menu_id=6944 AND id=1;
INSERT INTO gossip_menu_option VALUES 
(6944, 1, 2, "I was told you could get me to Light's Breach....", 29485, 4, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM gossip_menu_option WHERE menu_id=8782 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(8782, 0, 0, "Lady Jaina told me to speak to you about using a gryphon to survey Alcaz Island.", 22176, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM creature_text WHERE entry=4968;
INSERT INTO creature_text VALUES 
(4968, 1, 0, "Perhaps I should explain...", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33092),
(4968, 2, 0, "I had arranged for a secret summit between Warchief Thrall and King Wrynn, here in Theramore.", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33093),
(4968, 3, 0, "The king was to travel here by ship, in secret. But the ship never arrived, and King Wrynn disappeared.", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33094),
(4968, 4, 0, "Your help enabled us to connect the Defias to the mastermind behind the abduction, Onyxia, who was posing as a member of the royal court.", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33095),
(4968, 5, 0, "Meanwhile, the king managed to escape his captors, and returned to Stormwind to deal with Onyxia.", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33096),
(4968, 6, 0, "I will send word that you have discovered the link to the Defias. I was a fool to think them broken with the defeat of Edwin Van Cleef, and King Wrynn will want to make an example of all who remain.", 12, 0, 100, 0, 0, 0, "Lady Jaina Proudmoore", 33097);

DELETE FROM gossip_menu_option WHERE menu_id=8846 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(8846, 0, 0, "Can you send me to Theramore? I have an urgent message for Lady Jaina from King Wrynn.", 22524, 1, 1, 0, 0, 0, 0, 0, "", 0);


