#pragma once
#include "../../common.h"

namespace codechallenges
{
	namespace leetcode
	{
		class ProblemSet001 {
		public:
			struct ListNode {
				int val;
				ListNode* next;
				ListNode(int x) : val(x), next(NULL) {}
			};

			static void Two_Sum();
			static void Add_Two_Numbers_Linked_List();
			static void Longest_Substring();
		};
		
	}
}