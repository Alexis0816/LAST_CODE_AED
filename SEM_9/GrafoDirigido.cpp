#include <iostream>
#include <forward_list>
#include <iterator>
#include <exception>
#include <functional>
#include <string>
#include <map>  // mapeo de Key-Value
#include <list> // Doubly Linked List
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

  void _delete(TK key)
  {
    size_t index = _hash(key);
    auto &it0 = array[index];
    auto it1 = it0.begin();
    auto prevIt1 = it0.before_begin();
    // Encuentra el elemento a borrar y su posición
    while (it1 != end(it0) && it1->key != key)
    {
      ++it1;
      ++prevIt1;
    }
    // Verifica si el elemento existe
    if (it1 == end(it0))
    {
      throw runtime_error("La clave que intentas eliminar no existe");
    }
    // Borra el elemento de la lista
    it0.erase_after(prevIt1);
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

// Implementación de Graph con HashTable
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
    Vertex *from;
    Vertex *to;
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

  // Añadir una arista dirigida al grafo
  void createEdge(int fromId, int toId, TE weight)
  {
    auto fromVertex = m_vertexes.find(fromId);
    auto toVertex = m_vertexes.find(toId);

    if (fromVertex && toVertex)
    {
      auto *edge = new Edge();
      edge->from = fromVertex;
      edge->to = toVertex;
      edge->weight = weight;

      fromVertex->edges.push_back(edge);
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
          cout << "Arista al vertice " << findVertexId(edge->to) << " (" << edge->to->data << ") con peso " << edge->weight << "; ";
        }
        cout << endl;
        ++it0;
      }
    }
  }

  // Función para encontrar el ID de un vértice dado el puntero al vértice
  int findVertexId(Vertex* vertex)
  {
    auto keyValues = m_vertexes.key_value();
    for (const auto& kv : keyValues)
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
  Graph<string, int> graph;

  graph.insertVertex(1, "A");
  graph.insertVertex(2, "B");
  graph.insertVertex(3, "C");
  graph.insertVertex(4, "D");
  graph.insertVertex(5, "E");
  graph.insertVertex(6, "F");

  graph.createEdge(1, 2, 10);
  graph.createEdge(1, 5, 20);
  graph.createEdge(2, 6, 30);
  graph.createEdge(3, 1, 40);
  graph.createEdge(3, 5, 50);
  graph.createEdge(5, 2, 60);
  graph.createEdge(5, 4, 70);
  graph.createEdge(6, 5, 80);

  cout << "Grafo original: " << endl;
  graph.displayGraph();

  return 0;
}