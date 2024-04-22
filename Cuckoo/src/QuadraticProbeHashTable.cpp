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

        // Calculate hash value for the movie name
        size_t index = hashFunction(entry.Name);

        // Quadratic Probing
        int i = 1;
        while (!table[index].Name.empty()) {
            index = (index + i * i) % capacity;
            i++;
        }

        table[index] = entry;
        size++;

    }

    // Close the file
    file.close();
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
