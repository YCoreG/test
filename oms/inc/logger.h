/**
 * @file logger.h
 * @brief Provides logging functionality with file operations.
 *
 * This header file provides functions to initialize a log file, write messages to it, and close it.
 * It includes functions for setting up the log file, writing log entries with timestamps, and properly closing the file.
 *
 * @author [Don]
 * @version 1.0
 * @date 2024-09-07
 */

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
 * @brief Initializes the logger by opening the log file.
 *
 * This function constructs a log filename based on the provided base name and the current date, and opens the file for appending.
 * If the log file is already open, it will not reopen the file.
 *
 * @param fileName The base name for the log file.
 * @return 0 if the log file was successfully opened, 1 if an error occurred.
 */
int initLogMsg(const char *fileName);

/**
 * @brief Writes a message to the log file.
 *
 * This function writes a log entry to the currently open log file, including a timestamp and module name.
 *
 * @param module The module name from which the log message originates.
 * @param message The message to be logged.
 */
void logMsg(const char *module, const char *message);

/**
 * @brief Closes the log file.
 *
 * This function closes the currently open log file and sets the global file pointer to NULL.
 * It writes a final log entry indicating that the file is closed.
 */
void closeLogMsg();




#endif // LOGGER_H_INCLUDED
