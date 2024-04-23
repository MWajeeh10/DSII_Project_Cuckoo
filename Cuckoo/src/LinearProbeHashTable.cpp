#include "LinearProbeHashTable.hpp"

LinearProbeHashTable::LinearProbeHashTable(int table_size) : size(0), capacity(table_size) {
    table.resize(capacity);
}

size_t LinearProbeHashTable::hashFunction(const string& key) {
    size_t hashValue = std::hash<std::string>{}(key);

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
        std::stringstream ss(line);
        MovieEntry2 entry;

        // Parse movie data from the line
        std::getline(ss, entry.ID, ',');
        std::getline(ss, entry.Name, ',');
        std::getline(ss, entry.Year, ',');
        std::getline(ss, entry.Timing, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.Votes;
        ss.ignore();
        std::getline(ss, entry.Genre, ',');
        std::getline(ss, entry.Language);

        // std::cout << entry.Name << std::endl;

        // Insert the entry into the hash table
        insert(entry);
    }

    // Close the file
    file.close();
}


void LinearProbeHashTable::insert(const MovieEntry2& entry) {
    // Calculate hash value for the movie name
    size_t index = hashFunction(entry.Name);

    // Linear probing to find an empty slot
    while (!table[index].Name.empty() and table[index].Name != "tombstone") {
        index = (index + 1) % capacity;
        
    }

    // Insert the entry at the found index
    table[index] = entry;
    size++;
}

MovieEntry2* LinearProbeHashTable::search(const string& key) {
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

void LinearProbeHashTable::deleteEntry(const std::string& key) {
    // Calculate hash value for the key
    size_t index = hashFunction(key);

    // Linear probing to find the entry with the given key
    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            // Found the entry, mark it as deleted (Tombstone)
            table[index].Name = "tombstone";
            size--;
            return;
        }
        index = (index + 1) % capacity;
    }

    // If the loop ends without finding the entry, it's not present in the table
    std::cerr << "Entry with key '" << key << "' not found." << std::endl;
}
