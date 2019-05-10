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

			static void Start();
		};
	}
}