#include <iostream>
#include <list> // double linked list
#include <unordered_map> // key-value -> HashTable
#include <vector>
using namespace std;

// Nodo principal para: Stack & Queue
template <class T>
struct Node{
  T val;
  Node<T> *next;
};

// STACK - DFS
template <class T>
class Stack{
private:
  Node<T> *head;
  int nodes;

public:
  Stack() : head(nullptr), nodes(0){}

  int size(){
    return  nodes;
  }

  bool empty(){
    return !head;
  }

  T top(){
    return head->val;
  }

  void push(T x){
    auto *newNode = new Node<T>;
    newNode->val = x;
    (empty())? newNode->next = nullptr : newNode->next = head;
    
    head = newNode;
    nodes++;
  }

  void pop(){
    if (empty()) cout << endl << "Stack vacío" << endl;
    else{
      auto *temp = head;
      head = head->next;
      delete temp;
      nodes--;
    }
  }
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
        rear = rear->next; // if length of queue is 1;
      front = front->next;
      delete temp; // Add this line to avoid memory leak
      nodes--;
    }
  }
};

// DisjoinSet - para almacenar nodos visitados y no repetirlos
template <typename T>
class DisjoinSet{
private:
    unordered_map<T, T> parent;
    unordered_map<T, int> rank;

public:
    DisjoinSet() = default;

    void Makeset(T x)
    {
        parent[x] = x;
        rank[x] = 0;
    };

    T Find(T x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void mark_visited(T x) {
        if (parent.find(x) == parent.end()) {
            Makeset(x);
        }
    }

    bool is_visited(T x) {
        return parent.find(x) != parent.end();
    }
};

// GRAFO
template <typename TV, typename TE>
class Graph{
private:
  struct Edge;

  struct Vertex{
    TV data;
    list <Edge *> edges; // Lista de adyacencia
  };

  struct Edge{
    Vertex *vertex1;
    Vertex *vertex2;
    TE weight;
  };

  unordered_map<int, Vertex *> m_vertexes;

public:
  // Añadir un vértice al grafo
  void insertVertex(int id, TV data){
    auto* vertex = new Vertex();
    vertex->data = data;
    m_vertexes[id] = vertex;
  }

  // Añadir una arista no dirigida al grafo
  void createEdge(int id1, int id2, TE weight){
    auto vertex1 = m_vertexes[id1];
    auto vertex2 = m_vertexes[id2];

    if (vertex1 && vertex2){
      auto* edge = new Edge();
      edge->vertex1 = vertex1;
      edge->vertex2 = vertex2;
      edge->weight = weight;

      vertex1->edges.push_back(edge);
      vertex2->edges.push_back(edge);
    }
  }

  // Mostrar el grafo
  void displayGraph(){
    cout << "GRAFO:" << endl;
    for (auto [id, vertex] : m_vertexes){ 
      cout << "Vertice " << id << " (" << vertex->data << ") -> ";
      for (auto edge : vertex->edges){
        cout << "Arista al vertice " << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << " con peso " << edge->weight << "; ";
      }
      cout << endl;
    } cout << endl;
  }

  // Recorrido por anchura (BFS)
  // O(V+E)
  void BFS(int startId) {
    if (m_vertexes.find(startId) == m_vertexes.end()) return;

    DisjoinSet<Vertex *> visited;
    Queue<Vertex *> q;

    auto startVertex = m_vertexes[startId];
    visited.mark_visited(startVertex);
    q.enqueue(startVertex);

    while (!q.empty()) {
      auto vertex = q._front();
      q.dequeue();
      cout << vertex->data << " ";

      for (auto edge : vertex->edges) {
        auto adjVertex = edge->vertex1 == vertex ? edge->vertex2 : edge->vertex1;
        if (!visited.is_visited(adjVertex)) {
          visited.mark_visited(adjVertex);
          q.enqueue(adjVertex);
        }
      }
    }
    cout << endl;
  }

  // Recorrido por profundidad (DFS)
  // O(V+E)
  void DFS(int startId) {
    if (m_vertexes.find(startId) == m_vertexes.end()) return;

    DisjoinSet<Vertex *> visited; // conjunto de vértices visitados
    Stack<Vertex *> s;

    auto startVertex = m_vertexes[startId];
    visited.mark_visited(startVertex);
    s.push(startVertex);

    while (!s.empty()) {
      auto vertex = s.top();
      s.pop();
      cout << vertex->data << " ";

      for (auto edge : vertex->edges) {
        auto adjVertex = edge->vertex1 == vertex ? edge->vertex2 : edge->vertex1;
        if (!visited.is_visited(adjVertex)) {
          visited.mark_visited(adjVertex);
          s.push(adjVertex);
        }
      }
    }
    cout << endl;
  }
};

int main() {
  Graph<char, int> g;

  g.insertVertex(1, 'A');
  g.insertVertex(2, 'B');
  g.insertVertex(3, 'C');
  g.insertVertex(4, 'D');
  g.insertVertex(5, 'E');

  g.createEdge(1, 2, 1);
  g.createEdge(1, 3, 1);
  g.createEdge(2, 4, 1);
  g.createEdge(3, 5, 1);

  // // Añadir vértices
  // g.insertVertex(1, 'J');
  // g.insertVertex(2, 'F');
  // g.insertVertex(3, 'C');
  // g.insertVertex(4, 'D');
  // g.insertVertex(5, 'A');
  // g.insertVertex(6, 'H');
  // g.insertVertex(7, 'B');
  // g.insertVertex(8, 'E');
  // g.insertVertex(9, 'G');
  // g.insertVertex(10, 'I');

  // // Añadir aristas
  // g.createEdge(1, 2, 4);   // J - F | 4
  // g.createEdge(2, 3, 7);   // F - C | 7
  // g.createEdge(3, 4, 11);  // C - D | 11
  // g.createEdge(2, 4, 58);  // F - D | 58
  // g.createEdge(2, 5, 17);  // F - A | 17
  // g.createEdge(1, 5, 14);  // J - A | 14
  // g.createEdge(3, 6, 24);  // C - H | 24
  // g.createEdge(4, 5, 42);  // D - A | 42
  // g.createEdge(1, 8, 5);   // J - E | 5
  // g.createEdge(4, 6, 26);  // D - H | 26
  // g.createEdge(4, 7, 19);  // D - B | 19
  // g.createEdge(5, 7, 5);   // A - B | 5
  // g.createEdge(5, 8, 11);  // A - E | 11
  // g.createEdge(6, 7, 64);  // H - B | 64
  // g.createEdge(8, 10, 29); // E - I | 29
  // g.createEdge(6, 9, 3);   // H - G | 3
  // g.createEdge(7, 9, 52);  // B - G | 52
  // g.createEdge(7, 10, 51); // B - I | 51
  // g.createEdge(10, 9, 33); // I - G | 33

  g.displayGraph();

  cout << "BFS comenzando desde el vertice A: " << endl; 
  g.BFS(1);

  cout << "DFS comenzando desde el vertice A: " << endl; 
  g.DFS(1);

  return 0;
}
