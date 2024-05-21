#include <iostream>

using namespace std;

template <typename T>
class MaxHeap {
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

        if (data > root->data) {
            swap(root->data, data);
        }

        if (root->left == nullptr) {
            root->left = insert(root->left, data);
        } else if (root->right == nullptr) {
            root->right = insert(root->right, data);
        } else if (root->left->data < root->right->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }

        return root;
    }

    // Función para eliminar el nodo máximo del heap
    Node* deleteMax(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = (root->left != nullptr) ? root->left : root->right;
            delete root;
            return temp;
        }

        if (root->left->data > root->right->data) {
            swap(root->data, root->left->data);
            root->left = deleteMax(root->left);
        } else {
            swap(root->data, root->right->data);
            root->right = deleteMax(root->right);
        }

        return root;
    }

    // Función para aplicar el heapify hacia arriba (hacia la raíz)
    void heapifyUp(Node* node) {
        if (node == nullptr || node == root) {
            return;
        }

        if (node->data > node->right->data) {
            swap(node->data, node->right->data);
            heapifyUp(node->right);
        } else if (node->data > node->left->data) {
            swap(node->data, node->left->data);
            heapifyUp(node->left);
        }
    }

    // Función para aplicar el heapify hacia abajo (hacia las hojas)
    void heapifyDown(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->data > node->data) {
            swap(node->data, node->left->data);
            heapifyDown(node->left);
        } else if (node->right != nullptr && node->right->data > node->data) {
            swap(node->data, node->right->data);
            heapifyDown(node->right);
        }
    }

public:
    MaxHeap() : root(nullptr) {}

    // Función para insertar un elemento en el heap
    void insert(T data) {
        root = insert(root, data);
        heapifyUp(root);
    }

    // Función para extraer el máximo del heap
    T extractMax() {
        if (root == nullptr) {
            throw "Heap vacío";
        }

        T maxData = root->data;
        root = deleteMax(root);
        heapifyDown(root);

        return maxData;
    }

    // Función para obtener el valor máximo del heap
    T max() {
        if (root == nullptr) {
            throw "Heap vacío";
        }

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
    MaxHeap<int> maxHeap;

    // Insertar elementos en el heap
    maxHeap.insert(4);
    maxHeap.insert(2);
    maxHeap.insert(7);
    maxHeap.insert(1);
    maxHeap.insert(5);

    // Mostrar los elementos del heap
    cout << "Heap: ";
    maxHeap.display();

    // Extraer el elemento máximo
    cout << "Elemento maximo extraido: " << maxHeap.extractMax() << endl;

    // Mostrar los elementos del heap después de la extracción
    cout << "Heap despues de extraer el elemento maximo: ";
    maxHeap.display();

    cout << maxHeap.max() <<endl;

    return 0;
}
