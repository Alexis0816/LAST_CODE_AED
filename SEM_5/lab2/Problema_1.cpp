#include <iostream>
#include <vector>
#include <forward_list>
#include <string>
#include <algorithm>

using namespace std;

template <class TK, class TV>
class HashTable {
private:
    struct Entry {
        TK key;
        TV value;
    };

    using ht = forward_list<Entry>;
    ht *hashTable;

    int capacity; // tamaño del array
    double size;  // cantidad de elementos incluyendo colisionados

public:
    HashTable() : capacity(8), size(0){
        hashTable = new ht[capacity];
    }   

    HashTable(int _cap) : capacity(_cap), size(0){
        hashTable = new ht[capacity];
    }

    void insert(TK key){
        Entry entry;
        entry.key = key;
        int index = hashCode(key);

        auto it0 = begin(hashTable[index]);
        
        bool found = false;
        // actualiza valor
        while (it0 != end(hashTable[index])){
            if ((*it0).key == key){
                (*it0).value++; // aumenta el valor de repeticiones si la clave es la misma
                found = true;
                break; 
            }
            ++it0;
        }
        
        // si no encuentra la clave la agrega e inicializa en 1 sus repeticiones
        if(!found){
            entry.value = 1;
            hashTable[index].push_front(entry);
            size+=1;
        }
    }

    int _size(){
        return size;
    }

    vector<TV> values() {
        vector<TV> result;
        for (int i = 0; i < capacity; ++i) {
            auto it0 = begin(hashTable[i]);
            while (it0 != end(hashTable[i])) {
            result.push_back((*it0).value);
            ++it0;
            }
        }
        return result;
    }

private:
    size_t hashCode(TK key){
        hash<TK> ptr_hash;
        return ptr_hash(key) % capacity;
    }
};

class Solution{
private:
    HashTable<char,int> hash;
public:
    Solution() = default;
    Solution(int _cap): hash({_cap}) {};

    bool areOccurrencesEqual(string s){
        for (auto x : s){
            hash.insert(tolower(x));
        }

        vector<int> repeat = hash.values();

        // si no se encuentra ninguna pareja de elementos consecutivos diferentes, significa que todos los elementos son iguales. 
        bool equals  = adjacent_find(repeat.begin(), repeat.end(), not_equal_to<int>()) == repeat.end();

        return equals;
    }
};
    

int main(){
    Solution s;
    string Input {"abacbc"}; // imprime 1 -> true 
    // string Input {"aaabb"}; // imprime 0 -> false

    bool rpta = s.areOccurrencesEqual(Input);
    cout << rpta << endl;

    // (rpta)?
    // cout << "Los caracteres SI tienen el mismo # de ocurrencias" : 
    // cout << "Los caracteres NO tienen el mismo # de ocurrencias";
    
    return 0;
}
