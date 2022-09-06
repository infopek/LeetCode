#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <queue>

#include <numeric>
#include <algorithm>

/* Node definition */
class Node
{
public:
	int val;
	std::vector<Node*> children;

	Node() {}
	Node(int _val)
		: val(_val) {}
	Node(int _val, std::vector<Node*> _children)
		: val(_val), children(_children) {}
};

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

/* Binary tree node definition. */
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

/* Recursively fills out the digits. */
void DigitsRec(std::vector<int>& result, int length, int diff, int num, int digit)
{
	if (length == 0)
	{
		result.push_back(num);
		return;
	}
	for (int d = 0; d <= 9; d++)
	{
		if (std::abs(d - digit) == diff)
			DigitsRec(result, length - 1, diff, 10 * num + d, d);
	}
}

/* 3 SEPT, 2022: NUMBERS WITH SAME CONSECUTIVE DIFFERENCES */
std::vector<int> NumsSameConsecDiff(int length, int diff)
{
	std::vector<int> result;
	for (int d = 1; d <= 9; d++)
		DigitsRec(result, length - 1, diff, d, d);

	return result;
}

void VertTravelDFS(TreeNode* root, std::map<int, std::map<int, std::multiset<int>>>& nodes, int x, int y)
{
	if (root)
	{
		nodes[x][y].insert(root->val);
		VertTravelDFS(root->left, nodes, x - 1, y + 1);
		VertTravelDFS(root->right, nodes, x + 1, y + 1);
	}
}

/* 4 SEPT, 2022: VERTICAL ORDER TRAVERSAL OF A BINARY TREE */
std::vector<std::vector<int>> VerticalTraversal(TreeNode* root)
{
	std::map<int, std::map<int, std::multiset<int>>> nodes;
	VertTravelDFS(root, nodes, 0, 0);

	std::vector<std::vector<int>> result;
	for (const auto& map : nodes)
	{
		std::vector<int> currCol;
		for (const auto mSet : map.second)
			currCol.insert(currCol.end(), mSet.second.begin(), mSet.second.end());

		result.push_back(currCol);
	}

	return result;
}

/* 5 SEPT, 2022: N-ARY TREE LEVEL ORDER TRAVERSAL */
std::vector<std::vector<int>> LevelOrder(Node* root)
{
	std::vector<std::vector<int>> result;
	if (!root)
		return result;

	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		int size = queue.size();
		std::vector<int> level;
		for (int i = 0; i < size; i++)
		{
			Node* curr = queue.front();
			level.push_back(curr->val);
			queue.pop();

			for (const auto& child : curr->children)
				queue.push(child);
		}

		result.push_back(level);
	}

	return result;
}

/* 6 SEPT, 2022: BINARY TREE PRUNING */
TreeNode* PruneTree(TreeNode* root)
{
	if (!root)
		return nullptr;

	root->left = PruneTree(root->left);
	root->right = PruneTree(root->right);
	if (!root->left && !root->right && root->val == 0)
		return nullptr;

	return root;
}

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

int main()
{
	TreeNode* root = new TreeNode(1);
	root->right = new TreeNode(0);
	root->right->right = new TreeNode(1);
	root->right->left = new TreeNode(0);

	PruneTree(root);
}