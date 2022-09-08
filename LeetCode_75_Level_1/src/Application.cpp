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
class Node {
public:
	int val;
	std::vector<Node*> children;

	Node() {}
	Node(int _val)
		: val(_val) {}
	Node(int _val, std::vector<Node*> _children)
		: val(_val), children(_children) {}
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

/* Linked list definition */
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

// --------------------------------------------- //

// -------------	DAY 1	------------- //

/* RUNNING SUM OF 1D ARRAY */
std::vector<int> RunningSum(const std::vector<int>& nums)
{
	const int size = nums.size();
	std::vector<int> runningSum(size);

	int currSum = 0;
	for (int i = 0; i < size; i++)
	{
		currSum += nums[i];
		runningSum[i] = currSum;
	}

	return runningSum;
}

/* FIND PIVOT INDEX */
int PivotIndex(const std::vector<int>& nums)
{
	const int size = nums.size();

	int prefixSum = 0;
	for (int i = 0; i < size; i++)
	{
		prefixSum += nums[i];
	}

	int leftSum = 0;
	int rightSum = prefixSum;
	for (int i = 0; i < size; i++)
	{
		rightSum -= nums[i];
		if (leftSum == rightSum)
			return i;

		leftSum += nums[i];
	}

	return -1;
}

// -------------	DAY 2	------------- //

/* ISOMORPHIC STRINGS */
bool IsIsomorphic(const std::string& str1, const std::string& str2)
{
	const int length = str1.length();
	std::unordered_map<char, char> mapping1To2;
	std::unordered_map<char, char> mapping2To1;

	for (int i = 0; i < length; i++)
	{
		auto it1 = mapping1To2.find(str1[i]);
		auto it2 = mapping2To1.find(str2[i]);

		if (it1 == mapping1To2.end() && it2 == mapping2To1.end())
		{
			mapping1To2[str1[i]] = str2[i];
			mapping2To1[str2[i]] = str1[i];
		}

		else if (mapping1To2[str1[i]] != str2[i] || mapping2To1[str2[i]] != str1[i])
			return false;
	}

	return true;
}

/* IS SUBSEQUENCE */
bool IsSubsequence(const std::string& string, const std::string& text)
{
	const int strLength = string.length();
	const int textLength = text.length();
	if (strLength == 0)			return true;
	else if (textLength == 0)	return false;

	char curr = string[0];
	int strIdx = 0;
	int textIdx = 0;
	while (textIdx < textLength)
	{
		char candidate = text[textIdx];
		if (curr == candidate)
		{
			strIdx++;
			if (strIdx == strLength)
				return true;
			else
				curr = string[strIdx];
		}

		textIdx++;
	}

	return false;
}

// -------------	DAY 3	------------- //

/* MERGE TWO SORTED LISTS */
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
	if (!list1 && !list2)	// both lists are empty
		return nullptr;

	ListNode* merged = new ListNode();
	ListNode* mergedHead = merged;
	ListNode* curr1 = list1;
	ListNode* curr2 = list2;

	while (curr1 && curr2)
	{
		if (curr1->val < curr2->val)
		{
			merged->val = curr1->val;
			curr1 = curr1->next;
			merged->next = (curr1 || curr2) ? new ListNode() : nullptr;

			merged = merged->next;
		}
		else if (curr2->val < curr1->val)
		{
			merged->val = curr2->val;
			curr2 = curr2->next;
			merged->next = (curr1 || curr2) ? new ListNode() : nullptr;

			merged = merged->next;
		}
		else
		{
			merged->val = curr1->val;
			curr1 = curr1->next;
			merged->next = (curr1 || curr2) ? new ListNode() : nullptr;

			merged = merged->next;
			merged->val = curr2->val;
			curr2 = curr2->next;
			merged->next = (curr1 || curr2) ? new ListNode() : nullptr;

			merged = merged->next;
		}
	}
	while (curr1)
	{
		merged->val = curr1->val;
		curr1 = curr1->next;
		merged->next = curr1 ? new ListNode() : nullptr;;

		merged = merged->next;
	}
	while (curr2)
	{
		merged->val = curr2->val;
		curr2 = curr2->next;
		merged->next = curr2 ? new ListNode() : nullptr;;

		merged = merged->next;
	}

	return mergedHead;
}

/* REVERSE LINKED LIST */
ListNode* ReverseList(ListNode* head)
{
	// Iterative
	ListNode* prev = nullptr;
	ListNode* curr = head;
	while (curr)
	{
		ListNode* temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}

	return prev;

	// Recursive
	/*if (!(head && head->next))	return head;
	ListNode* rev = ReverseList(head->next);
	head->next->next = head;
	head->next = nullptr;
	return rev;*/
}

