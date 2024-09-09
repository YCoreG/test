#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>


#include "../inc/mysql_conn.h"
#include "../inc/user.h"
#include "../inc/menu.h"
#include "../inc/trade.h"
#include "../inc/utilities.h"
#include "../inc/logger.h"
#include "../inc/handler.h"


void handleUserTradeMenu(MYSQL *conn,const char* userId){

    int option = 0;
    int res = 0;
    char tradeBody[MAX_BUFFER_SIZE];
    char temp[MAX_BUFFER_SIZE];
    TradeSql    tradeSql;

    while (1) {

        system("cls");

        showTradeHistoryMenu();//Disply the trade history menu

        res = scanf("%d",&option);
        if(res != 1) {
            clear_input_buffer();
        }

        // Option 1: Display all trades for a user
        if (option == 1) {

            initTrade(&tradeSql);

            // Declare a pointer to hold the array of trades
            Trade    *trade = NULL;
            int size = tradeSql.getAllRecords(&tradeSql,conn,&trade,userId,"","");

            if (size > 0) {
                memset(tradeBody, '\0', sizeof(tradeBody));
                showHeader(tradeBody);
                // Print the number of records and each user
                for (int i = 0; i < size; i++) {
                    snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                            trade[i].id,
                            trade[i].shares,
                            trade[i].symbol,
                            trade[i].marketOrder,
                            trade[i].totalAmount,
                            trade[i].date);
                    printf("%s",temp);
                    strncat(tradeBody, temp, sizeof(tradeBody) - strlen(tradeBody) - 1);
                }

                showFooter();
                sprintf(temp,"handleUserTradeMenu::printing list of trades by user id [%s]",userId);
                logMsg(__MAIN__,temp);
                logMsg(__MAIN__,tradeBody);



            } else if (size == 0) {
                sprintf(temp,"No trade records found for user id [%s]",userId);
                printf("%s",temp);
                logMsg(__MAIN__,temp);
            } else {
                sprintf(temp,"Error for retrieving records for user id [%s]",userId);
                printf("%s",temp);
                logMsg(__MAIN__,temp);
            }

            // Free allocated memory for users
            if (trade != NULL) {
                free(trade);
            }

            printf("\nPress any key to exit: ");
            getch();
            system("cls");
            break;
        } else if(option == 2) {
            char dateFrom[MAX_DATE_LENGTH];
            char dateTo[MAX_DATE_LENGTH];
            int val = 0;
            int res = 0;
            struct tm date_from, date_to;

            do {
                system("cls");
                printf("REMINDER: START DATE MUST BE BEFORE OR SAME WITH END DATE\n");
                // Input start date with validation
                do {
                    printf("Input the correct date format(YYYY-MM-DD) ex. 2024-01-01 \n");
                    printf("Enter the START date): ");
                    scanf("%10s",dateFrom);
                } while ((val = validateDate(dateFrom,&date_from)) == 1);
                // Input start date with validation
                do {
                    //printf("Input the correct date format(YYYY-MM-DD) ex. 2024-01-01 \n");
                    printf("Enter the END date): ");
                    scanf("%10s",dateTo);
                } while ((val = validateDate(dateTo,&date_to)) == 1);

            } while ((res=compareDate(date_from,date_to))==1 );


            initTrade(&tradeSql);
            // Declare a pointer to hold the array of trades
            Trade    *trade = NULL;
            int size = tradeSql.getAllRecords(&tradeSql,conn,&trade,userId,dateFrom,dateTo);

            if (size > 0) {
                memset(tradeBody, '\0', sizeof(tradeBody));
                showHeader(tradeBody);
                // Print the number of records and each user
                for (int i = 0; i < size; i++) {
                    snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                            trade[i].id,
                            trade[i].shares,
                            trade[i].symbol,
                            trade[i].marketOrder,
                            trade[i].totalAmount,
                            trade[i].date);
                    printf("%s",temp);
                    strncat(tradeBody, temp, sizeof(tradeBody) - strlen(tradeBody) - 1);;
                }

                showFooter();
                sprintf(temp,"handleUserTradeMenu::printing list of trades by user id [%s]",userId);
                logMsg(__MAIN__,temp);
                logMsg(__MAIN__,tradeBody);

            } else if (size == 0) {
                sprintf(temp,"No trade records found for user id [%s]",userId);
                printf("%s",temp);
                logMsg(__MAIN__,temp);
            } else {
                sprintf(temp,"Error for retrieving records for user id [%s]",userId);
                printf("%s",temp);
                logMsg(__MAIN__,temp);
            }

            // Free allocated memory for users
            if (trade != NULL) {
                free(trade);
            }

            printf("\nPress any key to exit: ");
            getch();
            system("cls");
            break;

        } else if(option == 3) {
            return;
        } else {
            printf("Invalid option. Please try again.\n");
            printf("Select only from (1), (2), and (3).\n");
            sleep(2);
        }
   }
}




