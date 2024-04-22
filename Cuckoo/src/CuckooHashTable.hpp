#include "MovieDatabase.hpp"

class CuckooHashTable {
private:
    vector<MovieEntry> table1;
    vector<MovieEntry> table2;
    int size;

    // Hash functions
    size_t hashFunction1(const string& key);
    size_t hashFunction2(const string& key);

public:
    CuckooHashTable(int table_size);
    void insert(const MovieEntry& entry);
    void insertFromFile(const std::string& filename);
    MovieEntry* search(const string& key);
};