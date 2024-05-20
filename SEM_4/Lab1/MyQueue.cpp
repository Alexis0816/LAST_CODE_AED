// Queue con 2 stack

#include <iostream>
#include <stack>
using namespace std;

template <typename T>
class MyQueue
{
private:
  stack<T> s1, s2;

public:
  MyQueue() = default;

  // inserta un elemento al final de la cola
  void push(T x){
    while (!s2.empty()){
      s1.push(s2.top());
      s2.pop();
    }

    s2.push(x);
    while (!s1.empty()){
      s2.push(s1.top());
      s1.pop();
    }
  };

  // elimina un elemento del frente de la cola
  T pop(){
    T &temp = peek();
    s2.pop();
    return temp;
  };

  // Devuelve el elemento al frente pero no se elimina
  T front(){
    if (!empty())
    {
      return s2.top();
    }
    // cout+error = imprime mensajes de error en la salida de error estándar. 
    cerr << "Queue is empty" << endl;
    exit(0);
  };

  bool empty(){ return s2.empty() && s1.empty(); };
};


int main(){
  MyQueue<int> myQ;
  myQ.push(1);
  myQ.push(2);



  return 0;
}
