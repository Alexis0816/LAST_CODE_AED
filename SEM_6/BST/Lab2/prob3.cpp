#include <iostream>
#include <vector>
using namespace std;

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
  TreeNode *root = nullptr;

  void insert(TreeNode *&root, int data)
  {
    if (root == nullptr)
    {
      root = new TreeNode(data);
    }

    else if (root->val < data)
    {
      insert(root->right, data);
    }
    else if (root->val > data)
    {
      insert(root->left, data);
    }

    // else
    //{
    //     (root->val < data) ? insert(root->right, data) : insert(root->left, data);
    // }
  }

public:
  void insert(int data)
  {
    insert(this->root, data);
  }

  TreeNode *bstFromPreorder(vector<int> &preorder)
  {
    for (auto e : preorder)
    {
      insert(e);
    }

    return root;
  }
};

int main()
{
  vector<int> po = {8, 5, 1, 7, 10, 12};

  Solution s;

  cout << s.bstFromPreorder(po)->val << endl; // 8

  // hijos de la raÃz con valor 8
  cout << s.bstFromPreorder(po)->left->val << endl;  // 5
  cout << s.bstFromPreorder(po)->right->val << endl; // 10

  // hijos del nodo valor 5
  cout << s.bstFromPreorder(po)->left->left->val << endl;  // 1
  cout << s.bstFromPreorder(po)->left->right->val << endl; // 7

  // hijo del nodo valor 10
  cout << s.bstFromPreorder(po)->right->right->val << endl; // 12

  return 0;
}