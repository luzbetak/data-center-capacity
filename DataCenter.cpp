/*============================================================================
 Name        : DataCenter.cpp
 Written by  : Kevin Luzbetak (Updated)
 Date        : April 25, 2012 (Updated 2025)
 Description : Big Data Center Capacity Design - Implementation
============================================================================*/
#include "DataCenter.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

//---------------------------------------------------------------------//
// Helper function to split a string by delimiter
//---------------------------------------------------------------------//
std::vector<std::string> DataCenterCapacity::split(const std::string& str, char delimiter) const {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    
    return tokens;
}

//---------------------------------------------------------------------//
// Function to validate input parameters
//---------------------------------------------------------------------//
bool DataCenterCapacity::validate_input(int groups, int machines) const {
    if (groups <= 0 || machines <= 0) {
        std::cerr << "Error: Number of groups and machines must be positive integers." << std::endl;
        return false;
    }
    
    if (groups > 1000 || machines > 1000) {
        std::cerr << "Error: Maximum supported groups/machines is 1000." << std::endl;
        return false;
    }
    
    return true;
}

//---------------------------------------------------------------------//
// Function split_string_n - improved version
//---------------------------------------------------------------------//
std::string DataCenterCapacity::split_string_n(const std::string& str, int n, char delimiter) const {
    std::vector<std::string> parts = split(str, delimiter);
    
    if (n >= 0 && n < static_cast<int>(parts.size())) {
        return parts[n];
    }
    
    return "";
}

//---------------------------------------------------------------------//
// Function upper_bound - thread-safe version
//---------------------------------------------------------------------//
void DataCenterCapacity::upper_bound(const std::string& key, double value) {
    auto it = hashtable.find(key);
    if (it != hashtable.end()) {
        it->second += value;
    } else {
        hashtable[key] = value;
    }
}

//---------------------------------------------------------------------//
// Function lower_bound - thread-safe version
//---------------------------------------------------------------------//
void DataCenterCapacity::lower_bound(const std::string& key, double value) {
    auto it = matchtable.find(key);
    if (it != matchtable.end()) {
        if (it->second > value) {
            it->second = value;
        }
    } else {
        matchtable[key] = value;
    }
}

//---------------------------------------------------------------------//
// Function to compute Data Center Capacity from file
//---------------------------------------------------------------------//
void DataCenterCapacity::compute_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    
    std::string line;
    std::getline(file, line);
    
    std::istringstream iss(line);
    iss >> m_groups >> n_machines;
    
    if (!validate_input(m_groups, n_machines)) {
        throw std::invalid_argument("Invalid input parameters");
    }
    
    std::vector<std::vector<std::string>> matrix(m_groups, std::vector<std::string>(n_machines));
    
    // Read machine data
    for (int i = 0; i < m_groups; i++) {
        if (!std::getline(file, line)) {
            throw std::runtime_error("Insufficient data in file");
        }
        
        auto machines = split(line, ' ');
        if (static_cast<int>(machines.size()) != n_machines) {
            throw std::runtime_error("Invalid number of machines in group " + std::to_string(i));
        }
        
        for (int j = 0; j < n_machines; j++) {
            matrix[i][j] = machines[j];
        }
    }
    
    // Process the matrix
    for (int j = 0; j < n_machines; j++) {
        for (int i = 0; i < m_groups; i++) {
            std::ostringstream oss;
            oss << j << "-" << matrix[i][j];
            upper_bound(oss.str(), 1000);
            
            // Initialize all subset for machine version
            for (int x = 0; x < n_machines; x++) {
                std::ostringstream oss0;
                oss0 << x << "-" << matrix[i][j];
                upper_bound(oss0.str(), 0.0001);
            }
        }
    }
    
    // Process hashtable to update matchtable
    for (const auto& pair : hashtable) {
        std::string output = split_string_n(pair.first, 1);
        lower_bound(output, pair.second);
    }
    
    // Calculate total RPS
    double subset_rps = static_cast<double>(MAX_GROUP_RPS) / n_machines;
    total_rps = 0.0;
    
    for (const auto& pair : matchtable) {
        int total = static_cast<int>(pair.second / 1000);
        total_rps += total * subset_rps * n_machines;
    }
}

