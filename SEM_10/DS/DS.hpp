#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*DisjoinSet with optimization by rank & using unordered_*/
template <typename T>
class DisjoinSet
{
private:
    unordered_map<int, int> parent;
    unordered_map<T, int> rank;

public:
    DisjoinSet() = default;

    DisjoinSet(vector<T> &data)
    {
        for (int i = 0; i < data.size(); i++)
        {
            Makeset(i);
        }
    };

    void Makeset(int x)
    {
        parent[x] = x;
        rank[x] = 0;
    };

    int Find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void p()
    {
        cout << "PADRE: ";
        for (int i = 0; i < parent.size(); ++i)
        {
            cout << parent[i] << " ";
        }
        cout << endl;
    }
    void r()
    {
        cout << "RANK:  ";
        for (int i = 0; i < rank.size(); ++i)
        {
            cout << rank[i] << " ";
        }
        cout << endl;
    }

    void Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot)
        {
            return;
        }
        if (rank[xRoot] > rank[yRoot])
        {
            parent[yRoot] = xRoot;
        }
        else if (rank[xRoot] < rank[yRoot])
        {
            parent[xRoot] = yRoot;
        }
        else
        {
            parent[xRoot] = yRoot;
            rank[yRoot]++;
        }
    };

    int sets()
    {
        int tam = 0;
        for (int i = 0; i < parent.size(); ++i)
        {
            if (parent[i] == i)
                tam += 1;
        }
        return tam;
    };

    bool is_connected(int x, int y)
    {
        return (Find(x) == Find(y)) ? true : false;
    };
};