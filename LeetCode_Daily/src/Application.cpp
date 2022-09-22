#include <iostream>
#include <string>
#include <sstream>

#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <queue>

#include <numeric>
#include <algorithm>

/* Node definition. */
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

/* Singly-linked list node definition. */
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

/* Trie node definition. */
struct TrieNode
{
	TrieNode* next[26];
	int idx = -1;
	std::vector<int> indices;
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

void PreorderStr(TreeNode* root, std::string& str)
{
	if (!root)
		return;
	else
	{
		str += std::to_string(root->val);
		if (root->left)
		{
			str += '(';
			PreorderStr(root->left, str);
			str += ')';
		}
		else if (root->right)	// no left, but right exists
		{
			str += "()";
		}
		if (root->right)
		{
			str += '(';
			PreorderStr(root->right, str);
			str += ')';
		}
	}
}

/* 7 SEPT, 2022: CONSTRUCT STRING FROM BINARY TREE */
std::string TreeToStr(TreeNode* root)
{
	std::string result;
	PreorderStr(root, result);

	return result;
}

void Inorder(TreeNode* root, std::vector<int>& values)
{
	if (!root)
		return;
	else
	{
		Inorder(root->left, values);
		values.push_back(root->val);
		Inorder(root->right, values);
	}
}

/* 8 SEPT, 2022: BINARY TREE INORDER TRAVERSAL */
std::vector<int> InorderTraversal(TreeNode* root)
{
	std::vector<int> result;
	Inorder(root, result);
	return result;
}

/* 9 SEPT, 2022: THE NUMBER OF WEAK CHARACTERS IN THE GAME */
int NumberOfWeakCharacters(std::vector<std::vector<int>>& properties)
{
	const int size = properties.size();
	auto compare = [](const std::vector<int>& lhs, const std::vector<int>& rhs)
	{
		if (lhs[0] == rhs[0])
			return lhs[1] < rhs[1];
		return lhs[0] > rhs[0];
	};
	std::sort(properties.begin(), properties.end(), compare);


	int weaklings = 0;
	int minDef = INT_MIN;
	for (int i = 0; i < size; i++)
	{
		if (properties[i][1] < minDef)
			weaklings++;
		minDef = std::max(minDef, properties[i][1]);
	}

	return weaklings;
}

int MaxProfitUnlim(const std::vector<int>& prices)
{
	const int size = prices.size();
	int maxProfit = 0;
	for (int i = 1; i < size; i++)
		maxProfit += std::max(prices[i] - prices[i - 1], 0);

	return maxProfit;
}

/* 10 SEPT, 2022: BEST TIME TO BUY AND SELL STOCK IV */
int MaxProfit(const int k, const std::vector<int>& prices)
{
	const int size = prices.size();
	if (k >= size / 2)
		return MaxProfitUnlim(prices);

	std::vector<int> buys(k + 1, INT_MIN);
	std::vector<int> sells(k + 1, 0);
	for (int i = 0; i < size; i++)
	{
		int curr = prices[i];
		for (int j = 1; j <= k; j++)
		{
			buys[j] = std::max(buys[j], sells[j - 1] - curr);
			sells[j] = std::max(sells[j], buys[j] + curr);
		}
	}

	return sells[k];
}

/* 11 SEPT, 2022: MAXIMUM PERFORMANCE OF A TEAM */
int MaxPerformance(const int n, const std::vector<int>& speeds, const std::vector<int>& efficiencies, const int k)
{
	std::vector<std::pair<int, int>> engineers(n);
	for (int i = 0; i < n; i++)
		engineers[i] = std::make_pair(efficiencies[i], speeds[i]);
	std::sort(engineers.rbegin(), engineers.rend());

	std::priority_queue<int, std::vector<int>, std::greater<int>> pQueue;
	long sum = 0;
	long result = 0;
	for (const auto& [eff, spd] : engineers)
	{
		sum += spd;
		pQueue.push(spd);
		if (pQueue.size() > k)
		{
			sum -= pQueue.top();
			pQueue.pop();
		}

		result = std::max(result, sum * eff);
	}

	return result % (int)(1e9 + 7);
}

/* 12 SEPT, 2022: BAG OF TOKENS */
int BagOfTokensScore(std::vector<int>& tokens, int power)
{
	const int size = tokens.size();
	std::sort(tokens.begin(), tokens.end());

	int result = 0;
	int score = 0;
	int left = 0;
	int right = size - 1;
	while (left <= right)
	{
		if (power >= tokens[left])
		{
			power -= tokens[left];
			result = std::max(result, ++score);
			left++;
		}
		else if (score > 0)
		{
			power += tokens[right];
			score--;
			right--;
		}
		else
			break;
	}

	return result;
}

/* 13 SEPT, 2022: UTF-8 VALIDATION */
bool ValidUtf8(const std::vector<int>& data)
{
	const int bytes = data.size();

	// Special case, only 1 byte
	if (bytes == 1)
		return ((data[0] & 0b10000000) != 0b10000000);
	else if (bytes > 4)
		return false;

	int remaining = 0;
	for (int i = 0; i < bytes; i++)
	{
		int curr = data[i];
		if (remaining == 0)
		{
			if ((curr >> 3) == 0b11110)
				remaining = 3;
			else if ((curr >> 4) == 0b1110)
				remaining = 2;
			else if ((curr >> 5) == 0b110)
				remaining = 1;
		}
		else
		{
			// Continuation bytes, 2 msb must be 10
			if ((curr >> 6) != 0b10)
				return false;

			remaining--;
		}
	}

	return remaining == 0;
}

void PalindromeSearchDFS(TreeNode* node, int& result, int oddFreq)
{
	if (!node)
		return;

	oddFreq ^= (1 << node->val);
	if (!node->left && !node->right)
		if ((oddFreq & (oddFreq - 1)) == 0)
			result++;

	PalindromeSearchDFS(node->left, result, oddFreq);
	PalindromeSearchDFS(node->right, result, oddFreq);
}

/* 14 SEPT, 2022: PSEUDO-PALINDROMIC PATHS IN A BINARY TREE */
int PseudoPalindromicPaths(TreeNode* root)
{
	int result = 0;
	PalindromeSearchDFS(root, result, 0);
	return result;
}

/* 15 SEPT, 2022: FIND ORIGINAL ARRAY FROM DOUBLED ARRAY */
std::vector<int> FindOriginalArray(std::vector<int>& changed)
{
	const int size = changed.size();
	if (size % 2 != 0)
		return {};

	std::unordered_map<int, int> amountMap;
	for (int i = 0; i < size; i++)
		amountMap[changed[i]]++;

	std::sort(changed.begin(), changed.end());
	std::vector<int> original;
	for (int i = 0; i < size; i++)
	{
		int num = changed[i];
		if (amountMap[num] > 0)
		{
			// Isn't already a double of something else
			int numDouble = 2 * num;
			if (amountMap.find(numDouble) != amountMap.end() && amountMap[numDouble] > 0)
			{
				// Has a double somewhere later in the array
				original.push_back(num);
				amountMap[numDouble]--;
			}
			else
			{
				// Doesn't have a double
				return {};
			}

			amountMap[num]--;
		}
	}

	for (auto it = amountMap.begin(); it != amountMap.end(); it++)
		if (it->second > 0)
			return {};

	return original;
}

int ScoreMemo(std::vector<std::vector<int>>& dp, std::vector<int>& nums, std::vector<int>& multipliers, int mSize,
	int left, int right, int depth)
{
	if (depth == mSize)
		return 0;
	if (dp[depth][left] > INT_MIN)
		return dp[depth][left];

	int leftBranch = nums[left] * multipliers[depth] + ScoreMemo(dp, nums, multipliers, mSize, left + 1, right, depth + 1);
	int rightBranch = nums[right] * multipliers[depth] + ScoreMemo(dp, nums, multipliers, mSize, left, right - 1, depth + 1);
	dp[depth][left] = std::max(leftBranch, rightBranch);

	return dp[depth][left];
}

/* 16 SEPT, 2022: MAXIMUM SCORE FROM PERFORMING MULTIPLICATION OPERATIONS */
int MaximumScore(std::vector<int>& nums, std::vector<int>& multipliers)
{
	const int nSize = nums.size();
	const int mSize = multipliers.size();
	std::vector<std::vector<int>> dp(mSize + 1, std::vector<int>(mSize + 1, INT_MIN));

	return ScoreMemo(dp, nums, multipliers, mSize, 0, nSize - 1, 0);
}

class PaliPairs
{
public:
	/* 17 SEPT, 2022: PALINDROME PAIRS */
	std::vector<std::vector<int>> PalindromePairs(const std::vector<std::string>& words)
	{
		const int numWords = words.size();
		for (int i = 0; i < numWords; i++)
			Add(words[i], i);

		std::vector<std::vector<int>> indices;
		for (int i = 0; i < numWords; i++)
		{
			const std::string str = words[i];
			const int length = str.length();

			TrieNode* node = &m_Root;
			for (int j = 0; j < length; j++)
			{
				if (!node)
					break;
				else
				{
					if (node->idx > -1 && node->idx != i && IsPalindrome(str, j, length - 1))
						indices.push_back({ i, node->idx });

					node = node->next[str[j] - 'a'];
				}
			}
			if (!node)
				continue;

			for (int j = 0; j < node->indices.size(); j++)
				if (i != j)
					indices.push_back({ i, j });
		}

		return indices;
	}

private:
	TrieNode m_Root;

