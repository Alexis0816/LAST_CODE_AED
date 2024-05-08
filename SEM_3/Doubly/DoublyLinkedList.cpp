#include "DoublyLinkedList.hpp"

int main()
{
  DoublyLinkedList<int> ddl;
  ddl.push_back(1);
  ddl.push_back(2);
  ddl.push_back(3);
  ddl.push_back(4);
  cout << "Size: " << ddl.size() << endl;
  ddl.push_back(5);
  cout << "Size: " << ddl.size() << endl;
  ddl.push_back(6);

  cout << "Size: " << ddl.size() << endl;
  ddl.display();
  cout << "Front: " << ddl.front() << endl;
  cout << "Back: " << ddl.back() << endl;

  ddl.push_front(0);
  ddl.display();
  cout << "Size: " << ddl.size() << endl;

  ddl.insert(15, 3);
  ddl.display();
  cout << "Size: " << ddl.size() << endl;

  cout << "Front: " << ddl.front() << endl;
  cout << "Back: " << ddl.back() << endl;

  ddl.display();
  cout << "Elemento en posicion 3: " << ddl[3] << endl;
  cout << "Size: " << ddl.size() << endl;

  ddl.remove(3);
  ddl.display();
  cout << "Elemento en posicion 3: " << ddl[3] << endl;
  cout << "Size: " << ddl.size() << endl;

  ddl.reverse();
  ddl.display();

  ddl.reverse();
  ddl.display();

  ddl.clear();

  cout << ddl.size() << endl;

  return 0;
}