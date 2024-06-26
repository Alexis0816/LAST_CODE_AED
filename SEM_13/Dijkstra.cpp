#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
using namespace std;

template <typename T>
class MinHeap
{
private:
  struct Node
  {
    T data;
    Node *left;
    Node *right;
    Node(T data) : data(data), left(nullptr), right(nullptr) {}
  };

  Node *root;

  Node *insert(Node *root, T data)
  {
    if (root == nullptr)
    {
      return new Node(data);
    }

    if (data < root->data)
    {
      root->left = insert(root->left, data);
    }
    else
    {
      root->right = insert(root->right, data);
    }

    return root;
  }

  Node *findMin(Node *root)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    while (root->left != nullptr)
    {
      root = root->left;
    }

    return root;
  }

  Node *deleteMin(Node *root)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    if (root->left == nullptr)
    {
      Node *temp = root->right;
      delete root;
      return temp;
    }

    root->left = deleteMin(root->left);
    return root;
  }

  void heapifyUp(Node *node)
  {
    if (node == nullptr || node == root)
    {
      return;
    }

    if (node->left != nullptr && node->left->data < node->data)
    {
      swap(node->data, node->left->data);
      heapifyUp(node->left);
    }
    else if (node->right != nullptr && node->right->data < node->data)
    {
      swap(node->data, node->right->data);
      heapifyUp(node->right);
    }
  }

  void heapifyDown(Node *node)
  {
    if (node == nullptr)
    {
      return;
    }

    if (node->left != nullptr && node->left->data < node->data)
    {
      swap(node->data, node->left->data);
      heapifyDown(node->left);
    }
    else if (node->right != nullptr && node->right->data < node->data)
    {
      swap(node->data, node->right->data);
      heapifyDown(node->right);
    }
  }

public:
  MinHeap() : root(nullptr) {}

  void insert(T data)
  {
    root = insert(root, data);
    heapifyUp(root);
  }

  T extractMin()
  {
    if (root == nullptr)
    {
      throw "Heap vacío";
    }

    Node *minNode = findMin(root);
    T minData = minNode->data;
    root = deleteMin(root);
    heapifyDown(root);

    return minData;
  }

  bool isEmpty()
  {
    return root == nullptr;
  }
};

class Solution
{
public:
  int Dijkstra(vector<vector<int>> &heights)
  {
    int rows = heights.size();
    int cols = heights[0].size();

    vector<vector<int>> minEffort(rows, vector<int>(cols, INT_MAX));
    minEffort[0][0] = 0;

    MinHeap<tuple<int, int, int>> pq;
    pq.insert(make_tuple(0, 0, 0));

    vector<int> dirX = {-1, 1, 0, 0};
    vector<int> dirY = {0, 0, -1, 1};

    while (!pq.isEmpty())
    {
      auto [currentEffort, x, y] = pq.extractMin();

      if (x == rows - 1 && y == cols - 1)
      {
        return currentEffort;
      }

      for (int i = 0; i < 4; ++i)
      {
        int newX = x + dirX[i];
        int newY = y + dirY[i];

        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols)
        {
          int effort = max(currentEffort, abs(heights[newX][newY] - heights[x][y]));
          if (effort < minEffort[newX][newY])
          {
            minEffort[newX][newY] = effort;
            pq.insert(make_tuple(effort, newX, newY));
          }
        }
      }
    }

    return -1;
  }
};

int main()
{
  Solution sol;
  vector<vector<int>> heights = {{1, 2, 2},{3, 8, 2},{5, 3, 5}};
  cout << sol.Dijkstra(heights) << endl; // Output: 2


  vector<vector<int>> heights2 = {{1,2,3},{3,8,4},{5,3,5}};
  cout << sol.Dijkstra(heights2) << endl; // Output: 1

  return 0;
}
