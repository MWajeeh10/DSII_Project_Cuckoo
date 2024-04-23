#include "MovieDatabase.hpp"


class CuckooHashTable: public HashTable{
private:
    vector<MovieEntry2> table1;
    vector<MovieEntry2> table2;
    int size;
    int totalentries = 0;
    // Hash functions
    size_t hashFunction1(const string& key);
    size_t hashFunction2(const string& key);

public:
    CuckooHashTable(int table_size);
    void insert(const MovieEntry2& entry);
    void resize();
    void insertFromFile(const std::string& filename);
    MovieEntry2* search(const string& key);
    void deleteEntry(const string& key);
};