#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Nodo principal para: Queue
template <class T>
struct Node{
  T val;
  Node<T> *next;
};

// QUEUE - BFS
template <class T>
class Queue{
private:  
  Node<T> *front;
  Node<T> *rear;
  int nodes;

public:
  Queue() : nodes(0) { front = rear = nullptr; }

  int size(){
    return nodes;
  }

  T _front(){
    return front->val;
  }

  T _rear(){
    return rear->val;
  }

  bool empty(){
    return (!front && !rear) ? true : false;
  }

  void enqueue(T ele){
    auto *temp = new Node<T>();
    temp->val = ele;
    temp->next = nullptr;

    if (empty()) front = rear = temp;
    else{
      rear->next = temp;
      rear = temp;
    }
    nodes++;
  }

  void dequeue(){
    Node<T> *temp;
    if (empty()) cout << endl << "Queue vacio." << endl;
    else{
      temp = front;
      if (front == rear)
        rear = rear->next; 
      front = front->next;
      delete temp;
      nodes--;
    }
  }
};

int shortestCycle(int n, vector<vector<int>>& edges) {
    // construimos el grafo usando listas de adyacencia
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
      graph[edge[0]].push_back(edge[1]);
      graph[edge[1]].push_back(edge[0]);
    }
    
    int shortest_cycle = INT_MAX;
    
    // función que ejecuta el BFS y encuentra el ciclo más corto (lambda)
    auto bfs = [&](int start) {
      vector<int> dist(n, INT_MAX);
      vector<int> parent(n, -1);
      Queue<int> q;
      
      q.enqueue(start);
      dist[start] = 0;
      
      while (!q.empty()) {
          int node = q._front();
          q.dequeue();
          
          for (int vec : graph[node]) {
            if (dist[vec] == INT_MAX) {
              dist[vec] = dist[node] + 1;
              parent[vec] = node;
              q.enqueue(vec);
            } else if (vec != parent[node]) {
              // Encontrar un ciclo
              shortest_cycle = min(shortest_cycle, dist[node] + dist[vec] + 1);
            }
          }
      }
    };
    
    // ejecuto BFS a cada nodo para encontrar el ciclo más corto
    for (int i = 0; i < n; ++i) {
        bfs(i);
    }
    
    return (shortest_cycle == INT_MAX) ? -1 : shortest_cycle;
}

int main() {
  int n = 7;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {3, 4}, {4, 5}, {5, 6}, {6, 3}};
  
  int result = shortestCycle(n, edges);
  
  cout << "La longitud del ciclo mas corto es: " << result << endl;
  
  return 0;
}
