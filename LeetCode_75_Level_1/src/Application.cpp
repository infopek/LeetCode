#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

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

int main()
{
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(4);
	root->left->left = new TreeNode(6);
	root->left->right = new TreeNode(5);
	root->left->left->left = new TreeNode(12);
	root->left->right->left = new TreeNode(7);
	root->left->right->right = new TreeNode(2);

	root->right = new TreeNode(3);
	root->right->left = new TreeNode(10);
	root->right->right = new TreeNode(11);
	root->right->right->left = new TreeNode(9);

	std::vector<std::vector<int>> levels = LevelOrder(root);
}