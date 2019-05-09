#include "Problem4MedianSortedArray.h"

namespace codechallenges
{
	namespace leetcode
	{
		/**********************************************************************
		Problem 4 - Hard - Median of Two Sorted Arrays
		There are two sorted arrays nums1 and nums2 of size m and n respectively.
		Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
		You may assume nums1 and nums2 cannot be both empty.

		Example 1:
		nums1 = [1, 3]
		nums2 = [2]
		The median is 2.0

		Example 2:
		nums1 = [1, 2]
		nums2 = [3, 4]

		The median is (2 + 3)/2 = 2.5
		***********************************************************************/

		//binary search version - this really didn't improve performance so I don't see the point............ 
		//and it's quite possibly the grossest function I've written
		double findBSMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
			// std::cout << "size1: " << nums1.size() << " size2: " << nums2.size() << std::endl;
			if (nums2.empty() || nums1.empty()) {
				vector<int>& vec = nums2.empty() ? nums1 : nums2;
				bool oneAnswer = vec.size() % 2 != 0;
				double median = vec.size() / 2.0;
				int index = (int)median;
				if (oneAnswer) {
					return vec[index];
				}
				else {
					return (vec[index] + vec[index - 1]) / 2.0;
				}
			}
			vector<int>& vec1 = nums1[0] < nums2[0] ? nums1 : nums2;
			vector<int>& vec2 = nums1[0] < nums2[0] ? nums2 : nums1;
			int len1 = vec1.size();
			int len2 = vec2.size();
			int f1 = vec1[0];
			int f2 = vec2[0];
			int l1 = vec1[len1 - 1];
			int l2 = vec2[len2 - 1];
			double median = (len1 + len2) / 2.0;
			int index = (int)median;
			bool oneAnswer = (len1 + len2) % 2 != 0;
			//handle easy edge cases
			if (l1 <= f2) {
				if (index < len1) {
					if (oneAnswer) {
						return vec1[index];
					}
					return (vec1[index] + vec1[index - 1]) / 2.0;
				}
				else {
					if (oneAnswer) {
						return vec2[index - len1];
					}
					else {
						int prev = index - 1 < len1 ? vec1[index - 1] : vec2[index - 1 - len1];
						return (vec2[index - len1] + prev) / 2.0;
					}
				}
			}
			else
			{
				//handle easy median case where the index lies inside one vector and other vector starts well after the index value
				if (index < len1 && f2 >= vec1[index]) {
					if (oneAnswer) {
						return vec1[index];
					}
					else {
						return (vec1[index] + vec1[index - 1]) / 2.0;
					}
				}
				if (index < len2 && f1 >= vec2[index]) {
					if (oneAnswer) {
						return vec2[index];
					}
					else {
						return (vec2[index] + vec2[index - 1]) / 2.0;
					}
				}

				//handle size1 edge cases
				if (len1 == 1 || len2 == 1) {
					vector<int>& shortest = nums1.size() <= nums2.size() ? nums1 : nums2;
					vector<int>& longest = nums1.size() <= nums2.size() ? nums2 : nums1;
					if (oneAnswer) {
						int index = (longest.size() + 1) / 2;
						std::cout << index << std::endl;
						int x = longest[index];
						int y = shortest[0];
						if (y < x) {
							if (y < longest[index - 1]) {
								return longest[index - 1];
							}
							else {
								return y;
							}
						}
						return x;
					}
					else
					{
						int middle = longest.size() / 2;
						int x = longest[middle];
						int y = shortest[0];
						if (longest[middle + 1] < y) {
							return (x + longest[middle + 1]) / 2.0;
						}
						if (longest[middle - 1] > y) {
							return (x + longest[middle - 1]) / 2.0;
						}
						return (x + y) / 2.0;
					}
				}
				else
				{
					int totalParts = len1 + len2;
					int leftParts = (totalParts / 2) + 1;
					int left1 = len1 / 2;
					int left2 = (leftParts - 1) - (left1 + 1);
					//handle the case where the index is at one limit
					if (left1 == len1 - 1) {
						if (vec1[left1] > vec2[left2 + 1]) {
							left1--;
							left2++;
						}
					}
					else if (left2 == len2 - 1) {
						if (vec2[left2] > vec1[left1 + 1]) {
							left2--;
							left1++;
						}
					}
					//LOG("totalParts: " << totalParts << " leftParts: " << leftParts);
					//LOG("left1: " << left1 << " left2: " << left2 << " len1: " << len1 << " len2: " << len2);
					//utils::PrintVector(vec1, "vec1: ");
					//utils::PrintVector(vec2, "vec2: ");
					if (!(left2 + 1 >= len2 || left1 + 1 >= len1)) {
						//no limits reached -- move the pointers into the right location
						while (!((left2 + 1 >= len2 || vec1[left1] <= vec2[left2 + 1]) && (left1 + 1 >= len1 || vec2[left2] <= vec1[left1 + 1]))) {
							if (vec2[left2] > vec1[left1 + 1]) {
								left2 = left2 - 1 >= 0 ? left2 - 1 : left2;
								left1++;
							}
							else if (vec1[left1] > vec2[left2 + 1]) {
								left1 = left1 - 1 >= 0 ? left1 - 1 : left1;
								left2++;
							}
						}
					}
					if (oneAnswer) {
						return vec1[left1] >= vec2[left2] ? vec1[left1] : vec2[left2];
					}
					else
					{
						if (vec1[left1] >= vec2[left2]) {
							int x = vec1[left1];
							int y = vec2[left2];
							if (left1 - 1 >= 0) {
								if (y < vec1[left1 - 1]) {
									return (x + vec1[left1 - 1]) / 2.0;
								}
							}
							return (x + y) / 2.0;
						}
						int x = vec2[left2];
						int y = vec1[left1];
						if (left2 - 1 >= 0) {
							if (y < vec2[left2 - 1]) {
								return (x + vec2[left2 - 1]) / 2.0;
							}
						}
						return (x + y) / 2.0;
					}
				}

			}
			return median;
		}

