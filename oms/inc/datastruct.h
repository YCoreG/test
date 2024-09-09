/**
 * @file datastruct.h
 * @brief Defines data structures used in the application.
 *
 * This header file includes definitions for the data structures used to represent trades and persons
 * in the application. It provides a way to organize and manage the data related to trades and user
 * information.
 *
 * @author [Don]
 * @version 1.0
 * @date 2024-09-09
 */

#ifndef DATASTRUCT_H_INCLUDED
#define DATASTRUCT_H_INCLUDED

/**
 * @brief Structure to hold trade information.
 */
typedef struct {
    int     id;                  /**< Unique identifier for the trade. */
    char    symbol[8];          /**< Stock symbol (e.g., "AAPL", "GOOGL"). */
    int     shares;              /**< Number of shares traded. */
    float   totalAmount;         /**< Total amount for the trade. */
    char    marketOrder[8];      /**< Type of market order ("BOUGHT" or "SELL"). */
    char    userId[8];           /**< Unique identifier for the user making the trade. */
    char    date[32];            /**< Date of the trade in string format (e.g., "2024-09-09"). */
} Trade;

/**
 * @brief Structure to hold person (user) information.
 */
typedef struct {
    int     id;                  /**< Unique identifier for the person. */
    char    userId[32];          /**< Unique identifier for the user. */
    char    name[64];            /**< Name of the person. */
    int     age;                 /**< Age of the person. */
} Person;

#endif // DATASTRUCT_H_INCLUDED
