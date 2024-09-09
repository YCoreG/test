#include "../inc/logger.h"


// Global file pointer for the log file
static FILE *logFile = NULL;  // Global file pointer

// Initialize the logger
int initLogMsg(const char *fileName) {
    if (logFile != NULL) {
        return 0;  // File already opened, don't reopen
    }

    char currentDate[20];
    getCurrentDate(currentDate, sizeof(currentDate));

    // Construct the full log filename
    char logFileName[32];
    snprintf(logFileName, sizeof(logFileName), "%s%s.log", fileName, currentDate);


    // Open the log file for appending
    logFile = fopen(logFileName, "a");
    if (logFile == NULL) {
        perror("Failed to open log file");
        return 1;
    }

    // Write an initial log entry (optional)
    fprintf(logFile, "Log file created/initialized at: %s\n", __TIMESTAMP__);
    fflush(logFile);  // Ensure it is written immediately

    return 0;
}

// Write a message to the log file
void logMsg(const char *module,const char *message) {

    if (logFile == NULL) {
        printf("Log file is not initialized!\n");
        return;
    }

    // Get the current time
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';  // Remove newline

    // Write the log message with a timestamp
    fprintf(logFile, "[%s]::[%s] %s\n", time_str, module,message);
    fflush(logFile);  // Ensure the message is written immediately
}

// Close the log file
void closeLogMsg() {
    if (logFile != NULL) {
        fprintf(logFile, "Log file closed at: %s\n", __TIMESTAMP__);
        fclose(logFile);
        logFile = NULL;
    }
}
