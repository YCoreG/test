/**
 * @file menu.h
 * @brief Provides functions to display various menus and headers in the application.
 *
 * This header file includes functions to display the main menu, user menu, trade history menu,
 * and admin menu. It also includes functions for showing headers and footers for trade and user information.
 *
 * @author [Your Name]
 * @version 1.0
 * @date 2024-09-09
 */

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED


/**
 * @brief Displays the main menu of the application.
 */
void showMainMenu();

/**
 * @brief Displays the user menu after login.
 */
void showUserMenu();

/**
 * @brief Displays the trade history menu.
 */
void showTradeHistoryMenu();

/**
 * @brief Displays the header for the trade history table.
 *
 * @param tradeHeader A buffer to store the header string.
 */
void showHeader(char* tradeHeader);

/**
 * @brief Displays the footer for the trade history table.
 */
void showFooter();

/**
 * @brief Displays the header for the user information table.
 *
 * @param userHeader A buffer to store the header string.
 */
void showUserHeader(char* userHeader);

/**
 * @brief Displays the footer for the user information table.
 */
void showUserFooter();

/**
 * @brief Displays the admin menu.
 */
void showAdminMenu();

/**
 * @brief Displays the admin edit menu.
 */
void showAdminEditMenu();



#endif // MENU_H_INCLUDED
