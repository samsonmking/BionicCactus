# BionicCactus
Autonomous lighting and watering for house plants that's configurable through a simple web interface. Written in C++ for ESP8266 microcontroller using the Arduino framework and PlatformIO. Features include:
* Set desired soil moisture levels and watering frequency
* Set lighting schedule and drive up to 4A / 12V DC lights
  * Configurable brightness with PWM control
* Monitor water resevoir levels and recieve email notifications when it's time to refill
* Simple setup and monitoring through web interface

Most parts are 3D printed or simple off the shelf components. Clone the [KiCAD PCB Repository](https://github.com/samsonmking/BionicCactusPCB) to make the PCB.

![Image of system](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/system.jpg)

## Software
### Overview
![Software Index Page](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/bc_index.png)
### Watering System Configuration
![Watering System Configuration](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/bc_watering.png)

## Hardware
### 3D Printed pot with integrated water dispersion and soil moisture sensor housing
![Pot Design](https://github.com/samsonmking/BionicCactusESP8266/raw/master/images/pot_back.jpg)

*I'm in the the process of writing up full setup documentation and uploading the STLs to print the pot, light, tray, and PCB enclosure.*
