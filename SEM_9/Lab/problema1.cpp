#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

template <typename TV, typename TE>
class Graph
{
private:
  struct Edge; 

  struct Vertex
  {
    TV data;
    list<Edge *> edges;
  };

  struct Edge
  {
    Vertex *origin;
    Vertex *destination;
    TE weight;
  };

  unordered_map<int, Vertex *> m_vertices;

public:
  void insertVertex(int id, TV data)
  {
    auto *vertex = new Vertex();
    vertex->data = data;
    m_vertices[id] = vertex;
  }

  // añado una arista "dirigida" al grafo
  void createEdge(int originId, int destinationId, TE weight)
  {
    auto origin = m_vertices[originId];
    auto destination = m_vertices[destinationId];

    if (origin && destination){
      auto *edge = new Edge();
      edge->origin = origin;
      edge->destination = destination;
      edge->weight = weight;

      origin->edges.push_back(edge);
    }
  }

  // devuelve el vértice con la etiqueta dada
  Vertex *getVertex(int id){ return m_vertices[id]; }
};

class Solution
{
private:
  Graph<int, int> g;

public:
  int problem1(int n, vector<vector<int>> &trust){
    // agrego vértices al grafo para etiquetas de personas de 1 a n
    for (int i = 1; i <= n; ++i) g.insertVertex(i, i);

    // agrego aristas al grafo según las relaciones de confianza
    for (const auto &relation : trust) g.createEdge(relation[0], relation[1], 1); // Asumiendo peso 1 para todas las relaciones de confianza

    // Contador de confianza para cada persona
    vector<int> trusted_count(n + 1, 0); // Inicializar el contador de confianza para cada persona

    for (const auto &relation : trust) trusted_count[relation[1]]++; // Incrementar el contador para la persona confiada (bi)

    // Encontrar al juez del pueblo
    for (int i = 1; i <= n; ++i){
      if (trusted_count[i] == n - 1) { // Si una persona es confiada por todas las demás
        bool is_judge = true;
        auto vertex = g.getVertex(i);
        for (auto &edge : vertex->edges){
          if (edge->origin->data == i) { // Verificar si esa persona no confía en nadie (no tiene relaciones de confianza salientes)
            is_judge = false;
            break;
          }
        }
        if (is_judge) return i; // Devolver la etiqueta del juez del pueblo
      }
    }
    return -1; // Si no se encuentra ningún juez del pueblo
  }
};

int main()
{
  Solution sol;

  // Caso de prueba
  int n = 2;
  vector<vector<int>> trust = {{1, 2}};
  cout << "Resultado para el caso de prueba: " << sol.problem1(n, trust) << endl; // Salida esperada: 2

  int n2 = 3;
  vector<vector<int>> trust2 = {{1, 3}, {2, 3}};
  cout << "Resultado para el caso de prueba: " << sol.problem1(n2, trust2) << endl; // Salida esperada: 3

  int n3 = 3;
  vector<vector<int>> trust3 = {{1, 3}, {2, 3}, {3, 1}};
  cout << "Resultado para el caso de prueba: " << sol.problem1(n3, trust3) << endl; // Salida esperada: -1

  return 0;
}
