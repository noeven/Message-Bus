//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	ImageMessage.cpp
	ImageMessage class function declarations
*/


//Include class header
#include "ImageMessage.h"

//Class function to return message content
std::string ImageMessage::getImage() {
	return base64encoded;
}
//Class toString function to display all information of message
std::string ImageMessage::toString() {
	return "MESSAGE " + std::to_string(priority) + " " + from + " " + topic + " I " + base64encoded;
}
