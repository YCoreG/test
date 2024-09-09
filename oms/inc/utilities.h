/**
 * @file utilities.h
 * @brief Provides utility functions for common operations.
 *
 * This header file includes functions for generating random numbers and strings, validating dates,
 * comparing dates, getting the current date, and creating dummy data.
 * These utilities are commonly used for various operations in the application.
 *
 * @author [don]
 * @version 1.0
 * @date 2024-09-09
 */

#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <time.h>

/**
 * @brief Clears the input buffer.
 *
 * This function reads and discards all characters from the input buffer until a newline or EOF is encountered.
 */
void clear_input_buffer();

/**
 * @brief Generates a random number within a given range.
 *
 * @param lower The lower bound of the range (inclusive).
 * @param upper The upper bound of the range (inclusive).
 * @return A random number between lower and upper, inclusive.
 */
int generateRandomNumber(int lower, int upper);

/**
 * @brief Generates a random string of alphabets of a given length.
 *
 * @param result A pointer to the buffer where the generated string will be stored.
 * @param length The length of the string to generate.
 */
void generateRandomAlphabet(char *result, int length);

/**
 * @brief Validates a date string and converts it to a struct tm.
 *
 * @param inputDate The date string to validate (expected format: YYYY-MM-DD).
 * @param date A pointer to a struct tm to store the converted date.
 * @return 0 if the date is valid, 1 if the date is invalid.
 */
int validateDate(const char *inputDate, struct tm *date);

/**
 * @brief Compares two dates.
 *
 * @param dateFrom The first date to compare.
 * @param dateTo The second date to compare.
 * @return 1 if dateFrom is after dateTo, 0 if dateFrom is on or before dateTo.
 */
 int compareDate(struct tm dateFrom, struct tm dateTo);

 /**
 * @brief Gets the current date in MMDDYYYY format.
 *
 * @param buffer A pointer to the buffer where the formatted date will be stored.
 * @param size The size of the buffer.
 */
void getCurrentDate(char *buffer, size_t size);

/**
 * @brief Creates dummy data including a random symbol, number of shares, and amount.
 *
 * @param symbol A pointer to the buffer where the generated symbol will be stored.
 * @param shares A pointer to an integer where the number of shares will be stored.
 * @param amount A pointer to a float where the amount will be stored.
 */
void createDummyData(char* symbol, int* shares, float* amount);

/**
 * @brief Reads database configuration from a file and stores the values in provided variables.
 *
 * This function reads a configuration file line-by-line to extract database connection settings.
 * It parses the file for specific configuration parameters such as `host`, `user`, `password`,
 * `database`, and `port`, and stores these values in the provided character arrays and integer pointer.
 *
 * The configuration file should contain lines in the format of `key=value` for each parameter.
 *
 * @param fileName The name of the configuration file to read from.
 * @param host A pointer to a character array where the host value will be stored.
 * @param user A pointer to a character array where the user value will be stored.
 * @param password A pointer to a character array where the password value will be stored.
 * @param database A pointer to a character array where the database name will be stored.
 * @param port A pointer to an unsigned integer where the port number will be stored.
 *
 * @return Returns 1 if the configuration file was successfully read and all parameters were parsed,
 *         or 0 if there was an error opening the file.
 */
int readDBConfig(const char *fileName, char *host, char *user, char *password, char *database, unsigned int *port);



/*
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard the remaining characters
    }
}

// Function to generate a random number between a given range
int generateRandomNumber(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

// Function to generate a random string of alphabets of a given length
void generateRandomAlphabet(char *result, int length) {
    for (int i = 0; i < length; i++) {
        // Generate a random alphabet from 'A' to 'Z'
        result[i] = 'A' + (rand() % 26);
    }
    result[length] = '\0';  // Null-terminate the string
}

int validateDate(const char *inputDate, struct tm *date) {
    *date = (struct tm){0};

    // Parse the date from the input (expected format: YYYY-MM-DD)
    if (sscanf(inputDate, "%d-%d-%d", &date->tm_year, &date->tm_mon, &date->tm_mday) != 3) {
        printf("Invalid date format. Expected YYYY-MM-DD.\n");
        return 1;  // Invalid format
    }

    // Adjust year and month for `tm` structure (tm_year = years since 1900, tm_mon = months since January)
    date->tm_year -= 1900;  // tm_year expects years since 1900
    date->tm_mon -= 1;      // tm_mon expects months from 0 (January) to 11 (December)

    // Validate the date by converting it to time_t
    time_t t = mktime(date);
    if (t == -1) {
        printf("Invalid date values.\n");
        return 1;  // Invalid date
    }

    return 0;  // Valid date
}

int compareDate(struct tm dateFrom, struct tm dateTo) {
    // Convert both dates to time_t for comparison
    time_t timeFrom = mktime(&dateFrom);
    time_t timeTo = mktime(&dateTo);

    // Compare the two dates
    if (difftime(timeFrom, timeTo) > 0) {
        return 1;
    } else {
        return 0;
    }
}

void getCurrentDate(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%m%d%Y", t);  // Format: MMDDYYYY (e.g., 09082024)
}

void createDummyData(char* symbol, int* shares, float* amount) {
    *shares = generateRandomNumber(1, 100);
    *amount = generateRandomNumber(100, 1000);
    generateRandomAlphabet(symbol, 3);
}

// Function to trim newlines or extra spaces from strings
void trim_newline(char *str) {
    size_t len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}


// Function to read configuration file
int readDBConfig(const char *fileName, char *host, char *user, char *password, char *database, unsigned int *port) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: Could not open config file: %s\n", fileName);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);  // Remove newlines from the line

        // Parse host
        if (strncmp(line, "host=", 5) == 0) {
            strcpy(host, line + 5);
        }
        // Parse user
        else if (strncmp(line, "user=", 5) == 0) {
            strcpy(user, line + 5);
        }
        // Parse password
        else if (strncmp(line, "password=", 9) == 0) {
            strcpy(password, line + 9);
        }
        // Parse database
        else if (strncmp(line, "database=", 9) == 0) {
            strcpy(database, line + 9);
        }
        // Parse port
        else if (strncmp(line, "port=", 5) == 0) {
            *port = atoi(line + 5);
        }
    }

    fclose(file);
    return 1;
};
*/

#endif // UTILITIES_H_INCLUDED
