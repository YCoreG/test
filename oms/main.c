#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>

#include "inc/mysql_conn.h"
#include "inc/user.h"
#include "inc/menu.h"
#include "inc/trade.h"
#include "inc/utilities.h"
#include "inc/logger.h"
#include "inc/handler.h"
#include "inc/datastruct.h"

int main()
{
    unsigned int age;
    char userId[MAX_USER_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char logMessage[MAX_LOG_MSG_LENGTH];
    char host[MAX_USER_ID_LENGTH];
    char user[MAX_USER_ID_LENGTH];
    char password[MAX_USER_ID_LENGTH];
    char database[MAX_USER_ID_LENGTH];
    unsigned int option = 0;
    unsigned int regId =0;
    unsigned int port;


    userSql     _userSql;

    //Initialize logger
    if (initLogMsg("log") != 0) {
        printf("Failed to open log file");
        return 1;
    }

    // Initialize connection details
    if (!readDBConfig("db_config.cfg", host, user, password, database, &port)) {
        printf("Error reading config file\n");
        closeLogMsg();
        return 1;
    }

    //Initialize MYSQL connection
    MYSQL *conn = connect_db(host, user, password, database, port);
    if (conn == NULL) {
        printf("Error in database connection. Try again later\n");
        closeLogMsg();
        return 1; // Connection failed
    }

    while (1) {
        system("cls");

        showMainMenu(); //Display Main menu

        // Ensure input is read correctly
        if (scanf("%u", &option) != 1) {
            clear_input_buffer();
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            sleep(2);
            continue;
        }

        switch (option) {
            case 1: // Sign In
                system("cls");
                printf("Enter User ID: ");
                scanf("%s",userId);

                initUserSQL(&_userSql,name,age,userId);

                if(_userSql.isUserExist(&_userSql,conn,userId) == 0) {
                    snprintf(logMessage, sizeof(logMessage), "Sign-in failed. User ID not found [%s]", userId);
                    logMsg(__MAIN__,logMessage);
                    printf("Sign-in failed. User ID not found. [%s] Try Again!\n",userId);
                    sleep(2);
                } else {
                    snprintf(logMessage, sizeof(logMessage), "Sign-in successful with user ID [%s]", userId);
                    logMsg(__MAIN__,logMessage);

                    if ((strcmp(userId,"admin")==0)) {

                        handleAdminMenu(conn); //Handles Admin Operations

                    } else {

                        handleUserMenu(conn,userId); //Handles User Operations
                    }
                }

                break;
            case 2: // Register

                printf("Enter Name: ");
                scanf("%s", name);

                printf("Enter Age: ");
                if (scanf("%u", &age) != 1) {
                    fprintf(stderr, "Invalid age. Please enter a number.\n");
                    clear_input_buffer();
                    sleep(2);
                    break;
                }

                printf("Enter User ID: ");
                scanf("%s", userId);

                initUserSQL(&_userSql,name,age,userId);

                if(_userSql.isUserExist(&_userSql,conn,userId) == 1) {
                    printf("Registration failed. User ID already exist.\n");
                    printf("\nPlease Try Again.\n");
                    snprintf(logMessage,sizeof(logMessage),"Registration failed. User ID already exist. [%s]",userId);
                    logMsg(__MAIN__,logMessage);
                    sleep(2);
                    break;
                }

                regId = _userSql.registerUser(&_userSql, conn, userId, name, age);

                if (regId == 0) {
                    snprintf(logMessage, sizeof(logMessage), "ERROR::registerUser()");
                    logMsg(__MAIN__, logMessage);
                    printf("Registration failed. Please try again.\n");
                    sleep(2);
                } else {
                    snprintf(logMessage, sizeof(logMessage), "Registration successful with user ID [%s]", userId);
                    logMsg(__MAIN__, logMessage);
                    printf("Thank you! You may now sign in!\n");
                    sleep(2);
                }

                break;

            case 3: //Exit

                printf("Exiting...\n");
                close_db(conn);
                closeLogMsg();
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
                printf("Select only from (1), (2) and (3).\n");
                sleep(2);
                break;
        }
    }


    return 0;
}



