#include "QuadraticProbeHashTable.hpp"

QuadraticProbeHashTable::QuadraticProbeHashTable(int table_size) : size(0), capacity(table_size) {
    table.resize(capacity);
}

size_t QuadraticProbeHashTable::hashFunction(const string& key) {
    size_t hashValue = 0;
    for (char c : key) {
        hashValue += c;
    }
    return hashValue % capacity;
}

void QuadraticProbeHashTable::insertFromFile(const std::string& filename) {
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

        // Insert the entry into the hash table
        insert(entry);
    }

    // Close the file
    file.close();
}

void QuadraticProbeHashTable::insert(const MovieEntry& entry) {
    // Calculate hash value for the movie name
    size_t index = hashFunction(entry.Name);

    // Quadratic probing to find an empty slot
    int i = 1;
    while (!table[index].Name.empty() or table[index].Name != "tombstone") {
        index = (index + i * i) % capacity;
        i++;
    }

    // Insert the entry at the found index
    table[index] = entry;
    size++;
}

MovieEntry* QuadraticProbeHashTable::search(const string& key) {
    size_t index = hashFunction(key);
    int originalIndex = index;
    int i = 1;
    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            return &table[index];
        }
        index = (index + i * i) % capacity;
        i++;
        if (index == originalIndex) {
            break;
        }
    }
    return nullptr;
}

void QuadraticProbeHashTable::deleteEntry(const std::string& key) {
    // Calculate hash value for the key
    size_t index = hashFunction(key);
    int originalIndex = index;
    int i = 1;

    // Quadratic probing to find the entry with the given key
    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            // Found the entry, mark it as deleted (Tombstone)
            table[index].Name = "tombstone";
            size--;
            return;
        }

        index = (originalIndex + i * i) % capacity;
        i++;

        // If we've looped back to the original index, the key is not present
        if (index == originalIndex) {
            break;
        }
    }

    // If the loop ends without finding the entry, it's not present in the table
    std::cerr << "Entry with key '" << key << "' not found." << std::endl;
}
