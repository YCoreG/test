#include "../inc/user.h"


int GetAllUser(userSql* sql, MYSQL *conn, Person **person, const char *userId) {
    char query[512];

    if (strcmp(userId, "admin") == 0) {
        snprintf(query, sizeof(query), "SELECT id, name, age, user_id FROM tbl_user WHERE user_id != 'admin'");
    } else {
        snprintf(query, sizeof(query), "SELECT id, name, age, user_id FROM tbl_user WHERE user_id = '%s'", userId);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return -1;
    }

    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        mysql_free_result(result);
        return 0;  // No records found
    }

    *person = (Person *)malloc(num_rows * sizeof(Person));
    if (*person == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        mysql_free_result(result);
        return -1;
    }

    MYSQL_ROW row;
    int i = 0;
    while ((row = mysql_fetch_row(result))) {
        (*person)[i].id = atoi(row[0]);

        strncpy((*person)[i].name, row[1], sizeof((*person)[i].name) - 1);
        (*person)[i].name[sizeof((*person)[i].name) - 1] = '\0'; // Ensure null-termination

        (*person)[i].age = atoi(row[2]);

        strncpy((*person)[i].userId, row[3], sizeof((*person)[i].userId) - 1);
        (*person)[i].userId[sizeof((*person)[i].userId) - 1] = '\0'; // Ensure null-termination

        i++;
    }

    mysql_free_result(result);
    return num_rows;
}


int IsUserExist(userSql* sql, MYSQL *conn, const char* userId) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM tbl_user WHERE user_id = '%s'", userId);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT query failed: %s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return -1;
    }

    int num_rows = mysql_num_rows(res);
    mysql_free_result(res);

    return (num_rows > 0) ? 1 : 0;
}


int RegisterUser(userSql* sql, MYSQL *conn, const char* userId, const char *name, int age) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO tbl_user (user_id, name, age) VALUES ('%s', '%s', %d)", userId, name, age);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "INSERT query failed: %s\n", mysql_error(conn));
        return 0;  // Registration failed
    }

    return (int)mysql_insert_id(conn);  // Return the ID of the newly created user
}


void initUser(userSql* sql) {
    sql->getAllUser = GetAllUser;
    sql->isUserExist = IsUserExist;
    sql->registerUser = RegisterUser;
}


void initUserSQL(userSql* sql, const char* name, int age, const char* userId) {
    strncpy(sql->dataUser.name, name, sizeof(sql->dataUser.name) - 1);
    sql->dataUser.name[sizeof(sql->dataUser.name) - 1] = '\0'; // Ensure null-termination

    strncpy(sql->dataUser.userId, userId, sizeof(sql->dataUser.userId) - 1);
    sql->dataUser.userId[sizeof(sql->dataUser.userId) - 1] = '\0'; // Ensure null-termination

    sql->dataUser.age = age;

    sql->getAllUser = GetAllUser;
    sql->isUserExist = IsUserExist;
    sql->registerUser = RegisterUser;
}
