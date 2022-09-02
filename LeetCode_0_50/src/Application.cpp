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

/* PROBLEM 1: TWO SUM
* Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
* You may assume that each input would have exactly one solution, and you may not use the same element twice.
* You can return the answer in any order. */
std::vector<int> TwoSum(const std::vector<int>& nums, const int target)
{
	std::unordered_map<int, int> map;
	std::vector<int> indices;
	indices.resize(2);
	size_t size = nums.size();

	// O(n^2) time complexity
	/*for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			int sum = nums[i] + nums[j];
			if (sum == target)
			{
				indices[0] = i;
				indices[1] = j;
				return indices;
			}
		}
	}*/

	// O(n) time complexity
	for (int i = 0; i < size; i++)
	{
		int searchedNum = target - nums[i];
		if (map.find(searchedNum) != map.end())
		{
			// Found the solution
			indices[0] = i;
			indices[1] = map[searchedNum];
			return indices;
		}
		else
		{
			map[nums[i]] = i;
		}
	}

	return indices;
}

/* PROBLEM 2: ADD TWO NUMBERS
* You are given two non-empty linked lists representing two non-negative integers.
* The digits are stored in reverse order, and each of their nodes contains a single digit.
* Add the two numbers and return the sum as a linked list.
* You may assume the two numbers do not contain any leading zero, except the number 0 itself. */
ListNode* AddTwoNumbers(ListNode* head1, ListNode* head2)
{
	ListNode* res = new ListNode();
	ListNode* curr = res;
	int carry = 0;
	while (head1 || head2 || carry)
	{
		int lhs = head1 ? head1->val : 0;
		int rhs = head2 ? head2->val : 0;

		int sum = lhs + rhs + carry;
		carry = (sum >= 10) ? 1 : 0;
		if (carry)
			sum -= 10;

		curr->next = new ListNode(sum);
		curr = curr->next;

		head1 = head1 ? head1->next : nullptr;
		head2 = head2 ? head2->next : nullptr;
	}

	return res->next;
}

/* PROBLEM 3: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS
* Given a string s, find the length of the longest substring without repeating characters. */
int LengthOfLongestSubstring(const std::string& s)
{
	std::unordered_map<char, int> letters;
	size_t size = s.size();
	int maxLength = 0;

	int left = 0;
	int right = 0;
	while (right < size)
	{
		letters[s[right]]++;
		while (letters[s[right]] > 1)
		{
			letters[s[left]]--;
			left++;
		}

		int length = right - left + 1;
		maxLength = std::max(maxLength, length);
		right++;
	}

	return maxLength;
}

/* PROBLEM 4: MEDIAN OF TWO SORTED ARRAYS
* Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
* The overall run time complexity should be O(log (m+n)). */
double FindMedianSortedArrays(const std::vector<int>& numbers, const std::vector<int>& other)
{
	size_t numbersSize = numbers.size();
	size_t otherSize = other.size();
	size_t mergedSize = numbersSize + otherSize;
	size_t halfSize = mergedSize / 2;

	bool isEvenSize = mergedSize % 2 == 0;	// determines how the median is calculated

	std::vector<int> merged;
	merged.reserve(halfSize + 1);

	int nIndex = 0;
	int oIndex = 0;
	int mIndex = 0;
	// Union of two sorted arrays (merge algorithm)
	while (mIndex <= halfSize && nIndex < numbersSize && oIndex < otherSize)
	{
		if (numbers[nIndex] < other[oIndex])
		{
			merged.push_back(numbers[nIndex]);
			mIndex++;

			nIndex++;
		}
		else if (other[oIndex] < numbers[nIndex])
		{
			merged.push_back(other[oIndex]);
			mIndex++;

			oIndex++;
		}
		else
		{
			merged.push_back(numbers[nIndex]);
			mIndex++;
			if (mIndex <= halfSize)
			{
				merged.push_back(other[oIndex]);
				mIndex++;
			}

			nIndex++;
			oIndex++;
		}
	}
	while (mIndex <= halfSize && nIndex < numbersSize)
	{
		merged.push_back(numbers[nIndex]);
		mIndex++;

		nIndex++;
	}
	while (mIndex <= halfSize && oIndex < otherSize)
	{
		merged.push_back(other[oIndex]);
		mIndex++;

		oIndex++;
	}

	double median = 0;
	if (isEvenSize)
		median = (merged[halfSize - 1] + merged[halfSize]) / 2.0;
	else
		median = merged[halfSize];

	return median;
}

/* HELPER METHOD */
bool IsPalindrome(const std::string& string)
{
	size_t left = 0;
	size_t right = string.length() - 1;
	while (left < right)
	{
		if (string[left] != string[right])
			return false;

		left++;
		right--;
	}

	return true;
}

/* PROBLEM 5: LONGEST PALINDROMIC SUBSTRING
* Given a string s, return the longest palindromic substring in s. */
std::string LongestPalindrome(const std::string& string)
{
	// Bruteforce: O(n^3) time complexity -> time limit exceeded :(
	/*size_t size = string.length();
	std::string result = "";
	size_t maxLength = 0;

	size_t length = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			std::string sub = string.substr(i, j - i + 1);
			if (IsPalindrome(sub))
			{
				length = j - i + 1;
				if (length > maxLength)
				{
					result = sub;
					maxLength = length;
				}
			}
		}
	}*/

	// Expand from center

	// Dynamic programming: O(n^2) time and space complexity
	/*std::string result = "";
	int size = string.size();

	int maxLength = 0;
	std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));

	for (int diff = 0; diff < size; diff++)
	{
		for (int i = 0, j = i + diff; j < size; i++, j++)
		{
			if (i == j)
				dp[i][j] = 1;
			else if (diff == 1)
				dp[i][j] = (string[i] == string[j]) ? 2 : 0;
			else if (string[i] == string[j] && dp[i + 1][j - 1])
				dp[i][j] = dp[i + 1][j - 1] + 2;

			int length = j - i + 1;
			if (dp[i][j] && length > maxLength)
			{
				maxLength = length;
				result = string.substr(i, maxLength);
			}
		}
	}

	return result;*/

	// Manacher's algorithm: O(n) time
	size_t size = string.size();
	size_t modifiedSize = 2 * size + 1;

	std::string modified = "";
	modified.resize(modifiedSize);
	for (int i = 0; i < modifiedSize; i += 2)
	{
		modified[i] = '*';
	}
	for (int i = 1; i < modifiedSize; i += 2)
	{
		modified[i] = string[(i - 1) / 2];
	}

	std::vector<int> radii(modifiedSize, 0);
	int center = 0, radius = 0;
	while (center < modifiedSize)
	{
		// Expand radius until not palindrome
		while ((center - (radius + 1)) >= 0 && (center + (radius + 1)) < modifiedSize &&
			modified[center - (radius + 1)] == modified[center + (radius + 1)])
		{
			radius++;
		}
		radii[center] = radius;

		int oldCenter = center;
		int oldRadius = radius;

		center++;
		radius = 0;
		while (center <= oldCenter + oldRadius)
		{
			int mirrorCenter = oldCenter - (center - oldCenter);
			int maxMirrorRadius = oldCenter + oldRadius - center;

			if (radii[mirrorCenter] < maxMirrorRadius)
			{
				radii[center] = radii[mirrorCenter];
				center++;
			}
			else if (radii[mirrorCenter] > maxMirrorRadius)
			{
				radii[center] = maxMirrorRadius;
				center++;
			}
			else
			{
				radius = maxMirrorRadius;
				break;
			}
		}
	}

	int maxLength = radii[0];
	int modCenter = 0;
	for (int i = 0; i < modifiedSize; i++)
	{
		if (radii[i] > maxLength)
		{
			maxLength = radii[i];
			modCenter = i;
		}
	}

	// Convert back to unmodified string indices
	int unmCenter = (modCenter - 1) / 2;
	int unmRadius = (maxLength - 1) / 2;
	int start = unmCenter - unmRadius;

	std::string result = string.substr(start, maxLength);
	return result;
}