	bool IsPalindrome(const std::string& string, int left, int right)
	{
		while (left < right && string[left] == string[right])
		{
			left++;
			right--;
		}

		return left >= right;;
	}

	void Add(const std::string& str, const int i)
	{
		const int length = str.length();
		TrieNode* node = &m_Root;
		for (int r = length - 1; r >= 0; r--)
		{
			if (IsPalindrome(str, 0, r))
				node->indices.push_back(i);

			int ch = str[r] - 'a';
			if (!node->next[ch])
				node->next[ch] = new TrieNode();

			node = node->next[ch];
		}
		node->idx = i;
		node->indices.push_back(i);
	}
};

/* 18 SEPT, 2022: TRAPPING RAIN WATER */
int Trap(const std::vector<int>& heights)
{
	const int size = heights.size();

	int trapped = 0;
	std::stack<int> indices;	// decreasing monotonic stack
	for (int i = 0; i < size; i++)
	{
		while (!indices.empty() && heights[i] > heights[indices.top()])
		{
			int currTop = indices.top();
			indices.pop();
			if (!indices.empty())
				trapped += (i - indices.top() - 1) * (std::min(heights[indices.top()], heights[i]) - heights[currTop]);

		}

		indices.push(i);
	}

	return trapped;
}

/* 19 SEPT, 2022: FIND DUPLICATE FILE IN SYSTEM */
std::vector<std::vector<std::string>> FindDuplicate(const std::vector<std::string>& paths)
{
	std::unordered_map<std::string, std::vector<std::string>> allFiles;
	std::vector<std::vector<std::string>> duplicates;

	for (const auto& path : paths)
	{
		std::stringstream ss(path);
		std::string str, dir, filename, content;
		ss >> dir;
		while (ss >> str)
		{
			auto it = str.find('(');
			filename = str.substr(0, it);
			content = str.substr(it);
			allFiles[content].push_back(dir + '/' + filename);
		}
	}

	for (const auto& [content, files] : allFiles)
	{
		const int numFiles = files.size();
		if (numFiles > 1)
			duplicates.push_back(files);
	}

	return duplicates;
}

/* 20 SEPT, 2022: MAXIMUM LENGTH OF REPEATED SUBARRAY */
int FindLength(const std::vector<int>& nums1, const std::vector<int>& nums2)
{
	const int size1 = nums1.size();
	const int size2 = nums2.size();
	std::vector<std::vector<int>> dp(size1 + 1, std::vector<int>(size2 + 1, 0));

	int maxLength = 0;
	for (int i = 1; i <= size1; i++)
	{
		for (int j = 1; j <= size2; j++)
		{
			if (nums1[i - 1] == nums2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				maxLength = std::max(maxLength, dp[i][j]);
			}
			else
				dp[i][j] = 0;
		}
	}

	return maxLength;
}

/* 21 SEPT, 2022: SUM OF EVEN NUMBERS AFTER QUERIES */
std::vector<int> SumEvenAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
{
	const int size = nums.size();
	const int numQueries = queries.size();
	std::vector<int> result(numQueries);
	int rIdx = 0;

	// 0th even sum
	int currSum = 0;
	for (const int num : nums)
	{
		if (num % 2 == 0)
			currSum += num;
	}

	// Queries
	for (int i = 0; i < numQueries; ++i)
	{
		int val = queries[i][0];
		int idx = queries[i][1];

		currSum -= (nums[idx] % 2 == 0) ? nums[idx] : 0;
		currSum += ((nums[idx] + val) % 2 == 0) ? (nums[idx] + val) : 0;

		result[rIdx] = currSum;
		rIdx++;

		nums[idx] += val;
	}

	return result;
}

/* 22 SEPT, 2022: REVERSE WORDS IN A STRING III */
std::string ReverseWords(std::string& str)
{
	const int length = str.length();
	for (int i = 0; i < length; i++)
	{
		if (str[i] != ' ')
		{
			int j = i;
			while (j < length && str[j] != ' ')
				j++;

			std::reverse(str.begin() + i, str.begin() + j);
			i = j - 1;
		}
	}

	return str;
}


/* 23 SEPT, 2022:  */

/* 24 SEPT, 2022:  */

/* 25 SEPT, 2022:  */

/* 26 SEPT, 2022:  */

/* 27 SEPT, 2022:  */

int main()
{

}