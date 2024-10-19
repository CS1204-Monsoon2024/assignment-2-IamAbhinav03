#include <iostream>

const int MAX_PROBING_ATTEMPTS = 10; // Max attempts for quadratic probing

// change to euler's algorithm
bool isPrime(int n)
{
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i=5; i*i<=n; i+=6)
    {
        if (n%i == 0 || n % (i+2) == 0) return false;
    }
    return true;
};

int nextPrime(int n) 
{
    while (!isPrime(n)) n++;
    return n;
};

class HashTable
{
    private:
        int *keys;
        int *values;
        int tableSize;
        int numElements;
        float loadFactorThreshold = 0.8;

        // Hash function: h(x) = k mod m
        int hashFunction(int key)
        {
            return key % tableSize;
        }

        // Resize the table when the loa factor exceeds the threshold.
        void resizeTable()
        {   
        
            int newSize = nextPrime(tableSize * 2);

            int *oldKeys = keys;
            int *oldValues = values;

            // Alocate new arrays
            keys = new int[newSize];
            values = new int[newSize];

            // Initialize the new arrays with -1 to signify empty slots
            for (int i=0; i<newSize; i++)
            {
                keys[i] = -1;
                values[i] = -1;
            }

            int oldSize = tableSize;
            tableSize = newSize;
            numElements = 0;

            // Rehash all old keys into the new table
            for (int i=0; i<oldSize; i++)
            {
                if (oldKeys[i] != -1) insert(oldKeys[i], oldValues[i]);
            }

            // Free the old arrays
            delete[] oldKeys;
            delete[] oldValues;
        }

    void checkLoadFactorAndResize()
    {
        float loadFactor = static_cast<float>(numElements) / tableSize;

        if (loadFactor > loadFactorThreshold) resizeTable();
    }
    public:
        // Constructor
        HashTable(int size=11) : tableSize(nextPrime(size)), numElements(0)
        {
            keys = new int[tableSize];
            values = new int[tableSize];
            for (int i=0; i<tableSize; i++)
            {
                keys[i] = -1;
                values[i] = -1;
            }
        }

        // Deconstructor to release memory
        ~HashTable()
        {
            delete[] keys;
            delete[] values;
        }

        void insert(int key, int value) 
        {
            int index = hashFunction(key);
            int i = 0;

            // Check for duplicate key
            while (keys[(index + i * i) % tableSize] != -1 && i < MAX_PROBING_ATTEMPTS) {
                if (keys[(index + i * i) % tableSize] == key) {
                    std::cout << "Duplicate key insertion is not allowed" << std::endl;
                    return;
                }
                i++;
            }

            // Check if probing exceeds the maximum limit
            if (i >= MAX_PROBING_ATTEMPTS) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }

            index = (index + i * i) % tableSize;

            if (keys[index] == -1) {
                numElements++;  // New key, so increment the element count
            }

            keys[index] = key;
            values[index] = value;

            checkLoadFactorAndResize();
        }

    int search(int key)
    {
        int index = hashFunction(key);
        int i = 0;

        // quadractic probing to find the key
        while (keys[(index + i*i) % tableSize] != -1)
        {
            if (keys[(index + i*i) % tableSize] == key) return (index + i*i) % tableSize;

            i++;
        }
        return -1; // key not found
    }

    void remove(int key) 
    {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find the key
        while (keys[(index + i * i) % tableSize] != -1 && i < MAX_PROBING_ATTEMPTS) {
            if (keys[(index + i * i) % tableSize] == key) {
                keys[(index + i * i) % tableSize] = -1;    // Mark as deleted
                values[(index + i * i) % tableSize] = -1;  // Mark value as deleted
                numElements--;
                return;
            }
            i++;
        }
        std::cout << "Element not found" << std::endl;
    }

    void printTable() 
    {
        for (int i = 0; i < tableSize; i++) {
            if (keys[i] != -1) std::cout << values[i] << " ";
            else std::cout << "- ";
        }
        std::cout << std::endl;  // Add space at the end
    }

};

int main() {
//     HashTable ht(5);

//     ht.printTable();    // Should print: "- - - - - "
//     ht.insert(1, 1);
//     ht.printTable();    // Should print: "- 1 - - - "
//     ht.insert(4, 4);
//     ht.printTable();    // Should print: "- 1 - 4 - "

//     ht.remove(5);       // Should print: "Element not found"
//     ht.insert(1, 100);  // Should print: "Duplicate key insertion is not allowed"

//     ht.insert(0, 2);
//     ht.printTable();    // Should print: "2 1 - 4 - "
    
    return 0;
}