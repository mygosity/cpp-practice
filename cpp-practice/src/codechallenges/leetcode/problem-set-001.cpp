#pragma once
#include "problem-set-001.h"

namespace codechallenges
{
	namespace leetcode
	{
		using ListNode = ProblemSet001::ListNode;

		/**********************************************************************
			Problem 13: Easy - Roman Numerals to Integer
			Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
			Symbol       Value
			I             1
			V             5
			X             10
			L             50
			C             100
			D             500
			M             1000
			For example, two is written as II in Roman numeral, just two one's added together. 
			Twelve is written as, XII, which is simply X + II. 
			The number twenty seven is written as XXVII, which is XX + V + II.

			Roman numerals are usually written largest to smallest from left to right. 
			However, the numeral for four is not IIII. Instead, the number four is written as IV. 
			Because the one is before the five we subtract it making four. 
			The same principle applies to the number nine, which is written as IX. 
			There are six instances where subtraction is used:

			I can be placed before V (5) and X (10) to make 4 and 9.
			X can be placed before L (50) and C (100) to make 40 and 90.
			C can be placed before D (500) and M (1000) to make 400 and 900.
			Given a roman numeral, convert it to an integer. 
			Input is guaranteed to be within the range from 1 to 3999.
		***********************************************************************/
		static map<char, int> roman_table = {
			{'M', 1000},
			{'D', 500},
			{'C', 100},
			{'L', 50},
			{'X', 10},
			{'V', 5},
			{'I', 1}
		};
		static map<char, char> roman_jumpset = {
			{'M', 'C'},
			{'D', 'C'},
			{'C', 'X'},
			{'L', 'X'},
			{'X', 'I'},
			{'V', 'I'}
		};
		int romanToInt(string s) {
			int a = 0;
			int end = s.size();
			for (int i = 0; i < s.size(); ++i) {
				char c = s[i];
				char n = i + 1 < end ? s[i + 1] : ' ';
				if (n != ' ' && c == roman_jumpset[n]) {
					a += roman_table[n] - roman_table[roman_jumpset[n]];
					++i;
				}
				else
				{
					a += roman_table[c];
				}
			}
			return a;
		}

		void RomanNumeralsConversion() 
		{
			LOG(romanToInt("IV"));
			LOG(romanToInt("MMMXCVIII"));
		}

		/**********************************************************************
			Problem 9: Easy - Palindrome Integer
			Determine whether an integer is a palindrome.
			An integer is a palindrome when it reads the same backward as forward.
		***********************************************************************/
		bool isPalindrome(int x) {
			if (x < 0)
				return false;
			vector<int> vec;
			int t = x;
			while (t > 0) {
				vec.push_back(t % 10);
				t /= 10;
			}
			for (int i = 0; i < vec.size(); ++i) {
				int j = vec.size() - 1 - i;
				if (i == j) {
					return true;
				}
				if (vec[i] != vec[j]) {
					return false;
				}
			}
			return true;
		}

		void Is_Number_Palindrome()
		{
			LOG("isPalindrome(121): " << isPalindrome(121));
			LOG("isPalindrome(-121): " << isPalindrome(-121));
			LOG("isPalindrome(1210): " << isPalindrome(1210));
		}

		/**********************************************************************
			Problem 7: Medium - String to Integer (atoi)
			Implement atoi which converts a string to an integer.

			The function first discards as many whitespace characters as necessary until 
			the first non-whitespace character is found. Then, starting from this character, 
			takes an optional initial plus or minus sign followed by as many numerical digits 
			as possible, and interprets them as a numerical value.

			The string can contain additional characters after those that form the integral 
			number, which are ignored and have no effect on the behavior of this function.

			If the first sequence of non-whitespace characters in str is not a valid integral 
			number, or if no such sequence exists because either str is empty or it 
			contains only whitespace characters, no conversion is performed.

			If no valid conversion could be performed, a zero value is returned.

		***********************************************************************/

