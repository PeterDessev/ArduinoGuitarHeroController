# ArduinoGameController
## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Build](#Build)

## General info
This project is a simple driver for converting arduino serial output into keyboard input readable by any game or other peice of software
	
## Technologies
Project is created with:
* A modified version of Serial Port by Manash Kumar Mandal - https://github.com/manashmandal/SerialPort
* Windows 10 SDK - https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/

## Build
To build this project, use the C++ compiler of your choosing, here clang++

```
$ cd ../ArduinoGuitarHeroController
$ clang++ main.cpp serialPort/SeriaPort.cpp -o controller.exe
```
