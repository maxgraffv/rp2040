# rp2040
![rp2040](readme_images/rp2040.png)  
<!-- <img src="readme_images/rp2040.png" style="width:30%"/> -->
Description and examples for RP2040 elements, subsystems etc.

## Table Of Content
- [System Description](#system-description)
- [Data Bus](#data-bus)
- [Cortex M0+](#cortex-m0)




## System description
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

## Data Bus
Data Paths are 32-bit wide  
Priority levels are configured per master using BUS_PRIORITY register is BUSCTRL register block  

Bus has 4 masters:
- core 0
- core 1
- DMA read
- DMA write

BUS PERFORAMNCE
- BUSCTRL_PERFCTRx register
- BUSCTRL_PERFSELx register

### APB Bridge 
Access takes 2 cycles at minimum (setup phase, access phase)


## CORTEX M0+
**Configuration for RP2040**
- clock gating
- little endian
- 4 breakpoints
- 32bit instruction fetch
- IOPORT - for low latency access (SIO)
- 26 Interrupts
- 8 MPU (Memory Protecion Unit) regions
- All regsiters reset on powerup

**Architecture**
- ARM v6-M

**M0+ Features**
- ARM v6-M Thumb Instruction Set
- 24bit SysTick Timer
- deterministic, low-latency interrupt handling
- Load/Store multiple instructions (can be abandoned or restarted for an interrupt)
- C ABI - pure C functions as Interrupt handlers
- Low power sleep mode entry - using WFI, WFE or return from interrupt

## DMA
**Direct Memory Access**
- has seperate read and write master connections
- performs bulk data transfers on processors behalf
- let's processor attend other tasks or enter sleep
- data throughput is higher(a lot higher) than of the processor
- usual scenarios:
- - Memory to Peripheral
- - Peripheral to Memory
- - Memory to Memory
- transfer size can be 32, 16 or 8 bit
- channel configuration
- - each channel has 4 registers
- - READ_ADDR - pointer to next address to be read from
- - WRITE_ADDR - pointer to next address to be written to
- - TRANS_COUNT - number of transfers remaining in a sequence
- - CTRL - configure channel behaviour

FIFO - Fist In First Out buffer, temporarily store data in a sequential manner




## Processor subsystem
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

PMU - Power Management Unit

WFI - Wait For Interrupt, provides a mechanism for hardware support of entry to sleep state

WFE - Wait For Event, provides a mechanism for software to suspend program execution until a wake-up condition occurs

MPU - Memory Protection Unit
- 8 user-configurable memory regions
- 8 sub-regions disables, per region
- Execute Nver Support (XN)
- Default Memory Map Support


### Memory
RP2040 has embedded ROM and SRAM and access to external Flash via QSPI

ROM
- 16kB at address 0x00
- Contains
- - initial startup routine
- - flash boot sequence
- - flash programming routine
- - USB mass store device with UF2
- - Utility libraries such as fast floating point
RP2040 bootrom is available at pico-bootrom

SRAM
- 264kB physically partitioned into 6 Banks
- Four 16k * 32bit banks (64kB)
- Two 1k * 32bit banks (4kB)
- Mapped to address starting at 0x20000000

First 256kB region is word stripped across 4 larger banks

| System Address | Bank | SRAM word address |
|----------------|------|-------------------|
| 0x20000000     |   0  |         0         |
| 0x20000004     |   1  |         0         |
| 0x20000008     |   2  |         0         |
| 0x2000000c     |   3  |         0         |
| 0x20000010     |   0  |         1         |
| 0x20000014     |   1  |         1         |
| 0x20000018     |   2  |         1         |
| 0x2000001c     |   3  |         1         |
|      ...       |  ... |        ...        |


4kB Banks start at 0x20040000 and 0x20041000

Software may choose to use each of those banks per core

Other on-chip memory
- if XIP caching disabled,
    the cache becomes available as 16kB memory at 0x15000000
- if USB not used,
    USB DATA DPRAM can be used 4kB memory at 0x50100000

FLASH (external)
- accessed via the QSPI interface
    using the XIP (execute-in-place) hardware
    This allowes external flash memory to be addressed by the system as if it were an internal memory
- Memory window starts at 0x10000000

XIP Cache
- 16kB
- if disabled by clearing CTRL.EN, region behaves as additional 16kB SRAM bank

#### Bootrom
- size limited to 16kB
- contains
- - Core 0 initial boot sequence
- - Core 1 low power wait and launch protocol
- - USB MSC bootloader with UF2 support
- - USB Picoboot bootloader interface
- - Routines for programming and manipulating example. flash
- - Fast floating point library
- - Fast bit counting/manipulation functions
- - Fast memory fill/copy functions

RPI-RPI2 Drive
- appears as standard 128MB flash-drive
- formatted as single partitioned FAT16

Device ID
- idVendor 0x2e8a
- idProduct 0x0003

### PLL - phase locked loop
- generates pll_sys 133MHz system clock
- generates pll_usb 48MHz USB reference clock
- configurable based on used crystal

Crystal 
RP2040 supports 1MHz to 15MHz crystal

Internal Ring Oscillator is configurable but cannot provide accuracy because it varies based on temperature, voltage etc.

External Oscillator
- higher power consumption
- slow startup time (> 1ms)
- fixed, low frequency

### Sys Info
Registers start at 0x40000000 (SYSINFO_BASE in SDK)

| Offset |      Name     |      Info     |
|--------|---------------|---------------|
|  0x00  |    CHIP_ID    |    Chip ID    |
|  0x04  |    PLATFORM   | Allows software to know what environment it is running in    |
|  0x40  | GITREF_RP2040 | Git hash of chip source identifies chip version |
