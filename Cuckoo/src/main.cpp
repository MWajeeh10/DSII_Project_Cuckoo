#include <iostream>

#include "MovieDatabase.hpp"
#include "CuckooHashTable.hpp"
#include "LinearProbeHashTable.hpp"
#include "QuadraticProbeHashTable.hpp"

using namespace std;

// int main() {
//     MovieDatabase movieDB; // Create an instance of MovieDatabase

//     // Load movies from the CSV file
//     movieDB.LoadMoviesFromCsv("./Cuckoo/input/unique_indian_movies.csv");

//     // Print the loaded movie entries
//     movieDB.PrintMovieEntries();

//     return 0;
// }

int main() {
    // Create a CuckooHashTable instance
    // CuckooHashTable hashTable(1000);

    // Alternatively, create a LinearProbeHashTable instance
    // LinearProbeHashTable hashTable(50000);

    // Or, a QuadraticProbeHashTable
    QuadraticProbeHashTable hashTable(60000);

    // Insert movie entries from a file
    hashTable.insertFromFile("./Cuckoo/input/unique_indian_movies.csv");

    // -- Test cases -- //
    // Test cases to check if specific movies are in the hash table
    MovieEntry2* result1 = hashTable.search("Dr. Shaitan");
    if (result1 != nullptr) {
        std::cout << "Found movie: " << result1->Name << std::endl;
    } else {
        std::cout << "Movie 'Dr. Shaitan' not found." << std::endl;
    }

    MovieEntry2* result2 = hashTable.search("Prassthanam");
    if (result2 != nullptr) {
        std::cout << "Found movie: " << result2->Name << std::endl;
        // std::cout << "ID" << result2->ID << " Name" << result2->Name << " Year" << result2->Year << " Timing" << result2->Timing << " Rating" << result2->Rating << " Votes" << result2->Votes << " Genre" << result2->Genre << " Language" << result2->Language;
    } else {
        std::cout << "Movie 'Prassthanam' not found." << std::endl;
    }

    // Test case to check if a movie not in the hash table is found
    MovieEntry2* result3 = hashTable.search("Inception");
    if (result3 != nullptr) {
        std::cout << "Found movie: " << result3->Name << std::endl;
    } else {
        std::cout << "Movie 'Inception' not found." << std::endl;
    }

    MovieEntry2* result4 = hashTable.search("The Dark Knight");
    if (result4 != nullptr) {
        std::cout << "Found movie: " << result4->Name << std::endl;
    } else {
        std::cout << "Movie 'The Dark Knight' not found." << std::endl;
    }

    // Custom test case //
    // Inserting
    MovieEntry2 customMovie;
    customMovie.ID = "1234";
    customMovie.Name = "Custom Movie";
    customMovie.Year = "2024";
    customMovie.Timing = "120 min";
    customMovie.Rating = "4.5";
    customMovie.Votes = "15";
    customMovie.Genre = "Educational";
    customMovie.Language = "Urdu";
    hashTable.insert(customMovie);

    // Searching after insertion
    MovieEntry2* customResult = hashTable.search("Custom Movie");
    if (customResult != nullptr) {
        std::cout << "Found movie: " << customResult->Name << std::endl;
    } else {
        std::cout << "Movie 'Custom Movie' not found." << std::endl;
    }

    // Deleting
    hashTable.deleteEntry("Custom Movie");

    // Searching after deletion
    customResult = hashTable.search("Custom Movie");
    if (customResult != nullptr) {
        std::cout << "Found movie: " << customResult->Name << std::endl;
    } else {
        std::cout << "Movie 'Custom Movie' not found." << std::endl;
    }

    return 0;
}

// used for cleaning the dataset

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <unordered_set>
// #include <vector>

// int main() {
//     std::ifstream inFile("./Cuckoo/input/cleaned_indian_movies.csv");
//     std::ofstream outFile("./Cuckoo/input/unique_indian_movies.csv");
//     std::unordered_set<std::string> movieNames;
//     std::string line;

//     if (inFile.is_open()) {
//         std::getline(inFile, line);  // Skip header line
//         outFile << line << std::endl;  // Write header line to output file

//         while (std::getline(inFile, line)) {
//             std::istringstream ss(line);
//             std::string id, movieName;
//             std::getline(ss, id, ',');  // Extract ID
//             std::getline(ss, movieName, ',');  // Extract Movie Name

//             if (movieNames.find(movieName) == movieNames.end()) {  // Check if Movie Name is unique
//                 movieNames.insert(movieName);
//                 outFile << line << std::endl;  // Write line to output file
//             }
//         }
//     }

//     inFile.close();
//     outFile.close();

//     return 0;
// }