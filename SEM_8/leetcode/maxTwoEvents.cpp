#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool sortByEndTime(const vector<int> &a, const vector<int> &b){
    return a[1] < b[1];
}

class Solution
{
public:
    int maxTwoEvents(vector<vector<int>> &events){
        sort(events.begin(), events.end(), sortByEndTime);

        int n = events.size();
        vector<int> dp(n, 0);

        for (int i = 0; i < n; ++i){
            dp[i] = events[i][2];
            for (int j = i - 1; j >= 0; --j){
                if (events[j][1] < events[i][0]){
                    dp[i] = max(dp[i], dp[j] + events[i][2]);
                    break;
                }
            }
            if (i > 0){
                dp[i] = max(dp[i], dp[i - 1]);
            }
        }

        return dp[n - 1];
    }
};

int main()
{
    vector<vector<int>> events = {{1, 3, 2}, {4, 5, 2}, {2, 4, 3}};
    Solution s;
    auto result = s.maxTwoEvents(events); 

    cout << result << endl;

    return 0;
}
