#include "CuckooHashTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

// -- Code for Cuckoo hashing -- //
CuckooHashTable::CuckooHashTable(int table_size) : size(table_size) {
    table1.resize(size);
    table2.resize(size);
}


// These hash functions required a space of around 2 million entries for the hash table to work properly which is extremely inefficient
// and unreasonable. Hence, we will use the MurmurHash3 and FNV1a hash functions which are more efficient and provide a better distribution of hash values.

// size_t CuckooHashTable::hashFunction1(const string& key) {
//     // Simple hash function based on the sum of ASCII values of characters in the key
//     size_t hashValue = 0;
//     for (char c : key) {
//         hashValue += c;
//     }
//     return hashValue;
// }

// size_t CuckooHashTable::hashFunction2(const string& key) {
//     const size_t prime = 31; // Prime number for rolling hash 
//     size_t hash_value = 0;
//     size_t p_pow = 1;

//     for (char c : key) {
//         hash_value = (hash_value + (c - 'a' + 1) * p_pow) % size;
//         p_pow = (p_pow * prime) % size;
//     }

//     return hash_value;
// }

uint32_t MurmurHash3(const std::string& key) {
    uint32_t h = 0;
    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t r2 = 13;
    uint32_t m = 5;
    uint32_t n = 0xe6546b64;

    for (char c : key) {
        uint32_t k = c;
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));  // Rotate left
        k *= c2;

        h ^= k;
        h = (h << r2) | (h >> (32 - r2));  // Rotate left
        h = h * m + n;
    }

    h ^= key.size();
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}

uint32_t FNV1a(const std::string& key) {
    uint32_t h = 0x811c9dc5;  // FNV offset basis
    uint32_t prime = 0x01000193;  // FNV prime

    for (char c : key) {
        h ^= c;
        h *= prime;
    }

    return h;
}

size_t CuckooHashTable::hashFunction1(const string& key) {
    return MurmurHash3(key);
}

size_t CuckooHashTable::hashFunction2(const string& key) {
    return FNV1a(key);
}


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
        std::stringstream ss(line);
        MovieEntry2 entry;

        // Parse movie data from the line
        std::getline(ss, entry.ID, ',');
        std::getline(ss, entry.Name, ',');
        std::getline(ss, entry.Year, ',');
        std::getline(ss, entry.Timing, ',');
        std::getline(ss, entry.Rating, ',');
        
        // Check if Votes is enclosed within double quotes
        if (ss.peek() == '"') {
            ss.ignore(); // Ignore the opening double quote
            std::getline(ss, entry.Votes, '"');
            // After extracting the Votes, ignore the comma
            ss.ignore();
        } else {
            std::getline(ss, entry.Votes, ',');
        }

        // Check if Genre is enclosed within double quotes
        if (ss.peek() == '"') {
            ss.ignore(); // Ignore the opening double quote
            std::getline(ss, entry.Genre, '"');
            // After extracting the Genre, ignore the comma
            ss.ignore();
        } else {
            std::getline(ss, entry.Genre, ',');
        }

        std::getline(ss, entry.Language);

        // std::cout << entry.Name << std::endl;

        // Insert the entry into the hash table
        insert(entry);
        totalentries++;

    }

    // Close the file
    file.close();
}

MovieEntry2* CuckooHashTable::search(const string& key) {
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

void CuckooHashTable::insert(const MovieEntry2& entry) {
    // Calculate hash values for the movie name using both hash functions
    size_t hash1 = hashFunction1(entry.Name) % size;
    size_t hash2 = hashFunction2(entry.Name) % size;

    // Check if the slot at hash1 is empty
    if (table1[hash1].Name.empty()) {
        table1[hash1] = entry;
        return;
    }
    // Check if the slot at hash2 is empty
    if (table2[hash2].Name.empty()) {
        table2[hash2] = entry;
        return;
    }

    // If both slots are occupied, perform cuckoo hashing
    MovieEntry2 temp = entry;
    for (int i = 0; i < log(size); i++) {
        // Swap the entry with the slot at hash1 on even iterations
        if (i % 2 == 0) {
            std::swap(temp, table1[hash1]);
            hash1 = hashFunction1(temp.Name) % size;
            if (table1[hash1].Name.empty()) {
                table1[hash1] = temp;
                return;
            }
        }
        // Swap the entry with the slot at hash2
        else {
            std::swap(temp, table2[hash2]);
            hash2 = hashFunction2(temp.Name) % size;
            if (table2[hash2].Name.empty()) {
                table2[hash2] = temp;
                return;
            }
        }
    }

    // If the loop completes, the hash table is full
    if (totalentries > 0.75*size){
        std::cerr << "Resizing triggered." << entry.Name << "  Size:" << size << std::endl;
        resize();
    }
    insert(temp);
}

void CuckooHashTable::resize() {
  // Create a new table with a larger size
  int newSize = size * 2;
  vector<MovieEntry2> newTable1(newSize);
  vector<MovieEntry2> newTable2(newSize);

  // Rehash all the existing entries
  for (int i = 0; i < size; i++) {
    MovieEntry2 entry = table1[i];
    if (!entry.Name.empty()) {
      size_t hash1 = hashFunction1(entry.Name) % newSize;
      size_t hash2 = hashFunction2(entry.Name) % newSize;
      newTable1[hash1] = entry;
      newTable2[hash2] = entry;
    }
  }

  // Swap the new table with the old one
  table1 = std::move(newTable1); // using move semantics
  table2 = std::move(newTable2); // Transfer ownership of the data from newTable to table
  size = newSize;
}