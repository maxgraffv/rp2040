# rp2040
Description and examples for RP2040 elements, subsystems etc.

##Table Of Content
- [System Description]




###System description
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
