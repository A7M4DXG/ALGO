CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude
BUILD_DIR := build
COMMON_SRC := src/Record.cpp src/CSVReader.cpp src/CSVWriter.cpp

.PHONY: all clean

all: dataset_generator radix_sort_step radix_sort heap_sort_step heap_sort hash_table_search_step hash_table_search

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

dataset_generator: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/dataset_generator.cpp $(COMMON_SRC) -o $(BUILD_DIR)/dataset_generator.exe

radix_sort_step: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/radix_sort_step.cpp $(COMMON_SRC) -o $(BUILD_DIR)/radix_sort_step.exe

radix_sort: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/radix_sort.cpp $(COMMON_SRC) -o $(BUILD_DIR)/radix_sort.exe

heap_sort_step: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/heap_sort_step.cpp $(COMMON_SRC) -o $(BUILD_DIR)/heap_sort_step.exe

heap_sort: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/heap_sort.cpp $(COMMON_SRC) -o $(BUILD_DIR)/heap_sort.exe

hash_table_search_step: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/hash_table_search_step.cpp $(COMMON_SRC) -o $(BUILD_DIR)/hash_table_search_step.exe

hash_table_search: $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/hash_table_search.cpp $(COMMON_SRC) -o $(BUILD_DIR)/hash_table_search.exe

clean:
	rm -rf $(BUILD_DIR)/*.exe $(BUILD_DIR)/*.o $(BUILD_DIR)/*.obj \
		$(BUILD_DIR)/dataset_generator \
		$(BUILD_DIR)/radix_sort_step \
		$(BUILD_DIR)/radix_sort \
		$(BUILD_DIR)/heap_sort_step \
		$(BUILD_DIR)/heap_sort \
		$(BUILD_DIR)/hash_table_search_step \
		$(BUILD_DIR)/hash_table_search
