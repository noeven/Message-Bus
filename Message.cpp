//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	Message.cpp
	Message Superclass function declarations
*/

//Include class header
#include <string>
#include "Message.h"

//Class function to return message priority
int Message::getPriority() 
{
	return priority;
}

//Class function to return message sender
std::string Message::getFrom() 
{
	return from;
}
//Class function to return message topic
std::string Message::getTopic() 
{
	return topic;
}
//Class toString function to display all information of messag
std::string Message::toString() 
{
	return "MESSAGE " + std::to_string(priority) + " " + from + " " + topic + " Base Message";
}

