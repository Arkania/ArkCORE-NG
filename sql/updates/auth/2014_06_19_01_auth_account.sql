ALTER TABLE `account`   
   ADD COLUMN `lock_country` VARCHAR(2) NOT NULL DEFAULT '00' AFTER `locked`;