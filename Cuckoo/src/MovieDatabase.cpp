#include "MovieDatabase.hpp" // Assuming you'll define this header file

void MovieDatabase::LoadMoviesFromCsv(const string &csv_file)
{
    ifstream file(csv_file);
    if (!file.is_open())
    {
        cerr << "Error opening file " << csv_file << endl;
        return;
    }
    string line;

    getline(file, line); // Skip header
    while (getline(file, line))
    {
        stringstream ss(line);
        MovieEntry entry;
        getline(ss, entry.Name, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.RatingCount;
        ss.ignore();
        getline(ss, entry.ReleaseDate, ',');
        getline(ss, entry.Budget, ',');
        getline(ss, entry.DomesticGross, ',');
        getline(ss, entry.DomesticGross2, ',');
        getline(ss, entry.DomesticWeekendGross, ',');
        getline(ss, entry.DomesticWeekend, ',');
        getline(ss, entry.DomesticWeekendDate, ',');
        getline(ss, entry.WorldwideGross);

        entries.push_back(entry);
    }
    file.close();
}

void MovieDatabase::PrintMovieEntries()
{
    for (const auto &entry : entries)
    {
        cout << "Name: " << entry.Name << "\n";
        cout << "Rating: " << entry.Rating << "\n";
        cout << "Rating Count: " << entry.RatingCount << "\n";
        cout << "Release Date: " << entry.ReleaseDate << "\n";
        cout << "Budget: " << entry.Budget << "\n";
        cout << "Domestic Gross: " << entry.DomesticGross << "\n";
        cout << "Domestic Gross 2: " << entry.DomesticGross2 << "\n";
        cout << "Domestic Weekend Gross: " << entry.DomesticWeekendGross << "\n";
        cout << "Domestic Weekend: " << entry.DomesticWeekend << "\n";
        cout << "Domestic Weekend Date: " << entry.DomesticWeekendDate << "\n";
        cout << "Worldwide Gross: " << entry.WorldwideGross << "\n\n";
    }
}

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
        getline(ss, entry.Name, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.RatingCount;
        ss.ignore();
        getline(ss, entry.ReleaseDate, ',');
        getline(ss, entry.Budget, ',');
        getline(ss, entry.DomesticGross, ',');
        getline(ss, entry.DomesticGross2, ',');
        getline(ss, entry.DomesticWeekendGross, ',');
        getline(ss, entry.DomesticWeekend, ',');
        getline(ss, entry.DomesticWeekendDate, ',');
        getline(ss, entry.WorldwideGross);


        cout << "Name: " << entry.Name << "\n";

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



// -- Code for linear probing -- // 
LinearProbeHashTable::LinearProbeHashTable(int table_size) : size(0), capacity(table_size) {
    table.resize(capacity);
}

size_t LinearProbeHashTable::hashFunction(const string& key) {
    // Simple hash function based on the sum of ASCII values of characters in the key
    size_t hashValue = 0;
    for (char c : key) {
        hashValue += c;
    }
    return hashValue % capacity;
}

void LinearProbeHashTable::insertFromFile(const std::string& filename) {
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
        stringstream ss(line);
        MovieEntry entry;
        getline(ss, entry.Name, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.RatingCount;
        ss.ignore();
        getline(ss, entry.ReleaseDate, ',');
        getline(ss, entry.Budget, ',');
        getline(ss, entry.DomesticGross, ',');
        getline(ss, entry.DomesticGross2, ',');
        getline(ss, entry.DomesticWeekendGross, ',');
        getline(ss, entry.DomesticWeekend, ',');
        getline(ss, entry.DomesticWeekendDate, ',');
        getline(ss, entry.WorldwideGross);

        cout << "Name: " << entry.Name << "\n";

        // Calculate hash value for the movie name
        size_t index = hashFunction(entry.Name);

        // Linear probing to find an empty slot
        while (!table[index].Name.empty()) {
            index = (index + 1) % capacity;
        }

        // Insert the entry at the found index
        table[index] = entry;
        size++;
    }

    // Close the file
    file.close();
}


MovieEntry* LinearProbeHashTable::search(const string& key) {
    size_t index = hashFunction(key);
    int originalIndex = index;
    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            return &table[index];
        }
        index = (index + 1) % capacity;
        // If we've looped back to the original index, the key is not present
        if (index == originalIndex) {
            break;
        }
    }
    return nullptr; // Key not found
}

