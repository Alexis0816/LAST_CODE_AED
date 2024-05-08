#include <iostream>
using namespace std;

struct Node
{
  int key;
  int value;
  Node *next;
  Node *prev;
  Node() : key(0), value(0), next(nullptr), prev(nullptr) {}
  Node(Node *_next) : key(0), value(0), next(_next), prev(nullptr) {}
  Node(int _key, int _value) : key(_key), value(_value), next(nullptr), prev(nullptr) {}
};

class LRUCache
{
private:
  int capacity;
  int nodes = 0;
  Node *head;
  Node *tail;

public:
  LRUCache(int _capacity) : capacity(_capacity)
  {
    tail = new Node();
    head = new Node(tail);
    tail->prev = head;
  }

  ~LRUCache()
  {
    // Free memory for all nodes
    Node *curr = head;
    while (curr)
    {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    }
  }

  int size() { return nodes; }

  bool isEmpty() { return size() == 0; }

  void addToFront(Node *node)
  {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(Node *node)
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  int get(int key)
  {
    Node *node = findNode(key);
    if (node != nullptr)
    {
      removeNode(node);
      addToFront(node); // muevo el nodo al frente ya que es el recientemente usado
      return node->value;
    }
    return -1;
  }

  void put(int key, int value)
  {
    Node *node = findNode(key);
    if (node != nullptr)
    {
      node->value = value; // Si el nodo con la llave ya existe, actualizo el valor del nodo
      removeNode(node);
      addToFront(node); // muevo el nodo al frente ya que es el recientemente usado
    }
    else
    {
      if (size() >= capacity)
      {
        Node *toRemove = tail->prev;
        removeNode(toRemove); // si el caché está lleno, remuevo  el nodo menos utilizado (tail)
        delete toRemove;
        nodes--;
      }

      Node *newNode = new Node(key, value);
      addToFront(newNode); // agrego el nuevo nodo al frente
      nodes++;
    }
  }

  // Función de envoltura para iniciar la búsqueda desde el nodo después de la cabeza (head->next)
  Node *findNode(int key){ return findNodeRecursive(head->next, key); }

private:
  Node *findNodeRecursive(Node *curr, int key)
  {
    // Caso base: Si el nodo actual es el nodo final (tail) o nullptr, retornamos nullptr
    if (curr == nullptr || curr == tail) return nullptr;
    // Si encontramos el nodo con la clave deseada, lo retornamos
    if (curr->key == key) return curr;
    // Llamada recursiva para continuar la búsqueda en el siguiente nodo
    return findNodeRecursive(curr->next, key);
  }
};

int main()
{
  LRUCache lRUCache(2);
  lRUCache.put(1, 1);
  lRUCache.put(2, 2);
  cout << lRUCache.get(1) << endl; // Output 1
  lRUCache.put(3, 3);              // actualiza  el valor de la clave existente 2
  cout << lRUCache.get(2) << endl; // Output -1 porque la clave 2 fue desalojada
  lRUCache.put(4, 4);              // actualiza  el valor de la clave existente 1
  cout << lRUCache.get(1) << endl; // Output -1
  cout << lRUCache.get(3) << endl; // Output 3
  cout << lRUCache.get(4) << endl; // Output 4

  return 0;
}