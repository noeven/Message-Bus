//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	TextMessage.cpp
	TextMessage class function declarations
*/

//Include class header
#include "TextMessage.h"

//Class function to return message content
std::string TextMessage::getText()  {
	return text;
}
//Class toString function to display all information of message
std::string TextMessage::toString()  {
	return "MESSAGE " + std::to_string(priority) + " " + from + " " + topic + " T " + text;
}
