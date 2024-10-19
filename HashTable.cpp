#include <iostream>

class HashTable {
private:
    int* keys;
    int* values;
    int tableSize;
    int numElements;
    float loadFactorThreshold;
    int c1 = 1, c2 = 1;  // Constants for quadratic probing

    // Hash Function
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Quadratic Probing Function
    int quadraticProbe(int key, int i) {
        return (hashFunction(key) + c1 * i + c2 * i * i) % tableSize;
    }

    // Prime Checking Function
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Function to find the next prime number greater than n
    int nextPrime(int n) {
        if (n <= 1) return 2;
        int prime = n;
        bool found = false;

        // Loop continuously until isPrime returns true
        while (!found) {
            prime++;
            if (isPrime(prime)) {
                found = true;
            }
        }
        return prime;
    }

    // Resizes the hash table and rehashes all keys
    void resize() {
        int oldSize = tableSize;
        tableSize = nextPrime(2 * tableSize);  // Resize to the next prime after doubling
        int* oldKeys = keys;
        int* oldValues = values;

        // Allocate new arrays with the updated prime size
        keys = new int[tableSize];
        values = new int[tableSize];

        // Initialize the new arrays
        for (int i = 0; i < tableSize; i++) {
            keys[i] = -1;
            values[i] = -1;
        }

        numElements = 0;

        // Rehash all elements from the old table to the new table
        for (int i = 0; i < oldSize; i++) {
            if (oldKeys[i] != -1 && oldKeys[i] != -2) {
                insert(oldKeys[i], oldValues[i]);
            }
        }

        // Free the old arrays
        delete[] oldKeys;
        delete[] oldValues;
    }

public:
    // Constructor to initialize the hash table
    HashTable(int size = 7) : loadFactorThreshold(0.8), tableSize(size), numElements(0) {
        tableSize = nextPrime(size);  // Ensure the initial size is prime
        keys = new int[tableSize];
        values = new int[tableSize];

        // Initialize the arrays with -1 to denote empty slots
        for (int i = 0; i < tableSize; i++) {
            keys[i] = -1;  // -1 means the slot is empty
            values[i] = -1;
        }
    }

    // Destructor to free dynamically allocated arrays
    ~HashTable() {
        delete[] keys;
        delete[] values;
    }

    // to handle single keys
    void insert(int key)
    {
        insert(key, key);
    }

    // Insert Function with Quadratic Probing
    void insert(int key, int value) {
        // Check load factor and resize if necessary
        if ((float)numElements / tableSize >= loadFactorThreshold) {
            resize();
        }

        int index = hashFunction(key);

        // Linear probing to resolve collisions
        for (int i = 0; i < tableSize; i++) {
            int newIndex = quadraticProbe(key, i);

            if (keys[newIndex] == -1 || keys[newIndex] == -2) {  // Empty or deleted slot
                keys[newIndex] = key;
                values[newIndex] = value;
                numElements++;
                return;
            } else if (keys[newIndex] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
        }

        std::cout << "Max probing limit reached!\n";
    }

    // Search Function with Quadratic Probing
    int search(int key) {
        for (int i = 0; i < tableSize; i++) {
            int index = quadraticProbe(key, i);

            if (keys[index] == key) {
                return index;  // Found the key
            } else if (keys[index] == -1) {
                return -1;  // Not found, hit an empty slot
            }
        }

        return -1;  // Not found
    }

    // Delete Function
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            std::cout << "Element not found\n";
        } else {
            keys[index] = -2;  // Mark as deleted (-2 to indicate a deleted slot)
            values[index] = -1;
            numElements--;
        }
    }

    // Print Table Function
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (keys[i] >=0) std::cout << values[i] << " ";
            else std::cout << "- ";
        }
        std::cout << std::endl;
    }
};