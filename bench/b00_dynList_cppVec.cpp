#include <cstddef>
#include <vector>

int main() {
    auto vec = std::vector<std::size_t>();

    std::size_t i = 1000;
    while (i --> 0)
        vec.push_back(i);

    vec.clear();

    return 0;
}
