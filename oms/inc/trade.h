/**
 * @file trade.h
 * @brief Provides functions for managing trade records in a MySQL database.
 *
 * This header file includes function declarations and definitions for creating, updating,
 * and retrieving trade records from a MySQL database. It also defines a structure for managing
 * trade-related operations and data.
 *
 * @author [Don]
 * @version 1.0
 * @date 2024-09-07
 */

#ifndef TRADE_H_INCLUDED
#define TRADE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "datastruct.h"  // Assuming dataStruct.h contains the definition of the Trade structure

/**
 * @brief Structure for managing trade operations with function pointers.
 *
 * This structure includes a `Trade` data member and function pointers for performing various
 * SQL operations related to trades.
 */
typedef struct TRADE_SQL {
    Trade dataTrade; /**< The trade data. */

    /**
     * @brief Creates a new trade record in the database.
     *
     * @param sql Pointer to the TRADE_SQL structure.
     * @param conn Pointer to the MYSQL connection object.
     * @return The ID of the newly created trade if successful, or 0 if failed.
     */
    int (*createTrade) (struct TRADE_SQL* sql, MYSQL *conn);

    /**
     * @brief Retrieves all trade records for a user, optionally filtered by date range.
     *
     * @param sql Pointer to the TRADE_SQL structure.
     * @param conn Pointer to the MYSQL connection object.
     * @param dataTrade Pointer to a pointer to an array of Trade structures.
     * @param user_id User ID to filter trades.
     * @param dateFrom Start date for filtering trades.
     * @param dateTo End date for filtering trades.
     * @return The number of records retrieved, or -1 if an error occurred.
     */
    int (*getAllRecords) (struct TRADE_SQL* sql, MYSQL *conn, Trade **dataTrade, const char *user_id, const char* dateFrom, const char* dateTo);

    /**
     * @brief Retrieves a trade record by its ID.
     *
     * @param sql Pointer to the TRADE_SQL structure.
     * @param conn Pointer to the MYSQL connection object.
     * @param dataTrade Pointer to a pointer to a Trade structure.
     * @param tradeId The ID of the trade to retrieve.
     * @return The number of records retrieved, or -1 if an error occurred.
     */
    int (*getTradeRecById) (struct TRADE_SQL* sql, MYSQL *conn, Trade **dataTrade, unsigned int tradeId);

    /**
     * @brief Updates the number of shares for a specific trade.
     *
     * @param sql Pointer to the TRADE_SQL structure.
     * @param conn Pointer to the MYSQL connection object.
     * @param tradeId The ID of the trade to update.
     * @param share The new number of shares.
     * @return 0 if successful, or 1 if an error occurred.
     */
    int (*updateTradeShares) (struct TRADE_SQL *sql, MYSQL *conn, int tradeId, int share);

    /**
     * @brief Updates the total amount for a specific trade.
     *
     * @param sql Pointer to the TRADE_SQL structure.
     * @param conn Pointer to the MYSQL connection object.
     * @param tradeId The ID of the trade to update.
     * @param amount The new total amount.
     * @return 0 if successful, or 1 if an error occurred.
     */
    int (*updateTradeAmount) (struct TRADE_SQL *sql, MYSQL *conn, int tradeId, float amount);

} TradeSql;

/**
 * @brief Updates the number of shares for a specific trade in the database.
 *
 * Prepares and executes an SQL update statement to change the number of shares for a given trade.
 * Logs any errors encountered during execution.
 *
 * @param sql Pointer to the TRADE_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param tradeId The ID of the trade to update.
 * @param share The new number of shares.
 * @return 0 if successful, or 1 if an error occurred.
 */
int sql_updateTradeShares(struct TRADE_SQL *sql, MYSQL *conn, int tradeId, int share);

/**
 * @brief Updates the total amount for a specific trade in the database.
 *
 * Prepares and executes an SQL update statement to change the total amount for a given trade.
 * Logs any errors encountered during execution.
 *
 * @param sql Pointer to the TRADE_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param tradeId The ID of the trade to update.
 * @param amount The new total amount.
 * @return 0 if successful, or 1 if an error occurred.
 */
int sql_updateTradeAmount(struct TRADE_SQL *sql, MYSQL *conn, int tradeId, float amount);

/**
 * @brief Retrieves a trade record by its ID from the database.
 *
 * Executes a SELECT query to retrieve a trade record with a specific ID and stores the results
 * in a Trade structure. Handles errors and logs them if necessary.
 *
 * @param sql Pointer to the TRADE_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param dataTrade Pointer to a pointer to a Trade structure.
 * @param tradeId The ID of the trade to retrieve.
 * @return The number of records retrieved, or -1 if an error occurred.
 */
int sql_getTradeRecById(struct TRADE_SQL *sql, MYSQL *conn, Trade **dataTrade, unsigned int tradeId);

/**
 * @brief Retrieves all trade records for a user, optionally filtered by date range.
 *
 * Executes a SELECT query to retrieve trade records for a specific user, with optional filtering
 * by date range. Stores the results in an array of Trade structures and handles errors.
 *
 * @param sql Pointer to the TRADE_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @param dataTrade Pointer to a pointer to an array of Trade structures.
 * @param user_id User ID to filter trades.
 * @param dateFrom Start date for filtering trades.
 * @param dateTo End date for filtering trades.
 * @return The number of records retrieved, or -1 if an error occurred.
 */
int sql_getAllRecords(struct TRADE_SQL *sql, MYSQL *conn, Trade **dataTrade, const char *user_id, const char* dateFrom, const char* dateTo);

/**
 * @brief Creates a new trade record in the database.
 *
 * Prepares and executes an SQL INSERT statement to add a new trade record to the database.
 * Logs any errors encountered during execution.
 *
 * @param sql Pointer to the TRADE_SQL structure.
 * @param conn Pointer to the MYSQL connection object.
 * @return The ID of the newly created trade if successful, or 0 if failed.
 */
int sql_createTrade(struct TRADE_SQL *sql, MYSQL *conn);

/**
 * @brief Initializes a TradeSql structure with function pointers.
 *
 * Sets up the function pointers in the TRADE_SQL structure to point to the appropriate SQL
 * operation functions.
 *
 * @param sql Pointer to the TRADE_SQL structure to initialize.
 */
void initTrade(TradeSql* sql);

/**
 * @brief Initializes a TradeSql structure with trade data.
 *
 * Sets up the TRADE_SQL structure with the provided trade data and assigns the createTrade
 * function pointer to the appropriate implementation.
 *
 * @param sql Pointer to the TRADE_SQL structure to initialize.
 * @param structDataTrade Pointer to the Trade structure containing trade data.
 */
void initTradeSql(TradeSql* sql, Trade* structDataTrade);







#endif // TRADE_H_INCLUDED