/* PROBLEM 6: ZIGZAG CONVERSION
* The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
* P   A   H   N
* A P L S I I G
* Y   I   R
* And then read line by line: "PAHNAPLSIIGYIR"
* Write the code that will take a string and make this conversion given a number of rows */
std::string Convert(const std::string& string, const int numRows)
{
	// First approach -> slow, allocates a lot of extra space
	//if (numRows == 1)
	//	return string;

	//// Initialize things
	//size_t size = string.size();
	//char** pattern = new char*[numRows];
	//for (int i = 0; i < numRows; i++)
	//{
	//	pattern[i] = new char[size];
	//	for (int j = 0; j < size; j++)
	//	{
	//		pattern[i][j] = '*';	// filler symbol
	//	}
	//}

	//// 'Draw' the zigzag pattern
	//int counter = 0;
	//int offset = 0;
	//while (counter < size)
	//{
	//	// Go down
	//	int rowIndex = 0;
	//	int colIndex = offset;
	//	while (counter < size && rowIndex < numRows)
	//	{
	//		pattern[rowIndex++][colIndex] = string[counter++];
	//	}
	//	rowIndex--;

	//	// Go diagonally up
	//	while (counter < size && rowIndex > 1)
	//	{
	//		pattern[--rowIndex][++colIndex] = string[counter++];
	//	}

	//	offset += numRows - 1;
	//}

	//// Traverse the pattern line by line
	//std::string result;
	//result.resize(size);
	//int index = 0;
	//for (int i = 0; i < numRows; i++)
	//{
	//	for (int j = 0; j < size; j++)
	//	{
	//		if (pattern[i][j] != '*')
	//			result[index++] = pattern[i][j];
	//	}
	//}

	//delete[] pattern;
	//return result;

	// Second approach
	if (numRows == 1)
		return string;

	size_t size = string.size();

	std::vector<std::string> rows(numRows, "");
	int currRow = 0;
	int step = -1;

	for (const auto& ch : string)
	{
		rows[currRow] += ch;

		if (currRow == 0 || currRow == numRows - 1)
			step = -step;
		currRow += step;
	}

	std::string result = "";
	for (const auto& str : rows)
	{
		result += str;
	}

	return result;
}

/* HELPER METHOD */
int Magnitude(const int num)
{
	int tmp = num;
	int magnitude = -1;

	while (tmp != 0)
	{
		magnitude++;
		tmp /= 10;
	}

	return magnitude;
}

/* PROBLEM 7: REVERSE INTEGER
* Given a signed 32-bit integer x, return x with its digits reversed.
* If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.
* Assume the environment does not allow you to store 64-bit integers (signed or unsigned). */
int Reverse(int integer)
{
	// Convert to int and reverse -> not too fast, O(n) space
	/*bool isNegative = integer < 0;

	std::string strInt = std::to_string(integer);
	if (isNegative)
		strInt = strInt.substr(1, strInt.length() - 1);
	std::reverse(strInt.begin(), strInt.end());

	try
	{
		int reverse = std::stoi(strInt);
		if (isNegative)
			return -reverse;
		else
			return reverse;
	}
	catch (std::exception)
	{
		return 0;
	}*/

	// Digit by digit
	int reverse = 0;
	while (integer != 0)
	{
		int digit = integer % 10;
		integer /= 10;
		if ((reverse > INT_MAX / 10) || (reverse == INT_MAX / 10 && digit > 7))
			return 0;
		if ((reverse < INT_MIN / 10) || (reverse == INT_MIN / 10 && digit < -8))
			return 0;

		reverse = reverse * 10 + digit;
	}

	return reverse;
}

/* PROBLEM 8: STRING TO INTEGER (ATOI)
* Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function). */
int Atoi(const std::string& string)
{
	size_t size = string.size();
	int index = 0;

	// Ignore leading whitespaces
	while (index < size && string[index] == ' ')
	{
		index++;
	}

	// Check sign
	bool negative = false;
	if (index < size)
	{
		if (string[index] == '-')
		{
			negative = true;
			index++;
		}
		else if (string[index] == '+')
		{
			index++;
		}
	}

	// Read the digits
	int result = 0;
	if (negative)
	{
		while (index < size && std::isdigit(string[index]))
		{
			int digit = string[index] - '0';
			if ((result < INT_MIN / 10) || (result == INT_MIN / 10 && digit > 8))
				return INT_MIN;

			result = result * 10 - digit;
			index++;
		}
	}
	else
	{
		while (index < size && std::isdigit(string[index]))
		{
			int digit = string[index] - '0';
			if ((result > INT_MAX / 10) || (result == INT_MAX / 10 && digit > 7))
				return INT_MAX;

			result = result * 10 + digit;
			index++;
		}
	}

	return result;
}

