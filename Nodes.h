//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include "MessageBus.h"

class Nodes {
private:
	MessageBus* bus;
	void run();
public:
	Nodes(MessageBus* bus) : bus(bus) {}
	void start();
};

