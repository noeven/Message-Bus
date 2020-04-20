//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
#include "Nodes.h"
#include <iostream>
#include <mutex>
#include <chrono>

#include "Node.h"
#include "Message.h"
#include "ImageMessage.h"
#include "MeasurementMessage.h"
#include "MessageBus.h"




void Nodes::run() {

    while (true) {
        //Generate first logic signal to get measurement data
        MeasurementMessage* message1 = new MeasurementMessage(1, "Logic", "measurement",1);
        //Passing the logic signal to bus
        bus->acceptMessage(message1);

        std::cout << "~~~~~~~~~~ Messages generated ~~~~~~~~~~~~" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000)); //the process time of measurement takes 1050~1300ms
        delete message1;
    }
}

void Nodes::start() {
    //create three threads
    std::thread t1([this]() {this->run(); });
    t1.detach(); //detach to allow next thread run simultaneously
}
