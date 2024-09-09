/**
 * @file mysql_conn.h
 * @brief Provides functions for connecting to and disconnecting from a MySQL database.
 *
 * This header file includes function declarations and definitions for establishing and closing
 * a connection to a MySQL database. It also handles error logging related to database operations.
 *
 * @author [Don]
 * @version 1.0
 * @date 2024-09-07
 */

#ifndef MYSQL_CONN_H_INCLUDED
#define MYSQL_CONN_H_INCLUDED

#include <stdio.h>
#include <mysql.h>
#include "logger.h"

#define MYSQL_LOG_SZ       1024  /**< Size of the error log buffer. */
#define __MYSQL__          "MYSQL_CONN" /**< Module name for logging. */

/**
 * @brief Connects to a MySQL database.
 *
 * This function initializes a MySQL connection object and attempts to connect to the specified
 * MySQL database using the provided connection parameters. If the connection fails, it logs the
 * error message and returns NULL.
 *
 * @param host The hostname or IP address of the MySQL server.
 * @param user The username to authenticate with the MySQL server.
 * @param password The password for the specified user.
 * @param database The name of the database to connect to.
 * @param port The port number on which the MySQL server is listening.
 *
 * @return A pointer to the MYSQL connection object if successful, or NULL if the connection fails.
 */
MYSQL* connect_db(char *host, char *user, char *password, char *database, unsigned int port);

/**
 * @brief Closes the MySQL database connection.
 *
 * This function closes the connection to the MySQL database associated with the provided
 * MYSQL object.
 *
 * @param conn A pointer to the MYSQL connection object to be closed.
 */
void close_db(MYSQL *conn);

/** Error log buffer for recording MySQL connection errors. */
char ErrorLog[MYSQL_LOG_SZ];


#endif // MYSQL_CONN_H_INCLUDED
