#include "MovieDatabase.hpp"

class LinearProbeHashTable {
private:
    vector<MovieEntry2> table;  // hash table
    int size;                   // number of elements currently
    int capacity;               // maximum number of elements

    size_t hashFunction(const string& key);

    // vector<MovieEntry1> table1;
    // vector<MovieEntry> table2;

public:
    // Constructor
    LinearProbeHashTable(int table_size);

    // Insertion functions
    void insertFromFile(const std::string& filename);
    void insert(const MovieEntry2& entry);

    // Search/find function
    MovieEntry2* search(const string& key);

    // Delete/remove function
    void deleteEntry(const std::string& key);
};