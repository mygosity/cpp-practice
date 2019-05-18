#include "Problem0010RegularExpressionMatching.h"

namespace codechallenges
{
	namespace leetcode
	{
		static stringstream debuglog;
		/**********************************************************************
		Problem 10 - Hard - Regular Expression Matching
		Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
		'.' Matches any single character.
		'*' Matches zero or more of the preceding element.
		The matching should cover the entire input string (not partial).
		Note:
		s could be empty and contains only lowercase letters a-z.
		p could be empty and contains only lowercase letters a-z, and characters like . or *.
		***********************************************************************/
		int IndexOf(string& x, char c) {
			int len = x.size();
			for (int i = 0; i < len; ++i) {
				if (x[i] == c) {
					return i;
				}
			}
			return -1;
		}
		
		int IndexOf(string& x, string& y) {
			int len = x.size(), len2 = y.size(), j = 0;
			for (int i = 0; i < len; ++i) {
				if (len2 > len - i) {
					return -1;
				}
				j = 0;
				if (x[i] == y[j]) {
					int foundIndex = i++;
					for (j = 1; j < len2; ++j) {
						if (x[i] != y[j]) {
							foundIndex = -1;
							--i;
							break;
						}
						++i;
					}
					if (foundIndex > -1) {
						return foundIndex;
					}
				}
			}
			return -1;
		}

		vector<int>* IndexesOf(string& x, char& y) {
			vector<int>* a = new vector<int>();
			int currentIndex = 0;
			string temp = x;
			while (temp.size() >= 1) {
				int index = IndexOf(temp, y);
				if (index > -1) {
					a->push_back(currentIndex + index);
					temp = temp.substr(index + 1);
					currentIndex += index + 1;
				}
				else
				{
					break;
				}
			}
			return a;
		}

		vector<int>* IndexesOf(string& x, string& y) {
			vector<int>* a = new vector<int>();
			int ylen = y.size();
			int currentIndex = 0;
			string temp = x;
			while (temp.size() >= ylen) {
				int index = IndexOf(temp, y);
				if (index > -1) {
					a->push_back(currentIndex + index);
					temp = temp.substr(index + ylen);
					currentIndex += index + ylen;
				}
				else
				{
					break;
				}
			}
			return a;
		}

		bool StringEquals(string& x, string& y) 
		{
			int len = x.size(), len2 = y.size(), j = 0;
			if (len != len2)
				return 0;
			for (int i = 0; i < len; ++i) {
				if (y[i] != x[i]) {
					return 0;
				}
			}
			return 1;
		}

