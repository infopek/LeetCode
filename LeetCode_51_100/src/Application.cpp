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

/* Node definition. */
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

/* Linked List definition. */
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

/* Determines whether a queen can be placed on the board at a given position. */
bool IsValidQueen(std::vector<std::string>& board, int n, int row, int col)
{
	// Check column
	for (int i = 0; i < row; i++)
	{
		if (board[i][col] == 'Q')
			return false;
	}

	// Check diagonal (/)
	for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
	{
		if (board[i][j] == 'Q')
			return false;
	}

	// Check diagonal (\)
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (board[i][j] == 'Q')
			return false;
	}

	return true;
}

/* Finds solutions to the N-queens problem using backtracking. */
void NQueensBacktrack(std::vector<std::vector<std::string>>& solutions, std::vector<std::string>& board, int n, int row)
{
	if (row == n)
	{
		solutions.push_back(board);
		return;
	}
	else
	{
		for (int j = 0; j < n; j++)
		{
			if (IsValidQueen(board, n, row, j))
			{
				board[row][j] = 'Q';
				NQueensBacktrack(solutions, board, n, row + 1);
				board[row][j] = '.';
			}
		}
	}
}

/* PROBLEM 51: N-QUEENS */
std::vector<std::vector<std::string>> SolveNQueens(int n)
{
	std::vector<std::vector<std::string>> solutions;
	std::vector<std::string> board(n, std::string(n, '.'));
	NQueensBacktrack(solutions, board, n, 0);

	return solutions;
}

/* PROBLEM 52: N-QUEENS II */
int TotalQueens(int n)
{
	std::vector<std::vector<std::string>> solutions;
	std::vector<std::string> board(n, std::string(n, '.'));
	NQueensBacktrack(solutions, board, n, 0);

	return solutions.size();
}

/* PROBLEM 53: MAXIMUM SUBARRAY */
int MaxSubArray(const std::vector<int>& nums)
{
	const int size = nums.size();

	int maxSum = nums[0];
	int sum = nums[0];
	for (int i = 1; i < size; i++)
	{
		sum = std::max(sum + nums[i], nums[i]);
		maxSum = std::max(maxSum, sum);
	}

	return maxSum;
}

/* PROBLEM 54: SPIRAL MATRIX */
std::vector<int> SpiralOrder(const std::vector<std::vector<int>>& matrix)
{
	const int rows = matrix.size();
	const int cols = matrix[0].size();
	std::vector<int> spiral(rows * cols);

	// Four borders
	int leftBorder = 0;
	int rightBorder = cols - 1;
	int bottomBorder = rows - 1;
	int topBorder = 0;

	int spiralIdx = 0;

	// Travel clockwise
	while (leftBorder <= rightBorder && bottomBorder >= topBorder)
	{
		// Travel right
		for (int j = leftBorder; j <= rightBorder; j++)
		{
			spiral[spiralIdx] = matrix[leftBorder][j];
			spiralIdx++;
		}
		topBorder++;

		// Travel down
		for (int i = topBorder; i <= bottomBorder; i++)
		{
			spiral[spiralIdx] = matrix[i][rightBorder];
			spiralIdx++;
		}
		rightBorder--;

		// Travel left
		if (topBorder <= bottomBorder)
		{
			for (int j = rightBorder; j >= leftBorder; j--)
			{
				spiral[spiralIdx] = matrix[bottomBorder][j];
				spiralIdx++;
			}
		}
		bottomBorder--;

		// Travel up
		if (leftBorder <= rightBorder)
		{
			for (int i = bottomBorder; i >= topBorder; i--)
			{
				spiral[spiralIdx] = matrix[i][leftBorder];
				spiralIdx++;
			}
		}
		leftBorder++;
	}

	return spiral;
}

/* PROBLEM 55: JUMP GAME */
bool CanJump(const std::vector<int>& nums)
{
	int size = nums.size();

	int maxReach = nums[0];
	int i = 0;
	while (i <= std::min(maxReach, size - 1))
	{
		maxReach = std::max(maxReach, i + nums[i]);
		if (maxReach >= size - 1)
			return true;
		i++;
	}

	return false;
}

/* PROBLEM 56: MERGE INTERVALS */
std::vector<std::vector<int>> Merge(std::vector<std::vector<int>>& intervals)
{
	const int numIntervals = intervals.size();
	std::sort(intervals.begin(), intervals.end());

	std::vector<std::vector<int>> nonOverlapping;
	for (int i = 0; i < numIntervals; i++)
	{
		int lower = intervals[i][0];
		int upper = intervals[i][1];
		int j = i + 1;
		while (j < numIntervals && upper >= intervals[j][0])
		{
			upper = std::max(upper, intervals[j][1]);
			j++;
		}

		i = j - 1;
		nonOverlapping.push_back({ lower, upper });
	}

	return nonOverlapping;
}