// -------------	DAY 4	------------- //

/* MIDDLE OF THE LINKED LIST */
ListNode* MiddleNode(ListNode* head)
{
	if (!head)
		return head;

	ListNode* slow = head;
	ListNode* fast = head;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

/* LINKED LIST CYCLE II */
ListNode* DetectCycle(ListNode* head)
{
	// O(n) space complexity
	std::unordered_map<ListNode*, bool> visited;

	ListNode* curr = head;
	while (curr)
	{
		if (visited.find(curr) != visited.end())
			return curr;
		else
			visited[curr] = true;
		curr = curr->next;
	}

	return nullptr;

	// O(1) space complexity: slow-fast pointers

}

// -------------	DAY 5	------------- //

/* BEST TIME TO BUY AND SELL STOCK */
int MaxProfit(const std::vector<int>& prices)
{
	const int size = prices.size();

	int maxProfit = 0;
	int buy = 0;
	for (int i = 0; i < size; i++)
	{
		int profit = prices[i] - prices[buy];
		if (prices[i] < prices[buy])
			buy = i;
		maxProfit = std::max(maxProfit, profit);
	}

	return maxProfit;
}

/* LONGEST PALINDROME */
int LongestPalindrome(const std::string& str)
{
	int length = str.length();

	std::unordered_map<char, int> charCount;
	int result = 0;
	for (const auto& c : str)
	{
		charCount[c]++;
		if (charCount[c] % 2 == 0)
		{
			result += 2;
			length -= 2;
		}
	}

	// If length == 0, then we used all of the character, otherwise we could take one to be the center of the palindrome
	return (length > 0) ? result + 1 : result;
}

// -------------	DAY 6	------------- //

void PreorderRec(Node* root, std::vector<int>& result)
{
	if (!root)
		return;

	result.push_back(root->val);

	for (const auto& node : root->children)
		PreorderRec(node, result);
}

/* N-ARY TREE PREORDER TRAVERSAL */
std::vector<int> Preorder(Node* root)
{
	// Recursive
	//std::vector<int> result;
	//PreorderRec(root, result);
	//return result;

	// Iterative
	std::vector<int> result;
	if (!root)
		return result;

	std::stack<Node*> stack;
	stack.push(root);
	while (!stack.empty())
	{
		Node* top = stack.top();
		stack.pop();
		result.push_back(top->val);

		int numNodes = top->children.size();
		for (int i = numNodes - 1; i >= 0; i--)
			stack.push(top->children[i]);
	}

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

/* Traverses the tree in level order. */
void LevelOrderRec(TreeNode* root, int level, std::vector<int>& temp)
{
	if (!root)
		return;
	if (level == 0)
	{
		temp.push_back(root->val);
	}
	else if (level > 0)
	{
		LevelOrderRec(root->left, level - 1, temp);
		LevelOrderRec(root->right, level - 1, temp);
	}
}

/* BINARY TREE LEVEL ORDER TRAVERSAL */
std::vector<std::vector<int>> LevelOrder(TreeNode* root) 
{
	int height = TreeHeight(root);
	std::vector<std::vector<int>> result(height);
	for (int l = 0; l < height; l++)
	{
		std::vector<int> temp;
		LevelOrderRec(root, l, temp);
		result[l] = temp;
	}

	return result;
}

// -------------	DAY 7	------------- //

/* BINARY SEARCH */
int Search(const std::vector<int>& nums, const int target)
{
	const int size = nums.size();

	int low = 0;
	int high = size - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (nums[mid] == target)
			return mid;
		else if (nums[mid] < target)
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

bool IsBadVersion(int version)
{
	return true;
}

/* FIRST BAD VERSION */
int FirstBadVersion(const int n)
{
	int low = 1;
	int high = n;
	while (low < high)
	{
		int mid = low + (high - low) / 2;
		if (IsBadVersion(mid))
			high = mid;
		else
			low = mid + 1;
	}
	
	return low;
}

// -------------	DAY 8	------------- //

/* VALIDATE BINARY SEARCH TREE */
bool IsValidBST(TreeNode* root)
{
	std::stack<TreeNode*> stack;

	long prev = LONG_MIN;
	TreeNode* curr = root;
	while (curr || !stack.empty())
	{
		while (curr)
		{
			stack.push(curr);
			curr = curr->left;
		}

		curr = stack.top();
		stack.pop();
		if (curr->val <= prev)
			return false;

		prev = curr->val;
		curr = curr->right;
	}

	return true;
}

/* LOWEST COMMON ANCESTOR OF A BINARY SEARCH TREE */
TreeNode* LowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
	if (root)
	{
		int minVal = std::min(p->val, q->val);
		int maxVal = std::max(p->val, q->val);
		if (minVal < root->val && root->val < maxVal)
			return root;
		else if (root->val < minVal)
			return LowestCommonAncestor(root->right, p, q);
		else if (root->val > maxVal)
			return LowestCommonAncestor(root->left, p, q);
	}
	return root;
}

// -------------	DAY 9	------------- //

void FloodFillDFS(std::vector<std::vector<int>>& image, const int rows, const int cols, int row, int col, const int original, const int newColor)
{
	if (image[row][col] != newColor)
	{
		// Fill
		image[row][col] = newColor;

		// Up
		if (row - 1 >= 0 && image[row - 1][col] == original)
			FloodFillDFS(image, rows, cols, row - 1, col, original, newColor);

		// Down
		if (row + 1 < rows && image[row + 1][col] == original)
			FloodFillDFS(image, rows, cols, row + 1, col, original, newColor);

		// Left
		if (col - 1 >= 0 && image[row][col - 1] == original)
			FloodFillDFS(image, rows, cols, row, col - 1, original, newColor);

		// Right
		if (col + 1 < cols && image[row][col + 1] == original)
			FloodFillDFS(image, rows, cols, row, col + 1, original, newColor);
	}
}

/* FLOOD FILL */
std::vector<std::vector<int>> FloodFill(std::vector<std::vector<int>>& image, int row, int col, const int newColor) 
{
	const int rows = image.size();
	const int cols = image[0].size();
	const int original = image[row][col];
	FloodFillDFS(image, rows, cols, row, col, original, newColor);

	return image;
}

void NumIslandsDFS(std::vector<std::vector<char>>& grid, const int rows, const int cols, int row, int col)
{
	if (grid[row][col] == '1')
	{
		grid[row][col] = '0';

		// Up
		if (row - 1 >= 0)
			NumIslandsDFS(grid, rows, cols, row - 1, col);

		// Down
		if (row + 1 < rows)
			NumIslandsDFS(grid, rows, cols, row + 1, col);

		// Left
		if (col - 1 >= 0)
			NumIslandsDFS(grid, rows, cols, row, col - 1);

		// Right
		if (col + 1 < cols)
			NumIslandsDFS(grid, rows, cols, row, col + 1);
	}
}

/* NUMBER OF ISLANDS */
int NumIslands(std::vector<std::vector<char>>& grid)
{
	int islands = 0;
	const int rows = grid.size();
	const int cols = grid[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j] == '1')
			{
				NumIslandsDFS(grid, rows, cols, i, j);	// mark every land as visited
				islands++;
			}
		}
	}

	return islands;
}

