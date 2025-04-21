#include <regex>
#include <iostream>
#include <fstream>
#include <cstdint>

int main() {
    std::ifstream infile("3.txt");

    uint32_t count = 0;
    std::string line;

    std::regex mul_regex("mul\\(([0-9]+),([0-9]+)\\)");
    std::regex do_nt_regex("do(n't)?\\(\\)");
    uint64_t sum = 0;
    bool shouldDo = true;
    while (std::getline(infile, line))
    {
        // Find dos and donts
        for (std::smatch do_nt_match; std::regex_search(line, do_nt_match, do_nt_regex);) {
            // If last instruction is not don't
            if (shouldDo) {
                // Find mul instructions
                auto prefix = do_nt_match.prefix().str();
                for (std::smatch match; std::regex_search(prefix, match, mul_regex);) {
                    sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
                    prefix = match.suffix();
                }
            } 

            shouldDo = !do_nt_match[1].matched;
            line = do_nt_match.suffix();
        }

        // If last instruction is not don't
        if (shouldDo) {
            // Find mul instructions
            for (std::smatch match; std::regex_search(line, match, mul_regex);) {
                sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
                line = match.suffix();
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
