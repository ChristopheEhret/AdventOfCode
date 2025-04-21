#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <array>

std::array<char, 3> word_end = {'M', 'A', 'S'};

// Check a diagonal of three characters, returns true if it matches 'MAS'
bool checkDir(std::pair<int, int> origin, std::pair<int, int> direction, std::array<std::array<char, 140>, 140> puzzle) {
    for(int i = 0; i < 3; i++) {
        origin.first += direction.first;
        origin.second += direction.second;
        
        if (origin.first < 0 || origin.first >= 140 || origin.second < 0 || origin.second >= 140) 
            return false;

        if (puzzle[origin.first][origin.second] != word_end[i])
            return false;
    }

    return true;
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

    for(int x = 0; x < 140; x++) {
        for (int y = 0; y < 140; y++) {
            if (puzzle[y][x] == 'X') {
                for (int dx = -1; dx < 2; dx ++) {
                    for (int dy = -1; dy < 2; dy ++) {
                        if (dx == 0 && dy == 0)
                            continue;

                        if(checkDir({y, x}, {dy, dx}, puzzle))
                            count ++;
                    }
                }
            }

        }
    }

    std::cout << count << std::endl;
    return 0;
}

