#include <iostream>
#include <forward_list>
#include <functional>
#include <vector>
#include <string>
using namespace std;

template <typename TK, typename TV>
class HashChaining {
private:
  struct Entry {
      TK key;
      TV value;
      Entry* next;

      Entry(const TK& k, const TV& v) : key(k), value(v), next(nullptr) {}
  };

  using List = forward_list<Entry*>;
  forward_list<List> array;
  function<size_t(const TK&)> hashFunc;

  size_t capacity;
  size_t size;

public:
  HashChaining(size_t cap) : capacity(cap), size(0) {
    array.resize(capacity);
    // función lambda  para el cálculo del índice de la tabla de hash
    hashFunc = [this](const TK& key) { return hash<TK>{}(key) % capacity; };
  }

  ~HashChaining() {
    clear();
  }

  void insert(const TK& key, const TV& value) {
    size_t index = hashFunc(key);
    auto it = array.begin();
    advance(it, index); // Avanzar el iterador hasta la posición 'index'
    
    Entry* entry = new Entry(key, value);
    it->push_front(entry);
    ++size;
  }

  bool find(const TK& key) const {
    size_t index = hashFunc(key);
    for (Entry* entry : array[index]) {
      if (entry->key == key) {
        return true;
      }
    }
    return false;
  }

  void clear() {
    for (List& list : array) {
      for (Entry* entry : list) {
        delete entry;
      }
      list.clear();
    }
    size = 0;
  }

  void printHash() const {
    size_t forwardIndex = 1;
    auto it = array.begin();
    
    while (it != array.end()) {
      cout << "Forward " << forwardIndex++ << " :" << endl;
      int entryNumber = 1;
      for (Entry* entry : *it) {
        cout << "clave-valor numero " << entryNumber++ << ": " << entry->key << "-" << entry->value << endl;
      }
      ++it;
    }
  }
};

int main() {
    HashChaining<string, int> hashTable(10);
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 10);
    hashTable.insert("orange", 15);

    hashTable.printHash();

    return 0;
}