		//doesn't solve in log (m_n) time - need to use binary search
		double findMedianSortedArrays(vector<int> & nums1, vector<int> & nums2) {
			// std::cout << "size1: " << nums1.size() << " size2: " << nums2.size() << std::endl;
			if (nums2.empty() || nums1.empty()) {
				vector<int>& vec = nums2.empty() ? nums1 : nums2;
				bool oneAnswer = vec.size() % 2 != 0;
				double median = vec.size() / 2.0;
				int index = (int)median;
				if (oneAnswer) {
					return vec[index];
				}
				else {
					return (vec[index] + vec[index - 1]) / 2.0;
				}
			}
			vector<int>& vec1 = nums1[0] < nums2[0] ? nums1 : nums2;
			vector<int>& vec2 = nums1[0] < nums2[0] ? nums2 : nums1;
			int len1 = vec1.size();
			int len2 = vec2.size();
			int f1 = vec1[0];
			int f2 = vec2[0];
			int l1 = vec1[len1 - 1];
			int l2 = vec2[len2 - 1];
			double median = (len1 + len2) / 2.0;
			int index = (int)median;

			bool oneAnswer = (len1 + len2) % 2 != 0;
			// std::cout << "oneAnswer: " << oneAnswer << " len1: " << len1 << " len2: " << len2 << " mod:" << ((len1 + len2) % 2) << std::endl;
			//using the median index, can return straight from first array if the first array is enough to get a median return
			if (l1 <= f2) {
				if (index < len1) {
					if (oneAnswer) {
						return vec1[index];
					}
					return (vec1[index] + vec1[index - 1]) / 2.0;
				}
				else {
					if (oneAnswer) {
						return vec2[index - len1];
					}
					else {
						int prev = index - 1 < len1 ? vec1[index - 1] : vec2[index - 1 - len1];
						return (vec2[index - len1] + prev) / 2.0;
					}
				}
			}
			else {
				//worst case scenario, have to iterate and insert weave til midpoint
				int i1 = 0;
				int i2 = 0;
				int c1 = vec1[i1++];
				int c2 = vec2[i2++];
				if (i1 + 1 < len1 && vec1[i1] < c2) {
					c2 = vec1[i1++];
					i2 = 0;
				}
				for (int i = 1; i < index + 1; ++i) {
					if (i >= index) {
						if (oneAnswer) {
							return c2;
						}
						else {
							return (c1 + c2) / 2.0;
						}
					}
					c1 = c2;
					if (i1 >= len1) {
						c2 = vec2[i2++];
					}
					else if (i2 >= len2) {
						c2 = vec1[i1++];
					}
					else
					{
						c2 = vec1[i1] <= vec2[i2] ? vec1[i1++] : vec2[i2++];
					}
				}
			}
			return median;
		}

		void HardProblem4::Median_Two_Sorted_Arrays()
		{
			vector<int> vec1 = { 1, 3, 8, 9, 15 };
			vector<int> vec2 = { 7, 11, 19, 21, 22, 23 };
			LOG("{ 1, 3, 8, 9, 15 }, { 7, 11, 19, 21, 22, 23 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec1, vec2));
			LOG("binary answer: " << findBSMedianSortedArrays(vec1, vec2));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec3 = { 1, 3 };
			vector<int> vec4 = { 2, 11 };
			LOG("{ 1, 3 }, { 2, 11 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec3, vec4));
			LOG("binary answer: " << findBSMedianSortedArrays(vec3, vec4));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec5 = { 2 };
			vector<int> vec6 = { 1, 3, 4 };
			LOG("{ 2 }, { 1, 3, 4 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec5, vec6));
			LOG("binary answer: " << findBSMedianSortedArrays(vec5, vec6));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec7 = { 1, 2 };
			vector<int> vec8 = { -1, 3 };
			LOG("{ 1, 2 }, { -1, 3 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec7, vec8));
			LOG("binary answer: " << findBSMedianSortedArrays(vec7, vec8));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec9 = { 1, 3 };
			vector<int> vec10 = { 2 };
			LOG("{ 1, 3 }, { 2 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec9, vec10));
			LOG("binary answer: " << findBSMedianSortedArrays(vec9, vec10));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec11 = { 1, 2 };
			vector<int> vec12 = { 1, 2, 3 };
			LOG("{ 1, 2 }, { 1, 2, 3 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec11, vec12));
			LOG("binary answer: " << findBSMedianSortedArrays(vec11, vec12));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec13 = { 5, 6 };
			vector<int> vec14 = { 1, 2, 3, 4, 7 };
			LOG("{ 5, 6 }, { 1, 2, 3, 4, 7 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec13, vec14));
			LOG("binary answer: " << findBSMedianSortedArrays(vec13, vec14));
			LOG("*********************************************************");
			LOG("");
			vector<int> vec15 = { 5 };
			vector<int> vec16 = { 1, 2, 3, 4, 6 };
			LOG("{ 5 }, { 1, 2, 3, 4, 6 } ");
			LOG("brute answer: " << findMedianSortedArrays(vec15, vec16));
			LOG("binary answer: " << findBSMedianSortedArrays(vec15, vec16));
			LOG("*********************************************************");
			LOG("");
		}
	}
}