		bool isMatch213(string s, string p) {
			if (p.size() == 2) {
				if (p[0] == '.' && p[1] == '*') {
					return true;
				}
			}
			if (s.size() == 0 && p.size() == 2) {
				if (p[1] == '*') {
					return true;
				}
			}
			if (s.size() > 0 && p.size() == 0) {
				return false;
			}
			if (p.size() == 1 && p[0] != '*' && s.size() == 0)
				return false;
			if (p.size() == 0 && s.size() == 0)
				return true;
			//LOG("s: " << s);

			int len = s.size();
			int plen = p.size();
			int ptr = 0;
			for (int i = 0; i < plen; ++i) {
				char c = p[i];
				char nc = i + 1 < plen ? p[i + 1] : ' ';
				if (c == '*') {
					continue;
				}
				//LOG("ptr: " << ptr << " s[ptr]: " << s[ptr] << " c: " << c);
				if (ptr >= len) {
					//LOG("early return ");
					//validate remainder of the pattern as optionals
					int minLen = 0;
					for (int k = i; k < plen; ++k) {
						char current = p[k];
						if (current != '*') {
							if (k + 1 < plen) {
								if (p[k + 1] != '*') {
									minLen++;
									k++;
								}
							}
							else {
								minLen++;
							}
						}
					}
					//LOG("early return:: minLen: " << minLen);
					return minLen == 0;
				}
				if (c == '.') {
					if (nc == '*') {
						if (i + 2 < plen) {
							int minLen = 0;
							bool optionals = false;
							for (int k = i + 2; k < plen; ++k) {
								char current = p[k];
								if (current != '*') {
									if ((k + 1 < plen && p[k + 1] != '*') || k + 1 >= plen) {
										minLen++;
									}
								}
								else {
									optionals = true;
								}
							}
							//LOG(" minLen: "<< minLen << " ptr: " << ptr);
							if (optionals) {
								char stopTilChar = p[i + 2];
								if (stopTilChar != '.') {
									//LOG("ptr: " << ptr << " s[ptr]: " << s[ptr] << " stopTilChar: " << stopTilChar);
									while (ptr + minLen < len) {
										if (s[ptr] == stopTilChar) {
											break;
										}
										ptr++;
									}
									//LOG("ptr: " << ptr << " s[ptr]: " << s[ptr] << " p[i]: " << p[i]);
									if (ptr >= len) {
										//LOG("pointer exceeded string limit");
										return false;
									}
								}
							}
							else {
								ptr = len - minLen;
								if (minLen > len) {
									return false;
								}
							}
						}
						else {
							return true;
						}
					}
					else {
						ptr++;
					}
					//LOG("ptr: " << ptr << " p[i]: " << p[i]);
					continue;
				}
				//handle non asterix chars
				if (nc != '*') {
					//LOG("ptr: " << ptr << " s[ptr]: " << s[ptr] << " c: " << c);
					if (c != '.') {
						//std::cout << "handle non asterix chars -> ptr: " << ptr << " s[ptr]: " << s[ptr] << " c: " << c << std::endl;
						if (s[ptr++] != c) {
							return false;
						}
					}
					else {
						ptr++;
					}
				}
				//push the pointer forwards til the next valid point
				else {
					if (nc == '*') {
						if (i + 2 < plen) {
							//while loop and find the next non optional character
							int nextNonOptionIndex = i + 2;
							vector<char> checks = { p[i] };
							for (int k = nextNonOptionIndex; k < plen; k+=2) {
								if (k + 1 < plen) {
									if (p[k + 1] != '*') {
										break;
									}
									else {
										checks.push_back(p[k]);
									}
								}
								nextNonOptionIndex = k;
							}
							int minLen = 0;
							for (int k = nextNonOptionIndex; k < plen; ++k) {
								char current = p[k];
								if (current != '*') {
									if ((k + 1 < plen && p[k + 1] != '*') || k + 1 >= plen) {
										minLen++;
									}
								}
							}
							//LOG("nextNonOptionIndex: " << nextNonOptionIndex << " p[nextNonOptionIndex]: " << p[nextNonOptionIndex] << " minLen: "<< minLen << " ptr: " << ptr);
							if (minLen > len - ptr) {
								//LOG("not enough chrs to solve::");
								return false;
							}
							//crispyskies::utils::PrintVector(checks);
							char stopTilChar = p[nextNonOptionIndex];
							for (int k = 0; k < checks.size(); ++k) {
								char compare = checks[k];
								while (ptr + minLen < len) {
									char currentCharacter = s[ptr];
									if (compare != currentCharacter && compare != '.') {
										break;
									}
									ptr++;
								}
							}
							i = nextNonOptionIndex - 1;
							//LOG("s: " << s << " ptr: " << ptr << " s[ptr]: " << s[ptr] << " stopTilChar: " << stopTilChar << " c: " << c);
						}
						else {
							while (ptr < len) {
								if (s[ptr] != c) {
									break;
								}
								ptr++;
							}
						}
					}
				}
				//LOG("ptr: " << ptr << " p[i]: " << p[i] << " len: " << len);
			}
			//LOG("finally::ptr: " << ptr << " len: " << len);
			return ptr == len;
		}

		bool isMatch2(string s, string p) {
			int len = s.size();
			int plen = p.size();

			if (plen == 0) {
				return len == 0;
			}
			debuglog << "isMatch2:: (" << s << ", " << p << ")\n";
			//calc the minimum length that the answer must be
			vector<char> staticChars = {};
			int minLen = 0;
			for (int i = 0; i < plen; ++i) {
				char c = p[i];
				char nc = i + 1 < plen ? p[i + 1] : ' ';
				if (nc == '*') {
					i++;
				}
				else {
					minLen++;
					staticChars.push_back(c);
				}
			}
			if (minLen > len) {
				debuglog << "minLen > len returning false:: minLen: " << minLen << ", len: " << len << "\n";
				return false;
			}

			debuglog << "staticChars: { ";
			for (int i = 0; i < staticChars.size(); ++i) {
				debuglog << staticChars[i];
				if (i < staticChars.size() - 1) {
					debuglog << ", ";
				}
			}
			debuglog << " }\n";

			//.* and any chr combinations and .* means we can have anything in front / end and have this exact combo somewhere inside
			//lets group up infinite sets

			//loop backwrds through infinite sets and find the required length
			//.*a*aa*.*b*.c*.*a*
			/*int ptr = len - 1;
			vector<char> list;
			bool wildcard = false;
			for (int i = plen - 1; i > -1; --i) {
				char c = p[i];
				if (c == '*') {
					char n = p[--i];
					if (n != '.') {
						list.push_back(n);
					}
					else {
						wildcard = true;
					}
					continue;
				}
				else {

				}
			}*/

			debuglog 
				<< "FINAL_STATE\n"
				//<< "	ptr: " << ptr << "\n"
				<< "	minLen: " << minLen << ", len: " << len << "\n"
			;
			return true;
		}

