# School Assignment

A C++ program for school assignment problems, implementing algorithms to allocate students to schools based on preferences, capacities, and various constraints.

## Features

- Student-to-school assignment algorithms
- Multiple instance types (synthetic and real-world data)

## Building

This project uses CMake (minimum version 3.22) and requires C++17.

```bash
# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release
```

## Running

```bash
./build/SchoolAssignment
```

## Project Structure

- `src/` - Source files
- `include/` - Header files
  - `optimization/` - Optimization algorithms (Initial Solution, LNS)
  - `parameters/` - Configuration and parameters
  - `sideFunctions/` - Utility functions
- `Data/` - Input/output data directory
- `Instance_*.txt` - Various test instances
- `realschooldata.csv` / `realstudentdata.csv` - Real-world data

## License

See LICENSE file for details.
