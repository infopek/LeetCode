#include <iostream>
#include <string>

#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

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

int main()
{
	std::vector<std::vector<int>> matrix = GenerateMatrix(3);
}