#include <iostream>
#include <queue>

using namespace std;

int main()
{
  int arr[] = {1, 2, 3, 4, 5, 6};
  priority_queue<int> max;

  for (auto i : arr)
    max.push(i);

  // Recorremos la cola de prioridad
  while (!max.empty())
  {
    // Obtenemos y eliminamos el elemento con la mayor prioridad
    int elem = max.top();
    max.pop();
    cout << elem << " "; // Imprimimos el valor del elemento
  }
  cout << endl;

  return 0;
}