		//gross brute force method but this question was quite annoying to answer ...
		int myAtoi(string str) {
			int a = 0;
			int positive = 1;
			int zeroCharCode = (int)'0';
			int nineCharCode = (int)'9';
			const int maxIntLen = 10;
			int arr[maxIntLen] = { 0 };
			int index = 0;
			int len = str.size();
			int foundNumber = 0;

			int whiteSpaceIndex = -1;
			int plusSigns = 0;
			int negativeSigns = 0;
			int nonWhiteSpaceChr = 0;
			int zeroes = 0;
			for (int i = 0; i < len; ++i) {
				char s = str[i];
				int c = s - zeroCharCode;
				if (foundNumber == 0) {
					if (c > 0 && c <= 9) {
						foundNumber = 1;
						arr[index++] = c;
					}
					else {
						switch (s) {
						case '-': {
							positive = -1;
							if (negativeSigns > 0 || plusSigns > 0 || zeroes > 0) {
								return 0;
							}
							negativeSigns++;
							break;
						}
						case ' ': {
							//successive white space indexes indicate invalid input
							if (whiteSpaceIndex > -1 && whiteSpaceIndex != i - 1 || zeroes > 0) {
								// std::cout <<"whiteSpaceIndex: " << whiteSpaceIndex << std::endl;
								return 0;
							}
							if (negativeSigns > 0) {
								return 0;
							}
							whiteSpaceIndex = i;
							break;
						}
						case '+': {
							if (positive == -1 || plusSigns > 0) {
								return 0;
							}
							plusSigns++;
							break;
						}
						case '0': {
							zeroes++;
							break;
						}
						default: {
							return 0;
						}
						}
					}
				}
				else {
					if (c >= 0 && c <= 9) {
						if (index >= maxIntLen) {
							return positive == 1 ? INT_MAX : INT_MIN;
						}
						arr[index++] = c;
					}
					else {
						break;
					}
				}
			}
			index--;
			if (index < 0) {
				return 0;
			}
			bool checkLimits = index >= maxIntLen - 1;
			// std::cout << "checkLimits: " << checkLimits << " index: " << index << " positive: " << positive << std::endl;
			if (checkLimits) {
				if (arr[0] > 2) {
					return positive == 1 ? INT_MAX : INT_MIN;
				}
			}
			for (int i = 0; i < maxIntLen; ++i) {
				a += arr[i] * pow(10, index);
				index--;
				if (index < 0) {
					if (checkLimits) {
						if (positive == 1) {
							// std::cout << "positive: " << positive << " a: " << a << std::endl;
							if (a < 0) {
								return INT_MAX;
							}
						}
						else {
							long test = (long)a + 1;
							if (test - 1 <= INT_MIN) {
								return INT_MIN;
							}
						}
					}
					return a * positive;
				}
			}
			return a * positive;
		}

		void MyStringToIntegerParser() 
		{
			LOG("myAtoi(42): " << myAtoi("42"));
			LOG("myAtoi(-2147483648): " << myAtoi("-2147483648"));
			LOG("myAtoi(2147483648): " << myAtoi("2147483648"));

			//std::cout << "(int)char : (int)-: " << (int)'-' << std::endl;
			//std::cout << "(int)char : (int)0: " << (int)'0' << std::endl;
			//std::cout << "(int)char : (int)1: " << (int)'1' << std::endl;
			//std::cout << "(int)char : (int)2: " << (int)'2' << std::endl;
			//std::cout << "(int)char : (int)3: " << (int)'3' << std::endl;
			//std::cout << "(int)char : (int)4: " << (int)'4' << std::endl;
			//std::cout << "(int)char : (int)5: " << (int)'5' << std::endl;
			//std::cout << "(int)char : (int)6: " << (int)'6' << std::endl;
			//std::cout << "(int)char : (int)7: " << (int)'7' << std::endl;
			//std::cout << "(int)char : (int)8: " << (int)'8' << std::endl;
			//std::cout << "(int)char : (int)9: " << (int)'9' << std::endl;
		}

		/**********************************************************************
			Problem 6: Medium - Convert to zig zag
			The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
			P   A   H   N
			A P L S I I G
			Y   I   R
			And then read line by line: "PAHNAPLSIIGYIR"

			Write the code that will take a string and make this conversion given a number of rows:

			string convert(string s, int numRows);
			Example 1:

			Input: s = "PAYPALISHIRING", numRows = 3
			Output: "PAHNAPLSIIGYIR"
		***********************************************************************/

		//this actually calculates at the same rate as my own after testing it.. but it is shorter!
		string publicSolutionZigZag(string s, int nRows) {
			if (nRows <= 1)
				return s;
			string res = "";
			int size = 2 * nRows - 2;
			for (int i = 0; i < nRows; ++i) {
				for (int j = i; j < s.size(); j += size) {
					res += s[j];
					int tmp = j + size - 2 * i;
					if (i != 0 && i != nRows - 1 && tmp < s.size())
						res += s[tmp];
				}
			}
			return res;
		}

