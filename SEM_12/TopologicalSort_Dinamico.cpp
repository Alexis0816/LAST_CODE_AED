#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

// Nodo principal para: Queue
template <class T>
struct Node{
  T val;
  Node<T> *next;
};

// QUEUE
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

template <typename TV, typename TE>
class Graph {
private:
  struct Edge;

  struct Vertex {
    TV data;
    list<Edge *> edges; // Lista de adyacencia
    int inDegree;       // Grado de entrada para el ordenamiento topológico
  };

  struct Edge {
    Vertex *from;
    Vertex *to;
    TE weight;
  };

  unordered_map<int, Vertex *> m_vertexes;

public:
  // Añadir un vértice al grafo
  void insertVertex(int id, TV data) {
    auto *vertex = new Vertex();
    vertex->data = data;
    vertex->inDegree = 0; // Inicialmente no tiene aristas entrantes
    m_vertexes[id] = vertex;
  }

  // Añadir una arista dirigida al grafo
  void createEdge(int fromId, int toId, TE weight) {
    auto fromVertex = m_vertexes[fromId];
    auto toVertex = m_vertexes[toId];

    if (fromVertex && toVertex) {
      auto *edge = new Edge();
      edge->from = fromVertex;
      edge->to = toVertex;
      edge->weight = weight;

      fromVertex->edges.push_back(edge);
      toVertex->inDegree++; // Incrementar el grado de entrada del vértice destino
    }
  }

  // Mostrar el grafo
  void displayGraph() {
    for (auto &[id, vertex] : m_vertexes) {
      cout << "Vertice " << id << " (" << vertex->data << ") -> ";
      for (auto edge : vertex->edges) {
        cout << "Arista al vertice " << findVertexId(edge->to) << " (" << edge->to->data << ") con peso " << edge->weight << "; ";
      }
      cout << endl;
    }
  }

  // Encontrar el ordenamiento topológico utilizando el algoritmo de Kahn
  int* topologicalSort(int& size) {
    int *result = new int[m_vertexes.size()];
    int index = 0;

    Queue<Vertex *> q;

    // Inicializar la cola con los vértices que tienen grado de entrada cero
    for (auto &[id, vertex] : m_vertexes) {
      if (vertex->inDegree == 0) {
        q.enqueue(vertex);
      }
    }

    while (!q.empty()) {
      auto vertex = q._front();
      q.dequeue();
      result[index++] = findVertexId(vertex);

      // Procesar todos los vértices adyacentes
      for (auto edge : vertex->edges) {
        auto adjVertex = edge->to;
        adjVertex->inDegree--;

        if (adjVertex->inDegree == 0) {
          q.enqueue(adjVertex);
        }
      }
    }

    // Verificar si se encontró un ordenamiento topológico válido
    if (index != m_vertexes.size()) {
      cout << "El grafo contiene ciclos, no es un DAG." << endl;
      delete[] result; // Liberar memoria si no es un DAG (Directed Acyclic Graph - Grafo Dirigido Acíclico)
      size = 0;
      return nullptr;
    }

    size = index;
    return result;
  }

private:
  int findVertexId(Vertex *vertex) {
      for (auto &[id, v] : m_vertexes) {
          if (v == vertex) return id;
      }
      return -1;
  }
};

int main() {
  Graph<string, int> g;
  
  g.insertVertex(10, "A");
  g.insertVertex(2, "B");
  g.insertVertex(34, "C");
  g.insertVertex(4, "D");
  g.insertVertex(54, "E");
  g.insertVertex(6, "F");

  g.createEdge(10, 2, 1);
  g.createEdge(10, 34, 1);
  g.createEdge(2, 4, 1);
  g.createEdge(4, 6, 1);
  g.createEdge(34, 54, 1);

  cout << endl << "Grafo Original:" << endl;
  g.displayGraph();

  cout << endl << "Ordenamiento Topologico:" << endl;
  int size = 0;
  int *topoSort = g.topologicalSort(size);
  for (int i = 0; i < size; ++i) {
    cout << topoSort[i] << " ";
  }
  cout << endl << endl;

  delete[] topoSort; // Liberar memoria asignada al arreglo dinámico

  return 0;
}
