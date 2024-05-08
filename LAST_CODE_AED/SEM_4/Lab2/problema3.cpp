#include <iostream>
using namespace std;

struct Stack
{
    int val;
    int min{}; // guardo el mínimo valor
    Stack *next;
    Stack(int _val): val(_val), next(nullptr) {}
};

class MinStack
{
private:
    Stack *head;
    int nodes;

public:
    MinStack() : head(nullptr), nodes(0) {}

    void push(int val)
    {
        Stack *newNode = new Stack{val};

        newNode->min = (empty()) ? val : min(val, head->min); // Actualizar el mínimo hasta

        (empty()) ? newNode->next = nullptr : newNode->next = head;
        head = newNode;
        nodes++;
    }

    void pop(){
        if (empty()){ cout << endl << "Stack vacío" << endl;
        }
        else {
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
      return head->min; // Devuelve el mínimo valor
    }

    // para validar si está vacio o no
    bool empty(){
      return !head;
    }

    // extra
    int size(){
      return nodes;
    }
};

// TEST 
// int main(){

//     MinStack minStack = MinStack();
//     minStack.push(-2);
//     minStack.push(0);
//     minStack.push(-3);
//     cout << minStack.getMin() << endl; // return -3
//     minStack.pop();
//     cout << minStack.top() << endl;    // return 0
//     cout << minStack.getMin() << endl; // return -2

//     return 0;
// }
