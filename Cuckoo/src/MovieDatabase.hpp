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

struct MovieEntry1 {
    std::string ID;
    std::string type;
    std::string Name;
    std::string Cast;
    std::string Country;
    std::string DateAdded;
    std::string ReleaseYear;
    std::string Rating;
    std::string Duration;
    std::string ListedIn;
    std::string Description;
};

struct MovieEntry2 { // for the newest dataset: "unique_indian_movies.csv"
    std::string ID;
    std::string Name;
    std::string Year;
    std::string Timing;
    std::string Rating;
    std::string Votes;
    std::string Genre;
    std::string Language;
};

class MovieDatabase {
private:
    vector<MovieEntry2> entries;

public:
    // Function to load movies from a CSV file
    void LoadMoviesFromCsv(const string &csv_file);

    // Function to print movie entries
    void PrintMovieEntries();
};


#endif
