#include "../inc/trade.h"

// Function to update a user's age based on ID
int sql_updateTradeShares(struct TRADE_SQL *sql,MYSQL *conn, int tradeId, int share) {
    char query[256];

    // Prepare the SQL update statement
    snprintf(query, sizeof(query), "UPDATE tbl_trades SET num_of_shares = %d WHERE id = %d", share, tradeId);

    // Execute the SQL update statement
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to update number of shares: %s\n", mysql_error(conn));
        return 1;
    }

    printf("Trade shares updated successfully.\n");

    return 0;
}

int sql_updateTradeAmount(struct TRADE_SQL *sql,MYSQL *conn, int tradeId, float amount) {
    char query[256];

    // Prepare the SQL update statement
    snprintf(query, sizeof(query), "UPDATE tbl_trades SET total_amount = %.02f WHERE id = %d", amount, tradeId);

    // Execute the SQL update statement
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to update total amount: %s\n", mysql_error(conn));
        return 1;
    } else {
        printf("Trade amount updated successfully.\n");
    }

    return 0;
}

int sql_getTradeRecById(struct TRADE_SQL*sql,MYSQL *conn, Trade **dataTrade, unsigned int tradeId){
    // Query to get all users
    char query[512];

    sprintf(query,"SELECT id,num_of_shares,symbol,market_order,total_amount,date_executed FROM tbl_trades where id = %d",tradeId);


    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
        return -1;
    }

    // Store result set
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return -1;
    }

    // Get the number of rows in the result
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        mysql_free_result(result);
        return 0;
    }

    // Allocate memory for the array of users
    *dataTrade = (Trade *)malloc(num_rows * sizeof(Trade));
    if (*dataTrade == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        mysql_free_result(result);
        return -1;
    }

    // Fetch each row and store it in the array of structures
    MYSQL_ROW row;
    int i = 0;
     while ((row = mysql_fetch_row(result))) {
        (*dataTrade)[i].id = atoi(row[0]);
        (*dataTrade)[i].shares = atoi(row[1]);
        strncpy((*dataTrade)[i].symbol, row[2], sizeof((*dataTrade)[i].symbol) - 1);
        strncpy((*dataTrade)[i].marketOrder, row[3], sizeof((*dataTrade)[i].marketOrder) - 1);
        (*dataTrade)[i].totalAmount = atof(row[4]);
        strncpy((*dataTrade)[i].date, row[5], sizeof((*dataTrade)[i].date) - 1);
        i++;
    }

    // Free result set
    mysql_free_result(result);

    return num_rows;  // Return the number of rows (records)
}
int sql_getAllRecords(struct TRADE_SQL *sql, MYSQL *conn, Trade **dataTrade, const char *user_id, const char* dateFrom, const char* dateTo) {

    // Query to get all users
    char query[512];

    //const char *query = "SELECT id,num_of_shares,symbol,market_order,total_amount,date_executed FROM tbl_trades";
    if ((strlen(dateFrom)== 0))
        sprintf(query,"SELECT id,num_of_shares,symbol,market_order,total_amount,date_executed FROM tbl_trades where user_id = '%s'",user_id);
    else
        sprintf(query,"SELECT id,num_of_shares,symbol,market_order,total_amount,date_executed FROM tbl_trades where user_id = '%s' and (date_executed >= '%s 00:00:00' and date_executed <= '%s 23:59:59')",user_id,dateFrom,dateTo);



    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
        return -1;
    }


    // Store result set
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return -1;
    }

    // Get the number of rows in the result
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        mysql_free_result(result);
        return 0;
    }

    // Allocate memory for the array of users
    *dataTrade = (Trade *)malloc(num_rows * sizeof(Trade));
    if (*dataTrade == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        mysql_free_result(result);
        return -1;
    }

    // Fetch each row and store it in the array of structures
    MYSQL_ROW row;
    int i = 0;

    while ((row = mysql_fetch_row(result))) {
        (*dataTrade)[i].id = atoi(row[0]);
        (*dataTrade)[i].shares = atoi(row[1]);
        strncpy((*dataTrade)[i].symbol, row[2], sizeof((*dataTrade)[i].symbol) - 1);
        strncpy((*dataTrade)[i].marketOrder, row[3], sizeof((*dataTrade)[i].marketOrder) - 1);
        (*dataTrade)[i].totalAmount = atof(row[4]);
        strncpy((*dataTrade)[i].date, row[5], sizeof((*dataTrade)[i].date) - 1);
        i++;
    }


    // Free result set
    mysql_free_result(result);

    return num_rows;  // Return the number of rows (records)
}



int sql_createTrade(struct TRADE_SQL* sql,MYSQL *conn) {
    char query[512];

    sprintf(query,"INSERT INTO tbl_trades(num_of_shares,symbol,market_order,user_id,total_amount,date_executed) VALUES (%d,'%s','%s','%s',%.02f,now())",
            sql->dataTrade.shares,
            sql->dataTrade.symbol,
            sql->dataTrade.marketOrder,
            sql->dataTrade.userId,
            sql->dataTrade.totalAmount
            );

    if (mysql_query(conn, query)) {
        fprintf(stderr, "INSERT query failed: %s\n", mysql_error(conn));
        return 0;  // Registration failed
    }

    int last_id = mysql_insert_id(conn);
    //printf("User registered successfully! User ID: %s, Name: %s, Age: %d\n", user_id, name, age);
    return last_id;  // Registration successful
}


void initTrade(TradeSql* sql) {
    sql->getAllRecords = sql_getAllRecords;
    sql->getTradeRecById = sql_getTradeRecById;
    sql->updateTradeShares = sql_updateTradeShares;
    sql->updateTradeAmount = sql_updateTradeAmount;
     return;
}

void initTradeSql(TradeSql* sql, Trade* structDataTrade) {

    sql->dataTrade.id = structDataTrade->id;
    sql->dataTrade.shares = structDataTrade->shares;
    sql->dataTrade.totalAmount = structDataTrade->totalAmount;
    strncpy(sql->dataTrade.symbol,structDataTrade->symbol,sizeof(sql->dataTrade.symbol));
    strncpy(sql->dataTrade.marketOrder,structDataTrade->marketOrder,sizeof(sql->dataTrade.marketOrder));
    strncpy(sql->dataTrade.userId,structDataTrade->userId,sizeof(sql->dataTrade.userId));


     // Assign the function pointer to the method implementation
    sql->createTrade = sql_createTrade;


    return;
}

// Register a new user