/* PROBLEM 9: PALINDROME NUMBER
* Given an integer x, return true if x is palindrome integer.
* An integer is a palindrome when it reads the same backward as forward. */
bool IsPalindrome(int num)
{
	// Special cases
	if (num < 0)
		return false;
	else if (num == 0)
		return true;

	int magnitude = Magnitude(num);
	int left = std::pow(10, magnitude);

	int lDigit = num / left;
	int rDigit = num % 10;
	while (left > 10 && lDigit == rDigit)
	{
		num -= left * lDigit;
		num /= 10;
		left /= 100;

		lDigit = num / left;
		rDigit = num % 10;
	}

	return lDigit == rDigit;
}

/* PROBLEM 10: REGULAR EXPRESSION MATCHING
* Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
* '.' Matches any single character.​​​​
* '*' Matches zero or more of the preceding element.
* The matching should cover the entire input string (not partial). */
bool IsMatch(const std::string& string, const std::string& pattern)
{
	const size_t sSize = string.size();
	const size_t pSize = pattern.size();

	std::vector<std::vector<bool>> dp(sSize + 1, std::vector<bool>(pSize + 1, false));
	dp[0][0] = true;
	for (int i = 1; i <= pSize; i++)
	{
		if (pattern[i - 1] == '*')
			dp[0][i] = dp[0][i - 2];
	}

	for (int i = 1; i <= sSize; i++)
	{
		for (int j = 1; j <= pSize; j++)
		{
			if (pattern[j - 1] == '.' || pattern[j - 1] == string[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else if (pattern[j - 1] == '*')
			{
				dp[i][j] = dp[i][j - 2];
				if (!dp[i][j] && (pattern[j - 2] == '.' || pattern[j - 2] == string[i - 1]))
					dp[i][j] = dp[i - 1][j];
			}
			else
				dp[i][j] = false;
		}
	}

	return dp[sSize][pSize];
}

/* PROBLEM 11: CONTAINER WITH MOST WATER
* You are given an integer array heights of length n.
* There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, heights[i]).
* Find two lines that together with the x-axis form a container, such that the container contains the most water.
* Return the maximum amount of water a container can store.
* Notice that you may not slant the container */
int MaxArea(const std::vector<int>& heights)
{
	// Brute force: O(n^2) time, O(1) space -> time limit exceeded
	//const size_t size = heights.size();

	//int maxArea = 0;
	//for (int i = 0; i < size; i++)
	//{
	//	for (int j = i + 1; j < size; j++)
	//	{
	//		int area = (j - i) * std::min(heights[i], heights[j]);	// width * height
	//		maxArea = std::max(maxArea, area);
	//	}
	//}

	//return maxArea;

	// Left and right pointers: O(n) time, O(1) space
	const size_t size = heights.size();

	size_t left = 0;
	size_t right = size - 1;
	size_t maxArea = 0;
	while (left < right)
	{
		int height = std::min(heights[left], heights[right]);
		maxArea = std::max(maxArea, (right - left) * height);
		while (left < right && heights[left] <= height)
			left++;
		while (left < right && heights[right] <= height)
			right--;
	}

	return maxArea;
}

/* PROBLEM 12: INTEGER TO ROMAN
* Given an integer, convert it to a roman numeral. */
std::string IntToRoman(int num)
{
	// Greedy algorithm
	std::string symbols[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	int values[] = { 1000, 900, 500, 400,  100,  90,   50,  40,   10,  9,    5,   4,    1 };

	std::string result;
	int index = 0;
	while (num != 0)
	{
		while (values[index] <= num)
		{
			num -= values[index];
			result += symbols[index];
		}
		index++;
	}

	return result;
}

/* PROBLEM 14: LONGEST COMMON PREFIX
* Write a function to find the longest common prefix string amongst an array of strings.
* If there is no common prefix, return an empty string "". */
std::string LongestCommonPrefix(const std::vector<std::string>& strings)
{
	const size_t size = strings.size();

	std::string prefix = strings[0];
	size_t pfLength = prefix.length();

	int i = 1;
	while (i < size && prefix != "")
	{
		// Iterate until the characters do not match
		std::string curr = strings[i];
		int j = 0;
		while (j < pfLength && j < curr.length() && prefix[j] == curr[j])
		{
			j++;
		}

		prefix = prefix.substr(0, j);
		pfLength = j;

		i++;
	}

	return prefix;
}

/* PROBLEM 15: 3SUM
* Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
* such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
* Notice that the solution set must not contain duplicate triplets. */
std::vector<std::vector<int>> ThreeSum(std::vector<int>& nums)
{
	const size_t size = nums.size();
	std::unordered_map<int, int> indices;
	std::vector<std::vector<int>> triplets;

	for (int i = 0; i < size; i++)
	{
		indices[nums[i]] = i;
	}
	for (int i = 0; i < size - 2; i++)
	{
		int num1 = nums[i];
		for (int j = i + 1; j < size - 1; j++)
		{
			int num2 = nums[j];
			int num3 = 0 - num1 - num2;
			if (indices.find(num3) != indices.end() && indices[num3] > j)
			{
				triplets.push_back({ num1, num2, num3 });
				j = indices[nums[j]];
			}
			i = indices[nums[i]];
		}
	}

	return triplets;
}

/* PROBLEM 16: 3SUM CLOSEST
* Given an integer array nums of length n and an integer target, find three integers in nums such that the sum is closest to target.
* Return the sum of the three integers.
* You may assume that each input would have exactly one solution. */
int ThreeSumClosest(std::vector<int>& nums, const int target)
{
	const int size = nums.size();
	int best = nums[0] + nums[1] + nums[2];
	if (size == 3)
		return best;

	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < size - 2; i++)
	{
		int left = i + 1;
		int right = size - 1;
		while (left < right)
		{
			int sum = nums[i] + nums[left] + nums[right];
			if (abs(target - sum) < abs(target - best))
				best = sum;

			if (sum == target)
				return sum;
			else if (sum < target)
				left++;
			else
				right--;
		}
	}

	return best;
}

/* PROBLEM 17: LETTER COMBINATION OF A PHONE NUMBER
* Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
* Return the answer in any order. */
std::vector<std::string> LetterCombinations(const std::string& digits)
{
	std::unordered_map<int, std::string> phoneButtons =
	{
		{2, "abc"}, {3, "def"}, {4, "ghi"}, {5, "jkl"},
		{6, "mno"}, {7, "pqrs"}, {8, "tuv"}, {9, "wxyz"}
	};

	const size_t numSubsets = digits.size();
	if (numSubsets == 0)
		return {};

	std::vector<std::string> subsets(numSubsets);
	int productSize = 1;
	// Collect the letters in a vector to combine later
	for (int i = 0; i < numSubsets; i++)
	{
		std::string subset = phoneButtons[digits[i] - '0'];
		subsets[i] = subset;
		productSize *= subset.size();
	}

	// Softcode
	std::vector<std::string> desProduct(productSize);
	int index = 0;
	if (numSubsets == 1)
	{
		for (int i = 0; i < subsets[0].size(); i++)
		{
			desProduct[index++] = subsets[0][i];
		}
	}
	else if (numSubsets == 2)
	{
		for (int i = 0; i < subsets[0].size(); i++)
		{
			for (int j = 0; j < subsets[1].size(); j++)
			{
				std::string string = "";
				string += subsets[0][i];
				string += subsets[1][j];
				desProduct[index++] = string;
			}
		}
	}
	else if (numSubsets == 3)
	{
		for (int i = 0; i < subsets[0].size(); i++)
		{
			for (int j = 0; j < subsets[1].size(); j++)
			{
				for (int k = 0; k < subsets[2].size(); k++)
				{
					std::string string = "";
					string += subsets[0][i];
					string += subsets[1][j];
					string += subsets[2][k];
					desProduct[index++] = string;
				}
			}
		}
	}
	else if (numSubsets == 4)
	{
		for (int i = 0; i < subsets[0].size(); i++)
		{
			for (int j = 0; j < subsets[1].size(); j++)
			{
				for (int k = 0; k < subsets[2].size(); k++)
				{
					for (int l = 0; l < subsets[3].size(); l++)
					{
						std::string string = "";
						string += subsets[0][i];
						string += subsets[1][j];
						string += subsets[2][k];
						string += subsets[3][l];
						desProduct[index++] = string;
					}
				}
			}
		}
	}

	return desProduct;
}

/* PROBLEM 18: 4SUM
* Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
* 0 <= a, b, c, d < n
* a, b, c, and d are distinct.
* nums[a] + nums[b] + nums[c] + nums[d] == target
* You may return the answer in any order. */
std::vector<std::vector<int>> FourSum(std::vector<int>& nums, const int target)
{
	std::sort(nums.begin(), nums.end());
	const int size = nums.size();

	std::set<std::vector<int>> set;
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			int targetSum = target - nums[i] - nums[j];
			int left = j + 1;
			int right = size - 1;

			while (left < right)
			{
				long sum = nums[left] + nums[right];
				if (sum < targetSum)
					left++;
				else if (sum > targetSum)
					right--;
				else
				{
					set.insert({ nums[i], nums[j], nums[left], nums[right] });
					left++;
				}
			}
		}
	}

	std::vector<std::vector<int>> quadruplets(set.begin(), set.end());
	return quadruplets;
}