void handleUserMenu(MYSQL *conn,const char* userId){

    srand(time(0));
    int option = 0;
    TradeSql    tradeSql;
    Trade    trade;
    char temp[MAX_BUFFER_SIZE];
    int tradeId = 0;


    strncpy(trade.userId,userId,sizeof(trade.userId));

    while (1) {
        system("cls");
        showUserMenu();


        if (scanf("%u", &option) != 1) {
            clear_input_buffer();
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            sleep(2);
            continue;
        }


        switch(option) {
            case 1:
                //create random dummy data to simulate TRADE COMPLETE ORDER
                createDummyData(trade.symbol,&trade.shares,&trade.totalAmount);
                strncpy(trade.marketOrder,"BOUGHT",sizeof(trade.marketOrder));

                initTradeSql(&tradeSql,&trade);
                if ((tradeId = tradeSql.createTrade(&tradeSql,conn)) == 0) {
                    logMsg(__MAIN__,"handleUserMenu::ERROR on createTrade[BOUGHT]");
                    break;
                }

                printf("You have simulated on buying stocks. Thank you!\n");
                sprintf(temp,"handleUserMenu::User[%s] bought shares of [%d] with amount of [%.02f] with trade id[%d]",userId,trade.shares,trade.totalAmount,tradeId);
                logMsg(__MAIN__,temp);
                sleep(2);
                break;
            case 2:
                //create random dummy data to simulate TRADE COMPLETE ORDER
                createDummyData(trade.symbol,&trade.shares,&trade.totalAmount);
                strncpy(trade.marketOrder,"SELL",sizeof(trade.marketOrder));

                initTradeSql(&tradeSql,&trade);
                if ((tradeId = tradeSql.createTrade(&tradeSql,conn)) == 0) {
                    logMsg(__MAIN__,"handleUserMenu::ERROR on createTrade[SELL]");
                    break;
                }

                printf("You have simulated on selling stocks. Thank you!\n");
                sprintf(temp,"handleUserMenu::User[%s] selling shares of [%d] with amount of [%.02f] with trade id[%d]",userId,trade.shares,trade.totalAmount,tradeId);
                logMsg(__MAIN__,temp);
                sleep(2);
                break;
            case 3:
                handleUserTradeMenu(conn,userId);
                break;

            case 4:
                printf("You have successfully logout\n");
                sprintf(temp,"handleUserMenu::User[%s] had successfully logout",userId);
                logMsg(__MAIN__,temp);
                sleep(2);
                system("cls");
                return;
            default:
                printf("Invalid option. Please try again.\n");
                printf("Select only from (1), (2), (3) and (4).\n");
                sleep(2);
                system("cls");
                break;
        }

    }

}

