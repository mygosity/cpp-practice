#pragma once
#include "problem-set-001.h"

namespace codechallenges
{
	namespace leetcode
	{
		using ListNode = ProblemSet001::ListNode;

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
			//Reverse_Integer();
			//Longest_Substring();
			//Add_Two_Numbers_Linked_List();
			//Two_Sum();
		}
	}
}