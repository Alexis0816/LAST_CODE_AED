#include <iostream>
using namespace std;

struct Node {
    int val;
    Node *next;
};
class Queue {
    Node *front;
    Node *rear;
    int nodes;

public:

    Queue(): nodes(0) { front = rear = nullptr; }

    int size(){
      return nodes;
    }

    int _front(){
      return front->val;
    }

    int _rear(){
      return rear->val;
    }

    bool empty(){
        return (!front && !rear) ? true: false;
    }
    
    void enqueue(int ele){
      auto *temp = new Node();
      temp->val = ele;
      temp->next = nullptr;

      if (empty())
        front = rear = temp;
      else {
        rear->next = temp;
        rear = temp;
      }
      nodes++;
    };

    void dequeue(){
      if (empty())
        cout << endl << "Queue vacio." << endl;
      else {
        auto *temp = front;
        if (front == rear) rear = rear->next; // if length of queue is 1;
        front = front->next;
        delete temp;
        nodes--;
      }
    };
    
    void display(){
      auto *temp = front;
      while (temp) {
          cout << temp->val << endl;
          temp = temp->next;
      }
    };
};


int main() {
  Queue q;
  cout<< "Size: "<< q.size() <<endl;
  q.enqueue(1);
  cout<< "Size: "<< q.size() <<endl;
  q.enqueue(2);
  cout<< "Size: "<< q.size() <<endl;
  q.enqueue(3);
  cout<< "Size: "<< q.size() <<endl;
  q.enqueue(4);
  cout<< "Size: "<< q.size() <<endl;

  q.display();
  cout << "Front: "<<q._front() << endl;
  cout << "Rear: "<<q._rear() << endl;

  q.dequeue();
  
  cout<< "Size: "<< q.size() <<endl;

  q.display();
  
  cout << "Front: "<<q._front() << endl;
  cout << "Rear: "<<q._rear() << endl;


  
  
  
  
  return 0;
}