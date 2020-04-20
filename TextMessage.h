//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once

#include <string>
#include "Message.h"

class TextMessage: public Message {
private:
	std::string text;
public:
	TextMessage(int priority, const std::string& from, const std::string& topic, const std::string& text) : Message(priority, from, topic), text(text) {};
	std::string getText();
	virtual std::string toString();
};

