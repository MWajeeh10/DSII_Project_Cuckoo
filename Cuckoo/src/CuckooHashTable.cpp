#include "CuckooHashTable.hpp"

// -- Code for Cuckoo hashing -- //
CuckooHashTable::CuckooHashTable(int table_size) : size(table_size) {
    table1.resize(size);
    table2.resize(size);
}

size_t CuckooHashTable::hashFunction1(const string& key) {
    // Simple hash function based on the sum of ASCII values of characters in the key
    size_t hashValue = 0;
    for (char c : key) {
        hashValue += c;
    }
    return hashValue;
}

size_t CuckooHashTable::hashFunction2(const string& key) {
    // Another simple hash function based on the length of the key
    return key.length();
}

// void CuckooHashTable::insert(const MovieEntry& entry) {
//     // Calculate hash values for the movie name using both hash functions
//     size_t hash1 = hashFunction1(entry.Name) % size;
//     size_t hash2 = hashFunction2(entry.Name) % size;

//     // Check if the slots at hash1 and hash2 are available
//     if (table1[hash1].Name.empty()) {
//         table1[hash1] = entry;
//     } else if (table2[hash2].Name.empty()) {
//         table2[hash2] = entry;
//     } else {
//         // If both slots are occupied, perform cuckoo hashing
//         MovieEntry displacedEntry = entry;
//         for (int i = 0; i < size; ++i) {
//             // Swap displacedEntry with the entry at hash1
//             swap(displacedEntry, table1[hash1]);
//             // Recalculate hash value for displacedEntry
//             hash1 = hashFunction1(displacedEntry.Name) % size;
//             // Check if slot at hash1 is available
//             if (table1[hash1].Name.empty()) {
//                 table1[hash1] = displacedEntry;
//                 return;
//             }
//             // Swap displacedEntry with the entry at hash2
//             swap(displacedEntry, table2[hash2]);
//             // Recalculate hash value for displacedEntry
//             hash2 = hashFunction2(displacedEntry.Name) % size;
//             // Check if slot at hash2 is available
//             if (table2[hash2].Name.empty()) {
//                 table2[hash2] = displacedEntry;
//                 return;
//             }
//         }
//         // If the loop ends without finding an empty slot, rehash the table and try again
//         // (This part is omitted for simplicity)
//     }
// }

#include <fstream>

void CuckooHashTable::insertFromFile(const std::string& filename) {
    // Open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // skip header
    std::string header;
    std::getline(file, header);
    
    std::string line;
    while (std::getline(file, line)) {
        // Parse each line to create a MovieEntry
        // MovieEntry entry = {line};

        stringstream ss(line);
        MovieEntry entry;
        std::getline(ss, entry.Name, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.RatingCount;
        ss.ignore();
        std::getline(ss, entry.ReleaseDate, ',');
        std::getline(ss, entry.Budget, ',');
        std::getline(ss, entry.DomesticGross, ',');
        std::getline(ss, entry.DomesticGross2, ',');
        std::getline(ss, entry.DomesticWeekendGross, ',');
        std::getline(ss, entry.DomesticWeekend, ',');
        std::getline(ss, entry.DomesticWeekendDate, ',');
        std::getline(ss, entry.WorldwideGross);


        std::cout << "Name: " << entry.Name << "\n";

        // Calculate hash values for the movie name using both hash functions
        size_t hash1 = hashFunction1(entry.Name) % size;
        size_t hash2 = hashFunction2(entry.Name) % size;

        // Check if the slots at hash1 and hash2 are available
        if (table1[hash1].Name.empty()) {
            table1[hash1] = entry;
        } else if (table2[hash2].Name.empty()) {
            table2[hash2] = entry;
        } else {
            // If both slots are occupied, perform cuckoo hashing
            MovieEntry displacedEntry = entry;
            for (int i = 0; i < size; ++i) {
                // Swap displacedEntry with the entry at hash1
                swap(displacedEntry, table1[hash1]);
                // Recalculate hash value for displacedEntry
                hash1 = hashFunction1(displacedEntry.Name) % size;
                // Check if slot at hash1 is available
                if (table1[hash1].Name.empty()) {
                    table1[hash1] = displacedEntry;
                    break;
                }
                // Swap displacedEntry with the entry at hash2
                swap(displacedEntry, table2[hash2]);
                // Recalculate hash value for displacedEntry
                hash2 = hashFunction2(displacedEntry.Name) % size;
                // Check if slot at hash2 is available
                if (table2[hash2].Name.empty()) {
                    table2[hash2] = displacedEntry;
                    break;
                }
            }
            // If the loop ends without finding an empty slot, rehash the table and try again
            // (This part is omitted for simplicity)
        }
    }

    // Close the file
    file.close();
}

MovieEntry* CuckooHashTable::search(const string& key) {
    // Calculate hash values for the movie name using both hash functions
    size_t hash1 = hashFunction1(key) % size;
    size_t hash2 = hashFunction2(key) % size;

    // Check if the movie is stored at hash1
    if (table1[hash1].Name == key) {
        return &table1[hash1];
    }
    // Check if the movie is stored at hash2
    if (table2[hash2].Name == key) {
        return &table2[hash2];
    }
    // Movie not found
    return nullptr;
}