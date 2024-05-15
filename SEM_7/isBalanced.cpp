#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isBalanced(const vector<int>& arr, TreeNode*& root) {
    if (arr.empty()) {
        root = nullptr;
        return true;
    }

    int medio = arr.size() / 2;
    root = new TreeNode(arr[medio]);

    if (!isBalanced(vector<int>(arr.begin(), arr.begin() + medio), root->left) ||
        !isBalanced(vector<int>(arr.begin() + medio + 1, arr.end()), root->right)) {
        return false;
    }

    return true;
}

bool AVLsequence(const vector<int>& array, TreeNode*& root) {
    vector<int> array_ordenado = array;
    sort(array_ordenado.begin(), array_ordenado.end());
    return isBalanced(array_ordenado, root);
}

int main() {
	vector<int> array = {2, 4, 1, 3, 5, 6, 7};
	// vector<int> array = {1, 2, 3};
	TreeNode* root = nullptr;
	bool builded = AVLsequence(array, root);
	
	cout <<  builded << endl;

	return 0;
}