/* PROBLEM 19: REMOVE NTH NODE FROM END OF LIST
* Given the head of a linked list, remove the nth node from the end of the list and return its head. */
ListNode* RemoveNthFromEnd(ListNode* head, const int n)
{
	ListNode* slow = head;
	ListNode* fast = head;

	int center = 1;
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;

		center++;
	}

	// Handle special cases
	int size;
	if (head && !head->next)				// one node in list				
		return nullptr;
	else if (slow && !slow->next)	// two nodes in list
	{
		if (n == 1)	// remove last nodes
		{
			head->next = nullptr;
		}
		else if (n == 2)	// remove head
		{
			ListNode* temp = head;
			head = head->next;
			delete temp;
		}
		return head;
	}
	else
		size = fast ? (2 * center - 1) : (2 * center - 2);

	ListNode* prev = nullptr;
	ListNode* curr = head;
	int index = 1;
	int target = size - n + 1;
	while (curr && index < target)
	{
		prev = curr;
		curr = curr->next;
		index++;
	}

	if (head && n == size)		// remove head
		head = head->next;
	else if (prev && n == 1)	// remove last node
		prev->next = nullptr;
	else if (prev && curr)		// remove from somewhere in the middle
	{
		prev->next = curr->next;
		curr = nullptr;
	}

	return head;
}

/* If br1 is an open bracket, checks if br2 is a close bracket of the same type. */
bool IsMatchingBracket(const char br1, const char br2)
{
	if (br1 == '(')	return br2 == ')';
	else if (br1 == '[')	return br2 == ']';
	else if (br1 == '{')	return br2 == '}';
	return false;
}

/* PROBLEM 20: VALID PARENTHESES
* Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
* An input string is valid if:
*	Open brackets must be closed by the same type of brackets.
*   Open brackets must be closed in the correct order. */
bool IsValid(const std::string& string)
{
	const size_t size = string.size();
	std::stack<char> stack;

	for (int i = 0; i < size; i++)
	{
		char curr = string[i];
		if (curr == '(' || curr == '[' || curr == '{')
		{
			// Current character is an open bracket -> push
			stack.push(curr);
		}
		else if (!stack.empty() && IsMatchingBracket(stack.top(), curr))
		{
			// Current character is a close bracket and matches stack top -> pop
			stack.pop();
		}
		else
		{
			// Current character is a close bracket but does not match stack top -> string is not valid
			return false;
		}
	}

	// All parentheses have been 'cancelled' or not
	return stack.empty() ? true : false;
}

/* PROBLEM 21: MERGED TWO SORTED LISTS
* You are given the heads of two sorted linked lists list1 and list2.
* Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.
* Return the head of the merged linked list. */
ListNode* MergeTwoLists(ListNode* list1, ListNode* list2)
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

/* Recursively generates valid brackets. */
void Parenthesize(std::vector<std::string>& combinations, const std::string& expr, const int max, const int count)
{
	if (max == 0 && count == 0)
	{
		combinations.push_back(expr);
		return;
	}

	if (max > 0)
		Parenthesize(combinations, expr + '(', max - 1, count + 1);
	if (count > 0)
		Parenthesize(combinations, expr + ')', max, count - 1);
}

/* PROBLEM 22: GENERATE PARENTHESES
* Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses. */
std::vector<std::string> GenerateParenthesis(const int n)
{
	std::vector<std::string> combinations;
	Parenthesize(combinations, "", n, 0);
	return combinations;
}

/* Merge two sorted linked lists into merged */
ListNode* MergeTwoLists2(ListNode*& list1, ListNode*& list2)
{
	if (list1 == list2)	return list1;
	if (!list1)	return list2;
	if (!list2)	return list1;

	if (list2->val < list1->val)
		return MergeTwoLists2(list2, list1);

	ListNode* newNode = new ListNode(0);
	newNode->next = list2;
	ListNode* curr = list1;
	while (curr->next && newNode->next)
	{
		if (curr->next->val < newNode->next->val)
			curr = curr->next;
		else
		{
			ListNode* temp = curr->next;
			curr->next = newNode->next;
			newNode->next = newNode->next->next;
			curr->next->next = temp;
			curr = curr->next;
		}
	}
	if (!curr->next)
		curr->next = newNode->next;
	delete newNode;
	return list1;
}

