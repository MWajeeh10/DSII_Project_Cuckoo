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

    }

    // Close the file
    file.close();
}

void QuadraticProbeHashTable::insert(const MovieEntry2& entry) {
    // Calculate hash value for the movie name
    size_t index = hashFunction(entry.Name);

    // Quadratic probing to find an empty slot
    int i = 1;
    while (!table[index].Name.empty() and table[index].Name != "tombstone") {
        index = (index + i * i) % capacity;
        i++;
    }

    // Insert the entry at the found index
    table[index] = entry;
    size++;
}

MovieEntry2* QuadraticProbeHashTable::search(const string& key) {
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