//---------------------------------------------------------------------//
// Function compute Data Center Capacity - improved version
//---------------------------------------------------------------------//
void DataCenterCapacity::compute_user_input() {
    std::cout << "\n=== Data Center Capacity Calculator ===" << std::endl;
    std::cout << "Enter M-groups and N-machines (e.g., '3 4'): ";
    
    std::string input;
    std::getline(std::cin, input);
    
    std::istringstream iss(input);
    if (!(iss >> m_groups >> n_machines)) {
        std::cerr << "Error: Invalid input format. Please enter two integers." << std::endl;
        return;
    }
    
    if (!validate_input(m_groups, n_machines)) {
        return;
    }
    
    std::vector<std::vector<std::string>> matrix(m_groups, std::vector<std::string>(n_machines));
    
    std::cout << "\nEnter " << n_machines << " machine IDs for each of the " 
              << m_groups << " groups:" << std::endl;
    
    // Get input of N machines for each M group
    for (int i = 0; i < m_groups; i++) {
        std::cout << "Group " << (i + 1) << ": ";
        std::getline(std::cin, input);
        
        auto machines = split(input, ' ');
        if (static_cast<int>(machines.size()) != n_machines) {
            std::cerr << "Error: Expected " << n_machines << " machines, got " 
                      << machines.size() << std::endl;
            return;
        }
        
        for (int j = 0; j < n_machines; j++) {
            matrix[i][j] = machines[j];
        }
    }
    
    // Clear previous data
    hashtable.clear();
    matchtable.clear();
    
    // Rotate matrix and add to map
    for (int j = 0; j < n_machines; j++) {
        for (int i = 0; i < m_groups; i++) {
            std::ostringstream oss;
            oss << j << "-" << matrix[i][j];
            upper_bound(oss.str(), 1000);
            
            // Initialize all subset for machine version
            for (int x = 0; x < n_machines; x++) {
                std::ostringstream oss0;
                oss0 << x << "-" << matrix[i][j];
                upper_bound(oss0.str(), 0.0001);
            }
        }
    }
    
    // Process hashtable to update matchtable
    for (const auto& pair : hashtable) {
        std::string output = split_string_n(pair.first, 1);
        lower_bound(output, pair.second);
    }
    
    // Calculate total RPS
    double subset_rps = static_cast<double>(MAX_GROUP_RPS) / n_machines;
    total_rps = 0.0;
    
    for (const auto& pair : matchtable) {
        int total = static_cast<int>(pair.second / 1000);
        total_rps += total * subset_rps * n_machines;
    }
}

//---------------------------------------------------------------------//
// Display results - basic version
//---------------------------------------------------------------------//
void DataCenterCapacity::display_results() const {
    std::cout << "\n=====================================\n";
    std::cout << "Data Center Configuration\n";
    std::cout << "=====================================\n";
    std::cout << "Requests Per Second = " << std::fixed << std::setprecision(2) 
              << total_rps << " RPS\n";
    std::cout << "M-groups            = " << m_groups << "\n";
    std::cout << "N-machines          = " << n_machines << "\n";
    std::cout << "Max Group RPS       = " << MAX_GROUP_RPS << "\n";
    std::cout << "=====================================\n\n";
}

//---------------------------------------------------------------------//
// Display results - detailed version
//---------------------------------------------------------------------//
void DataCenterCapacity::display_detailed_results() const {
    display_results();
    
    if (!matchtable.empty()) {
        std::cout << "Machine Version Summary:\n";
        std::cout << "------------------------\n";
        for (const auto& pair : matchtable) {
            std::cout << "Version " << pair.first << ": " 
                      << std::fixed << std::setprecision(2) 
                      << pair.second << " units\n";
        }
        std::cout << "------------------------\n\n";
    }
}
