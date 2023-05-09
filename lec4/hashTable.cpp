#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class HashTable {
private:
    static const int hashGroups = 10;
    list<pair<int, string>> table[hashGroups]; // List 1, Index 0, List 2, Index 1...
public:
    bool isEmpty() const;
    int hashFunction(int key);
    void insertItem(int key, string value);
    void removeItem(int key);
    void searchTable(int key);
    void printTable();
};

bool HashTable::isEmpty() const {
    int sum{};
    for (int i{}; i < hashGroups; i++) {
        sum += table[i].size();
    }
    if (!sum) {
        return true;
    }
    return false;
}

int HashTable::hashFunction(int key) {
    return key % hashGroups; // Key: 101, in return, this function will return 1
}

void HashTable::insertItem(int key, string value) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr->second = value;
            cout << "[WARNING] Key exists. Value replaced" << endl;
            break;
        }
    }
    if (!keyExists) {
        cell.emplace_back(key, value);
    }
    return;
}

void HashTable::removeItem(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            bItr = cell.erase(bItr);
            cout << "[INFO] Item removed." << endl;
            break;
        }
    }
    if (!keyExists) {
        cout << "[WARNING] Key not found. Pair not removed." << endl;
    }
    return;
}

void HashTable::searchTable(int key) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];
    auto bItr = begin(cell);
    bool keyExists = false;
    for (; bItr != end(cell); bItr++) {
        if (bItr->first == key) {
            keyExists = true;
            cout << "[INFO] Item found." << " Key: " << bItr->first << " Value: " << bItr->second << endl;
            break;
        }
    }
    if (!keyExists) {
        cout << "[WARNING] Key not found. Pair not found." << endl;
    }
    return;
}

void HashTable::printTable() {
    for (int i{}; i < hashGroups; i++) {
        if (table[i].size() == 0) continue;
        auto bItr = table[i].begin();
        for (; bItr != table[i].end(); bItr++) {
            cout << "[INFO] Key: " << bItr->first << " Value: " << bItr->second << endl;
        }
    }
    return;
}

int main() {
    HashTable HT;
    if (HT.isEmpty()) {
        cout << "Correct answer. Good job." << endl;
    } else {
        cout << "Oh oh. We need to check out code!" << endl;
    }
    HT.insertItem(109, "Jim");
    HT.insertItem(108, "Jack");
    HT.insertItem(332, "Bob");
    HT.insertItem(421, "Sally");
    HT.insertItem(954, "Sandy");
    HT.insertItem(632, "Barb");
    HT.insertItem(288, "Rob");
    HT.insertItem(288, "Rick");

    HT.printTable();
    cout << "------------------------------------" << endl;
    HT.removeItem(332);
    HT.removeItem(100);
    cout << "------------------------------------" << endl;

    if (HT.isEmpty()) {
        cout << "Oh oh. We need to check out code!" << endl;
    } else {
        cout << "Correct answer! Good job! " << endl;
    }
    cout << "------------------------------------" << endl;

    HT.searchTable(109);
    return 0;
}