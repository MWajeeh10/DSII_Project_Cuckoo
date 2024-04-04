#ifndef MOVIE_DATABASE_HPP
#define MOVIE_DATABASE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct MovieEntry {
    string Name;
    double Rating;
    double RatingCount;
    string ReleaseDate;
    string Budget;
    string DomesticGross;
    string DomesticGross2;
    string DomesticWeekendGross;
    string DomesticWeekend;
    string DomesticWeekendDate;
    string WorldwideGross;
};

class MovieDatabase {
private:
    vector<MovieEntry> entries;

public:
    // Function to load movies from a CSV file
    void LoadMoviesFromCsv(const string &csv_file);

    // Function to print movie entries
    void PrintMovieEntries();
};

// Cuckoo Hasing
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

// Linear probing
class LinearProbeHashTable {
private:
    vector<MovieEntry> table;
    int size;
    int capacity;

    size_t hashFunction(const string& key);

public:
    LinearProbeHashTable(int table_size);

    void insertFromFile(const std::string& filename);

    MovieEntry* search(const string& key);
};

#endif /* MOVIE_DATABASE_HPP */
