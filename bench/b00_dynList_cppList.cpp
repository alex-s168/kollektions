#include <cstddef>
#include <list>

int main() {
    auto list = std::list<std::size_t>();

    std::size_t i = 1000;
    while (i --> 0)
        list.push_back(i);

    list.clear();

    return 0;
}
