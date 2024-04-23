#include <string>

class HashTable {
public:
    virtual ~HashTable() {}

    // Insert a key into the hash table
    virtual bool insert(const std::string& key) = 0;

    // Delete a key from the hash table
    virtual bool remove(const std::string& key) = 0;

    // Search for a key in the hash table
    virtual bool search(const std::string& key) const = 0;

    // Get the space complexity of the hash table
    virtual int getSpaceComplexity() const = 0;

    // Insert keys from a file into the hash table
    virtual void insertFromFile(const std::string& filename) = 0;

    // Search for keys from a file in the hash table
    virtual void searchFromFile(const std::string& filename) = 0;

    // Delete keys from a file from the hash table
    virtual void deleteFromFile(const std::string& filename) = 0;
};