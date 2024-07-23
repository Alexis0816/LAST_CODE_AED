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
    Node *head; //sentinel

public:
    ~CircularLinkedList()
    {
        clear();
        delete head;
    }

    CircularLinkedList() : nodes(0)
    {
        head = new Node;
        head->next = head;
        head->prev = head;
    }

    int front()
    {
        if (empty())
            throw out_of_range("List is empty");
        return head->next->data;
    }

    int back()
    {
        if (empty())
            throw out_of_range("List is empty");
        return head->prev->data;
    }

    void push_front(int data)
    {
        Node* nodo = new Node;
        nodo->data = data;

        nodo->next = head->next;
        nodo->prev = head;
        head->next->prev = nodo;
        head->next = nodo;
        
        nodes++;
    }

    void push_back(int data)
    {
        Node* nodo = new Node;
        nodo->data = data;

        nodo->next = head;
        nodo->prev = head->prev;
        head->prev->next = nodo;
        head->prev = nodo;

        nodes++;
    }

    int pop_front()
    {
        if (empty())
            throw out_of_range("List is empty");

        Node* oldHead = head->next;
        int data = oldHead->data;

        head->next = oldHead->next;
        oldHead->next->prev = head;
        delete oldHead;

        --nodes;
        return data;
    }

    int pop_back()
    {
        if (empty())
            throw out_of_range("List is empty");

        Node* oldTail = head->prev;
        int data = oldTail->data;

        head->prev = oldTail->prev;
        oldTail->prev->next = head;
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
            for (i = size(), trav = head->prev; i != pos; i--)
                trav = trav->prev;
        else
            for (i = 0, trav = head->next; i != pos; i++)
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
            for (i = 0, trav = head->next; i != pos; i++)
                trav = trav->next;
        else
            for (i = size() - 1, trav = head->prev; i != pos; i--)
                trav = trav->prev;

        return removeNode(trav);
    }

    int &operator[](int pos)
    {
        Node *iter = head->next;
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
        
        Node *current = head->next;
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
            head->next = temp->prev;
        }
    }

    void display()
    {
        if (empty()) return;
        
        Node *temp = head->next;
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
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
