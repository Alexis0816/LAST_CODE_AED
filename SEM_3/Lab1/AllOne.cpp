#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    string key;
    int recuento;
    Node *next;
    Node *prev;
    Node(string _key, Node *_next = nullptr, Node *_prev = nullptr, int rec = 1) : key(_key), next(_next), prev(_prev), recuento(rec) {}
};

class AllOne {
private:
    unordered_map<string, Node*> keyMap;
    Node *head;
    Node *tail;

public:
    AllOne() {
        head = new Node("");
        tail = new Node("");
        head->next = tail;
        tail->prev = head;
    }

    void inc(string key) {
        if (keyMap.find(key) != keyMap.end()) {
            // La clave ya existe, incrementamos su recuento
            Node *node = keyMap[key];
            node->recuento++;
            // Movemos el nodo a la posición correcta según su nuevo recuento
            while (node->next != tail && node->recuento > node->next->recuento) {
                moveNode(node, node->next);
            }
        } else {
            // La clave no existe, creamos un nuevo nodo
            Node *newNode = new Node(key);
            // Insertamos el nuevo nodo después del nodo head
            insertAfter(head, newNode);
            // Mapeamos la clave al nuevo nodo
            keyMap[key] = newNode;
        }
    }

    void dec(string key) {
        if (keyMap.find(key) != keyMap.end()) {
            // La clave existe, decrementamos su recuento
            Node *node = keyMap[key];
            if (node->recuento > 1) {
                node->recuento--;
                // Movemos el nodo a la posición correcta según su nuevo recuento
                while (node->prev != head && node->recuento < node->prev->recuento) {
                    moveNode(node->prev, node);
                }
            } else {
                // Si el recuento llega a 0, eliminamos el nodo y lo eliminamos del mapa
                keyMap.erase(key);
                removeNode(node);
                delete node;
            }
        }
    }

    string getMaxKey() {
        return tail->prev != head ? tail->prev->key : "";
    }

    string getMinKey() {
        return head->next != tail ? head->next->key : "";
    }

private:
    // Inserta un nodo newNode después del nodo prevNode
    void insertAfter(Node *prevNode, Node *newNode) {
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        prevNode->next->prev = newNode;
        prevNode->next = newNode;
    }

    // Mueve el nodo moveNode después del nodo prevNode
    void moveNode(Node *prevNode, Node *moveNode) {
        removeNode(moveNode);
        insertAfter(prevNode, moveNode);
    }

    // Elimina el nodo node de la lista enlazada
    void removeNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};

int main() {
    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("hello");
    cout << allOne.getMaxKey() << endl; // devuelve "hello"
    cout << allOne.getMinKey() << endl; // devuelve "hello"
    allOne.inc("leet");
    cout << allOne.getMaxKey() << endl; // devuelve "hello"
    cout << allOne.getMinKey() << endl; // devuelve "leet"

    return 0;
}

