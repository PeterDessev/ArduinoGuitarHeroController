#include "serialPort/SerialPort.hpp"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>

//controls for windows keyboard
namespace keycontrol{
    std::vector<int> keyPressed (10);


    void keyDown(int keyCode, int keyItter){
        if(!keyPressed[keyItter]){
            keyPressed[keyItter] = 1;
            INPUT input;

            input.type = INPUT_KEYBOARD;
            input.ki.time = 0;
            input.ki.wVk = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.dwFlags = KEYEVENTF_SCANCODE;
            input.ki.wScan = keyCode;

            SendInput(1, &input, sizeof(INPUT));
        }
    }

    void keyUp(int keyCode, int keyItter){
        if(keyPressed[keyItter]){
            keyPressed[keyItter] = 0;
            INPUT input;

            input.type = INPUT_KEYBOARD;
            input.ki.time = 0;
            input.ki.wVk = 0;
            input.ki.dwExtraInfo = 0;
            input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
            input.ki.wScan = keyCode;

            SendInput(1, &input, sizeof(INPUT));
        }
    }
    
    void mouseMove(int x, int y){
        
    }
};

//process the data and determin whether to press or release the key
void process(int* data, int controls[10]){
    for(int i = 0; i < 10; i++){
        if(*(data + i)){ //Star Power
            keycontrol::keyDown(controls[i], i);
        }else{
            keycontrol::keyUp(controls[i], i);
        }
    }
    // TODO: Add mouse functionality
    /*if(data[10]){ //Whammy Bar
         //mouseMove(0, data[10]); 
    }*/
}

//parse packet into data points
int* parse(std::string data){
    int* parsedData = (int*)malloc(11 * sizeof(int));
    std::string token;
    
    //-----
    std::string delimiter = ":";
    //-----
    
    
    size_t pos = 0;
    data.pop_back();
    for(int i = 0; i == i; i++){
        pos = data.find(delimiter);
        token = data.substr(0, pos);
        std::istringstream convert(token);
        
        if(pos == std::string::npos){
            convert >> parsedData[i];
            break;
        }
        convert >> parsedData[i];
        data.erase(0, pos + delimiter.length());
    }
    return &parsedData[0];
}

void connect(int& portID, SerialPort *currentPort, int baudRate){
    std::string portName = "\\\\.\\COM";
    currentPort = new SerialPort((portName + (char)(portID + '0')).c_str(), baudRate);

    if (!currentPort->isConnected()){
        delete currentPort;
        std::cout << "Connection unable to established at port COM" << portID << ", try again:" << std::endl;
        std::cin >> portID;
        connect(portID, currentPort, baudRate);
    }else{
        std::cout << "Connected to port COM" << portID << ", keyboard starting..." << std::endl;
    }
}


int main(void){
    SerialPort *currentPort;
    std::string currentData;
    
    char DataBuffer[1];
    int* parsedData;
    int keyboardButtons[10] = {
        0x1F, //s
        0x16, //u
        0x20, //d
        0x1C, //enter
        0x39, //space
        0x02, //1
        0x03, //2
        0x04, //3
        0x05, //4
        0x06  //5
    };
    int portID;
    
    //The baudrate of the connection to the arduino, remember to change this as well as the baudrate in the arduino program
    int baudRate = 115200;
    
    std::string portName = "\\\\.\\COM";
    
    
    //Detect all ports that are open
    for(int i = 0; i < 10; i++){
        currentPort = new SerialPort((portName + (char)(i + '0')).c_str(), baudRate);
        if (currentPort->isConnected()){
            std::cout << "Device detected at port COM" << i << std::endl;
        }
        delete currentPort;
    }
    
    //allow user to choose the port they want to use, if multiple arduinos are connected

    std::cout << "Which port do you want to use?" << std::endl;
    std::cin >> portID;
    connect(portID, currentPort, baudRate);
    
    
    //Device connected, begin processing input and performing tasks
    std::cout << "ready" << std::endl;
    while(currentPort->isConnected()){
        //read data from serial bit by bit
        int readResult = currentPort->readSerialPort(DataBuffer, 1);
        if(isprint(DataBuffer[0]) || DataBuffer[0] == '\n'){
            currentData += DataBuffer[0];
        }
        
        //process data once whole packet has been collected
        if(DataBuffer[0] == '\n'){
            parsedData = parse(currentData);
            process(parsedData, keyboardButtons);
            free(parsedData);
            currentData.clear();
        }
    }
}
