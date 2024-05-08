#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node(T value) : data(value), next(nullptr), prev(nullptr) {}
  Node(T value, Node<T> *_next, Node<T> *_prev) : data(value), next(_next), prev(_prev) {}
};

template <class T>
class DoublyLinkedList
{
private:
  int nodes{};
  Node<T> *head;
  Node<T> *tail;

public:
  ~DoublyLinkedList() {}

  DoublyLinkedList() : head(nullptr), tail(nullptr), nodes(0) {}

  T front()
  {
    return head->data;
  }

  T back()
  {
    return tail->data;
  }

  // O(1)
  void push_front(T elem)
  {
    if (empty())
    {
      head = tail = new Node<T>{elem};
    }
    else
    {
      head->prev = new Node<T>{elem, head, nullptr};
      head = head->prev;
    }
    nodes++;
  }

  // O(1)
  void push_back(T elem)
  {
    if (empty())
    {
      head = tail = new Node<T>{elem};
    }
    else
    {
      tail->next = new Node<T>{elem, nullptr, tail};
      tail = tail->next;
    }
    nodes++;
  }

  T pop_front()
  {
    if (empty())
      throw out_of_range("List is empty");
    T data = head->data;
    head = head->next;
    --nodes;
    if (empty())
      tail = nullptr;
    else
    {
      delete head->prev;
      head->prev = nullptr;
    }

    return data;
  }

  T pop_back()
  {
    if (empty())
      throw out_of_range("List is empty");
    T data = tail->data;
    tail = tail->prev;
    --nodes;
    if (empty())
      head = nullptr;
    else
    {
      delete tail->next;
      tail->next = nullptr;
    }

    return data;
  }

  // O(1)
  void insertNode(Node<T> *trav, T elem)
  {
    if (trav->prev == nullptr)
    {
      push_front(elem);
    };
    if (trav->next == nullptr)
    {
      push_back(elem);
    };
    Node<T> *newNode = new Node<T>{elem};
    newNode->prev = trav->prev;
    newNode->next = trav;
    newNode->next->prev = newNode->prev->next = newNode;
    nodes++;
  }

  // O(n)
  void insert(T elem, int pos)
  {
    if (pos < 0 || pos >= size())
      throw invalid_argument("Position is out of range.");
    int i;
    Node<T> *trav;
    // busca desde el final de la lista
    if (pos > size() / 2)
      for (i = size(), trav = tail; i != pos; i--)
        trav = trav->next;
    // busca desde el principio de la lista
    else
      for (i = 1, trav = head; i != pos; i++)
        trav = trav->next;

    return insertNode(trav, elem);
  }

  // O(1)
  T removeNode(Node<T> *node)
  {
    if (node->prev == nullptr)
    {
      return pop_front();
    };
    if (node->next == nullptr)
    {
      return pop_back();
    };
    node->next->prev = node->prev;
    node->prev->next = node->next;
    T data = node->data; //  not necessary, we can just remove the node
    delete node;
    node = nullptr;
    --nodes;

    return data;
  }

  // O(n)
  T remove(int pos)
  {
    if (pos < 0 || pos >= size())
      throw invalid_argument("Position is out of range.");
    int i;
    Node<T> *trav;
    // busca desde el principio de la lista
    if (pos < size() / 2)
      for (i = 0, trav = head; i != pos - 1; i++)
        trav = trav->next;
    // busca desde el final de la lista
    else
      for (i = size() - 1, trav = tail; i != pos - 1; i--)
        trav = trav->prev;

    return removeNode(trav);
  }

  T &operator[](int pos)
  {
    Node<T> *iter = head;
    for (int i = 1; i < pos; i++)
    {
      iter = iter->next;
    }
    return iter->data;
  }

  bool empty() { return !size(); }

  int size() { return nodes; }

  // O(n)
  void clear()
  {
    auto *trav = head;
    while (trav != nullptr)
    {
      Node<T> *next = trav->next;
      trav->prev = trav->next = nullptr;
      trav = next;
    }
    delete trav;
    head = tail = trav = nullptr;
    nodes = 0;
    cout << "Lista vacia." << endl; // comentario de aviso
  }

  // O(n)
  void reverse()
  {
    Node<T> *current = head;
    Node<T> *temp = nullptr;

    while (current != nullptr)
    {
      temp = current->prev; // Intercambiar los punteros next y prev del nodo actual
      current->prev = current->next;
      current->next = temp;
      current = current->prev; // Mover al siguiente nodo
    }

    if (temp != nullptr) // Si current es nullptr, entonces tail se convierte en el nuevo head y viceversa
    {
      head = temp->prev;
    }
  }

  void display()
  {
    for (Node<T> *temp = head; temp != nullptr; temp = temp->next)
    {
      cout << temp->data << " ";
    }
    cout << endl;
  }
};
