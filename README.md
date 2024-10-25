# SRAM Physical Unclonable Function (PUF) Analysis for the IDT71V416 Chip
## Overview
This repository contains code for extracting and analyzing the SRAM Physical Unclonable Function (PUF) data. The project includes three primary tasks, each designed to analyze SRAM's power-up behavior under different conditions, using Python for data analysis and Arduino code to interface with the SRAM chip.

## Tasks

### Task 1: Calculate the Percentage of '1' Bits
This task involves writing a Python script that:
1. Reads hex data from a file.
2. Converts hex values to binary.
3. Calculates the percentage of '1' bits in the data.

The output provides a metric to assess the randomness of SRAM data at power-up, aiding in PUF analysis.

### Task 2: Compare Consecutive Power-Up States
This task compares the bit differences between two consecutive power-up states of the SRAM. It:
1. Reads two power-up hex data files.
2. Converts the hex data to binary.
3. Calculates the bit difference and expresses it as a percentage.

The task assesses how environmental and physical changes (e.g., keeping the chip in or out of the socket) impact the SRAM's PUF stability.

### Task 3: Measure Bit Differences after Writing All Zeros and All Ones
This task investigates the SRAM's response after writing all zeros or all ones to the memory array and then powering it off and on. The Python script:
1. Reads hex data after writing all zeros and all ones.
2. Compares bit differences in power-up states after each write.

This comparison gives insights into the SRAM's retention characteristics and how initial memory states influence power-up patterns.

## Python Scripts

### `calculate_percentage_of_ones.py`
- **Functionality**: Calculates the percentage of '1' bits in hex data files.
- **Output**: Displays the percentage of '1' bits in the data.

### `compare_power_up_states.py`
- **Functionality**: Compares consecutive power-up states and calculates the bit differences.
- **Output**: Displays bit differences and their percentage, offering insights into PUF stability.

### `analyze_zero_one_write_states.py`
- **Functionality**: Compares power-up states after writing all zeros and all ones.
- **Output**: Displays bit differences between zero and one writes, showcasing the SRAM's sensitivity to initial conditions.

## Arduino Code

### `sram_read.ino`
This Arduino code interfaces with the SRAM chip to:
- Read data and output it in hexadecimal format.
- Initialize control, address, and data lines.
- Collect 4Mb of data from the SRAM chip for analysis.

### `sram_write_zero_one.ino`
This code writes all zeros or all ones to the SRAM chip:
- Initializes address and data lines.
- Writes specified data patterns to SRAM.
- Powers off SRAM between reads for analyzing PUF stability.

## Usage

1. **Arduino Setup**: Upload the appropriate Arduino code (`sram_read.ino` or `sram_write_zero_one.ino`) to your board to read or write data to the SRAM.
2. **Data Extraction**: Save the hex data output from the Arduino serial monitor into a text file.
3. **Data Analysis**: Run the respective Python script to analyze bit distribution, power-up state differences, or the impact of initial writes.


