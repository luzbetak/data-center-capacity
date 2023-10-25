# Data Center Capacity Computation Program

Author: Kevin Luzbetak  
Date: April 25, 2012  
Description: This program is designed to compute the capacity of a big data center. It's written in C++ and can be compiled using the command `c++ data_center.cpp`.

## Class: DataCenterCapacity

The `DataCenterCapacity` class encapsulates all the necessary methods and data structures to compute the data center capacity based on user input.

### Data Structures:
- **hashtable**: A map to store the computation data with a string as a key and a double as a value.
- **matchtable**: A map to store the matching data with a string as a key and a double as a value.
- **MAX_GROUP_RPS**: A constant integer initialized to 100, representing the maximum requests per second for a group.

### Methods:
- **split_string_n(string str, int n)**: A method to split a string `str` at the nth occurrence of a character.
- **upper_bound(string key, double i)**: A method to insert or update the `hashtable` with a key-value pair.
- **lower_bound(string key, double i)**: A method to insert or update the `matchtable` with a key-value pair if the value is lower.
- **compute_user_input()**: The core method to handle user input, compute the data center capacity, and output the results.

#### Method Descriptions:
1. **split_string_n**:
    - Utilizes `stringstream` to split a string based on a delimiter and returns a specific word based on the index `n`.
   
2. **upper_bound**:
    - Inserts a new key-value pair into `hashtable` or updates the value of an existing key by adding the new value `i`.
   
3. **lower_bound**:
    - Inserts a new key-value pair into `matchtable` or updates the value of an existing key if the new value `i` is lower.
   
4. **compute_user_input**:
    - Prompts the user to input the number of M-groups and N-machines.
    - Accepts input for N machines for each M group.
    - Rotates the matrix and adds data to `hashtable`.
    - Iterates through `hashtable` to update `matchtable` based on specific conditions.
    - Computes the Requests Per Second (RPS) based on the data in `matchtable`.
    - Outputs the Data Center Configuration including Requests Per Second, M-group, and N-machines.

## Main Function:
The main function creates an instance of `DataCenterCapacity`, calls the `compute_user_input()` method to compute the data center capacity based on user input, and finally deletes the `DataCenterCapacity` instance to free up memory.

## Compilation:
Compile the program using the following command:
```bash
c++ data_center.cpp
