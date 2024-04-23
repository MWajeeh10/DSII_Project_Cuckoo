#include "MovieDatabase.hpp"

class LinearProbeHashTable {
private:
    vector<MovieEntry> table;
    vector<MovieEntry1> table1;
    vector<MovieEntry2> table2;
    int size;
    int capacity;

    size_t hashFunction(const string& key);

public:
    LinearProbeHashTable(int table_size);

    void insertFromFile(const std::string& filename);
    void insert(const MovieEntry& entry);

    MovieEntry* search(const string& key);

    void deleteEntry(const std::string& key);
};