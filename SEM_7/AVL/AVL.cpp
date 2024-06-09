#include <iostream>
#include <queue>
#include <stack>
#include <initializer_list>
#include "AVL.hpp"

using namespace std;

int main()
{
    AVL<int> avl;
    avl.insert({1, 2, 3, 4, 5, 6, 7});      

    cout << "InOrder: ";
    avl.display_in_order();

    cout << "PreOrder: ";
    avl.display_pre_order();

    cout << "PostOrder: ";
    avl.display_post_order();

    cout << "BFS: ";
    avl.displayBFS();

    cout << "DFS: ";
    avl.displayDFS();

    avl.remove(1);
    cout << "Remove 1: ";
    avl.display_in_order();

    // test de prueba
    cout << "Tree Height: " << avl.height() << endl;

    avl.remove(4);
    cout << "Remove 4: ";
    avl.display_in_order();

    // test de prueba
    cout << "Tree Height: " << avl.height() << endl;

    cout << "Max: " << avl.maxValue() << endl;
    cout << "Min: " << avl.minValue() << endl;

    cout << "Sucesor de 3: " << avl.successor(3) << endl;
    cout << "Predecesor de 3: " << avl.predecessor(3) << endl;

    cout << "Tree Height: " << avl.height() << endl;
    cout << "Is Balanced?: " << (avl.isBalanced() ? "Yes" : "No") << endl;

    return 0;
}