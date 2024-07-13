#include <iostream>
#include <list>          // double linked list
#include <unordered_map> // key-value -> HashTable
#include <vector>
using namespace std;

// Nodo principal para: Stack
template <class T>
struct Node
{
  T val;
  Node<T> *next;
};

// STACK - DFS
template <class T>
class Stack
{
private:
  Node<T> *head;
  int nodes;

public:
  Stack() : head(nullptr), nodes(0) {}

  int size()
  {
    return nodes;
  }

  bool empty()
  {
    return !head;
  }

  T top()
  {
    return head->val;
  }

  void push(T x)
  {
    auto *newNode = new Node<T>;
    newNode->val = x;
    (empty()) ? newNode->next = nullptr : newNode->next = head;

    head = newNode;
    nodes++;
  }

  void pop()
  {
    if (empty())
      cout << endl << "Stack vacío" << endl;
    else
    {
      auto *temp = head;
      head = head->next;
      delete temp;
      nodes--;
    }
  }
};

// DisjoinSet - para almacenar nodos visitados y no repetirlos
template <typename T>
class DisjoinSet
{
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

  void mark_visited(T x)
  {
    if (parent.find(x) == parent.end())
    {
      Makeset(x);
    }
  }

  bool is_visited(T x)
  {
    return parent.find(x) != parent.end();
  }

  void clear()
  {
    parent.clear();
    rank.clear();
  }
};

// GRAFO
template <typename TV, typename TE>
class Graph
{
private:
  struct Edge;

  struct Vertex
  {
    TV data;
    list<Edge *> edges; // Lista de adyacencia
  };

  struct Edge
  {
    Vertex *vertex1;
    Vertex *vertex2;
    TE weight;
  };

  unordered_map<int, Vertex *> m_vertexes;
  DisjoinSet<Vertex *> visited; // conjunto de vértices visitados

public:
  // Añadir un vértice al grafo
  void insertVertex(int id, TV data)
  {
    auto *vertex = new Vertex();
    vertex->data = data;
    m_vertexes[id] = vertex;
  }

  // Añadir una arista no dirigida al grafo
  void createEdge(int id1, int id2, TE weight)
  {
    auto vertex1 = m_vertexes[id1];
    auto vertex2 = m_vertexes[id2];

    if (vertex1 && vertex2)
    {
      auto *edge = new Edge();
      edge->vertex1 = vertex1;
      edge->vertex2 = vertex2;
      edge->weight = weight;

      vertex1->edges.push_back(edge);
      vertex2->edges.push_back(edge);
    }
  }

  // Mostrar el grafo
  void displayGraph()
  {
    cout << "GRAFO:" << endl;
    for (auto [id, vertex] : m_vertexes)
    {
      cout << "Vertice " << id << " (" << vertex->data << ") -> ";
      for (auto edge : vertex->edges)
      {
        cout << "Arista al vertice " << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << " con peso " << edge->weight << "; ";
      }
      cout << endl;
    }
    cout << endl;
  }

  // Recorrido por profundidad (DFS)
  // O(V+E)
  void DFS(int startId)
  {
    if (m_vertexes.find(startId) == m_vertexes.end())
      return;

    Stack<Vertex *> s;

    auto startVertex = m_vertexes[startId];
    visited.mark_visited(startVertex);
    s.push(startVertex);

    while (!s.empty())
    {
      auto vertex = s.top();
      s.pop();
      // cout << vertex->data << " ";

      for (auto edge : vertex->edges)
      {
        auto adjVertex = edge->vertex1 == vertex ? edge->vertex2 : edge->vertex1;
        if (!visited.is_visited(adjVertex))
        {
          visited.mark_visited(adjVertex);
          s.push(adjVertex);
        }
      }
    }
    // cout << endl;
  }

  int FindComponents()
  {
    visited.clear(); // limpiamos el conjunto visitado antes de comenzar
    int count = 0;

    for (auto &[id, vertex] : m_vertexes)
    {
      if (!visited.is_visited(vertex)){
        count++;
        DFS(id);
      }
    }
    return count;
  }
};

int main()
{
  Graph<char, int> g;

  g.insertVertex(1, 'A');
  g.insertVertex(2, 'B');
  g.insertVertex(3, 'C');
  g.insertVertex(4, 'D');
  g.insertVertex(5, 'E');

  g.createEdge(1, 2, 1);
  g.createEdge(1, 3, 1);
  g.createEdge(3, 2, 1);

  g.createEdge(4, 5, 1);

  cout << "Componentes: " << g.FindComponents() << endl;

  return 0;
}