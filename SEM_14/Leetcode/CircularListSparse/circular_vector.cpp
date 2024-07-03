#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

struct Node {
    int col;
    int value;
    Node* next;
    Node(int c, int v) : col(c), value(v), next(nullptr) {}
};

class CircularLinkedList {
private:  
  Node* head;
  Node *tail;

public:
  CircularLinkedList() : head(nullptr) {}

  void insert(int col, int value) {
    auto* newNode = new Node(col, value);
    if (!head) {
      head = newNode;
      tail = newNode;
      newNode->next = head;
    } else {
      tail->next = newNode;
      tail = newNode;
      tail->next = head;
    }
  }

  void print() {
    if (!head) return;

    auto* current = head;
    do {
      cout << "(" << current->col << ", " << current->value << ") ";
      current = current->next;
    } while (current != head);
  }

  ~CircularLinkedList() {
    if (!head) return;

    auto* current = head;
    do {
      auto* toDelete = current;
      current = current->next;
      delete toDelete;
    } while (current != head);
  }
};


vector<CircularLinkedList> transformToCircularLinkedList(int rows, int cols, const vector<tuple<int, int, int>>& matrix) {
  vector<CircularLinkedList> circularLinkedMatrix(rows);

  for (const auto& element : matrix) {
    int row, col, value;
    tie(row, col, value) = element;
    circularLinkedMatrix[row - 1].insert(col, value); // row - 1 para indexar desde 0
  }

  return circularLinkedMatrix;
}


int main() {
  // Ejemplo de entrada
  int rows = 9, cols = 7;
  vector<tuple<int, int, int>> matrix = {
      {2, 3, 7}, {5, 1, 5}, {5, 4, 2}, {7, 4, 9}, {8, 1, 4}, {8, 6, 6}, {9, 3, 3}
  };

  vector<CircularLinkedList> circularLinkedMatrix = transformToCircularLinkedList(rows, cols, matrix);

  // Imprimir la representación enlazada circular
  for (int i = 0; i < rows; ++i) {
    cout << "Row " << i + 1 << ": ";
    circularLinkedMatrix[i].print();
    cout << endl;
  }

  return 0;
}