ListNode* MergeKListsRec(std::vector<ListNode*>& lists, int left, int right)
{
	if (left == right)
		return lists[left];
	else if (left + 1 == right)
		return MergeTwoLists2(lists[left], lists[right]);

	int center = (left + right) / 2;
	ListNode* list1 = MergeKListsRec(lists, left, center);
	ListNode* list2 = MergeKListsRec(lists, center + 1, right);
	return MergeTwoLists2(list1, list2);
}

/* PROBLEM 23: MERGE K SORTED LISTS
* You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
* Merge all the linked-lists into one sorted linked-list and return it. */
ListNode* MergeKLists(std::vector<ListNode*>& lists)
{
	// Merge sort
	const size_t size = lists.size();
	if (size == 0)	return nullptr;
	if (size == 1)  return lists[0];
	return MergeKListsRec(lists, 0, size - 1);
}

/* PROBLEM 24: SWAP NODES IN PAIRS
* Given a linked list, swap every two adjacent nodes and return its head.
* You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.) */
ListNode* SwapPairs(ListNode* head)
{
	// Edge cases
	if (!head)			return nullptr;
	if (!head->next)	return head;
	ListNode* newHead = head->next;

	ListNode* prev = nullptr;
	ListNode* left = head;
	ListNode* right = head->next;

	while (right)
	{
		ListNode* temp = right->next;
		if (prev)
			prev->next = right;
		right->next = left;
		left->next = temp;

		prev = left;
		left = left ? left->next : nullptr;
		right = left ? left->next : nullptr;
	}

	return newHead;
}

int GetListLength(ListNode* head)
{
	int length = 0;
	while (head)
	{
		length++;
		head = head->next;
	}

	return length;
}

/* PROBLEM 25: REVERSE NODES IN K-GROUP
* Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
* k is a positive integer and is less than or equal to the length of the linked list.
* If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
* You may not alter the values in the list's nodes, only nodes themselves may be changed. */
ListNode* ReverseKGroup(ListNode* head, const int k)
{
	// Special case
	if (!head->next || k == 1)	return head;

	ListNode dummy(-1, head);
	ListNode* prev = &dummy;

	int length = GetListLength(head);
	for (int i = 0; i < length / k; i++)
	{
		for (int j = 1; j < k; j++)
		{
			ListNode* after = prev->next;
			prev->next = head->next;
			head->next = head->next->next;
			prev->next->next = after;
		}

		prev = head;
		head = head->next;
	}

	return dummy.next;
}

/* PROBLEM 26: REMOVE DUPLICATES FROM SORTED ARRAY
* Given an integer array nums sorted in non-decreasing order,
* remove the duplicates in-place such that each unique element appears only once.
* The relative order of the elements should be kept the same.
* Return k after placing the final result in the first k slots of nums.
* Do not allocate extra space for another array.
* You must do this by modifying the input array in-place with O(1) extra memory. */
int RemoveDuplicates(std::vector<int>& nums)
{
	size_t length = nums.size();
	for (int i = 0; i < length - 1; i++)
	{
		int j = i + 1;
		while (j < length && nums[i] == nums[j])
		{
			j++;
			length--;
		}
		if (j > i + 1)
		{
			nums.erase(nums.begin() + (i + 1), nums.begin() + j);
		}
	}

	return length;
}

/* PROBLEM 27: REMOVE ELEMENT
* Given an integer array nums and an integer val, remove all occurrences of val in nums in-place.
* The relative order of the elements may be changed.
* Do not allocate extra space for another array.
* You must do this by modifying the input array in-place with O(1) extra memory. */
int RemoveElement(std::vector<int>& nums, const int val)
{
	int length = nums.size();
	int left = 0;
	int right = length - 1;
	while (left <= right)
	{
		if (nums[left] == val)
		{
			nums[left] = nums[right];
			right--;
		}
		else
			left++;
	}

	return left;
}

/* PROBLEM 28: IMPLEMENT STRSTR()
* Given two strings needle and haystack, return the index of the first occurrence of needle in haystack,
* or -1 if needle is not part of haystack. */
int StrStr(const std::string& haystack, const std::string& needle)
{
	int hLength = haystack.length();
	int nLength = needle.length();

	for (int i = 0; i < hLength; i++)
	{
		int k = 0;
		while ((i + k) < hLength && k < nLength && haystack[i + k] == needle[k])
			k++;

		if (k == nLength)
			return i;

		i += k;
	}

	return -1;
}

/* PROBLEM 29: DIVIDE TWO INTEGERS
* Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
* The integer division should truncate toward zero, which means losing its fractional part.
* For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
* Return the quotient after dividing dividend by divisor.
* Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range. */
int Divide(int dividend, int divisor)
{
	int quotient = 0;

	// Special cases
	if (dividend == INT_MIN)
	{
		if (divisor == 1)	return INT_MIN;
		else if (divisor == -1)	return INT_MAX;
		else
		{
			dividend += abs(divisor);
			quotient++;
		}
	}

	if (divisor == INT_MIN)
	{
		if (dividend == divisor)	return 1;
		else						return 0;
	}

	bool negative = dividend > 0 ^ divisor > 0;

	dividend = abs(dividend);
	divisor = abs(divisor);

	while (dividend >= divisor)
	{
		int multiplier = 1;
		int currDividend = dividend >> 1;
		int currDivisor = divisor;

		while (currDividend >= divisor)
		{
			currDivisor <<= 1;
			multiplier <<= 1;
			currDividend >>= 1;
		}

		dividend -= currDivisor;
		quotient += multiplier;
	}

	return negative ? -quotient : quotient;
}

/* Checks if string is a permutation of words in seen. */
bool IsWordPermutation(std::unordered_map<std::string, int> seen, const std::string& string, const int wordLength)
{
	for (int k = 0; k < string.size(); k += wordLength)
	{
		std::string windowSegment = string.substr(k, wordLength);
		auto it = seen.find(windowSegment);
		if (it == seen.end() || it->second == 0)	// all occurrences of word is used or not in map
			return false;
		else
			it->second--;	// use one instance of word
	}

	return true;
}

