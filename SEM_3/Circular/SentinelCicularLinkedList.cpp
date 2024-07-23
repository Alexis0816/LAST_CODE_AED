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

class CircularLinkedList
{
private:
    int nodes;
    Node *sentinel;

public:
    ~CircularLinkedList()
    {
        clear();
        delete sentinel;
    }

    CircularLinkedList() : nodes(0)
    {
        sentinel = new Node;
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

    int front()
    {
        if (empty())
            throw out_of_range("List is empty");
        return sentinel->next->data;
    }

    int back()
    {
        if (empty())
            throw out_of_range("List is empty");
        return sentinel->prev->data;
    }

    void push_front(int data)
    {
        Node* nodo = new Node;
        nodo->data = data;

        nodo->next = sentinel->next;
        nodo->prev = sentinel;
        sentinel->next->prev = nodo;
        sentinel->next = nodo;
        
        nodes++;
    }

    void push_back(int data)
    {
        Node* nodo = new Node;
        nodo->data = data;

        nodo->next = sentinel;
        nodo->prev = sentinel->prev;
        sentinel->prev->next = nodo;
        sentinel->prev = nodo;

        nodes++;
    }

    int pop_front()
    {
        if (empty())
            throw out_of_range("List is empty");

        Node* oldHead = sentinel->next;
        int data = oldHead->data;

        sentinel->next = oldHead->next;
        oldHead->next->prev = sentinel;
        delete oldHead;

        --nodes;
        return data;
    }

    int pop_back()
    {
        if (empty())
            throw out_of_range("List is empty");

        Node* oldTail = sentinel->prev;
        int data = oldTail->data;

        sentinel->prev = oldTail->prev;
        oldTail->prev->next = sentinel;
        delete oldTail;

        --nodes;
        return data;
    }

    void insertNode(Node *trav, int elem)
    {
        Node* newNode = new Node;
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
            for (i = size(), trav = sentinel->prev; i != pos; i--)
                trav = trav->prev;
        else
            for (i = 0, trav = sentinel->next; i != pos; i++)
                trav = trav->next;

        insertNode(trav, elem);
    }

    int removeNode(Node *node)
    {
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
            for (i = 0, trav = sentinel->next; i != pos; i++)
                trav = trav->next;
        else
            for (i = size() - 1, trav = sentinel->prev; i != pos; i--)
                trav = trav->prev;

        return removeNode(trav);
    }

    int &operator[](int pos)
    {
        Node *iter = sentinel->next;
        for (int i = 0; i < pos; i++)
        {
            iter = iter->next;
        }
        return iter->data;
    }

    bool empty() { return nodes == 0; }

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
        if (empty()) return;
        
        Node *current = sentinel->next;
        Node *temp = nullptr;
        
        do
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        } while (current != sentinel);

        if (temp != nullptr)
        {
            sentinel->next = temp->prev;
        }
    }

    void display()
    {
        if (empty()) return;
        
        Node *temp = sentinel->next;
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != sentinel);
        cout << endl;
    }
};

int main()
{
    CircularLinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.display(); // Output: 1 2 3

    list.push_front(0);
    list.display(); // Output: 0 1 2 3

    list.pop_back();
    list.display(); // Output: 0 1 2

    list.pop_front();
    list.display(); // Output: 1 2

    list.insert(5, 1);
    list.display(); // Output: 1 5 2

    list.remove(1);
    list.display(); // Output: 1 2

    list.reverse();
    list.display(); // Output: 2 1

    list.clear();
    list.display(); // Output: Lista vacia.
}
