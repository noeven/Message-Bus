//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#pragma once
#include <vector>
#include <string>
#include "TextMessage.h"
#include "MeasurementMessage.h"
//#include "MessageBus.h"

class MessageBus;

class Node {
private:
	std::string name;
	std::string nodeaddress;
	int nodeport;
	std::string applicationaddress;
	int applicationport;
    double measurement;
    int movement;
	MessageBus* bus;
    unsigned char enc_msg;
    
public:
	Node(const std::string name, const std::string nodeaddress, const int nodeport, const std::string applicationaddress, const int applicationport, MessageBus* bus) :
		name(name), bus(bus), nodeaddress(nodeaddress), nodeport(nodeport), applicationaddress(applicationaddress), applicationport(applicationport) {}
	std::string getName() const;
	void sendMessage(Message*);
	void acceptMessage(Message*);
	friend bool operator<(const Node&, const Node&);
    
    //Accept measurement message and send MeasurementMessage to Servo
    void ProcessMeasurement(Message*);
    //Accept logic signal and send Imagemessage to Logic
    void CameraSnapshot();
    //Accept logic signal and sned MeasurementMessage to  Logic
    void TemperatureMeasurement();
    //Accept logic signal and change servo position
    void ServoMovement(Message*);


};

