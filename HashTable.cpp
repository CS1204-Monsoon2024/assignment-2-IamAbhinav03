#include <iostream>

class HashTable
{
    private:
        int tableSize;
        int *table;
        int numElements;
        float loadFactorthreshold;

        int nextPrime(int n) 
        {
            // A helper function to find the next prime number greater than n
            while (true) {
                n++;
                if (isPrime(n)) return n;
            }
        }

        bool isPrime(int n) 
        {
            if (n <= 1) return false;
            if (n == 2 || n == 3) return true;
            if (n % 2 == 0 || n % 3 == 0) return false;
            for (int i = 5; i * i <= n; i += 6) {
                if (n % i == 0 || n % (i + 2) == 0) return false;
            }
            return true;
        }

        int hash(int key)
        {
            return key % tableSize;
        }

        int quadraticProbe(int key, int i)
        {
            return (hash(key) + i*i) % tableSize;
        }

        void resize()
        {
            int *oldTable = table;
            int oldSize = tableSize;

            int newSize = nextPrime(2*oldSize);
            table = new int[newSize];
            tableSize = newSize;

            for (int i=0; i<newSize; i++)
            {
                table[i] = -1;
            }

            for (int i=0; i<oldSize; i++)
            {
                if (oldTable[i] != -1)
                {
                    insert(oldTable[i]);
                }
            }

            delete[] oldTable;
        }

    public:

        HashTable(int size) : tableSize(size), numElements(0), loadFactorthreshold(0.8)
        {
            tableSize = nextPrime(size);
            table = new int[tableSize];

            for (int i=0; i<tableSize; i++)
            {
                table[i] = -1;
            }
            
        }
        ~HashTable()
        {
            delete[] table;
        }

        void insert(int key)
        {
            if ((float)numElements / tableSize >= loadFactorthreshold) resize();

            int index = hash(key);


            if (table[index] == -1)
            {
                table[index] = key;
                numElements++;
            }
            else if (table[index] == key)
            {
                std::cout << "Duplicate key insertion is not allowed\n";
            }
            else
            {
                for (int i=1; i<=tableSize; i++)
                {
                    index = quadraticProbe(key, i);
                    if (table[index] == -1)
                    {
                        table[index] = key;
                        numElements++;
                        return;
                    }
                }
                std::cout << "Max probing limit reached!\n";
            }
        }

        void remove(int key)
        {
            int index = hash(key);


            if (table[index] == -1)
            {
                std::cout << "Element not found\n";
            }
            else if (table[index] == key)
            {
                table[index] = -1;
                numElements--;
            }
            else
            {
                for (int i=1; i<=tableSize; i++)
                {
                    index = quadraticProbe(key, i);
                    if (table[index] == key)
                    {
                        table[index] = -1;
                        numElements--;
                        return;
                    }
                }
                std::cout << "Element not found\n";
            }
            
        }

        int search(int key)
        {
            int index = hash(key);
            
            if (table[index] == -1)
            {
                return -1;
            }
            else if (table[index] == key)
            {
                return index;
            }
            else
            {

                for (int i=1; i<=tableSize; i++)
                {
                    index = quadraticProbe(key, i);
                    if (table[index] == key)
                    {
                        return index;
                    }
                }
                return -1;
            }
        }

        void printTable()
        {
            for (int i=0; i<tableSize; i++)
            {
                if (table[i] == -1)
                {
                    std::cout << "_ ";
                }
                else
                {
                    std::cout << table[i] << " ";
                }
            }
            std::cout << std::endl;
        }

};