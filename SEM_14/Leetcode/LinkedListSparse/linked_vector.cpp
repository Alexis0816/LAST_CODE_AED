#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

struct Node
{
  int col;
  int value;
  Node *next;
  Node(int c, int v) : col(c), value(v), next(nullptr) {}
};

class LinkedList
{
public:
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
      cout << "(" << current->col << ", " << current->value << ") ";
      current = current->next;
    }
  }
};


vector<LinkedList> transformToLinkedList(int rows, int cols, const vector<tuple<int, int, int>> &matrix){
  vector<LinkedList> linkedMatrix(rows);

  for (const auto &element : matrix){
    int row, col, value;
    tie(row, col, value) = element;
    linkedMatrix[row - 1].insert(col, value); // row - 1 para indexar desde 0
  }

  return linkedMatrix;
}

int main() {
  // Ejemplo de entrada
  int rows = 9, cols = 9;
  vector<tuple<int, int, int>> matrix = {
      {2, 1, 3}, {2, 2, 5}, {2, 7, 9}, {3, 7, 5}, {4, 5, 5}, {4, 9, 22},
      {6, 5, 5}, {7, 2, 5}, {7, 8, 5}, {9, 9, 5}
  };

  vector<LinkedList> linkedMatrix = transformToLinkedList(rows, cols, matrix);

  // Imprimir la representación enlazada
  for (int i = 0; i < rows; ++i) {
    cout << "Row " << i + 1 << ": ";
    linkedMatrix[i].print();
    cout << endl;
  }

  return 0;
}
