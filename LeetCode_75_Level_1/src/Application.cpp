#include <iostream>

#include <vector>
#include <unordered_map>

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

// -------------	DAY 4	------------- //

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

int main()
{
	std::string string = "abccccdd";
	std::cout << LongestPalindrome(string);
}