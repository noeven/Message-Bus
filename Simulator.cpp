//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*
The simulator is to simulate a robot system with following modules: Logic, Temperature sensor, Camera module, and Servo module.
Logic module processes the input and commands the actuator and sensors.
    - If temp is higher then 37, logic will send meesage to servo, making positive movement, and vice versa.
    - The temperature record will be stored locally as log file for future service.
    - The snapshot, or the image taken by camera module, will be stored as well for the purpose of recording data.
Temperature sensor measures the temperature by logics' command and sends it back to logic module.
    - If temperature is higher then 37, the servo needs to make a positive movement; if temperature is lower then 33, the servo needs to make a nagative movement.
Camera module take the snapshot from webcame by logics' command and sends it back to logic module.
Servo module change the position by logics' command.
    - If Servo receive the message with signal:1 from logic module, it moves positively, and vice versa.
 
 If you are running on the macOS, please load the list.plist file and change Xcode setting based on following website: https://stackoverflow.com/questions/55518922/missing-info-plist-file-for-c-command-line-tool-application-within-xcode
 
*/
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "Message.h"
#include "TextMessage.h"
#include "MeasurementMessage.h"
#include "ImageMessage.h"
#include "Node.h"
#include "MessageBus.h"
#include "NodeConfigReader.h"
#include "NodeConfigWriter.h"
#include "Nodes.h"


int main() {
    //clear text file of temperature log file
    std::ofstream outdata;
    outdata.open("/Users/evenwu/Documents/UT/2A/Programming 2/Project/messagebus/Challenge4_FINAL/text.txt",std::ios::trunc); //Change this to the desired local address
    outdata.close();
    
    //clear db database
    std::string db = "/Users/evenwu/Documents/UT/2A/Programming 2/Project/messagebus/Challenge4_FINAL/node_clean.db"; //Change this to load you db file
	NodeConfigWriter* n = new NodeConfigWriter(db);
	n->clear();

    //start to step up database table
	n->writeNode("Logic", "localhost", 10000, "localhost", 20000);
	n->writeNode("Temperature", "localhost", 10001, "localhost", 20001);
	n->writeNode("Camera", "localhost", 10002, "localhost", 20002);
    n->writeNode("Servo", "localhost", 10003, "localhost", 20003);
    //Set up topic
	n->writeTopic("logic");
	n->writeTopic("measurement");
	n->writeTopic("servo");
    //Subscribe specific topics to the nodes
	n->writeNodeTopic("Logic", "logic");
	n->writeNodeTopic("Servo", "servo");
    n->writeNodeTopic("Temperature", "measurement");
	n->writeNodeTopic("Camera", "measurement");
    std::cout<<"======"<<std::endl;
    
    //The thread of messagebus starts running
	MessageBus* bus = new MessageBus(db);
	bus->init();
	bus->start();

    std::cout << "==========" << std::endl;
    //The thread of Logic signal generator starts running
	Nodes* nodes = new Nodes(bus);
	nodes->start();
    
    //User press any key to stop processing
	std::string str;
	std::getline(std::cin, str);

	// clean up
    delete n;
    delete bus;
    delete nodes;

}
