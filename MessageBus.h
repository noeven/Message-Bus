//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once

#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Node.h"
#include "Message.h"
#include "MessageCompare.cpp"

class MessageBus {
private:
	std::set<Node*> nodes;
	std::unordered_map<std::string, std::vector<Node*>> subscriptions;
	std::priority_queue<Message*, std::vector<Message*>, MessageCompare> queue;
	std::string dblocation;				//This is new
	void run();

public:
	MessageBus(const std::string dblocation): dblocation(dblocation) {}
	void init();						//This is new
	void registerTopic(const std::string&);
	void registerNode(Node*);
	void registerNodeForTopic(Node*, std::string);
	void acceptMessage(Message*);
	void printMessages();
	void handleMessages();
	void start();
    
};
