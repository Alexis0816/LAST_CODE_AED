#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Función para calcular el MCD
int calcularMCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

template <typename T>
class DisjoinSetArray {
private:
    int *rank, *parent;
    int size;

public:
    DisjoinSetArray(vector<T> &data) {
        size = data.size();
        rank = new int[size];
        parent = new int[size];
        for (int i = 0; i < size; i++) {
            MakeSet(i);
        }
    }

    ~DisjoinSetArray() {
        delete[] rank;
        delete[] parent;
    }

    void MakeSet(int x) {
        parent[x] = x;
        rank[x] = 0;
    }

    int Find(int x) {
        if (parent[x] != x) {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y) {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot) return;

        if (rank[xRoot] > rank[yRoot]) {
            parent[yRoot] = xRoot;
        } else if (rank[xRoot] < rank[yRoot]) {
            parent[xRoot] = yRoot;
        } else {
            parent[yRoot] = xRoot;
            rank[xRoot]++;
        }
    }
};

bool gcdSort(vector<int>& nums) {
    int n = nums.size();
    DisjoinSetArray<int> ds(nums);

    // Unir conjuntos según el MCD
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (calcularMCD(nums[i], nums[j]) > 1) {
                ds.Union(i, j);
            }
        }
    }

    // Crear un vector de pares (representante, número original)
    vector<pair<int, int>> repNumPairs(n);
    for (int i = 0; i < n; ++i) {
        repNumPairs[i] = {ds.Find(i), nums[i]};
    }

    // Ordenar el array original
    vector<int> sortedNums = nums;
    sort(sortedNums.begin(), sortedNums.end());

    // Verificar si podemos obtener el array ordenado
    for (int i = 0; i < n; ++i) {
        int repSorted = ds.Find(find(nums.begin(), nums.end(), sortedNums[i]) - nums.begin());
        int repOriginal = ds.Find(i);
        if (repSorted != repOriginal) {
            return false;
        }
    }

    return true;
}

int main() {
    vector<int> nums = {7, 21, 3};
    bool resultado = gcdSort(nums);
    cout << "Resultado: " << (resultado ? "true" : "false") << endl;

    return 0;
}
