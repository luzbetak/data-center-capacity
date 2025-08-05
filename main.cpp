/*============================================================================
 Name        : main.cpp
 Written by  : Kevin Luzbetak (Updated)
 Date        : April 25, 2012 (Updated 2025)
 Description : Big Data Center Capacity Design - Main Program
============================================================================*/
#include "DataCenter.h"
#include <iostream>
#include <memory>
#include <cstring>

void display_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options]\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help        Show this help message\n";
    std::cout << "  -f, --file FILE   Read input from file\n";
    std::cout << "  -d, --detailed    Show detailed results\n";
    std::cout << "  -i, --interactive Interactive mode (default)\n\n";
    std::cout << "Example input format:\n";
    std::cout << "  3 4                 (3 groups, 4 machines per group)\n";
    std::cout << "  A1 B1 C1 D1        (Group 1 machines)\n";
    std::cout << "  A2 B2 C2 D2        (Group 2 machines)\n";
    std::cout << "  A3 B3 C3 D3        (Group 3 machines)\n\n";
}

int main(int argc, char* argv[]) {
    try {
        auto data_capacity = std::make_unique<DataCenterCapacity>();
        bool detailed = false;
        bool file_mode = false;
        std::string filename;
        
        // Parse command line arguments
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                display_usage(argv[0]);
                return 0;
            } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--detailed") == 0) {
                detailed = true;
            } else if ((strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) && i + 1 < argc) {
                file_mode = true;
                filename = argv[++i];
            } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interactive") == 0) {
                file_mode = false;
            } else {
                std::cerr << "Unknown option: " << argv[i] << std::endl;
                display_usage(argv[0]);
                return 1;
            }
        }
        
        // Process input
        if (file_mode) {
            std::cout << "Reading from file: " << filename << std::endl;
            data_capacity->compute_from_file(filename);
        } else {
            data_capacity->compute_user_input();
        }
        
        // Display results
        if (detailed) {
            data_capacity->display_detailed_results();
        } else {
            data_capacity->display_results();
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 1;
    }
}