		//upon retrospection I could've shortened it like the public solution above. dang it!
		string fasterConvertZigZag(string s, int numRows) {
			int len = s.size();
			if (len == 1 || numRows == 1 || len < numRows) {
				return s;
			}
			string a;
			int added = 0;
			int ptr = 0;
			int row = 0;
			bool add = false;
			// std::cout << "len: " << len << std::endl;
			while (added < len) {
				// std::cout << "s[ptr]: " << s[ptr] << " ptr: " << ptr << " added: " << added << " row: " << row << std::endl;
				a.push_back(s[ptr]);
				add = !add;
				ptr += (numRows - 1) + numRows - 1;
				if (add && row != 0 && row != numRows - 1) {
					int additional = ptr - row * 2;
					if (additional > 0 && additional < len) {
						// std::cout << "additional : " << s[additional] << std::endl;
						a.push_back(s[additional]);
						added++;
						add = false;
					}
				}
				if (ptr >= len) {
					row++;
					ptr = row;
					add = false;
				}
				added++;
			}
			return a;
		}

		//slow brute force method
		string convertZigZag(string s, const int numRows) {
			int len = s.size();
			if (len == 1 || numRows == 1 || len < numRows) {
				return s;
			}
			int count = 0;
			int** matrix = new int* [numRows];
			for (int i = 0; i < numRows; i++)
			{
				matrix[i] = new int[len];
				for (int j = 0; j < len; ++j) {
					matrix[i][j] = 0;
					count++;
				}
			}
			//LOG("matrix count: " << count);

			int x = 0, y = 0;
			bool forwards = true;
			for (int i = 0; i < len; ++i) {
				matrix[y][x] = i + 1;
				y = forwards ? ++y : --y;
				if (forwards) {
					if (y >= numRows) {
						forwards = false;
						y = numRows - 2;
						x++;
					}
				}
				else
				{
					if (y < 0) {
						forwards = true;
						y = 0;
					}
					else
					{
						x++;
					}
				}
			}
			string a;
			for (int row = 0; row < numRows; ++row) {
				for (int column = 0; column < len; ++column) {
					int i = matrix[row][column];
					if (i != 0) {
						//std::cout << "index: " << (i - 1) << std::endl;
						a.push_back(s[i - 1]);
					}
				}
			}
			for (int i = 0; i < numRows; i++)
				delete[] matrix[i];
			delete[] matrix;
			return a;
		}

		void ConvertToZigZag()
		{
			LOG(convertZigZag("PAYPALISHIRING", 3));
			LOG(convertZigZag("PAYPALISHIRING", 4));
			LOG("");
			LOG("fasterConvertZigZag: answer and expected: \n" << fasterConvertZigZag("PAYPALISHIRING", 3) << " \n" << "PAHNAPLSIIGYIR");
			LOG("fasterConvertZigZag: answer and expected: \n" << fasterConvertZigZag("PAYPALISHIRING", 4) << " \n" << "PINALSIGYAHRPI");
		}

		/**********************************************************************
			Problem 5: Medium - Longest Palindromic Substring
			Given a string s, find the longest palindromic substring in s.
			You may assume that the maximum length of s is 1000.
		***********************************************************************/

		string maxString(string& a, string& b, string& c) {
			// std::cout << "a:" << a << " b: " << b << " c: " << c << std::endl;
			if (a.size() > b.size()) {
				if (a.size() > c.size()) {
					return a;
				}
				else {
					return c;
				}
			}
			else
			{
				if (b.size() > c.size()) {
					return b;
				}
				else {
					return c;
				}
			}
		}

