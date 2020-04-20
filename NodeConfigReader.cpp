//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#include "NodeConfigReader.h"
#include "sqlite3.h"

//Select messageBus to give info to
void NodeConfigReader::setMessageBus(MessageBus* bus)
{	
	NodeConfigReader::bus = bus;
    fprintf(stdout, "MessageBus succesfully linked to NodeConfigReader\n");
}

/* Callback function that puts fetched table data into a 2D string vector */
static int callback(void* data, int argc, char** argv, char** azColName) {
    
    int i;
    std::vector<std::vector<std::string>>* tableData = static_cast<std::vector<std::vector<std::string>>*>(data);
    std::vector<std::string> Row;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        Row.push_back(argv[i] ? argv[i] : "NULL");

    }
    tableData->push_back(Row);
    data = static_cast<void*>(&tableData);
    printf("\n");
    return 0;
}
/*If the above callback is provided in sqlite_exec() routine as the third argument,
SQLite will call this callback function for each record processed in each SELECT statement executed within the SQL argument.
*/


//Read database file and pass everything to messagebus functions
void NodeConfigReader::setupNodes()
{
    /*Create some Local vars*/
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;
    char* sql;
    std::vector<std::vector<std::string>> tableData2D;
    std::vector<Node*> nodes;

    /*  ~~~~~~~~~~~~~~~~~~  Fetch Topics  ~~~~~~~~~~~~~~~~~~~~~~ */
    /* Open database */
    rc = sqlite3_open("/Users/evenwu/Documents/UT/2A/Programming 2/Project/messagebus/Challenge4_FINAL/node_clean.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = (char*)"SELECT * FROM Topics";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, static_cast<void*>(&tableData2D), &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }

    /* Load results into Messagebus */
    std::cout << "Passing TOPIC table contents to the MessageBus\n" << std::endl;
    for (int i = 0; i < static_cast<int>(tableData2D.size()); i++) {
        bus->registerTopic(tableData2D[i][0]);
    }
    tableData2D.clear();

    /*  ~~~~~~~~~~~~~~~~~~  Fetch Nodes  ~~~~~~~~~~~~~~~~~~~~~~ */
    /* Create SQL statement */
    sql = (char*)"SELECT * FROM Nodes";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, static_cast<void*>(&tableData2D), &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }

    /* Load results into Messagebus */
    std::cout << "Passing NODE table contents to the MessageBus\n" << std::endl;
    int i;
    for (i = 0; i < static_cast<int>(tableData2D.size()); i++) {

        //Create new Node and register it to messageBus
        Node* node = new Node(tableData2D[i][0], tableData2D[i][1], std::stoi(tableData2D[i][2]), tableData2D[i][3], std::stoi(tableData2D[i][4]), bus);
        bus->registerNode(node);
        nodes.push_back(node);
        //??delete node; 
    }
    tableData2D.clear();

    /*  ~~~~~~~~~~~~~~~~~~  Fetch NodeTopics  ~~~~~~~~~~~~~~~~~~~~~~ */
    /* Create SQL statement */
    sql = (char*)"SELECT * FROM NodeTopics";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, static_cast<void*>(&tableData2D), &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        fprintf(stdout, "Operation done successfully\n");
    }
    std::cout << "Passing NODETOPICS table contents to the MessageBus\n" << std::endl;
    for (i = 0; i < static_cast<int>(tableData2D.size()); i++) {
        std::string nodeName = tableData2D[i][0];
        std::string topic = tableData2D[i][1];
        fprintf(stdout, "Checking for node %s and topic %s\n", tableData2D[i][0].c_str(), tableData2D[i][1].c_str());
        
        int known = 0;
        int j = 0;
        while (known != 1) {
            if (nodeName == nodes[j]->getName()) {
                Node* node = nodes[j];
                bus->registerNodeForTopic(node, topic);
                fprintf(stdout, "Adding subscription for node %s to topic %s\n", tableData2D[i][0].c_str(), tableData2D[i][1].c_str());
                known = 1;
            }
            if (j > 3) {
                fprintf(stdout, "No Node with name %s Known in system!\n", nodes[j]->getName().c_str());
                break;
            }
            else {
                j++;
            }
        }
        
        

            
        
    }
       
    tableData2D.clear();


    /* Close DB connection */
    sqlite3_close(db);

  
}
