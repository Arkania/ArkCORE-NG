

REVOKE ALL PRIVILEGES ON *.* FROM 'arkania'@'localhost';
REVOKE ALL PRIVILEGES ON *.* FROM 'arkania'@'127.0.0.1';
REVOKE ALL PRIVILEGES ON *.* FROM 'arkania'@'%';

REVOKE ALL PRIVILEGES ON `ng_world`.* FROM 'arkania'@'localhost';
REVOKE ALL PRIVILEGES ON `ng_world`.* FROM 'arkania'@'127.0.0.1';
REVOKE ALL PRIVILEGES ON `ng_world`.* FROM 'arkania'@'%';

REVOKE GRANT OPTION ON `ng_world`.* FROM 'arkania'@'localhost';
REVOKE GRANT OPTION ON `ng_world`.* FROM 'arkania'@'127.0.0.1';
REVOKE GRANT OPTION ON `ng_world`.* FROM 'arkania'@'%';

REVOKE ALL PRIVILEGES ON `ng_characters`.* FROM 'arkania'@'localhost';
REVOKE ALL PRIVILEGES ON `ng_characters`.* FROM 'arkania'@'127.0.0.1';
REVOKE ALL PRIVILEGES ON `ng_characters`.* FROM 'arkania'@'%';

REVOKE GRANT OPTION ON `ng_characters`.* FROM 'arkania'@'localhost';
REVOKE GRANT OPTION ON `ng_characters`.* FROM 'arkania'@'127.0.0.1';
REVOKE GRANT OPTION ON `ng_characters`.* FROM 'arkania'@'%';

REVOKE ALL PRIVILEGES ON `ng_auth`.* FROM 'arkania'@'localhost';
REVOKE ALL PRIVILEGES ON `ng_auth`.* FROM 'arkania'@'127.0.0.1';
REVOKE ALL PRIVILEGES ON `ng_auth`.* FROM 'arkania'@'%';

REVOKE GRANT OPTION ON `ng_auth`.* FROM 'arkania'@'localhost';
REVOKE GRANT OPTION ON `ng_auth`.* FROM 'arkania'@'127.0.0.1';
REVOKE GRANT OPTION ON `ng_auth`.* FROM 'arkania'@'%';

