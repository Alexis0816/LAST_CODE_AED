#include <iostream>
#include <string>
using namespace std;

struct Node
{
  char val;
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

  char top(){
    return head->val;
  }

  void push(char ele){
    Node *newNode = new Node;
    newNode->val = ele;
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
      cout << temp->val << " borrado" << endl;
      head = head->next;
      delete temp;
      temp = nullptr;
      nodes--;
    }
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

  void createStackChar(string word){
    Stack s;
    for(auto e : word){
      s.push(e);
    }
  }

  int depth(string s){
    if(empty())
      return;
    else if(s == "("){

    }
  }
};

int main()
{
  string s = "(1+(2*3)+((8)+4))+1";
  Stack SS;



  return 0;
}