#include <iostream>
#include <list> // double linked list
#include <unordered_map> // key-value
#include <queue> // para el recorrido por anchura - BFS
#include <stack> // para el recorrido por profundidad - DFS
#include <set> // para almacenar nodos visitados
using namespace std;

template <typename TV, typename TE>
class Graph
{
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
    }
  }

  // Recorrido por anchura (BFS)
  void BFS(int startId) {
    if (m_vertexes.find(startId) == m_vertexes.end()) return;

    set<Vertex *> visited;
    queue<Vertex *> q;

    auto startVertex = m_vertexes[startId];
    visited.insert(startVertex);
    q.push(startVertex);

    while (!q.empty()) {
      auto vertex = q.front();
      q.pop();
      cout << vertex->data << " ";

      for (auto edge : vertex->edges) {
        auto adjVertex = edge->vertex1 == vertex ? edge->vertex2 : edge->vertex1;
        if (visited.find(adjVertex) == visited.end()) {
          visited.insert(adjVertex);
          q.push(adjVertex);
        }
      }
    }
    cout << endl;
  }

  // Recorrido por profundidad (DFS)
  void DFS(int startId) {
    if (m_vertexes.find(startId) == m_vertexes.end()) return;

    set<Vertex *> visited;
    stack<Vertex *> s;

    auto startVertex = m_vertexes[startId];
    s.push(startVertex);

    while (!s.empty()) {
      auto vertex = s.top();
      s.pop();

      if (visited.find(vertex) == visited.end()) {
        cout << vertex->data << " ";
        visited.insert(vertex);

        for (auto edge : vertex->edges) {
          auto adjVertex = edge->vertex1 == vertex ? edge->vertex2 : edge->vertex1;
          if (visited.find(adjVertex) == visited.end()) {
            s.push(adjVertex);
          }
        }
      }
    }
    cout << endl;
  }
};

int main() {
  Graph<string, int> g;

  g.insertVertex(1, "A");
  g.insertVertex(2, "B");
  g.insertVertex(3, "C");
  g.insertVertex(4, "D");
  g.insertVertex(5, "E");

  g.createEdge(1, 2, 1);
  g.createEdge(1, 3, 1);
  g.createEdge(2, 4, 1);
  g.createEdge(3, 5, 1);

  g.displayGraph();

  cout << "BFS comenzando desde el vertice A: " << endl; 
  g.BFS(1);

  cout << "DFS comenzando desde el vertice A: " << endl; 
  g.DFS(1);

  return 0;
}

