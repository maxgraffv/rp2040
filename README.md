# rp2040
![rp2040](readme_images/rp2040.png)  
<!-- <img src="readme_images/rp2040.png" style="width:30%"/> -->
Description and examples for RP2040 elements, subsystems etc.

## Table Of Content
- [System Description](#system-description)




### System description
<img src="readme_images/rp2040-system.png" alt="rp2040 system diagram" style="width:100%"/>  

- Arm Cortex M0+
- 133MHz
- SRAM 264kB - addressed as one, physically partitioned into 6 banks
- 30 GPIO
- 6 IO for SPI Flash
- ADC - 4-channel; internal temperature sensor; 12bit conversion;
- USB 1.1
- DMA (Direct Memory Access)
- SWD (Serial Wire Debug)
- APB - Advanced Peripheral Bus
- QSPI - SPI/Dual SPI/Quad SPI
- XIP - Execute In Place, Flash Memory
- PLL - Phase Locked Loop, fixed 48MHz for USB
- SIO - Single-cycle IO; Software Control of GPIO; SIO must be selected to drive GPIO
- PIO - Programmable IO block; PIO must be selected to drive GPIO

Priority levels are configured per master using BUS_PRIORITY register is BUSCTRL register block

Data Paths are 32-bit wide

Bus has 4 masters:
- core 0
- core 1
- DMA read
- DMA write

BUS PERFORAMNCE
- BUSCTRL_PERFCTRx register
- BUSCTRL_PERFSELx register

APB Bridge 
Access takes 2 cycles at minimum (setup phase, access phase)


### CORETEX M0+
Configuration for RP2040
- clock gating
- little endian
- 4 breakpoints
- 32bit instruction fetch
- IOPORT - for low latency access (SIO)
- 26 Interrupts
- 8 MPU (Memory Protecion Unit) regions
- All regsiters reset on powerup

Architecture
- ARM v6-M

M0+ Features
- ARM v6-M Thumb Instruction Set
- 24bit SysTick Timer
- deterministic, low-latency interrupt handling
- Load/Store multiple instructions (can be abandoned or restarted for an interrupt)
- C ABI - pure C functions as Interrupt handlers
- Low power sleep mode entry - using WFI, WFE or return from interrupt

NVIC - Nested Vector Interrupt Controller
- 26 external interrupts with 4 levels of priority
- Wake-Up Interrupt Controller (WIC)

WIC - Wake-Up Interrupt Controller
- used to wake the processor from a DEEPSLEEP controlled by SCR register
- In DEEPSLEEP state clocks to the processor core and NVIC are not running
- It can take a few cycles to wake-up
- takes inputs from other processor, 32 interrupt lines and NMI

DAP - Debug Access Port
    Provides Serial Wire debug port and connects to processor's slave port

Reset control - controls: debug reset, M0+ core reset, PMU reset