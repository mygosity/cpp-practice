#pragma once
#include "leetcode/problem-set-001.h"
#include "leetcode/hard/Problem0004MedianSortedArray.h"
#include "leetcode/hard/Problem0010RegularExpressionMatching.h"

namespace codechallenges
{
	namespace leetcode
	{
		static void Start()
		{
			ProblemSet001::Start();
			//HardProblem4::Median_Two_Sorted_Arrays();
			HardProblem10::Regular_Expression_Matching();
		}
	}
}