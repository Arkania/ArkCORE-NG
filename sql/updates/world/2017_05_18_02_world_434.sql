
ALTER TABLE `gameobject_template`
CHANGE COLUMN `WDBVerified` `VerifiedBuild`  smallint(5) NOT NULL DEFAULT 0 AFTER `ScriptName`;

