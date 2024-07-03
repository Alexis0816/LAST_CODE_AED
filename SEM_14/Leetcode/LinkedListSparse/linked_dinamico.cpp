#include <iostream>
#include <tuple>
using namespace std;

struct Node
{
  int col;
  int value;
  Node *next;
  Node(int c, int v) : col(c), value(v), next(nullptr) {}
};

struct LinkedList
{
  Node *head;
  LinkedList() : head(nullptr) {}

  void insert(int col, int value)
  {
    Node *newNode = new Node(col, value);
    if (!head)
    {
      head = newNode;
    }
    else
    {
      Node *current = head;
      while (current->next)
      {
        current = current->next;
      }
      current->next = newNode;
    }
  }

  void print() const
  {
    Node *current = head;
    while (current)
    {
      cout<< "(" << current->col << ", " << current->value << ") ";
      current = current->next;
    }
  }

  ~LinkedList()
  {
    Node *current = head;
    while (current)
    {
      Node *toDelete = current;
      current = current->next;
      delete toDelete;
    }
  }
};

LinkedList** transformToLinkedList(int rows, int cols, int numElements, int matrix[][3]) {
  LinkedList** linkedMatrix = new LinkedList*[rows];
  for (int i = 0; i < rows; ++i) {
    linkedMatrix[i] = new LinkedList();
  }

  for (int i = 0; i < numElements; ++i) {
    int row = matrix[i][0] - 1;
    int col = matrix[i][1];
    int value = matrix[i][2];
    linkedMatrix[row]->insert(col, value);
  }

  return linkedMatrix;
}


int main() {
  // Ejemplo de entrada
  int rows = 9, cols = 9, numElements = 10;
  int matrix[10][3] = {
      {2, 1, 3}, {2, 2, 5}, {2, 7, 9}, {3, 7, 5}, {4, 5, 5}, {4, 9, 22},
      {6, 5, 5}, {7, 2, 5}, {7, 8, 5}, {9, 9, 5}
  };

  LinkedList** linkedMatrix = transformToLinkedList(rows, cols, numElements, matrix);

  // Imprimir la representación enlazada
  for (int i = 0; i < rows; ++i) {
      cout << "Row " << i + 1 << ": ";
      linkedMatrix[i]->print();
      cout << endl;
  }

  // Liberar memoria
  for (int i = 0; i < rows; ++i) {
      delete linkedMatrix[i];
  }
  delete[] linkedMatrix;

  return 0;
}
