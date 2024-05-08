#include <iostream>
using namespace std;

struct Node
{
  int val;
  int min; // guardo el mínimo valor
  Node *next;
};

class MinStack
{
private:
  Node *head;
  int nodes;

public:
  MinStack() : head(nullptr), nodes(0){}


  void push(int x){
    Node *newNode = new Node;
    newNode->val = x;
    newNode->min = (empty()) ? x : min(x, head->min); // Actualizar el mínimo hasta este nodo    
    
    (empty())? newNode->next = nullptr : newNode->next = head;
    head = newNode;
    nodes++;
  }

  void pop()
  {
    if (empty())
    {
      cout << endl << "Stack vacío" << endl;
    }
    else
    {
      auto *temp = head;
      head = head->next;
      delete temp;
      temp = nullptr;
      nodes--;
    }
  }

  int top(){
    return head->val;
  }

  int getMin(){
    return head->min; // Devolver el mínimo valor hasta este nodo
  }

  int size(){
    return  nodes;
  }

  bool empty(){
    return !head;
  }
    
  void display()
  {
    auto *temp = head;
    while (temp != nullptr)
    {
      cout << temp->val << endl;;
      temp = temp->next;
    }
  }
};

int main(){
  MinStack minStack = MinStack();
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  cout << minStack.getMin() <<endl; // return -3
  minStack.pop();
  cout << minStack.top() << endl;// return 0
  cout << minStack.getMin() << endl; // return -2


  return 0;
}