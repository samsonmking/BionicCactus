# BionicCactus
Robotic lighting and watering for house plants that's configurable through a simple web interface. Written in C++ for ESP8266 microcontroller using the Arduino framework and PlatformIO. Features include:
* Set desired soil moisture levels and watering frequency
* Set lighting schedule and control brightness
* Monitor water resevoir levels and recieve email notifications when it's time to refill
* Simple setup and monitoring through web interface
* Persist settings to flash memory

![Image of system](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/system.jpg)

## Software
### Overview
![Software Index Page](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/bc_index.png)
### Watering System Configuration
![Watering System Configuration](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/bc_watering.png)
### Installation
1. Install [PlatformIO](https://docs.platformio.org/en/latest/installation.html)
2. Build and Upload
```bash
platformio run --target upload
```
To run in simulation mode with only the ESP8266 (no PCB connected) change Settings.hpp
```c++
#define SIMULATED false
```
to
```c++
#define SIMULATED true
```
3. See [wiki](https://github.com/samsonmking/BionicCactus/wiki) for setup and configuration


## Hardware
### PCB and Schematics
Clone the [KiCAD PCB Repository](https://github.com/samsonmking/BionicCactusPCB) for PCB and circuit schematics.

### 3D Printed Components
* [Robotic Gardening Planter Pot](https://www.thingiverse.com/thing:3351677)
* [Light with Drip Tray](https://www.thingiverse.com/thing:3351565)
* [Enclosure and Pump Bracket](https://www.thingiverse.com/thing:3351861)

![Pot Design](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/pot_back.jpg)
![Water Flowing](https://github.com/samsonmking/BionicCactus/raw/master/images/water.gif)
