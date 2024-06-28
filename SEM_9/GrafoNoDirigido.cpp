#include <iostream>
#include <list> // Doubly linked list
#include <unordered_map> // key-value
using namespace std;

template <typename TV, typename TE>
class Graph{
private:
  struct Edge; // Predeclaración de la estructura Edge

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
    for (auto [id, vertex] : m_vertexes){ cout << "Vertice " << id << " (" << vertex->data << ") -> ";
      for (auto edge : vertex->edges){
        cout << "Arista al vertice " << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << " con peso " << edge->weight << "; ";
      }
      cout << endl;
    }
  }
};

// Graph: Esta clase representa un grafo no dirigido.

// Vertex: Es una estructura que contiene los datos del vértice y una lista de aristas (edges) que conectan este vértice con otros vértices.
// Edge: Es una estructura que representa una arista, conteniendo punteros a los vértices que conecta (vertex1 y vertex2) y el peso de la arista (weight).
// m_vertexes: Es un unordered_map que mapea IDs de vértices a sus respectivos objetos Vertex.
// insertVertex: Este método inserta un vértice en el grafo con un ID y datos data.

// createEdge: Este método crea una arista no dirigida entre dos vértices dados por sus IDs (id1 y id2) con un peso weight. La arista se añade tanto a la lista de aristas del vertex1 como del vertex2.

// displayGraph: Este método imprime en consola la representación del grafo, mostrando cada vértice y sus aristas con los respectivos pesos.

int main()
{
  Graph<char, int> graph;

  // Añadir vértices
  graph.insertVertex(1, 'J');
  graph.insertVertex(2, 'F');
  graph.insertVertex(3, 'C');
  graph.insertVertex(4, 'D');
  graph.insertVertex(5, 'A');
  graph.insertVertex(6, 'H');
  graph.insertVertex(7, 'B');
  graph.insertVertex(8, 'E');
  graph.insertVertex(9, 'G');
  graph.insertVertex(10, 'I');

  // Añadir aristas
  graph.createEdge(1, 2, 4);   // J - F | 4
  graph.createEdge(2, 3, 7);   // F - C | 7
  graph.createEdge(3, 4, 11);  // C - D | 11
  graph.createEdge(2, 4, 58);  // F - D | 58
  graph.createEdge(2, 5, 17);  // F - A | 17
  graph.createEdge(1, 5, 14);  // J - A | 14
  graph.createEdge(3, 6, 24);  // C - H | 24
  graph.createEdge(4, 5, 42);  // D - A | 42
  graph.createEdge(1, 8, 5);   // J - E | 5
  graph.createEdge(4, 6, 26);  // D - H | 26
  graph.createEdge(4, 7, 19);  // D - B | 19
  graph.createEdge(5, 7, 5);   // A - B | 5
  graph.createEdge(5, 8, 11);  // A - E | 11
  graph.createEdge(6, 7, 64);  // H - B | 64
  graph.createEdge(8, 10, 29); // E - I | 29
  graph.createEdge(6, 9, 3);   // H - G | 3
  graph.createEdge(7, 9, 52);  // B - G | 52
  graph.createEdge(7, 10, 51); // B - I | 51
  graph.createEdge(10, 9, 33); // I - G | 33

  // Mostrar el grafo
  graph.displayGraph();

  return 0;
}
