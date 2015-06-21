
delete from arkcore_string where entry=8003;
insert into arkcore_string (entry, content_default) values (8003,"Message from ChatCensor: Please, not use bad words.");

update arkcore_string set content_loc3="Nachricht der Zensur: Bitte benutze keine Gossensprache." where entry=8003;

-- Censor for bad words
CREATE TABLE IF NOT EXISTS `censor_bad_words` (
    `word` varchar(100) NOT NULL DEFAULT '' COMMENT 'Bad word, to be banned',
    `level` tinyint(3) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'Value that give a badness level of the word. 0=ok, >0 badness',
    PRIMARY KEY  (`word`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

replace into `censor_bad_words` (`word`, `level`)
values
('Motherfucker','2'), 
('Scheiße','1'),
('Scheisse','1'); 
