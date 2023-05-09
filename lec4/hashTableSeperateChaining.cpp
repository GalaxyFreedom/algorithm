#include <cstring>
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Hash {
private:
    // number of buckets
    int m_bucket;

    // Pointer to an array containing buckets
    list<int> *table;
public:
    // constructor
    Hash(int b) {
        this->m_bucket = b;
        table = new list<int> [m_bucket];
    }

    // string to int
    int strToInt(const string& str) {
        int result = 0;
        for (char c : str) {
            result += c;
        }
        return result;
    }

    // hash function to map values to keys
    int hashFunction(int key) {
        return (key % m_bucket);
    }

    // inserts a key into the hash table
    void insertItemChaining(string key) {
        int intKey = strToInt(key);
        int index = hashFunction(intKey);
        table[index].push_back(intKey);
    }


    // deletes a key from the hash table
    void removeItem(string key) {
        // change string key to int key
        int intKey = strToInt(key);

        // get the hash index of key
        int index = hashFunction(intKey);

        // find the key in (index)th list
        list<int>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); it++) {
            if (*it == intKey) {
                break;
            }
            else {
                cout << "[WARNING] Key \"" << key << "\" was not found! Cannot remove. " << endl;
            }
        }

        // if key is found in hash table, remove it
        if (it != table[index].end()) {
            table[index].erase(it);
        }
    }

    // display the hash table
    void displayHash() {
        for (int i = 0; i < m_bucket; i++) {
            cout << i;
            for (int x : table[i]) {
                cout << " --> " << x;
            }
            cout << endl;
        }
    }

    void searchItem(string key) {
        int intKey = strToInt(key);

    }
};

int main() {
    string a[] = {"Anna", "Alice", "Bob", "Chris", "David", "Elvis", "Greg"};
    int n = sizeof(a)/sizeof(a[0]);

    Hash hash(17);


    for (int i = 0; i < n; i++) {
        hash.insertItemChaining(a[i]);
    }

    hash.displayHash();
    cout << "----------------------------------" << endl;

/*
    Hash hash2(17);

    for (int i = 0; i < n; i++) {
        hash2.insertItemLinearProbing(a[i]);
    }
*/


    hash.removeItem("David");
    hash.displayHash();
    cout << "----------------------------------" << endl;

    return 0;
}