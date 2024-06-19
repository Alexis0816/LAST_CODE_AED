// #include <iostream>
// #include <unordered_map>
// #include <list>
// #include <algorithm>

// using namespace std;

// // Conjuntos disjuntos (Union-Find)
// template <typename T>
// class DisjoinSet
// {
// private:
//   unordered_map<T, T> parent;
//   unordered_map<T, int> rank;

// public:
//   DisjoinSet() = default;

//   void Makeset(T x)
//   {
//     parent[x] = x;
//     rank[x] = 0;
//   }

//   T Find(T x)
//   {
//     if (parent[x] != x)
//     {
//       parent[x] = Find(parent[x]);
//     }
//     return parent[x];
//   }

//   void Union(T x, T y)
//   {
//     T rootX = Find(x);
//     T rootY = Find(y);

//     if (rootX != rootY)
//     {
//       if (rank[rootX] > rank[rootY])
//       {
//         parent[rootY] = rootX;
//       }
//       else if (rank[rootX] < rank[rootY])
//       {
//         parent[rootX] = rootY;
//       }
//       else
//       {
//         parent[rootY] = rootX;
//         rank[rootX]++;
//       }
//     }
//   }

//   bool SameComponent(T x, T y)
//   {
//     return Find(x) == Find(y);
//   }
// };

// // GRAFO
// template <typename TV, typename TE>
// class Graph
// {
// private:
//   struct Edge;

//   struct Vertex
//   {
//     TV data;
//     list<Edge *> edges; // Lista de adyacencia
//   };

//   struct Edge
//   {
//     Vertex *vertex1;
//     Vertex *vertex2;
//     TE weight;

//     Edge(Vertex *v1, Vertex *v2, TE w)
//     {
//       vertex1 = v1;
//       vertex2 = v2;
//       weight = w;
//     }
//   };

//   unordered_map<int, Vertex *> m_vertexes;

// public:
//   // Añadir un vértice al grafo
//   void insertVertex(int id, TV data)
//   {
//     auto *vertex = new Vertex();
//     vertex->data = data;
//     m_vertexes[id] = vertex;
//   }

//   // Añadir una arista no dirigida al grafo
//   void createEdge(int id1, int id2, TE weight)
//   {
//     auto vertex1 = m_vertexes[id1];
//     auto vertex2 = m_vertexes[id2];

//     if (vertex1 && vertex2)
//     {
//       auto *edge = new Edge(vertex1, vertex2, weight);
//       vertex1->edges.push_back(edge);
//       vertex2->edges.push_back(edge);
//     }
//   }

//   // Obtener todas las aristas únicas y ordenadas por peso del grafo
//   Edge **getEdges(int &size)
//   {
//     Edge **edges = new Edge *[m_vertexes.size() * 2]; // Max possible edges in undirected graph

//     int index = 0;
//     for (auto [id, vertex] : m_vertexes)
//     {
//       for (auto edge : vertex->edges)
//       {
//         // Evitar duplicados asegurando que vertex1 < vertex2
//         if (edge->vertex1 == vertex || edge->vertex1->data < edge->vertex2->data)
//         {
//           edges[index++] = edge;
//         }
//       }
//     }

//     // Ordenar aristas por peso
//     sort(edges, edges + index, [](Edge *a, Edge *b) { return a->weight < b->weight; });

//     // Redimensionar el arreglo dinámico para ajustarlo al número real de aristas encontradas
//     Edge **resizedEdges = new Edge *[index];
//     for (int i = 0; i < index; ++i){
//       resizedEdges[i] = edges[i];
//     }

//     delete[] edges; // Liberar memoria del arreglo original
//     size = index;
//     return resizedEdges;
//   }

//   // Algoritmo Kruskal para encontrar el MST
//   void KruskalMST(){
//     int size = 0;
//     Edge **edges = getEdges(size);
//     DisjoinSet<Vertex *> ds;

//     for (auto [id, vertex] : m_vertexes){
//       ds.Makeset(vertex);
//     }