/* PROBLEM 30: SUBSTRING WITH CONCATENATION OF ALL WORDS
* You are given a string s and an array of strings words. All the strings of words are of the same length.
* A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.
* For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings.
* "acdbef" is not a concatenated substring because it is not the concatenation of any permutation of words.
* Return the starting indices of all the concatenated substrings in s. You can return the answer in any order. */
std::vector<int> FindSubstring(const std::string& string, const std::vector<std::string>& words)
{
	std::vector<int> result;
	std::unordered_map<std::string, int> seen;
	for (const auto& word : words)
		seen[word]++;

	const int strLength = string.length();

	const int wordLength = words[0].length();
	const int numWords = words.size();
	const int winLength = numWords * wordLength;

	int left = 0;
	int right = winLength - 1;
	while (right < strLength)
	{
		std::string window = string.substr(left, winLength);
		if (IsWordPermutation(seen, window, wordLength))
			result.push_back(left);

		left++;
		right++;
	}

	return result;
}

/* PROBLEM 31: NEXT PERMUTATION
* A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
* For example, for arr = [1,2,3], the following are considered permutations of arr: [1,2,3], [1,3,2], [3,1,2], [2,3,1].
* The next permutation of an array of integers is the next lexicographically greater permutation of its integer.
* More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container.
* If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
* Given an array of integers nums, find the next permutation of nums.
* The replacement must be in place and use only constant extra memory. */
void NextPermutation(std::vector<int>& nums)
{
	const int length = nums.size();

	// Find pivot
	int pivot = length - 1;
	while (pivot > 0 && nums[pivot - 1] >= nums[pivot])
		pivot--;

	// Special case: loop back around
	if (pivot == 0)
	{
		std::reverse(nums.begin(), nums.end());
		return;
	}
	else
		pivot--;

	// Find first successor candidate
	int succ = length - 1;
	while (succ > pivot && nums[succ] <= nums[pivot])
		succ--;

	// Find closest greater integer to nums[pivot]
	int curr = succ;
	while (curr > pivot)
	{
		if (nums[curr] > nums[pivot] && nums[curr] < nums[succ])
			succ = curr;

		curr--;
	}

	// Swap pivot with its successor
	std::swap(nums[pivot], nums[succ]);

	// Reverse suffix (subarray after pivot)
	std::reverse(nums.begin() + (pivot + 1), nums.end());
}

/* PROBLEM 32: LONGEST VALID PARENTHESES
* Given a string containing just the characters '(' and ')',
* find the length of the longest valid (well-formed) parentheses substring. */
int LongestValidParentheses(const std::string& string)
{
	const int length = string.length();
	if (length == 0) return 0;	// empty string

	std::stack<int> stack;
	stack.push(-1);
	int maxLength = 0;
	for (int i = 0; i < length; i++)
	{
		if (string[i] == '(')
			stack.push(i);
		else
		{
			stack.pop();
			if (stack.empty())
				stack.push(i);
			else
			{
				int currLength = i - stack.top();
				maxLength = std::max(maxLength, currLength);
			}
		}
	}

	return maxLength;
}

/* PROBLEM 33: SEARCH IN ROTATED ARRAY
* There is an integer array nums sorted in ascending order (with distinct values).
* Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length)
* such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
* For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].
* Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums,
* or -1 if it is not in nums.
* You must write an algorithm with O(log n) runtime complexity. */
int Search(const std::vector<int>& nums, const int target)
{
	const int length = nums.size();

	int left = 0;
	int right = length - 1;
	while (right > left)
	{
		int center = (left + right) / 2;
		if (nums[center] == target)
			return center;
		else if (nums[center] < nums[right])
		{
			if (nums[center] < target && nums[right] >= target)
				left = center + 1;
			else
				right = center - 1;
		}
		else
		{
			if (nums[left] <= target && nums[center] > target)
				right = center - 1;
			else
				left = center + 1;
		}
	}

	return -1;
}

/* PROBLEM 34: FIND FIRST AND LAST POSITION OF ELEMENT IN SORTED ARRAY
* Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
* If target is not found in the array, return [-1, -1].
* You must write an algorithm with O(log n) runtime complexity. */
std::vector<int> SearchRange(const std::vector<int>& nums, const int target)
{
	const int length = nums.size();
	std::vector<int> result(2, -1);

	// Find first occurrence
	int left = 0;
	int right = length - 1;
	while (left <= right)
	{
		int center = left + (right - left) / 2;
		if (nums[center] < target)
			left = center + 1;
		else
		{
			if (nums[center] == target)
				result[0] = center;
			right = center - 1;
		}
	}

	// Find last occurrence
	left = 0;
	right = length - 1;
	while (left <= right)
	{
		int center = left + (right - left) / 2;
		if (nums[center] > target)
			right = center - 1;
		else
		{
			if (nums[center] == target)
				result[1] = center;
			left = center + 1;
		}
	}

	return result;
}

/* PROBLEM 35: SEARCH INSERT POSITION
* Given a sorted array of distinct integers and a target value, return the index if the target is found.
* If not, return the index where it would be if it were inserted in order.
* You must write an algorithm with O(log n) runtime complexity. */
int SearchInsert(const std::vector<int>& nums, const int target)
{
	const int length = nums.size();

	int left = 0;
	int right = length - 1;
	while (left <= right)
	{
		int center = left + (right - left) / 2;
		if (nums[center] == target)
			return center;
		else if (nums[center] < target)
			left = center + 1;
		else
			right = center - 1;
	}

	return left;
}

/* PROBLEM 36: VALID SUDOKU
* Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
*	Each row must contain the digits 1-9 without repetition.
* 	Each column must contain the digits 1-9 without repetition.
* 	Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
* Note:
*	A Sudoku board (partially filled) could be valid but is not necessarily solvable.
* 	Only the filled cells need to be validated according to the mentioned rules. */
bool isValidSudoku(const std::vector<std::vector<char>>& board)
{
	const int rows = 9;
	const int cols = 9;
	const int boxes = 9;

	// Check rows
	for (int i = 0; i < rows; i++)
	{
		std::unordered_map<char, bool> used;
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] != '.')	// not an empty cell
			{
				auto it = used.find(board[i][j]);
				if (it != used.end() && it->second)	// exists and already used
					return false;
				else
					used[board[i][j]] = true;
			}
		}
	}

	// Check columns
	for (int j = 0; j < cols; j++)
	{
		std::unordered_map<char, bool> used;
		for (int i = 0; i < rows; i++)
		{
			if (board[i][j] != '.')	// not an empty cell
			{
				auto it = used.find(board[i][j]);
				if (it != used.end() && it->second)	// exists and already used
					return false;
				else
					used[board[i][j]] = true;
			}
		}
	}

	// Check 3x3 sub-boxes
	for (int i = 0; i < boxes; i++)
	{
		std::unordered_map<char, bool> used;
		for (int j = 0; j < boxes; j++)
		{
			int row = (i / 3) * 3 + j / 3;
			int col = (i % 3) * 3 + j % 3;
			if (board[row][col] != '.')	// not an empty cell
			{
				auto it = used.find(board[row][col]);
				if (it != used.end() && it->second)	// exists and already used
					return false;
				else
					used[board[row][col]] = true;
			}
		}
	}

	return true;
}

