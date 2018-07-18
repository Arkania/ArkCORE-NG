
-- npc 25895  Dun Morogh Flame Warden
UPDATE gossip_menu_option SET option_text="The Festival Loremaster asked me to speak with you.", OptionBroadcastTextID=25445 WHERE menu_id=9203 AND id=0;

UPDATE locales_gossip_menu_option SET option_text_loc3="Der Geschichtenerzähler hat mich gebeten, mit Euch zu sprechen." WHERE menu_id=9203 AND id=0;

UPDATE npc_text SET BroadcastTextID0=25444 WHERE id=12588;

UPDATE npc_text SET text0_0="Then I am glad you came. Now that you know of our fires, and of honoring them... and of the fires of our enemies, and of extinguishing them... you may return to him and be rewarded.", text0_1="Then I am glad you came. Now that you know of our fires, and of honoring them... and of the fires of our enemies, and of extinguishing them... you may return to him and be rewarded." WHERE id=12588;
