#include "QuadraticProbeHashTable.hpp"

// Constructor
QuadraticProbeHashTable::QuadraticProbeHashTable(int table_size) : size(0), capacity(table_size) {
    table.resize(capacity);
}

size_t QuadraticProbeHashTable::hashFunction(const string& key) {
    // Using std::hash
    size_t hashValue = std::hash<std::string>{}(key);

    // Modulus to make sure it is within bounds
    return hashValue % capacity;
}

void QuadraticProbeHashTable::insertFromFile(const std::string& filename) {
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

void QuadraticProbeHashTable::insert(const MovieEntry2& entry) {
    // Calculating hash value for the movie name
    size_t index = hashFunction(entry.Name);

    // Quadratic probing to find an empty slot
    int i = 1;
    while (!table[index].Name.empty() and table[index].Name != "tombstone") {
        index = (index + i * i) % capacity;
        i++;
    }

    // Inserting the entry at the found index
    table[index] = entry;
    size++;
}

MovieEntry2* QuadraticProbeHashTable::search(const string& key) {
    // Calculating hash value for the key
    size_t index = hashFunction(key);

    // Original index to check if we have looped back
    int originalIndex = index;

    int i = 1;
    while (!table[index].Name.empty()) {

        if (table[index].Name == key) {
            return &table[index];
        }

        // Quadratic probing
        index = (index + i * i) % capacity;
        i++;

        // If we've looped back to the original index, the key is not present
        if (index == originalIndex) {
            break;
        }
    }

    // If key is not found
    return nullptr;
}

void QuadraticProbeHashTable::deleteEntry(const std::string& key) {
    // Calculate hash value for the key
    size_t index = hashFunction(key);

    // Original index to check if we have looped back
    int originalIndex = index;
    
    // Quadratic probing to find the entry with the given key
    int i = 1;
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
