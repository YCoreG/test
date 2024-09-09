#ifndef HANDLER_H_INCLUDED
#define HANDLER_H_INCLUDED



#define __MAIN__                "MAIN"
#define MAX_BUFFER_SIZE         2056
#define MAX_USER_ID_LENGTH      32
#define MAX_NAME_LENGTH         64
#define MAX_LOG_MSG_LENGTH      256
#define MAX_DATE_LENGTH         16


/**
 * @brief Handles the admin menu functionality, allowing the admin to view and manage users and trades.
 *
 * This function provides options for:
 * 1. Viewing all users
 * 2. Viewing and editing a user's trades
 * 3. Logging out
 *
 * @param conn MYSQL connection object.
 */
void handleAdminMenu(MYSQL *conn);

/**
 * @brief Handles the user trade menu.
 *
 * This function displays the trade history menu, allows users to view all trades or trades within a specific date range,
 * and handles user input to perform the desired actions.
 *
 * @param conn MySQL connection handle.
 * @param userId The ID of the user whose trades are to be managed.
 */

void handleUserTradeMenu(MYSQL *conn, const char* userId);

/**
 * @brief Handles the user menu for performing various actions.
 *
 * This function displays the user menu, allows users to simulate buying or selling stocks, view their trade history,
 * or log out. It handles user input and performs the corresponding actions.
 *
 * @param conn MySQL connection handle.
 * @param userId The ID of the user.
 */

void handleUserMenu(MYSQL *conn,const char* userId);


void handleEditTrade(MYSQL *conn,char* userId);










#endif // HANDLER_H_INCLUDED
