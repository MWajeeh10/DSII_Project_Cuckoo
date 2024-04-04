#include <iostream>
#include "MovieDatabase.hpp" // Include the header file

using namespace std;

// int main() {
//     MovieDatabase movieDB; // Create an instance of MovieDatabase

//     // Load movies from the CSV file
//     movieDB.LoadMoviesFromCsv("./input/Movies.csv");

//     // Print the loaded movie entries
//     movieDB.PrintMovieEntries();

//     return 0;
// }

int main() {
    // Create a CuckooHashTable instance
    CuckooHashTable hashTable(1000); // Choose an appropriate table size

    // Alternatively, create a LinearProbeHashTable instance
    // LinearProbeHashTable hashTable(1000);

    // Insert movie entries from a file
    hashTable.insertFromFile("./input/Movies.csv");

    // Test cases to check if specific movies are in the hash table
    MovieEntry* result1 = hashTable.search("The Shawshank Redemption");
    if (result1 != nullptr) {
        std::cout << "Found movie: " << result1->Name << std::endl;
    } else {
        std::cout << "Movie 'The Shawshank Redemption' not found." << std::endl;
    }

    MovieEntry* result2 = hashTable.search("The Godfather");
    if (result2 != nullptr) {
        std::cout << "Found movie: " << result2->Name << std::endl;
    } else {
        std::cout << "Movie 'The Godfather' not found." << std::endl;
    }

    MovieEntry* result3 = hashTable.search("Inception");
    if (result3 != nullptr) {
        std::cout << "Found movie: " << result3->Name << std::endl;
    } else {
        std::cout << "Movie 'Inception' not found." << std::endl;
    }

    MovieEntry* result4 = hashTable.search("The Dark Knight");
    if (result4 != nullptr) {
        std::cout << "Found movie: " << result4->Name << std::endl;
    } else {
        std::cout << "Movie 'The Dark Knight' not found." << std::endl;
    }


    // Test case to check if a movie not in the hash table is found
    MovieEntry* result5 = hashTable.search("The Love Story");
    if (result5 != nullptr) {
        std::cout << "Found movie: " << result5->Name << std::endl;
    } else {
        std::cout << "Movie 'The Love Story' not found." << std::endl;
    }

    // Test case to check for spelling mistakes
    MovieEntry* result6 = hashTable.search("The Shawshank Redemtion"); // Misspelled
    if (result6 != nullptr) {
        std::cout << "Found movie: " << result6->Name << std::endl;
    } else {
        std::cout << "Movie 'The Shawshank Redemtion' not found." << std::endl;
    }

    MovieEntry* result7 = hashTable.search("GoodFellas");
    if (result7 != nullptr) {
        std::cout << "Found movie: " << result7->Name << std::endl;
    } else {
        std::cout << "Movie 'GoodFellas' not found." << std::endl;
    }

    return 0;
}