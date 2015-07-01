
SET NAMES 'utf8';

INSERT IGNORE INTO locales_gossip_menu_option (menu_id, id) SELECT menu_id, id FROM gossip_menu_option;

update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Kämpfer" where menu_id=56100 and id=0;
update locales_gossip_menu_option set option_text_loc3="Entlasse einen Kämpfer" where menu_id=56100 and id=1;
update locales_gossip_menu_option set option_text_loc3="Hilfe" where menu_id=56100 and id=2;
update locales_gossip_menu_option set option_text_loc3="Entlasse alle Kämpfer" where menu_id=56100 and id=3;
update locales_gossip_menu_option set option_text_loc3="Zum Hauptmenü" where menu_id=56100 and id=4;
update locales_gossip_menu_option set option_text_loc3="Keine weiteren Kämpfer verfügbar." where menu_id=56100 and id=5;
update locales_gossip_menu_option set option_text_loc3="Kämpfer ist verfügbar." where menu_id=56100 and id=6;
update locales_gossip_menu_option set option_text_loc3="Kämpfer sind verfügbar." where menu_id=56100 and id=7;
update locales_gossip_menu_option set option_text_loc3="Weiterer Kämpfer verfügbar." where menu_id=56100 and id=8;
update locales_gossip_menu_option set option_text_loc3="Weitere Kämpfer verfügbar." where menu_id=56100 and id=9;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Krieger." where menu_id=56100 and id=10;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Jäger." where menu_id=56100 and id=11;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Paladin." where menu_id=56100 and id=12;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Schamanen." where menu_id=56100 and id=13;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Schurken." where menu_id=56100 and id=14;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Druiden." where menu_id=56100 and id=15;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Magier." where menu_id=56100 and id=16;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Priester." where menu_id=56100 and id=17;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Hexenmeister." where menu_id=56100 and id=18;
update locales_gossip_menu_option set option_text_loc3="Rekrutiere einen Todesritter." where menu_id=56100 and id=19;

