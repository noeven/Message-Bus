//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	MeasurementMessage.cpp
	MeasurementMessage class function declarations
*/


//Include class header
#include "MeasurementMessage.h"

//Class function to return message content
double MeasurementMessage::getMeasurement() {
	return m;
}
//Class toString function to display all information of message
std::string MeasurementMessage::toString() {
	return "MESSAGE " + std::to_string(priority) + " " + from + " " + topic + " M " + std::to_string(m);
}
