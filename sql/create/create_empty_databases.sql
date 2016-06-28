
CREATE DATABASE `ng_world` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `ng_characters` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
CREATE DATABASE `ng_auth` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;

GRANT ALL PRIVILEGES ON `ng_world` . * TO 'arkania'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_characters` . * TO 'arkania'@'localhost' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_auth` . * TO 'arkania'@'localhost' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `ng_world` . * TO 'arkania'@'127.0.0.1' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_characters` . * TO 'arkania'@'127.0.0.1' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_auth` . * TO 'arkania'@'127.0.0.1' WITH GRANT OPTION;

GRANT ALL PRIVILEGES ON `ng_world` . * TO 'arkania'@'%' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_characters` . * TO 'arkania'@'%' WITH GRANT OPTION;
GRANT ALL PRIVILEGES ON `ng_auth` . * TO 'arkania'@'%' WITH GRANT OPTION;
