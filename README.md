# PMD
A "Pseudo Medical Device" and more

## Summary
An ESP32 microcontroller project with a printed cirucit designed by nagham.kheir25.  
This repository contains files which started as a KiCad home work project but which has evolved to become so usefull that in the summer of 2024 orders were placed for real hardware from JLCPCB for delivery in USA and from PCBWay for delivery in Lebanon.  
Begun as Homework 2, by late 2024 we began refering to it as a "Pseudo Medical Device" akd **PMD**.  
At times the PMD approximates the Krake hardware of the Public Invention project Krake. See: https://github.com/PubInv/krake  

## Status 
As of 20240911 See the README.md with in the Firmware folder for descriptions of files there.
As of 202709  
Journal of assembly of PCBWay order in this issue:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/33  
Journal of assembly of JLCPCB order in this issue:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/32  

To finish the assemblies LEDs were soldered to the PCB 
Image of assembly with LEDs on the Public Inventino GPAD stand off spacers.    
![image](https://github.com/user-attachments/assets/ff2cf124-d601-4fc4-b69f-2300d63e25a9)

Another view of the LEDs.  
![image](https://github.com/user-attachments/assets/7caf22b7-1025-4c08-a0a9-01e63282fd1c)

PMD mounted to the workbench
<img src="https://github.com/user-attachments/assets/21fc2465-29c3-45e0-9f70-c0dd6d872534" width="900px" height="450px">

View of the PMD on the workbench. Workbench designed by Oyindamola Adeniran 

<img src="https://github.com/user-attachments/assets/f4dcb31e-5f27-4f46-9496-25603c884c55" width="600px" height="400px">

Several firmware "sketches" have been developed to assist in the verification of the assemblies including a marching 1 and marching 0 test.

During brain storming we have discussed how this assembly might be used as a "PMD" Pesudo Medical Device. A device to control a Krake and the Mocking Krake. (See Krake: https://github.com/PubInv/krake)

## The KiCad File "HOMEWORK 2" 

The "HOMEWORK 2" PCB is designed around the ESP32 Devkit V1. Documentation for the devkit V1 can be found here.
https://embedded-systems-design.github.io/overview-of-the-esp32-devkit-doit-v1/

Valuable symbols and circuits have been acquired and deposited in this repository for the public use:
* ESP32 symbol and footprint libraries.
* A voltage regulation circuit.
* Switches are linked to the input pins of the ESP32 with pull-up resistors.


## PMD Design Summary

* 4 switches connected to the input pins of the esp32
* 6 leds are connected to the output pins of the Esp32
* the voltage regulator supply the esp32 with a 5 V

## Design Details 
 
* ### Esp32-6leds-2switches-1pj-circuit > Kicanvas live view of current schematic and PCB is found at:  

>> [schematic Link](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fnk25719%2FKiCad-esp32-6leds-2switches-1pj-circuit%2Fblob%2Fmain%2FhomeWork2.kicad_sch) & [PCB Link](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fnk25719%2FKiCad-esp32-6leds-2switches-1pj-circuit%2Fblob%2Fmain%2FhomeWork2.kicad_pcb)

* ### Esp32-6leds-2switches-1pj-circuit > KiCad PCB Layers View:

<img width="535" alt="image" src="https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/assets/133608369/654ed731-11bc-4bf3-9324-bcb3c00c4725">

> 3D view of the PCB
  
<img width="555" alt="Screenshot 2024-07-07 074220" src="https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/assets/133608369/896a5381-ad8e-4afd-be37-51b45ef2eafa">

> All Layers View

## PMD ESP32 Pin Mapping 

| GPIO number 	| Function               	| ESP32_DEVKITV1 pin number 	|
|-------------	|------------------------	|---------------------------	|
| 2           	| LED_BUILTIN            	| 27                        	|
| 34          	| S3                     	| 12                        	|
| 35          	| S4                     	| 11                        	|
| 39          	| S2 / ON_OFF_BUTTON_PIN 	| 13                        	|
| 36          	| S1 / MUTE_BUTTON_PIN   	| 14                        	|
| 23          	| LED_PIN_M              	| 1                         	|
| 15          	| D5                     	| 28                        	|
| 4           	| D3                     	| 26                        	|
| 5           	| D8                     	| 23                        	|
| 18          	| D7                     	| 22                        	|
| 19          	| D6                     	| 21                        	|
| 21          	| SDA                    	| 19                        	|
| 22          	| SCL                    	| 17                        	|
| 17          	| TX2                    	| 24                        	|
| 16          	| RX2                    	| 25                        	|
|             	|                        	|                           	|



## Facts

* I understand the function of a decoupling resistor.
* I comprehend the rationale behind including a voltage regulator circuit.
* ESP32 input pins require a pull-up resistor.
* It's necessary to include a power flag next to your GND and Vin connections in the KiCad schematic.
* The ESP32 antenna should be positioned at the edge of the PCB.
* The anular ring between the inner and outer diameters of the through holes in the ESP32 footprint is 0.7 mm.
* the pins of the Esp32 are numberred counter clockwise

## Do Not Tell

* I've made errors.
* Engineers and spelling are not bestfriends.
* I was about to distroy the universe but my ESP32 was not strong enough.

## Did You Know? 

In propositional logic and Boolean algebra, De Morgan's laws, AKA De Morgan's theorem,  
are a pair of transformation rules that are both valid rules of inference.  
The rules allow the expression of conjunctions and disjunctions purely in terms of each other via negation.
Named after Augustus De Morgan, a 19th-century British mathematician.

## Credits
I would like to express my gratitude to the developers and maintainers of several platforms. Firstly, GitHub, for its project management features, issues tracking, and project board, which have consistently proven useful during our usage. Additionally, I extend my thanks to KiCAD for providing the tools necessary for schematic capture and PCB design. I also appreciate the inventors and developers of the Arduino ecosystem, whose tools and hardware have had a profoundly positive impact on many individuals.

Furthermore, I am grateful for the Public Invention platform, which has facilitated communication and collaboration. Special recognition goes to my exceptional mentors and colleague Oyindamola Adeniran, Mr. Forrest Lee Ereckson and Mr. Robert Reed. Their guidance has been invaluable in navigating these projects, fostering skill development, and providing ongoing support. Their mentorship has empowered me to apply my knowledge to projects that benefit public invention.

## License

* Firmware: Affero GPL 3.0
* CERN Open Hardware Licence Version 2 - Strongly Reciprocal
  
