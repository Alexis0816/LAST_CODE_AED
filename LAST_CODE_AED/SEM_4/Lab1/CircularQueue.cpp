#include <iostream>
using namespace std;

struct Node {
  int value;
  Node *next;
};
class CQueue
{
  Node *front ;
  Node *rear ;

public:
  CQueue() : front(nullptr), rear(nullptr) {}
  
  void createNode(int val)
  {
    auto *newNode = new Node;
    newNode->value = val;
    newNode->next = nullptr;
    front = newNode;
    rear = newNode;
  }
  void enqueue(int val)
  {
    if (front == nullptr || rear == nullptr)
    {
      createNode(val);
    }
    else
    {
      auto *newNode = new Node;
      newNode->value = val;
      rear->next = newNode;
      newNode->next = front;
      rear = newNode;
    }
  }
  void dequeue()
  {
    auto *newNode = front;
    if (newNode)
    {
      front = front->next;
      delete newNode;
      newNode = nullptr;
    }
  }
  void display()
  {
    auto *temp = front;
    if (temp)
    {
      do
      {
        cout << temp->value << " ";
        temp = temp->next;
      } while (temp != rear->next);
      // así sé que  estoy llegando al final, porque el  next del último es el primero.
      cout << front->value << endl;
    }
  }
};
int main(void)
{
  CQueue cq;
  cq.enqueue(10);
  cq.enqueue(20);
  cq.enqueue(30);
  cq.enqueue(40);
  cq.enqueue(50);
  cq.enqueue(60);
  cq.enqueue(70);

  cq.display();
  
  cq.dequeue();
  
  cq.display();

  return 0;
}