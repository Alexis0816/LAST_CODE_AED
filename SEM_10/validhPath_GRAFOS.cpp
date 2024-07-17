#include <iostream>
#include <unordered_map>
#include <vector>
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
    for (int i = 0; i < n; i++)
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

bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
{
  DisjoinSet ds(n);

  for (auto &edge : edges)
  {
    ds.Union(edge[0], edge[1]);
  }

  return ds.is_connected(source, destination);
}

int main()
{
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}};
  int source = 0;
  int destination = 2;
  cout << (validPath(n, edges, source, destination) ? "true" : "false") << endl;
  return 0;
}
