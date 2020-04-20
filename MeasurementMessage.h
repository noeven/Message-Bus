//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include "Message.h"
class MeasurementMessage : public Message {
private:
	double m; //double
public:
	MeasurementMessage(int priority, const std::string& from, const std::string& topic, double m) : Message(priority, from, topic), m(m) {};
	double getMeasurement();
	virtual std::string toString();
};


