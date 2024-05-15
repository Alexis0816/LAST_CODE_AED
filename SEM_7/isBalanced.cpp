#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <class T>
struct Node
{
	T val;
	Node<T> *next;
};

template <class T>
class Queue
{
	Node<T> *front;
	Node<T> *rear;
	int nodes;

public:
	Queue() : nodes(0) { front = rear = nullptr; }

	int size()
	{
		return nodes;
	}

	T _front()
	{
		return front->val;
	}

	T _rear()
	{
		return rear->val;
	}

	bool empty()
	{
		return (!front && !rear) ? true : false;
	}

	void enqueue(T ele)
	{
		auto *temp = new Node<T>();
		temp->val = ele;
		temp->next = nullptr;

		if (empty())
			front = rear = temp;
		else
		{
			rear->next = temp;
			rear = temp;
		}
		nodes++;
	};

	void dequeue()
	{
		Node<T> *temp;
		if (empty())
			cout << endl << "Queue vacio." << endl;
		else
		{
			temp = front;
			if (front == rear)
				rear = rear->next; // si el tamaño de la cola es 1;
			front = front->next;
			nodes--;
		}
	};
};

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
	
	bool isBalanced(vector<int> &vec)
	{
		// Queue<TreeNode *> queue;

		// queue.enqueue(root);
		// while (!queue.empty())
		// {
		// 	TreeNode *curr = queue._rear();
		// 	int balanceFactor = this->height(curr->left) - this->height(curr->right);
		// 	if (abs(balanceFactor) > 1)
		// 	{
		// 		return false;
		// 	}
		// 	queue.dequeue();
		// 	if (curr->left)
		// 	{
		// 		queue.enqueue(curr->left);
		// 	}
		// 	if (curr->right)
		// 	{
		// 		queue.enqueue(curr->right);
		// 	}
		// }
		// return true;
	}
};

void test()
{
	vector<int> array = {2, 4, 1, 3, 5, 6, 7};
	cout << (Solution().isBalanced(array)) << endl;
	// true --> devuelve bool?


	// vector<int> array = {2, 4, 1, 3, 5, 6, 7};	
	// cout << (Solution().isBalanced(array)) << endl;
	// // false --> devuelve bool?

}

int main()
{
	test();
	return 0;
}