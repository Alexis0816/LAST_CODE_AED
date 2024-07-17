#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

class Solution
{
public:
  double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
  {
    // vector de probabilidades máximas con todos sus valores en -infinito excepto el nodo de inicio
    vector<double> maxProb(n, -numeric_limits<double>::infinity());
    maxProb[start_node] = 0; // log(1) = 0

    // actualizamos según las n-1 relajaciones
    for (int i = 0; i < n - 1; ++i)
    {
      bool updated = false;
      for (int j = 0; j < edges.size(); ++j)
      {
        int u = edges[j][0];
        int v = edges[j][1];
        double logProb = log(succProb[j]);

        if (maxProb[u] != -numeric_limits<double>::infinity() && maxProb[u] + logProb > maxProb[v])
        {
          maxProb[v] = maxProb[u] + logProb;
          updated = true;
        }
        if (maxProb[v] != -numeric_limits<double>::infinity() && maxProb[v] + logProb > maxProb[u])
        {
          maxProb[u] = maxProb[v] + logProb;
          updated = true;
        }
      }
      // Si no se actualiza en una iteración, podemos terminar antes
      if (!updated)
        break;
    }

    // Si no hay un camino de start_node a end_node, devolvemos 0
    if (maxProb[end_node] == -numeric_limits<double>::infinity())
    {
      return 0.0;
    }

    // Devolvemos la probabilidad exponencial de logProbabilidad máxima
    return exp(maxProb[end_node]);
  }
};

int main()
{
  Solution sol;
  int n = 3;
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
  vector<double> succProb = {0.5, 0.5, 0.2};
  int start_node = 0;
  int end_node = 2;

  double result = sol.maxProbability(n, edges, succProb, start_node, end_node);
  cout << "Output: " << result << endl;



  vector<double> succProb2 = {0.5, 0.5, 0.3};
  double result2 = sol.maxProbability(n, edges, succProb2, start_node, end_node);
  cout << "Output: " << result2 << endl;


  return 0;
}
