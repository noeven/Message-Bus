//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once

#include <string>

// This is the correct format
class Message {
 protected:
	int priority;
	std::string from;
	std::string topic;

 public:
	Message(int priority, const std::string& from, const std::string& topic) : priority(priority), from(from), topic(topic) {}
	int getPriority();
	std::string getFrom();
	std::string getTopic();
	virtual std::string toString();
};

