#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <cmath>
using namespace std;

/*INTEGRANTES:

->DANIEL CASQUINO

->ALEXIS RAZA

-> GABRIEL BLANCO
*/

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
	int max(int a, int b)
	{
		return a > b ? a : b;
	}
	int height(TreeNode *node)
	{
		return !node ? -1 : 1 + max(height(node->left), height(node->right));
	}
	bool isBalanced(TreeNode *root)
	{
		std::queue<TreeNode *> queue;
		queue.push(root);
		while (!queue.empty())
		{
			TreeNode *curr = queue.back();
			int balanceFactor = this->height(curr->left) - this->height(curr->right);
			if (abs(balanceFactor) > 1)
			{
				return false;
			}
			queue.pop();
			if (curr->left)
			{
				queue.push(curr->left);
			}
			if (curr->right)
			{
				queue.push(curr->right);
			}
		}
		return true;
	}
};

void test()
{

	TreeNode *nodo_a = new TreeNode(3);
	TreeNode *nodo_b = new TreeNode(9);
	TreeNode *nodo_c = new TreeNode(20);
	TreeNode *nodo_d = new TreeNode(15);
	TreeNode *nodo_e = new TreeNode(7);

	nodo_a->left = nodo_b;
	nodo_a->right = nodo_c;
	nodo_c->left = nodo_d;
	nodo_c->right = nodo_e;
	assert(Solution().isBalanced(nodo_a) == true);

	nodo_a = new TreeNode(1);
	nodo_b = new TreeNode(2);
	nodo_c = new TreeNode(2);
	nodo_d = new TreeNode(3);
	nodo_e = new TreeNode(3);
	TreeNode *nodo_f = new TreeNode(4);
	TreeNode *nodo_g = new TreeNode(4);
	nodo_a->left = nodo_b;
	nodo_a->right = nodo_c;
	nodo_b->left = nodo_d;
	nodo_b->right = nodo_e;
	nodo_d->left = nodo_f;
	nodo_d->left = nodo_g;
	assert(Solution().isBalanced(nodo_a) == false);
}

int main()
{
	test();
	return 0;
}