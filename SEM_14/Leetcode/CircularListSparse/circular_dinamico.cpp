#include <iostream>
using namespace std;

struct Node
{
  int col;
  int value;
  Node *next;
  Node(int c, int v) : col(c), value(v), next(nullptr) {}
};

struct CircularLinkedList
{
  Node *head;
  Node *tail;

  CircularLinkedList() : head(nullptr), tail(nullptr) {}

  void insert(int col, int value){
    Node *newNode = new Node(col, value);
    if (!head)
    {
      head = newNode;
      tail = newNode;
      newNode->next = head;
    }
    else {
      tail->next = newNode;
      tail = newNode;
      tail->next = head;
    }
  }

  void print(){
    if (!head) return;

    auto *current = head;
    do{
      cout << "(" << current->col << ", " << current->value << ") ";
      current = current->next;
    } while (current != head);
  }

  ~CircularLinkedList(){
    if (!head) return;
    
    auto *current = head;
    do{
      Node *toDelete = current;
      current = current->next;
      delete toDelete;
    } while (current != head);
  }
};


CircularLinkedList** transformToCircularLinkedList(int rows, int cols, int numElements, int matrix[][3]) {
  CircularLinkedList** circularLinkedMatrix = new CircularLinkedList*[rows];
  for (int i = 0; i < rows; ++i) {
    circularLinkedMatrix[i] = new CircularLinkedList();
  }

  for (int i = 0; i < numElements; ++i) {
    int row = matrix[i][0] - 1;
    int col = matrix[i][1];
    int value = matrix[i][2];
    circularLinkedMatrix[row]->insert(col, value);
  }

  return circularLinkedMatrix;
}


int main() {
  // Ejemplo de entrada
  int rows = 9, cols = 7, numElements = 7;
  int matrix[7][3] = {
    {2, 3, 7}, {5, 1, 5}, {5, 4, 2}, {7, 4, 9}, {8, 1, 4}, {8, 6, 6}, {9, 3, 3}
  };

  CircularLinkedList** circularLinkedMatrix = transformToCircularLinkedList(rows, cols, numElements, matrix);

  // Imprimir la representación enlazada circular
  for (int i = 0; i < rows; ++i) {
    cout << "Row " << i + 1 << ": ";
    circularLinkedMatrix[i]->print();
    cout << std::endl;
  }

  // Liberar memoria
  for (int i = 0; i < rows; ++i) {
      delete circularLinkedMatrix[i];
  }
  delete[] circularLinkedMatrix;

  return 0;
}
