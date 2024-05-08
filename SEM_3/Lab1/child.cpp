#include <iostream>
using namespace std;

struct Node
{
  int val;
  Node *next;
  Node *prev;
  Node *child;
  Node(int value) : val(value), next(nullptr), prev(nullptr), child(nullptr) {}
  Node(int value, Node *_next, Node *_prev) : val(value), next(_next), prev(_prev), child(nullptr) {}
};

class ChildLinkedList
{
private:
  int nodes = 0;
  Node *head = nullptr;
  Node *tail = nullptr;

public:
  int size() { return nodes; }

  bool isEmpty() { return size() == 0; }

  // O(1)
  void push_back(int elem)
  {
    if (isEmpty())
    {
      head = tail = new Node{elem};
    }
    else
    {
      tail->next = new Node{elem, nullptr, tail};
      tail = tail->next;
    }
    nodes++;
  }

  Node *search(int key, Node *nodito)
  {
    if (nodito == nullptr || nodito->val == key)
    {
      return nodito;
    }

    Node *found = search(key, nodito->child);
    if (found != nullptr)
    {
      return found;
    }

    return search(key, nodito->next);
  }

  void push_back(int nodePrev, int nodeNext)
  {
    Node *temp = search(nodePrev, head);
    if (temp != nullptr)
    {
      Node *nuevo = new Node{nodeNext, nullptr, temp};
      temp->next = nuevo;
      // Node(T value, Node<T> *_next, Node<T> *_prev) : val(value), next(_next), prev(_prev), child(nullptr) {}
      if (temp == tail)
      {
        tail = nuevo;
      }
      nodes++;
    }
    else
    {
      cout << "Node prev not found: " << nodePrev << endl;
    }
  }

  void insert_child(int p, int h)
  {
    Node *padre = search(p, head);
    if (padre)
    {
      Node *hijo = new Node{h};
      padre->child = hijo;
      nodes++;
      // Node(T value = T()) : val(value), next(nullptr), prev(nullptr), child(nullptr) {}
    }
    else
    {
      cout << "Parent node not found: " << p << endl;
    }
  }

  void display()
  {
    for (Node *temp = head; temp != nullptr; temp = temp->next)
    {
      cout << temp->val << " ";
    }
    cout << endl;
  }

  void display_flatten()
  {
    if (isEmpty())
    {
      cout << "Lista vacía" << endl;
      return;
    }

    flatten(head);
    cout << endl;
  }

  void flatten(Node *nodito)
  {
    if (nodito == nullptr)
      return; // Si es NULL no hay nada que hacer

    // Añadir el dato
    cout << nodito->val << " ";
    // Recorrer los hijos y llamar recursivamente
    if (nodito->child)
    {
      flatten(nodito->child);
    }
    if (nodito->next)
    {
      flatten(nodito->next);
    }
  }
};

int main()
{
  ChildLinkedList c;
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);

  // el padre - el hijo
  c.insert_child(3, 7);

  // nodo anterior - nodo siguiente
  c.push_back(7, 8);
  c.push_back(8, 9);
  c.push_back(9, 10);

  // el padre - el hijo
  c.insert_child(8, 11);

  // nodo anterior - nodo siguiente
  c.push_back(11, 12);

  c.display_flatten();

  return 0;
}