bool IsValidBoard(const std::vector<std::vector<char>>& board, const int currRow, const int currCol, const char c)
{
	// Check rows
	for (int i = 0; i < 9; i++)
	{
		if (board[i][currCol] == c)
			return false;
	}

	// Check columns
	for (int j = 0; j < 9; j++)
	{
		if (board[currRow][j] == c)
			return false;
	}

	// Check box
	int boxRow = (currRow / 3) * 3;
	int boxCol = (currCol / 3) * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[boxRow + i][boxCol + j] == c)
				return false;
		}
	}

	return true;
}

bool SudokuBacktrack(std::vector<std::vector<char>>& board, int row, int col)
{
	if (row == 9)	// filled in all squares
		return true;

	if (col == 9)	// done with current row
		return SudokuBacktrack(board, row + 1, 0);

	if (board[row][col] != '.')	// skip already occupied cells
		return SudokuBacktrack(board, row, col + 1);

	for (char c = '1'; c <= '9'; c++)
	{
		if (IsValidBoard(board, row, col, c))
		{
			board[row][col] = c;
			if (SudokuBacktrack(board, row, col + 1))
				return true;
			board[row][col] = '.';	// backtrack
		}
	}

	return false;
}

/* PROBLEM 37: SUDOKU SOLVER
* Write a program to solve a Sudoku puzzle by filling the empty cells.
* A sudoku solution must satisfy all of the following rules:
* 	Each of the digits 1-9 must occur exactly once in each row.
* 	Each of the digits 1-9 must occur exactly once in each column.
* 	Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
* The '.' character indicates empty cells. */
void SolveSudoku(std::vector<std::vector<char>>& board)
{
	SudokuBacktrack(board, 0, 0);
}

/* PROBLEM 38: COUNT AND SAY
* The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
* 	countAndSay(1) = "1"
* 	countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.
* To determine how you "say" a digit string, split it into the minimal number of substrings such that each substring contains exactly one unique digit.
* Then for each substring, say the number of digits, then say the digit. Finally, concatenate every said digit.
* Given a positive integer n, return the nth term of the count-and-say sequence. */
std::string CountAndSay(const int n)
{
	// Iterative approach
	std::string result = "1";
	int iter = 1;
	while (iter < n)
	{
		std::string tempResult = "";
		const int length = result.length();
		int idx = 0;
		while (idx < length)
		{
			int digitCount = 1;
			while (idx < length - 1 && result[idx] == result[idx + 1])
			{
				idx++;
				digitCount++;
			}

			tempResult += std::to_string(digitCount);
			tempResult += result[idx];
			idx++;
		}

		result = tempResult;
		iter++;
	}

	return result;
}

/* Combination sum helper method. */
void CombinationSumBacktrack(const std::vector<int>& candidates,
	std::vector<std::vector<int>>& combinations, std::vector<int>& combination,
	const int size, int index, int target)
{
	if (target == 0)
	{
		combinations.push_back(combination);
		return;
	}

	while (index < size && (target - candidates[index]) >= 0)
	{
		// Add to current combination
		combination.push_back(candidates[index]);

		// Generate all possible combinations
		CombinationSumBacktrack(candidates, combinations, combination, size, index, target - candidates[index]);
		index++;

		// Backtrack
		combination.pop_back();
	}
}

/* PROBLEM 39: COMBINATION SUM
* Given an array of distinct integers candidates and a target integer target,
* return a list of all unique combinations of candidates where the chosen numbers sum to target.
* You may return the combinations in any order.
* The same number may be chosen from candidates an unlimited number of times.
* Two combinations are unique if the frequency of at least one of the chosen numbers is different.
* It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input. */
std::vector<std::vector<int>> CombinationSum(std::vector<int>& candidates, const int target)
{
	std::sort(candidates.begin(), candidates.end());

	const int size = candidates.size();
	std::vector<std::vector<int>> combinations;
	std::vector<int> combination;

	CombinationSumBacktrack(candidates, combinations, combination, size, 0, target);

	return combinations;
}

/* Combination sum 2 helper method. */
void CombinationSum2Backtrack(const std::vector<int>& candidates,
	std::vector<std::vector<int>>& combinations, std::vector<int>& combination,
	const int size, int index, const int target)
{
	if (target == 0)
	{
		combinations.push_back(combination);
		return;
	}

	for (int i = index; i < size; i++)
	{
		if (candidates[i] > target)
			break;
		if (i > index && candidates[i] == candidates[i - 1])
			continue;

		combination.push_back(candidates[i]);

		CombinationSum2Backtrack(candidates, combinations, combination, size, i + 1, target - candidates[i]);

		combination.pop_back();
	}
}

/* PROBLEM 40: COMBINATION SUM 2
* Given a collection of candidate numbers (candidates) and a target number (target),
* find all unique combinations in candidates where the candidate numbers sum to target.
* Each number in candidates may only be used once in the combination.
* Note: The solution set must not contain duplicate combinations. */
std::vector<std::vector<int>> CombinationSum2(std::vector<int>& candidates, const int target)
{
	std::sort(candidates.begin(), candidates.end());

	const int size = candidates.size();
	std::vector<std::vector<int>> combinations;
	std::vector<int> combination;

	CombinationSum2Backtrack(candidates, combinations, combination, size, 0, target);

	return combinations;
}

/* PROBLEM 41: FIRST MISSING POSITIVE
* Given an unsorted integer array nums, return the smallest missing positive integer.
* You must implement an algorithm that runs in O(n) time and uses constant extra space. */
int FirstMissingPositive(std::vector<int>& nums)
{
	const int size = nums.size();

	// Make nums[i] = i + 1 for all i, if possible
	for (int i = 0; i < size; i++)
	{
		int temp = nums[i];
		while (temp > 0 && temp <= size && nums[temp - 1] != temp)
		{
			int temp2 = nums[temp - 1];
			nums[temp - 1] = temp;
			temp = temp2;
		}
	}

	// Iterate until nums[i] != i + 1
	int idx = 0;
	while (idx < size && nums[idx] == idx + 1)
		idx++;

	int missing = idx + 1;
	return missing;
}

