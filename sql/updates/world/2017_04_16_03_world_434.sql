
ALTER TABLE `creature_template_addon`
ADD COLUMN `aiAnimKit`  smallint(6) NOT NULL DEFAULT 0 AFTER `emote`,
ADD COLUMN `movementAnimKit`  smallint(6) NOT NULL DEFAULT 0 AFTER `aiAnimKit`,
ADD COLUMN `meleeAnimKit`  smallint(6) NOT NULL DEFAULT 0 AFTER `movementAnimKit`;


