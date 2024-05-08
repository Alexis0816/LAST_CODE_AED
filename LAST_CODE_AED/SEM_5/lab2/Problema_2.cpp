#include <iostream>
using namespace std;

class HashTable {
private:
    static const int length = 100; 
    struct Node {
        string key;
        int value;
        Node* next;
        Node(const string& k, int v) : key(k), value(v), next(nullptr) {}
    };
    Node* table[length]; 
    int hash(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue = hashValue * 31 + (c - '0');
        }
        return hashValue % length;
    }
public:
    HashTable() {
        for (int i = 0; i < length; ++i) {
            table[i] = nullptr;
        }
    }

    // Insertar un valor en la tabla hash
    void insert(const string& key, int value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Buscar un valor en la tabla hash
    int find(const string& key) {
        int index = hash(key);
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == key) {
                return temp->value;
            }
            temp = temp->next;
        }
        return -1;
    }
};

class Solution {
public:
    int numOfPairs(string nums[], int numslength, string target) {
        HashTable hashTable;
        int count = 0;

        // Llenar la tabla hash con nums
        for (int i = 0; i < numslength; ++i) {
            hashTable.insert(nums[i], i);
        }

        // Verificar pares válidos
        for (int i = 0; i < numslength; ++i) {
            for (int j = 0; j < numslength; ++j) {
                if (i != j) {
                    string concat = nums[i] + nums[j];
                    if (concat == target) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};

int main() {
    Solution sol;

    // Ejemplo 1
    string nums1[] = {"777", "7", "77", "77"};
    string target1 = "7777";
    cout << "Ejemplo 1: " << sol.numOfPairs(nums1, 4, target1) << endl;

    // Ejemplo 2
    string nums2[] = {"123", "4", "12", "34"};
    string target2 = "1234";
    cout << "Ejemplo 2: " << sol.numOfPairs(nums2, 4, target2) << endl;

    // Ejemplo 3
    string nums3[] = {"1", "1", "1"};
    string target3 = "11";
    cout << "Ejemplo 3: " << sol.numOfPairs(nums3, 3, target3) << endl;

    return 0;
}
