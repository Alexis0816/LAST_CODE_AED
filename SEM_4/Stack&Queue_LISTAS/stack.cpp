// Estructura LIFO (Last-In, First-Out)
#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:
  T *array;
  int capacity; // valor cambiable
  int size;

public:
  Stack(int max) : capacity(max), size(0){
    array = new T[capacity];
  };

  void redimensionar(int &longitud, int newlongitud){
    resize(array, longitud, newlongitud);
  }

  int _size(){
    return size;
  }

  int _capacity(){
    return capacity;
  }

  void push(T data){
    if (size == capacity){
      cout << "Redimensionando" << endl;
      redimensionar(capacity, capacity * 2); // O(n)
    }
    array[size] = data; // O(1)
    size += 1;
  };

  // O(1)
  int pop(){
    int data = array[size - 1];
    size--;
    return data;
  };

  // O(1)
  int top(){
    int indexTop = size - 1;
    return array[indexTop];
  };

  void display()
  {
    for (int i = 0; i < size; ++i){
      cout << array[i] << " ";
    }
    cout << endl;
  };

  ~Stack(){
    delete[] array;
  }

private:
  void resize(T *&arr, int &longi, int newlong){
    T *arr_aux = new T[newlong];
    for (int i = 0; i < longi; ++i) arr_aux[i] = arr[i];

    longi = newlong;
    arr = arr_aux;
  }
};

int main()
{
  Stack<int> s1(5);
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s1.push(4);
  s1.push(5);
  cout << s1.top() << endl;
  s1.display();
  s1.pop();
  s1.display();

  cout << s1.top() << endl;

  return 0;
}
