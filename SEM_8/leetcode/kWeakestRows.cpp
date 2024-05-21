#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution
{
    struct Node
    {
        int _sum{};
        int _index{};
        Node(int sum, int index) : _sum(sum), _index(index) {}
        ~Node() {}
    };

    int sum(vector<int> &a)
    {
        int res = 0;
        for (auto e : a)
        {
            res += e;
        }
        return res;
    }

public:
    vector<int> kWeakestRows(vector<vector<int>> &mat, int k)
    {
        auto lesserNode = [](Node &a, Node &b)
        {
            if (a._sum != b._sum)
            {
                return a._sum > b._sum;
            }
            return a._index > b._index;
        };

        std::priority_queue<Node, std::vector<Node>, decltype(lesserNode)> queue(lesserNode);
        for (int i = 0; i < mat.size(); ++i)
        {
            int val = sum(mat[i]);
            Node n = Node(val, i);
            queue.push(n);
        }
        vector<int> kWeakest;
        for (int i = 0; i < k; ++i)
        {
            int index = queue.top()._index;
            kWeakest.push_back(index);
            queue.pop();
        }
        return kWeakest;
    }
};

// int main()
// {
//     vector<vector<int>> mat = {
//         {1, 1, 0, 0, 0},
//         {1, 1, 1, 1, 0},
//         {1, 0, 0, 0, 0},
//         {1, 1, 0, 0, 0},
//         {1, 1, 1, 1, 1}};

//     auto res = Solution().kWeakestRows(mat, 3);
//     for (auto e : res)
//     {
//         std::cout << e << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }