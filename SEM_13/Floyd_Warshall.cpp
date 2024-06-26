#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

class TeamBuilder
{
public:
  vector<int> specialLocations(vector<string> routes)
  {
    int n = routes.size();
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

    // Inicialización de la matriz de adyacencia
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        if (routes[i][j] == '1')
        {
          dist[i][j] = 1;
        }
        else if (i == j)
        {
          dist[i][j] = 0;
        }
      }
    }

    // Floyd-Warshall
    for (int k = 0; k < n; ++k)
    {
      for (int i = 0; i < n; ++i)
      {
        for (int j = 0; j < n; ++j)
        {
          if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
          {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }

    int canReachAll = 0, reachableByAll = 0;

    // Contar las ubicaciones que pueden llegar a todas las demás
    for (int i = 0; i < n; ++i)
    {
      bool canReach = true;
      for (int j = 0; j < n; ++j)
      {
        if (dist[i][j] == INT_MAX)
        {
          canReach = false;
          break;
        }
      }
      if (canReach)
      {
        ++canReachAll;
      }
    }

    // Contar las ubicaciones a las que se puede llegar desde todas las demás
    for (int j = 0; j < n; ++j)
    {
      bool reachableBy = true;
      for (int i = 0; i < n; ++i)
      {
        if (dist[i][j] == INT_MAX)
        {
          reachableBy = false;
          break;
        }
      }
      if (reachableBy)
      {
        ++reachableByAll;
      }
    }

    return {canReachAll, reachableByAll};
  }
};

int main()
{
  TeamBuilder tb;

  vector<string> edges1 = {"010", "000", "110"};
  vector<int> result1 = tb.specialLocations(edges1);
  cout << "[" << result1[0] << ", " << result1[1] << "]" << endl; // Output: [1, 1]

  vector<string> edges2 = {"0010", "1000", "1100", "1000"};
  vector<int> result2 = tb.specialLocations(edges2);
  cout << "[" << result2[0] << ", " << result2[1] << "]" << endl; // Output: [1, 3]

  vector<string> edges3 = {"01000", "00100", "00010", "00001", "10000"};
  vector<int> result3 = tb.specialLocations(edges3);
  cout << "[" << result3[0] << ", " << result3[1] << "]" << endl; // Output: [5, 5]

  vector<string> edges4 = {"0110000", "1000100", "0000001", "0010000", "0110000", "1000010", "0001000"};
  vector<int> result4 = tb.specialLocations(edges4);
  cout << "[" << result4[0] << ", " << result4[1] << "]" << endl; // Output: [1, 3]

  return 0;
}
