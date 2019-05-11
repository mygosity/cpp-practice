#pragma once
#include "problem-set-001.h"

namespace codechallenges
{
	namespace leetcode
	{
		using ListNode = ProblemSet001::ListNode;

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
			LongestPalindromicSubstring();
			/*string s = "babad";
			int middle = (s.size() - 0.5) / 2;
			string a(s, middle, 1);
			LOG(a);*/
			//Is_Number_Palindrome();
			//Reverse_Integer();
			//Longest_Substring();
			//Add_Two_Numbers_Linked_List();
			//Two_Sum();
		}
	}
}