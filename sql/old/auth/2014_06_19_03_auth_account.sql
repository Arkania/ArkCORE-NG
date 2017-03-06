
ALTER TABLE `account`   
   ADD COLUMN `token_key` VARCHAR(100) NOT NULL DEFAULT '' AFTER `s`;
