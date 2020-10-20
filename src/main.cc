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

vector<int> isComplete(vector<int>& arr) {
    // determine if the array has all but one matching value
    map<int, int> values;
    vector<int> uniqueValues;
    for (int i = 0; i < arr.size(); ++i) {
        const int c = arr[i];
        if (values.find(c) == values.end()) {
            if (uniqueValues.size() >= 2) {
                // not valid
                return {};
            }
            values.insert({c, 1});
            uniqueValues.push_back(c);
        } else {
            ++values[c];
        }
    }
    if (uniqueValues.size() == 2 && (values[uniqueValues[0]] == 1 || values[uniqueValues[1]] == 1)) {
        return uniqueValues;
    }
    return {};
}

// Complete the equal function below.
int equal(vector<int> arr) {
    std::sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });
    int total = INT32_MAX;

    for (int j = 0; j < 3; ++j) {
        int target = arr[0] - j;
        int currentTotal = j == 0 ? 0 : 1;
        for (int i = 1; i < arr.size(); ++i) {
            const int c = arr[i];
            if (c != target) {
                int targetGoal = c - target;
                int fives = targetGoal / 5;
                int twos = (targetGoal % 5) / 2;
                int remaining = (targetGoal % 5) % 2;
                currentTotal += fives + twos + remaining;
            }
        }
        total = std::min(currentTotal, total);
    }
    return total;
}

int public_answer_equal(vector<int> a) {
    const int n = a.size();

    // giving x chocs to every colleague other than chosen one
    // is the same as taking away x chocs from the chosen one
    int min = *min_element(a.begin(), a.end());
    int numops = 0;

    // consider taking away 5 chocs first (nChocs)
    for (int i = 0; i < n; i++) {
        int nChocs = floor((a[i] - min) / 5.0);
        a[i] -= (5 * floor((a[i] - min) / 5.0));
        numops += nChocs;
    }
    min = *min_element(a.begin(), a.end());  // min of leftovers in a[]

    // fine tuning for last calc, get freq of diff first
    vector<int> freq(5);  // stores diff of 0 to 4
    for (int i = 0; i < n; i++) freq[a[i] - min]++;

    // case of min num of chocs is min
    int extra_numops = 1 * (freq[1] + freq[2]) + 2 * (freq[3] + freq[4]);

    // case of min num of chocs is min-1
    int extra_numops1 = 1 * (freq[0] + freq[1] + freq[4]) + 2 * (freq[2] + freq[3]);
    if (extra_numops1 < extra_numops) extra_numops = extra_numops1;

    // case of min num of chocs is min-2
    int extra_numops2 = 1 * (freq[0] + freq[3]) + 2 * (freq[1] + freq[2] + freq[4]);
    if (extra_numops2 < extra_numops) extra_numops = extra_numops2;

    // cout << numops + extra_numops << endl;
    return numops + extra_numops;
}

int main(int argc, char* argv[]) {
    const std::string baseFilePath = "./inputs/";
    FileInput input = getVectorizedFileInput(baseFilePath + "test01.txt");
    PRINT_INPUT_SIZE(input);

    const std::string customFilePath = "./inputs/hacker_rank/dynamic_programming/equal/";

    const std::string answer15File = "answer15.txt";
    std::string answer15String = mgcp::FileHelper::ReadFile(customFilePath + answer15File);
    mgcp::StringReplace(answer15String, "\n", " ");
    const std::vector<std::vector<std::string>> cases({
        {customFilePath + "sample01.txt", "10605 8198 18762 16931 5104"},  //
        {customFilePath + "sample02.txt", "2"},                            //
        // {customFilePath + "sample03.txt", "3"},    //
        // {customFilePath + "input01.txt", "15"},    //
        // {customFilePath + "input02.txt", "27"},    //
        // {customFilePath + "input04.txt", "321"},   //
        // {customFilePath + "input05.txt", "1417"},  //
        // {customFilePath + "input10.txt", "1618"},  //
        {customFilePath + "input11.txt", "3"},             //
        {customFilePath + "input12.txt", "7"},             //
        {customFilePath + "input13.txt", "6"},             //
        {customFilePath + "input15.txt", answer15String},  //
    });

    for (const std::vector<std::string>& vs : cases) {
        std::string inputstring = mgcp::FileHelper::ReadFile(vs[0]);
        std::vector<std::string> inputsplit = mgcp::SplitString(inputstring, '\n');

        // vector<string> fargs = mgcp::SplitString(inputsplit[0], ' ');
        // vector<int> args;
        // for (std::string& s : fargs) args.push_back(std::stoi(s));

        std::vector<std::string> expected = mgcp::SplitString(vs[1], ' ');
        for (int i = 2, j = 0; i < inputsplit.size(); i += 2, ++j) {
            vector<string> fdata = mgcp::SplitString(inputsplit[i], ' ');
            vector<int> data;
            for (std::string& s : fdata) data.push_back(std::stoi(s));
            auto answer = equal(data);
            cout << "answer: " << answer << " expected: " << expected[j] << '\n';
        }
    }
}