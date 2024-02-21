#include <cstddef>
#include <vector>

int main() {
    auto vec = std::vector<std::size_t>();

    vec.reserve(1000);

    std::size_t i = 1000;
    while (i --> 0) {
        vec.emplace_back(i);
    }

    vec.clear();

    return 0;
}
