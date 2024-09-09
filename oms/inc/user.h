/**
 * @file user.h
 * @brief Provides functions for managing user records in a MySQL database.
 *
 * This header file includes function declarations and definitions for creating, updating,
 * and retrieving user records from a MySQL database. It also defines a structure for managing
 * user-related operations and data.
 *
 * @autor Don
 * @version 1.0
 * @date 2024-09-08
 */

#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include "datastruct.h"

/**
 * @struct USER_SQL
 * @brief Structure to handle user-related SQL operations.
 *
 * This structure includes user data and function pointers to SQL operations related
 * to user management, such as checking if a user exists, registering a user, and
 * retrieving user records.
 */
typedef struct USER_SQL {
    Person dataUser;  ///< User data structure

    // Function pointers for SQL operations
    int (*isUserExist)(struct USER_SQL* sql, MYSQL *conn, const char *userId);
    int (*registerUser)(struct USER_SQL* sql, MYSQL *conn, const char* userId, const char *name, int age);
    int (*getAllUser)(struct USER_SQL* sql, MYSQL *conn, Person **person, const char *userId);
} userSql;

// Function declarations
/**
 * @brief Retrieves all user records from the database based on the user ID.
 *
 * Executes a SELECT query to retrieve user records. If the user ID is "admin",
 * retrieves all users except the admin. Otherwise, retrieves records for the specified user.
 *
 * @param sql Pointer to the USER_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param person Pointer to a pointer to a Person structure array.
 * @param userId The user ID to filter records.
 * @return Number of records retrieved, or -1 if an error occurred.
 */
int GetAllUser(userSql* sql, MYSQL *conn, Person **person, const char *userId);

/**
 * @brief Checks if a user exists in the database.
 *
 * Executes a SELECT query to check if a user with the specified user ID exists in the database.
 *
 * @param sql Pointer to the USER_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param userId The user ID to check.
 * @return 1 if the user exists, 0 if the user does not exist, or -1 if an error occurred.
 */
int IsUserExist(userSql* sql, MYSQL *conn, const char* userId);

/**
 * @brief Registers a new user in the database.
 *
 * Executes an INSERT query to add a new user to the database.
 *
 * @param sql Pointer to the USER_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param userId The user ID for the new user.
 * @param name The name of the new user.
 * @param age The age of the new user.
 * @return The ID of the newly created user if successful, or 0 if the registration failed.
 */
int RegisterUser(userSql* sql, MYSQL *conn, const char* userId, const char *name, int age);

/**
 * @brief Initializes a USER_SQL structure with function pointers.
 *
 * Sets up the function pointers in the USER_SQL structure to point to the appropriate SQL
 * operation functions.
 *
 * @param sql Pointer to the USER_SQL structure to initialize.
 */
void initUser(userSql* sql);


/**
 * @brief Initializes a USER_SQL structure with user data.
 *
 * Sets up the USER_SQL structure with the provided user data.
 *
 * @param sql Pointer to the USER_SQL structure to initialize.
 * @param name Name of the user.
 * @param age Age of the user.
 * @param userId User ID of the user.
 */
void initUserSQL(userSql* sql, const char* name, int age, const char* userId);

#endif // USER_H_INCLUDED