/* Find the index where the interval will be inserted using binary search. */
int FindInsertIndex(const std::vector<std::vector<int>>& intervals, const int numIntervals, const std::vector<int>& interval)
{
	int low = 0;
	int high = numIntervals - 1;
	int target = interval[0];
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (target == intervals[mid][0])
			return (intervals[mid][1] <= interval[1]) ? mid + 1 : mid;
		else if (target < intervals[mid][0])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return low;
}

/* Merges intervals that are already sorted. */
std::vector<std::vector<int>> MergeSortedIntervals(const std::vector<std::vector<int>>& intervals, const int numIntervals)
{
	std::vector<std::vector<int>> nonOverlapping;
	for (int i = 0; i < numIntervals; i++)
	{
		int lower = intervals[i][0];
		int upper = intervals[i][1];
		int j = i + 1;
		while (j < numIntervals && upper >= intervals[j][0])
		{
			upper = std::max(upper, intervals[j][1]);
			j++;
		}

		i = j - 1;
		nonOverlapping.push_back({ lower, upper });
	}

	return nonOverlapping;
}

/* PROBLEM 57: INSERT INTERVAL */
std::vector<std::vector<int>> Insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval)
{
	int numIntervals = intervals.size();

	int idx = FindInsertIndex(intervals, numIntervals, newInterval);
	intervals.insert(intervals.begin() + idx, newInterval);

	MergeSortedIntervals(intervals, numIntervals + 1);

	return intervals;
}

/* PROBLEM 58: LENGTH OF LAST WORD */
int LengthOfLastWord(const std::string& str)
{
	const int length = str.length();

	int i = length - 1;
	while (i >= 0 && str[i] == ' ')
		i--;

	int result = 0;
	while (i >= 0 && str[i] != ' ')
	{
		result++;
		i--;
	}

	return result;
}

/* PROBLEM 59: SPIRAL MATRIX II */
std::vector<std::vector<int>> GenerateMatrix(const int n)
{
	std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

	// Four borders
	int leftBorder = 0;
	int rightBorder = n - 1;
	int bottomBorder = n - 1;
	int topBorder = 0;

	int currNum = 1;

	// Travel clockwise
	while (leftBorder <= rightBorder && bottomBorder >= topBorder)
	{
		// Travel right
		for (int j = leftBorder; j <= rightBorder; j++)
		{
			matrix[leftBorder][j] = currNum;
			currNum++;
		}
		topBorder++;

		// Travel down
		for (int i = topBorder; i <= bottomBorder; i++)
		{
			matrix[i][rightBorder] = currNum;
			currNum++;
		}
		rightBorder--;

		// Travel left
		if (topBorder <= bottomBorder)
		{
			for (int j = rightBorder; j >= leftBorder; j--)
			{
				matrix[bottomBorder][j] = currNum;
				currNum++;
			}
		}
		bottomBorder--;

		// Travel up
		if (leftBorder <= rightBorder)
		{
			for (int i = bottomBorder; i >= topBorder; i--)
			{
				matrix[i][leftBorder] = currNum;
				currNum++;
			}
		}
		leftBorder++;
	}

	return matrix;
}

void NextPermutation(std::string& str)
{
	const int length = str.size();

	// Find pivot
	int pivot = length - 1;
	while (pivot > 0 && str[pivot - 1] >= str[pivot])
		pivot--;

	// Special case: loop back around
	if (pivot == 0)
	{
		std::reverse(str.begin(), str.end());
		return;
	}
	else
		pivot--;

	// Find first successor candidate
	int succ = length - 1;
	while (succ > pivot && str[succ] <= str[pivot])
		succ--;

	// Find closest greater integer to nums[pivot]
	int curr = succ;
	while (curr > pivot)
	{
		if (str[curr] > str[pivot] && str[curr] < str[succ])
			succ = curr;

		curr--;
	}

	// Swap pivot with its successor
	std::swap(str[pivot], str[succ]);

	// Reverse suffix (subarray after pivot)
	std::reverse(str.begin() + (pivot + 1), str.end());
}

/* PROBLEM 60: PERMUTATION SEQUENCE */
std::string GetPermutation(int n, int k)
{
	// Create string 
	std::string result;
	result.resize(n);
	for (int i = 1; i <= n; i++)
		result[i - 1] = i + '0';

	// Get next permutation (k - 1) times
	for (int i = 1; i < k; i++)
		NextPermutation(result);

	return result;
}

