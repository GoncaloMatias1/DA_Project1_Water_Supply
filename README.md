# Water Supply Management Analysis Tool

## Introduction
Developed for the Design of Algorithms course (Spring 2024), this tool is designed to assist in managing the water supply network in Portugal. It simulates and analyzes water flow through the network, ensuring optimal distribution and resource management.

## Team Members
- Rodrigo Ferreira Alves - up202207478
- Gonçalo de Abreu Matias - up202108703
- David Tavares Simões - up202210329

## Installation
To install and run the project, follow these steps:

```bash
git clone https://github.com/GoncaloMatias1/DA-Project-23-24
cd DA-Project-23-24
```

To compile the project:
```bash
mkdir build
cd build
cmake ..
make
```

## Features
- Implementation of the greedy algorithmic approach for maximum-flow problems.
- Data parsing and processing from CSV files.
- Graphical representation of water networks.
- User-friendly menu interface for system interaction.
- Comprehensive analysis and reporting of network's water distribution.

## Usage
To use the application, execute the following command in the terminal:

```bash
./DA_Project_23_24
```

Navigate through the menu to access different functionalities such as data parsing, analysis, and simulation results.

## Algorithmic Approach
The core algorithmic approach used in this project is based on the Edmonds-Karp algorithm, ensuring efficient and optimal water flow through the network.

## Documentation
The project's documentation is generated using Doxygen and is available under the `docs` directory. It includes an exhaustive time complexity analysis of the implemented algorithms.