		string extractPalindrome(string& s, int startingIndex, int end) {
			if (s.size() == 2) {
				if (s[0] == s[1]) {
					return s;
				}
				return s.substr(0,1);
			}
			if (s.size() < 2) {
				return "";
			}
			char middle = s[startingIndex];

			int leftIndex = startingIndex;
			int rightIndex = startingIndex;
			int prevLeftIndex = leftIndex;
			int prevRightIndex = rightIndex;
			char left = s[leftIndex];
			char right = s[rightIndex];
			int pass = 0;
			while (leftIndex >= 0 && rightIndex < end) {
				left = leftIndex - 1 >= 0 ? s[leftIndex - 1] : ' ';
				right = rightIndex + 1 < end ? s[rightIndex + 1] : ' ';
				prevLeftIndex = leftIndex;
				prevRightIndex = rightIndex;
				if (middle == right) {
					rightIndex = rightIndex + 1 >= end ? end - 1 : rightIndex + 1;
					pass++;
				}
				if (middle == left) {
					leftIndex = leftIndex - 1 < 0 ? 0 : leftIndex - 1;
					pass++;
				}
				if (leftIndex == 0 && rightIndex == end - 1) {
					if (middle == left && middle == right) {
						return s;
					}
					break;
				}
				if (prevLeftIndex == leftIndex && prevRightIndex == rightIndex) {
					break;
				}
			}
			while (leftIndex >= 0 && rightIndex < end)
			{
				left = leftIndex - 1 >= 0 ? s[leftIndex - 1] : ' ';
				right = rightIndex + 1 < end ? s[rightIndex + 1] : ' ';
				if (left != right) {
					//if the first check fails return empty string
					if (pass == 0) {
						// std::cout << "s[startingIndex]: " << s[startingIndex] << " s[leftIndex]: " << s[leftIndex] << " s[rightIndex]: " << s[rightIndex] << std::endl;
						if (middle == left) {
							return string(s, leftIndex, 2);
						}
						else if (middle == right) {
							return string(s, startingIndex, 2);
						}
						return "";
					}
					break;
				}
				--leftIndex;
				++rightIndex;
				pass++;
			}
			leftIndex = leftIndex < 0 ? 0 : leftIndex;
			rightIndex = rightIndex >= end ? end - 1 : rightIndex;
			//std::cout << "leftIndex: " << leftIndex << " rightIndex: " << rightIndex << " (rightIndex - leftIndex + 1: )" << (rightIndex - leftIndex + 1) << std::endl;
			//std::cout << "end: "<< end << std::endl;
			return string(s, leftIndex, rightIndex - leftIndex + 1);
		}

		string longestPalindrome(string& s) {
			if (s.size() == 2 && s[0] == s[1]) {
				return s;
			}
			if (s.size() < 2) {
				return s;
			}

			int total = s.size();
			int middle = (total - 0.5) / 2;
			string longest = extractPalindrome(s, middle, total);
			int nextMax = ((total - 1) - (middle + 1)) * 2 + 1;
			// std::cout << "middle: " << middle << " total: " << total << " nextMax: " << nextMax << std::endl;
			if (longest.size() >= nextMax) {
				return longest;
			}
			int leftIndex = middle - 1;
			int rightIndex = middle + 1;
			while (leftIndex >= 0 || rightIndex < total)
			{
				//a palindrome on the right will be bigger than the left as the middle defaults to the shorter end
				string rightString = extractPalindrome(s, rightIndex, total);
				string leftString = leftIndex > 0 ? extractPalindrome(s, leftIndex, total) : "";
				// std::cout << "longest:" << longest.size() << " rightString: " << rightString.size() << " leftString: " << leftString.size() << std::endl;
				longest = maxString(longest, rightString, leftString);
				// std::cout << "longest: " << longest << " checky: " << ((total - rightIndex - 1) * 2 + 1) << std::endl;
				nextMax = ((total - 1) - (rightIndex + 1)) * 2 + 1;
				// std::cout << "longest.size(): " << longest.size() << " nextMax: " << nextMax << std::endl;
				if (longest.size() >= nextMax) {
					return longest;
				}
				--leftIndex;
				++rightIndex;
			}
			return longest.size() == 0 ? s.substr(0, 1) : longest;
		}

		//amazing fast cpp solution from public
		string publicSolution_longestPalindrome(string s) {
			int len = s.length();
			if (len < 2)
			{
				return s;
			}
			int i = 0;
			int start = 0, max = 1;
			int l_ptr = 0, r_ptr = 0;
			for (i = 0; i < len;)
			{
				l_ptr = i;
				r_ptr = i;
				while (r_ptr < len && s[l_ptr] == s[r_ptr])
				{
					++r_ptr;
				}
				i = r_ptr;
				--l_ptr;

				while (l_ptr > -1 && r_ptr < len && s[l_ptr] == s[r_ptr])
				{
					--l_ptr;
					++r_ptr;
				}

				if (r_ptr - l_ptr - 1 > max)
				{
					start = l_ptr + 1;
					max = r_ptr - l_ptr - 1;
				}
			}

			return s.substr(start, max);
		}

