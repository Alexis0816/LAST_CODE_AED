#include <iostream>
using namespace std;

struct Node
{
  int val;
  Node *next;
};

class Stack
{
private:
  Node *head;
  int nodes;

public:
  Stack() : head(nullptr), nodes(0){}

  int size(){
    return  nodes;
  }

  bool empty(){
    return !head;
  }

  int top(){
    return head->val;
  }

  void push(int x){
    Node *newNode = new Node;
    newNode->val = x;
    (empty())? newNode->next = nullptr : newNode->next = head;
    
    head = newNode;
    nodes++;
  }


  void pop(){
    if (empty())
      cout << endl << "Stack vacío" << endl;
    else
    {
      auto *temp = head;
      head = head->next;
      delete temp;
      nodes--;
    }
  }
  
  void display(){
    auto *temp = head;
    while (temp){
      cout << temp->val << endl;;
      temp = temp->next;
    }
  }
};

int main()
{
  Stack s;
  cout<< "Size: "<< s.size() <<endl;
  s.push(1);
  cout<< "Size: "<< s.size() <<endl;
  s.push(2);
  cout<< "Size: "<< s.size() <<endl;
  s.push(3);
  cout<< "Size: "<< s.size() <<endl;
  s.push(4);
  cout<< "Size: "<< s.size() <<endl;

  s.display();
  cout <<"Head value: "<< s.top() <<endl;
  
  s.pop();
  
  cout<< "Size: "<< s.size() <<endl;

  s.display();
  cout <<"Head value: "<< s.top() <<endl;

  return 0;
}