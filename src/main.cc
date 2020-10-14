#include "main.h"

#include <algorithm>
#include <array>
#include <deque>
#include <list>
#include <map>
#include <vector>

using namespace std;

#define STRINGIFY(s) #s
#define TEST_ANSWER(tag, yourAnswer, theirAnswer) std::cout << tag << "\nyour: " << yourAnswer << "\nthem: " << theirAnswer << '\n';
#define PRINT_INPUT_SIZE(input) std::cout << STRINGIFY(input) << " args: " << input.args.size() << " data: " << input.data.size() << '\n';

// based off of HackerRank input files
struct FileInput {
    std::vector<std::string> args;
    std::vector<std::string> data;
};

FileInput getVectorizedFileInput(const std::string& filepath) {
    std::string inputstring = mgcp::FileHelper::ReadFile(filepath);
    std::vector<std::string> inputsplit = mgcp::SplitString(inputstring, '\n');

    FileInput input;
    input.args = mgcp::SplitString(inputsplit[0], ' ');
    input.data = mgcp::SplitString(inputsplit[1], ' ');
    return input;
}

struct IntegerFileInput {
    IntegerFileInput(FileInput fi) {
        for (std::string& s : fi.args) args.push_back(std::stoi(s));
        for (std::string& s : fi.data) data.push_back(std::stoi(s));
    }
    std::vector<int> args;
    std::vector<int> data;
};

static std::array<std::array<int, 5001>, 5001> dp;

int commonChild(string& s1, string& s2, int i = 0, int j = 0) {
    if (i == 0 && j == 0) {
        for (auto& itr : dp)
            for (auto& itry : itr) itry = -1;

        // letters1.clear();
    }
    if (i >= s1.size() - 1 || j >= s2.size() - 1) return 0;
    int total = 0;

    vector<int> letters1(26, -1);
    for (; i < s1.size(); ++i) {
        const int c = (int)s1[i] - (int)'A';
        if (letters1[c] == -1) {
            letters1[c] = i;
        }
    }
    vector<int> letters2(26, -1);
    int max = 0;
    int earliestIndex = 15001;

    for (; j < s2.size(); ++j) {
        const int c = (int)s2[j] - (int)'A';
        const int targetIndex = letters1[c];
        if (targetIndex > -1 && targetIndex < earliestIndex && letters2[c] == -1) {
            earliestIndex = targetIndex;

            int currentLength = 1;
            letters2[c] = targetIndex;
            if (targetIndex + 1 < 5000 && j + 1 < 5000) {
                int v = dp[targetIndex + 1][j + 1];
                if (v == -1) {
                    int value = commonChild(s1, s2, targetIndex + 1, j + 1);
                    dp[targetIndex + 1][j + 1] = value;
                    currentLength += value;
                } else {
                    currentLength += v;
                }
                if (currentLength > max) {
                    max = currentLength;
                }
            }
            if (earliestIndex == i) break;
        }
    }
    total += max;
    return total;
}

// static map<double, int> chklist;

// int commonChild(string& s1, string& s2, int i = 0, int j = 0) {
//     if (i == 0 && j == 0) {
//         chklist.clear();
//     }
//     if (i >= s1.size() - 1 || j >= s2.size() - 1) return 0;
//     // cout << "i: " << i << " j: " << j << '\n';
//     int total = 0;
//     vector<int> letters1(26, -1);
//     for (; i < s1.size(); ++i) {
//         const int c = (int)s1[i] - (int)'A';
//         if (letters1[c] == -1) letters1[c] = i;
//     }
//     vector<int> letters2(26, -1);
//     int max = 0;
//     for (; j < s2.size(); ++j) {
//         const int c = (int)s2[j] - (int)'A';
//         const int targetIndex = letters1[c];
//         if (targetIndex > -1) {
//             if (letters2[c] == -1) {
//                 int currentLength = 1;
//                 letters2[c] = targetIndex;
//                 double hash = (targetIndex + 1) + s1.size() * (j + 1);
//                 const auto target = chklist.find(hash);
//                 if (target == chklist.end()) {
//                     int value = commonChild(s1, s2, targetIndex + 1, j + 1);
//                     chklist.insert({hash, value});
//                     currentLength += value;
//                 } else {
//                     currentLength += target->second;
//                 }
//                 if (currentLength > max) {
//                     max = currentLength;
//                 }
//             }
//         }
//     }
//     total += max;
//     return total;
// }

int main(int argc, char* argv[]) {
    const std::string baseFilePath = "./inputs/";
    FileInput input = getVectorizedFileInput(baseFilePath + "test01.txt");
    PRINT_INPUT_SIZE(input);

    const std::string customFilePath = "./inputs/hacker_rank/interview_prep_kit/strings/commonchild/";
    const std::vector<std::vector<std::string>> cases({
        {customFilePath + "sample01.txt", "2"},  //
        {customFilePath + "sample02.txt", "0"},  //
        {customFilePath + "sample03.txt", "3"},  //
        {customFilePath + "input01.txt", "15"},  //
        {customFilePath + "input02.txt", "27"},  //
        // {customFilePath + "input04.txt", "321"},   //
        // {customFilePath + "input05.txt", "1417"},  //
        // {customFilePath + "input10.txt", "1618"},  //
        // {customFilePath + "input13.txt", "1618"},  //
    });

    for (const std::vector<std::string>& vs : cases) {
        std::string inputstring = mgcp::FileHelper::ReadFile(vs[0]);
        std::vector<std::string> inputsplit = mgcp::SplitString(inputstring, '\n');
        // cout << "size of input: " << inputsplit[0].size() << '\n';

        int answer = commonChild(inputsplit[0], inputsplit[1]);
        cout << "substrCount: " << answer << " expected: " << vs[1] << '\n';

        // IntegerFileInput fileInput(getVectorizedFileInput(s));
        // PRINT_INPUT_SIZE(fileInput);
    }
}