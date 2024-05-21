#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    void heapify(vector<int>& arr, int n, int i) {
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l] < arr[smallest]) {
            smallest = l;
        }

        if (r < n && arr[r] < arr[smallest]) {
            smallest = r;
        }

        if (smallest != i) {
            swap(arr[i], arr[smallest]);
            heapify(arr, n, smallest);
        }
    }

public:
    void heapSort(vector<int>& arr) {
        int n = arr.size();

        // Construir el min heap (reorganizar el array)
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Extraer elementos uno por uno del min heap
        for (int i = n - 1; i > 0; i--) {
            // Mover la raíz actual al final
            swap(arr[0], arr[i]);

            // Llamar heapify en el heap reducido
            heapify(arr, i, 0);
        }
    }
};

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    MinHeap minHeap;
    minHeap.heapSort(arr);

    cout << "Array ordenado en orden descendente: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
