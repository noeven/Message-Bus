//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#define _CRT_SECURE_NO_WARNINGS
#include "NodeConfigWriter.h"
#include "sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("Inserting %s into %s\n", argv[i] ? argv[i] : "NULL", azColName[i]);
    }
    printf("\n");
    return 0;
}

//Clears all fields of the database, resetting it
void NodeConfigWriter::clear()
{
    // Local vars
    sqlite3* ppdb;
    char* zErrMsg = 0; 
    int rc;
    char* sql;
    
    // Try to open database
    rc = sqlite3_open(dbLocation.c_str(), &ppdb);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(ppdb));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Define the sql statement to clean all 3 tables
    sql = (char*)"DELETE from NodeTopics;"\
        "DELETE from Nodes;"\
        "DELETE from Topics;";

    //Try to execute the SQL statement
    rc = sqlite3_exec(ppdb, sql, nullptr, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records DELETED successfully\n");
    }

    //Close the connection
    sqlite3_close(ppdb);
}

void NodeConfigWriter::writeNode(const std::string& node, const std::string& nodeAddress, int nodePort, const std::string& applicationAddress, int applicationPort)
{
    // Local vars
    sqlite3* ppdb;
    char* zErrMsg = 0;
    int rc;
    char sql[500];


    // Try to open database
    rc = sqlite3_open(dbLocation.c_str(), &ppdb);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(ppdb));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Define the sql statement 
    sprintf(sql, "INSERT INTO Nodes VALUES('%s','%s','%i','%s','%i')", node.c_str(), nodeAddress.c_str(), nodePort, applicationAddress.c_str(), applicationPort);
    
    //Try to execute the SQL statement
    rc = sqlite3_exec(ppdb, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records INSERTED successfully\n");
    }

    //Close the connection
    sqlite3_close(ppdb);
}

void NodeConfigWriter::writeTopic(const std::string& topic)
{
    // Local vars
    sqlite3* ppdb;
    char* zErrMsg = 0; //error message var?
    int rc;
    char sql[50];


    // Try to open database
    rc = sqlite3_open(dbLocation.c_str(), &ppdb);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(ppdb));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Define the sql statement 
    sprintf(sql,"INSERT INTO Topics VALUES('%s')",topic.c_str());

    //Try to execute the SQL statement
    rc = sqlite3_exec(ppdb, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records INSERTED successfully\n");
    }

    //Close the connection
    sqlite3_close(ppdb);
}

void NodeConfigWriter::writeNodeTopic(const std::string& node, const std::string& topic)
{
    // Local vars
    sqlite3* ppdb;
    char* zErrMsg = 0; //error message var?
    int rc;
    char sql[60]; //50 is not enough for "Temperature" and "temperature"


    // Try to open database
    rc = sqlite3_open(dbLocation.c_str(), &ppdb);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(ppdb));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    // Define the sql statement 
    sprintf(sql, "INSERT INTO NodeTopics VALUES('%s','%s')", node.c_str() ,topic.c_str() );


    //Try to execute the SQL statement
    rc = sqlite3_exec(ppdb, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Records INSERTED successfully\n");
    }

    //Close the connection
    sqlite3_close(ppdb);
}
