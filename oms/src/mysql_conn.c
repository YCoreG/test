#include "../inc/mysql_conn.h"
#include "../inc/logger.h"

/**
 * @brief Connects to a MySQL database.
 *
 * Initializes a MYSQL object and attempts to establish a connection to the MySQL database using
 * the provided parameters. Logs errors if initialization or connection fails.
 *
 * @param host The hostname or IP address of the MySQL server.
 * @param user The username to authenticate with the MySQL server.
 * @param password The password for the specified user.
 * @param database The name of the database to connect to.
 * @param port The port number on which the MySQL server is listening.
 *
 * @return A pointer to the MYSQL connection object if successful, or NULL if the connection fails.
 */
MYSQL* connect_db(char *host, char *user, char *password, char *database, unsigned int port) {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        snprintf(ErrorLog, MYSQL_LOG_SZ, "::connect_db::mysql_init() failed: %s", mysql_error(conn));
        ErrorLog[MYSQL_LOG_SZ-1] = '\0';
        logMsg(__MYSQL__, ErrorLog);
        return NULL;
    }

    if (mysql_real_connect(conn, host, user, password, database, port, NULL, 0) == NULL) {
        snprintf(ErrorLog, MYSQL_LOG_SZ, "::connect_db::mysql_real_connect() failed: %s", mysql_error(conn));
        ErrorLog[MYSQL_LOG_SZ-1] = '\0';
        logMsg(__MYSQL__, ErrorLog);
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

/**
 * @brief Closes the MySQL database connection.
 *
 * Closes the specified MYSQL connection object and frees associated resources.
 *
 * @param conn A pointer to the MYSQL connection object to be closed.
 */
void close_db(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
    }
};



