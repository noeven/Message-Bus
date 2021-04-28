# Message-Bus
Constructing a Message Bus structure that enables the applications to work together using messages

# Description:
1. The simulator is to simulate a robot system with following modules: Logic module, Temperature sensor, Camera module, and Servo module.
Logic module processes the input and commands the actuator and sensors.
If temperature is higher than 37, the logic module will send a message to the servo module, making positive movement; if the temperature is lower than 33, the logic module will send a message to the servo module, making negative movement.
The temperature record will be stored locally as a log file for future service.
The snapshot, or the image taken by Camera module, will be stored as well for the purpose of recording.
2. Temperature sensor measures the temperature by logics' command and sends it back to  Logic module.
If temperature is higher than 37, the servo module needs to make a positive movement; if temperature is lower than 33, the servo module needs to make a negative movement.
3. Camera module takes the snapshot from the webcam by logics' command and sends it back to the logic module.
4. Servo module changes the position by logics' command.
If Servo module receives the message with signal:1 from the logic module, it moves positively, and vice versa.

# Workflow:
1. Logic module sends messages to the Camera module and Temperature sensor.
2. Message bus accepts and handles the messages.
3. Temperature sensor responds with a random double value within the range of 30 to 40, delivering a measurement message; the Camera module opens the webcam and takes a snapshot. The image will be encoded as jpg type and then transfer to base64 type. With the base64 data, the image message will be sent to the Logic module.
4. Message bus accepts and handles the messages.
5. Logic module receives the temperature message, and determines the movement based on the temperature. The temperature will be recorded as a log file for service purposes. The movement message will be sent to Servo module with the movement command.
6. Logic module receives the image message. It will decode the base64 type to jpg data type, and then save the image.
7. Message bus accepts and handles the messages.
8. Servo module receives the command from Logic module, and it will make movement based. If it receives a measurement message with 1.0, Servo module moves positively; if it receives a measurement message with -1.0, Servo module moves negatively.

# Note:
Note 1: If you are running the script on macOS, make sure you include the Info.plist as following instruction: https://stackoverflow.com/questions/55518922/missing-info-plist-file-for-c-command-line-tool-application-within-xcode

Note 2: Several file address you might need to change:
  Simulator.cpp: line 46 (address of text file) and line 50 (address of db.file).
  Node.cpp: line 128 (address of text file) and line 169 (address of image file)
