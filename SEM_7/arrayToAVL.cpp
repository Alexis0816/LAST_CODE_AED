#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;

struct TreeNode
{
  int val;
  TreeNode *left;
  TreeNode *right;
  int height; // Altura del nodo en el árbol AVL

  TreeNode() : val(0), left(nullptr), right(nullptr), height(1) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right), height(1) {}
};

class Solution
{
public:
  TreeNode *arrayToAVL(vector<int> &array)
  {
    if (array.empty())
      return nullptr;

    sort(array.begin(), array.end()); // ordenamos el array

    return constructAVL(array, 0, array.size() - 1);
  }

  TreeNode *constructAVL(vector<int> &array, int start, int end)
  {
    if (start > end) // no hay elementos en el array actual
      return nullptr;

    int mid = start + (end - start) / 2;       // dividimos en 2 partes aprox. iguales
    TreeNode *root = new TreeNode(array[mid]); // la raíz será el nodo del medio
    root->left = constructAVL(array, start, mid - 1);
    root->right = constructAVL(array, mid + 1, end);
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalance(root);

    // casos de rotación
    // Rotación derecha
    if (balance > 1 && array[mid] < root->left->val)
      return rotateRight(root);

    // Rotación izquierda
    if (balance < -1 && array[mid] > root->right->val)
      return rotateLeft(root);

    // Rotación izquierda-derecha
    if (balance > 1 && array[mid] > root->left->val)
    {
      root->left = rotateLeft(root->left);
      return rotateRight(root);
    }

    // Rotación derecha-izquierda
    if (balance < -1 && array[mid] < root->right->val)
    {
      root->right = rotateRight(root->right);
      return rotateLeft(root);
    }

    return root;
  }

  // altura de cada nodo
  int getHeight(TreeNode *node)
  {
    if (node == nullptr)
      return 0;
    return node->height;
  }

  // halla el factor de equilibrio
  int getBalance(TreeNode *node)
  {
    if (node == nullptr)
      return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  TreeNode *rotateRight(TreeNode *y)
  {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
  }

  TreeNode *rotateLeft(TreeNode *x)
  {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
  }
};

// ordenar
vector<int> levelOrder(TreeNode *root)
{
  vector<int> vec;
  if (root == nullptr)
    return vec;

  queue<TreeNode *> q;
  q.push(root);

  while (!q.empty())
  {
    TreeNode *node = q.front();
    vec.push_back(node->val);
    q.pop();
    if (node->left != nullptr)
      q.push(node->left);
    if (node->right != nullptr)
      q.push(node->right);
  }
  return vec;
}

int main()
{
  // case 1
  vector<int> array = {2, 4, 1, 3, 5, 6, 7};
  vector<int> expected = {4, 2, 6, 1, 3, 5, 7};
  
  // case 2
  // vector<int> array = {8, 10, 15, 25, 49, 56, 60, 64, 75, 89, 100};
	// vector<int> expected = {56, 15, 75, 8, 25, 60, 89, 10, 49, 64, 100};
  
  vector<int> ans = levelOrder(Solution().arrayToAVL(array));


  for (auto e : ans)
    cout << e << " ";
  cout << endl;

  return 0;
}
