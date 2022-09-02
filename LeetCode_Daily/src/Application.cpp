#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

#include <numeric>
#include <algorithm>

/* Singly-linked list node */
struct ListNode
{
	int val;
	ListNode* next;

	ListNode()
		: val(0), next(nullptr) {}
	ListNode(int x)
		: val(x), next(nullptr) {}
	ListNode(int x, ListNode* next)
		: val(x), next(next) {}
};

/* Binary tree node */
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode()
		: val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x)
		: val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right)
		: val(x), left(left), right(right) {}
};

/* Helper method */
void DFSCount(TreeNode* node, int& goodNodes, int prevPathMax, int pathMax)
{
	if (!node)
	{
		pathMax = prevPathMax;
		prevPathMax = INT_MIN;
		return;
	}
	
	if (node->val >= pathMax)
	{
		prevPathMax = pathMax;
		pathMax = node->val;
		goodNodes++;
	}

	std::cout << node->val << ", ";

	DFSCount(node->left, goodNodes, prevPathMax, pathMax);
	DFSCount(node->right, goodNodes, prevPathMax, pathMax);
}

/* 1 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */
int GoodNodes(TreeNode* root)
{
	int result = 0;
	DFSCount(root, result, INT_MIN, INT_MIN);

	return result;
}

/* Calculates the height of a binary tree. */
int TreeHeight(TreeNode* root)
{
	if (!root)
		return 0;
	else
	{
		int leftHeight = TreeHeight(root->left);
		int rightHeight = TreeHeight(root->right);

		if (leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}

/* Helps calculate the average of a level in a tree with root node. */
void AvgCurrLevel(TreeNode* root, int level, double& sum, int& totalNodes)
{
	if (!root)
		return;
	if (level == 0)
	{
		sum += root->val;
		totalNodes++;
	}
	else if (level > 0)
	{
		AvgCurrLevel(root->left, level - 1, sum, totalNodes);
		AvgCurrLevel(root->right, level - 1, sum, totalNodes);
	}
}

/* 2 SEPT, 2022: AVERAGE OF LEVELS IN BINARY TREE */
std::vector<double> AverageOfLevels(TreeNode* root)
{
	int height = TreeHeight(root);
	std::vector<double> averages(height);
	for (int l = 0; l < height; l++)
	{
		double sum = 0;
		int totalNodes = 0;
		AvgCurrLevel(root, l, sum, totalNodes);
		averages[l] = (double)sum / totalNodes;
	}

	return averages;
}

/* 3 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 4 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 5 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 6 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 7 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 8 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 9 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 10 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 11 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 12 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 13 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 14 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 15 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 16 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 17 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 18 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 19 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 20 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 21 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 22 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 23 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 24 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 25 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 26 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 27 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 28 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 29 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

/* 30 SEPT, 2022: COUNT GOOD NODES IN BINARY TREE */

int main()
{
	
}