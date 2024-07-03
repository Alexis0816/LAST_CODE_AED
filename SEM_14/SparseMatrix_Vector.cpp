#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Node {
public:
  T data;
  int pos_row;
  int pos_col;
  Node<T>* next_row;
  Node<T>* next_col;

  Node(int r, int c, T value) : pos_row(r), pos_col(c), data(value), next_row(nullptr), next_col(nullptr) {}
};

template <class T>
class SparseMatrix {
private:
  vector<Node<T>*> rows;
  vector<Node<T>*> cols;
  int n_rows;
  int n_cols;

public:
  SparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
    this->rows.resize(rows, nullptr);
    this->cols.resize(cols, nullptr);
  }

  ~SparseMatrix() {
    // Destructor para liberar memoria
    for (auto& head : rows) {
      while (head) {
        Node<T>* temp = head;
        head = head->next_row;
        delete temp;
      }
    }
  }

  void insert(int r, int c, T value) {
    Node<T>* newNode = new Node<T>{r, c, value};
    if (!rows[r]) { rows[r] = newNode; } 
    else {
      Node<T>* temp = rows[r];
      while (temp->next_row && temp->next_row->pos_col < c) {
        temp = temp->next_row;
      }
      newNode->next_row = temp->next_row;
      temp->next_row = newNode;
    }

    if (!cols[c]) { cols[c] = newNode; } 
    else {
      Node<T>* temp = cols[c];
      while (temp->next_col && temp->next_col->pos_row < r) {
        temp = temp->next_col;
      }
      newNode->next_col = temp->next_col;
      temp->next_col = newNode;
    }
  }

  void remove(int r, int c) {
    if (!rows[r]) return;

    if (rows[r]->pos_col == c) {
      Node<T>* temp = rows[r];
      rows[r] = rows[r]->next_row;
      delete temp;
    } else {
      Node<T>* temp = rows[r];
      while (temp->next_row && temp->next_row->pos_col != c) {
        temp = temp->next_row;
      }
      if (temp->next_row) {
        Node<T>* toDelete = temp->next_row;
        temp->next_row = toDelete->next_row;
        delete toDelete;
      }
    }

    if (!cols[c]) return;

    if (cols[c]->pos_row == r) {
      Node<T>* temp = cols[c];
      cols[c] = cols[c]->next_col;
      delete temp;
    } else {
      Node<T>* temp = cols[c];
      while (temp->next_col && temp->next_col->pos_row != r) {
        temp = temp->next_col;
      }
      if (temp->next_col) {
        Node<T>* toDelete = temp->next_col;
        temp->next_col = toDelete->next_col;
        delete toDelete;
      }
    }
  }

  T get(int r, int c) {
    Node<T>* temp = rows[r];
    while (temp && temp->pos_col != c) {
      temp = temp->next_row;
    }
    return temp ? temp->data : T();
  }

  bool compare(SparseMatrix<T>& other) {
    if (n_rows != other.n_rows || n_cols != other.n_cols) return false;

    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp1 = rows[i];
      Node<T>* temp2 = other.rows[i];
      while (temp1 && temp2) {
        if (temp1->pos_col != temp2->pos_col || temp1->data != temp2->data) return false;
        temp1 = temp1->next_row;
        temp2 = temp2->next_row;
      }
      if (temp1 || temp2) return false;
    }
    return true;
  }

  SparseMatrix<T> add(SparseMatrix<T>& other) {
    SparseMatrix<T> result(n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp1 = rows[i];
      Node<T>* temp2 = other.rows[i];
      while (temp1 || temp2) {
        if (temp1 && (!temp2 || temp1->pos_col < temp2->pos_col)) {
          result.insert(temp1->pos_row, temp1->pos_col, temp1->data);
          temp1 = temp1->next_row;
        } else if (temp2 && (!temp1 || temp2->pos_col < temp1->pos_col)) {
          result.insert(temp2->pos_row, temp2->pos_col, temp2->data);
          temp2 = temp2->next_row;
        } else {
          result.insert(temp1->pos_row, temp1->pos_col, temp1->data + temp2->data);
          temp1 = temp1->next_row;
          temp2 = temp2->next_row;
        }
      }
    }
    return result;
  }

  SparseMatrix<T> subtract(SparseMatrix<T>& other) {
    SparseMatrix<T> result(n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp1 = rows[i];
      Node<T>* temp2 = other.rows[i];
      while (temp1 || temp2) {
        if (temp1 && (!temp2 || temp1->pos_col < temp2->pos_col)) {
          result.insert(temp1->pos_row, temp1->pos_col, temp1->data);
          temp1 = temp1->next_row;
        } else if (temp2 && (!temp1 || temp2->pos_col < temp1->pos_col)) {
          result.insert(temp2->pos_row, temp2->pos_col, -temp2->data);
          temp2 = temp2->next_row;
        } else {
          result.insert(temp1->pos_row, temp1->pos_col, temp1->data - temp2->data);
          temp1 = temp1->next_row;
          temp2 = temp2->next_row;
        }
      }
    }
    return result;
  }

  SparseMatrix<T> transpose() {
    SparseMatrix<T> result(n_cols, n_rows);

    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp = rows[i];
      while (temp) {
        result.insert(temp->pos_col, temp->pos_row, temp->data);
        temp = temp->next_row;
      }
    }
    return result;
  }

  SparseMatrix<T> multiply(SparseMatrix<T>& other) {
    SparseMatrix<T> result(n_rows, other.n_cols);

    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp1 = rows[i];
      while (temp1) {
        Node<T>* temp2 = other.cols[temp1->pos_col];
        while (temp2) {
          result.insert(i, temp2->pos_col, result.get(i, temp2->pos_col) + temp1->data * temp2->data);
          temp2 = temp2->next_col;
        }
        temp1 = temp1->next_row;
      }
    }
    return result;
  }

  void display() {
    for (int i = 0; i < n_rows; ++i) {
      Node<T>* temp = rows[i];
      for (int j = 0; j < n_cols; ++j) {
        if (temp && temp->pos_col == j) {
          std::cout << temp->data << " ";
          temp = temp->next_row;
        } else {
          std::cout << "0 ";
        }
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  SparseMatrix<int> mat1(4, 4);
  mat1.insert(1, 1, 5);
  mat1.insert(1, 3, 1);
  mat1.insert(2, 2, 9);
  mat1.insert(4, 1, 3);
  mat1.insert(4, 4, 11);

  SparseMatrix<int> mat2(4, 4);
  mat2.insert(1, 1, 5);
  mat2.insert(1, 3, 1);
  mat2.insert(2, 2, 9);
  mat2.insert(4, 1, 3);
  mat2.insert(4, 4, 11);

  SparseMatrix<int> result = mat1.add(mat2);

  // Display results or further operations as needed.
  mat1.display() ;

  return 0;
}
