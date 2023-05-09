#include <iostream>
#include <string>
#include <array>
using namespace std;

//How hash table linear probing works
/*
Linear probing is a collision resolution technique for searching the location of an element in a hash table.
When inserting keys, collisions are mitigated by scanning the cells in the table sequentially. Once an available cell is found,
the key is inserted. Similarly, to find an element in a hash table, cells are scanned linearly until the key is found or all positions have been scanned
*/
#define TABLE_SIZE 11

class HashTable {
private:
    array<string, TABLE_SIZE> table;
    int currentSize;

    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

public:
    HashTable() : currentSize(0) {}

    void insert(string key) {
        if (currentSize == TABLE_SIZE) {
            cerr << "Hash table is full" << std::endl;
            return;
        }

        int index = hashFunction(key);
        while (!table[index].empty()) {
            index = (index + 1) % TABLE_SIZE;
        }
        table[index] = key;
        currentSize++;
    }

    bool search(string key) {
        int index = hashFunction(key);
        int startIndex = index;
        while (!table[index].empty()) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                break;
            }
        }
        return false;
    }

    void remove(string key) {
        int index = hashFunction(key);
        int startIndex = index;
        while (!table[index].empty()) {
            if (table[index] == key) {
                table[index].clear();
                currentSize--;
                break;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                break;
            }
        }
    }
    void print() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << ": " << table[i] << endl;
        }
    }
};

int main() {
    HashTable ht;
    ht.insert("Alice");
    ht.insert("Bob");
    ht.insert("Charlie");
    ht.print();
    cout << "---------------------------" << endl;
    cout << ht.search("Bob") << endl; // 1
    cout << "---------------------------" << endl;
    ht.remove("Bob");
    ht.print();
    cout << "---------------------------" << endl;
    cout << ht.search("Bob") << endl; // 0
}
