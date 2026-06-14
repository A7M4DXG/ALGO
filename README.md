# CCP6214 Algorithm Assignment

## Assignment Overview

This project is the skeleton for the CCP6214 Algorithm Design and Analysis assignment. It is prepared for implementing and comparing:

- Radix Sort
- Heap Sort
- Hash Table Search

No algorithm implementations are included yet. Source files contain placeholders and TODO markers so development can begin from a clean, compilable structure.

## Project Structure

```text
CCP6214_Algorithm_Assignment/
|-- src/
|   |-- dataset_generator.cpp
|   |-- radix_sort_step.cpp
|   |-- radix_sort.cpp
|   |-- heap_sort_step.cpp
|   |-- heap_sort.cpp
|   |-- hash_table_search_step.cpp
|   |-- hash_table_search.cpp
|   |-- Record.cpp
|   |-- CSVReader.cpp
|   `-- CSVWriter.cpp
|-- include/
|   |-- Record.h
|   |-- CSVReader.h
|   |-- CSVWriter.h
|   |-- Utilities.h
|   |-- Timer.h
|   |-- HashTable.h
|   |-- RadixSort.h
|   `-- HeapSort.h
|-- datasets/
|-- outputs/
|   |-- radix_steps/
|   |-- heap_steps/
|   |-- sorted/
|   `-- search/
|-- experiments/
|   |-- screenshots/
|   |-- charts/
|   `-- results/
|-- documentation/
|   |-- report.docx
|   `-- references.txt
|-- build/
|-- README.md
|-- Makefile
`-- .gitignore
```

## Build Instructions

Use the provided Makefile from the project root:

```bash
make all
```

To build one program:

```bash
make dataset_generator
make radix_sort_step
make radix_sort
make heap_sort_step
make heap_sort
make hash_table_search_step
make hash_table_search
```

To remove compiled files:

```bash
make clean
```

## Execution Instructions

After building, executables are placed in the `build/` folder.

```bash
./build/dataset_generator
./build/radix_sort_step
./build/radix_sort
./build/heap_sort_step
./build/heap_sort
./build/hash_table_search_step
./build/hash_table_search
```

On Windows PowerShell:

```powershell
.\build\dataset_generator.exe
.\build\radix_sort_step.exe
.\build\radix_sort.exe
.\build\heap_sort_step.exe
.\build\heap_sort.exe
.\build\hash_table_search_step.exe
.\build\hash_table_search.exe
```

## Expected Outputs

- Generated datasets should be saved in `datasets/`.
- Radix Sort step outputs should be saved in `outputs/radix_steps/`.
- Heap Sort step outputs should be saved in `outputs/heap_steps/`.
- Final sorted files should be saved in `outputs/sorted/`.
- Hash Table search outputs should be saved in `outputs/search/`.
- Experiment results should be saved in `experiments/results/`.
- Charts should be saved in `experiments/charts/`.
- Screenshots should be saved in `experiments/screenshots/`.

## Experiment Workflow

1. Generate datasets using `dataset_generator`.
2. Run step-by-step programs for small datasets.
3. Run full Radix Sort and Heap Sort experiments.
4. Run Hash Table search experiments.
5. Record execution time and observations.
6. Create charts from collected results.
7. Add screenshots, charts, and analysis to the report.

## Documentation Checklist

- Assignment cover page completed.
- Member details updated in every `.cpp` file.
- Task distribution completed in every `.cpp` file.
- Algorithm explanation added.
- Time complexity analysis added.
- Experiment method described.
- Results tables included.
- Charts included.
- Screenshots included.
- References listed in `documentation/references.txt`.

## Submission Checklist

- Source code compiles successfully.
- All required executables are present or buildable.
- Dataset files are available when required.
- Output files are organized in the correct folders.
- Report is completed as `documentation/report.docx`.
- References are completed in `documentation/references.txt`.
- Unnecessary build files are removed before submission.