void handleEditTrade(MYSQL *conn,char* userId) {

    int tradeId = 0;
    int option = 0;
    char tradeBody[MAX_BUFFER_SIZE];
    char temp[MAX_BUFFER_SIZE];
    Trade    *trade = NULL;
    TradeSql    tradeSql;

    initTrade(&tradeSql);

    printf("Enter Trade ID: ");
    scanf("%d", &tradeId);

    int sz = tradeSql.getTradeRecById(&tradeSql,conn,&trade,tradeId);
    if (sz > 0 ) {
        char key[8];

        memset(tradeBody, '\0', sizeof(tradeBody));
        showHeader(tradeBody);
        // Print the number of records and each user
        for (int i = 0; i < sz; i++) {
            snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                    trade[i].id,
                    trade[i].shares,
                    trade[i].symbol,
                    trade[i].marketOrder,
                    trade[i].totalAmount,
                    trade[i].date);

            printf("%s",temp);
            strncat(tradeBody, temp, sizeof(tradeBody) - strlen(tradeBody) - 1);
        }

        showFooter();
        sprintf(temp,"handleEditTrade::printing details of trade:[%d] by user id [%s]",tradeId,userId);
        logMsg(__MAIN__,temp);
        logMsg(__MAIN__,tradeBody);

        int iShare = 0;
        int res = 0;
        float fAmount = 0;

        strcpy(key,"Y");
        do { //reiterate until done on editing
            showAdminEditMenu();
            scanf("%d",&option);
            switch(option) {
                case 1:
                        printf("Enter new number of shares: ");
                        scanf("%d", &iShare);

                        printf("Do you want to save your changes? Y/N: ");
                        scanf("%1s", key);

                        if(strcmp(key,"Y")== 0) {
                            if( (res = tradeSql.updateTradeShares(&tradeSql,conn,tradeId,iShare) == 1 )){
                                sprintf(temp,"handleEditTrade::updateTradeShares::ERROR updating for trade:[%d] by user id [%s]",tradeId,userId);
                                printf("%s",temp);
                                logMsg(__MAIN__,temp);
                                break;
                            }

                            memset(temp, '\0', sizeof(temp));
                            sprintf(temp,"handleEditTrade::update successfull for trade:[%d] by user id [%s]",tradeId,userId);
                            logMsg(__MAIN__,temp);

                            //DISPLAY TRADE RECORD WITH THE NEW UPDATES.
                            tradeSql.getTradeRecById(&tradeSql,conn,&trade,tradeId);

                            memset(tradeBody, '\0', sizeof(tradeBody));
                            showHeader(tradeBody);
                            // Print the number of records and each user
                            for (int i = 0; i < sz; i++) {
                                snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                                        trade[i].id,
                                        trade[i].shares,
                                        trade[i].symbol,
                                        trade[i].marketOrder,
                                        trade[i].totalAmount,
                                        trade[i].date);

                                printf("%s",temp);
                                strcat(tradeBody,temp);
                            }

                            showFooter();
                            memset(temp, '\0', sizeof(temp));
                            sprintf(temp,"handleEditTrade::printing details of new update of trade:[%d] by user id [%s]",tradeId,userId);
                            logMsg(__MAIN__,temp);
                            logMsg(__MAIN__,tradeBody);

                        } else {
                            break;
                        }
                        break;
                case 2:
                        printf("Enter new Amount: ");
                        scanf("%f", &fAmount);

                        printf("Do you want to save your changes? Y/N: ");
                        scanf("%1s", key);

                        if(strcmp(key,"Y")== 0) {
                            if((res = tradeSql.updateTradeAmount(&tradeSql,conn,tradeId,fAmount) == 1 )){
                                sprintf(temp,"handleEditTrade::updateTradeAmount::ERROR updating for trade:[%d] by user id [%s]",tradeId,userId);
                                printf("%s",temp);
                                logMsg(__MAIN__,temp);
                                break;
                            }

                            memset(temp, '\0', sizeof(temp));
                            sprintf(temp,"handleEditTrade::update successfull for trade:[%d] by user id [%s]",tradeId,userId);
                            logMsg(__MAIN__,temp);


                            //DISPLAY TRADE RECORD WITH THE NEW UPDATES.
                            tradeSql.getTradeRecById(&tradeSql,conn,&trade,tradeId);

                            memset(tradeBody, '\0', sizeof(tradeBody));
                            showHeader(tradeBody);
                            // Print the number of records and each user
                            for (int i = 0; i < sz; i++) {
                                snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                                        trade[i].id,
                                        trade[i].shares,
                                        trade[i].symbol,
                                        trade[i].marketOrder,
                                        trade[i].totalAmount,
                                        trade[i].date);

                                printf("%s",temp);
                                strcat(tradeBody,temp);
                            }

                            showFooter();
                            memset(temp, '\0', sizeof(temp));
                            sprintf(temp,"handleEditTrade::printing details of new update of trade:[%d] by user id [%s]",tradeId,userId);
                            logMsg(__MAIN__,temp);
                            logMsg(__MAIN__,tradeBody);

                        } else {
                            break;
                        }

                        break;
                case 3:
                        return;
                default:
                       printf("Invalid option. Please try again.\n");
                        break;
            }

            printf("Do you still want to continue? Y/N: ");
            scanf("%1s",key);

        } while ((strcmp(key,"Y")== 0));


        system("cls");

    } else {//sz
        printf("Trade Id:[%d] for user:[%s] not found.",tradeId,userId);
        sprintf(temp,"handleEditTrade::Trade Id:[%d] for user:[%s] not found.",tradeId,userId);
        logMsg(__MAIN__,temp);
    }
}



