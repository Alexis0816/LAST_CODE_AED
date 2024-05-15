#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <cmath>
#include <algorithm>
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
public:
  TreeNode *balanceBST(TreeNode *root)
  {
    if (!root)
      return nullptr;

    vector<int> nodes;
    // Realizamos un recorrido en anchura para obtener todos los nodos del árbol
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
      int levelSize = q.size();
      while (levelSize--)
      {
        TreeNode *curr = q.front();
        q.pop();
        nodes.push_back(curr->val);
        if (curr->left)
          q.push(curr->left);
        if (curr->right)
          q.push(curr->right);
      }
    }

    // ordenamos
    sort(nodes.begin(), nodes.end());

    // Construimos un árbol balanceado usando los valores ordenados
    return buildTree(nodes, 0, nodes.size() - 1);
  }

  TreeNode *buildTree(vector<int> &nodes, int start, int end)
  {
    if (start > end)
      return nullptr;

    int mid = start + (end - start) / 2;
    TreeNode *root = new TreeNode(nodes[mid]);
    root->left = buildTree(nodes, start, mid - 1);
    root->right = buildTree(nodes, mid + 1, end);
    return root;
  }
};

int main()
{
  TreeNode *nodo_a = new TreeNode(1);
  TreeNode *nodo_b = new TreeNode(2);
  TreeNode *nodo_c = new TreeNode(3);
  TreeNode *nodo_d = new TreeNode(4);
  nodo_a->right = nodo_b;
  nodo_b->right = nodo_c;
  nodo_c->right = nodo_d;

  TreeNode *balancedRoot = Solution().balanceBST(nodo_a);

  cout << balancedRoot->left->val <<endl;
  cout << balancedRoot->right->val <<endl;
  cout << balancedRoot->right->right->val <<endl;

  return 0;
}
