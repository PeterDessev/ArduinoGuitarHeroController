Arduino Guitar Hero Controller
==============================
## Table of contents
* [General info](#general-info)
* [Features](#features)
* [Technologies](#technologies)
* [Build](#Build)
* [Download](#Download)
* [License](#license)

---

## General info
This project is a simple driver for converting arduino serial output into keyboard input readable by any game or other peice of software
	
---

## Features
- Detect multiple open COM ports and allow the user to choose which to use

### To-Do
- Add Disconect/Reconect features
- Add suport for whammy-bar via mouse movement
- Add GUI

---

## Technologies
Project is created with:
* A modified version of Serial Port by Manash Kumar Mandal - https://github.com/manashmandal/SerialPort
* The Windows 10 SDK - https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk/

---

## Build
To build this project, use the C++ compiler of your choice, here clang++

```
$ cd ../ArduinoGuitarHeroController
$ clang++ main.cpp serialPort/SeriaPort.cpp -o controller.exe
```

---

## Download
Pre-compiled binaries for version 0.1.0 are available [here](https://github.com/SnowCheetah/ArduinoGuitarHeroController/releases/tag/v0.1.0)

## License
>You can check out the full license [here](https://github.com/SnowCheetah/ArduinoGuitarHeroController/blob/master/LICENSE)

This project is licensed under the terms of the **MIT** license.
