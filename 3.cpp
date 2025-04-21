#include <regex>
#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
    std::ifstream infile("3.txt");

    uint32_t count = 0;
    std::string line;

    std::regex mul_regex("mul\\(([0-9]+),([0-9]+)\\)");
    uint64_t sum = 0;
    while (std::getline(infile, line))
    {
        for (std::smatch match; std::regex_search(line, match, mul_regex);) {
            sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
            line = match.suffix();
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
