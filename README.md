# Data Center Capacity Calculator

A high-performance C++ application for computing big data center capacity based on machine groups and configurations.

## Overview

This tool calculates the total Requests Per Second (RPS) capacity of a data center based on the distribution of machines across multiple groups. It uses an efficient algorithm to process machine configurations and compute optimal capacity metrics.

### Key Features

- **Flexible Input**: Interactive mode or file-based input
- **Scalable Design**: Supports up to 1000 groups with 1000 machines each
- **Modern C++**: Written in C++17 with best practices
- **macOS Optimized**: Specifically configured for macOS compilation
- **Command Line Interface**: Multiple options for different use cases
- **Error Handling**: Comprehensive input validation and error messages

## Requirements

- macOS 10.14+ (Mojave or later)
- Xcode Command Line Tools or full Xcode installation
- clang++ compiler (included with Xcode)
- GNU Make (included with macOS)

## Installation

### 1. Install Xcode Command Line Tools (if not already installed)

```bash
xcode-select --install
```

### 2. Clone or Download the Project

```bash
git clone <repository-url>
cd datacenter-capacity
```

### 3. Build the Project

```bash
make
```

For a debug build with sanitizers:
```bash
make debug
```

### 4. (Optional) Install System-wide

```bash
make install
```

This will copy the executable to `/usr/local/bin/` (requires sudo).

## Usage

### Interactive Mode (Default)

```bash
./datacenter
```

Example interaction:
```
=== Data Center Capacity Calculator ===
Enter M-groups and N-machines (e.g., '3 4'): 3 4

Enter 4 machine IDs for each of the 3 groups:
Group 1: A1 B1 C1 D1
Group 2: A2 B2 C2 D2
Group 3: A3 B3 C3 D3

=====================================
Data Center Configuration
=====================================
Requests Per Second = 300.00 RPS
M-groups            = 3
N-machines          = 4
Max Group RPS       = 100
=====================================
```

### File Input Mode

```bash
./datacenter -f input.txt
```

Input file format:
```
3 4
A1 B1 C1 D1
A2 B2 C2 D2
A3 B3 C3 D3
```

### Detailed Output

```bash
./datacenter -d
```

Shows additional information about machine version distribution.

### Command Line Options

- `-h, --help` : Display help message
- `-f, --file FILE` : Read input from file
- `-d, --detailed` : Show detailed results
- `-i, --interactive` : Interactive mode (default)

## Algorithm Description

The calculator uses the following approach:

1. **Input Processing**: Reads M groups with N machines each, creating an M×N matrix
2. **Matrix Rotation**: Processes the matrix to create machine-position mappings
3. **Hash Table Operations**: Uses two maps for efficient lookups:
   - `hashtable`: Stores position-machine combinations
   - `matchtable`: Stores minimum values for each machine type
4. **RPS Calculation**: Computes total capacity based on:
   - MAX_GROUP_RPS (100) divided by number of machines per group
   - Distribution of machines across positions
   - Total machines in the configuration

### Time Complexity

- Matrix operations: O(M × N)
- Map operations: O(log n) for insertions
- Iterator traversal: O(n) amortized
- Overall: O(M × N × log(M × N))

## Project Structure

```
datacenter-capacity/
├── DataCenter.h      # Header file with class definition
├── DataCenter.cpp    # Implementation of core algorithms
├── main.cpp          # Main program with CLI handling
├── Makefile          # Build configuration
├── README.md         # This file
└── sample_input.txt  # Example input file (created by make sample)
```

## Building and Running Examples

### Create and run with sample data:
```bash
make sample
make run-file
```

### Clean build:
```bash
make clean
make
```

### Run interactively:
```bash
make run
```

## Improvements from Original

1. **Modern C++ Features**:
   - Smart pointers for automatic memory management
   - Range-based loops where applicable
   - constexpr for compile-time constants
   - Move semantics support

2. **Better Error Handling**:
   - Input validation with meaningful error messages
   - Exception handling for file operations
   - Bounds checking for array access

3. **Code Organization**:
   - Separated into header, implementation, and main files
   - Clear separation of concerns
   - Improved naming conventions

4. **Enhanced Functionality**:
   - File input support
   - Command-line argument parsing
   - Detailed output option
   - Help documentation

5. **Build System**:
   - Professional Makefile with multiple targets
   - Debug build option with sanitizers
   - Installation/uninstallation support
   - macOS-specific optimizations

## Performance Considerations

- Uses efficient STL containers (std::map)
- Optimized for modern CPUs with `-march=native`
- O2 optimization level for release builds
- Memory-efficient design with move semantics

## Troubleshooting

### Compilation Errors

If you encounter compilation errors:

1. Ensure Xcode Command Line Tools are installed:
   ```bash
   xcode-select --install
   ```

2. Check your compiler version:
   ```bash
   clang++ --version
   ```

3. Try building with verbose output:
   ```bash
   make clean
   make VERBOSE=1
   ```

### Runtime Issues

- Ensure input format matches expected pattern
- Check that group and machine counts are positive integers
- Maximum supported configuration is 1000×1000

## License

Copyright © 2012-2025 Kevin Luzbetak. All rights reserved.

## Author

Kevin Luzbetak  
Original Date: April 25, 2012  
Updated: 2025

---

For questions or issues, please contact the author or submit an issue on the project repository.