		void LongestPalindromicSubstring()
		{
			string s = "abcdasdfghjkldcba";
			string s2 = "cbbd";
			string s3 = "ccc";
			string s4 = "caba";
			string s5 = "aaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeffffffffffgggggggggghhhhhhhhhhiiiiiiiiiijjjjjjjjjjkkkkkkkkkkllllllllllmmmmmmmmmmnnnnnnnnnnooooooooooppppppppppqqqqqqqqqqrrrrrrrrrrssssssssssttttttttttuuuuuuuuuuvvvvvvvvvvwwwwwwwwwwxxxxxxxxxxyyyyyyyyyyzzzzzzzzzzyyyyyyyyyyxxxxxxxxxxwwwwwwwwwwvvvvvvvvvvuuuuuuuuuuttttttttttssssssssssrrrrrrrrrrqqqqqqqqqqppppppppppoooooooooonnnnnnnnnnmmmmmmmmmmllllllllllkkkkkkkkkkjjjjjjjjjjiiiiiiiiiihhhhhhhhhhggggggggggffffffffffeeeeeeeeeeddddddddddccccccccccbbbbbbbbbbaaaa";
			string s6 = "bananas";
			string s7 = "abadd";
			string s8 = "aaaabaaa";
			string s9 = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
			string s10 = "ac";
			string s11 = "abcda";

			string y10 = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
			string a10 = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
			//std::cout << y10.size() << std::endl;
			//std::cout << a10.size() << std::endl;
			std::cout << longestPalindrome(s) << std::endl;
			std::cout << longestPalindrome(s2) << std::endl;
			std::cout << longestPalindrome(s3) << std::endl;
			std::cout << longestPalindrome(s4) << std::endl;
			std::cout << longestPalindrome(s5) << std::endl;
			std::cout << longestPalindrome(s6) << std::endl;
			std::cout << longestPalindrome(s7) << std::endl;
			std::cout << longestPalindrome(s8) << std::endl;
			std::cout << longestPalindrome(s9) << std::endl;
			std::cout << longestPalindrome(s10) << std::endl;
			std::cout << longestPalindrome(s11) << std::endl;
		}

		/**********************************************************************
			Problem 3: Easy - Reverse Integer
			Given a 32 - bit signed integer, reverse digits of an integer.
			Use modulus to get digits and print them back with exponents
		***********************************************************************/
		int reverse(int x) {
			//integer overflow
			if (x <= INT_MIN || x >= INT_MAX)
				return 0;
			if (x < 0) {
				return (-1 * reverse(x * -1));
			}
			int t = x;
			int answer = 0;
			vector<int> list;
			while (t > 0) {
				list.push_back(t % 10);
				t /= 10;
			}
			int exp = list.size() - 1;
			for (int& i : list) {
				answer += i * pow(10, exp--);
			}
			//integer overflow
			if (answer < 0) {
				return 0;
			}
			return answer;
		}

		void Reverse_Integer()
		{
			LOG("Reverse_Integer:: 1321312 = " << reverse(1321312));
		}

		/**********************************************************************
			Problem 3: Medium - Longest Substring Without Repeating Characters
			using maps / maths to solve repeating character problem
			called sliding windows when moving indexes around
		***********************************************************************/

		//brute force method
		int lengthOfLongestSubstring(string& s) {
			int max = 0;
			std::map<int, int> dic;
			std::vector<int> list;
			for (int i = 0; i < s.size(); ++i) {
				int c = s[i];
				// std::cout << "s: " << s[i] << " c: " << c << " dic[c]:" << dic[c]<< std::endl;
				if (dic[c] != 0) {
					//'abcdvefged'
					//'dvdfa'
					int eraseInt = 0;
					max = max > list.size() ? max : list.size();
					bool deletefrom = false;
					for (int j = list.size() - 1; j >= 0; --j) {
						if (!deletefrom) {
							if (c == list[j]) {
								deletefrom = true;
								list.erase(list.begin() + j);
							}
						}
						else {
							dic[list[j]] = 0;
							list.erase(list.begin() + j);
						}
					}
					list.push_back(c);
				}
				else {
					list.push_back(c);
					dic[c] = 1;
				}
				// std::cout << c << std::endl;
			}
			//char* str = new char[list.size()];
			//for (int i = 0; i < list.size(); ++i) {
				//str[i] = (char)list[i];
			//}
			//LOG(str);
			//delete[] str;
			return max > list.size() ? max : list.size();
		}

