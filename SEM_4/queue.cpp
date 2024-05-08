// Estructura FIFO (First-In, First-Out)  --> Similar al Stack
/*
front -> apunta al inicio
rear -> apunta al final
(encolar) enqueue: O(1)  - (desencolar) dequeue: O(n)
 */
#include <iostream>
using namespace std;

template <typename T>
class Queue
{
private:
  T *array;
  int capacity;
  int front, rear;

public:
  Queue(int size)
  {
    this->capacity = size;
    this->array = new int[capacity];
    this->front = this->rear = -1;
  };

  ~Queue();
  bool isempty();
  void enqueue(int _value);
  T dequeue();
  void showfront();
  void showrear();
  void displayQueue();
  void resize();
};

template <typename T>
bool Queue<T>::isempty()
{
  bool verificar;
  return (front == -1 and rear == -1) ? verificar = true : verificar = false;
}

template <typename T>
void Queue<T>::enqueue(int value)
{
  if (rear == capacity - 1)
  {
    cout << "Queue esta lleno\n";
    // displayQueue();
    resize();
  }
  if (front == -1)
    front = 0;
  rear++;
  array[rear] = value;
}

template <typename T>
T Queue<T>::dequeue()
{
  if (isempty() == true)
  {
    cout << "Queue vacio" << endl;
  }
  else if (front == rear)
  {
    front = rear = -1;
  }
  else
  {
    front++;
  }
  return front;
}

template <typename T>
void Queue<T>::showfront()
{
  if (isempty())
  {
    cout << "Queue vacio" << endl;
  }
  else
  {
    cout << "front: " << array[front] << endl;
  }
}
template <typename T>
void Queue<T>::showrear()
{
  if (isempty())
  {
    cout << "Queue vacio" << endl;
  }
  else
  {
    cout << "rear: " << array[rear] << endl;
  }
}

template <typename T>
void Queue<T>::displayQueue()
{
  if (isempty())
  {
    cout << "Queue vacio" << endl;
  }
  else
  {
    for (int i = front; i <= rear; ++i)
    {
      cout << array[i] << " ";
    }
    cout << endl;
  }
}

template <typename T>
void Queue<T>::resize()
{
  int *arr_aux = new int[capacity * 2];
  int i = 0;
  int j = front;
  do
  {
    arr_aux[i++] = array[j];
    j = (j + 1) % capacity;
  } while (j != front);
  front = 0;
  rear = capacity - 1;
  array = arr_aux;
  cout << "Se ha redimensionado el queue" << endl;
};

template <typename T>
Queue<T>::~Queue()
{
  delete[] array;
}

int main()
{
  Queue<int> A(5);
  A.enqueue(1);
  A.enqueue(2);
  A.enqueue(3);
  A.enqueue(4);
  A.enqueue(5);

  A.displayQueue();
  cout << A.dequeue() << endl;
  A.displayQueue();
  
  return 0;
}