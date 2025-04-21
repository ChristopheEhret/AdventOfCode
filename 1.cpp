#include <fstream>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdint>

// Dichotomy insert
void insert(std::vector<int>& v, int val) {
    size_t a = 0;
    size_t b = v.size();

    while (a < b) {
        auto i = (a + b) / 2;
        if (val > v[i]) {
            a = i + 1;
        } else {
            b = i;
        }
    }

    v.insert(v.begin() + a, val);
}

int main() {
    std::vector<int> l1(1000);
    std::vector<int> l2(1000);

    std::ifstream infile("1.txt");
    int a, b;
    while (infile >> a >> b)
    {
        insert(l1, a);
        insert(l2, b);
    }
    
    uint64_t diff = 0;
    for(size_t i = 0; i < l1.size() && i < l2.size(); i++) {
        diff += std::abs(l1[i] - l2[i]);
    }

    std::cout << diff << std::endl;

    return 0;
}
