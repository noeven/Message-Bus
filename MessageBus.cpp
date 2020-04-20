//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	MessageBus.cpp
	MessageBus class function declarations
*/
//Include MessageBus header file
#include <map>
#include <chrono>
#include "MessageBus.h"
#include "sqlite3.h"
#include "NodeConfigReader.h"

void MessageBus::init()
{
	//Create nodeConfigReader object
	NodeConfigReader* NCR = new NodeConfigReader(dblocation);
	//Link it to this messageBus
	NCR->setMessageBus(this);
	//Provide nodes,topics and subscription information to current messagebus
	NCR->setupNodes();
}

//Class Function to register new messagebus message topics
void MessageBus::registerTopic(const std::string& str) {
	subscriptions[str] = std::vector<Node*>();
}

//Class Function to register new messagebus nodes
void MessageBus::registerNode(Node* node) {
	nodes.insert(node);
}

//Class Function to link nodes to topics
void MessageBus::registerNodeForTopic(Node* node, std::string str) {
	std::vector<Node*> elements = subscriptions[str];
	elements.push_back(node);
	subscriptions[str] = elements;
}
//Class Function to push message to all receiving nodes
void MessageBus::acceptMessage(Message* message) { //possible object slicing
	queue.push(message);
}
//Class Function to print all messages on the queue from top to bottom
void MessageBus::printMessages() {
	while (!queue.empty()) {
		Message tm = *(queue.top());
		std::cout << tm.toString() << std::endl;
		queue.pop();
	}
}
//Class Function to send messages to appropriate nodes based
//on their subscriptions
void MessageBus::handleMessages() {
	while (queue.size()!=0) {
		Message* message = queue.top();  //take the greatest elements in the container
		
 		std::vector<Node*> elements = subscriptions[message->getTopic()];
        
		for (Node* node : elements) {
            node->acceptMessage(message);
			//node->acceptMeesageLTemp(message);
            //node->acceptMessageM(message);
            //std::cout << "Node accept message from Messagebus" <<std::endl;
		}
		queue.pop();
	}
}

void MessageBus::run(){
    //apply while loop so the handleMessages() can be executed continuously
    while(true){
    //auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    handleMessages();
    //std::cout<<"message handled" <<std::endl;
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //std::cout<<duration.count()<<std::endl;

    }
}

void MessageBus::start(){
    std::thread t1 ([this](){this->run();}); //passing a lambda to the constructor of the thread
    t1.detach(); //detach to allow next thread run simultaneously. If we use join here, then the compiler will stock here.
    
}
