#include <iostream>
#include <list> // Doubly linked list
#include <forward_list>
#include <iterator>
#include <exception>
#include <functional>
#include <string>
#include <map> // mapeo de Key-Value
using namespace std;

const int maxColision = 3;
const float maxFillFactor = 0.5;

// HashTable
template <typename TK, typename TV>
class HashTable
{
private:
  struct Entry
  {
    TK key;
    TV value;
  };
  using Set_from_Seq = forward_list<Entry>;
  Set_from_Seq *array;

  int capacity; // tamaño del array
  double size;  // cantidad de elemetos incluyendo colisionados

public:
  HashTable() : capacity(13), size(0)
  {
    array = new Set_from_Seq[capacity];
  }

  HashTable(int _capacity) : capacity(_capacity), size(0)
  {
    array = new Set_from_Seq[capacity];
  }

  void insert(TK key, TV value)
  {
    if (fillFactor() >= maxFillFactor)
    {
      cout << "Size actual: " << _size() << " Rehashing ..." << endl;
      resize();
    }

    Entry entry = {key, value}; // entrada de 2 valores (key and value)
    int index = _hash(key);

    auto it0 = begin(array[index]);
    // actualiza llave-valor
    while (it0 != end(array[index]))
    {
      if (it0->key == key)
      {
        it0->value = value;
        return;
      }
      ++it0;
    }

    // no encontró la llave, significa que ese registro con la llave-valor se ha agregado correctamente.
    if (it0 == end(array[index]))
    {
      array[index].push_front(entry);
      size++;
    }
  }

  TV find(TK key)
  {
    int index = _hash(key);
    auto it0 = array[index];
    auto it1 = begin(it0);

    while (it1 != end(it0))
    {
      if (it1->key == key)
      {
        return it1->value;
      }
      else
      {
        ++it1;
      }
    }
    throw runtime_error("La clave no existe");
  }

  int _size()
  {
    return capacity;
  }

  // typename Set_from_Seq::iterator = auto
  auto _begin(int iList)
  {
    return begin(array[iList]);
  }

  auto _end(int iList)
  {
    return end(array[iList]);
  }

  map<TK, TV> key_value()
  {
    map<TK, TV> result;
    for (int i = 0; i < capacity; ++i)
    {
      auto it0 = begin(array[i]);
      while (it0 != end(array[i]))
      {
        result[it0->key] = it0->value;
        ++it0;
      }
    }
    return result;
  }

private:
  size_t _hash(TK key)
  {
    hash<TK> ptr_hash;
    return ptr_hash(key) % capacity;
  }

  // FillFactor = # of elements / (capacity * k) --> size(# of elements) ; maxColision (k)
  double fillFactor()
  {
    return size / (capacity * maxColision);
  }

  void resize()
  {
    int prev_capacity = capacity;
    capacity = capacity * 2;
    auto *prev_array = array;
    array = new Set_from_Seq[capacity];
    for (int i = 0; i < prev_capacity; ++i)
    {
      auto it0 = prev_array[i];
      auto it1 = begin(it0);
      while (it1 != end(it0))
      {
        insert(it1->key, it1->value);
        ++it1;
      }
    }
    delete[] prev_array;
  }
};

// Implementación del grafo no dirigido usando HashTable
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

  HashTable<int, Vertex *> m_vertexes;

public:
  // Añadir un vértice al grafo
  void insertVertex(int id, TV data)
  {
    auto *vertex = new Vertex();
    vertex->data = data;
    m_vertexes.insert(id, vertex);
  }

  // Añadir una arista no dirigida al grafo
  void createEdge(int id1, int id2, TE weight)
  {
    auto vertex1 = m_vertexes.find(id1);
    auto vertex2 = m_vertexes.find(id2);

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
    for (int i = 0; i < m_vertexes._size(); ++i)
    {
      auto it0 = m_vertexes._begin(i);
      while (it0 != m_vertexes._end(i))
      {
        auto [id, vertex] = *it0;
        cout << "Vertice " << id << " (" << vertex->data << ") -> ";
        for (auto edge : vertex->edges)
        {
          cout << "Arista al vertice " << (edge->vertex1 == vertex ? findVertexId(edge->vertex2) : findVertexId(edge->vertex1)) << " (" << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << ") con peso " << edge->weight << "; ";
        }
        cout << endl;
        ++it0;
      }
    }
  }

  // Función para encontrar el ID de un vértice dado el puntero al vértice
  int findVertexId(Vertex *vertex)
  {
    auto keyValues = m_vertexes.key_value();
    for (const auto &kv : keyValues)
    {
      if (kv.second == vertex)
      {
        return kv.first;
      }
    }
    return -1; // Retorna -1 si el vértice no se encuentra (esto no debería ocurrir)
  }
};

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
  graph.createEdge(7, 9, 21);  // B - G | 21
  graph.createEdge(8, 9, 32);  // E - G | 32
  graph.createEdge(9, 10, 7);  // G - I | 7

  // Mostrar el grafo
  graph.displayGraph();

  return 0;
}
