# CCP6214 Algorithm Design and Analysis Assignment

## Overview

This repository contains the complete implementation of the CCP6214 Algorithm Design and Analysis assignment.

The project implements and evaluates:

* Dataset Generator
* Radix Sort (LSD)
* Heap Sort (Max Heap)
* Hash Table Search using Open Addressing and Linear Probing

The project includes algorithm implementations, step-by-step demonstrations, performance experiments, output files, and documentation required for the assignment.

---

## Implemented Components

### Dataset Generator

Generates datasets in CSV format containing:

```text
id,text
```

Features:

* Unique 10-digit integer IDs
* Random 5-letter lowercase strings
* Assignment-compliant random seed
* User-specified dataset size

Output:

```text
datasets/dataset_n.csv
```

---

### Radix Sort (LSD)

Implements Least Significant Digit Radix Sort using stable Counting Sort.

Includes:

* Full sorting implementation
* Runtime measurement
* Step-by-step demonstration version

Outputs:

```text
outputs/sorted/radix_sorted_dataset_n.csv
outputs/sorted/radix_sort_runtime_n.txt
outputs/radix_steps/dataset_n_radix_sorted_step_1_7.txt
```

---

### Heap Sort (Max Heap)

Implements Heap Sort using a Max Heap.

Includes:

* Full sorting implementation
* Runtime measurement
* Step-by-step demonstration version

Outputs:

```text
outputs/sorted/heap_sorted_dataset_n.csv
outputs/sorted/heap_sort_runtime_n.txt
outputs/heap_steps/dataset_n_heap_sorted_step_1_7.txt
```

---

### Hash Table Search

Implements a custom hash table using:

* Open Addressing
* Linear Probing
* Hash Function:

```text
index = key % capacity
```

Includes:

* Best-case search analysis
* Average-case search analysis
* Worst-case search analysis
* Step-by-step search demonstration

Outputs:

```text
outputs/search/hash_table_search_dataset_n.txt
outputs/search/dataset_n_hash_table_search_step_TARGET.txt
```

---

## Project Structure

```text
CCP6214_Algorithm_Assignment/
│
├── src/
│   ├── dataset_generator.cpp
│   ├── radix_sort_step.cpp
│   ├── radix_sort.cpp
│   ├── heap_sort_step.cpp
│   ├── heap_sort.cpp
│   ├── hash_table_search_step.cpp
│   ├── hash_table_search.cpp
│   ├── Record.cpp
│   ├── CSVReader.cpp
│   └── CSVWriter.cpp
│
├── include/
│   ├── Record.h
│   ├── CSVReader.h
│   ├── CSVWriter.h
│   ├── Utilities.h
│   ├── Timer.h
│   ├── HashTable.h
│   ├── RadixSort.h
│   └── HeapSort.h
│
├── datasets/
│   ├── dataset_1000.csv
│   ├── dataset_5000.csv
│   ├── dataset_10000.csv
│   ├── dataset_50000.csv
│   ├── dataset_100000.csv
│   ├── dataset_250000.csv
│   ├── dataset_500000.csv
│   ├── dataset_1000000.csv
│   ├── dataset_2000000.csv
│   └── dataset_5000000.csv
│
├── outputs/
│   ├── radix_steps/
│   │   └── dataset_n_radix_sorted_step_1_7.txt
│   │
│   ├── heap_steps/
│   │   └── dataset_n_heap_sorted_step_1_7.txt
│   │
│   ├── sorted/
│   │   ├── radix_sorted_dataset_n.csv
│   │   ├── heap_sorted_dataset_n.csv
│   │   ├── radix_sort_runtime_n.txt
│   │   └── heap_sort_runtime_n.txt
│   │
│   └── search/
│       ├── hash_table_search_dataset_n.txt
│       └── dataset_n_hash_table_search_step_TARGET.txt
│
├── experiments/
│   ├── screenshots/
│   ├── charts/
│   └── results/
│
├── documentation/
│   ├── report.docx
│   ├── references.txt
│   └── empty report template.docx
│
├── build/
│   ├── dataset_generator.exe
│   ├── radix_sort_step.exe
│   ├── radix_sort.exe
│   ├── heap_sort_step.exe
│   ├── heap_sort.exe
│   ├── hash_table_search_step.exe
│   └── hash_table_search.exe
│
├── README.md
├── Makefile
└── .gitignore
```


## Build Instructions

### Linux / macOS

Build all programs:

```bash
make all
```

Clean build files:

```bash
make clean
```

### Windows (g++)

Example:

```powershell
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/dataset_generator.cpp src/Record.cpp src/CSVReader.cpp src/CSVWriter.cpp -o build/dataset_generator.exe
```

---

## Running the Programs

### Generate Dataset

```powershell
.\build\dataset_generator.exe 1000
```

Example output:

```text
datasets/dataset_1000.csv
```

---

### Radix Sort

```powershell
.\build\radix_sort.exe datasets\dataset_1000.csv
```

---

### Heap Sort

```powershell
.\build\heap_sort.exe datasets\dataset_1000.csv
```

---

### Hash Table Search

```powershell
.\build\hash_table_search.exe datasets\dataset_1000.csv
```

---

## Experiment Dataset Sizes

The experiments are designed to support at least ten input sizes:

```text
1000
5000
10000
50000
100000
250000
500000
1000000
2000000
5000000
```

---

## Compiler Configuration

All programs were compiled and tested using:

```text
C++17
-Wall
-Wextra
-pedantic
```

---

## Assignment Requirements Satisfied

* Custom Dataset Generator
* Custom Radix Sort
* Custom Heap Sort
* Custom Hash Table Search
* Open Addressing
* Linear Probing
* Step-by-Step Demonstrations
* Runtime Analysis
* Experimental Evaluation
* Documentation and Report Preparation

---

## Authors

### Group Leader

Ahmed Siddig Adam Mohamed
241UC240H5

### Group Members

AL-MAWERI, Ebrahim Mohammed Abdullah
241UC240QK

MOHAMMED, Mohammed Abdulaziz
251UC25085

---

## Course Information

Course: CCP6214 Algorithm Design and Analysis
Lecture Class: TC1L
Tutorial Class: TT3L
Trimester: 2610
