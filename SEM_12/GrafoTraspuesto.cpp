#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

// Grafo Dirigido
template <typename TV, typename TE>
class Graph{
private:
    struct Edge;

    struct Vertex {
        TV data;
        list<Edge *> edges; // Lista de adyacencia
    };

    struct Edge {
        Vertex *from;
        Vertex *to;
        TE weight;
    };

    unordered_map<int, Vertex *> m_vertexes;
    // m_vertexes: Es un unordered_map que mapea IDs de vértices (enteros) a punteros de tipo Vertex, almacenando así todos los vértices del grafo.

public:
    // Añadir un vértice al grafo
    void insertVertex(int id, TV data) {
        auto *vertex = new Vertex();
        vertex->data = data;
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

    // Generar el grafo traspuesto
    Graph<TV, TE> transpose() {
        Graph<TV, TE> transposedGraph;

        // Insertar los vértices en el grafo transpuesto
        for (auto &[id, vertex] : m_vertexes) {
            transposedGraph.insertVertex(id, vertex->data);
        }

        // Insertar las aristas invertidas en el grafo transpuesto
        for (auto &[id, vertex] : m_vertexes) {
            for (auto edge : vertex->edges) {
                int fromId = findVertexId(edge->from);
                int toId = findVertexId(edge->to);

                transposedGraph.createEdge(toId, fromId, edge->weight);
            }
        }

        return transposedGraph;
    }

private:
    int findVertexId(Vertex *vertex) {
        for (auto &[id, v] : m_vertexes) {
            if (v == vertex) return id;
        }
        return -1; // En teoría nunca debería llegar aquí si el vértice existe en el grafo
    }
    // findVertexId: Busca y devuelve el ID de un vértice dado su puntero. Itera sobre m_vertexes y compara los punteros para encontrar el ID correspondiente.
};

// Graph: Es la plantilla de la clase grafo. Utiliza dos tipos de plantilla TV (tipo de datos del vértice) y TE (tipo de datos del peso de la arista).

// Vertex: Es una estructura interna que representa un vértice en el grafo. Contiene data que almacena la información del vértice y edges, que es una lista de punteros a las aristas que salen del vértice.

// Edge: Es una estructura interna que representa una arista dirigida. Tiene punteros from y to que indican los vértices de origen y destino respectivamente, y weight que representa el peso de la arista.

// insertVertex: Inserta un nuevo vértice en el grafo con un ID y datos específicos. Crea un nuevo objeto Vertex, le asigna los datos y lo inserta en el unordered_map m_vertexes usando el ID como clave.

// createEdge: Crea una arista dirigida desde un vértice con ID fromId hacia un vértice con ID toId, con un peso especificado weight. Primero obtiene los punteros a los vértices de origen y destino desde m_vertexes, y si ambos existen, crea una nueva arista (Edge), la conecta al vértice de origen y la agrega a la lista de aristas salientes (edges) de ese vértice.

// displayGraph: Muestra el grafo en consola. Itera sobre cada vértice y muestra sus aristas salientes. Utiliza findVertexId para obtener el ID de destino de cada arista y mostrarlo junto con el peso.

// transpose: Genera y devuelve el grafo traspuesto. Crea un nuevo grafo transposedGraph con los mismos vértices pero aristas invertidas. Itera sobre cada vértice y sus aristas en el grafo original, y crea aristas invertidas en transposedGraph usando createEdge.


int main() {
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

    auto transposedGraph = graph.transpose();
    cout << endl << "Grafo traspuesto: " << endl;
    transposedGraph.displayGraph();

    return 0;
}
