#include "MovieDatabase.hpp"

class QuadraticProbeHashTable {
private:
    vector<MovieEntry> table;
    int size;
    int capacity;

    size_t hashFunction(const string& key);

public:
    QuadraticProbeHashTable(int table_size);

    void insertFromFile(const std::string& filename);
    void insert(const MovieEntry& entry);
    
    MovieEntry* search(const string& key);

    void deleteEntry(const std::string& key);
};