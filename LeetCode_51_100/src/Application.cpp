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

int main()
{
	
}