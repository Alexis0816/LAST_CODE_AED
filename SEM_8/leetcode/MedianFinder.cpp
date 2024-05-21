// #include <iostream>
// #include <queue>
// #include <vector>

// class MedianFinder {
// private:
//     std::priority_queue<int> maxHeap; // max-heap para la mitad menor
//     std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // min-heap para la mitad mayor

// public:
//     /** initialize your data structure here. */
//     MedianFinder() {}

//     void addNum(int num) {
//         // Insertar en el max-heap primero
//         maxHeap.push(num);
        
//         // Asegurarse de que el mayor del max-heap sea menor que el menor del min-heap
//         if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
//             int maxTop = maxHeap.top();
//             maxHeap.pop();
//             minHeap.push(maxTop);
//         }

//         // Balancear los heaps si es necesario
//         if (maxHeap.size() > minHeap.size() + 1) {
//             minHeap.push(maxHeap.top());
//             maxHeap.pop();
//         } else if (minHeap.size() > maxHeap.size()) {
//             maxHeap.push(minHeap.top());
//             minHeap.pop();
//         }
//     }

//     double findMedian() {
//         if (maxHeap.size() == minHeap.size()) {
//             return (maxHeap.top() + minHeap.top()) / 2.0;
//         } else {
//             return maxHeap.top();
//         }
//     }
// };

// int main() {
//     MedianFinder medianFinder;
//     medianFinder.addNum(2);
//     medianFinder.addNum(3);
//     std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 1.5
//     medianFinder.addNum(4);
//     std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 2
//     return 0;
// }


// /**
//  * Your MedianFinder object will be instantiated and called as such:
//  * MedianFinder* obj = new MedianFinder();
//  * obj->addNum(num);
//  * double param_2 = obj->findMedian();
//  */




#include <iostream>

template <typename T>
class MaxHeap {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* root, T data) {
        if (root == nullptr) {
            return new Node(data);
        }

        if (data > root->data) {
            std::swap(root->data, data);
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
            std::swap(root->data, root->left->data);
            root->left = deleteMax(root->left);
        } else {
            std::swap(root->data, root->right->data);
            root->right = deleteMax(root->right);
        }

        return root;
    }

    void heapifyUp(Node* node) {
        if (node == nullptr || node == root) {
            return;
        }

        if (node->data > node->right->data) {
            std::swap(node->data, node->right->data);
            heapifyUp(node->right);
        } else if (node->data > node->left->data) {
            std::swap(node->data, node->left->data);
            heapifyUp(node->left);
        }
    }

    void heapifyDown(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->data > node->data) {
            std::swap(node->data, node->left->data);
            heapifyDown(node->left);
        } else if (node->right != nullptr && node->right->data > node->data) {
            std::swap(node->data, node->right->data);
            heapifyDown(node->right);
        }
    }

public:
    MaxHeap() : root(nullptr) {}

    void insert(T data) {
        root = insert(root, data);
        heapifyUp(root);
    }

    T extractMax() {
        if (root == nullptr) {
            throw "Heap vacío";
        }

        T maxData = root->data;
        root = deleteMax(root);
        heapifyDown(root);

        return maxData;
    }

    T max() {
        if (root == nullptr) {
            throw "Heap vacío";
        }

        return root->data;
    }

    void display() {
        display(root);
        std::cout << std::endl;
    }

private:
    void display(Node* root) {
        if (root == nullptr) {
            return;
        }

        display(root->left);
        std::cout << root->data << " ";
        display(root->right);
    }
};

template <typename T>
class MinHeap {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    Node* root;

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

    Node* findMin(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        while (root->left != nullptr) {
            root = root->left;
        }

        return root;
    }

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

        if (root->left != nullptr && root->right != nullptr) {
            if (root->left->data < root->right->data) {
                std::swap(root->data, root->left->data);
            } else {
                std::swap(root->data, root->right->data);
            }
        }

        return root;
    }

    void heapifyUp(Node* node) {
        if (node == nullptr || node == root) {
            return;
        }

        if (node->data < node->right->data) {
            std::swap(node->data, node->right->data);
            heapifyUp(node->right);
        } else if (node->data < node->left->data) {
            std::swap(node->data, node->left->data);
            heapifyUp(node->left);
        }
    }

    void heapifyDown(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left != nullptr && node->left->data < node->data) {
            std::swap(node->data, node->left->data);
            heapifyDown(node->left);
        } else if (node->right != nullptr && node->right->data < node->data) {
            std::swap(node->data, node->right->data);
            heapifyDown(node->right);
        }
    }

public:
    MinHeap() : root(nullptr) {}

    void insert(T data) {
        root = insert(root, data);
        heapifyUp(root);
    }

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

    T min() {
        return root->data;
    }

    void display() {
        display(root);
        std::cout << std::endl;
    }

private:
    void display(Node* root) {
        if (root == nullptr) {
            return;
        }

        display(root->left);
        std::cout << root->data << " ";
        display(root->right);
    }
};

class MedianFinder {
private:
    MaxHeap<int> maxHeap; // max-heap for the lower half
    MinHeap<int> minHeap; // min-heap for the upper half

public:
    MedianFinder() {}

    void addNum(int num) {
        if (maxHeap.root == nullptr || num <= maxHeap.max()) {
            maxHeap.insert(num);
        } else {
            minHeap.insert(num);
        }

        // Balance heaps
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.insert(maxHeap.extractMax());
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.insert(minHeap.extractMin());
        }
    }

    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.max() + minHeap.min()) / 2.0;
        } else {
            return maxHeap.max();
        }
    }
};

int main() {
    MedianFinder medianFinder;
    medianFinder.addNum(2);
    medianFinder.addNum(3);
    std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 2.5
    medianFinder.addNum(4);
    std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 3
    return 0;
}
