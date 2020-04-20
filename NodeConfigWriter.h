//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include <iostream>

class NodeConfigWriter {
private:
	std::string dbLocation;

public:
	NodeConfigWriter(const std::string& dbLocation) : dbLocation(dbLocation) {}
	void clear();
	void writeNode(const std::string& node, const std::string& nodeAddress, int nodePort, const std::string& applicationAddress, int applicationPort);
	void writeTopic(const std::string& topic);
	void writeNodeTopic(const std::string& node, const std::string& topic);
};

