#pragma once
#include "../common.h"

//these are totally unncessary but leaving them here as reminders anyway
namespace crispyskies
{
	namespace utils
	{
		using namespace std;
		//https://www.systutorials.com/131/convert-string-to-int-and-reverse/
		//to string conversion method 1:
		//std::string ToString(int i) {
		//	std::string out_string;
		//	std::stringstream ss;
		//	ss << i;
		//	return ss.str();
		//}

		//https://www.systutorials.com/131/convert-string-to-int-and-reverse/
		//to string conversion method 2:
		template <typename T>
		static string ToString(T i) {
			string str = to_string(i);
			return str;
		}

		static int ParseStringToInt(std::string i) {
			return std::stoi(i);
		}
		
		static void DebugLog(const char* msg)
		{
			std::cout << msg << std::endl;
		}

		static void DebugLog(std::string msg)
		{
			std::cout << msg << std::endl;
		}

		static void PrintVector(vector<int> vec, string optionalPrepend = "") {
			string s = optionalPrepend + "{ ";
			for (int i = 0; i < vec.size(); ++i) {
				s.append(std::to_string(vec[i]));
				if (i < vec.size() - 1) {
					s.append(", ");
				}
			}
			std::cout << s << " }" << std::endl;
		}

		static void PrintVector(vector<string> vec, string optionalPrepend = "") {
			string s = optionalPrepend + "{ ";
			for (int i = 0; i < vec.size(); ++i) {
				s.append(vec[i]);
				if (i < vec.size() - 1) {
					s.append(", ");
				}
			}
			std::cout << s << " }" << std::endl;
		}

		static void PrintVector(vector<char> vec, string optionalPrepend = "") {
			string s = optionalPrepend + "{ ";
			for (int i = 0; i < vec.size(); ++i) {
				s.push_back(vec[i]);
				if (i < vec.size() - 1) {
					s.append(", ");
				}
			}
			std::cout << s << " }" << std::endl;
		}
	}
}