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

int main(int argc, char* argv[]) {
    const std::string baseFilePath = "./inputs/";
    FileInput input = getVectorizedFileInput(baseFilePath + "test01.txt");
    PRINT_INPUT_SIZE(input);

    const std::string customFilePath = "./inputs/hacker_rank/interview_prep_kit/strings/commonchild/";
    const std::vector<std::vector<std::string>> cases({
        {customFilePath + "sample01.txt", "2"},    //
        {customFilePath + "sample02.txt", "0"},    //
        {customFilePath + "sample03.txt", "3"},    //
        {customFilePath + "input01.txt", "15"},    //
        {customFilePath + "input02.txt", "27"},    //
        {customFilePath + "input04.txt", "321"},   //
        {customFilePath + "input05.txt", "1417"},  //
        {customFilePath + "input10.txt", "1618"},  //
        {customFilePath + "input13.txt", "1618"},  //
    });

    for (const std::vector<std::string>& vs : cases) {
        std::string inputstring = mgcp::FileHelper::ReadFile(vs[0]);
        std::vector<std::string> inputsplit = mgcp::SplitString(inputstring, '\n');
        // cout << "size of input: " << inputsplit[0].size() << '\n';

        // int answer = commonChild(inputsplit[0], inputsplit[1]);
        // cout << "substrCount: " << answer << " expected: " << vs[1] << '\n';

        // IntegerFileInput fileInput(getVectorizedFileInput(s));
        // PRINT_INPUT_SIZE(fileInput);
    }
}