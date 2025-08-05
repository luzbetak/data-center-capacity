# Makefile for Data Center Capacity Calculator
# Optimized for macOS (also works on Linux)

# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -march=native
DEBUGFLAGS = -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS = 

# Target executable
TARGET = datacenter

# Source files
SOURCES = main.cpp DataCenter.cpp
HEADERS = DataCenter.h
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install (optional)
install: $(TARGET)
	@echo "Installing $(TARGET) to /usr/local/bin/"
	@sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	@echo "Removing $(TARGET) from /usr/local/bin/"
	@sudo rm -f /usr/local/bin/$(TARGET)

# Run with sample input
run: $(TARGET)
	./$(TARGET)

# Run with sample file
run-file: $(TARGET)
	./$(TARGET) -f sample_input.txt

# Create sample input file
sample:
	@echo "3 4" > sample_input.txt
	@echo "A1 B1 C1 D1" >> sample_input.txt
	@echo "A2 B2 C2 D2" >> sample_input.txt
	@echo "A3 B3 C3 D3" >> sample_input.txt
	@echo "Sample input file created: sample_input.txt"

# Help
help:
	@echo "Available targets:"
	@echo "  make          - Build the datacenter executable"
	@echo "  make debug    - Build with debug symbols and sanitizers"
	@echo "  make clean    - Remove build files"
	@echo "  make install  - Install to /usr/local/bin/"
	@echo "  make run      - Build and run interactively"
	@echo "  make run-file - Build and run with sample file"
	@echo "  make sample   - Create sample input file"
	@echo "  make help     - Show this help message"

.PHONY: all clean debug install uninstall run run-file sample help
