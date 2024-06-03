#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

template <typename TV, typename TE>
class Graph
{
private:
  struct Edge; // predeclaro la estructura de la arista

  struct Vertex
  {
    TV data;
    list<Edge *> edges; // lista de adyacencia
    Vertex(TV val) : data(val) {}
  };

  struct Edge
  {
    Vertex *vertex1;
    Vertex *vertex2;
  };

  unordered_map<int, Vertex *> m_vertexes;

public:
  // añado un vértice al grafo
  void insertVertex(int id, TV data)
  {
    auto *vertex = new Vertex{data};
    m_vertexes[id] = vertex;
  }

  // añado una arista no dirigida al grafo
  void createEdge(int id1, int id2)
  {
    auto vertex1 = m_vertexes[id1];
    auto vertex2 = m_vertexes[id2];

    if (vertex1 && vertex2)
    {
      auto *edge = new Edge();
      edge->vertex1 = vertex1;
      edge->vertex2 = vertex2;

      vertex1->edges.push_back(edge);
      vertex2->edges.push_back(edge);
    }
  }

  // Función para encontrar el centro del grafo estrella
  int findCenter()
  {
    unordered_map<int, int> count;

    // contamos las apariciones de cada nodo
    for (auto &[id, vertex] : m_vertexes)
      count[id] = vertex->edges.size();

    // buscamos el nodo que aparece en todas las aristas (n-1 veces)
    for (auto &[node, cnt] : count)
    {
      if (cnt == m_vertexes.size() - 1)
        return node;
    }

    // si no se encuentra retornamos -1, pero al final del problema se menciona -> Las aristas dadas representan un grafo estrella válido (en caso de que no)
    return -1;
  }
};

class Solution
{
private:
  Graph<int, int> g;

public:
  int problem3(vector<vector<int>> &edges)
  {
    unordered_set<int> vertices; // inserción única de vértices en el grafo de manera eficiente

    // inserto vértices y crear aristas según el vector -> edges
    for (auto &edge : edges)
    {
      int id1 = edge[0];
      int id2 = edge[1];

      // inserto vértices solo si no se han insertado previamente
      if (vertices.find(id1) == vertices.end())
      {
        g.insertVertex(id1, id1);
        vertices.insert(id1);
      }

      if (vertices.find(id2) == vertices.end())
      {
        g.insertVertex(id2, id2);
        vertices.insert(id2);
      }

      // creo la arista con los vértices
      g.createEdge(id1, id2);
    }

    return g.findCenter();
  }
};

// TESTS

/*
int main()
{
  Solution sol;
  vector<vector<int>> edges = {{1, 2}, {2, 3}, {4, 2}};
  int center = sol.problem3(edges);
  cout << "El centro del grafo estrella es: " << center << endl; // Output should be 2

  vector<vector<int>> edges2 = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};
  int center2 = sol.problem3(edges2);
  cout << "El centro del grafo estrella es: " << center2 << endl; // Output should be 1

  return 0;
}
*/