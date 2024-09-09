#include <stdio.h>
#include <string.h>
#include "../inc/menu.h"

void showMainMenu() {
    printf("\n--- OMS XO System ---\n");
    printf("(1) Sign In\n");
    printf("(2) Register\n");
    printf("(3) Exit\n");
    printf("Select an option: ");
}


void showUserMenu() {
    printf("\n--- W E L C O M E ---");
    printf("\n--- User Menu ---\n");
    printf("(1) Buy Stocks\n");
    printf("(2) Sell Stocks\n");
    printf("(3) My Trades\n");
    printf("(4) Logout\n");
    printf("Select an option: ");
}


void showTradeHistoryMenu() {
    printf("\n--- User Trade History ---\n");
    printf("1. All Trade History\n");
    printf("2. Input Date Range\n");
    printf("3. Back\n");
    printf("Select an option: ");
}


void showHeader(char* tradeHeader) {
    const char *header = "\n+----+----------------------------------------------------------------+\n"
                         "| Id | Shares | Symbol |  Order | Total Amount | Date                 |\n"
                         "+----+----------------------------------------------------------------+\n";
    printf("%s", header);
    strcpy(tradeHeader, header);
}


void showFooter() {
    printf("+----+----------------------------------------------------------------+\n");
}


void showUserHeader(char* userHeader) {
    const char *header = "\n+----+----------------------------------+\n"
                         "| Id | Name            | Age |  User ID |\n"
                         "+----+----------------------------------+\n";
    printf("%s", header);
    strcpy(userHeader, header);
}


void showUserFooter() {
    printf("+----+----------------------------------+\n");
}


void showAdminMenu() {
    printf("\n--- W E L C O M E ---\n");
    printf("\n--- Admin Menu ---\n");
    printf("(1) Display Users\n");
    printf("(2) Search Trades\n");
    printf("(3) Logout\n");
    printf("Select an option: ");
}


void showAdminEditMenu() {
    printf("\nWhich of the following do you want to change?\n");
    printf("(1) Number of Shares\n");
    printf("(2) Total Amount\n");
    printf("(3) Cancel\n");
    printf("Select an option: ");
}
