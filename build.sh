#!/bin/bash
# Build script for Data Center Capacity Calculator
# Alternative to Makefile for simple builds on macOS

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
CXX="clang++"
CXXFLAGS="-std=c++17 -Wall -Wextra -Wpedantic -O2 -march=native"
TARGET="datacenter"
SOURCES="main.cpp DataCenter.cpp"

echo -e "${YELLOW}Building Data Center Capacity Calculator...${NC}"

# Check if clang++ is available
if ! command -v $CXX &> /dev/null; then
    echo -e "${RED}Error: clang++ not found. Please install Xcode Command Line Tools.${NC}"
    echo "Run: xcode-select --install"
    exit 1
fi

# Clean previous build
if [ -f "$TARGET" ]; then
    echo "Removing previous build..."
    rm -f "$TARGET"
fi

# Compile
echo "Compiling with $CXX..."
if $CXX $CXXFLAGS -o $TARGET $SOURCES; then
    echo -e "${GREEN}Build successful!${NC}"
    echo -e "Run with: ${YELLOW}./$TARGET${NC}"
    
    # Make executable
    chmod +x $TARGET
    
    # Show file info
    echo -e "\nExecutable info:"
    ls -lh $TARGET
    
    # Offer to run
    echo -e "\nWould you like to run the program now? (y/n)"
    read -r response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        echo -e "\n${YELLOW}Running $TARGET...${NC}\n"
        ./$TARGET
    fi
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi
