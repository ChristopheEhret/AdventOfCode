#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <optional>
#include <vector>

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

bool check(std::vector<int>& val_list, int prev_val, int curr_i, std::optional<bool> increasing, bool hasRemovedValue) {
    if(curr_i >= val_list.size()) 
        return true;

    int diff = val_list[curr_i] - prev_val;

    if (!checkDiff(increasing, diff)) {
        if (hasRemovedValue)
            return false;
        else
            return check(val_list, val_list[curr_i - 1], curr_i + 1, increasing, true) || check(val_list, val_list[curr_i - 2], curr_i, increasing, true);
    }

    return check(val_list, val_list[curr_i], curr_i + 1, increasing, hasRemovedValue);
}

int main() {
    std::ifstream infile("2.txt");

    uint32_t count = 0;
    std::string line;
    std::vector<int> v;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);

        v.clear();
        for (int a; iss >> a;) {
            v.push_back(a);
        }

        if (check(v, v[0], 1, std::nullopt, false) || check(v, v[1], 2, std::nullopt, true) || check(v, v[0], 2, std::nullopt, true)) {
            count++;
        }
    }

    std::cout << count << std::endl;

    return 0;
}
