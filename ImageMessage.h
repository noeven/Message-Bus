//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include "Message.h"
#include "base64.h"
#include <vector>

class ImageMessage : public Message {
private:
	std::string base64encoded;
public:
	ImageMessage(int priority, const std::string& from, const std::string& topic, unsigned char* data, int length) : Message(priority, from, topic) {
		base64encoded = base64_encode(data, length);
	};
	ImageMessage(int priority, const std::string& from, const std::string& topic, std::string base64encoded) : Message(priority, from, topic), base64encoded(base64encoded) {}
	std::string getImage();
	virtual std::string toString();
};

