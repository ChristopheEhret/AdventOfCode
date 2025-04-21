#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <array>

bool checkDiag(std::pair<int, int> origin, std::pair<int, int> direction, std::array<std::array<char, 140>, 140> puzzle) {
    auto c1 = puzzle[origin.first + direction.first][origin.second + direction.second];
    auto c2 = puzzle[origin.first - direction.first][origin.second - direction.second];

    return (c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M');
}

int main() {
    // I will assume the input is 140x140 to make my life easier. It would be easy to test the file size beforehand, just a little time consuming
    std::array<std::array<char, 140>, 140> puzzle;

    std::ifstream infile("4.txt");

    uint32_t count = 0;
    std::string line;
    for (int i = 0; std::getline(infile, line); i++) {
        std::memcpy(puzzle[i].begin(), line.c_str(), 140);
    }

    for(int x = 1; x < 139; x++) {
        for (int y = 1; y < 139; y++) {
            if (puzzle[y][x] == 'A') {
                if (checkDiag({y, x}, {1, 1}, puzzle) && checkDiag({y, x}, {1, -1}, puzzle))
                    count ++;
            }
        }
    }

    std::cout << count << std::endl;
    return 0;
}

