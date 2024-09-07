## Summary

This repository contains files which started as a KiCad home work project but which has evolved to become so usefull that in the summer of 2024 orders were placed for real hardware from JLCPCB for delivery in USA and from PCBWay for delivery in Lebanon.

## Status 
As of 202709  
Journal of assembly of PCBWay order in this issue:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/33  
Journal of assembly of JLCPCB order in this issue:  https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/issues/32  

To finish the assemblies LEDs were soldered to the PCB 
Image of assembly with LEDs on the Public Inventino GPAD stand off spacers.    
![image](https://github.com/user-attachments/assets/ff2cf124-d601-4fc4-b69f-2300d63e25a9)
Another view of the LEDs.  
![image](https://github.com/user-attachments/assets/7caf22b7-1025-4c08-a0a9-01e63282fd1c)

Several firmware "sketches" have been developed to assist in the verification of the assemblies including a marching 1 and marching 0 test.

During brain storming we have discussed how this assembly might be used as a "PMD" Pesudo Medical Device. A device to control a Krake and the Mocking Krake. (See Krake: https://github.com/PubInv/krake)

## The KiCad File "HOMEWORK 2"

Valuable symbols and circuits have been acquired and deposited in this repository for the public use:
* ESP32 symbol and footprint libraries.
* A voltage regulation circuit.
* Switches are linked to the input pins of the ESP32 with pull-up resistors.


## Design Summary

* 4 switches connected to the input pins of the esp32
* 6 leds are connected to the output pins of the Esp32
* the voltage regulator supply the esp32 with a 5 V

## Designs Details
 
* ### Esp32-6leds-2switches-1pj-circuit > Kicanvas live view of current schematic and PCB is found at:  

>> [schematic Link](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fnk25719%2FKiCad-esp32-6leds-2switches-1pj-circuit%2Fblob%2Fmain%2FhomeWork2.kicad_sch) & [PCB Link](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fnk25719%2FKiCad-esp32-6leds-2switches-1pj-circuit%2Fblob%2Fmain%2FhomeWork2.kicad_pcb)

* ### Esp32-6leds-2switches-1pj-circuit > KiCad PCB Layers View:

<img width="535" alt="image" src="https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/assets/133608369/654ed731-11bc-4bf3-9324-bcb3c00c4725">

> 3D view of the PCB
  
<img width="555" alt="Screenshot 2024-07-07 074220" src="https://github.com/nk25719/KiCad-esp32-6leds-2switches-1pj-circuit/assets/133608369/896a5381-ad8e-4afd-be37-51b45ef2eafa">

> All Layers View


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

Furthermore, I am grateful for the Public Invention platform, which has facilitated communication and collaboration. Special recognition goes to my exceptional mentors, Mr. Forrest Lee Ereckson and Mr. Robert Reed. Their guidance has been invaluable in navigating these projects, fostering skill development, and providing ongoing support. Their mentorship has empowered me to apply my knowledge to projects that benefit public invention.

## License

* Firmware: Affero GPL 3.0
* CERN Open Hardware Licence Version 2 - Strongly Reciprocal
  
