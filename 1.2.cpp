#include <fstream>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cstdint>

int main() {
    std::vector<int> l1(1000);
    std::unordered_map<int, size_t> l2(1000);

    std::ifstream infile("1.txt");
    int a, b;
    while (infile >> a >> b)
    {
        l1.push_back(a);

        auto i2 = l2.find(b);
        if (i2 == l2.end())
            l2[b] = 1;
        else 
            i2->second++;
    }
    
    uint64_t score = 0;
    for(size_t i = 0; i < l1.size(); i++) {
        auto i2 = l2.find(l1[i]);
        if (i2 != l2.end())
            score += l1[i] * i2->second;
    }

    std::cout << score << std::endl;

    return 0;
}
