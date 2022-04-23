
# Oxemetry and pulsometry
## Description
This system allows you to distribute people between warehouse equipment and give permission to control certain types of machines. It also allows you to take into account the working hours of employees and conduct convenient analytics according to these hours.
## System Composition
- Wrist bracelet
	>The printed circuit board and circuit diagram of the device are created in [KiCad](https://www.kicad.org) 
	Firmware created in Keil uVision for ARM in C languages
- Server that receives data from devices and adds this data to the database
	>The server part was created in Visual Studio C ++, as a console application
	MySQL was used as the database. And MySQL Workbench for administration

## Main view PCB
![PCB top](https://github.com/dimaib/Pulse_bracelet/blob/main/braslet/schematic&pcb/body_temp_v4.2/pcb_top.png?raw=true)
![PCB bottom](https://github.com/dimaib/Pulse_bracelet/blob/main/braslet/schematic&pcb/body_temp_v4.2/pcb_bottom.png?raw=true)
