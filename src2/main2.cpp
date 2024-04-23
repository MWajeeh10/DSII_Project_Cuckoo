#include <iostream>
#include <chrono>
#include "LinearProbeHashTable2.hpp"
#include "QuadraticProbeHashTable2.hpp"
#include "CuckooHashTable2.hpp"
#include "HashTable2.hpp"
#include <vector>
#include <string>

class Timer {
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() {
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};

int main() {
    std::vector<HashTable*> hashTables = {
        // new LinearProbeHashTable(250),
        // new QuadraticProbeHashTable(250),
        // new CuckooHashTable(250)
    };

    std::vector<std::string> csvFiles = {"./Cuckoo/input/Movies.csv", "./Cuckoo/input/netflix_titles.csv", "./Cuckoo/input/cleaned_indian_movies.csv"};

    Timer timer;

    int mode = 0;
    for (auto& csvFile : csvFiles) {
        for (auto& hashTable : hashTables) {
            timer.start();
            hashTable->insertFromFile(csvFile);
            timer.stop();
            std::cout << "Insertion time for " << csvFile << ": " << timer.elapsed() << " ms" << std::endl;

            timer.start();
            hashTable->searchFromFile(csvFile);
            timer.stop();
            std::cout << "Search time for " << csvFile << ": " << timer.elapsed() << " ms" << std::endl;

            timer.start();
            hashTable->deleteFromFile(csvFile);
            timer.stop();
            std::cout << "Deletion time for " << csvFile << ": " << timer.elapsed() << " ms" << std::endl;

            std::cout << "Space complexity for " << csvFile << ": " << hashTable->getSpaceComplexity() << std::endl;
        }
        mode++;
    }

    return 0;
}