#include "HashTable.cpp"

int main() {
    int initialSize = 17; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(13);
    ht.printTable();
    ht.insert(3);
    ht.printTable();
    ht.remove(3);
    ht.printTable(); 
    ht.insert(20);
    ht.printTable();
    ht.insert(4);
    ht.printTable();
    ht.insert(21);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at: " << find << std::endl;
    find = ht.search(4);
    std::cout << "Found at: " << find << std::endl;
    return 0;
}