//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include <string>
#include "MessageBus.h"

class NodeConfigReader {
private:
	std::string dblocation;
	MessageBus* bus = nullptr;
	
public:
	NodeConfigReader(const std::string dblocation) : dblocation(dblocation) {}
	void setMessageBus(MessageBus* bus);
	void setupNodes();
};

