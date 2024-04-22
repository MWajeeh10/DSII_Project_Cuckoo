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


#endif
