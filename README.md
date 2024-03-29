# USB_SERIAL_JTAG_ESP32-C6
The "ESP32-C6 USB Serial/JTAG Controller Library" provides a software interface to fully utilize the integrated USB Serial/JTAG controller in the ESP32-C6 SoC. 

This controller allows for programming the SoC's flash memory, reading program output, and attaching a debugger to the running program, all using a computer with a USB port without the need for active external components.

## Overview:

The ESP32-C6 project contains a USB Serial/JTAG controller that significantly simplifies programming and debugging of projects. By utilizing this integrated functionality, developers can circumvent the drawbacks associated with using UART and JTAG separately, such as pin IO occupation and the need for external components to interface with a host computer.


## Features:

USB Full-Speed Device: The controller operates as a USB Full-Speed device and is hardwired for CDC-ACM (Communication Device Class - Abstract Control Model) and JTAG adapter functionality.

CDC-ACM Support: Integrates CDC-ACM compliant serial port emulation, facilitating plug-and-play compatibility with most modern operating systems. It also supports host-controllable chip reset and entry into download mode.

JTAG Adapter Functionality: Enables fast communication with the CPU debugging core using a compact representation of JTAG instructions.

Multiple Endpoints: Includes two OUT endpoints and three IN endpoints in addition to Control Endpoint 0, supporting up to a 64-byte data payload size.

Internal PHY: Requires very few or no external components to connect to a host computer, simplifying hardware design and reducing component costs.
