#include "MovieDatabase.hpp"

class QuadraticProbeHashTable {
private:
    vector<MovieEntry2> table;
    int size;
    int capacity;

    size_t hashFunction(const string& key);

    // vector<MovieEntry1> table1;
    // vector<MovieEntry> table2;

public:
    QuadraticProbeHashTable(int table_size);

    void insertFromFile(const std::string& filename);
    void insert(const MovieEntry2& entry);
    
    MovieEntry2* search(const string& key);

    void deleteEntry(const std::string& key);
};