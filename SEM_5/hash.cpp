#include "hash.hpp"

int main(){
    HashTable<string, int> hash(5);
    hash.insert("Alonso", 9);
    hash.insert("Amanda", 12);
    hash.insert("Manuel", 7);
    
    hash.insert("Adrian", 7);
    hash.insert("Danilo", 6);
    hash.insert("Jorge", 4);
    hash.insert("Alexander", 2);

    cout << "Manuel: " << hash["Manuel"] << endl;

    hash.insert("Vicente", 3);
    hash.insert("Franchesca", 6);
    hash.insert("Dario", 8);

    hash._delete("Manuel");

    cout << "Adrian: " << hash.find("Adrian") << endl; // con función find()

    try {
        cout << "Valor encontrado: " << hash.find("Manuel") << endl;
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }

    try {
        cout << "Valor encontrado: " << hash["Mia"] << endl;  // con operador sobrecargado
    } catch (runtime_error& e) {
        cerr << e.what() << endl;
    }


    cout << endl << "HashTable: Contenido (Key - Value):" << endl << endl;
    for (int i = 0; i < hash._size(); ++i){
        cout << "Lista #" << i << " - Registros:";
        for (auto local_it = hash._begin(i); local_it != hash._end(i); ++local_it)
            cout << " " << local_it->key << ": " << local_it->value;
        cout << endl;
    }
    cout<< "Size: "<<hash._size()<<endl;
    cout<< "Size de la lista #"<<16<<": "<<hash.bucket_size(16)<<endl<<endl;


    // se obtiene el mapa de (Key - Values)
    map<string, int> KeyValues = hash.key_value();

    // imprimo mapa de (Key - Values)
    for (auto& [k ,v] : KeyValues) {
        cout << "Key: " << k << ", Value: " << v << endl;
    } cout << endl;

    
    return 0;
}
