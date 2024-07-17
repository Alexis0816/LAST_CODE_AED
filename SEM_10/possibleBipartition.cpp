#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class DisjoinSet
{
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;

public:
    DisjoinSet() = default;

    DisjoinSet(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            Makeset(i);
        }
    }

    void Makeset(int x)
    {
        parent[x] = x;
        rank[x] = 0;
    }

    int Find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y)
    {
        int xRoot = Find(x);
        int yRoot = Find(y);

        if (xRoot == yRoot)
            return;

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
    }

    bool is_connected(int x, int y)
    {
        return (Find(x) == Find(y));
    }
};

bool possibleBipartition(int n, vector<vector<int>> &dislikes)
{
    DisjoinSet ds(n);
    vector<vector<int>> graph(n + 1);

    for (auto &d : dislikes)
    {
        graph[d[0]].push_back(d[1]);
        graph[d[1]].push_back(d[0]);
    }

    vector<int> color(n + 1, -1);

    for (int i = 1; i <= n; ++i)
    {
        if (color[i] == -1)
        {
            queue<int> q;
            q.push(i);
            color[i] = 0;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neighbor : graph[node])
                {
                    if (color[neighbor] == -1)
                    {
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    }
                    else if (color[neighbor] == color[node])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    int n = 4;
    vector<vector<int>> dislikes = {{1, 2}, {1, 3}, {2, 4}};
    cout << (possibleBipartition(n, dislikes) ? "true" : "false") << endl;
    return 0;
}
