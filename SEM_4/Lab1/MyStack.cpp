// Stack con 2 queue

#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> q1;
    queue<int> q2;

public:
  MyStack(){}
  // Empuja el elemento x a la parte superior de la pila.
  void push(int x) {
    q2.push(x);
    while (!q1.empty()) {
        q2.push(q1.front());
        q1.pop();
    }
    swap(q1, q2);
  }

  // Elimina el elemento en la parte superior de la pila y lo devuelve.
  int pop() {
    int topElement = q1.front();
    q1.pop();
    return topElement;
  }

  // Devuelve el elemento en la parte superior de la pila.
  int top() {
    return q1.front();
  }

  bool empty() { return q1.empty(); }
};

int main(){
  MyStack myStack;
  myStack.push(1);
  myStack.push(2);
  cout << myStack.top() <<endl; // return 2
  cout << myStack.pop() <<endl; // return 2
  cout << myStack.empty() <<endl; // return False


  return 0;
}
