#include "LinearProbeHashTable.hpp"

// Constructor
LinearProbeHashTable::LinearProbeHashTable(int table_size) : size(0), capacity(table_size) {
    table.resize(capacity);    // using vector resize() function
}

size_t LinearProbeHashTable::hashFunction(const string& key) {
    // Using std::hash
    size_t hashValue = std::hash<std::string>{}(key);

    // Modulus to make sure it is within bounds
    return hashValue % capacity;
}

void LinearProbeHashTable::insertFromFile(const std::string& filename) {
    // Opening the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Skipping header
    std::string header;
    std::getline(file, header);
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        MovieEntry2 entry;

        // Parse movie data from the line, using commas as separators
        std::getline(ss, entry.ID, ',');
        std::getline(ss, entry.Name, ',');
        std::getline(ss, entry.Year, ',');
        std::getline(ss, entry.Timing, ',');
        std::getline(ss, entry.Rating, ',');
        
        // Checking if Votes is enclosed within double quotes
        if (ss.peek() == '"') {
            ss.ignore();                        // Ignore the opening double quote
            std::getline(ss, entry.Votes, '"'); 
            ss.ignore();                        // After extracting the Votes, ignore the comma
        } else {
            std::getline(ss, entry.Votes, ',');
        }

        // Check if Genre is enclosed within double quotes
        if (ss.peek() == '"') {
            ss.ignore();                        // Ignore the opening double quote
            std::getline(ss, entry.Genre, '"');
            ss.ignore();                        // After extracting the Genre, ignore the comma
        } else {
            std::getline(ss, entry.Genre, ',');
        }

        std::getline(ss, entry.Language);

        // std::cout << entry.Name << std::endl;

        // Inserting the entry into the hash table
        insert(entry);

    }

    file.close();
}


void LinearProbeHashTable::insert(const MovieEntry2& entry) {
    // Calculating hash value for the movie name
    size_t index = hashFunction(entry.Name);

    // Linear probing to find an empty slot
    while (!table[index].Name.empty() and table[index].Name != "tombstone") {
        index = (index + 1) % capacity;
    }

    // Inserting the entry at the found index
    table[index] = entry;
    size++;
}

MovieEntry2* LinearProbeHashTable::search(const string& key) {
    // Calculating hash value for the key
    size_t index = hashFunction(key);

    // Original index to check if we have looped back
    int originalIndex = index;

    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            return &table[index];
        }

        // Linear probing
        index = (index + 1) % capacity;

        // If we've looped back to the original index, the key is not present
        if (index == originalIndex) {
            break;
        }
    }

    // If key is not found
    return nullptr; 
}

void LinearProbeHashTable::deleteEntry(const std::string& key) {
    // Calculate hash value for the key
    size_t index = hashFunction(key);

    // Original index to check if we have looped back
    int originalIndex = index;
    
    // Linear probing to find the entry with the given key
    while (!table[index].Name.empty()) {
        if (table[index].Name == key) {
            // Found the entry, mark it as deleted (Tombstone)
            table[index].Name = "tombstone";

            size--;
            return;
        }

        // Linear Probing
        index = (index + 1) % capacity;

        // If we've looped back to the original index, the key is not present
        if (index == originalIndex) {
            break;
        }
    }

    // If the loop ends without finding the entry, it's not present in the table
    std::cerr << "Entry with key '" << key << "' not found." << std::endl;
}
