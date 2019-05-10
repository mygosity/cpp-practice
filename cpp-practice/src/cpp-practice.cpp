#include "common.h"
#include "codechallenges/leetcodeHub.cpp"

int main()
{
	int a[26];
	memset(a, -1, sizeof(a));
	for (int& i : a) {
		//std::cout << (i) << std::endl;
	}
	string c = "asdfsdafs";
	c.push_back('d');
	//c.clear();
	std::cout<<(c.substr(0, 2))<<std::endl;

	codechallenges::leetcode::Start();
}