void handleAdminMenu(MYSQL *conn){
    int option;
    userSql    _userSql;
    TradeSql   tradeSql;
    char userId[MAX_USER_ID_LENGTH];
    char userBody[MAX_BUFFER_SIZE];
    char tradeBody[MAX_BUFFER_SIZE];
    char temp[MAX_BUFFER_SIZE];
    char key[2];

    while(1) {

        showAdminMenu(); //Display Admin Menu

        if (scanf("%d", &option) != 1) {
            clear_input_buffer();
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            sleep(2);
            continue;
        }


        switch(option) {
            case 1:
                initUser(&_userSql);
                Person    *person = NULL;

                strcpy(userId,"admin");
                int size = _userSql.getAllUser(&_userSql,conn,&person,userId);

                if (size > 0) {
                    system("cls");

                    memset(userBody, '\0', sizeof(userBody));

                    showUserHeader(userBody);//Display User header
                    // Print user details
                    for (int i = 0; i < size; i++) {
                        snprintf(temp,sizeof(temp),"| %-2d | %-15s | %-3d | %-8s |\n",
                               person[i].id,
                               person[i].name,
                               person[i].age,
                               person[i].userId);

                        printf("%s",temp);

                        strncat(userBody, temp, sizeof(userBody) - strlen(userBody) - 1);
                    }


                    logMsg(__MAIN__,"handleAdminMenu::printing list of users");
                    logMsg(__MAIN__,userBody);
                    showUserFooter();

                    printf("\nPress any key to exit: ");
                    getch();
                    system("cls");
                    break;
                } else if (size == 0) {
                    printf("Table user is empty. Use Register option to add user\n");
                    logMsg(__MAIN__,"handleAdminMenu::Table user is empty.");
                } else {
                    printf("Error retrieving user.\n");
                    logMsg(__MAIN__,"handleAdminMenu::Error on retrieving user.\n");
                }

                break;
            case 2:
                system("cls");
                printf("Display User's Trades\n");
                printf("Enter User ID: ");
                scanf("%s",userId);

                initTrade(&tradeSql);
                // Declare a pointer to hold the array of Trades
                Trade    *trade = NULL;
                int cnt = tradeSql.getAllRecords(&tradeSql,conn,&trade,userId,"","");

                if (cnt > 0) {

                    memset(tradeBody, '\0', sizeof(tradeBody));
                    showHeader(tradeBody);
                    // Print the number of records and each user
                    for (int i = 0; i < cnt; i++) {
                        snprintf(temp,sizeof(temp),"| %-2d | %-6d | %-6s | %-6s | %-11.02f  | %-11s  |\n",
                                trade[i].id,
                                trade[i].shares,
                                trade[i].symbol,
                                trade[i].marketOrder,
                                trade[i].totalAmount,
                                trade[i].date);
                        printf("%s",temp);
                        strcat(tradeBody,temp);
                    }

                    showFooter();
                    sprintf(temp,"handleAdminMenu::printing list of trades by user id [%s]",userId);
                    logMsg(__MAIN__,temp);
                    logMsg(__MAIN__,tradeBody);


                    printf("Do you want to make changes on trades of user id %s? Y/N : ", userId);
                    scanf("%1s",key);

                    if(strcmp(key,"Y")== 0) {

                        handleEditTrade(conn,userId);
                        break;

                    } else { //key = "N"
                        system("cls");
                        break;
                    }

                    break;
                } else if (cnt == 0) { //size
                    sprintf(temp,"No trade records found for user id [%s]",userId);
                    printf("%s",temp);
                    logMsg(__MAIN__,temp);

                } else {
                    printf("Error retrieving trades.\n");
                    logMsg(__MAIN__,"handleAdminMenu::Error on retrieving trades.");


                }

                sleep(2);
                system("cls");
                break;
            case 3:
                printf("You have been logout\n");
                logMsg(__MAIN__,"handleAdminMenu::Admin Logout");
                sleep(2);
                system("cls");

                return;
            default:
                printf("Invalid option. Please try again.\n");
                printf("Select only from (1), (2) and (3).\n");
                sleep(2);
                system("cls");
                break;
        }

    }

}
