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

    TV find(TK key) {
        int index = hashCode(key);
        auto it0 = begin(hashTable[index]);
        
        // Busca la clave en la lista correspondiente
        while (it0 != end(hashTable[index])) {
            if ((*it0).key == key) {
                return (*it0).value;
            }
            ++it0;
        }

        // Si no se encuentra la clave, devuelve un valor predeterminado
        return TV(); // Devuelve un valor predeterminado para el tipo de valor TV
    }
    
private:
    size_t hashCode(TK key){
        hash<TK> ptr_hash;
        return ptr_hash(key) % capacity;
    }
};

class Solution {
public:
    string minimizeStringValue(string s) {
        HashTable<char, int> freq; 

        vector<int> pos;
        int count = 0;

        // Contar la frecuencia de cada letra
        for (char ch : s) {
            if (ch == '?')
                count++;
            else if (ch < 'a' || ch > 'z') // Validar el rango de caracteres
                return ""; // Devuelve una cadena vacía en caso de un carácter no válido
            else
                freq.insert(ch);
        }

        // Buscar las posiciones de los caracteres de interrogación
        for (auto it = s.begin(); it != s.end(); ++it) {
            if (*it == '?') {
                pos.push_back(distance(s.begin(), it));
            }
        }

        // Reemplazar los caracteres de interrogación con las letras menos frecuentes
        for (int p : pos) {
            char minChar;
            int minFreq = INT_MAX;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                int freqCh = freq.find(ch);
                if (freqCh < minFreq) {
                    minFreq = freqCh;
                    minChar = ch;
                }
            }
            s[p] = minChar;
            freq.insert(minChar); // Incrementa la frecuencia del carácter seleccionado
        }

        return s;
    }

};


int main() {
    Solution solution;
    cout << solution.minimizeStringValue("???") << endl; // abc
    cout << solution.minimizeStringValue("a?a?") << endl; // abac
    
    return 0;
}