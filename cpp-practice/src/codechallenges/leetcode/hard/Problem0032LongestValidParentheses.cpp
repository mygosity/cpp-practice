#include "Problem0032LongestValidParentheses.h"

namespace codechallenges
{
	namespace leetcode
	{
		static stringstream debuglog;
		/**********************************************************************
		Problem 32 - Longest Valid Parentheses
		Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

		Example 1:

		Input: "(()"
		Output: 2
		Explanation: The longest valid parentheses substring is "()"
		Example 2:

		Input: ")()())"
		Output: 4
		Explanation: The longest valid parentheses substring is "()()"
		***********************************************************************/

		//long ass solution I wrote that uses constant memory cos that's totally what I was aiming for lulz.. obviously the stack solution below is way better...
		int longestValidParentheses(string s) {
			if (s.size() <= 1) {
				return 0;
			}
			if (s.size() == 2) {
				return s[0] == '(' && s[1] == ')' ? 2 : 0;
			}

			int max = 0,
				left = 0,
				right = 0,
				nl = 0,
				nr = 0,
				len = s.size();

			for (int i = 0; i < len; ++i) {
				if (s[i] == '(' && s[i + 1] == ')') {
					left = i;
					right = i + 1;
					int c = 2;

					while (left > -1 && right < len) {
						nl = left - 1;
						nr = right + 1;

						if (nl > -1 && nr < len) {
							if (s[nl] == '(' && s[nr] == ')') {
								--left;
								++right;
								continue;
							}
							else
							{
								if (s[nr] == '(') {
									int balance = 0;
									while (nr < len && s[nr] == '(' && balance == 0) {
										for (int j = nr; j < len; ++j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;
											if (balance == 0) {
												right = j;
												nr = right + 1;
												break;
											}
										}
										if (balance != 0)
											break;
									}
								}
								if (s[nl] == ')') {
									int balance = 0;
									while (nl > -1 && s[nl] == ')' && balance == 0) {
										for (int j = nl; j > -1; --j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;

											if (balance == 0) {
												left = j;
												nl = left - 1;
												break;
											}
										}
										if (balance != 0)
											break;
									}
								}

								if (s[nl] == '(') {
									if (s[nr] == '(') {
										int balance = -1;
										for (int j = nr; j < len; ++j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;
											if (balance == 0) {
												right = j;
												break;
											}
										}
										if (balance != 0)
											break;
										left = nl;
										nr = right + 1;
										nl = left - 1;
									}
								}
								else if (s[nl] == ')')
								{
									//  )()(  -> if left and right are not balanced this is max length 2
									if (s[nr] == '(') {
										break;
									}
									else {
										//search left with balance at 1
										int balance = 1;
										for (int j = nl; j > -1; --j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;
											if (balance == 0) {
												left = j;
												break;
											}
										}
										if (balance != 0)
											break;
										right = nr;
										nl = left - 1;
										nr = right + 1;
									}
								}
							}
						}
						else
						{
							if (nl > -1) {
								if (s[nl] == ')') {
									int balance = 0;
									while (nl > -1 && s[nl] == ')' && balance == 0) {
										for (int j = nl; j > -1; --j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;

											if (balance == 0) {
												left = j;
												nl = left - 1;
												break;
											}
										}
										if (balance != 0)
											break;
									}
								}
								break;
							}
							else if (nr < len) {
								if (s[nr] == '(') {
									int balance = 0;
									while (nr < len && s[nr] == '(' && balance == 0) {
										for (int j = nr; j < len; ++j) {
											if (s[j] == '(')
												--balance;
											else if (s[j] == ')')
												++balance;
											if (balance == 0) {
												right = j;
												nr = right + 1;
												break;
											}
										}
										if (balance != 0)
											break;
									}
								}
								break;
							}
							else {
								//only condition that should break 100% and count should already be accounted for
								break;
							}
						}
					}

					c = right - left + 1;

					if (right > i)
						i = right;

					if (c > max)
						max = c;
				}
			}
			return max;
		}

		//short public solution - way more elegant than mine ey? lol
		 int publiclongestValidParentheses(string s) {
		     stack<int> sk;
		     int index = 0;
		     int res = 0;
		     while (index < s.size()) {
		         if (s[index] == '(') {
		             sk.push(index);
		         } else if (s[index] == ')') {
		             if (!sk.empty() && s[sk.top()] == '(') {
		                 sk.pop();
		                 res = max(res, sk.empty() ? index + 1 : index - sk.top());
		             } else {
		                 sk.push(index);
		             }
		         }
		         index++;
		     }
		     return res;
		 }

		void HardProblem32::Longest_Valid_Parentheses()
		{
		}
	}
}