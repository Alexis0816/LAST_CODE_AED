#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[low], nums[mid]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    vector<int> nums2 = {2, 0, 1};

    solution.sortColors(nums1);
    solution.sortColors(nums2);

    cout << "Salida para nums1: ";
    for (int num : nums1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Salida para nums2: ";
    for (int num : nums2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
