#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <optional>

// Returns false if diff does not respect the requirements. Will set 'increasing' if currently std::nullopt.
bool checkDiff(std::optional<bool>& increasing, int diff) {
    if (increasing.has_value()) {
        if ((*increasing && diff < 0) || (!*increasing && diff > 0)) {
            return false;
        }
    } else {
        increasing = (diff > 0);
    }

    diff = std::abs(diff);
    if (diff == 0 || diff > 3) {
        return false;
    }

    return true;
}

int main() {
    std::ifstream infile("2.txt");

    uint32_t count = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);

        int prev, curr;
        iss >> prev;

        bool isOk = true;
        std::optional<bool> increasing = std::nullopt;

        while (iss >> curr && isOk) {
            int diff = curr - prev;
            if (!checkDiff(increasing, diff)) {
                isOk = false;
            }

            prev = curr;
        }

        if (isOk) 
            count++;
    }

    std::cout << count << std::endl;

    return 0;
}
