#include "../include/example.hpp"
#include <algorithm>
#include <numeric>

namespace cpptest {

std::pair<int, std::string> Example::getData() const {
    return {42, "Hello C++17!"};
}

std::optional<int> Example::findValue(const std::vector<int>& vec, int target) const {
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        return *it;
    }
    return std::nullopt;
}

int Example::sumVector(const std::vector<int>& vec) const {
    return std::accumulate(vec.begin(), vec.end(), 0);
}

} // namespace cpptest
