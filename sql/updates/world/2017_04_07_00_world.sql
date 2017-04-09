

DELETE FROM gossip_menu_option WHERE menu_id=10204 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(10204, 0, 0, "I... I think so....", 32988, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=10204 AND SourceEntry=0 AND SourceId=0;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES 
(15, 10204, 9, 13413),
(15, 10204, 9, 13414);

DELETE FROM gossip_menu_option WHERE menu_id=9417 AND id=0;
INSERT INTO gossip_menu_option VALUES 
(9417, 0, 0, "Let's do this, Thassarian.  It's now or never.", 25840, 1, 1, 0, 0, 0, 0, 0, "", 0);

DELETE FROM conditions WHERE SourceTypeOrReferenceId=15 AND SourceGroup=9417 AND SourceEntry=0 AND SourceId=0;
INSERT INTO conditions (SourceTypeOrReferenceId, SourceGroup, ConditionTypeOrReference, ConditionValue1) VALUES (15, 9417, 9, 12019);

UPDATE gossip_menu_option SET option_text="I have reason to believe you're involved in cultist activity.", OptionBroadcastTextID=25239 WHERE menu_id=9218 AND id=0;

UPDATE gossip_menu_option SET option_text="How long have you worked for the Cult of the Damned?", OptionBroadcastTextID=25242 WHERE menu_id=9219 AND id=0;

