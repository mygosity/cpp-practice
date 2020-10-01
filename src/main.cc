#include "main.h"

#include <algorithm>
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

    const std::string customFilePath = "./_logs/hacker_rank/interview_prep_kit/sorting/mergesort/";
    const std::vector<std::string> cases({
        customFilePath + "customin01.txt",  //
        customFilePath + "customin02.txt",  //
        customFilePath + "customin03.txt",  //
        customFilePath + "customin04.txt",  //
        customFilePath + "customin05.txt",  //
    });

    for (const std::string& s : cases) {
        IntegerFileInput fileInput(getVectorizedFileInput(s));
        PRINT_INPUT_SIZE(fileInput);
    }
}