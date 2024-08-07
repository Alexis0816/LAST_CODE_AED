#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Node{
public:
  T data;
  int pos_row;
  int pos_col;
  Node<T> *next_row;
  Node<T> *next_col;

  Node(int r, int c, T value) : pos_row(r), pos_col(c), data(value), next_row(nullptr), next_col(nullptr) {}
};

template <class T>
class SparseMatrix{
private:
  vector<Node<T> *> rows; // Vector de punteros a nodos para las filas
  vector<Node<T> *> cols; // Vector de punteros a nodos para las columnas
  int n_rows;
  int n_cols;

public:
  SparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols){
    this->rows.resize(rows, nullptr);
    this->cols.resize(cols, nullptr);
  }

  void insert(int r, int c, T value){
    Node<T> *newNode = new Node<T>(r, c, value);

    if (!rows[r]){ rows[r] = newNode;} 
    else {
      Node<T> *temp = rows[r];
      Node<T> *prev = nullptr;
      while (temp && temp->pos_col < c){
        prev = temp;
        temp = temp->next_row;
      }
      if (prev){
        prev->next_row = newNode;
      }
      else { rows[r] = newNode; }

      newNode->next_row = temp;
    }

    if (!cols[c]) { cols[c] = newNode; }
    else {
      Node<T> *temp = cols[c];
      Node<T> *prev = nullptr;
      while (temp && temp->pos_row < r){
        prev = temp;
        temp = temp->next_col;
      }
      if (prev) { prev->next_col = newNode; }
      else { cols[c] = newNode; }

      newNode->next_col = temp;
    }
  }

  void display() {
    for (int i = 0; i < n_rows; ++i) {
      cout<< "Row "<< i+1 <<": ";
      Node<T>* temp = rows[i];
      for (int j = 0; j < n_cols; ++j) {
        if (temp && temp->pos_col == j) {
          cout << temp->data << " ";
          temp = temp->next_row;
        } else {
          cout << "0 ";
        }
      }
      cout << endl;
    }
    cout << endl;
  }
};

int main()
{
  SparseMatrix<int> mat1(4, 5);
  mat1.insert(0, 2, 3);
  mat1.insert(0, 4, 4);
  mat1.insert(1, 2, 5);
  mat1.insert(1, 3, 7);
  mat1.insert(3, 1, 2);
  mat1.insert(3, 2, 6);

  mat1.display();

  return 0;
}
