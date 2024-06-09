using namespace std;

template <class T>
struct Node
{
    T data;
    int height;
    Node<T> *left;
    Node<T> *right;

    Node(T _d) : data(_d), height(0), left(nullptr), right(nullptr) {}
};

template <class T>
class AVL
{

public:
    AVL() : root(nullptr) {}

    int size() { return _size; }

    bool find(T data) { return find(this->root, data); }

    // se utiliza para hallar el predecesor y sucesor
    Node<T> *find_root(T data) { return find_root(this->raiz, data); }

    void insert(T item)
    {
        insert(this->root, item);
    }

    void insert(initializer_list<T> &&data)
    {
        for (const auto e : data)
            root = insert(root, e);
    }

    void remove(T item)
    {
        root = remove(root, item);
    }

    int height() { return treeHeight(this->root); }

    bool isBalanced() { return isBalanced(this->root); }

    T maxValue() { return maxValue(this->root); }

    T minValue() { return minValue(this->root); }

    T successor(T value) { return successor(this->root, value); }

    T predecessor(T value) { return predecessor(this->root, value); }

    void display_in_order()
    {
        display_in_order(root);
        cout << endl;
    }
    void display_pre_order()
    {
        display_pre_order(root);
        cout << endl;
    }
    void display_post_order()
    {
        display_post_order(root);
        cout << endl;
    }
    void displayBFS()
    {
        displayBFS(root);
        cout << endl;
    }
    void displayDFS()
    {
        displayDFS(root);
        cout << endl;
    }

private:
    Node<T> *root;
    int _size{};

    Node<T> *createNode(T data)
    {
        auto *newNode = new Node<T>{data};
        return newNode;
    }

    int nodeHeight(Node<T> *node)
    {
        return (node == nullptr) ? -1 : node->height;
    }

    int getBalance(Node<T> *node)
    {
        return (node == nullptr) ? 0 : nodeHeight(node->left) - nodeHeight(node->right);
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
        x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
        y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;

        return y;
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node<T> *insert(Node<T> *node, T data)
    {
        if (node == nullptr)
        {
            _size++;
            return createNode(data);
        }

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data)
            return rightRotate(node);
        if (balance < -1 && data > node->right->data)
            return leftRotate(node);
        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *remove(Node<T> *root, T data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        root->left = remove(root->left, data);
    else if (data > root->data)
        root->right = remove(root->right, data);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node<T> *temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
                delete temp;
                _size--;
        } else {
            Node<T> *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(nodeHeight(root->left), nodeHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

    Node<T> *find_root(Node<T> *root, T data)
    {
        if (root == nullptr)
            throw "arbol vacio";
        if (data < root->data)
        {
            return find_root(root->left, data);
        }
        else if (data > root->data)
        {
            return find_root(root->right, data);
        }
        else
        {
            return root;
        }
    }

    bool find(Node<T> *root, T data)
    {
        if (root == nullptr)
            return false;
        if (data < root->data)
            return find(root->left, data);
        else if (data > root->data)
            return find(root->right, data);
        else
            return true;
    }

    int treeHeight(Node<T> *root)
    {
        return (root == nullptr) ? -1 : 1 + max(nodeHeight(root->left), nodeHeight(root->right));
    }    

    bool isBalanced(Node<T> *root)
    {
        return (root == nullptr) ? true : abs(nodeHeight(root->left) - nodeHeight(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }

    T maxValue(Node<T> *root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        while (root->right != nullptr)
            root = root->right;
        return root->data;
    }

    T minValue(Node<T> *root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        while (root->left != nullptr)
            root = root->left;
        return root->data;
    }

    T successor(Node<T> *root, T value)
    {
        Node<T> *current = find_root(root, value);
        if (current == nullptr)
            throw "sucesor no encontrado";
        if (current->right != nullptr)
        {
            return minValue(current->right);
        }
        else
        {
            Node<T> *successor = nullptr;
            Node<T> *ancestor = root;
            while (ancestor != current)
            {
                if (current->data < ancestor->data)
                {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else
                    ancestor = ancestor->right;
            }
            return successor ? successor->data : throw "sucesor no encontrado";
        }
    }

    T predecessor(Node<T> *root, T value)
    {
        Node<T> *current = find_root(root, value);
        if (current == nullptr)
            throw "predecesor no encontrado";
        if (current->left != nullptr)
        {
            return maxValue(current->left);
        }
        else
        {
            Node<T> *predecessor = nullptr;
            Node<T> *ancestor = root;
            while (ancestor != current)
            {
                if (current->data > ancestor->data)
                {
                    predecessor = ancestor;
                    ancestor = ancestor->right;
                }
                else
                    ancestor = ancestor->left;
            }
            return predecessor ? predecessor->data : throw "predecesor no encontrado";
        }
    }

    void display_in_order(Node<T> *root)
    {
        if (root == nullptr)
            return;
        display_in_order(root->left);
        cout << root->data << " ";
        display_in_order(root->right);
    }

    void display_pre_order(Node<T> *root)
    {
        if (root == nullptr)
            return;
        cout << root->data << " ";
        display_pre_order(root->left);
        display_pre_order(root->right);
    }

    void display_post_order(Node<T> *root)
    {
        if (root == nullptr)
            return;
        display_post_order(root->left);
        display_post_order(root->right);
        cout << root->data << " ";
    }

    void displayBFS(Node<T> *root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        queue<Node<T> *> q;
        q.push(root);
        while (!q.empty())
        {
            Node<T> *node = q.front();
            cout << node->data << " ";
            q.pop();
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    void displayDFS(Node<T> *root)
    {
        if (root == nullptr)
            throw "arbol vacio";
        stack<Node<T> *> s;
        s.push(root);
        while (!s.empty())
        {
            Node<T> *node = s.top();
            cout << node->data << " ";
            s.pop();
            if (node->right)
                s.push(node->right);
            if (node->left)
                s.push(node->left);
        }
    }
};