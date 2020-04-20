//==============================================================
// Filename :   Challegne 5A - Implementation of nodes
// Authors :    Max Kivits (s1590294) & Sheng Chih Wu (s2305356)
// Version :    1.0
// License :    NA
// Description :    Final Assignment of Programming 2 (5 EC version)
//==============================================================
/*	Node.cpp
	Node class function declarations
*/

//Dependencies
#include <iostream>
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <vector>
#include <thread>

#include "base64.h"
#include "Node.h"
#include "Message.h"
#include "ImageMessage.h"
#include "MeasurementMessage.h"
#include "MessageBus.h"

//Class Function that returns name of the node
std::string Node::getName() const {
	return name;
}
//Class function to push message to message bus
void Node::sendMessage(Message* message)  {
	bus->acceptMessage(message);
}
//Class Function to print message
void Node::acceptMessage(Message* message) {
    std::string s = getName();

    //If the message is sent to temperature sensor, run TemperatureMeasurement.
    if (s == "Temperature"){
        std::thread t4([this]() {this->TemperatureMeasurement(); });
        t4.detach(); //detach to allow next thread run simultaneously
    }
    //If the message is sent to Camera module, run CameraSnapshot.
    else if (s == "Camera"){
        std::thread t3([this]() {this->CameraSnapshot(); });
        t3.detach(); //detach to allow next thread run simultaneously
    }
    //If the message is sent to Logic module, run ProcessMeasurement.
    else if (s == "Logic"){
        ProcessMeasurement(message);
    }
    //If the message is sent to Servo module, run ServoMovement.
    else if (s == "Servo"){
        ServoMovement(message);
        }
}

//Accept logic signal and generate image signal
void Node::CameraSnapshot(){
    std::cout << "Camera start taking snapchot. " << std::endl;
    //Video capture section
    cv::VideoCapture cap;
    cap.open(0);
    //Show error message if camera can not open
    if(!cap.isOpened())
    {
        std::cerr << "Couldn't open capture." << std::endl;
    }
    //If camera runs properly, proceed the snapshot procedure
    else if (cap.isOpened()){
        std::vector<uchar> img_data;
        cv::Mat image;
        cap.read(image);
        //encode the image -> jpg -> base64
        cv::imencode(".jpg",image,img_data);
        auto *enc_msg = reinterpret_cast<unsigned char*>(img_data.data());
        int k = img_data.size();
        std::string encoded = base64_encode(enc_msg, k);
        std::cout << "Image data encoded. " << std::endl;
        //Generating image message
        int i = 1;
        ImageMessage* message3 = new ImageMessage(i, "Camera", "logic", encoded);
        bus->acceptMessage(message3);
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        delete message3;    //deallocate the memory.
    }
    //close video capture
    cap.release();
    std::cout << "Camera module sends Imagemessage to Logic. " << std::endl;
}

//Accept logic signal and generate temeperature signal
void Node::TemperatureMeasurement(){
    std::cout << "Sensor start measuring temperature. " << std::endl;
    int i = 1;
    //Randomly generating temeperature data
    measurement= (double)rand()/RAND_MAX*10.0+30.0;
    //Send measurement data to logic
    MeasurementMessage* message2 = new MeasurementMessage(i, "Temperature", "logic", measurement);
    bus->acceptMessage(message2);
    std::cout << "Temperature module deliever the message!" << measurement << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    delete message2;    //deallocate the memory.
}

//Accept measurement (camera and temperature) message and generate logic signal
void Node::ProcessMeasurement(Message* message){
    //If the measurement message comes from Temperature sensor
    if (message->getFrom() == "Temperature"){
        std::cout << "Logic Start processing temperature. " << std::endl;
        //to extract the measurement data from string
        std::string str = message->toString();
        std::stringstream s1(str);
        int x; double y;
        s1.ignore(7,' ');
        s1 >> x; //store priority
        s1.ignore(256,'M');
        s1.ignore(1,' ');
        s1 >> y; // store double measurement
        measurement = y; //store measurement data
        //Save to text file
        std::ofstream outdata;
        outdata.open("/Users/evenwu/Documents/UT/2A/Programming 2/Project/messagebus/Challenge4_FINAL/text.txt",std::ios::app); //Change this to store file in desired address
        outdata << measurement << std::endl;
        outdata.close();
        std::cout << "Measured Temperature: "<< measurement << ". The data has been saved in the text file." << std::endl;
        
        int i = 1;
        //If temp > 37, generate logic signal to move positive
        if (measurement >= 37){
            MeasurementMessage* message2 = new MeasurementMessage(i, "Logic", "servo",1.0);
            bus->acceptMessage(message2);
            std::cout<< "Logic module delievers the postive command to servo. " << std::endl;
            }
        //If temp < 33, generate logic signal to move negative
        else if (measurement <= 33){
            MeasurementMessage* message2 = new MeasurementMessage(i, "Logic", "servo", -1.0);
            bus->acceptMessage(message2);
            std::cout<< "Logic module delievers the negative command to servo!  " << std::endl;
            }
        //If temp are btw 33~37, no need to change servo position
        else
            std::cout<<"Logic module decides not to deliever command due to stable measurement." << std::endl;
        }
    
    //If the measurement message comes from Camera module
    else if (message->getFrom() == "Camera"){
        std::cout << "Logic Start processing image. " << std::endl;
        //to extract the base64 from string
        std::string str = message->toString();
        std::stringstream s1(str);
        int x;
        std::string encoded;
        s1.ignore(7,' ');
        s1 >> x; //store priority
        s1.ignore(256,'I');
        s1.ignore(1,' ');
        s1 >> encoded; // store base64 data
        //decode base64->jpg->img
        std::string dec_jpg = base64_decode(encoded);
        std::vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
        cv::Mat img = cv::imdecode(cv::Mat(data), 1);
        //save image to file
        imwrite("/Users/evenwu/Documents/Frame.jpg",img); //Change this to store file in desired address
        std::cout << "Logic module saves the image to the local file. " << std::endl;
    }
}

//Accept logic signal and generate servo signal
void Node::ServoMovement(Message* message){
    std::cout << "Servo start changing servo position" << std::endl;
    //Extract movement information from string
    std::string str = message->toString();
    std::stringstream s1(str);
    std::string a;
    int x; double y;
    s1.ignore(7,' ');
    s1 >> x; //store priority
    s1.ignore(256,'M');
    s1.ignore(1,' ');
    s1 >> y;
    
    //Determine the movement based on logic command
    if (y == 1.0)
        std::cout << "Servo module has moved positively.  " << std::endl;
    else if (y == -1.0)
        std::cout << "Servo module has moved negatively. " << std::endl;
    else
        std::cout << "No change on servo position." <<std::endl;
    delete message; //deallocate the message (message from Logic module to command servo movement)
}

// Similar to string::compare()
bool operator<(const Node& lhs, const Node& rhs) {
	return lhs.name < rhs.name;
}

