// árbol binario
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <class T>
struct Node{
  T data;
  Node *left;
  Node *right;
  Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <class T>
class BSTree{
public:
  // BreadthFirstSearch
  void displayBFS(Node<int> *&root)
  {
    if (root == nullptr)
      throw "arbol vacio";

    queue<Node<int> *> QUEUE;
    QUEUE.push(root);
    while (QUEUE.size() != 0)
    {
      Node<int> *nodo = QUEUE.front();
      cout << nodo->data << " ";
      QUEUE.pop();

      if (nodo->left != nullptr)
        QUEUE.push(nodo->left);
      if (nodo->right != nullptr)
        QUEUE.push(nodo->right);
    }
  }
};

int main()
{
  Node<int>* root = new Node(3);
  Node<int>* a = new Node(9);
  Node<int>* b = new Node(20);
  Node<int>* c = new Node(15);
  Node<int>* d = new Node(7);
      
  root->left = a;
  root->right = b;
  b->left = c;
  b->right = d;

  BSTree<int> tree;

  cout << "BFS: ";
  tree.displayBFS(root);
  cout << endl;


  return 0;
}
