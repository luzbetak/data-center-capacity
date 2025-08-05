/*============================================================================
 Name        : DataCenter.h
 Written by  : Kevin Luzbetak (Updated)
 Date        : April 25, 2012 (Updated 2025)
 Description : Big Data Center Capacity Design - Header File
============================================================================*/
#ifndef DATACENTER_H
#define DATACENTER_H

#include <string>
#include <map>
#include <vector>
#include <memory>

class DataCenterCapacity {
private:
    std::map<std::string, double> hashtable;
    std::map<std::string, double> matchtable;
    static constexpr int MAX_GROUP_RPS = 100;
    
    // Configuration parameters
    int m_groups = 0;
    int n_machines = 0;
    double total_rps = 0.0;
    
    // Helper methods
    std::string split_string_n(const std::string& str, int n, char delimiter = '-') const;
    void upper_bound(const std::string& key, double value);
    void lower_bound(const std::string& key, double value);
    std::vector<std::string> split(const std::string& str, char delimiter = ' ') const;
    bool validate_input(int groups, int machines) const;
    
public:
    DataCenterCapacity() = default;
    ~DataCenterCapacity() = default;
    
    // Disable copy constructor and assignment operator
    DataCenterCapacity(const DataCenterCapacity&) = delete;
    DataCenterCapacity& operator=(const DataCenterCapacity&) = delete;
    
    // Move constructor and assignment operator
    DataCenterCapacity(DataCenterCapacity&&) = default;
    DataCenterCapacity& operator=(DataCenterCapacity&&) = default;
    
    // Main computation methods
    void compute_user_input();
    void compute_user_input(bool auto_generate);
    void compute_from_file(const std::string& filename);
    
    // Getters for results
    double get_requests_per_second() const { return total_rps; }
    int get_groups() const { return m_groups; }
    int get_machines() const { return n_machines; }
    
    // Display methods
    void display_results() const;
    void display_detailed_results() const;
};

#endif // DATACENTER_H
