#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec {0, 5, 2, 9, 7, 6, 1, 3, 4, 8};
    int comparison_count = 0;

    std::sort(vec.begin(), vec.end(), [&comparison_count](int a, int b) {
        ++comparison_count;
        return a < b;
    });

    std::cout << "Sorted vector: ";
    for (const auto& el : vec) {
        std::cout << el << ' ';
    }
    std::cout << "\nNumber of comparisons: " << comparison_count << std::endl;

    return 0;
}