//     cout << "Arbol de Expansion Minima (Kruskal):" << endl;
//     for (int i = 0; i < size; ++i){
//       Vertex *u = edges[i]->vertex1;
//       Vertex *v = edges[i]->vertex2;

//       if (!ds.SameComponent(u, v)){
//         ds.Union(u, v);
//         cout << "(" << u->data << " - " << v->data << ") Peso: " << edges[i]->weight << endl;
//       }
//     }

//     delete[] edges; // Liberar memoria del arreglo dinámico
//   }

//   // Mostrar el grafo
//   void displayGraph(){
//     cout << "GRAFO:" << endl;
//     for (auto [id, vertex] : m_vertexes){
//       cout << "Vertice " << id << " (" << vertex->data << ") -> ";
//       for (auto edge : vertex->edges){
//         cout << "Arista al vertice " << (edge->vertex1 == vertex ? edge->vertex2->data : edge->vertex1->data) << " con peso " << edge->weight << "; ";
//       }
//       cout << endl;
//     }
//     cout << endl;
//   }
// };

// int main()
// {
//   Graph<char, int> g;

//   g.insertVertex(1, 'A');
//   g.insertVertex(2, 'B');
//   g.insertVertex(3, 'C');
//   g.insertVertex(4, 'D');
//   g.insertVertex(5, 'E');

//   g.createEdge(1, 2, 3);
//   g.createEdge(1, 3, 2);
//   g.createEdge(1, 4, 1);
//   g.createEdge(2, 3, 4);
//   g.createEdge(2, 4, 3);
//   g.createEdge(3, 4, 5);
//   g.createEdge(4, 5, 6);

//   g.displayGraph();
//   g.KruskalMST();

//   return 0;
// }


#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

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

        Edge(Vertex *v1, Vertex *v2, TE w) {
            vertex1 = v1;
            vertex2 = v2;
            weight = w;
        }
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
            auto* edge = new Edge(vertex1, vertex2, weight);
            vertex1->edges.push_back(edge);
            // No añadir la misma arista dos veces si el grafo es no dirigido
            if (vertex1 != vertex2) {
                vertex2->edges.push_back(edge);
            }
        }
    }

    // Obtener todas las aristas únicas y ordenadas por peso del grafo
    Edge** getEdges(int& size) {
        Edge** edges = new Edge*[m_vertexes.size() * 2]; // Máximas aristas posibles un un grafo no dirigido

        int index = 0;
        unordered_map<Edge*, bool> visited;

        for (auto [id, vertex] : m_vertexes) {
            for (auto edge : vertex->edges) {
                // Asegurar que la arista se considere solo una vez y en una dirección (vertex1 < vertex2)
                if (!visited[edge]) {
                    edges[index++] = edge;
                    visited[edge] = true;
                }
            }
        }

        // Ordenar aristas por peso
        sort(edges, edges + index, [](Edge *a, Edge *b) { return a->weight < b->weight; });

        // Redimensionar el arreglo dinámico para ajustarlo al número real de aristas encontradas
        Edge** resizedEdges = new Edge*[index];
        for (int i = 0; i < index; ++i) {
            resizedEdges[i] = edges[i];
        }

        delete[] edges; // Liberar memoria del arreglo original
        size = index;
        return resizedEdges;
    }

    // Algoritmo Kruskal para encontrar el MST
    void KruskalMST() {
        int size = 0;
        Edge** edges = getEdges(size);
        DisjoinSet<Vertex *> ds;

        for (auto [id, vertex] : m_vertexes) {
            ds.Makeset(vertex);
        }

        cout << "Arbol de Expansion Minima (Kruskal):" << endl;
        for (int i = 0; i < size; ++i) {
            Vertex *u = edges[i]->vertex1;
            Vertex *v = edges[i]->vertex2;

            if (!ds.SameComponent(u, v)) {
                ds.Union(u, v);
                cout << "(" << u->data << " - " << v->data << ") Peso: " << edges[i]->weight << endl;
            }
        }

        delete[] edges; // Liberar memoria del arreglo dinámico
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
