#include <iostream>
#include <vector>
using namespace std;

struct BTreeNode {
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    int t;

    BTreeNode(int t, bool leaf);

    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    BTreeNode* search(int k);
    int findKey(int k);
    void remove(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
};

class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int t) {
        root = nullptr;
        this->t = t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
    void remove(int k);
};

BTreeNode::BTreeNode(int t, bool leaf) {
    this->t = t;
    this->leaf = leaf;
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf)
            children[i]->traverse();
        cout << " " << keys[i];
    }
    if (!leaf)
        children[i]->traverse();
}

BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < keys.size() && k > keys[i])
        i++;
    if (i < keys.size() && keys[i] == k)
        return this;
    if (leaf)
        return nullptr;
    return children[i]->search(k);
}

void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    } else {
        if (root->keys.size() == 2*t-1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);
            root = s;
        } else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.push_back(0);
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;
        if (children[i + 1]->keys.size() == 2*t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->keys.resize(t - 1);
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }
    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    y->keys.resize(t - 1);
}

void BTree::remove(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }
    root->remove(k);
    if (root->keys.size() == 0) {
        BTreeNode* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    if (idx < keys.size() && keys[idx] == k) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = ((idx == keys.size()) ? true : false);
        if (children[idx]->keys.size() < t)
            fill(idx);
        if (flag && idx > keys.size())
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->keys.size() >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPredecessor(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->keys.size()];
    return cur->keys[cur->keys.size() - 1];
}

int BTreeNode::getSuccessor(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    for (int i = child->keys.size() - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->children.size() - 1; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }
    child->keys[0] = keys[idx - 1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->keys.size()];
    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
    child->keys.push_back(0);
    sibling->keys.pop_back();
    if (!sibling->leaf)
        sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys[child->keys.size()] = keys[idx];
    if (!child->leaf)
        child->children[(child->keys.size()) + 1] = sibling->children[0];
    keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->keys.size(); ++i)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->children.size(); ++i)
            sibling->children[i - 1] = sibling->children[i];
    }
    sibling->keys.pop_back();
    if (!sibling->leaf)
        sibling->children.pop_back();
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys[t - 1] = keys[idx];
    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys[i + t] = sibling->keys[i];
    if (!child->leaf) {
        for (int i = 0; i <= sibling->children.size(); ++i)
            child->children[i + t] = sibling->children[i];
    }
    for (int i = idx + 1; i < keys.size(); ++i)
        keys[i - 1] = keys[i];
    for (int i = idx + 2; i <= children.size(); ++i)
        children[i - 1] = children[i];
    child->keys.resize(2 * t - 1);
    sibling->keys.clear();
    sibling->children.clear();
    keys.pop_back();
    children.pop_back();
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < k)
        ++idx;
    return idx;
}

int main() {
    BTree t(3); // Grado mínimo del árbol B
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Recorrido del arbol B: ";
    t.traverse();
    cout << endl;

    int key = 6;
    t.search(key) ? cout << endl <<"Clave " << key << " encontrada en el arbol" << endl : cout << endl <<"Clave " << key << " no encontrada en el arbol" << endl;

    t.remove(6);
    cout << "Recorrido del arbol B despues de eliminar 6: ";
    t.traverse();
    cout << endl;

    return 0;
}


// BTreeNode: Representa un nodo en el árbol B.
// insertNonFull(int k): Inserta una clave en un nodo no lleno.
// splitChild(int i, BTreeNode* y): Divide el hijo y del nodo en dos nodos.
// traverse(): Recorre y imprime todas las claves en el árbol.
// search(int k): Busca una clave en el subárbol.
// remove(int k): Elimina una clave del subárbol.
// removeFromLeaf(int idx): Elimina una clave de un nodo hoja.
// removeFromNonLeaf(int idx): Elimina una clave de un nodo no hoja.
// getPredecessor(int idx): Obtiene el predecesor de una clave.
// getSuccessor(int idx): Obtiene el sucesor de una clave.
// fill(int idx): Llena un nodo hijo que tiene menos claves de las necesarias.
// borrowFromPrev(int idx): Pide prestada una clave del nodo hermano anterior.
// borrowFromNext(int idx): Pide prestada una clave del nodo hermano siguiente.
// merge(int idx): Fusiona un nodo con su nodo hermano.
// BTree: Representa el árbol B completo.

// traverse(): Recorre el árbol.
// search(int k): Busca una clave en el árbol.
// insert(int k): Inserta una clave en el árbol.
// remove(int k): Elimina una clave del árbol.