// -------------	DAY 10	------------- //

/* FIBONACCI NUMBER */
int Fib(const int n)
{
	if (n == 0)
		return 0;

	int a = 0;
	int b = 1;
	int result = a + b;

	int i = 1;
	while (i < n)
	{
		result = a + b;
		a = b;
		b = result;

		i++;
	}

	return result;
}

/* CLIMBING STAIRS */
int ClimbStairs(const int n)
{
	if (n == 1 || n == 2)
		return n;

	int* dp = new int[n + 1];
	dp[1] = 1;
	dp[2] = 2;

	for (int i = 3; i <= n; i++)
		dp[i] = dp[i - 1] + dp[i - 2];

	return dp[n];
}

// -------------	DAY 11	------------- //

/* MIN COST CLIMBING STAIRS */
int MinCostClimbingStairs(const std::vector<int>& costs)
{
	const int size = costs.size();
	int* dp = new int[size];
	dp[0] = costs[0];
	dp[1] = costs[1];

	for (int i = 2; i < size; i++)
		dp[i] = costs[i] + std::min(dp[i - 1], dp[i - 2]);

	int minCost = std::min(dp[size - 1], dp[size - 2]);
	delete[] dp;
	return minCost;
}

/* UNIQUE PATHS */
int UniquePaths(const int m, const int n)
{
	// Initialize dp array
	int** dp = new int*[m];
	for (int i = 0; i < m; i++)
	{
		dp[i] = new int[n];
		for (int j = 0; j < n; j++)
			dp[i][j] = 1;
	}

	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++)
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

	int paths = dp[m - 1][n - 1];
	for (int i = 0; i < m; i++)
		delete[] dp[i];
	delete[] dp;

	return paths;
}

int main()
{
	std::cout << UniquePaths(5, 8);
}