#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
// Definition for a binary tree node.

template <class T>
struct Node {
    T val;
    Node *next;
};

template <class T>
class Queue {
    Node<T> *front;
    Node<T> *rear;
    int nodes;

public:

    Queue(): nodes(0) { front = rear = nullptr; }

    int size(){
      return nodes;
    }

    int _front(){
      return front->val;
    }

    int _rear(){
      return rear->val;
    }

    bool empty(){
        return (!front && !rear) ? true: false;
    }
    
    void enqueue(T ele){
      auto *temp = new Node<T>();
      temp->val = ele;
      temp->next = nullptr;

      if (empty())
        front = rear = temp;
      else {
        rear->next = temp;
        rear = temp;
      }
      nodes++;
    };

    void dequeue(){
      Node<T> *temp;
      int ele;
      if (empty())
        cout << endl << "Queue vacio." << endl;
      else {
        temp = front;
        // ele = temp->val;
        if (front == rear) rear = rear->next;
        front = front->next;
        delete temp;
        nodes--;
      }
      // return ele;
    };
    
    void display(){
      if (empty()) cout << endl <<"Queue vacio." << endl;
      else {
          auto *temp = front;
          while (temp) {
              cout << temp->val << endl;
              temp = temp->next;
          }
      }
    };
};



struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution
{
public:
  TreeNode *lcaDeepestLeaves(TreeNode *root)
  {
    Queue<TreeNode *> colita;
    vector<TreeNode *> v;
    colita.enqueue(root);
    if (root->left != nullptr && root->right != nullptr)
    {
      v.push_back(root);
      lcaDeepestLeaves(root->left);
      lcaDeepestLeaves(root->right);
      colita.dequeue();
    }
    else if (root->left == nullptr && root->right != nullptr)
    {
      v.push_back(root);
      lcaDeepestLeaves(root->right);
    }
    else if (root->right == nullptr && root->left != nullptr)
    {
      v.push_back(root);
      lcaDeepestLeaves(root->left);
    }
    return v[v.size() - 1];
  }
};
void test()
{
  TreeNode *nodo_a = new TreeNode(3);
  TreeNode *nodo_b = new TreeNode(5);
  TreeNode *nodo_c = new TreeNode(1);
  TreeNode *nodo_d = new TreeNode(6);
  TreeNode *nodo_e = new TreeNode(2);
  TreeNode *nodo_f = new TreeNode(0);
  TreeNode *nodo_g = new TreeNode(8);
  TreeNode *nodo_h = new TreeNode(7);
  TreeNode *nodo_i = new TreeNode(4);
  nodo_a->left = nodo_b;
  nodo_a->right = nodo_c;
  nodo_b->left = nodo_d;
  nodo_b->right = nodo_e;
  nodo_c->left = nodo_f;
  nodo_c->right = nodo_g;
  nodo_e->left = nodo_h;
  nodo_e->right = nodo_i;
  assert(Solution().lcaDeepestLeaves(nodo_a) == nodo_e);
  // nodo_a = new TreeNode(0);
  // nodo_b = new TreeNode(1);
  // nodo_c = new TreeNode(3);
  // nodo_d = new TreeNode(2);
  // nodo_a->left = nodo_b;
  // nodo_a->right = nodo_c;
  // nodo_b->right = nodo_d;
  // assert(Solution().lcaDeepestLeaves(nodo_a) == nodo_d);
}

int main()
{
  // test();
  // return 0;
}