#include <iostream>

using namespace std;

template <typename T>
class MinHeap {
private:
    // Estructura de un nodo en el heap
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Función para insertar un elemento en el heap
    Node* insert(Node* root, T data) {
        if (root == nullptr) {
            return new Node(data);
        }

        if (data < root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }

        return root;
    }

    // Función para encontrar el nodo mínimo en el heap
    Node* findMin(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        while (root->left != nullptr) {
            root = root->left;
        }

        return root;
    }

    // Función para eliminar el nodo mínimo del heap
    Node* deleteMin(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        root->left = deleteMin(root->left);

        // Seleccionar el nuevo mínimo entre el hijo izquierdo y el hijo derecho
        if (root->left != nullptr && root->right != nullptr) {
            if (root->left->data < root->right->data) {
                swap(root->data, root->left->data);
            } else {
                swap(root->data, root->right->data);
            }
        }

        return root;
    }

    // Función para aplicar el heapify hacia arriba (hacia la raíz)
    void heapifyUp(Node* node) {
        if (node == nullptr || node == root) {
            return;
        }

        if (node->data < node->right->data) {
            swap(node->data, node->right->data);
            heapifyUp(node->right);
        } else if (node->data < node->left->data) {
            swap(node->data, node->left->data);
            heapifyUp(node->left);
        }
    }

    // Función para aplicar el heapify hacia abajo (hacia las hojas)
    void heapifyDown(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->data < node->data) {
            swap(node->data, node->left->data);
            heapifyDown(node->left);
        } else if (node->right != nullptr && node->right->data < node->data) {
            swap(node->data, node->right->data);
            heapifyDown(node->right);
        }
    }

public:
    MinHeap() : root(nullptr) {}

    // Función para insertar un elemento en el heap
    void insert(T data) {
        root = insert(root, data);
        heapifyUp(root);
    }

    // Función para extraer el mínimo del heap
    T extractMin() {
        if (root == nullptr) {
            throw "Heap vacío";
        }

        Node* minNode = findMin(root);
        T minData = minNode->data;
        root = deleteMin(root);
        heapifyDown(root);

        return minData;
    }

    // Función para obtener el valor mínimo del heap
    T min() {
        return root->data;
    }

    // Función para mostrar los elementos del heap
    void display() {
        display(root);
        cout << endl;
    }

private:
    // Función auxiliar para mostrar los elementos del heap
    void display(Node* root) {
        if (root == nullptr) {
            return;
        }

        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
};


int main() {
    MinHeap<int> minHeap;

    // Insertar elementos en el heap
    minHeap.insert(4);
    minHeap.insert(2);
    minHeap.insert(7);
    minHeap.insert(1);
    minHeap.insert(5);

    cout << minHeap.min() <<endl;

    // Mostrar los elementos del heap
    cout << "Heap: ";
    minHeap.display();

    // Extraer el elemento mínimo
    cout << "Elemento minimo extraido: " << minHeap.extractMin() << endl;

    // Mostrar los elementos del heap después de la extracción
    cout << "Heap despues de extraer el elemento minimo: ";
    minHeap.display();

    cout << minHeap.min() <<endl;


    return 0;
}