/* PROBLEM 61: ROTATE LIST */
ListNode* RotateRight(ListNode* head, int k)
{
	// Special case
	if (!head)
		return nullptr;

	// Calculate length of list
	ListNode* tail = head;
	int length = 1;
	while (tail->next)
	{
		tail = tail->next;
		length++;
	}
	tail->next = head;

	// Rotate the head to new position
	int rotIdx = length - k % length;
	for (int i = 0; i < rotIdx; i++)
		tail = tail->next;

	head = tail->next;
	tail->next = nullptr;

	return head;
}

/* PROBLEM 62: UNIQUE PATHS */
int UniquePaths(int m, int n)
{
	m--;
	n--;

	const int total = m + n;
	const int greater = std::max(m, n);

	long paths = 1;
	int d = 1;
	for (int i = greater + 1; i <= total; i++)
	{
		paths *= i;
		paths /= d;
		d++;
	}

	return (int)paths;
}

/* PROBLEM 63: UNIQUE PATHS II */
int UniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid)
{
	const int rows = obstacleGrid.size();
	const int cols = obstacleGrid[0].size();
	std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));

	// Initialize first row and col
	for (int j = 0; j < cols; j++)
	{
		if (obstacleGrid[0][j] == 1)
			break;
		dp[0][j] = 1;
	}
	for (int i = 0; i < rows; i++)
	{
		if (obstacleGrid[i][0] == 1)
			break;
		dp[i][0] = 1;
	}

	// Fill rest of dp
	for (int i = 1; i < rows; i++)
	{
		for (int j = 1; j < cols; j++)
		{
			if (obstacleGrid[i][j] == 1)
				dp[i][j] = 0;
			else
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}

	return dp[rows - 1][cols - 1];
}

/* PROBLEM 64: MINIMUM PATH SUM */
int MinPathSum(std::vector<std::vector<int>>& grid)
{
	const int rows = grid.size();
	const int cols = grid[0].size();

	// First row and col
	for (int i = 1; i < rows; i++)
		grid[i][0] += grid[i - 1][0];
	for (int j = 1; j < cols; j++)
		grid[0][j] += grid[0][j - 1];

	// Rest of grid
	for (int i = 1; i < rows; i++)
		for (int j = 1; j < cols; j++)
			grid[i][j] += std::min(grid[i - 1][j], grid[i][j - 1]);

	return grid[rows - 1][cols - 1];
}

/* PROBLEM 65: VALID NUMBER */
bool IsNumber(const std::string& str)
{
	const int length = str.length();
	int idx = 0;

	// Skip sign
	if (str[0] == '+' || str[0] == '-')
		idx++;

	// Skip digits before decimal
	int aroundDecimal = 0;
	while (idx < length && '0' <= str[idx] && str[idx] <= '9')
	{
		idx++;
		aroundDecimal++;
	}

	// Skip decimal point
	if (idx < length && str[idx] == '.')
		idx++;

	// Skip digits after decimal
	while (idx < length && '0' <= str[idx] && str[idx] <= '9')
	{
		idx++;
		aroundDecimal++;
	}

	if (idx == 0 || aroundDecimal == 0)
		return false;

	// Skip exponent
	if (idx < length && (str[idx] == 'E' || str[idx] == 'e'))
	{
		idx++;

		// Skip sign after exponent
		if (idx < length && (str[idx] == '+' || str[idx] == '-'))
			idx++;

		// Skip at least one integer
		int count = 0;
		while (idx < length && '0' <= str[idx] && str[idx] <= '9')
		{
			idx++;
			count++;
		}
		if (count == 0)
			return false;
	}

	// Valid if we are at the end of the string
	return idx == length;
}

/* PROBLEM 66: PLUS ONE */
std::vector<int> PlusOne(std::vector<int>& digits)
{
	const int numDigits = digits.size();
	int carry = 1;
	int i = numDigits - 1;
	while (i >= 0 && carry != 0)
	{
		if (digits[i] < 9)
		{
			digits[i]++;
			carry = 0;
		}
		else
		{
			digits[i] = 0;
			carry = 1;
		}
		i--;
	}
	if (carry == 1)
		digits.insert(digits.begin(), 1);

	return digits;
}

