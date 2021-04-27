/*============================================================================
 Name        : DataCenter.cpp
 Written by  : Kevin Luzbetak
 Date        : April 25, 2012
 Email       : fdxowye@gmail.com 
 Description : Big Data Center Capacity Design 
 Compile     : c++ data_center.cpp
============================================================================*/
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <sstream>
using namespace std;

/* --------------------------------------------------------------------------
 *  DataCenterCapacity class is using the following O:
 *   1. copying user data into matrix m*n
 *   2. reading data from matrix m*n
 *   3. inserts into C++ associative containers O(log n)
 *   4. incrementing an iterator 0 (log n) (amortized O(1))
 *   5. inserts into C++ associative containers O(log n)
 *   6. incrementing an iterator 0 (log n) (amortized O(1))
 * -------------------------------------------------------------------------*/
class DataCenterCapacity  {

    map<string, double> hashtable;
    map<string, double> matchtable;
    static const int MAX_GROUP_RPS=100;

    string split_string_n(string str, int n);
    void upper_bound(string key, double i);
    void lower_bound(string key, double i);

public:
    DataCenterCapacity() {}
    void compute_user_input();
};

//---------------------------------------------------------------------//
// function split_string_n using string stream
//---------------------------------------------------------------------//
string DataCenterCapacity::split_string_n(string str, int n)
{
    string word;
    stringstream stream(str);

    for (int i=0; i<n; i++)
        getline(stream, word, '-');

    getline(stream, word, '-');
    return word;
}
//---------------------------------------------------------------------//
// function upper_bound using
// inserts into C++ associative containers O(log n)
//---------------------------------------------------------------------//
void DataCenterCapacity::upper_bound(string key, double i)
{
    if (hashtable[key]) hashtable[key] += i;
    else hashtable[key] = i;
}
//---------------------------------------------------------------------//
// function lower_bound using
// inserts into C++ associative containers O(log n)
//---------------------------------------------------------------------//
void DataCenterCapacity::lower_bound(string key, double i)
{
    if (matchtable[key]) {
        if (matchtable[key] > i) matchtable[key] = i;
    }
    else matchtable[key] = i;
}
//---------------------------------------------------------------------//
// function compute Data Center Capacity
// inserts into C++ associative containers O(log n)
//---------------------------------------------------------------------//
void DataCenterCapacity::compute_user_input()
{
    char user_input[256];
    string user_in;
    int m_groups = 0;
    int n_machines = 0;
    double RequestPerSecond = 0;

    // get user input for number of M-groups and N-machines
    cout << "Enter M-groups by N-machines:" << endl;;
    cin.getline (user_input,256);
    stringstream stream(user_input);
    getline(stream, user_in, ' ');
    if ( ! (istringstream(user_in) >> m_groups) ) m_groups = 0;
    getline(stream, user_in, ' ');
    if ( ! (istringstream(user_in) >> n_machines) ) n_machines = 0;
    string matrix[m_groups][n_machines];

    //get input of N machines for each M group
    for (int i=0; i < m_groups; i++)
    {
        cin.getline (user_input,256);
        int j=0;
        istringstream iss(user_input);
        do {
            string sub;
            iss >> sub;
            if (sub.length()) {
                matrix[i][j] = sub;
                j++;
            }
        } while (iss);
    }

    // rotate matrix and add to map
    for (int j=0; j < n_machines; j++)
    {
        for (int i=0; i < m_groups  ; i++)
        {
            ostringstream oss;
            oss << j << "-" << matrix[i][j];
            upper_bound(oss.str(),  1000);

            //--- Initialize all subset for machine version
            for (int x=0; x < n_machines; x++)
            {
                ostringstream oss0;
                oss0 << x << "-" << matrix[i][j];
                upper_bound(oss0.str(),  0.0001);
            }
        }
    }

    // Incrementing an iterator O(log n) (amortized O(1))
    for ( map<string, double>::iterator ii=hashtable.begin(); ii!=hashtable.end(); ++ii)
    {
        string output = split_string_n((*ii).first, 1);
        lower_bound(output, (*ii).second);
    }

    float subset_rps = MAX_GROUP_RPS / n_machines;

    // Incrementing an iterator O(log n) (amortized O(1))
    for ( map<string, double>::iterator ii=matchtable.begin(); ii!=matchtable.end(); ++ii)
    {
        int total = (*ii).second  / 1000;
        RequestPerSecond += total * subset_rps * n_machines;
    }

    cout << "-------------------------------------" << endl;
    cout << "Data Center Configuration"             << endl;
    cout << "Requests Per Second = " << RequestPerSecond << endl;
    cout << "M-group             = " << m_groups    << endl;
    cout << "N-machines          = " << n_machines  << endl;
    cout << "-------------------------------------" << endl << endl;
}

//---------------------------------------------------------------------//
//           Main function instantiate DataCenterCapacity
//---------------------------------------------------------------------//
int main()
{
    DataCenterCapacity *data_capacity = new DataCenterCapacity();
    data_capacity->compute_user_input();
    delete data_capacity;
    return 0;
}

