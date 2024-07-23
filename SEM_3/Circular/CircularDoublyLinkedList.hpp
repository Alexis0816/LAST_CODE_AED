#include <iostream>
#include <stdexcept>

using namespace std;

class Node
{
public:
  int data;
  Node *next;
  Node *prev;
};

class CircularDoublyLinkedList
{
private:
  int nodes;
  Node *head;

public:
  ~CircularDoublyLinkedList()
  {
    clear();
  }

  CircularDoublyLinkedList() : head(nullptr), nodes(0) {}

  int front()
  {
    if (empty())
      throw out_of_range("List is empty");
    return head->data;
  }

  int back()
  {
    if (empty())
      throw out_of_range("List is empty");
    return head->prev->data;
  }

  void push_front(int data)
  {
    Node *nodo = new Node;
    nodo->data = data;

    if (empty())
    {
      nodo->next = nodo->prev = nodo;
      head = nodo;
    }
    else
    {
      nodo->next = head;
      nodo->prev = head->prev;
      head->prev->next = nodo;
      head->prev = nodo;
      head = nodo;
    }
    nodes++;
  }

  void push_back(int data)
  {
    Node *nodo = new Node;
    nodo->data = data;

    if (empty())
    {
      nodo->next = nodo->prev = nodo;
      head = nodo;
    }
    else
    {
      nodo->next = head;
      nodo->prev = head->prev;
      head->prev->next = nodo;
      head->prev = nodo;
    }
    nodes++;
  }

  int pop_front()
  {
    if (empty())
      throw out_of_range("List is empty");

    int data = head->data;
    Node *oldHead = head;

    if (size() == 1)
    {
      head = nullptr;
    }
    else
    {
      head->next->prev = head->prev;
      head->prev->next = head->next;
      head = head->next;
    }
    delete oldHead;
    --nodes;
    return data;
  }

  int pop_back()
  {
    if (empty())
      throw out_of_range("List is empty");

    int data = head->prev->data;
    Node *oldTail = head->prev;

    if (size() == 1)
    {
      head = nullptr;
    }
    else
    {
      head->prev = oldTail->prev;
      oldTail->prev->next = head;
    }
    delete oldTail;
    --nodes;
    return data;
  }

  void insertNode(Node *trav, int elem)
  {
    if (trav->prev == nullptr)
    {
      push_front(elem);
      return;
    }
    if (trav->next == nullptr)
    {
      push_back(elem);
      return;
    }

    Node *newNode = new Node;
    newNode->data = elem;
    newNode->prev = trav->prev;
    newNode->next = trav;
    newNode->next->prev = newNode->prev->next = newNode;
    nodes++;
  }

  void insert(int elem, int pos)
  {
    if (pos < 0 || pos >= size())
      throw invalid_argument("Position is out of range.");
    int i;
    Node *trav;
    if (pos > size() / 2)
      for (i = size(), trav = head->prev; i != pos; i--)
        trav = trav->prev;
    else
      for (i = 0, trav = head; i != pos; i++)
        trav = trav->next;

    insertNode(trav, elem);
  }

  int removeNode(Node *node)
  {
    if (node == head)
    {
      return pop_front();
    }
    if (node == head->prev)
    {
      return pop_back();
    }

    int data = node->data;
    node->next->prev = node->prev;
    node->prev->next = node->next;
    delete node;
    --nodes;
    return data;
  }

  int remove(int pos)
  {
    if (pos < 0 || pos >= size())
      throw invalid_argument("Position is out of range.");
    int i;
    Node *trav;
    if (pos < size() / 2)
      for (i = 0, trav = head; i != pos; i++)
        trav = trav->next;
    else
      for (i = size() - 1, trav = head->prev; i != pos; i--)
        trav = trav->prev;

    return removeNode(trav);
  }

  int &operator[](int pos)
  {
    Node *iter = head;
    for (int i = 0; i < pos; i++)
    {
      iter = iter->next;
    }
    return iter->data;
  }

  bool empty() { return !size(); }

  int size() { return nodes; }

  void clear()
  {
    while (!empty())
    {
      pop_front();
    }
    cout << "Lista vacia." << endl;
  }

  void reverse()
  {
    if (empty())
      return;

    Node *current = head;
    Node *temp = nullptr;

    do
    {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    } while (current != head);

    if (temp != nullptr)
    {
      head = temp->prev;
    }
  }

  void display()
  {
    if (empty())
      return;

    Node *temp = head;
    do
    {
      cout << temp->data << " ";
      temp = temp->next;
    } while (temp != head);
    cout << endl;
  }
};