		int getMinimumChrs(string& s, string& p) {
			int len = s.size();
			int plen = p.size();
			int minLen = 0;
			for (int i = 0; i < plen; ++i) {
				char c = p[i];
				char nc = i + 1 < plen ? p[i + 1] : ' ';
				if (nc == '*') {
					i++;
				}
				else {
					minLen++;
				}
			}
			return minLen;
		}

		bool matchEraseRegularChars(string& s, string& p) {
			int p_ptr = 0;
			int s_ptr = 0;
			int plen = p.size();
			for (int i = 0; i < plen; ++i) {
				char c = p[i];
				char nc = i + 1 < plen ? p[i + 1] : ' ';
				if (nc == '*') {
					//substr the s and remove the ps used
					s = s.substr(s_ptr);
					p = p.substr(p_ptr);
					return true;
				}
				else {
					if (c == '.' || c == s[s_ptr]) {
						p_ptr++;
						s_ptr++;
					}
					else {
						return false;
					}
				}
			}
			s = s_ptr < s.size() ? s.substr(s_ptr) : "";
			p = "";
			if (s.size() > 0) {
				if (p.size() == 0) {
					return false;
				}
			}
			return true;
		}

		//vector<string> matchWildSets(string& s, string& p, int i, vector<int> anyWildIndexes, vector<string> operations) {
		vector<string> matchWildSets(string& s, string& p) {
			return {};
		}

		//vector<string> matchAnyWildSets(string& s, string& p, int i, vector<int> anyWildIndexes, vector<string> operations) {
		vector<string> matchAnyWildSets(string& s, string& p) {
			return {};
		}

		void summarizeAnyCharSets(string& s, string& p) {
			bool foundWild = false;
			bool foundAnyWild = false;
			int i = 0, wildStart = 0;
			string temp = "";
			for (; i < p.size(); ++i) {
				char c = p[i];
				char nc = i + 1 < p.size() ? p[i + 1] : ' ';
				if (c == '*') {
					continue;
				}
				if (nc == '*') {
					if (!foundWild) {
						wildStart = i;
						foundWild = true;
					}
					if (c == '.') {
						foundAnyWild = true;
					}
				}
				else {
					if (foundAnyWild && foundWild) {
						//debuglog << "foundAnyWild && foundWild:: temp: " << temp << "\n";
						int cutLen = (i - wildStart);
						temp += ".*";
						p = temp + p.substr(i);
						i = temp.size();
						//debuglog << "foundAnyWild && foundWild:: i: " << i << " wildStart: " << wildStart << " (i - wildStart): " << (i - wildStart) << " p.substr(i): " << p.substr(i) << "\n";
						//debuglog << "foundAnyWild && foundWild:: p: " << p << "\n";
					}
					foundAnyWild = false;
					foundWild = false;
					if (nc != '*') {
						temp.push_back(c);
						//debuglog << "push back (c) :" << c << " i: " << i << "\n";
					}
				}
			}
			if (foundAnyWild && foundWild) {
				//debuglog << "foundAnyWild && foundWild:: temp: " << temp << "\n";
				p = temp + ".*" + p.substr(i);
				//debuglog << "foundAnyWild && foundWild:: wildStart: " << (wildStart) << "\n";
			}
		}

