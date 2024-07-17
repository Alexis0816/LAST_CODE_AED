#include <iostream>
#include <vector>
using namespace std;

// Nodo principal para: Queue
template <class T>
struct Node
{
  T val;
  Node<T> *next;
};

// QUEUE - BFS
template <class T>
class Queue
{
private:
  Node<T> *front;
  Node<T> *rear;
  int nodes;

public:
  Queue() : nodes(0) { front = rear = nullptr; }

  int size()
  {
    return nodes;
  }

  T _front()
  {
    return front->val;
  }

  T _rear()
  {
    return rear->val;
  }

  bool empty()
  {
    return (!front && !rear) ? true : false;
  }

  void enqueue(T ele)
  {
    auto *temp = new Node<T>();
    temp->val = ele;
    temp->next = nullptr;

    if (empty())
      front = rear = temp;
    else
    {
      rear->next = temp;
      rear = temp;
    }
    nodes++;
  }

  void dequeue()
  {
    Node<T> *temp;
    if (empty())
      cout << endl
           << "Queue vacio." << endl;
    else
    {
      temp = front;
      if (front == rear)
        rear = rear->next; // if length of queue is 1;
      front = front->next;
      delete temp; // Add this line to avoid memory leak
      nodes--;
    }
  }
};

class Solution
{
  public:
  bool isBipartite(vector<vector<int>> &graph)
  {
    int n = graph.size();
    vector<int> color(n, -1); // -1 significa no color, 0 and 1 are the two colors
    // -1 significa sin colorear, 0 and 1 son 2 colores

    for (int start = 0; start < n; ++start)
    {
      if (color[start] == -1)
      { // Si el vértice no está coloreado
        Queue<int> q;
        q.enqueue(start);
        color[start] = 0; // default color 0 xd

        while (!q.empty())
        {
          int node = q._front();
          q.dequeue();

          for (int neighbor : graph[node])
          {
            if (color[neighbor] == -1)
            {
              // Si el vecino no está coloreado, coloreo color opuesto
              color[neighbor] = 1 - color[node];
              q.enqueue(neighbor);
            }
            else if (color[neighbor] == color[node])
            {
              return false; // Si el vecino tiene el mismo color, el grafo no es bipartito
            }
          }
        }
      }
    }

    return true;
  }
};

int main()
{
  Solution s;

  vector<vector<int>> graph = {
      {1, 2, 3},
      {0, 2},
      {0, 1, 3},
      {0, 2}};
  
  cout << s.isBipartite(graph) << endl;

  vector<vector<int>> graph2 = {
      {1, 3},
      {0, 2},
      {1, 3},
      {0, 2}};

  cout << s.isBipartite(graph2) << endl;

  return 0;
}