		//slightly faster
		int fasterLengthOfLongestSubstring(string & s) {
			if (s.size() < 2) {
				return s.size();
			}
			int len = s.size(),
				count = 0,
				max = 0,
				fromIndex = 1;
			std::map<int, int> dic;
			for (int i = 0; i < len; ++i) {
				int c = s[i];
				int d = dic[c];
				// std::cout << "dic[c]: " << dic[c] << " fromIndex: " << fromIndex << std::endl;
				if (d != 0 && d > fromIndex - 1) {
					max = max > count ? max : count;
					fromIndex = d;
					count = i + 1 - fromIndex;
					dic[c] = i + 1;
				}
				else
				{
					//store unique index
					dic[c] = i + 1;
					count++;
				}
			}
			return max > count ? max : count;
		}

		//fastest using heuristics
		int fastestLengthOfLongestSubstring(string & s) {
			if (s.size() < 2) {
				return s.size();
			}
			int len = s.size(),
				count = 0,
				max = 0,
				fromIndex = 1;
			int dic[256] = {};
			for (int i = 0; i < len; ++i) {
				int c = s[i];
				int d = dic[c];
				if (d != 0 && d > fromIndex - 1)
				{
					max = max > count ? max : count;
					fromIndex = d;
					count = i + 1 - fromIndex;
					dic[c] = i + 1;
				}
				else
				{
					dic[c] = i + 1;
					count++;
				}
			}
			return max > count ? max : count;
		}

		void Longest_Substring()
		{
			std::string t1 = "abcdvefged";
			std::string t2 = "dvdfa";
			LOG(fastestLengthOfLongestSubstring(t1));
			LOG(fastestLengthOfLongestSubstring(t2));
		}

		/************************************************************
			Problem 2: Medium - Add Two Numbers -
			linked list addition to solve long numbers in scale
		*************************************************************/

		ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
			int current = l1->val + l2->val;
			ListNode* head = new ListNode(current % 10);
			ListNode* node = head;
			current /= 10;
			ListNode* p1 = l1->next;
			ListNode* p2 = l2->next;
			while (p1 != NULL || p2 != NULL) {
				if (p1 != NULL) {
					current += p1->val;
					p1 = p1->next;
				}
				if (p2 != NULL) {
					current += p2->val;
					p2 = p2->next;
				}
				node->next = new ListNode(current % 10);
				node = node->next;
				current /= 10;
			}
			if (current > 0) {
				node->next = new ListNode(current);
			}
			return head;
		}

		void Add_Two_Numbers_Linked_List()
		{
			LOG("Add_Two_Numbers_Linked_List");
			ListNode* node1 = new ListNode(7);
			node1->next = new ListNode(0);
			node1->next = new ListNode(3);
			ListNode* node2 = new ListNode(5);
			node2->next = new ListNode(2);
			node2->next = new ListNode(3);
			addTwoNumbers(node1, node2);
		}

		/************************************************************
			Problem 1: Easy - Two Sum
		*************************************************************/

		std::vector<int> twoSum(std::vector<int>& nums, int target) {
			std::map<int, int> umap;
			int count = 0;
			for (int& i : nums) {
				int composite = target - i;
				if (umap.find(composite) != umap.end()) {
					return { umap.at(composite), count };
				}
				else {
					umap.insert({ i, count });
				}
				count++;
			}
			return { 0, 0 };
		}

		void Two_Sum()
		{
			std::vector<int> vec = { 2, 7, 323, 23 };
			vec = twoSum(vec, 9);
			for (int& i : vec) {
				LOG(i);
			}
		}

		void ProblemSet001::Start() 
		{
			MyStringToIntegerParser();
			//RomanNumeralsConversion();
			//ConvertToZigZag();
			//LongestPalindromicSubstring();
			//Is_Number_Palindrome();
			//Reverse_Integer();
			//Longest_Substring();
			//Add_Two_Numbers_Linked_List();
			//Two_Sum();
		}
	}
}