/* PROBLEM 42: TRAPPING RAIN WATER
* Given n non-negative integers representing an elevation map where the width of each bar is 1,
* compute how much water it can trap after raining. */
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

/* PROBLEM 43: MULTIPLY STRINGS
* Given two non-negative integers num1 and num2 represented as strings,
* return the product of num1 and num2, also represented as a string.
* Note: You must not use any built-in BigInteger library or convert the inputs to integer directly. */
std::string Multiply(const std::string& num1, const std::string& num2)
{
	const int length1 = num1.length();
	const int length2 = num2.length();
	std::string result(length1 + length2, '0');

	for (int i = length2 - 1; i >= 0; i--)
	{
		int carry = 0;
		int multiplier = num2[i] - '0';
		for (int j = length1 - 1; j >= 0; j--)
		{
			int digit = num1[j] - '0';
			int tempResult = (result[i + j + 1] - '0') + (multiplier * digit) + carry;

			result[i + j + 1] = tempResult % 10 + '0';
			carry = tempResult / 10;
		}
		result[i] += carry;
	}

	int startpos = result.find_first_not_of("0");
	if (std::string::npos != startpos)
		return result.substr(startpos);

	return "0";
}

/* PROBLEM 44: WILDCARD MATCHING (INCOMPLETE)
* Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
* 	'?' Matches any single character.
* 	'*' Matches any sequence of characters (including the empty sequence).
* The matching should cover the entire input string (not partial). */
bool WildcardMatch(const std::string& string, const std::string& pattern)
{
	return true;
}

/* PROBLEM 45: JUMP GAME II
* Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
* Each element in the array represents your maximum jump length at that position.
* Your goal is to reach the last index in the minimum number of jumps.
* You can assume that you can always reach the last index. */
int Jump2(const std::vector<int>& nums)
{
	/* Dynamic Programming */
	const int size = nums.size();
	std::vector<int> dp(size, INT_MAX);
	dp[0] = 0;

	for (int i = 0; i < size; i++)
	{
		int maxJump = nums[i];
		for (int j = i + 1; j < i + 1 + maxJump; j++)
		{
			if (j < size)
				dp[j] = std::min(dp[j], dp[i] + 1);
		}
	}

	return dp[size - 1];
}

/* Generate permutations using backtracking. */
void PermuteRec(std::vector<std::vector<int>>& permutations, std::vector<int>& perm, int idx, int size)
{
	if (idx == size)
	{
		permutations.push_back(perm);
		return;
	}

	for (int i = idx; i < size; i++)
	{
		std::swap(perm[i], perm[idx]);
		PermuteRec(permutations, perm, idx + 1, size);
		std::swap(perm[i], perm[idx]);
	}
}

/* PROBLEM 46: PERMUTATIONS
* Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order. */
std::vector<std::vector<int>> Permute(std::vector<int>& nums)
{
	const int size = nums.size();
	std::vector<std::vector<int>> permutations;
	PermuteRec(permutations, nums, 0, size);

	return permutations;
}

/* Generate unique permutations using backtracking. */
void PermuteRec2(std::vector<std::vector<int>>& permutations, std::vector<int>& perm, int idx, int size)
{
	if (idx == size)
	{
		permutations.push_back(perm);
		return;
	}

	for (int i = idx; i < size; i++)
	{
		if (i != idx && perm[i] == perm[idx])
			continue;
		std::swap(perm[i], perm[idx]);
		PermuteRec2(permutations, perm, idx + 1, size);
		std::swap(perm[i], perm[idx]);
	}
}

/* PROBLEM 47: PERMUTATIONS II */
std::vector<std::vector<int>> PermuteUnique(std::vector<int>& nums) 
{
	const int size = nums.size();
	std::vector<std::vector<int>> permutations;
	PermuteRec2(permutations, nums, 0, size);

	return permutations;
}

/* Rotates 4 elements in a matrix 90 degrees clockwise. */
void RotateFourElements(std::vector<std::vector<int>>& matrix, int iter, int end, int i)
{
	int cache = matrix[end - i][iter];
	matrix[end - i][iter] = matrix[end][end - i];	// set left side
	matrix[end][end - i] = matrix[i + iter][end];	// set bottom
	matrix[i + iter][end] = matrix[iter][i + iter];	// set right side
	matrix[iter][i + iter] = cache;					// set top
}

/* PROBLEM 48: ROTATE IMAGE */
void Rotate(std::vector<std::vector<int>>& matrix)
{
	const int dim = matrix.size();
	
	int end = dim - 1;
	for (int iter = 0; iter < dim / 2; iter++)
	{
		for (int i = 0; i < end - iter; i++)
		{
			RotateFourElements(matrix, iter, end, i);
		}

		end--;
	}
}

/* PROBLEM 49: GROUP ANAGRAMS */
std::vector<std::vector<std::string>> GroupAnagrams(const std::vector<std::string>& strings) 
{
	const int size = strings.size();

	std::vector<std::vector<std::string>> anagrams;
	std::unordered_map<std::string, int> hash;
	int hashIdx = 0;

	for (int i = 0; i < size; i++)
	{
		std::string sortedCopy = strings[i];
		std::sort(sortedCopy.begin(), sortedCopy.end());

		auto it = hash.find(sortedCopy);
		if (it != hash.end())
			anagrams[hash[sortedCopy]].push_back(strings[i]);
		else
		{
			hash[sortedCopy] = hashIdx;
			anagrams.push_back({ strings[i] });
			hashIdx++;
		}
	}

	return anagrams;
}

/* PROBLEM 50: POW(X, N) */
double MyPow(double x, int n)
{
	if (x == 0 || x == 1 || n == 1)
		return x;
	else if (n == 0)
		return 1;
	else if (n == -1)
		return 1.0 / x;
	else if (n % 2 == 0)
	{
		double result = (n > 0) ? MyPow(x, n / 2) : MyPow(x, abs(n / 2));
		return (n > 0) ? (result * result) : (1.0 / (result * result));
	}
	else
	{
		double result = (n > 0) ? MyPow(x, n / 2) : MyPow(x, abs(n / 2));
		return (n > 0) ? (x * result * result) : (1.0 / (x * result * result));
	}
}

int main()
{
	
}