		bool isMatch3(string s, string p) {
			int len = s.size();
			int plen = p.size();
			debuglog << "isMatch2:: (" << s << ", " << p << ")\n";

			if (plen == 0) {
				return len == 0;
			}

			//loop thru and simplify -> so if there's simple chrs just wipe them off from the front
			bool canMatchRegular = matchEraseRegularChars(s, p);
			if (!canMatchRegular) {
				return false;
			}
			bool foundWild = false;
			bool foundAnyWild = false;
			vector<string> operations;
			//wild sets create zones of text that can be matched in small subsections
			vector<int> anyWildSets;
			string wildTemp = "";
			string regTemp = "";
			for (int i = 0, plen = p.size(), len = s.size(); i < plen; ++i) {
				char c = p[i];
				char nc = i + 1 < plen ? p[i + 1] : ' ';
				if (c == '*') {
					continue;
				}
				if (nc == '*') {
					if (!foundWild) {
						if (regTemp.size() > 0) {
							operations.push_back(regTemp);
							regTemp = "";
						}
					}
					foundWild = true;
					if (c == '.') {
						foundAnyWild = true;
					}
					else {
						wildTemp.push_back(c);
					}
				}
				else {
					if (foundWild) {
						if (foundAnyWild) {
							anyWildSets.push_back(operations.size());
							operations.push_back("*");
						}
						else {
							operations.push_back("$" + wildTemp);
						}
						foundWild = false;
						foundAnyWild = false;
						wildTemp = "";
					}
					regTemp.push_back(c);
				}
			}
			if (foundWild) {
				if (foundAnyWild) {
					anyWildSets.push_back(operations.size());
					operations.push_back("*");
				}
				else {
					operations.push_back("$" + wildTemp);
				}
			}
			else {
				if (regTemp.size() > 0) {
					operations.push_back(regTemp);
				}
			}

			int minLen = getMinimumChrs(s, p);
			int maxLen = len;
			if (minLen > len) {
				debuglog << "minLen > len returning false:: minLen: " << minLen << ", len: " << len << "\n";
				return false;
			}
			vector<string> possibilities = {s};
			for (int i = 0; i < operations.size(); ++i) {
				bool matchverified = false;
				vector<string> tempList;
				for (int k = 0; k < possibilities.size(); ++k) {
					string& current = possibilities[k];
					switch (operations[i][0]) {
						case '*': {
							vector<string> answers = matchAnyWildSets(current, p);
							for (int u = 0; u < answers.size(); ++u) {
								tempList.push_back(answers[i]);
							}
							//MIKE TAG THE CURRENT FOR DELETION OR ALTERATION IN THE FUNCTION?
							break;
						}
						case '$': {
							vector<string> answers = matchWildSets(current, p);
							for (int u = 0; u < answers.size(); ++u) {
								tempList.push_back(answers[i]);
							}
							//MIKE TAG THE CURRENT FOR DELETION OR ALTERATION IN THE FUNCTION?
							break;
						}
						default: {
							matchverified = matchEraseRegularChars(current, p);
						}
					}
				}
				if (!matchverified) {
					debuglog << "!matchverified: returning early";
					return false;
				}
				int maxChars = 0;
				bool staticCharsOnly = true;
				for (int j = i + 1; j < operations.size(); ++j) {
					if (operations[j][0] == '*' || operations[j][0] == '$') {
						staticCharsOnly = false;
					}
				}
				if (staticCharsOnly) {
					maxLen = getMinimumChrs(s, p);
					debuglog << " maxLen set: " << maxLen << " getMinimumChrs: " << getMinimumChrs(s, p)<< "\n";
				}
				if (s.size() > maxLen || s.size() < minLen) {
					debuglog << "size: " << s.size() << " maxLen: " << maxLen << " minLen: " << minLen << "\n";
					return false;
				}
			}

			debuglog << "operations: { ";
			for (int i = 0; i < operations.size(); ++i)
			{
				debuglog << operations[i];
				if (i != operations.size() - 1) {
					debuglog << ", ";
				}
			}
			debuglog << " }\n";

			debuglog
				<< "FINAL_STATE\n"
				<< "	s: " << s << " p: " << p << "\n"
				//<< "	ptr: " << ptr << "\n"
				//<< "	minLen: " << minLen << ", len: " << len << "\n"
				;
			return true;
		}

