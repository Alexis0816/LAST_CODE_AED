#include <iostream>
#include <string>
#include <forward_list>
#include "ForwardList.hpp"

using namespace std;


template <class TK, class TV>
class HashChaining {
private:
    struct Entry {
        TK key;
        TV value;
        Entry* next;
        Entry(TK k, TV v): key(k) , value(v), next(nullptr){}
    };

    using ForwardListEntry = forward_list<forward_list<Entry*>>;
    ForwardListEntry array;

    int capacity;
    double size;

public:
    HashChaining(int _capacity = 5) : capacity(_capacity), size(0) {
        array.resize(capacity);
    }

    void insert(TK key, TV value) {
      size_t index = hashCode(key);
      auto it = array.begin();
      advance(it,index); // avanza el iterador hasta la posición 'index'

      Entry* entry = new Entry(key,value);
      it->push_front(entry);
      size++;
    }

    void printHash() {
      size_t forwardIndex = 1;
      auto it = array.begin();
      
      while (it != array.end()) {
        cout << "Forward " << forwardIndex++ << " :" << endl;
        int n = 1;
        for (auto entry : *it) {
          cout << "\tKey-Value " << n++ << " : {" << entry->key << " - " << entry->value <<"}" << endl;
        }
        ++it;
      }
    }


    bool find(const TK& key) {
      size_t index = hashCode(key);
      auto it = array.begin();
      advance(it,index);

      for (Entry* entry : *it) {
        if (entry->key == key) {
          return true;
        }
      }
      return false;
    }

    int bucket_size(int index) { 
      auto it = array.begin();
      advance(it, index-1);
      return distance((*it).begin(), (*it).end());
    }

private:
    size_t hashCode(TK key) {
        hash<TK> ptr_hash;
        return ptr_hash(key) % capacity;
    }
};

int main() {
  HashChaining<string, int> hashTable(10);
  hashTable.insert("Alexis", 5);
  hashTable.insert("Fernando", 10);
  hashTable.insert("Carlos", 15);
  hashTable.insert("Julio", 20);
  hashTable.insert("Antony", 25);
  hashTable.insert("Vicente", 30);
  hashTable.insert("Diego", 35);
  
  hashTable.printHash();

  // hashTable.sizeBound(1);
  cout << hashTable.bucket_size(10) << endl;

  cout <<  "Is \"Diego\" in the table? " << hashTable.find("Diego") << endl;

  return 0;
}