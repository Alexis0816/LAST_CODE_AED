#include "CircularDoublyLinkedList.hpp"

int main()
{
  CircularDoublyLinkedList list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.display(); // Output: 1 2 3

  list.push_front(0);
  list.display(); // Output: 0 1 2 3

  list.pop_back();
  list.display(); // Output: 0 1 2

  list.pop_front();
  list.display(); // Output: 1 2

  list.insert(5, 1);
  list.display(); // Output: 1 5 2

  list.remove(1);
  list.display(); // Output: 1 2

  list.reverse();
  list.display(); // Output: 2 1

  list.clear();
  list.display(); // Output: Lista vacia.

  return 0;
}