		//FINALLY SOLVED IT AND THIS SOLUTION IS SO MUCH CLEANER TEH JOY***
		bool isMatch(string s, string p) {
			debuglog << "	bestIsMatch:: (" << s << ", " << p << ")\n";
			if (p.empty()) {
				return s.empty();
			}
			int s_ptr = 0;
			for (int i = 0; i < p.size(); ++i) {
				char c = p[i];
				char nc = i + 1 < p.size() ? p[i + 1] : ' ';
				if (c == '*') {
					continue;
				}
				if (nc != '*') {
					//ran out of string vs pointer moving through the string
					if (s_ptr >= s.size()) {
						debuglog << "s_ptr >= s.size() : returning false | s_ptr: " << s_ptr << " s.size(): " << s.size() << " c: " << c << " i: " << i << "\n";
						return false;
					}
					//static character mismatch returns false
					if (s[s_ptr] != c && c != '.') {
						debuglog << "s[s_ptr] != c && s[s_ptr] != '.' : returning false | s[s_ptr]: " << s[s_ptr] << " c: " << c << "\n";
						return false;
					}
					s_ptr++;
				}
				else
				{
					if (s.size() > 0 && s_ptr < s.size()) {
						string remainingP = i + 2 < p.size() ? p.substr(i + 2) : "";
						string nextString = s.substr(s_ptr);
						bool foundMatch = isMatch(nextString, remainingP);
						debuglog << "recursive loop c: " << c << " remainingP: " << remainingP << "\n";
						for (s_ptr; s_ptr < s.size(); ++s_ptr) {
							if (c != '.' && s[s_ptr] != c) {
								debuglog << "breaking recursive loop c: " << c << " s[s_ptr]: " << s[s_ptr] << "\n";
								break;
							}
							if (c == '.' || s[s_ptr] == c) {
								nextString = s_ptr + 1 < s.size() ? s.substr(s_ptr + 1) : "";
								foundMatch = foundMatch || isMatch(nextString, remainingP);
								debuglog << "recursive looping c: " << c << " s[s_ptr]: " << s[s_ptr] << " nextString: " << nextString << " remainingP: " << remainingP << " foundMatch: " << foundMatch << "\n";
							}
						}
						return foundMatch;
					}
				}
			}
			debuglog << " s_ptr: " << s_ptr << "\n";
			return s_ptr >= s.size();
		}

		bool publicSolution4msisMatch(string s, string p) {
			stack<pair<int, int>> positions;
			vector<vector<bool>> seen(s.size() + 5, vector<bool>(p.size() + 5, false));

			positions.push(make_pair(0, 0));

			while (!positions.empty()) {
				pair<int, int> indexes = positions.top();
				positions.pop();

				if (seen.at(indexes.first).at(indexes.second)) {
					continue;
				}

				seen.at(indexes.first).at(indexes.second) = true;

				bool isNextAStar = indexes.second + 1 < p.size() && p.at(indexes.second + 1) == '*';

				if (isNextAStar) {
					positions.push(make_pair(indexes.first, indexes.second + 2));
				}

				if (indexes.first >= s.size() || indexes.second >= p.size()) {
					if (indexes.first >= s.size() && indexes.second >= p.size()) {
						return true;
					}
					continue;
				}

				// if there is not a match
				if (p.at(indexes.second) != '.' && s.at(indexes.first) != p.at(indexes.second)) {
					continue;
				}

				// there was a match, move one
				indexes.first++;

				if (isNextAStar) {
					positions.push(indexes);
					positions.push(make_pair(indexes.first, indexes.second + 2));
				}
				else {
					positions.push(make_pair(indexes.first, indexes.second + 1));
				}
			}
			return false;
		}

		//bool publicSolution4msisMatch(string s, string p) {
		//	if (s.empty() && p.empty()) return true;

		//	const int len_s = s.size();
		//	const int len_p = p.size();
		//	bool dp[len_s + 1][len_p + 1];

		//	char last;
		//	for (int i = 0; i <= len_s; i++) {
		//		last = 0;
		//		dp[i][0] = (i == 0);
		//		for (int j = 1; j <= len_p; j++) {
		//			dp[i][j] = false;
		//			// match xy => xy or x.
		//			if (i >= 1 && dp[i - 1][j - 1] && (p[j - 1] == '.' || s[i - 1] == p[j - 1])) {
		//				dp[i][j] = true;
		//			}
		//			if (p[j - 1] != '*') {
		//				last = p[j - 1];
		//			}
		//			else {
		//				// match x => x*
		//				if (dp[i][j - 1]) dp[i][j] = true;
		//				// match xx => x*
		//				// match xxx => x*, xxxx => x*
		//				else if (i >= 1
		//					&& (dp[i - 1][j - 1] || dp[i - 1][j])
		//					&& (last == '.' || last == s[i - 1]))
		//					dp[i][j] = true;
		//				// match '' => x*
		//				else if (j >= 2 && dp[i][j - 2]) dp[i][j] = true;
		//			}
		//			//          cout << i << "," << j << "==>" << dp[i][j] << endl;
		//		}
		//	}

