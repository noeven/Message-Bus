//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	MessageCompare.cpp
	MessageCompare class function declarations
*/

//Dependencies
#include <iostream>

#include "Message.h"

//Class that compares priority of message a and b
//Returns boolean 1 if priority of a > b
class MessageCompare {
public:
	bool operator()(Message* a, Message* b) {
		return (a->getPriority() > b->getPriority());
	}
};
