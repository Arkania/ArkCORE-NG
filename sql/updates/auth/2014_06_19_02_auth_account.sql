ALTER TABLE `account`   
   ADD COLUMN `reg_mail` VARCHAR(255) NOT NULL DEFAULT '' AFTER `email`;