		//	return dp[len_s][len_p];
		//}

		/*bool publicSolution0msisMatch(string s, string p) {
			unsigned int m = s.size();
			unsigned int n = p.size();

			bool b[m + 1][n + 1];
			b[0][0] = true;

			for (int i = 1; i <= m; ++i) {
				b[i][0] = false;
			}

			for (int j = 1; j <= n; ++j) {
				if (j > 1 && p[j - 1] == '*' && b[0][j - 2]) {
					b[0][j] = true;
				}
				else {
					b[0][j] = false;
				}
			}

			for (int i = 1; i <= m; ++i) {
				for (int j = 1; j <= n; ++j) {
					if (p[j - 1] != '*') {
						b[i][j] = b[i - 1][j - 1] && (p[j - 1] == '.' || s[i - 1] == p[j - 1]);
					}
					else {
						b[i][j] = (j > 1 && b[i][j - 2]) ||
							b[i][j - 1] ||
							(b[i - 1][j] && j > 1 && ('.' == p[j - 2] || s[i - 1] == p[j - 2]));
					}
				}
			}

			return b[m][n];
		}*/

		void HardProblem10::Regular_Expression_Matching()
		{
			string aaa = "0123456";
			//LOG(aaa.substr(2));
			using matcher = bool (*)(string, string);
			matcher matchingFunction = &isMatch;
			map<string, matcher> delegators = {
				//{ "isMatch::", &isMatch },
				//{ "isMatch2::", &isMatch2 },
				//{ "isMatch3::", &isMatch3 },
				{ "isMatch::", &isMatch },
			};

			map<vector<string>, bool> tests = {
				{ {"", ""}, 1 },
				{ {"aa", "a"}, 0 },
				{ {"aa", "a*"}, 1 },
				{ {"aaasdsadasdasasdasd", "a*.*aaasd.*l*a*"}, 1 },
				{ {"aa", ".*"}, 1 },
				{ {"aab", "c*a*b"}, 1 },
				{ {"miiiiiiiis", "mi*s"}, 1 },
				{ {"mississippi", "mis*is*p*."}, 0 },
				{ {"ab", ".*"}, 1 },
				{ {"ab", ".*b"}, 1 },
				{ {"aaa", "aaaa"}, 0 },
				{ {"aaa", "a*a"}, 1 },
				{ {"aaa", "ab*a*c*a"}, 1 },
				{ {"aaa", "ab*a*c*aa"}, 1 },
				{ {"aaa", "ab*a*c*aaaaaaaa"}, 0 },
				{ {"aaba", "ab*a*c*a"}, 0 },
				{ {"ab", ".*.."}, 1 },
				{ {"a", ".*..a*"}, 0 },
				{ {"a", "a."}, 0 },
				{ {"a", "ab*"}, 1 },
				{ {"abcdede", "ab.*de"}, 1 },
				{ {"a", ".*.."}, 0 },
				//{ {"aabcbcbcaccbcaabc", ".*a*aa*.*b*.c*.*a*"}, 1 },
				{ {"", ""}, 1 }
			};
			//debuglog.clear();
			int count = 0;
			for (auto it = tests.begin(); it != tests.end(); it++, count++)
			{
				auto currentTest = it->first;
				auto correctAnswer = it->second;
				for (auto func = delegators.begin(); func != delegators.end(); func++) {
					debuglog.str(string());
					auto funcName = func->first;
					auto matchFunc = func->second;
					bool yourAnswer = matchFunc(currentTest[0], currentTest[1]);

					/*if (count != 0 && count != tests.size()) {
						LOG("****************************************************************************************************");
						LOG("" << yourAnswer << " vs " << correctAnswer);
						LOG(debuglog.str());
						LOG("****************************************************************************************************");
						LOG("");
					}*/
					if (yourAnswer != correctAnswer) {
						LOG("****************************************************************************************************");
						LOG("failed unit test");
						LOG("" << yourAnswer << " vs " << correctAnswer);
						//LOG("" << funcName << "(" << currentTest[0] << ", " << currentTest[1] << ")\nanswer: " << correctAnswer);
						LOG(debuglog.str());
						LOG("****************************************************************************************************");
						return;
					}
				}
			}
		}
	}
}