/* PROBLEM 67: ADD BINARY */
std::string AddBinary(const std::string& str1, const std::string& str2)
{
	const int length1 = str1.length();
	const int length2 = str2.length();

	int idx1 = length1 - 1;
	int idx2 = length2 - 1;

	std::string sum;
	const int sumLength = std::max(length1, length2) + 1;
	sum.resize(sumLength);
	int sumIdx = sumLength - 1;

	char carry = '0';
	while (idx1 >= 0 && idx2 >= 0)
	{
		if (str1[idx1] == '1' && str2[idx2] == '1')
		{
			sum[sumIdx] = carry;
			carry = '1';
		}
		else if (str1[idx1] == '1' || str2[idx2] == '1')
			sum[sumIdx] = (carry == '0') ? '1' : '0';
		else
		{
			sum[sumIdx] = carry;
			carry = '0';
		}

		idx1--;
		idx2--;
		sumIdx--;
	}

	while (idx1 >= 0)
	{
		if (str1[idx1] == '1' && carry == '1')
			sum[sumIdx] = '0';
		else if (str1[idx1] == '1' || carry == '1')
		{
			sum[sumIdx] = '1';
			carry = '0';
		}
		else
			sum[sumIdx] = '0';

		idx1--;
		sumIdx--;
	}

	while (idx2 >= 0)
	{
		if (str2[idx2] == '1' && carry == '1')
			sum[sumIdx] = '0';
		else if (str2[idx2] == '1' || carry == '1')
		{
			sum[sumIdx] = '1';
			carry = '0';
		}
		else
			sum[sumIdx] = '0';

		idx2--;
		sumIdx--;
	}

	if (carry == '1')
		sum[0] = '1';
	else
		sum = sum.substr(1, sumLength - 1);

	return sum;
}

/* PROBLEM 68: TEXT JUSTIFICATION */
std::vector<std::string> FullJustify(const std::vector<std::string>& words, const int maxWidth)
{
	const int numWords = words.size();
	int wordIdx = 0;

	std::vector<std::string> justified;
	while (wordIdx < numWords)
	{
		// Line
		std::string currLine;
		currLine.resize(maxWidth);
		int lineIdx = 0;

		// Count # of words that fit on current line with 1 space between them
		int wordsPerLine = 0;
		int baseLength = 0;
		while (wordIdx < numWords && (baseLength + words[wordIdx].length()) <= maxWidth)
		{
			baseLength += words[wordIdx].length() + 1;
			wordsPerLine++;
			wordIdx++;
		}
		baseLength--;

		int allSpaces = maxWidth - (baseLength - (wordsPerLine - 1));
		if (wordIdx == numWords || wordsPerLine == 1)
		{
			// Last line or one word fits -> left-justify
			int i = 0;
			while (i < wordsPerLine)
			{
				// Add word
				for (const auto c : words[wordIdx - wordsPerLine + i])
				{
					currLine[lineIdx] = c;
					lineIdx++;
				}
				i++;

				if (i < wordsPerLine)
				{
					// Add only one space
					currLine[lineIdx] = ' ';
					lineIdx++;
					allSpaces--;
				}
				else
				{
					// Fill rest of line with spaces
					for (int s = 0; s < allSpaces; s++)
					{
						currLine[lineIdx] = ' ';
						lineIdx++;
					}
				}
			}
		}
		else
		{
			// Count # of spaces after words, # of extra spaces to be distributed starting from the left
			int spacesAfterWord = allSpaces / (wordsPerLine - 1);
			int extraSpaces = allSpaces % (wordsPerLine - 1);

			int i = 0;
			while (i < wordsPerLine)
			{
				// Add word
				for (const auto c : words[wordIdx - wordsPerLine + i])
				{
					currLine[lineIdx] = c;
					lineIdx++;
				}
				i++;

				if (i < wordsPerLine)
				{
					// Add spaces
					for (int s = 0; s < spacesAfterWord; s++)
					{
						currLine[lineIdx] = ' ';
						lineIdx++;
					}
					if (extraSpaces > 0)
					{
						currLine[lineIdx] = ' ';
						lineIdx++;
						extraSpaces--;
					}
				}
			}
		}

		justified.push_back(currLine);
	}

	return justified;
}

/* PROBLEM 69: SQRT(X) */
int MySqrt(const int x)
{
	int left = 1;
	int right = x;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (mid == x / mid)
			return mid;
		else if (mid < x / mid)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return std::min(left, right);
}

/* PROBLEM 70: CLIMBING STAIRS */
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

/* PROBLEM 71: SIMPLIFY PATH */
std::string SimplifyPath(std::string& path)
{
	int length = path.length();
	std::stack<std::string> stack;

	if (path[length - 1] != '/')
	{
		path += "/";
		length++;
	}

	int i = 1;	// skip the first '/'
	std::string dir = "";
	while (i < length)
	{
		if (path[i] == '/')
		{
			if (dir == "" || dir == ".")
			{
				// Skip   
			}
			else if (dir == "..")
			{
				if (!stack.empty())
					stack.pop();
			}
			else
				stack.push(dir);

			dir = "";
		}
		else
			dir.push_back(path[i]);

		i++;
	}

	// Fill resulting path from stack
	std::string canonical = "";
	while (!stack.empty())
	{
		canonical = '/' + stack.top() + canonical;
		stack.pop();
	}
	if (canonical.length() == 0)
		canonical = "/";

	return canonical;
}

/* PROBLEM 72: EDIT DISTANCE */
int MinDistance(std::string& orig, const std::string& target)
{

}

int main()
{
	
}