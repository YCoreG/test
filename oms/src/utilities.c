#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "../inc/utilities.h"

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
