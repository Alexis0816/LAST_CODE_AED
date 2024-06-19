#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

// Conjuntos disjuntos (Union-Find)
template <typename T>
class DisjoinSet {
private:
    unordered_map<T, T> parent;
    unordered_map<T, int> rank;

public:
    DisjoinSet() = default;

    void Makeset(T x) {
        parent[x] = x;
        rank[x] = 0;
    }

    T Find(T x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(T x, T y) {
        T rootX = Find(x);
        T rootY = Find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool SameComponent(T x, T y) {
        return Find(x) == Find(y);
    }
};


// DisjoinSet: Esta clase implementa una estructura de conjuntos disjuntos (Union-Find) con las siguientes características:

// parent: Un unordered_map que guarda el padre de cada elemento.
// rank: Un unordered_map que guarda la altura del árbol para la optimización de uniones por rango.
// Makeset: Este método inicializa un nuevo conjunto para el elemento x. Lo establece como su propio padre y le asigna un rango inicial de 0.

// Find: Este método encuentra el representante (raíz) del conjunto al que pertenece x, utilizando la técnica de compresión de camino (path compression). Esta técnica optimiza la estructura del árbol de búsqueda para futuras operaciones.

// Union: Este método une los conjuntos que contienen x y y. Primero encuentra las raíces de ambos conjuntos y luego decide cómo unirlos basado en el rango de cada raíz. Esto asegura que el árbol resultante sea lo más plano posible, lo que optimiza las operaciones futuras.

// SameComponent: Este método verifica si dos elementos x e y pertenecen al mismo conjunto encontrando y comparando sus raíces.


// GRAFO
template <typename TV, typename TE>
class Graph {
private:
    struct Edge;

    struct Vertex {
        TV data;
        list<Edge *> edges; // Lista de adyacencia
    };

    struct Edge {
        Vertex *vertex1;
        Vertex *vertex2;
        TE weight;
    };

    unordered_map<int, Vertex *> m_vertexes;

public:
    // Añadir un vértice al grafo
    void insertVertex(int id, TV data) {
        auto* vertex = new Vertex();
        vertex->data = data;
        m_vertexes[id] = vertex;
    }

    // Añadir una arista no dirigida al grafo
    void createEdge(int id1, int id2, TE weight) {
        auto vertex1 = m_vertexes[id1];
        auto vertex2 = m_vertexes[id2];

        if (vertex1 && vertex2) {
            auto* edge = new Edge();
            edge->vertex1 = vertex1;
            edge->vertex2 = vertex2;
            edge->weight = weight;

            vertex1->edges.push_back(edge);
            vertex2->edges.push_back(edge);
        }
    }

    // Obtener todas las aristas del grafo
    vector<Edge *> getEdges() {
        vector<Edge *> edges;

        for (auto [id, vertex] : m_vertexes) {
            for (auto edge : vertex->edges) {
                // Evitamos duplicados asegurando que vertex1 < vertex2
                if (edge->vertex1 == vertex || edge->vertex1->data < edge->vertex2->data) {
                    edges.push_back(edge);
                }
            }
        }

        // Ordenar aristas por peso
        sort(edges.begin(), edges.end(), [](Edge *a, Edge *b) {
            return a->weight < b->weight;
        });

        return edges;
    }

    // Algoritmo Kruskal para encontrar el MST
    void KruskalMST() {
        // Obtener todas las aristas ordenadas por peso
        vector<Edge *> edges = getEdges();
        DisjoinSet<Vertex *> ds;

        for (auto [id, vertex] : m_vertexes) {
            ds.Makeset(vertex);
        }

        cout << "Arbol de Expansion Minima (Kruskal):" << endl;
        for (auto edge : edges) {
            Vertex *u = edge->vertex1;
            Vertex *v = edge->vertex2;

            if (!ds.SameComponent(u, v)) {
                ds.Union(u, v);
                cout << "(" << u->data << " - " << v->data << ") Peso: " << edge->weight << endl;
            }
        }
    }

    // Mostrar el grafo
    void displayGraph() {
        cout << "GRAFO:" << endl;
        for (auto [id, vertex] : m_vertexes) {
            cout << "Vertice " << id << " (" << vertex->data << ") -> ";
            for (auto edge : vertex->edges) {
                cout << "Arista al vertice " << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << " con peso " << edge->weight << "; ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

// insertVertex: Inserta un nuevo vértice en el grafo con un ID y datos específicos. Crea un nuevo objeto Vertex, le asigna los datos y lo inserta en el unordered_map m_vertexes usando el ID como clave.

// createEdge: Crea una arista dirigida desde un vértice con ID fromId hacia un vértice con ID toId, con un peso especificado weight. Primero obtiene los punteros a los vértices de origen y destino desde m_vertexes, y si ambos existen, crea una nueva arista (Edge), la conecta al vértice de origen y la agrega a la lista de aristas salientes (edges) de ese vértice.

// getEdges: Este método obtiene todas las aristas del grafo, ordenadas por peso. Para evitar duplicados, se asegura que para cada arista solo se guarde una dirección (vertex1 < vertex2).

// KruskalMST: Este método implementa el algoritmo de Kruskal para encontrar el MST del grafo. Utiliza una instancia de DisjoinSet para manejar las uniones y búsquedas eficientemente. Itera sobre las aristas ordenadas por peso y, para cada arista, verifica si sus extremos pertenecen al mismo componente usando SameComponent de DisjoinSet. Si no pertenecen al mismo componente, une los conjuntos usando Union y añade la arista al MST resultante.


int main() {
    Graph<char, int> g;

    g.insertVertex(1, 'A');
    g.insertVertex(2, 'B');
    g.insertVertex(3, 'C');
    g.insertVertex(4, 'D');
    g.insertVertex(5, 'E');

    g.createEdge(1, 2, 3);
    g.createEdge(1, 3, 2);
    g.createEdge(1, 4, 1);
    g.createEdge(2, 3, 4);
    g.createEdge(2, 4, 3);
    g.createEdge(3, 4, 5);
    g.createEdge(4, 5, 6);

    g.displayGraph();
    g.KruskalMST();

    return 0;
}
